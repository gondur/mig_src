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

///------------------------------------------------------------------------------
//Filename	transite.cpp
//System
//Author	 Martin Alderton
//Date		Thu 22 Feb 1996
//Description	TransientItem routines.
//------------------------------------------------------------------------------
//NOT INITIALISED!!!			lrstate /= 85;										//RJS 21Feb97

#define	ANGLES_MATHABLE
#define F_GRAFIX												//DAW 05Aug96
#define F_BATTLE
#include	"dosdefs.h"
#include	"worldinc.h"

#include	"world.h"											//MGA 27Feb96
#include	"myerror.h"


#include	"transite.h"
#include	"shapes.h"
#include	"myangles.h"
#include	"LandScap.h"										//MGA 29Mar96
#include	"MyTime.h"											//PD 26Apr96
#include	"collided.h"										//PD 29Apr96
//MATHABLE	(ANGLES);
#include	"mymath.h"
#include	"miles.h"
#include	"3dcom.h"
#include	"missman2.h"										//RDH 03Oct96
#include	"viewsel.h"											//MGA 22Mar96
#include	"keytest.h"											//PD 29Apr96
//#include	"3dinstr.h"											//PD 01May96
#include	"flymodel.h"										//PD 02May96

#include	"persons2.h"
#include	"files.g"
#include	"deathnum.g"										//RJS 29Jul96
#include "bitfield.h"											//DAW 23Aug96
//#include	"misssub.h"										//RJS 08Aug96
#include	"savegame.h"										//PD 02Sep96
#include	"boxcol.h"										//PD 02Sep96
#include	"ranges.h"										//PD 02Sep96
#include	"Mytime.h"										//PD 02Sep96
#include	"speed.h"											//RJS 15Dec96
#include	"modinst.h"
#include	"model.h"											//RJS 08Apr98
#include	"3dcode.h"
#include	"winmove.h"											//ARM 05Sep96
#include	"ai.h"
#include	"rchatter.h"										//RJS 11Jun98
#include	"globrefs.h"
#include	"shapenam.h"										//RJS 20Nov98
#include	"overlay.h"

#include	"anmradio.h"


int firstroll = NULL;								//MGA 03Apr96
//extern	ULong	GR_Quit3DNow,									//JIM 05Dec96
//				GR_NAT_FRIEND									//JIM 05Dec96
				;												//JIM 05Dec96

TransObj Trans_Obj;
int	TransientItem::transcount=0;
extern void	CheckE3();
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		TransObj
//Author		Martin Alderton
//Date			Tue 5 Mar 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
TransObj::TransObj()
{
	TransToGoList=NULL;											//PD 11May96
	shootdelay = DefaultShootDelay;								//PD 29Apr96
	autobulletcount=0;											//PD 29Apr96
	transientcounter = 0;										//PD 24Jul96
	vapourcount = 0;
	fakeshootdelay = 0;											//RJS 21Apr98

	StaticTrailCnt = 0;											//RJS 18Feb99
	StaticTrailIndex = 0;										//RJS 18Feb99
	trailcounter = 0;											//RJS 06Apr99

	HitTheDeck = false;											//RDH 09May99

	realFrameTime = 0;											//RJS 27May99
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		~TransObj
//Author		Martin Alderton
//Date			Tue 5 Mar 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
TransObj::~TransObj()
{
	TransToGoList=NULL;				//MGA 27Feb96
}
void	TransObj::SetViewPoint(MobileItem* vp,ViewPoint* vo)
{
	View_Point=vp;
	View_Object=vo;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AddTransientItemToWorld
//Author		Martin Alderton
//Date			Tue 27 Feb 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void TransObj::AddTransientItemToWorld(TransientItemPtr transitem,WorldStuff& world)
{

//TempCode MGA 07Mar96	World_Stuff.AddToWorld(transitem);
	
	world.AddToWorld((itemptr)transitem);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AddTransientItemToDeadList
//LastModified:	RDH 25Jul96
//Author		Martin Alderton
//Date			Tue 27 Feb 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void TransObj::AddTransientItemToDeadList(TransientItemPtr transitem, bool novapour)
{
	if (!transitem->isOwned && !transitem->isDeleted)
	{
		SLong	newlife = SHAPE.DetatchAllVapourStreams(transitem,400,novapour);//RJS 19May99
		if (newlife > 0)											//RJS 06Apr99
			transitem->LaunchTime = newlife;
		else
		{
	//DeadCode JIM 06Jan97	CheckE3();
			transitem->movecode=MOBILE_NOPPILOT;						//RJS 09Dec98
			transientcounter--;											//PD 24Jul96
			TransientItemPtr temp;
			transitem->transcount--;

			transitem->LaunchTime = 0x7FFFFFFF;					//RJS 04Jun99
			transitem->TimeOfLaunch = 0xFFFFFFFF;				//RJS 04Jun99
			transitem->isDeleted = 1;							//RJS 14May99

			//if newlife == -1, then this is a transient trail dying...//RJS 06Apr99
			if (newlife)											//RJS 06Apr99
				trailcounter--;										//RJS 06Apr99

		//	OverLay.speed = transientcounter;

	//DeadCode RJS 21Jan99	SHAPE.DetatchAllVapourStreams(transitem,400);	//RJS 04Sep98

			if (TransToGoList==NULL)
			{
				TransToGoList=*transitem;
			}
			else
			{
				//Debug code to check whether the item has already been
				//added to the dead list

				temp=TransToGoList;

				for(;;)
				{
					if (temp==transitem)
					{
						_Miles.HaltItemSound((ItemBasePtr) transitem);
						return;
					}

					if (temp->nexttogo)							//RJS 24Mar98
						temp = temp->nexttogo;
					else
					{
						temp->nexttogo = transitem;
						break;
					}
				}

		//		temp->nexttogo = transitem;

		//DeadCode JIM 07Oct96		transitem->nexttogo = NULL;
			}

			transitem->nexttogo = NULL;
			_Miles.HaltItemSound((ItemBasePtr) transitem);
		//DeadCode JIM 06Jan97	CheckE3();
		}
	}
}

//TempCode MGA 27Mar96 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//TempCode MGA 27Mar96 //Procedure		gettranslist
//TempCode MGA 27Mar96 //Author		Martin Alderton
//TempCode MGA 27Mar96 //Date			Wed 13 Mar 1996
//TempCode MGA 27Mar96 //
//TempCode MGA 27Mar96 //Description	allows access to protected TransientList by transite functions
//TempCode MGA 27Mar96 //
//TempCode MGA 27Mar96 //Inputs		
//TempCode MGA 27Mar96 //
//TempCode MGA 27Mar96 //Returns	
//TempCode MGA 27Mar96 //
//TempCode MGA 27Mar96 //------------------------------------------------------------------------------
//TempCode MGA 27Mar96 TransientItemPtr TransientItem::gettranslist(void)
//TempCode MGA 27Mar96 {
//TempCode MGA 27Mar96	TransientItemPtr retval = new TransientItem;
//TempCode MGA 27Mar96	retval->Launcher	= TransientList->Launcher;
//TempCode MGA 27Mar96	retval->Target		= TransientList->Target;
//TempCode MGA 27Mar96	retval->LaunchTime	= TransientList->LaunchTime;
//TempCode MGA 27Mar96	retval->shape		= TransientList->shape;
//TempCode MGA 27Mar96	retval->Next		= TransientList->Next;
//TempCode MGA 27Mar96	retval->nexttogo	= TransientList->nexttogo;
//TempCode MGA 27Mar96	retval->nextmobile	= TransientList->nextmobile;
//TempCode MGA 27Mar96	retval->nexttrans	= TransientList->nexttrans;
//TempCode MGA 27Mar96	retval->waypoint	= TransientList->waypoint;
//TempCode MGA 27Mar96	retval->movecode	= TransientList->movecode;
//TempCode MGA 27Mar96	retval->roll		= TransientList->roll;
//TempCode MGA 27Mar96	retval->pitch		= TransientList->pitch;
//TempCode MGA 27Mar96	retval->hdg			= TransientList->hdg;
//TempCode MGA 27Mar96	retval->Next		= TransientList->Next;
//TempCode MGA 27Mar96	retval->World		= TransientList->World;
//TempCode MGA 27Mar96	retval->velx		= TransientList->velx;
//TempCode MGA 27Mar96	retval->velz		= TransientList->velz;
//TempCode MGA 27Mar96	retval->vely		= TransientList->vely;
//TempCode MGA 27Mar96	retval->velhori		= TransientList->velhori;
//TempCode MGA 27Mar96	retval->vel			= TransientList->vel;
//TempCode MGA 27Mar96 //TempCode MGA 27Mar96	retval->Anim		= TransientList->Anim;
//TempCode MGA 27Mar96	retval->Status		= TransientList->Status;
//TempCode MGA 27Mar96	retval->uniqueID	= TransientList->uniqueID;
//TempCode MGA 27Mar96	retval->despos		= TransientList->despos;
//TempCode MGA 27Mar96
//TempCode MGA 27Mar96	//I may not yet have all the options covered here			//MGA 26Mar96
//TempCode MGA 27Mar96
//TempCode MGA 27Mar96	return (retval);
//TempCode MGA 27Mar96 }

//DeadCode JIM 07Oct96 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode JIM 07Oct96 //Procedure		FindInTransientList
//DeadCode JIM 07Oct96 //Author		Martin Alderton
//DeadCode JIM 07Oct96 //Date			Thu 29 Feb 1996
//DeadCode JIM 07Oct96 //
//DeadCode JIM 07Oct96 //Description	
//DeadCode JIM 07Oct96 //
//DeadCode JIM 07Oct96 //Inputs		
//DeadCode JIM 07Oct96 //
//DeadCode JIM 07Oct96 //Returns	
//DeadCode JIM 07Oct96 //
//DeadCode JIM 07Oct96 //------------------------------------------------------------------------------
//DeadCode JIM 07Oct96 int TransObj::FindInTransientList(TransientItemPtr transit)
//DeadCode JIM 07Oct96 {
//DeadCode JIM 07Oct96	int retval=-1;
//DeadCode JIM 07Oct96	int count=0;
//DeadCode JIM 07Oct96
//DeadCode JIM 07Oct96 //TempCode MGA 13Mar96	TransientItemPtr testlist = mobileitem::TransientList;
//DeadCode JIM 07Oct96
//DeadCode JIM 07Oct96	TransientItemPtr testlist;
//DeadCode JIM 07Oct96 //TempCode MGA 27Mar96	testlist=TransientItem::gettranslist();
//DeadCode JIM 07Oct96	testlist=TransientItem::TransientList;
//DeadCode JIM 07Oct96
//DeadCode JIM 07Oct96
//DeadCode JIM 07Oct96	while (testlist!=NULL)
//DeadCode JIM 07Oct96	{
//DeadCode JIM 07Oct96		if (testlist->uniqueID.count==transit->uniqueID.count)
//DeadCode JIM 07Oct96		{
//DeadCode JIM 07Oct96			retval=count;
//DeadCode JIM 07Oct96		}
//DeadCode JIM 07Oct96		testlist=testlist->nexttrans;
//DeadCode JIM 07Oct96		count++;
//DeadCode JIM 07Oct96	}
//DeadCode JIM 07Oct96	return(retval);
//DeadCode JIM 07Oct96 }
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		KillTheDeadList
//Author		Martin Alderton
//Date			Thu 29 Feb 1996
//
//Description	removes the list of dead transients from the transient	list
//				and the world.
//				
//				Must not be performed during 3d-draw (object may get reallocated)
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void TransObj::RemoveDeadListFromWorld()
{
	WorldStuff &world=*MobileItem::currworld;
	if (transientcounter>MaxTransients)	KillOldest();			//PD 24Jul96

	TransientItemPtr Ptr = TransientItem::TransientList;
	TransientItemPtr TempPtr = TransToGoList;
	TransientItemPtr NextToGo = NULL;

	TransientItemPtr remove = NULL;
	TransientItemPtr lastitem = NULL;
															
//DeadCode RJS 11Nov98	SHAPE.KillVapourStreamDeadList();							//RJS 09Apr98


	while (TempPtr)
	{
		NextToGo = TempPtr->nexttogo;

		lastitem =
			remove = Ptr;

		while (remove!=TempPtr)
		{
			lastitem = remove;
			remove = remove->nexttrans;
		}

		if (lastitem==remove)
			Ptr = remove->nexttrans;
		else
		{
			lastitem->nexttrans = remove->nexttrans;
		}
		world.RemoveFromWorld((itemptr)remove);

		delete (remove);

		TempPtr = NextToGo;
	}

	TransientItem::TransientList = Ptr;

	TransToGoList=NULL;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		KillOldest
//Author		Paul.
//Date			Wed 24 Jul 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void TransObj::KillOldest()
{
	SLong	trans2kill = transientcounter - MaxTransients;

//DeadCode DAW 19May99 	while (trans2kill--)
//DeadCode DAW 19May99 	{
//DeadCode DAW 19May99 		TransientItemPtr tip,otp;
//DeadCode DAW 19May99 		
//DeadCode DAW 19May99 		tip = otp = TransientItem::TransientList;
//DeadCode DAW 19May99 
//DeadCode DAW 19May99 		tip = tip->nexttrans;
//DeadCode DAW 19May99 
//DeadCode DAW 19May99 		while (tip)
//DeadCode DAW 19May99 		{
//DeadCode DAW 19May99 			if (tip->LaunchTime<otp->LaunchTime)
//DeadCode DAW 19May99 				otp = tip;
//DeadCode DAW 19May99 
//DeadCode DAW 19May99 			tip = tip->nexttrans;
//DeadCode DAW 19May99 		}
//DeadCode DAW 19May99 
//DeadCode DAW 19May99 		otp->LaunchTime = 0x7FFFFFFF;
//DeadCode DAW 19May99 
//DeadCode DAW 19May99 		AddTransientItemToDeadList(otp);
//DeadCode DAW 19May99 	}

	while (trans2kill--)
	{
		TransientItemPtr tip;
		TransientItemPtr oldestdeletable;
		TransientItemPtr oldest;
		
		tip = oldestdeletable = oldest = TransientItem::TransientList;

		tip = tip->nexttrans;

		while (tip)
		{
			if (	!tip->isDeleted	&& !tip->isOwned
				&&	(tip->TimeOfLaunch < oldestdeletable->TimeOfLaunch)	)
			{
				oldest = tip;
				if (!tip->isArmed)
					oldestdeletable = tip;
			}

			tip = tip->nexttrans;
		}

		//Did we find anything to kill???
		if (oldestdeletable == TransientItem::TransientList)		//RJS 02Jul99
			break;
		else
			AddTransientItemToDeadList(oldestdeletable,true);		//RJS 19May99
	}

	//Has to be called after KillOldest!!!!!!!!!!!!!
	SHAPE.GenerateProbeTrails();								//RJS 19May99
	SHAPE.KillVapourStreamDeadList();							//RJS 19May99
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CountTheTransients
//Author		Martin Alderton
//Date			Tue 27 Feb 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
int TransObj::CountTheTransients(TransientItemPtr trans)
{
	int counter=0;
	TransientItemPtr translist;
	translist=trans;

	while (translist!=NULL)
	{
		counter++;
		translist=translist->nexttrans;
	}

	translist=NULL;
	return(counter);
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CountTheDeadTransients
//Author		Martin Alderton
//Date			Tue 27 Feb 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
int TransObj::CountTheDeadTransients(TransientItemPtr trans)
{
	int counter=0;
	TransientItemPtr translist;
	translist=trans;

	while (translist!=NULL)
	{
		counter++;
		translist=translist->nexttogo;
	}

	translist=NULL;
	return(counter);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DeleteTransientItem
//Author		Martin Alderton
//Date			Thu 22 Feb 1996
//
//Description	for use deleting from master TransientList
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
TransientItemPtr TransObj::DeleteTransientItem(TransientItemPtr translist)
{
	TransientItemPtr temp;
	temp = translist->nexttrans;

	delete translist;

	return(temp);
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DeleteTransientItem
//Author		Martin Alderton
//Date			Thu 22 Feb 1996
//
//Description	for use with TransToGoList
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
TransientItemPtr TransObj::DeleteTempTransientItem(TransientItemPtr translist)
{
	TransientItemPtr temp;

	temp = translist->nexttogo;

//TempCode MGA 27Mar96	delete translist;

	return (temp);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DeleteAll
//Author		Martin Alderton
//Date			Thu 22 Feb 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void TransObj::DeleteAll()
{
	//Clear world frees the items so all that needs doing
	//is emptying the list
	TransientItem::transcount=0;
	TransToGoList=NULL;											//PD 11May96
	shootdelay = DefaultShootDelay;								//PD 29Apr96
	autobulletcount=0;											//PD 29Apr96
	transientcounter = 0;										//RJS 21Aug96
	trailcounter = 0;											//RJS 06Apr99
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetRand
//Author		Martin Alderton
//Date			Tue 2 Apr 1996
//
//Description	gets a rnd from mathlib. returns a no between 1 and 6.
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
int TransObj::GetRand()
{
	int retval;
	UWord temp;

	temp = Math_Lib.rnd(6);

	retval = temp + 1;

	return(retval);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MobileCarpetStrike
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
void TransObj::MobileCarpetStrike(TransientItemPtr transit,WorldStuff& world)
{
	SLong	timeleft = transit->LaunchTime;
	
	if (timeleft > 0)
	{
		if ((transit->LaunchTime-=Timer_Code.FRAMETIME)<0)		//DAW 31Jul96
			transit->LaunchTime=0;

		timeleft = transit->TransRandom;
		timeleft -= Timer_Code.FRAMETIME;
		if (timeleft <= 0)
		{
			//Explode...
			Coords3D hitcoords;
			Coords3D oldhitcoords;
			UByte	theArea;
			itemptr	hititem;
			int		gindex;
#ifndef NDEBUG
#ifdef CARPETTRACE
// defined in rchatter.h
	UWord cw=GETFPCW();
	::AfxTrace("...strike 0x%x\n",transit);
	SETFPCW(cw);
#endif
#endif
			
			oldhitcoords = transit->World;
			transit->World.X += Math_Lib.rnd(2000) - 1000;
			transit->World.Z += Math_Lib.rnd(2000) - 1000;
			transit->World.Y = GetGroundLevel(transit,theArea) + METRES01;

			hititem=BoxCol::NineSectorCol(transit,hitcoords,gindex);
			if (!hititem)
			{
				hitcoords = transit->World;
				DoImpactGround(transit,hitcoords,theArea);
			}

			transit->World = oldhitcoords;
			transit->TransRandom = transit->TmpLaunchTime;
		}
		else
			transit->TransRandom = timeleft;

		if (transit->LaunchTime>0)	
			GAndFriction(transit,0);
	}
	else
		AddTransientItemToDeadList(transit);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MobileCrater
//Author		Martin Alderton
//Date			Tue 27 Feb 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void TransObj::MobileCrater(TransientItemPtr transit,WorldStuff&)//PD 26Apr96
{
	SLong	timeleft = transit->LaunchTime;
	if (timeleft)
	{
		if ((transit->LaunchTime-=Timer_Code.FRAMETIME)<0)
			transit->LaunchTime=0;

		NoGravityAndFriction(transit,RetardedDrag);
//DeadCode RJS 18Jun98		GAndFriction(transit,RetardedDrag,100);

		SLong	groundheight = GetGroundLevel(transit);			//RJS 14Apr99
		if (transit->World.Y <= groundheight)
			transit->World.Y = groundheight;
	}
	else
		AddTransientItemToDeadList(transit);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MobileNoExplosion
//Author		Martin Alderton
//Date			Wed 20 Mar 1996
//
//Description	puts unwanted transients in dead list
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void TransObj::MobileSink(TransientItemPtr transit,WorldStuff& worldptr)
{
	SLong	timeleft = transit->LaunchTime;
	UWord	roff = transit->TransRandom;

	if (timeleft)
	{
		if ((transit->LaunchTime-=Timer_Code.FRAMETIME)<0)
			transit->LaunchTime=0;

		SWord			roll,pitch;
		ShapeDescPtr	sdptr = SHAPESTUFF.GetShapePtr(transit->shape);
		SLong			size = sdptr->Size << 4;

		roll = roff & 0xF000;
		roll >>= 12;
		pitch = roll & 3;

		roll >>= 2;

		//after 4 secs, should have tilted 90deg...
		if (roll < 0)
			roll--;
		else
			roll++;

		roll *= 40;

		if (pitch < 0)
			pitch--;
		else
			pitch++;

		pitch *= 30;

		transit->roll += (Angles) roll;	
		transit->pitch += (Angles) pitch;
		transit->World.Y -= Timer_Code.FRAMETIME;

		LaunchBubbles(transit,size,worldptr);
	}
	else
	{
		// Remove the transient bridge element, and turn on the real bridge element to dead....
		MinAnimData*	mad;
		animptr			adptr = transit->Launcher->Anim;
														
		adptr += (roff & 0x0FFF);						

		mad = (MinAnimData*) adptr;						
		mad->IsInvisible = 0;

		AddTransientItemToDeadList(transit);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchDummyExplosion
//Author		Martin Alderton
//Date			Wed 20 Mar 1996
//
//Description	used to initialise TransientList. i.e. does nowt visually
//				and not even used to do this so not much use all round//MGA 29Mar96
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void TransObj::LaunchDummyExplosion(mobileitem input)
{
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchDitchEffect
//Author		Martin Alderton
//Date			Thu 29 Feb 1996
//
//Description	sets up a transientitem
//
//Inputs		a rotitem giving initial position
//				does not require a target as target is always same as launcher value
//Returns	
//
//------------------------------------------------------------------------------
void TransObj::LaunchDitchEffect(mobileitem input,WorldStuff& worldptr)
{
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchCrater
//Author		Martin Alderton
//Date			Thu 29 Feb 1996
//
//Description	sets up a transientitem
//
//Inputs		a rotitem giving initial position
//
//Returns	
//
//------------------------------------------------------------------------------
void TransObj::LaunchCrater(mobileitem *input,WorldStuff &worldptr)
{
	TransientItem*	newitem;

	newitem = SimplifiedSpriteLaunch(input,CraterShape,3000,MOBILE_STATIONARY);//RJS 12Jun98

	if (newitem)
	{
		// Make very old, so lowest priority transient...
		newitem->TimeOfLaunch -= 3000;

		newitem->TransRandom = 0;

		AddTransientItemToWorld(newitem,worldptr);
	}
}

////////////////////////////////////////////////////////////////////////////////
//
//				Specific launch code for transients
//
////////////////////////////////////////////////////////////////////////////////


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		PlayGunSound
//Author		R. Hyde
//Date			Thu 18 Jul 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void TransObj::PlayGunSound(mobileitem* launcher,WorldStuff& worldptr)

{
	FormationItemPtr flauncher = *launcher;

	if ((flauncher == Manual_Pilot.ControlledAC2) && !_Replay.Playback)	//RJS 22Apr99
	{
		if (_Miles.StartShooting(flauncher->classtype->gunsnd0,flauncher->classtype->gundelay,flauncher->classtype->gunfrequency))//RJS 31May99
			_Miles.PlayLooped(flauncher->classtype->gunsnd0, (ItemBasePtr) launcher, 128, 0, FALSE);//RJS 01Jun99
	}
	else
		_Miles.PlayLooped(flauncher->classtype->gunsnd0, (ItemBasePtr) launcher);//RJS 12Apr99
//	if (flauncher->classtype->gunsnd1 != INVALIDFILENUM)
//		_Miles.PlayLooped(flauncher->classtype->gunsnd1, (ItemBasePtr) launcher);//RJS 22Nov96


}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DropOneBomb
//Author		R. Hyde
//Date			Mon 23 Sep 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
SWord	TransObj::DropOneBomb (mobileitem* launcher,WorldStuff& world)
{
	SWord	retval =-1;												//RJS 17Jun99
	AirStrucPtr	ac = (AirStrucPtr) *launcher;
	SLong	timeleft = ac->weap.ShootDelay-Timer_Code.FRAMETIME;//RJS 05May99
	if (timeleft<0)
	{
		retval =0;													//RJS 17Jun99

		WeapAnimData*	weapon;										//RJS 29Aug96
		SLong			xpos, ypos, zpos;							//RJS 29Aug96
		UByte			index;										//RJS 29Aug96
		UWord			thisstore;									//RJS 10Sep96
		UWord			mvel;										//RJS 11May98
		UWord			mdelay = Timer_Code.FRAMETIME;				//RJS 05May99
		UWord			mburst;										//RDH 31Jul98
		UWord			weaponshape = BOMB;							//MS 20May99
		ShapeDescPtr	sdptr;

		for (index = 0; index < 8; index++)						//RJS 12May97
		{
			weapon = SHAPE.GetWeaponLauncher(ac,index,xpos,ypos,zpos,mvel,mdelay,mburst,LT_BOMB,&weaponshape);//RJS 20May99
			if (weapon)
			{
				timeleft = mdelay;									//RJS 05May99
				if (weapon->LoadedStores > 0)					//RJS 10Sep96
				{
					retval = weapon->LoadedStores;
					if (weapon->stationshape)
					{
						sdptr = SHAPESTUFF.GetShapePtr(weapon->stationshape);
						weaponshape = sdptr->Type.shapenumber;
					}

					LaunchBombDrop((mobileitem*) ac,(ShapeNum)weaponshape,xpos,ypos,zpos,world);//MS 20May99
					if (!Save_Data.gamedifficulty [GD_UNLIMITEDARM] || ac!=Manual_Pilot.ControlledAC2)//RJS 06May99
						weapon->LoadedStores--;						//RJS 10Sep96

					//don't launch bomb stacks in pairs!!!
					if (weapon->LauncherType >= LT_BOMBB29)							//RJS 17Jun99
						break;
				}
				else
				{
					if (ac == Manual_Pilot.ControlledAC2)
						_Miles.PlaySample (FIL_SFX_GUN_CLICK1, (ItemBasePtr) ac,80);//RJS 05Dec96
				}
			}
		}
	}

	ac->weap.ShootDelay = timeleft;										//RJS 05May99
	return(retval);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DropAllStores
//Author		Robert Slater
//Date			Wed 27 May 1998
//
//Description	Dumps all external stores.....
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::DropAllStores(mobileitem* ac,WorldStuff& world)
{
	DumpFuel((AirStrucPtr)ac,world);
	DumpWeapons((AirStrucPtr)ac,world);

//DeadCode RJS 27May98	WeapAnimData*	weapon;										
//DeadCode RJS 27May98	SLong			xpos, ypos, zpos;							
//DeadCode RJS 27May98	UByte			index;										
//DeadCode RJS 27May98	UWord			thisstore;
//DeadCode RJS 27May98	int				retval;
//DeadCode RJS 27May98	UWord			mvel;
//DeadCode RJS 27May98
//DeadCode RJS 27May98	for (index = 0; index < 4; index++)
//DeadCode RJS 27May98	{
//DeadCode RJS 27May98		weapon = SHAPE.GetWeaponLauncher(ac,index,xpos,ypos,zpos,mvel,LT_BOMB);
//DeadCode RJS 27May98		if (weapon)
//DeadCode RJS 27May98		{
//DeadCode RJS 27May98			if (weapon->LoadedStores > 0)				
//DeadCode RJS 27May98			{
//DeadCode RJS 27May98				retval = weapon->LoadedStores;
//DeadCode RJS 27May98				LaunchBombDrop((mobileitem*) ac,BOMB,xpos,ypos,zpos,world,TRUE);//RJS 11Jun97
//DeadCode RJS 27May98				
//DeadCode RJS 27May98				weapon->LoadedStores = 0;
//DeadCode RJS 27May98
//DeadCode RJS 27May98 //rdh 8/5/98: storesweight not used now
//DeadCode RJS 27May98 //				((AirStruc*) *ac)->fly.storesweight -= retval * BOMBWEIGHT;
//DeadCode RJS 27May98 //
//DeadCode RJS 27May98 //				if (((AirStruc*) *ac)->fly.storesweight < 0)
//DeadCode RJS 27May98 //					((AirStruc*) *ac)->fly.storesweight = 0;
//DeadCode RJS 27May98				
//DeadCode RJS 27May98				_Miles.SequenceAudible(FIL_MUSIC_BOMBS_DROPPED);
//DeadCode RJS 27May98			}
//DeadCode RJS 27May98		}
//DeadCode RJS 27May98	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchOneGunBullet
//Author		Paul.
//Date			Fri 26 Apr 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
TransientItem* TransObj::LaunchOneGunBullet(mobileitem* launcher,SLong MuzVel,ShapeNum	weapshape,SLong xpos, SLong ypos, SLong zpos, WorldStuff& worldptr,SWord theangle)
{
	TransientItem* newitem;

	newitem=LaunchUnguidedMissile(launcher,weapshape,LIFETIME_BULLET,MOBILE_BULLET);//PD 26Jun96
	if (newitem)
	{
		SLong	temp;
		SWord	pitchang = newitem->pitch + theangle;			//RJS 26May98

		SWord	sin_ang,cos_ang;

		newitem->World.X = xpos;								//RJS 29Aug96
		newitem->World.Y = ypos;								//RJS 29Aug96
		newitem->World.Z = zpos;								//RJS 29Aug96

		SWord	vx,vy,vz,vhori;

//DeadCode AMM 07Jul99 		if (!_Replay.Playback || (_Replay.Playback && launcher!=Persons2::PlayerSeenAC))//AMM 18Jun99
		if ((!_Replay.Playback || (_Replay.Playback && launcher!=Persons2::PlayerSeenAC))//AMM 07Jul99
			&& !(_DPlay.Implemented && launcher->uniqueID.commsmove && launcher!=Persons2::PlayerSeenAC))//AMM 07Jul99
		{
//DeadCode RJS 21Jun99 			if (_Replay.Playback)					//RJS 18Jun99
//DeadCode RJS 21Jun99 				MuzVel += launcher->vel;	
			((AirStrucPtr)launcher)->fly.pModel->CalcLauncherVel(MuzVel,vx,vy,vz);

			newitem->velx = vx;
			newitem->vely = vy;
			newitem->velz = vz;
			newitem->velhori = Math_Lib.distance3d(vx,vz,0);
			newitem->hdg = Math_Lib.arctan(vx,vz);
		}
		else
		{
			Math_Lib.high_sin_cos((Angles)pitchang,sin_ang,cos_ang);
			temp = (MuzVel * sin_ang)>>ANGLES_SHIFT; newitem->vely += (SWord )temp;		
			temp = (MuzVel * cos_ang)>>ANGLES_SHIFT; newitem->velhori += (SWord )temp;
			Math_Lib.high_sin_cos((ANGLES )newitem->hdg,sin_ang,cos_ang);
			temp = (newitem->velhori * sin_ang)>>ANGLES_SHIFT; newitem->velx = (SWord )temp;
			temp = (newitem->velhori * cos_ang)>>ANGLES_SHIFT; newitem->velz = (SWord )temp;
		}


//Dead		if (launcher == Manual_Pilot.ControlledAC2)				//RJS 19May99
//DeadCode AMM 18Jun99 			newitem->isArmed = 1;								//RJS 19May99

//DeadCode RJS 15Mar99		Math_Lib.high_sin_cos((Angles)pitchang,sin_ang,cos_ang);//RJS 26May98
//DeadCode RJS 15Mar99
//DeadCode RJS 15Mar99		temp = (MuzVel * sin_ang)>>ANGLES_SHIFT; newitem->vely += (SWord )temp;		//RJS 11May98
//DeadCode RJS 15Mar99
//DeadCode RJS 15Mar99		temp = (MuzVel * cos_ang)>>ANGLES_SHIFT; newitem->velhori += (SWord )temp;	//RJS 11May98
//DeadCode RJS 15Mar99
//DeadCode RJS 15Mar99		Math_Lib.high_sin_cos((ANGLES )newitem->hdg,sin_ang,cos_ang);
//DeadCode RJS 15Mar99
//DeadCode RJS 15Mar99		temp = (newitem->velhori * sin_ang)>>ANGLES_SHIFT; newitem->velx = (SWord )temp;
//DeadCode RJS 15Mar99
//DeadCode RJS 15Mar99		temp = (newitem->velhori * cos_ang)>>ANGLES_SHIFT; newitem->velz = (SWord )temp;

		 newitem->isArmed = 1;									//AMM 18Jun99
		AddTransientItemToWorld(newitem,worldptr);
	}
	return newitem;												//ARM 05Sep96
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchManyGunBullets
//Author		R. Hyde
//Date			Tue 16 Jun 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
TransientItem* TransObj::LaunchManyGunBullets(	mobileitem* launcher,
												SLong		MuzVel,
												SWord		nobullets,
												SWord		bdelay,
												SWord		weapindex,
												SWord		weapindex2,
												ShapeNum	weapshape,
												SLong		xpos,
												SLong		ypos,
												SLong		zpos,
												WorldStuff& worldptr,
												SWord		theangle,
												SLong		lnchrtype,
												Bool		isArmed		)
{
	SWord	vel;
	SLong	vely, velx, velz, velhori;	
	SLong	temp;
	SWord	headgang = launcher->hdg;	//CSB 11/06/99	
	SWord	pitchang = launcher->pitch + theangle;			//RJS 26May98

	SWord	sin_ang,cos_ang;
	Coords3D	xyz;
	TransientItem*	newitem = NULL;

//DeadCode CSB 10/03/99		velhori = launcher->velhori;
//DeadCode CSB 10/03/99		vely = launcher->vely;
//DeadCode CSB 10/03/99	
//DeadCode CSB 10/03/99		Math_Lib.high_sin_cos((Angles)pitchang,sin_ang,cos_ang);
//DeadCode CSB 10/03/99	
//DeadCode CSB 10/03/99		temp = (MuzVel * sin_ang)>>ANGLES_SHIFT; vely += temp;
//DeadCode CSB 10/03/99		temp = (MuzVel * cos_ang)>>ANGLES_SHIFT; velhori += temp;
//DeadCode CSB 10/03/99	
//DeadCode CSB 10/03/99		Math_Lib.high_sin_cos((ANGLES )launcher->hdg,sin_ang,cos_ang);
//DeadCode CSB 10/03/99	
//DeadCode CSB 10/03/99		velx = (velhori * sin_ang)>>ANGLES_SHIFT;
//DeadCode CSB 10/03/99		velz = (velhori * cos_ang)>>ANGLES_SHIFT;

	AirStrucPtr AC = (AirStrucPtr)launcher;	//CSB 11/06/99	
	SWord bhdg, bpitch, bvel;						
	AC->CalcBulletVel(MuzVel, headgang, pitchang, vel);
	
	Math_Lib.high_sin_cos((Angles)pitchang, sin_ang, cos_ang);
	vely    = (vel * sin_ang)>>ANGLES_SHIFT;
	velhori = (vel * cos_ang)>>ANGLES_SHIFT;
	
	Math_Lib.high_sin_cos((Angles)headgang, sin_ang, cos_ang);
	velx = (velhori * sin_ang)>>ANGLES_SHIFT;
	velz = (velhori * cos_ang)>>ANGLES_SHIFT;	//CSB 11/06/99	
	
//DeadCode CSB 11/06/99		SLong vel = launcher->vel + MuzVel;
//DeadCode CSB 11/06/99	
//DeadCode CSB 11/06/99		Math_Lib.high_sin_cos((Angles)pitchang,sin_ang,cos_ang);
//DeadCode CSB 11/06/99	
//DeadCode CSB 11/06/99		velhori = vel * cos_ang / 32768;
//DeadCode CSB 11/06/99		vely	= vel * sin_ang / 32768;
//DeadCode CSB 11/06/99	
//DeadCode CSB 11/06/99		Math_Lib.high_sin_cos((ANGLES )launcher->hdg,sin_ang,cos_ang);
//DeadCode CSB 11/06/99		velx = velhori * sin_ang / 32768;
//DeadCode CSB 11/06/99		velz = velhori * cos_ang / 32768;

	xyz.X = xpos;
	xyz.Y = ypos;
	xyz.Z = zpos;

	//Reset previous bullet store...
	if (launcher->Status.size == AIRSTRUCSIZE)			//RJS 29Mar99
		((AirStrucPtr)launcher)->weap.currentbullet = NULL;

	SLong	lifetime;
	AutoMoveCodeTypeSelect	movecode;

	switch (lnchrtype)
	{
	case LT_BULLET:
	{
		if (nobullets > 1)										//RJS 06Jun99
		{
			ShapeDescPtr	sdptr = SHAPESTUFF.GetShapePtr(launcher->shape);
			if (sdptr->AnimDataSize == AIRCRAFTANIM)
			{
				AircraftAnimData*	ladptr= (AircraftAnimData*) launcher->Anim;
				ladptr->shooting = 1;
			}
		}

		lifetime = LIFETIME_BULLET+Math_Lib.rnd(30)|3;
		movecode = MOBILE_BULLET;
		break;
	}
	case LT_ROCKET:
		lifetime = LIFETIME_ROCKET;
		movecode = MOBILE_ROCKET;
		break;
	case LT_NAPALM:
		break;
	case LT_BOMB:
		break;
	}

	newitem = LaunchSuperLauncher(	launcher,
									weapshape,
									LIFETIME_BULLET+Math_Lib.rnd(30)|3,
									MOBILE_BULLET,
									xyz,
									(Angles)headgang,	//launcher->hdg,
									(Angles)pitchang,
									velx,
									vely,
									velz,
									velhori,
									MuzVel,
									launcher->nationality,
									weapindex,
									weapindex2,
									bdelay,
									nobullets,
									lnchrtype,
									worldptr,
									isArmed);					//RJS 27May99

	return(newitem);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchCommsBullet
//Author		Andrew McRae
//Date			Fri 6 Sep 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
//DeadCode AMM 24Jul98 TransientItem* TransObj::LaunchCommsBullet(AirStrucPtr Me, BULPACKET BulPacket)
//DeadCode AMM 24Jul98 {
//DeadCode AMM 24Jul98	mobileitem* launcher = (mobileitem*)Me;
//DeadCode AMM 24Jul98	TransientItem* newitem;
//DeadCode AMM 24Jul98
//DeadCode AMM 24Jul98	newitem=LaunchUnguidedMissile(launcher,GunfireShape,LIFETIME_BULLET,MOBILE_BULLET);
//DeadCode AMM 24Jul98	
//DeadCode AMM 24Jul98	if (newitem)
//DeadCode AMM 24Jul98	{
//DeadCode AMM 24Jul98		SWord	sin_ang,cos_ang;
//DeadCode AMM 24Jul98
//DeadCode AMM 24Jul98		newitem->World.X=BulPacket.PosX;
//DeadCode AMM 24Jul98		newitem->World.Y=BulPacket.PosY;
//DeadCode AMM 24Jul98		newitem->World.Z=BulPacket.PosZ;
//DeadCode AMM 24Jul98
//DeadCode AMM 24Jul98		newitem->velhori = BulPacket.HorzVel;
//DeadCode AMM 24Jul98		newitem->hdg.a = (Angles)BulPacket.Head.a;
//DeadCode AMM 24Jul98		newitem->velx = 0;
//DeadCode AMM 24Jul98		newitem->vely = BulPacket.VertVel;
//DeadCode AMM 24Jul98		newitem->velz = 0;
//DeadCode AMM 24Jul98		newitem->Status.deadtime = 1;						
//DeadCode AMM 24Jul98
//DeadCode AMM 24Jul98		Math_Lib.high_sin_cos((ANGLES )newitem->hdg,sin_ang,cos_ang);
//DeadCode AMM 24Jul98
//DeadCode AMM 24Jul98		newitem->velx = (SWord)((newitem->velhori * sin_ang)/ANGLES_FRACT);
//DeadCode AMM 24Jul98		newitem->velz = (SWord)((newitem->velhori * cos_ang)/ANGLES_FRACT);
//DeadCode AMM 24Jul98
//DeadCode AMM 24Jul98		newitem->LaunchTime = BulPacket.LaunchTime;
//DeadCode AMM 24Jul98
//DeadCode AMM 24Jul98		WorldStuff* thisworld = newitem->GetCurrWorld();
//DeadCode AMM 24Jul98		WorldStuff& worldptr = (WorldStuff&)(*thisworld);
//DeadCode AMM 24Jul98
//DeadCode AMM 24Jul98		AddTransientItemToWorld(newitem,worldptr);
//DeadCode AMM 24Jul98	}
//DeadCode AMM 24Jul98	return newitem;												
//DeadCode AMM 24Jul98 }

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchTrackedBullet
//Author		Robert Slater
//Date			Tue 21 Apr 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
//DeadCode RJS 03Dec98 void	TransObj::LaunchTrackedBullet(mobileitem* launcher,WorldStuff& worldptr)
//DeadCode RJS 03Dec98 {
//DeadCode RDH 29Nov98	if (View_Object->PolyPitEnabled())
//DeadCode RDH 29Nov98	{
//DeadCode RDH 29Nov98		SLong			usexpos, useypos, usezpos;
//DeadCode RDH 29Nov98		SLong			xpos, ypos, zpos;
//DeadCode RDH 29Nov98		SLong			index, wpcnt;
//DeadCode RDH 29Nov98		WeapAnimData*	weapon;
//DeadCode RDH 29Nov98		UWord			mvel,mdelay,mburst;						//RDH 31Jul98
//DeadCode RDH 29Nov98
//DeadCode RDH 29Nov98		usexpos = 0;
//DeadCode RDH 29Nov98		useypos = 0;
//DeadCode RDH 29Nov98		usezpos = 0;
//DeadCode RDH 29Nov98		wpcnt = 0;
//DeadCode RDH 29Nov98
//DeadCode RDH 29Nov98		index = 0;
//DeadCode RDH 29Nov98		while (index < 3)
//DeadCode RDH 29Nov98		{
//DeadCode RDH 29Nov98			weapon = SHAPE.GetWeaponLauncher(launcher,index,xpos,ypos,zpos,mvel,mdelay,mburst,LT_BULLET);//RDH 31Jul98
//DeadCode RDH 29Nov98			if (weapon)
//DeadCode RDH 29Nov98			{
//DeadCode RDH 29Nov98				usexpos += xpos;
//DeadCode RDH 29Nov98				useypos += ypos;
//DeadCode RDH 29Nov98				usezpos += zpos;
//DeadCode RDH 29Nov98
//DeadCode RDH 29Nov98				wpcnt++;
//DeadCode RDH 29Nov98			}
//DeadCode RDH 29Nov98			index++;
//DeadCode RDH 29Nov98		}
//DeadCode RDH 29Nov98
//DeadCode RDH 29Nov98		if (wpcnt)
//DeadCode RDH 29Nov98		{
//DeadCode RDH 29Nov98			TransientItem* newitem;
//DeadCode RDH 29Nov98
//DeadCode RDH 29Nov98			newitem=LaunchUnguidedMissile(launcher,EMPTY,LIFETIME_BULLET,MOBILE_TRACKBULLET);
//DeadCode RDH 29Nov98			if (newitem)
//DeadCode RDH 29Nov98			{
//DeadCode RDH 29Nov98				SLong			temp;
//DeadCode RDH 29Nov98				SWord			sin_ang,cos_ang;
//DeadCode RDH 29Nov98
//DeadCode RDH 29Nov98				newitem->World.X = usexpos/wpcnt;					
//DeadCode RDH 29Nov98				newitem->World.Y = useypos/wpcnt;					
//DeadCode RDH 29Nov98				newitem->World.Z = usezpos/wpcnt;	
//DeadCode RDH 29Nov98
//DeadCode RDH 29Nov98				Math_Lib.high_sin_cos((ANGLES )newitem->pitch,sin_ang,cos_ang);
//DeadCode RDH 29Nov98
//DeadCode RDH 29Nov98				temp = (mvel * sin_ang)>>ANGLES_SHIFT; newitem->vely += (SWord )temp;
//DeadCode RDH 29Nov98				temp = (mvel * cos_ang)>>ANGLES_SHIFT; newitem->velhori += (SWord )temp;
//DeadCode RDH 29Nov98
//DeadCode RDH 29Nov98				AddTransientItemToWorld(newitem,worldptr);
//DeadCode RDH 29Nov98			}
//DeadCode RDH 29Nov98		}
//DeadCode RDH 29Nov98	}
//}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchMiniExplosion
//Author		Martin Alderton
//Date			Thu 29 Feb 1996
//
//Description	sets up a transientitem
//
//Inputs		a rotitem giving initial position		
//
//Returns	
//
//------------------------------------------------------------------------------
void TransObj::LaunchMiniExplosion(mobileitem* launcher,WorldStuff& worldptr)
{
	TransientItem*	newitem;

	newitem = SimplifiedSpriteLaunch(launcher,MiniExplosionShape,100,MOBILE_STATIONARY);//RJS 10Dec98
	if (newitem)
	{
		newitem->World.Y += 400;
		if ((launcher->Status.size >= MovingSize) && (launcher->Status.size != TransientSize))//RJS 16Nov98
			newitem->Target = launcher;							//RJS 16Nov98

		_Miles.PlaySample((FileNum) (FIL_SFX_EXPLOSION_OILDRUM1+Math_Lib.rnd(5)), newitem);
		AddTransientItemToWorld(newitem,worldptr);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchDebris
//Author		Robert Slater
//Date			Fri 21 Jun 1996
//
//Description	catapults debris of any shape into the air....
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::LaunchDebris(mobileitem* launcher,ShapeNum shapeBase,SLong	randcnt, SLong maxbits, WorldStuff& worldptr, Bool nospin)
{
	if (Save_Data.desiredfps <= realFrameTime)					//RJS 11Jun99
	{
		TransientItem*	newitem;
		UWord	newhdg;
		SLong	vel;
		SLong	vely;
		SLong	count;
		SLong	cntrand = maxbits / 2;
		UWord	pitchover,rollover;

		cntrand += Math_Lib.rnd(cntrand);

		if (launcher->Status.size == AirStrucSize)
			vely = 150;
		else
			vely = 0;

		UWord	shprand;

		for (count = 0; count < cntrand; count++)
		{
			shprand = Math_Lib.rnd(randcnt);								//RJS 1/20/99
			newitem = SimplifiedSpriteLaunch(launcher,			
											(ShapeNum) (shapeBase + shprand), //RJS 1/20/99
											250,MOBILE_DEBRIS);
			if (newitem)
			{
				if ((newitem->shape >= DebrisStartShape) && (newitem->shape <= DebrisEndShape))
				{
					DebrisAnimData*	adptr = (DebrisAnimData*) newitem->Anim;
					adptr->frameno = Math_Lib.rnd(4);
				}

				newhdg = Math_Lib.rnd();

				vel = Math_Lib.rnd(300);

				newitem->hdg = (Angles) newhdg;			
				newitem->vely = ((300 * (300-vel))/300)-vely;		
				newitem->velhori = vel;	
			
				if (!nospin)
				{
					pitchover = (vel << 8)/300;	//greater the vel, the more it spins
					rollover = newhdg>>8;

					newitem->TransRandom = (rollover<<8) + pitchover;		
				}

				AddTransientItemToWorld(newitem,worldptr);
			}
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchFire
//Author		Robert Slater
//Date			Mon 1 Jul 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::LaunchFire(mobileitem* launcher,WorldStuff& worldptr)
{
	TransientItem*	newitem;
	newitem = SimplifiedSpriteLaunch(	launcher,
										LargeFireShape,
										LIFETIME_GROUNDEXP,MOBILE_GROUNDEXP);//RJS 09Oct96*/
	if (newitem)
	{
		MoveGunAnimData*	adptr = (MoveGunAnimData*)newitem->Anim;
		WeapAnimData*		weapon = (WeapAnimData*) &adptr->weaponlaunchers[0];

		SHAPE.InitTrailFields((UByteP)weapon,0,32000,LT_FUEL);	//RJS 12Jan98

		LaunchVapourStream((UByteP)weapon,LargeFireShape,0,1000,64);

		newitem->TransRandom = SmokeLaunchDelay;

		AddTransientItemToWorld(newitem, worldptr);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchTroop
//Author		Robert Slater
//Date			Mon 1 Jul 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::LaunchTroops(	item*		launcher,
								ShapeNum	troopshape,
								Coords3D	realpos,
								WorldStuff& worldptr,
								SByte		maxtroops	)
{
//DeadCode RJS 11Jun99 	if (Save_Data.desiredfps <= realFrameTime)					//RJS 11Jun99
	{
		if (maxtroops)
		{
			SLong	realmaxtroops = maxtroops;
			if (realmaxtroops > 16)	realmaxtroops = 16;

			if (Save_Data.desiredfps > realFrameTime)
				realmaxtroops >>= 1;

			maxtroops = realmaxtroops/2;
			maxtroops += Math_Lib.rnd(maxtroops);
			if (maxtroops)
			{
				TransientItem*	newitem;
				SWord			count;
				SLong			xpos, ypos, zpos,dist;
				SWord			thehdg;
				Bool			homingtroops = FALSE;
				ShapeDescPtr	sdptr;
				ShapeNum		newshp;
				animptr			adptrtmp;
	//DeadCode RJS 21Apr99			FireAnimData*	adptr2;										
				Bool			isours = FALSE;
				TroopAnimData*	adptr;
				MinAnimData*	mad;
				SLong			dx,dy,dz;
				SLong			mindist = 10000000;
				Coords3D		placelist[64];
				SLong			placecnt = 0;
				Bool			dim = TRUE;
				SWord			randindex;
//Dead				SLong			groundheight = Land_Scape.GetGroundLevel(realpos);

				sdptr = SHAPESTUFF.GetShapePtr(launcher->shape);
				adptrtmp = launcher->Anim;

				if (SHAPESTUFF.GetShapeScale(sdptr) == SHP_GRP)
				{
					UByteP		instr_ptr;
					instr_ptr = (UByteP )sdptr + sdptr->liveshpref;

					// Search for nearest strongest....

					while (SHAPE.GetGroupElement(instr_ptr,newshp,xpos,ypos,zpos))
					{
						mad = (MinAnimData*) adptrtmp;
						if (mad->itemstate == ALIVE)
						{
							dx = xpos + launcher->World.X;
							dy = ypos + launcher->World.Y;
							dz = zpos + launcher->World.Z;
							if ((realpos.X != dx) && (realpos.Z != dz))
							{
								dx -= realpos.X;
								dy -= realpos.Y;
								dz -= realpos.Z;

								dist = Math_Lib.distance3d(dx,dy,dz);
								if (dist < mindist)
								{
									mindist = dist;
									placelist[placecnt].X = xpos + launcher->World.X;
									placelist[placecnt].Y = ypos + launcher->World.Y;
									placelist[placecnt++].Z = zpos + launcher->World.Z;
								}
							}
						}

						adptrtmp += SHAPE.GetElementAnimOffset(newshp);//RJS 21Apr99
					}
				}
				else
				{
					// Find nearest alive thing in this sector....
					Coords3D	oldpos = launcher->World;
					ItemPtr		nearestItm;

					launcher->World = realpos;
					nearestItm = Three_Dee.NearestAliveThing(launcher);
					launcher->World = oldpos;

					if (nearestItm)
					{
						placelist[placecnt].X = nearestItm->World.X;
						placelist[placecnt].Y = nearestItm->World.Y;
						placelist[placecnt++].Z = nearestItm->World.Z;
					}
				}

				if (placecnt)
				{
					// Set homing devices....
					SWord	randindex;

					placecnt--;
					dim = FALSE;
				}

				PointBlokes(launcher,troopshape,realpos,maxtroops,placelist,placecnt);
//DeadCode RJS 01Jun99 				for (count = 0; count < maxtroops; count++)
//DeadCode RJS 01Jun99 				{
//DeadCode RJS 01Jun99 					newitem = SimplifiedSpriteLaunch(launcher,troopshape,LIFETIME_TROOP,MOBILE_TROOP);
//DeadCode RJS 01Jun99 					if (newitem)
//DeadCode RJS 01Jun99 					{
//DeadCode RJS 01Jun99 						adptr = (TroopAnimData*) newitem->Anim;
//DeadCode RJS 01Jun99 						if (!dim)
//DeadCode RJS 01Jun99 						{
//DeadCode RJS 01Jun99 							randindex = placecnt-Math_Lib.rnd(maxtroops);
//DeadCode RJS 01Jun99 							if (randindex < 0)
//DeadCode RJS 01Jun99 								randindex = placecnt;
//DeadCode RJS 01Jun99 
//DeadCode RJS 01Jun99 							adptr->xpos = placelist[randindex].X;								
//DeadCode RJS 01Jun99 							adptr->ypos = placelist[randindex].Y;
//DeadCode RJS 01Jun99 							adptr->zpos = placelist[randindex].Z;
//DeadCode RJS 01Jun99 							adptr->oncourse = FALSE;
//DeadCode RJS 01Jun99 
//DeadCode RJS 01Jun99 							// Someone might panic!!!!!... headless chicken code
//DeadCode RJS 01Jun99 							if (Math_Lib.rnd()>50000)
//DeadCode RJS 01Jun99 								adptr->homing = FALSE;
//DeadCode RJS 01Jun99 							else
//DeadCode RJS 01Jun99 								adptr->homing = TRUE;
//DeadCode RJS 01Jun99 						}
//DeadCode RJS 01Jun99 						else
//DeadCode RJS 01Jun99 						{
//DeadCode RJS 01Jun99 							adptr->oncourse = FALSE;
//DeadCode RJS 01Jun99 							adptr->homing = FALSE;
//DeadCode RJS 01Jun99 						}
//DeadCode RJS 01Jun99 	
//DeadCode RJS 01Jun99 						// 5 metre spread around...
//DeadCode RJS 01Jun99 						newitem->World.X = realpos.X + Math_Lib.rnd(1000) - 500;
//DeadCode RJS 01Jun99 						newitem->World.Y = groundheight;								
//DeadCode RJS 01Jun99 						newitem->World.Z = realpos.Z + Math_Lib.rnd(1000) - 500;
//DeadCode RJS 01Jun99 
//DeadCode RJS 01Jun99 						newitem->hdg = (Angles) Math_Lib.rnd();
//DeadCode RJS 01Jun99 						newitem->vely = 0;
//DeadCode RJS 01Jun99 						newitem->velhori = 100 + Math_Lib.rnd(20);
//DeadCode RJS 01Jun99 						newitem->TransRandom = 50;
//DeadCode RJS 01Jun99 
//DeadCode RJS 01Jun99 						AddTransientItemToWorld(newitem, worldptr);
//DeadCode RJS 01Jun99 					}
//DeadCode RJS 01Jun99 				}
			}
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchParachute
//Author		Robert Slater
//Date			Tue 2 Jul 1996
//
//Description	Jump from side of the plane/balloon at any angle from 0-180 degrees
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::LaunchParachute(mobileitem* launcher,WorldStuff& worldptr)
{
	AircraftAnimData	*adptr = (AircraftAnimData *) launcher->Anim;	//RJS 18Feb98
																		//RJS 18Feb98
	// Canopy must have been blown.....									//RJS 18Feb98
	if (	(adptr->CANOPY1 == BS_DEAD)									//RJS 18Feb98
		&&	(adptr->PILOTLEFT != BS_DEAD)	)							//RJS 18Feb98
	{																	//RJS 18Feb98
		if (launcher->Status.size == AIRSTRUCSIZE)				//RJS 31May99
		{														//RJS 31May99
			AirStrucPtr	ac = (AirStrucPtr)*launcher;			//RJS 31May99
																//RJS 31May99
			if (ac->ai.pilotnum < ai_info::PROPER_PILOT_MAX)	//RJS 31May99
				MMC.Active_Pilots[ac->ai.pilotnum].status=MIA;	//RJS 31May99

			if (!ac->uniqueID.commsmove)								  //AMM 07/07/99
				ac->ai.radiosilent = TRUE;							//RJS 11Jun99
		}														//RJS 31May99

		TransientItem*	newitem;										//RJS 18Feb98

		// Turn him off...... give him 2 mins...
		adptr->PILOTLEFT = BS_DEAD;										//RJS 18Feb98
		newitem = SimplifiedSpriteLaunch(launcher,DUMY19,12000,MOBILE_PARACHUTE);//RJS 22Apr99
		if (newitem)													//RJS 18Feb98
		{																//RJS 18Feb98
			_Miles.PlayOnce(FIL_SFX_EJECT_SEAT,launcher);				//RJS 18Feb98
			if (launcher == Manual_Pilot.ControlledAC2)						//RJS 21May98
			{																//RJS 21May98
				Persons2::UpdatePlayerLog	(Manual_Pilot.ControlledAC2,EventLog::PARACHUTED); //RDH 19/06/99

				if (View_Object)											//RJS 21May98
					View_Object->SetToParachuteView((mobileitem*)newitem);	//RJS 22Apr99
																			//RJS 21May98
				Manual_Pilot.controlmode=ManualPilot::PILOTDEAD;			//RJS 21May98
				Manual_Pilot.DeathSequenceOverride((AirStrucPtr)launcher,AUTO_DEATHSEQUENCE);

				_Miles.PlayFlyAway(launcher);								//RJS 21May98

				_Miles.SequenceAudible(FIL_MUSIC_PARACHUTE);	//RJS 17Mar99
			}																//RJS 21May98
			else
			{
				Manual_Pilot.DeathSequenceOverride((AirStrucPtr)launcher,AUTO_DEATHSEQUENCE);
				if (launcher->nationality != Manual_Pilot.ControlledAC2->nationality)
					_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_ENEMYEJECT, MSG_EJECTREPLY, launcher , launcher, Manual_Pilot.ControlledAC2));//RDH 18May99
				else
				{
					AirStrucPtr	buddy;
					if (((AirStrucPtr)launcher)->PlayerInGroup())
					{
						buddy = Manual_Pilot.ControlledAC2->FindBuddy();
						if (buddy)
							_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_EJECTREPLY, MSG_EJECTREPLY, buddy , launcher, Manual_Pilot.ControlledAC2));
					}
				}
			}

			newitem->isOwned = 1;			//cannot remove...					//RJS 22Apr99

			ClassPtr	clstyp = ((AirStrucPtr)launcher)->classtype;
			if (clstyp->phrasename != PHRASE_F51S)
			{
				SWord	vx,vy,vz;

				((AirStrucPtr)launcher)->fly.pModel->CalcParachuteVel(vx,vy,vz,launcher->hdg,launcher->pitch,launcher->roll,launcher->vel/10,40, launcher->World.Y);	//RJS 10May99	//CSB 13/06/99	

				newitem->velx = vx;
				newitem->vely = vy;
				newitem->velz = vz;
				newitem->velhori = Math_Lib.distance3d(vx,vz,0);
				newitem->pitch = launcher->pitch;
				newitem->roll = launcher->roll;

//DeadCode CSB 13/06/99					if (((AirStrucPtr)launcher)->AcIsPlayer())		//RJS 13May99
					newitem->hdg = Math_Lib.arctan(vx,vz);		//RJS 13May99
//DeadCode CSB 13/06/99					else											//RJS 13May99
//DeadCode CSB 13/06/99						newitem->hdg = launcher->hdg;				//RJS 13May99
			}
			else
			{
				ParachuteAnimData* adptr = (ParachuteAnimData*) newitem->Anim;
				adptr->OTHER = 255;		//dead the rest...

				newitem->velx = launcher->velx;
				newitem->vely = launcher->vely;
				newitem->velz = launcher->velz;
				newitem->velhori = 100;

				newitem->vely += 100;
				newitem->hdg = launcher->hdg + ANGLES_90Deg;
				newitem->pitch = launcher->pitch;
				newitem->roll = launcher->roll;
			}

			// Inherit launcher ori & speed.
			// Give vel = 20ms (200)
			// Give drag.
			// Launch propellent smoke when eject.
			// Rotate guy in seat to upright position.. eject at -20 ms
			// splat guy on ground
			//... calc drag with air density
			//	(20 - kmheight)/(20 + kmheight)

			newitem->TransRandom = 300;									//RJS 18Feb98
																		//RJS 18Feb98
			AddTransientItemToWorld(newitem, worldptr);					//RJS 18Feb98
		}																//RJS 18Feb98
	}																	//RJS 18Feb98
	else																//RJS 18Feb98
	{																	//RJS 18Feb98
		_Miles.PlayOnce(FIL_SFX_YELP1, launcher);						//RJS 18Feb98
																		//RJS 18Feb98
		adptr->PILOTLEFT = BS_DEAD;										//RJS 18Feb98
		if (adptr->CANOPY1 < BS_DEAD)									//RJS 18Feb98
			adptr->CANOPY1 = BS_DAMLV2;									//RJS 18Feb98
	}																	//RJS 18Feb98
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchBarage
//Author		Robert Slater
//Date			Fri 5 Jul 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::LaunchBarage(	mobileitem* launcher,
								SLong		launchtime )
{
	SLong			mintime = launchtime / 2;
	SWord			howlong = 0;
	SWord			thistimer;
	SWord			count;
	SLong			groundheight;
	TransientItem*	newitem;
	UWord			totaltime = mintime + Math_Lib.rnd(mintime);//Max of 'launchtime' secs, min of .5 launchtime
	UWord			maxhowmany;
	UWord			howmany;
	SWord			ttime;

	//3 bangs per 1.5 sec max...

	if (Three_Dee.IsItVisible(launcher->World)==true)					//RJS 09Dec98
	{
		maxhowmany = (3 * totaltime)/150;
		howmany = maxhowmany / 2;
		howmany += Math_Lib.rnd(howmany);

		ttime = ((totaltime / howmany)*10) - 167;

		groundheight = GetGroundLevel(launcher);				//RJS 14Apr99

		for (count = 0; count < howmany; count++)
		{
			thistimer = 167 + Math_Lib.rnd(ttime);				//RJS 01Oct98
			howlong += thistimer;								//RJS 25Oct96

			newitem = SimplifiedSpriteLaunch(launcher,ShockwaveShape,howlong/10,MOBILE_BARAGE);
			if (newitem)
			{
				// With a max radius of about 200 metres

				newitem->World.X = launcher->World.X + Math_Lib.rnd(40000) - 20000;//RJS 25Oct96
				newitem->World.Z = launcher->World.Z + Math_Lib.rnd(40000) - 20000;//RJS 25Oct96
				newitem->World.Y = groundheight;						//RJS 23Jul96

				AddTransientItemToWorld(newitem, *newitem->currworld);
			}
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchDelayedExplosion
//Author		Robert Slater
//Date			Fri 5 Jul 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::LaunchDelayedExplosion(mobileitem* launcher,WorldStuff& worldptr)
{
	SLong			delay;
	TransientItem*	newitem;

	delay = 150 + Math_Lib.rnd(150);

	newitem = LaunchGuidedMissile(launcher,(itemptr) launcher,
									InvisibleLauncher,delay,MOBILE_DELEXP);//RJS 06Dec98

	if (newitem)
	{
		// this means it really will explode...
		newitem->TransRandom = 2;								//RJS 06Dec98

		AddTransientItemToWorld(newitem, worldptr);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchFlak
//Author		Robert Slater
//Date			Fri 5 Jul 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::LaunchFlak(mobileitem* launcher,WorldStuff& worldptr)
{
	LaunchRealShockwave(launcher,4,worldptr);					//RJS 29Jun99

	if (WithinVisibleRange(launcher->World,300000))				//RJS 30Apr99
	{
		SLong	count,howlong,newx,newy,newz;
		howlong = 0;
		for (count = 0; count < 4; count++)
		{
			howlong += Math_Lib.rnd(80);

			TransientItem*	newitem = SimplifiedSpriteLaunch(launcher,launcher->shape,howlong,MOBILE_FLAK);
			if (newitem)
			{
				MinAnimData*	mad = (MinAnimData*)newitem->Anim;			//RJS 06May99
				mad->IsInvisible = 1;
				// Place randomly about that point....

				newx = Math_Lib.rnd(8000) - 4000;
				newy = Math_Lib.rnd(8000) - 4000;
				newz = Math_Lib.rnd(8000) - 4000;

				newitem->World.X += newx;				
				newitem->World.Z += newy;				
				newitem->World.Y += newz;				

				AddTransientItemToWorld(newitem, worldptr);
			}
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchRicochet
//Author		Robert Slater
//Date			Fri 5 Jul 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::LaunchRicochet(mobileitem* launcher,WorldStuff& worldptr)
{
	TransientItem*	newitem;
	UWord			MaxVel = 300;
	UWord			count;
//DeadCode RJS 19Feb98	ExplodeAnimData* adptr;									//PD 10May96

//DeadCode RJS 10Jul96	newitem = SimplifiedSpriteLaunch(launcher,SPURT1,10,MOBILE_RICOCHET);
//DeadCode RJS 10Jul96	if (newitem)
//DeadCode RJS 10Jul96	{
//DeadCode RJS 10Jul96		newitem->hdg = ANGLES_0Deg - View_Point.hdg;
//DeadCode RJS 10Jul96		adptr = (ExplodeAnimData* )newitem->Anim;
//DeadCode RJS 10Jul96		adptr->frameno = Math_Lib.rnd(3);
//DeadCode RJS 10Jul96
//DeadCode RJS 10Jul96		AddTransientItemToWorld(newitem,worldptr);
//DeadCode RJS 10Jul96	}

	newitem = SimplifiedSpriteLaunch(launcher,DustShape,LIFETIME_MINIEX / 6,MOBILE_STATIONARY);//RJS 20Apr98
	if (newitem)
	{
		AddTransientItemToWorld(newitem,worldptr);
		_Miles.PlaySample((FileNum) (FIL_SFX_RICOCHET_SOFT_SURFACE1+Math_Lib.rnd(5)), (ItemBasePtr) newitem);//RJS 22Nov96
	}

	if (Save_Data.desiredfps <= realFrameTime)					//RJS 11Jun99
	{
		for (count = 0; count < 3; count++)
		{
			newitem = SimplifiedSpriteLaunch(launcher,SparkShape,//RJS 28May99
											10,MOBILE_RICOCHET);
			if (newitem)
			{
				newitem->hdg = (Angles) Math_Lib.rnd();				//RJS 24Jul96
				newitem->pitch = (Angles) Math_Lib.rnd(16000);		//RJS 24Jul96
				newitem->vely =	100 + Math_Lib.rnd(100);			//RJS 24Jul96
				newitem->velhori = 100 + Math_Lib.rnd(100);			//RJS 24Jul96

				AddTransientItemToWorld(newitem,worldptr);
			}
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchSpark
//Author		Robert Slater
//Date			Wed 24 Jul 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::LaunchSpark(mobileitem* launcher,WorldStuff& worldptr)
{
	if (	WithinVisibleRange(launcher->World,100000)
		&&	(Save_Data.desiredfps <= realFrameTime)		)		//RJS 11Jun99
	{
		TransientItem*	newitem;
		UWord			count;

		for (count = 0; count < 2; count++)
		{
			newitem = SimplifiedSpriteLaunch(launcher,SparkShape,		//RDH 20Dec96
											40,MOBILE_GANDF);	//RJS 28May99
			if (newitem)
			{
				newitem->hdg = (Angles) (launcher->hdg + ANGLES_180Deg - Math_Lib.rnd(ANGLES_120Deg) + ANGLES_60Deg);				
				newitem->vely = Math_Lib.rnd(100);					//RJS 17Nov98
				newitem->velhori = 100 - newitem->vely;				//RJS 17Nov98
				AddTransientItemToWorld(newitem,worldptr);
			}
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchExplosion
//Author		Martin Alderton
//Date			Thu 29 Feb 1996
//
//Description	Launches a big explosion animation,
//				and a fan of debris	
//
//Inputs		a rotitem giving initial position
//
//Returns	
//
//------------------------------------------------------------------------------
void TransObj::LaunchExplosion(mobileitem* launcher,WorldStuff& worldptr,int	strength)
{
	TransientItem*	newitem;
	SLong			dx, dy, dz, dh;
	SLong			distance;
	SWord			thehdg, thehdg1;
	SWord			pitch;
	SLong			radius;
	SWord			sin_ang,cos_ang;
	ShapeDescPtr	sshp;										//RJS 08Nov96

	newitem	= RelativeSpriteLaunch(launcher,launcher->shape,HugeExplosionShape,100,MOBILE_BIGEXP);
	if (newitem)
	{
//DeadCode RJS 26Nov98		sshp = SHAPESTUFF.GetShapePtr(launcher->shape);
//DeadCode RJS 26Nov98		radius = (sshp->Size << 4) + 4;
//DeadCode RJS 26Nov98
//DeadCode RJS 26Nov98		dx = launcher->World.X - View_Point->World.X;
//DeadCode RJS 26Nov98		dy = launcher->World.Y - View_Point->World.Y;
//DeadCode RJS 26Nov98		dz = launcher->World.Z - View_Point->World.Z;
//DeadCode RJS 26Nov98
//DeadCode RJS 26Nov98		Math_Lib.Intercept(dx,dy,dz,distance,thehdg,pitch);
//DeadCode RJS 26Nov98		Math_Lib.high_sin_cos((Angles)pitch,sin_ang,cos_ang);
//DeadCode RJS 26Nov98
//DeadCode RJS 26Nov98		dy = (sin_ang * radius) / ANGLES_FRACT;
//DeadCode RJS 26Nov98		dh = (cos_ang * radius) / ANGLES_FRACT;
//DeadCode RJS 26Nov98
//DeadCode RJS 26Nov98		Math_Lib.high_sin_cos((Angles)thehdg,sin_ang,cos_ang);
//DeadCode RJS 26Nov98
//DeadCode RJS 26Nov98		dx = (sin_ang * dh) / ANGLES_FRACT;
//DeadCode RJS 26Nov98		dz = (cos_ang * dh) / ANGLES_FRACT;
//DeadCode RJS 26Nov98
//DeadCode RJS 26Nov98		newitem->pitch = (Angles) 1;
//DeadCode RJS 26Nov98		newitem->roll = (Angles) 1;
//DeadCode RJS 26Nov98		newitem->hdg = (Angles) 1;
//DeadCode RJS 26Nov98
//DeadCode RJS 26Nov98		newitem->World.Z -= 1;
//DeadCode RJS 26Nov98		newitem->World.X -= 1;
//DeadCode RJS 26Nov98		newitem->World.Y -= 1;
//DeadCode RJS 26Nov98		newitem->TransRandom = 10;
//DeadCode RJS 26Nov98

		AddTransientItemToWorld(newitem, worldptr);
	}

	LaunchSkinDebris(launcher,worldptr);
	LaunchSparkDebris(launcher,worldptr);			
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchSparkDebris
//Author		Robert Slater
//Date			Tue 13 Aug 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void TransObj::LaunchSparkDebris(mobileitem* launcher, WorldStuff& worldptr)
{
	if (Save_Data.desiredfps <= realFrameTime)					//RJS 11Jun99
	{
		int				count;
		TransientItem*	newitem;

		for (count = 0; count < 8; count++)							//DAW 01Sep98
		{
	//DeadCode RJS 23Nov98		newitem = SimplifiedSpriteLaunch(launcher,SPARK,LIFETIME_DEBRISLNCHR,MOBILE_DEBRIS);//RDH 20Dec96
			newitem = LaunchUnguidedMissile(launcher,SparkShape,200,MOBILE_GANDF);//RJS 28May99
			if (newitem)
			{
				SLong	vely = Math_Lib.rnd(400) - 200;

				newitem->hdg = (Angles) Math_Lib.rnd();			//RJS 06Aug96
				newitem->vely += vely;							//RJS 26Nov98
				newitem->velhori += 300 - vely;					//RJS 26Nov98

				AddTransientItemToWorld(newitem,worldptr);
			}
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchSkinDebris
//Author		Robert Slater
//Date			Wed 14 Aug 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void TransObj::LaunchSkinDebris(mobileitem* launcher, WorldStuff& worldptr)
{
	if (Save_Data.desiredfps <= realFrameTime)					//RJS 11Jun99
	{
		int				count;
		TransientItem*	newitem;
		SLong			tot = 2 + Math_Lib.rnd(4);

		for (count = 0; count < tot; count++)
		{
			newitem = LaunchUnguidedMissile(	launcher,		
												DebrisMechShape,
												300,MOBILE_DEBRIS);//RJS 28May99
			if (newitem)
			{
				SLong	vely = Math_Lib.rnd(400) - 200;

				newitem->hdg = (Angles) Math_Lib.rnd();			
				newitem->pitch = (Angles) Math_Lib.rnd(16000);	
				newitem->roll = (Angles) Math_Lib.rnd();	
				newitem->vely += vely;		
				newitem->velhori += 300 - vely;			
				newitem->TransRandom = 0;							//RJS 16Aug96

				if ((newitem->shape >= DebrisStartShape) && (newitem->shape <= DebrisEndShape))
				{
					DebrisAnimData*	adptr = (DebrisAnimData*) newitem->Anim;//RJS 20Jan99
					adptr->frameno = Math_Lib.rnd(4);
				}

				AddTransientItemToWorld(newitem,worldptr);
			}
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchDeadACPart
//Author		Martin Alderton
//Date			Fri 29 Mar 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void TransObj::LaunchDeadACPart(AirStruc* launcher,BitFlags bitflag, WorldStuff &worldptr, Bool	blowup)
{
	TransientItem*	newitem;
	AircraftAnimData*	adptr2 = (AircraftAnimData* )launcher->Anim;

	newitem = LaunchUnguidedMissile((mobileitem* )launcher,
									launcher->shape,
									LIFETIME_ACPART,MOBILE_DEADACPART);
	if (newitem)
	{
		//Set 3D to only draw the dead part

		AircraftAnimData*	adptr = (AircraftAnimData* )newitem->Anim;

//DeadCode RJS 09Jun97		adptr->imagemaptail = adptr2->imagemaptail;
//DeadCode RJS 09Jun97		adptr->imagemapbtmwing = adptr2->imagemapbtmwing;
//DeadCode RJS 09Jun97		adptr->imagemapfuselage = adptr2->imagemapfuselage;
//DeadCode RJS 09Jun97		adptr->imagemapother = adptr2->imagemapother;
//DeadCode RJS 09Jun97		adptr->imagemaptopwing = adptr2->imagemaptopwing;
		adptr->imagemapemblem = adptr2->imagemapemblem;
//DeadCode RJS 27May97		adptr->vapourtrail = 0;

		if (blowup)
		{
			newitem->hdg = (Angles) Math_Lib.rnd();			//RJS 06Aug96
			newitem->vely = Math_Lib.rnd(400) - 200;		//RJS 06Aug96
			newitem->velhori = 300 - newitem->vely;			//RJS 06Aug96
		}
		else
			newitem->hdg += ANGLES_180Deg;						//RJS 07Nov96

		UWord	localdamflag;									//RJS 31Oct96

		localdamflag = 0x0FFFF;		//All dead					//RJS 31Oct96
		localdamflag &= ~(BS_DEAD<<bitflag);					//RJS 31Oct96

//DeadCode RJS 09Jun97		adptr->dammageflags = localdamflag;	//(BS_DEAD<<bitflag) + (BS_DEAD<<BF_TheRest);//RJS 31Oct96

		newitem->TransRandom = Math_Lib.rnd();

		AddTransientItemToWorld(newitem, worldptr);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchBitsOffPart
//Author		Robert Slater
//Date			Thu 20 Feb 1997
//
//Description	Eject a 'detachable' part from a shape
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void TransObj::LaunchBitsOffPart(	ItemPtr	launcher,
									UByteP	damageptr,
									WorldStuff &worldptr,
									UByte	lastdamage,
									UByteP	lastdamptr,
									UWord	blowup,
									Bool	noFlash)
{
	TransientItem*	newitem;
	UByteP			flagptr;
	int				flagend;
	ShapeDescPtr	sdptr;
	int				index;
	int				damageoffset;								//RJS 07Jul99
	animptr			adptrold;									//RJS 21Apr99
	animptr			adptr;										//RJS 21Apr99

//DeadCode RJS 05May99	if (noFlash == FALSE)
//DeadCode RJS 05May99	{
//DeadCode RJS 05May99		// A flash......colpos_impact should have been set up at this point...
//DeadCode RJS 05May99		newitem = SimplifiedSpriteLaunch((mobileitem*)launcher,EXPLO,10,MOBILE_BIGEXP);//RJS 20Apr98
//DeadCode RJS 05May99		if (newitem)
//DeadCode RJS 05May99		{
//DeadCode RJS 05May99			newitem->World = BoxCol::colpos_impact;
//DeadCode RJS 05May99			if ((launcher->Status.size >= MovingSize) && (launcher->Status.size != TransientSize))//RJS 16Nov98
//DeadCode RJS 05May99				newitem->Target = launcher;						//RJS 16Nov98
//DeadCode RJS 05May99
//DeadCode RJS 05May99			_Miles.PlaySample((FileNum) (FIL_SFX_EXPLOSION_OILDRUM1+Math_Lib.rnd(5)), newitem,32);
//DeadCode RJS 05May99			AddTransientItemToWorld(newitem,worldptr);
//DeadCode RJS 05May99		}
//DeadCode RJS 05May99	}

	sdptr = SHAPESTUFF.GetShapePtr(launcher->shape);
	newitem = LaunchUnguidedMissile((mobileitem* )launcher,
									launcher->shape,
									LIFETIME_ACPART,MOBILE_DEADACPART,TRUE);//RJS 13Jul98
	if (newitem)
	{
		adptrold = launcher->Anim;								//RJS 21Apr99
		adptr = newitem->Anim;									//RJS 21Apr99

//DeadCode RJS 13Jul98		if (launcher->Status.size == AirStrucSize)		// Inherit imagemaps
//DeadCode RJS 13Jul98		{
//DeadCode RJS 13Jul98			adptrold2 = (AircraftAnimData* )adptrold;
//DeadCode RJS 13Jul98			adptr2 = (AircraftAnimData* )adptr;
//DeadCode RJS 13Jul98		}



		//Set 3D to only draw the dead part

//DeadCode RJS 21Apr99		flagptr = (UByteP) newitem->Anim;
		flagend = SHAPE.GetAnimDataSize(launcher->shape);
		index = sdptr->DamageOffset;							//RJS 28Apr99

		while (index < flagend)
			adptr[index++] = BS_DEAD;							//RJS 21Apr99

		damageoffset = adptrold.Offset(damageptr);				//RJS 21Apr99
		if (damageptr == lastdamptr)
			adptr[damageoffset] = lastdamage;
		else
			adptr[damageoffset] = BS_DAMLV2;

		MinAnimData*	mad = (MinAnimData*) adptr;				//RJS 15Jul98
		mad->itemstate = DEAD;								//RJS 15Jul98

		if (blowup)
		{
//DeadCode DAW 03Sep98			SLong	vely = (((400 * Math_Lib.rnd())>>16) - 200);
//DeadCode DAW 03Sep98			SLong	velhori = 300 - newitem->vely;
//DeadCode DAW 03Sep98
//DeadCode DAW 03Sep98			blowup += 16;
//DeadCode DAW 03Sep98			vely = (vely * blowup)>>6;
//DeadCode DAW 03Sep98			velhori = (velhori * blowup)>>6;
//DeadCode DAW 03Sep98
//DeadCode DAW 03Sep98			newitem->hdg = (Angles) Math_Lib.rnd();			
//DeadCode DAW 03Sep98			newitem->vely = vely;		
//DeadCode DAW 03Sep98			newitem->velhori = velhori;
//DeadCode DAW 03Sep98
			UWord	newhdg = Math_Lib.rnd();
			UWord	newpitch = (Math_Lib.rnd()*ANGLES_60Deg) >> 16;
			SWord	sin_ang, cos_ang;
			SLong	vel = 100 + (Math_Lib.rnd() * blowup)>>14;
			SLong	velhori,vely;

			Math_Lib.high_sin_cos((Angles)newpitch,sin_ang,cos_ang);

			vely = (vel * sin_ang)>>ANGLES_SHIFT;
			velhori = (vel * cos_ang)>>ANGLES_SHIFT;

			newitem->hdg = (Angles) newhdg;			
			newitem->vely = vely;		
			newitem->velhori = velhori;			
		}
//		else
//			newitem->hdg += ANGLES_180Deg;

		newitem->TransRandom = Math_Lib.rnd();

		//Make sure this bits-off part can have no smoketrails!!!
		SLong				nolaunchers = mad->nolaunchers;
		MoveGunAnimData*	weap;
		if (nolaunchers)
		{
			weap = (MoveGunAnimData*) newitem->Anim;
			for (index=0; index < nolaunchers; index++)
			{
				weap->weaponlaunchers[index].hdg = 0;
				weap->weaponlaunchers[index].pitch = 0;
				weap->weaponlaunchers[index].Stores = 0;
				weap->weaponlaunchers[index].LoadedStores = 0;
				weap->weaponlaunchers[index].stationshape = 0;
			}
		}

		AddTransientItemToWorld(newitem, worldptr);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchSmokeTrail
//Author		Paul.
//Date			Tue 30 Apr 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void TransObj::LaunchSmokeTrail(mobileitem* launcher,WorldStuff& worldptr)
{
	TransientItem*	newitem;

	newitem = LaunchGuidedMissile(	launcher,
									(itemptr )launcher,	//launcher==target
									SMKTRL,
									LIFETIME_SMOKETRAIL,MOBILE_SMOKETRAIL);
	if (newitem)
	{
		MoveGunAnimData*	adptr = (MoveGunAnimData*)newitem->Anim;
		WeapAnimData*		weapon = (WeapAnimData*) &adptr->weaponlaunchers[0];

		SHAPE.InitTrailFields((UByteP)weapon,0,32000,LT_FUEL);	//RJS 12Jan98

		LaunchVapourStream((UByteP)weapon,SMKTRL);				//RJS 17Sep97

		AddTransientItemToWorld(newitem, worldptr);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchGroundExplosion
//Author		Paul.
//Date			Wed 1 May 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void TransObj::LaunchGroundExplosion(mobileitem* launcher,WorldStuff& worldptr)
{
	TransientItem*	newitem;

//DeadCode RJS 01Aug96	_Miles.PlaySample((FileNum) FIL_SFX_FIREBURN_LOOP, (rotitem) View_Point, (ItemBasePtr) launcher);

	newitem = SimplifiedSpriteLaunch(	launcher,
										LargeFireShape,
										LIFETIME_GROUNDEXP,MOBILE_GROUNDEXP);//RJS 09Oct96
	if (newitem)
	{
		_Miles.PlaySample((FileNum) (FIL_SFX_EXPLOSION_OILDRUM1+Math_Lib.rnd(5)), (ItemBasePtr) newitem);//RJS 22Nov96

		SLong	groundlevel;									//MS 07May96

		groundlevel = GetGroundLevel(newitem);					//RJS 14Apr99

//DeadCode RJS 02Oct96		if (newitem->World.Y<groundlevel)						//MS 07May96
			newitem->World.Y=groundlevel;						//MS 07May96

		newitem->TransRandom = SmokeLaunchDelay;

		AddTransientItemToWorld(newitem, worldptr);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchSmoulder
//Author		Robert Slater
//Date			Wed 20 Nov 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void TransObj::LaunchSmoulder(mobileitem* launcher,WorldStuff& worldptr,Bool	uselch)
{
//DeadCode RJS 26Nov98	TransientItem*	newitem;
//DeadCode RJS 26Nov98	WeapAnimData*	weapon;										//RJS 09Dec96
//DeadCode RJS 26Nov98	SLong			xpos, ypos, zpos;							//RJS 09Dec96
//DeadCode RJS 26Nov98	UWord			mvel,mdelay,mburst;							//RDH 31Jul98
//DeadCode RJS 26Nov98
//DeadCode RJS 26Nov98	if (uselch)													//RJS 09Dec96
//DeadCode RJS 26Nov98		weapon = SHAPE.GetWeaponLauncher(launcher,0,xpos,ypos,zpos,mvel,mdelay,mburst,LT_VAPOUR);//RDH 31Jul98
//DeadCode RJS 26Nov98	else
//DeadCode RJS 26Nov98	{
//DeadCode RJS 26Nov98		xpos = launcher->World.X;								//RJS 09Dec96
//DeadCode RJS 26Nov98		ypos = launcher->World.Y;								//RJS 09Dec96
//DeadCode RJS 26Nov98		zpos = launcher->World.Z;								//RJS 09Dec96
//DeadCode RJS 26Nov98	}
//DeadCode RJS 26Nov98
//DeadCode RJS 26Nov98	newitem = SimplifiedSpriteLaunch(	launcher,
//DeadCode RJS 26Nov98										ShockwaveShape,
//DeadCode RJS 26Nov98										LIFETIME_GROUNDEXP/2,MOBILE_GROUNDEXP);
//DeadCode RJS 26Nov98
//DeadCode RJS 26Nov98	if (newitem)
//DeadCode RJS 26Nov98	{
//DeadCode RJS 26Nov98		SLong	groundlevel;								
//DeadCode RJS 26Nov98
//DeadCode RJS 26Nov98		groundlevel = Land_Scape.GetGroundLevel((itemptr )newitem);
//DeadCode RJS 26Nov98
//DeadCode RJS 26Nov98		if (newitem->World.Y<groundlevel)						
//DeadCode RJS 26Nov98			newitem->World.Y=groundlevel;
//DeadCode RJS 26Nov98
//DeadCode RJS 26Nov98		newitem->World.X = xpos;								//RJS 09Dec96
//DeadCode RJS 26Nov98		newitem->World.Y = ypos;								//RJS 09Dec96
//DeadCode RJS 26Nov98		newitem->World.Z = zpos;								//RJS 09Dec96
//DeadCode RJS 26Nov98
//DeadCode RJS 26Nov98		newitem->TransRandom = SmokeLaunchDelay;
//DeadCode RJS 26Nov98
//DeadCode RJS 26Nov98		AddTransientItemToWorld(newitem, worldptr);
//DeadCode RJS 26Nov98	}

	TransientItem*	newitem;
	newitem = SimplifiedSpriteLaunch(	launcher,
										VAPSHP,
										4500,					//RJS 25Jun99
										MOBILE_STATIONARY);

	if (newitem)
		AddTransientItemToWorld(newitem, worldptr);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchGuidedExplosion
//Author		Robert Slater
//Date			Mon 8 Jul 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::LaunchGuidedExplosion(mobileitem* launcher,WorldStuff& worldptr)
{
//	TransientItem*	newitem;
//
//	newitem = LaunchGuidedMissile(launcher,(itemptr) launcher,BigExplosionShape,LIFETIME_BIGEXP,MOBILE_MOBEXP);
//
//	if (newitem)
//	{
//		AddTransientItemToWorld(newitem, worldptr);
//		_Miles.PlaySample((FileNum) (FIL_SFX_EXPLOSION_GROUND+Math_Lib.rnd(5)), (ItemBasePtr) newitem);//RJS 22Nov96
//	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchGuidedBurning
//Author		Robert Slater
//Date			Mon 8 Jul 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::LaunchGuidedBurning(mobileitem* launcher,WorldStuff& worldptr)
{
	TransientItem*	newitem;

	newitem = SimplifiedSpriteLaunch(	launcher,
										SmallFireShape,
										LIFETIME_SMALLFIRE,
										MOBILE_FIRE);

	if (newitem)
	{
		if ((launcher->Status.size >= MovingSize) && (launcher->Status.size != TransientSize))
		{
			newitem->Target = launcher;
			newitem->pitch = (Angles)50;
		}

		AddTransientItemToWorld(newitem, worldptr);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchGuidedFire
//Author		Robert Slater
//Date			Tue 9 Jul 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::LaunchGuidedFire(mobileitem* launcher,WorldStuff& worldptr)
{
	TransientItem*	newitem;

	newitem = SimplifiedSpriteLaunch(	launcher,
										PLUME1,
										3000,
										MOBILE_STATIONARY);

	if (newitem)
		AddTransientItemToWorld(newitem, worldptr);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchBombDrop
//Author		Robert Slater
//Date			Wed 24 Jul 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::LaunchBombDrop(mobileitem* launcher,ShapeNum	bombshape,SLong xpos, SLong ypos, SLong zpos,WorldStuff& worldptr,Bool	duff)
{
	TransientItem*	newitem;

//DeadCode AMM 02Jul99 	_Replay.guncameradelay=BOMBDELAY;					//AMM 25Jan99

	if (duff)													//RJS 03Dec96
		newitem = LaunchUnguidedMissile((mobileitem* )launcher,bombshape,LIFETIME_BOMB,MOBILE_MUSHROOM);//RJS 17Nov98
	else													
		newitem = LaunchUnguidedMissile((mobileitem* )launcher,bombshape,LIFETIME_BOMB,MOBILE_BOMBDROP);//RJS 03Dec96

	if (newitem)
	{
// want to keep recording for a while after bomb has been dropped so that
// people can see robs cool effects and stuff!
		if (launcher == Manual_Pilot.ControlledAC2)
		{
			newitem->hdg = Math_Lib.arctan(launcher->velx,launcher->velz);			//RJS 04May99
			if (Save_Data.gamedifficulty[GD_GUNCAMERAONTRIGGER] && !_DPlay.Implemented && !_Replay.Record)//RJS 02Jul99
			{													//RJS 02Jul99
				_Replay.StartRecordFlag=TRUE;					//RJS 02Jul99
				_Replay.guncameradelay=BOMBDELAY;				//RJS 02Jul99
			}													//RJS 02Jul99
		}

		if (!duff)												//RJS 10Jun99
			newitem->isArmed = 1;								//RJS 19May99

//DeadCode DAW 02Jul99 		if (Save_Data.gamedifficulty[GD_GUNCAMERAONTRIGGER] && !_DPlay.Implemented && !_Replay.Record)//AMM 25Jan99
//DeadCode DAW 02Jul99 		{													//AMM 25Jan99
//DeadCode DAW 02Jul99 			_Replay.StartRecordFlag=TRUE;					//AMM 25Jan99
//DeadCode DAW 02Jul99 		}													//AMM 25Jan99

//		newitem->pitch = ANGLES_0Deg;
		newitem->TransRandom = LIFETIME_BOMB - 150;
		newitem->World.X = xpos;								//RJS 29Aug96
		newitem->World.Y = ypos;								//RJS 29Aug96
		newitem->World.Z = zpos;								//RJS 29Aug96

		if ((_Replay.Playback || _Replay.Record) && launcher==Persons2::PlayerSeenAC)
		{
// velhori will be wrong so recalc

			SLong totalvel=Persons2::PlayerSeenAC->vel;
			SWord	sin_ang,cos_ang;
			Math_Lib.high_sin_cos(Persons2::PlayerSeenAC->pitch,sin_ang,cos_ang);
			newitem->velhori = (totalvel * cos_ang)>>ANGLES_SHIFT;
		}

		AddTransientItemToWorld(newitem, worldptr);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchVapourStream
//Author		Robert Slater
//Date			Thu 8 Aug 1996
//
//Description	Set up pointer to vapour animation
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
UWord	TransObj::LaunchVapourStream(	UByteP		weapptr,
										ShapeNum	vapshape,
										SWord		velh,
										SWord		vely,
										SWord		resistance,
										UByteP		smkptr	)
{
	UWord			oldindex = 0;								//RJS 08Apr99
#ifndef	_NOSMOKETRAILS_											//RJS 08Apr99
	ShapeDescPtr	sdptr = SHAPESTUFF.GetShapePtr(vapshape);	//RJS 17Sep97
	WeapAnimData*	weapon = (WeapAnimData*) weapptr;			//RJS 17Sep97
	SByte			index;										//RJS 17Sep97

	if (weapon && sdptr->Type.VapourType)						//RJS 10Mar99
	{
		index = (SByte) weapon->hdg;						//RJS 12Jan98
		if (index < 0)
		{
			oldindex = -index;
//DeadCode RDH 13Apr99			index = 0;
		}

		if (index == 0)
		{
			if (	(weapon->LauncherType == LT_CONTRAIL)
				|| (weapon->LauncherType == LT_MUDDY))
				weapon->pitch = -1;							//RJS 12Jan98

			weapon->hdg = SHAPE.NextFreeVapour(velh,vely,resistance,smkptr);//RJS 09Apr98
		}
	}
#else
	#pragma message (__HERE__ "Smoke-trails disabled!")
#endif
	return(oldindex);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchBigExplosion
//Author		Robert Slater
//Date			Mon 12 Aug 1996
//
//Description	For destroying something big, like a balloon
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::LaunchBigExplosion(mobileitem* launcher,WorldStuff& worldptr,ShapeNum	groundshape)
{
	TransientItem*	newitem;
	SLong			dx, dy, dz, dh;
	SLong			distance;
	SWord			thehdg, thehdg1;
	SWord			pitch;
	SLong			radius;
	SWord			sin_ang,cos_ang;
	ShapeDescPtr	sdptr;										//RJS 08Nov96
	SWord			shpsize;
	
	MinAnimData* mad = (MinAnimData* )launcher->Anim;			//RJS 08Nov96

	_Miles.PlayOnce((FileNum) (FIL_SFX_EXPLOSION_GROUND+Math_Lib.rnd(5)),launcher);

	sdptr = (ShapeDescPtr) SHAPESTUFF.GetShapePtr(groundshape);
	shpsize = sdptr->Size << 4;

	SLong	tot2 = (shpsize * 6)/832;
	SLong	totexp = (tot2 + Math_Lib.rnd(tot2))/2;
	SLong	i;

	for (i=0; i < totexp; i++)
	{
		newitem	= RelativeSpriteLaunch(launcher,groundshape,BEXP,Math_Lib.rnd(100),MOBILE_DELEXP);//DAW 03Sep98
		if (newitem)
		{
			MinAnimData*	mad = (MinAnimData*) newitem->Anim;
			mad->IsInvisible = 1;

			thehdg = Math_Lib.rnd();
			radius = Math_Lib.rnd(shpsize);

			Math_Lib.high_sin_cos((Angles)thehdg,sin_ang,cos_ang);		
			dx = (cos_ang * radius) / ANGLES_FRACT;					
			dz = (sin_ang * radius) / ANGLES_FRACT;					

			newitem->World.X += dx;
			newitem->World.Z += dz;
			newitem->World.Y += Math_Lib.rnd(250) - 125;

			AddTransientItemToWorld(newitem, worldptr);
		}
	}

//DeadCode DAW 27Nov98	LaunchSkinDebris(launcher,worldptr);
	LaunchSparkDebris(launcher,worldptr);			
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchMovingSmoke
//Author		Robert Slater
//Date			Mon 2 Sep 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::LaunchRealShockwave(mobileitem* launcher,UByte strength,WorldStuff& worldptr)
{
	TransientItem*	newitem;

	newitem = SimplifiedSpriteLaunch(	launcher,
										ShockwaveShape,			//RJS 20Nov96
										50,MOBILE_DODAMAGE);	//RJS 23Jun99
	if (newitem)
	{
		if (launcher->Status.size == TRANSIENTSIZE)							//RJS 12Apr99
			newitem->Launcher = ((TransientItem*)launcher)->Launcher;		//RJS 12Apr99

		MissileAnimData*	adptr = (MissileAnimData*) newitem->Anim;
//DeadCode DAW 23Jun99 		adptr->hitstrength = (3*strength)>>1;								//RJS 1/20/99//RJS 26Feb99
 		adptr->hitstrength = strength;								//RJS 23Jun99

		newitem->isArmed = 1;												//RJS 10Jun99

		AddTransientItemToWorld(newitem, worldptr);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchRicochetSmoke
//Author		Robert Slater
//Date			Thu 5 Sep 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::LaunchRicochetSmoke(mobileitem* launcher,ShapeNum	theShape,WorldStuff& worldptr)
{
	TransientItem*	newitem;

	newitem = SimplifiedSpriteLaunch(	launcher,
										theShape,
										LIFETIME_SMOKE,MOBILE_STATIONARY);
	if (newitem)
	{
		if (launcher->Status.size >= MOBILESIZE)
		{
			newitem->vely = launcher->vely;
			newitem->velhori = launcher->velhori;
		}
		SLong	groundlevel;								
//DeadCode RJS 19Feb98		ExplodeAnimData* adptr;

//		groundlevel = GetGroundLevel(newitem);					//RJS 14Apr99
//
//		if (newitem->World.Y<groundlevel)						
//			newitem->World.Y=groundlevel;

//DeadCode RJS 19Feb98		adptr = (ExplodeAnimData* )newitem->Anim;
//DeadCode RJS 19Feb98		adptr->frameno = Math_Lib.rnd(3);						//RJS 06Dec96
		newitem->roll = (Angles) 0;								//RJS 03Dec96
		newitem->pitch = (Angles) 1;							//RJS 06Dec96

		AddTransientItemToWorld(newitem, worldptr);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchDustRing
//Author		Robert Slater
//Date			Sun 13 Oct 1996
//
//Description	Launches a ring of dust balls around an item
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::LaunchDustRing(mobileitem* launcher,WorldStuff& worldptr)
{
	TransientItem*	newitem;
	newitem = SimplifiedSpriteLaunch(	launcher,
										GRNDD6,
										300,MOBILE_STATIONARY);

	if (newitem)
		AddTransientItemToWorld(newitem, worldptr);
}

 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
 //Procedure		LaunchShockwave
 //Author		Robert Slater
 //Date			Wed 16 Oct 1996
 //
 //Description	
 //
 //Inputs		
 //
 //Returns	
 //
 //------------------------------------------------------------------------------
 void	TransObj::LaunchShockwave(mobileitem* launcher,WorldStuff& worldptr)
 {
	if (Save_Data.desiredfps <= realFrameTime)					//RJS 11Jun99
	{
		TransientItem*	newitem;

		newitem = SimplifiedSpriteLaunch(	launcher,
											ExplosionShockShape,
											100,MOBILE_STATIONARY);//no damage at the mo...
		if (newitem)
		{
			Three_Dee.pMigLand->GetShadowAngles(newitem->World,newitem->hdg,newitem->pitch,newitem->roll);
			newitem->World.Y += (METRES01*3);						//RJS 21Apr99

			AddTransientItemToWorld(newitem, worldptr);
		}
	}
 }

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchBirds
//Author		Robert Slater
//Date			Thu 17 Oct 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::LaunchBirds(mobileitem* launcher,ShapeNum	birdshape,WorldStuff& worldptr)
{
//DeadCode RJS 21Apr99	TransientItem*	newitem;
//DeadCode RJS 21Apr99	UByte			count;
//DeadCode RJS 21Apr99	UByte			nobirds;
//DeadCode RJS 21Apr99	ShapeDescPtr	sdptr;
//DeadCode RJS 21Apr99	SLong			xpos, ypos, zpos;
//DeadCode RJS 21Apr99	ShapeNum		newshp;
//DeadCode RJS 21Apr99	FireAnimData*	adptr;
//DeadCode RJS 21Apr99	UByteP			adptrtmp;
//DeadCode RJS 21Apr99	int				treeheight;									//RJS 06Dec96
//DeadCode RJS 21Apr99	Bool			foundone,flyaway;
//DeadCode RJS 21Apr99
//DeadCode RJS 21Apr99	sdptr = SHAPESTUFF.GetShapePtr(PCHUTE);						//AM 14Jan97
//DeadCode RJS 21Apr99	treeheight = (3 * sdptr->sy) >> 2;							//RJS 06Dec96
//DeadCode RJS 21Apr99
//DeadCode RJS 21Apr99	sdptr = SHAPESTUFF.GetShapePtr(launcher->shape);
//DeadCode RJS 21Apr99	adptrtmp = (UByteP) launcher->Anim;
//DeadCode RJS 21Apr99
//DeadCode RJS 21Apr99	foundone = FALSE;
//DeadCode RJS 21Apr99	flyaway = FALSE;
//DeadCode RJS 21Apr99
//DeadCode RJS 21Apr99	if (SHAPESTUFF.GetShapeScale(sdptr) == SHP_GRP)
//DeadCode RJS 21Apr99	{
//DeadCode RJS 21Apr99		UByteP		instr_ptr;
//DeadCode RJS 21Apr99		instr_ptr = (UByteP )sdptr + sdptr->liveshpref;
//DeadCode RJS 21Apr99
//DeadCode RJS 21Apr99		while (SHAPE.GetGroupElement(instr_ptr,newshp,xpos,ypos,zpos))
//DeadCode RJS 21Apr99		{
//DeadCode RJS 21Apr99			sdptr = SHAPESTUFF.GetShapePtr(newshp);
//DeadCode RJS 21Apr99
//DeadCode RJS 21Apr99			if (	(sdptr->AnimDataSize == FLAMEANIM)
//DeadCode RJS 21Apr99				&&	(newshp != TroopLauncherShape)	)			//RJS 08Nov96
//DeadCode RJS 21Apr99			{
//DeadCode RJS 21Apr99				foundone = TRUE;
//DeadCode RJS 21Apr99				break;
//DeadCode RJS 21Apr99			}
//DeadCode RJS 21Apr99
//DeadCode RJS 21Apr99			adptrtmp = (UByteP) ((ULong)adptrtmp + SHAPE.GetElementAnimOffset(newshp));
//DeadCode RJS 21Apr99		}
//DeadCode RJS 21Apr99	}
//DeadCode RJS 21Apr99
//DeadCode RJS 21Apr99	if (foundone)
//DeadCode RJS 21Apr99	{
//DeadCode RJS 21Apr99		adptr = (FireAnimData*) adptrtmp;
//DeadCode RJS 21Apr99
//DeadCode RJS 21Apr99		if ((adptr->itemstate == ALIVE) && (adptr->frameno == 0))
//DeadCode RJS 21Apr99			flyaway = TRUE;
//DeadCode RJS 21Apr99	}
//DeadCode RJS 21Apr99	else
//DeadCode RJS 21Apr99	{
//DeadCode RJS 21Apr99		MinAnimData*	mad = (MinAnimData*) launcher->Anim;	//RJS 07Feb97
//DeadCode RJS 21Apr99																//RJS 07Feb97
//DeadCode RJS 21Apr99		if (mad->itemstate == ALIVE)							//RJS 07Feb97
//DeadCode RJS 21Apr99			flyaway = TRUE;										//RJS 07Feb97
//DeadCode RJS 21Apr99
//DeadCode RJS 21Apr99		xpos = 0;
//DeadCode RJS 21Apr99		ypos = 0;
//DeadCode RJS 21Apr99		zpos = 0;
//DeadCode RJS 21Apr99	}
//DeadCode RJS 21Apr99
//DeadCode RJS 21Apr99	if (flyaway)
//DeadCode RJS 21Apr99	{
//DeadCode RJS 21Apr99		if (foundone)
//DeadCode RJS 21Apr99			adptr->frameno = 1;
//DeadCode RJS 21Apr99
//DeadCode RJS 21Apr99		nobirds = 2 + Math_Lib.rnd(6);							//RJS 06Dec96
//DeadCode RJS 21Apr99
//DeadCode RJS 21Apr99		for (count = 0; count < nobirds; count++)
//DeadCode RJS 21Apr99		{
//DeadCode RJS 21Apr99			newitem = SimplifiedSpriteLaunch(	launcher,		//RDH 20Dec96
//DeadCode RJS 21Apr99												birdshape,
//DeadCode RJS 21Apr99												LIFETIME_DEBRISLNCHR*4,MOBILE_BIRD);
//DeadCode RJS 21Apr99
//DeadCode RJS 21Apr99			if (newitem)
//DeadCode RJS 21Apr99			{
//DeadCode RJS 21Apr99				SLong	groundlevel;								
//DeadCode RJS 21Apr99 //DeadCode RJS 19Feb98				ExplodeAnimData* adptr;
//DeadCode RJS 21Apr99
//DeadCode RJS 21Apr99				groundlevel = GetGroundLevel(newitem);			//RJS 14Apr99
//DeadCode RJS 21Apr99
//DeadCode RJS 21Apr99				newitem->World.X += xpos;
//DeadCode RJS 21Apr99				newitem->World.Y += ypos + treeheight;			//RJS 06Dec96
//DeadCode RJS 21Apr99				newitem->World.Z += zpos;
//DeadCode RJS 21Apr99
//DeadCode RJS 21Apr99				if (newitem->World.Y<groundlevel)						
//DeadCode RJS 21Apr99					newitem->World.Y=groundlevel;
//DeadCode RJS 21Apr99
//DeadCode RJS 21Apr99				newitem->hdg = (Angles) Math_Lib.rnd();
//DeadCode RJS 21Apr99				newitem->velhori = 100 + Math_Lib.rnd(50);
//DeadCode RJS 21Apr99				newitem->vely = 50 + Math_Lib.rnd(50);
//DeadCode RJS 21Apr99
//DeadCode RJS 21Apr99 //DeadCode RJS 19Feb98				adptr = (ExplodeAnimData* )newitem->Anim;
//DeadCode RJS 21Apr99 //DeadCode RJS 19Feb98				adptr->frameno = 0;
//DeadCode RJS 21Apr99
//DeadCode RJS 21Apr99				AddTransientItemToWorld(newitem, worldptr);
//DeadCode RJS 21Apr99			}
//DeadCode RJS 21Apr99		}
//DeadCode RJS 21Apr99	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchAmmoBoxes
//Author		Robert Slater
//Date			Thu 17 Oct 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::LaunchIgniteAmmoBoxes(mobileitem* launcher,UByte gindex,WorldStuff& worldptr)
{
	TransientItem*	newitem;
	UWord			halfdetonate;
	UWord			detonate;
	ShapeNum		shapehit;
	MyGroundVector	pos;
	MinAnimData*	mad = (MinAnimData*) SHAPE.GetGroupItemAnim(launcher,shapehit,gindex,&pos);
	UWord			animoffset = launcher->Anim.Offset(mad);//((UByteP)mad) - ((UByteP)&launcher->Anim[0]);

	halfdetonate = (DEAD - mad->itemstate)*100;
	detonate = halfdetonate + Math_Lib.rnd(halfdetonate);

	newitem = SimplifiedSpriteLaunch(	launcher,
										ShockwaveShape,
										detonate,MOBILE_AMMODEATH);
	if (newitem)
	{
		SLong	groundlevel;								
		groundlevel = GetGroundLevel(newitem);					//RJS 14Apr99

		newitem->roll = (Angles) CLUSTA;						//RJS 26May99
		newitem->pitch = (Angles) shapehit;
		newitem->TransRandom = animoffset;						//RJS 20Nov98
		newitem->World.Y = groundlevel;

		AddTransientItemToWorld(newitem, worldptr);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchDustTrail
//Author		Robert Slater
//Date			Thu 31 Oct 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::LaunchDustTrail(	mobileitem* launcher,
									WorldStuff& worldptr,
									SByte	distance)
{
/*	TransientItem*	newitem;
	Bool			isplane = TRUE;								//RDH 08Nov96
	SLong			dx,dz,radius;								//RJS 13Nov96
	ANGLES			direction = launcher->hdg + ANGLES_180Deg;//RJS 13Nov96

	if (launcher->velhori < MPHHALF)							//RJS 15Dec96
		return;

	if (distance > -1)											//RJS 13Nov96
		isplane = FALSE;

	if (isplane)												//RJS 13Nov96
	{
		newitem = SimplifiedSpriteLaunch(	launcher,
											DustShape,
											LIFETIME_RICOCHET,MOBILE_STATIONARY);//RJS 20Apr98

		dx = 0;													//RJS 13Nov96
		dz = 0;													//RJS 13Nov96
	}
	else
	{
		ShapeDescPtr	sdptr = SHAPESTUFF.GetShapePtr(launcher->shape);//RJS 13Nov96
		SWord			sin_ang,cos_ang;						//RJS 13Nov96

		newitem = SimplifiedSpriteLaunch(	launcher,
											DustShape,
											LIFETIME_RICOCHET*2,MOBILE_STATIONARY);//RJS 20Apr98

		radius = sdptr->sz << 4;								//RJS 13Nov96

		Math_Lib.high_sin_cos(direction,sin_ang,cos_ang);		//RJS 13Nov96
		dx = (cos_ang * radius) / ANGLES_FRACT;					//RJS 13Nov96
		dz = (sin_ang * radius) / ANGLES_FRACT;					//RJS 13Nov96
	}

	if (newitem)
	{
//DeadCode RJS 19Nov96		SLong	groundlevel = Land_Scape.GetGroundLevel((itemptr )newitem);//RJS 13Nov96

		if (isplane)
			direction += (Angles)(Math_Lib.rnd(ANGLES_90Deg) - ANGLES_45Deg);//RDH 08Nov96

//DeadCode RJS 19Nov96		newitem->World.Y=groundlevel;
		newitem->World.X += dx;									//RJS 13Nov96
		newitem->World.Z += dz;									//RJS 13Nov96
		newitem->hdg = direction;

		if (!isplane && (distance == 1))						//RJS 13Nov96
			newitem->velhori = 200 + Math_Lib.rnd(200);		
		else
			newitem->velhori = Math_Lib.rnd(200);

		AddTransientItemToWorld(newitem, worldptr);
	}*/
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchDustTrail2
//Author		Robert Slater
//Date			Thu 8 Jan 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::LaunchDustTrail2(	mobileitem* launcher,
									WorldStuff& worldptr	)
{
	TransientItem*	newitem;

	newitem = LaunchGuidedMissile(	launcher,
									(itemptr )launcher,
									DUSSHP,
									LIFETIME_SMOKETRAIL,MOBILE_SMOKETRAIL);
	if (newitem)
	{
		MoveGunAnimData*	adptr = (MoveGunAnimData*)newitem->Anim;
		WeapAnimData*		weapon = (WeapAnimData*) &adptr->weaponlaunchers[0];

		SHAPE.InitTrailFields((UByteP)weapon,0,32000,LT_DUST);	//RJS 12Jan98

		LaunchVapourStream((UByteP)weapon,DUSSHP);				//RJS 17Sep97

		AddTransientItemToWorld(newitem, worldptr);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchMushroomCloud
//Author		Robert Slater
//Date			Wed 6 Nov 1996
//
//Description	Throw several dust shapes into the air
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::LaunchMushroomCloud(mobileitem* launcher,SLong impact,WorldStuff& worldptr)
{
	TransientItem*	newitem;
	SLong			count = 0;
	ShapeDescPtr	sdptr = SHAPESTUFF.GetShapePtr(launcher->shape);
	SLong			sx = sdptr->sx<<4;
	SLong			sz = sdptr->sz<<4;
	SLong			sx2 = sx<<1;
	SLong			sz2 = sz<<1;
	SLong			totsize = sdptr->Size << 4;
	SLong			tot = totsize + ((Math_Lib.rnd()*totsize)>>16);

	sdptr = SHAPESTUFF.GetShapePtr(BDUST);
	if (Save_Data.desiredfps <= realFrameTime)					//RJS 11Jun99
	{															//RJS 28May99
		tot /= (sdptr->Size << 4);								//RJS 28May99
		tot *= impact;											//RJS 28May99
		tot /= 16;												//RJS 28May99
	}															//RJS 28May99
	else														//RJS 28May99
		tot = 1;												//RJS 28May99

	do
	{
		newitem = RelativeSpriteLaunch(		launcher,
											launcher->shape,
											BDUST,
											500,					//RJS 18May99
											MOBILE_STATIONARY);		//RJS 06Oct98
		if (newitem)
		{
//DeadCode RJS 28May99 			sdptr = SHAPESTUFF.GetShapePtr(BDUST);
			newitem->DrawOffset += sdptr->Size << 2;

			newitem->World.X += Math_Lib.rnd(sx2) - sx;
			newitem->World.Z += Math_Lib.rnd(sz2) - sz;
			newitem->World.Y += Math_Lib.rnd(500) - 250;

			AddTransientItemToWorld(newitem, worldptr);
		}
		count++;
	}while (count < tot);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchSmokePuff
//Author		Robert Slater
//Date			Thu 14 Nov 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::LaunchSmokePuff(	mobileitem* launcher,
									ShapeNum	theShape,
									SLong		xpos,
									SLong		ypos,
									SLong		zpos,
									WorldStuff& worldptr)
{
	TransientItem*	newitem;
	newitem = SimplifiedSpriteLaunch(	launcher,
										theShape,
										134,MOBILE_CRATER);
	
	if (newitem)
	{
		UWord	randno = Math_Lib.rnd();
		SWord	heading = ANGLES_180Deg + ((randno>>3) - 4096);
		
		newitem->hdg = (Angles) (launcher->hdg + heading);
		newitem->velhori = Math_Lib.rnd()>>12;
		newitem->World.X = xpos;
		newitem->World.Y = ypos;
		newitem->World.Z = zpos;
		newitem->TransRandom = 0;							//RJS 09Dec96

		newitem->vely = 16-newitem->velhori;

		AddTransientItemToWorld(newitem, worldptr);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchFuelBarrels
//Author		Robert Slater
//Date			Fri 22 Nov 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::LaunchFuelBarrels(mobileitem* launcher,WorldStuff& worldptr)
{
	if (Save_Data.desiredfps <= realFrameTime)					//RJS 11Jun99
	{
		TransientItemPtr	newitem;						
		UByte			count;

		for (count = 0; count < 4; count++)
		{
			newitem = SimplifiedSpriteLaunch((mobileitem*)launcher,CLUSTF,//RJS 26May99
											LIFETIME_DEBRISLNCHR,MOBILE_DEBRIS);
			if (newitem)
			{
				newitem->vely = 100 + Math_Lib.rnd(150);			//RJS 16Aug96
				newitem->velhori = 100 + Math_Lib.rnd(100);			//RJS 16Aug96
				newitem->World.Y += 100;						//RJS 03Jun99
				newitem->TransRandom = Math_Lib.rnd();				//RJS 16Aug96
				AddTransientItemToWorld(newitem,worldptr);
			}
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchScatteredFire
//Author		Robert Slater
//Date			Fri 6 Dec 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::LaunchScatteredFire(mobileitem* launcher,ShapeNum	shapehit,WorldStuff& worldptr)
{
	TransientItem*	newitem;
	ShapeDescPtr	sdptr = SHAPESTUFF.GetShapePtr(shapehit);
	ShapeDescPtr	sdptr2 = SHAPESTUFF.GetShapePtr(SmallScatFireShape);
	ULong			area_m = (sdptr->sx << 4) * (sdptr->sz << 4);
	ULong			area_s = (sdptr2->sx << 4) * (sdptr2->sz << 4);
	ULong			count = area_m / area_s;
	ULong			i;
	SLong			sx = (sdptr->sx << 4);
	SLong			sz = (sdptr->sz << 4);
	ShapeNum		theshape = SmallScatFireShape;

	if (Save_Data.desiredfps <= realFrameTime)					//RJS 11Jun99
	{
		count /= 16;
		count = count + Math_Lib.rnd(count) + 1;
		if (count > 16)
		{
			theshape = LargeScatFireShape;
			count /= 8;
			if (count > 16)
				count = 16;
		}
	}
	else
		count = 1;												//RJS 28May99

	for (i=0; i < count; i++)
	{
		newitem = SimplifiedSpriteLaunch(launcher,theshape,Math_Lib.rnd(1500)+1500,MOBILE_STATIONARY);//RJS 11Jan98
		if (newitem)
		{
			newitem->World.X += ((sx * Math_Lib.rnd())>>15) - sx;
			newitem->World.Z += ((sz * Math_Lib.rnd())>>15) - sz;
			newitem->World.Y = GetGroundLevel(newitem);			//RJS 14Apr99

			AddTransientItemToWorld(newitem,worldptr);
		}
	}

	LaunchGuidedFire(launcher,worldptr);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchVapourTransient
//Author		Robert Slater
//Date			Tue 27 May 1997
//
//Description	Gives an invisible transient vapour item an already known
//				vapour list....
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool	TransObj::LaunchVapourTransient(	mobileitem*	launcher,
											SLong			xpos,
											SLong			ypos,
											SLong			zpos,
											int				index,
											int				lifetime,
											WorldStuff&		worldptr,
											ShapeNum		theshape)
{
	Bool	retval = TRUE;										//RJS 13May99
	if (trailcounter >= MaxTrails)								//RJS 06Apr99
		retval = KillOldestTrail(launcher);						//RJS 13May99

	if (retval)
	{
		TransientItemPtr	newitem;
		newitem = SimplifiedSpriteLaunch(	launcher,
											theshape,							//RJS 03Dec97
											lifetime,
											MOBILE_STATIONARY);		//RJS 20Apr98

		if (newitem)
		{
			MoveGunAnimData*	adptr = (MoveGunAnimData*) newitem->Anim;
	
			if (launcher->Status.size == TRANSIENTSIZE)				//RJS 21Apr99
				newitem->Launcher = NULL;							//RJS 21Apr99

			newitem->World.X = xpos;
			newitem->World.Y = ypos;
			newitem->World.Z = zpos;

			adptr->weaponlaunchers[0].hdg = -index;					//RJS 21Jan99
			adptr->weaponlaunchers[0].pitch = -1;					//RJS 28Jan98
			//Don't really care what type, as long as its valid...
			adptr->weaponlaunchers[0].LauncherType = LT_VAPOUR;	//RJS 13Apr99
			AddTransientItemToWorld(newitem, worldptr);

			trailcounter++;											//RJS 06Apr99
		}
		else
			retval = FALSE;
	}

	return(retval);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchRocket
//Author		Robert Slater
//Date			Tue 3 Jun 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
TransientItem* TransObj::LaunchRocket(mobileitem* launcher,ShapeNum	weapshape,SLong xpos, SLong ypos, SLong zpos, WorldStuff& worldptr)
{
	TransientItem* newitem;

	newitem=LaunchUnguidedMissile(launcher,weapshape,LIFETIME_ROCKET,MOBILE_ROCKET);//RJS 26mAR99

	if (newitem)
	{
		SWord	vx,vy,vz,vhori;									//RJS 10Jun99

//DeadCode AMM 18Jun99 		if (launcher == Persons2::PlayerSeenAC)					//RJS 10Jun99
//DeadCode DAW 28Jun99 		if (launcher == Persons2::PlayerSeenAC && !_Replay.Playback)//AMM 18Jun99
		if (launcher == Persons2::PlayerSeenAC && !_Replay.Playback && !_Replay.Record)//AMM 28Jun99
		{
			((AirStrucPtr)launcher)->fly.pModel->CalcLauncherVel(1500,vx,vy,vz);

			newitem->velx = vx;
			newitem->vely = vy;
			newitem->velz = vz;
			newitem->velhori = Math_Lib.distance3d(vx,vz,0);
			newitem->hdg = Math_Lib.arctan(vx,vz);
		}
		else
		{
			SLong	temp;
			SWord	sin_ang,cos_ang;
			SLong	totalvel = launcher->vel + 1500;


			Math_Lib.high_sin_cos(launcher->pitch,sin_ang,cos_ang);

			newitem->vely = (totalvel * sin_ang)>>ANGLES_SHIFT;
			newitem->velhori = (totalvel * cos_ang)>>ANGLES_SHIFT;

			Math_Lib.high_sin_cos(launcher->hdg,sin_ang,cos_ang);

			temp = (newitem->velhori * sin_ang)>>ANGLES_SHIFT; newitem->velx = (SWord )temp;
			temp = (newitem->velhori * cos_ang)>>ANGLES_SHIFT; newitem->velz = (SWord )temp;
		}

		newitem->World.X = xpos;								
		newitem->World.Y = ypos;								
		newitem->World.Z = zpos;

		//Give it a 3 second burn burst....						//RJS 15Jun99!!
		newitem->TransRandom = 300;								//RJS 15Jun99

		MoveGunAnimData	*adptr = (MoveGunAnimData*)newitem->Anim;
		WeapAnimData*	weapon = (WeapAnimData*) &adptr->weaponlaunchers[0];

		adptr->itemstate = DEAD;

		SHAPE.InitTrailFields((UByteP)weapon,0,5000,LT_FUEL);

		_Miles.PlayOnce(FIL_SFX_MISSILE2, newitem);
		LaunchVapourStream((UByteP)weapon,newitem->shape);

//Dead		if (launcher == Manual_Pilot.ControlledAC2)				//RJS 19May99
			newitem->isArmed = 1;								//RJS 19May99

		AddTransientItemToWorld(newitem,worldptr);
	}
	return newitem;					
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchFuelDrop
//Author		Robert Slater
//Date			Tue 10 Jun 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
TransientItem* TransObj::LaunchFuelDrop(mobileitem* launcher,ShapeNum	weapshape,WeapAnimData*	weapon,SLong xpos, SLong ypos, SLong zpos, WorldStuff& worldptr)
{
	TransientItem*	newitem;
	newitem=LaunchUnguidedMissile(launcher,weapshape,LIFETIME_BOMB,MOBILE_FUELDROP);//RJS 28May98

	if (newitem)
	{
		SLong	temp;
		SWord	sin_ang,cos_ang;
		ShapeDescPtr	sdptr = SHAPESTUFF.GetShapePtr(weapshape);

		if (sdptr->Type.VapourType)												//RJS 10Mar98
		{
			MoveGunAnimData*	adptr = (MoveGunAnimData*)newitem->Anim;
			DirectAnimData*		newweapon = (DirectAnimData*) &adptr->weaponlaunchers[0];

			//Inherit leaks...
			adptr->weaponlaunchers[0].hdg = weapon->hdg;
			adptr->weaponlaunchers[0].pitch = weapon->pitch;
		}

		weapon->LoadedStores = 0;

		newitem->World.X = xpos;								
		newitem->World.Y = ypos;								
		newitem->World.Z = zpos;

		newitem->TransRandom = 1;								//RJS 28May98

		SWord	tip = Math_Lib.rnd() >> 5;
//		tip <<= 1;

		newitem->TransRandom += tip;
		newitem->pitch = ANGLES_0Deg;
		if (((AirStrucPtr)launcher)->AcIsPlayer())
		{
			SWord	vx,vy,vz;

//DeadCode DAW 28Jun99 			if (!_Replay.Playback)
			if (!_Replay.Playback && !_Replay.Record)			//AMM 28Jun99
			{
				((AirStrucPtr)launcher)->fly.pModel->CalcParachuteVel(vx,vy,vz,launcher->hdg,launcher->pitch,launcher->roll,launcher->vel/10,-10, launcher->World.Y);	//CSB 13/06/99	

				newitem->velx = vx;
				newitem->vely = vy;
				newitem->velz = vz;
				newitem->velhori = Math_Lib.distance3d(vx,vz,0);
				newitem->hdg = Math_Lib.arctan(vx,vz);				//DAW 11May99
				newitem->pitch = launcher->pitch;
				newitem->roll = launcher->roll;
			}
			else
			{
				SLong	temp;
				SWord	sin_ang,cos_ang;
				SLong	totalvel = launcher->vel;

				Math_Lib.high_sin_cos(launcher->pitch,sin_ang,cos_ang);
				newitem->vely = (totalvel * sin_ang)>>ANGLES_SHIFT;
				newitem->velhori = (totalvel * cos_ang)>>ANGLES_SHIFT;
				Math_Lib.high_sin_cos(launcher->hdg,sin_ang,cos_ang);
				temp = (newitem->velhori * sin_ang)>>ANGLES_SHIFT; newitem->velx = (SWord )temp;
				temp = (newitem->velhori * cos_ang)>>ANGLES_SHIFT; newitem->velz = (SWord )temp;

				newitem->hdg=launcher->hdg;
				newitem->pitch = launcher->pitch;
				newitem->roll = launcher->roll;
			}
		}
		else
			newitem->vely -= 200;				//A bit of a push...//RJS 11Dec98

		AddTransientItemToWorld(newitem,worldptr);
	}
	return newitem;		
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchGunPuff
//Author		Robert Slater
//Date			Mon 5 Jan 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void TransObj::LaunchGunPuff(mobileitem* launcher,SLong xpos, SLong ypos, SLong zpos, WorldStuff& worldptr)
{
	TransientItem*	newitem;
	newitem=LaunchUnguidedMissile(launcher,MigPuffShape,6,MOBILE_GANDF);//RJS 20Apr98

	if (newitem)
	{
		newitem->World.X = xpos;								
		newitem->World.Y = ypos;								
		newitem->World.Z = zpos;								

		AddTransientItemToWorld(newitem,worldptr);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchWeapon
//Author		Robert Slater
//Date			Tue 10 Jun 1997
//
//Description	Launches a weapon depending on the weapon's type.
//				Also will eventually log the weapon for comms...
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
//DeadCode AMM 09Apr99 void TransObj::LaunchWeapon(AirStrucPtr	ac,
SLong TransObj::LaunchWeapon(bool received,						//AMM 09Apr99
							AirStrucPtr	ac,					//AMM 09Apr99
							WeapAnimData*	weapon,
							SLong xpos, SLong ypos, SLong zpos,
							WorldStuff& worldptr,
							SLong		muzvel,
							SLong		muzdelay,
							Bool		unarmed)
{
	LnchrType	wptype = (LnchrType) (weapon->LauncherType & LT_MASK);
	SLong		itemweight = 0;
	ShapeNum	weaponshape = GunfireShape;
	ULong		failchance;
	SWord		amount = 1;

	if (weapon->stationshape)
	{
		ShapeDescPtr	sdptr = SHAPESTUFF.GetShapePtr(weapon->stationshape);
		weaponshape = (ShapeNum)sdptr->Type.shapenumber;
	}

//DeadCode RJS 27May98	failchance = weapon->SubDamage * Math_Lib.rnd();

	if (unarmed)												//RJS 27May98
	{
		switch (wptype)
		{
			case LT_BOMB:
			case LT_NAPALM:
			case LT_ROCKET:
				LaunchBombDrop(ac,weaponshape,xpos,ypos,zpos,worldptr,unarmed);
				break;
			case LT_FUEL:
				LaunchFuelDrop(ac,weaponshape,weapon,xpos,ypos,zpos,worldptr);
				break;
		}
	}
	else
	{
		switch (wptype)
		{
			case LT_BOMB:
				LaunchBombDrop(ac,weaponshape,xpos,ypos,zpos,worldptr);
				break;
			case LT_NAPALM:
				LaunchBombDrop(ac,weaponshape,xpos,ypos,zpos,worldptr);
				break;
			case LT_ROCKET:
				LaunchRocket(ac,weaponshape,xpos,ypos,zpos,worldptr);
				break;
			case LT_FUEL:
				LaunchFuelDrop(ac,weaponshape,weapon,xpos,ypos,zpos,worldptr);
				break;
			case LT_BULLET:
			{
				AircraftAnimData*	acadptr = (AircraftAnimData*) ac->Anim;

// dont want muzzle flash in playback or in comms if another player is firing

				if (!_Replay.Playback && (!(_DPlay.Implemented && ac->uniqueID.commsmove && ac!=Persons2::PlayerSeenAC)))					//RJS 17Jun99
					acadptr->shooting = TRUE;

				PlayGunSound((mobileitem* )ac,worldptr);
				TransientItem*	currbul;
				if (weapon->LauncherType > LT_BULLET)
				{
					currbul = LaunchOneGunBullet(ac,muzvel,weaponshape,xpos,ypos,zpos,worldptr,ANGLES_1_67Deg);//RJS 29Mar99
					LaunchGunPuff(ac,xpos,ypos,zpos,worldptr);
				}
				else
				{
					currbul = LaunchOneGunBullet(ac,muzvel,weaponshape,xpos,ypos,zpos,worldptr);//RJS 29Mar99
					if (	!_Miles.CockpitView					//RJS 07Jun99
						&& (Save_Data.desiredfps <= realFrameTime)//RJS 11Jun99
						&& (ac->shape == F51)	)
					{
						TransientItem*		newitem;
						newitem = LaunchUnguidedMissile(	ac,
															BULCSE,
															33,
															MOBILE_STATIONARY);
						if (newitem)
						{
							newitem->World.X = xpos;
							newitem->World.Y = ypos;
							newitem->World.Z = zpos;

							AddTransientItemToWorld(newitem,worldptr);
						}
					}
				}


//DeadCode AMM 09Apr99				if (!_Replay.Playback)						//RJS 08Apr99
				if (!received)									//AMM 09Apr99
				{
					MissileAnimData*	adptr = (MissileAnimData*) currbul->Anim;
					adptr->lastmissile = (ULong) ac->weap.currentbullet;
					adptr->novirtualguns = ac->classtype->noGuns;	//RJS 29Mar99
					if (adptr->lastmissile)
					{
						TransientItemPtr	tmpitm = (TransientItemPtr)adptr->lastmissile;
						if (tmpitm->isDeleted)// || tmpitm->Status.deadtime)				//RJS 03Jun99
							adptr->lastmissile = NULL;									//RJS 03Jun99
						else															//RJS 03Jun99
							tmpitm->isOwned = 1;										//RJS 03Jun99
					}
				}
				amount = ac->classtype->noGuns;					//RJS 20Apr99
				ac->weap.currentbullet = currbul;				//RJS 29Mar99
			}
			break;
//			case LT_CANNON:
//				PlayGunSound((mobileitem* )ac,worldptr);
//				LaunchOneGunBullet(ac,muzvel,weaponshape,xpos,ypos,zpos,worldptr,ANGLES_1_67Deg);//RJS 27Jul98
//				LaunchGunPuff(ac,xpos,ypos,zpos,worldptr);
//				break;
		}
	}

	if (weapon->LoadedStores)									//RJS 27May98
	{
		if (amount > weapon->LoadedStores)							//RJS 11Jun99
		{
			amount = 1;
			weapon->LoadedStores = 0;								//RJS 11Jun99
		}
		else														//RJS 11Jun99
			weapon->LoadedStores-=amount;							//RJS 11Jun99
	}

	return amount;													//RJS 11Jun99
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchTrailTail
//Author		Robert Slater
//Date			Mon 16 Jun 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void TransObj::LaunchTrailTail( mobileitem*	launcher,
								SLong		xpos,
								SLong		ypos,
								SLong		zpos,
								ShapeNum	globshape,
								WorldStuff&	world)
{
	TransientItem*	newitem;

	newitem = SimplifiedSpriteLaunch(	launcher,
										globshape,
										LIFETIME_SMOKE>>1,
										MOBILE_GANDF);
	if (newitem)
	{
//DeadCode RJS 19Feb98		ExplodeAnimData*	adptr = (ExplodeAnimData*) newitem->Anim;

		newitem->World.X = xpos;
		newitem->World.Y = ypos;
		newitem->World.Z = zpos;

//DeadCode RJS 19Feb98		adptr->frameno = 52;

		AddTransientItemToWorld(newitem,world);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchClouds
//Author		Robert Slater
//Date			Mon 16 Jun 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void TransObj::LaunchClouds()
{
//DeadCode RJS 28May99 	if (	(View_Point->World.Y > Land_Scape.cloud_base)
//DeadCode RJS 28May99 		&&	(CloudTotal < 20)
//DeadCode RJS 28May99 		&&	!Three_Dee.IsPaused()	)							//RJS 27Feb98
//DeadCode RJS 28May99 	{
//DeadCode RJS 28May99 		if (CloudTimer > 0)
//DeadCode RJS 28May99 			CloudTimer -= Timer_Code.FRAMETIME;
//DeadCode RJS 28May99 		else
//DeadCode RJS 28May99 		{
//DeadCode RJS 28May99 			SWord	rndheading, rndpitch;
//DeadCode RJS 28May99 			SLong	xpos, ypos, zpos;
//DeadCode RJS 28May99 			SLong	wx, wy, wz, ccount, noclouds;
//DeadCode RJS 28May99 			SWord	sin_ang,cos_ang,tan_ang;
//DeadCode RJS 28May99 
//DeadCode RJS 28May99 			rndheading = Math_Lib.rnd(ANGLES_60Deg) - (SWord)ANGLES_30Deg;
//DeadCode RJS 28May99 			rndpitch = Math_Lib.rnd(ANGLES_60Deg) - (SWord)ANGLES_30Deg;
//DeadCode RJS 28May99 
//DeadCode RJS 28May99 			rndheading += (SWord)View_Point->hdg;
//DeadCode RJS 28May99 			rndpitch += (SWord)View_Point->pitch;
//DeadCode RJS 28May99 
//DeadCode RJS 28May99 			Math_Lib.high_sin_cos((Angles) -rndheading,sin_ang,cos_ang);
//DeadCode RJS 28May99 
//DeadCode RJS 28May99 			// distance away is -65536
//DeadCode RJS 28May99 			xpos = (sin_ang << 16) >> (ANGLES_SHIFT-2);
//DeadCode RJS 28May99 			zpos = (cos_ang << 16) >> (ANGLES_SHIFT-2);
//DeadCode RJS 28May99 
//DeadCode RJS 28May99 			Math_Lib.high_sin_cos((Angles) -rndpitch,sin_ang,cos_ang);
//DeadCode RJS 28May99 
//DeadCode RJS 28May99 			ypos = (sin_ang << 16) >> (ANGLES_SHIFT-2);
//DeadCode RJS 28May99 
//DeadCode RJS 28May99 			wx = xpos + View_Point->World.X;
//DeadCode RJS 28May99 			wy = ypos + View_Point->World.Y;
//DeadCode RJS 28May99 			wz = zpos + View_Point->World.Z;
//DeadCode RJS 28May99 
//DeadCode RJS 28May99 			if (wy > (Land_Scape.cloud_base+2000))				//RJS 02Sep97
//DeadCode RJS 28May99 			{
//DeadCode RJS 28May99 				TransientItem*	newitem;
//DeadCode RJS 28May99 				WorldStuff*	world = mobileitem::currworld;
//DeadCode RJS 28May99 
//DeadCode RJS 28May99 				noclouds = Math_Lib.rnd() >> 13;
//DeadCode RJS 28May99 				for (ccount=0; ccount < noclouds; ccount++)
//DeadCode RJS 28May99 				{
//DeadCode RJS 28May99 					newitem = SimplifiedSpriteLaunch(	Manual_Pilot.ControlledAC2,
//DeadCode RJS 28May99 														CLOUD1,
//DeadCode RJS 28May99 														2000,	//RJS 02Sep97
//DeadCode RJS 28May99 														MOBILE_GANDF);
//DeadCode RJS 28May99 					if (newitem)
//DeadCode RJS 28May99 					{
//DeadCode RJS 28May99 						CloudTimer = 300;
//DeadCode RJS 28May99 						CloudTotal++;
//DeadCode RJS 28May99 
//DeadCode RJS 28May99 						newitem->World.X = wx + ((Math_Lib.rnd() - 32768)>>1);
//DeadCode RJS 28May99 						newitem->World.Y = wy + ((Math_Lib.rnd() - 32768)>>1);
//DeadCode RJS 28May99 						newitem->World.Z = wz + ((Math_Lib.rnd() - 32768)>>1);
//DeadCode RJS 28May99 
//DeadCode RJS 28May99 						AddTransientItemToWorld(newitem,*world);
//DeadCode RJS 28May99 					}
//DeadCode RJS 28May99 				}
//DeadCode RJS 28May99 			}
//DeadCode RJS 28May99 		}
//DeadCode RJS 28May99 	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchCloneGun
//Author		Robert Slater
//Date			Mon 22 Sep 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::LaunchCloneGun(	mobileitem* launcher,
									mobileitem* bulletlnchr,
									Nationality nat,
									SWord		noclones,
									SWord		weapindex,
									SWord		weapindex2,
									SWord		bulletdelay,
									SWord		lchtype,
									WorldStuff& worldptr)
{
	TransientItemPtr	newitem;
	newitem = LaunchUnguidedMissile(	bulletlnchr,
										CloneShape,
										bulletdelay,
										MOBILE_CLONEGUN );

	if (newitem)
	{
		CloneAnimData*	adptr = (CloneAnimData*) newitem->Anim;

		newitem->nationality = nat;
		newitem->TransRandom = noclones;
		newitem->vel = bulletlnchr->vel;
		newitem->Status.deadtime = bulletlnchr->Status.deadtime;//RJS 27May99

		adptr->weapindex = weapindex2;				//Swap indexes around,
		adptr->weapindex2 = weapindex;				//... so as to alternate fire
		adptr->originitm = (ULong) launcher;
		adptr->delay = bulletdelay;
		adptr->shapename = bulletlnchr->shape;
		adptr->lnchtype = lchtype;

		adptr->IsInvisible = 1;				//RJS 27Apr99

		AddTransientItemToWorld(newitem, worldptr);
	}
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchNapalmStrike
//Author		Robert Slater
//Date			Thu 22 Jan 1998
//
//Description	Number of secondary napalm spread shapes depends on velocity..
//				and travels in same direction
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::LaunchNapalmStrike(mobileitem* launcher,WorldStuff& worldptr)
{
	TransientItem*	newitem;
	int				dx, dz, thedist;
	SWord			hdg = launcher->hdg;
	SWord			sin_ang,cos_ang;
	int				i;
	SLong			wx, wz, noblobs;
	SWord			timedelay = 0;
	Bool			isInRange = FALSE;

	wx = launcher->World.X;
	wz = launcher->World.Z;

	thedist = 750;
	
	Math_Lib.high_sin_cos((Angles)hdg,sin_ang,cos_ang);

	dx = (sin_ang * thedist) >> 15;
	dz = (cos_ang * thedist) >> 15;

	if (WithinVisibleRange(launcher->World,400000))				//RJS 30Apr99
	{
		newitem = SimplifiedSpriteLaunch((mobileitem*)launcher,EXPLO,20,MOBILE_STATIONARY);
		if (newitem)
		{
			newitem->DrawOffset = 100;
			AddTransientItemToWorld(newitem,worldptr);
		}

		isInRange = TRUE;
	}

	noblobs = 1 + (launcher->velhori/160);
	SWord	thetime;

	ItemPtr	realLauncher;
	if (launcher->Status.size == TRANSIENTSIZE)								//RJS 05May99
		realLauncher = ((TransientItemPtr)launcher)->Launcher;			//RJS 05May99
	else
		realLauncher = launcher;

	if (noblobs > 8)
		noblobs = 8;

	SLong	activecnt = 0;										//RJS 13May99
	if (Save_Data.desiredfps > realFrameTime)					//RJS 28May99
		noblobs = 1;											//RJS 28May99

	for (i=0; i < noblobs; i++)									//RJS 09Feb98
	{															//RJS 09Feb98
		thetime = 250 - timedelay;
		if (thetime > 0)
		{
			newitem = SimplifiedSpriteLaunch(	launcher,			//RJS 09Feb98
												EMPTY,				//RJS 09Feb98
												timedelay,			//RJS 09Feb98
												MOBILE_NAPALM);		//RJS 09Feb98
			if (newitem)											//RJS 09Feb98
			{														//RJS 09Feb98
				if (!isInRange)
				{
					MinAnimData* mad = (MinAnimData*) newitem->Anim;
					mad->IsInvisible = 1;
				}
				if (i==0)										//RJS 11May99
					newitem->Target = realLauncher;				//RJS 11May99

				activecnt--;									//RJS 13May99
				if (activecnt <= 0)								//RJS 13May99
					activecnt = 2;								//RJS 13May99
				else											//RJS 13May99
					newitem->Status.deadtime = 1;				//RJS 13May99

				newitem->Launcher = realLauncher;					//RJS 05May99
				newitem->pitch = (Angles) thetime;
				newitem->hdg = launcher->hdg;
				newitem->World.X = wx;
				newitem->World.Z = wz;
				newitem->TransRandom = thetime;						//RJS 03Dec98
				AddTransientItemToWorld(newitem,worldptr);			//RJS 09Feb98
			}														//RJS 09Feb98

			wx += dx;
			wz += dz;
			timedelay += 20;
		}
		else
			break;
	}

	LaunchFingersFire(launcher,worldptr);

	if (Save_Data.desiredfps <= realFrameTime)					//RJS 11Jun99
	{
		if (WithinVisibleRange(launcher->World,100000))				//RJS 30Apr99
		{
			int				count;
			for (count = 0; count < 8; count++)							//DAW 01Sep98
			{
				newitem = SimplifiedSpriteLaunch(launcher,SPARK,250,MOBILE_GANDF);//RJS 28May99
				if (newitem)
				{
					SLong	vely = 150 + Math_Lib.rnd(150);

					newitem->hdg = (Angles) Math_Lib.rnd();			//RJS 06Aug96
					newitem->vely = vely;							//RJS 26Nov98
					newitem->velhori = 300 - vely;					//RJS 26Nov98

					AddTransientItemToWorld(newitem,worldptr);
				}
			}
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchCanopyEject
//Author		Robert Slater
//Date			Thu 19 Feb 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::LaunchCanopyEject(mobileitem* launcher,WorldStuff& worldptr)
{
	AirStrucPtr	ac=*launcher;
	if (ac->weap.Ejected==FALSE)
	{
		AircraftAnimData	*adptr = (AircraftAnimData*)launcher->Anim;
		if (adptr->PILOTLEFT != BS_DEAD)								//RJS 05May99
		{
			SLong				OpenChance = adptr->CANOPY1 - BS_DAMLV2;

			OpenChance = (OpenChance * Math_Lib.rnd()) >> 16;
			if (OpenChance < 32)
			{
				ac->weap.Ejected=TRUE;

				TransientItem*	newitem;

				_Miles.PlayOnce(FIL_SFX_CANOPY_BLOW, launcher);

				newitem=LaunchUnguidedMissile(launcher,launcher->shape,75,MOBILE_CANOPY);
				if (newitem)
				{
					AircraftAnimData*	adptr2 = (AircraftAnimData*) newitem->Anim;
					UByte				oldstate = adptr->CANOPY1;
		//DeadCode RJS 21Apr99			UByteP				flagptr;
					SLong				flagend;
					int					index;							//RJS 21Apr99
					ShapeDescPtr		sdptr = SHAPESTUFF.GetShapePtr(launcher->shape);

					adptr2->itemstate = DEAD;								

					//Set 3D to only draw the dead part
		//DeadCode RJS 21Apr99			flagptr = (UByteP) newitem->Anim;
					flagend = SHAPE.GetAnimDataSize(launcher->shape);
					index = sdptr->DamageOffset;

					while (index < flagend)
						newitem->Anim[index++] = BS_DEAD;				//RJS 21Apr99

					adptr2->CANOPY1 = oldstate;

					newitem->TransRandom = 1;

					AddTransientItemToWorld(newitem, worldptr);

					if (launcher == Manual_Pilot.ControlledAC2)						//RJS 21May98
					{																//RJS 21May98
						if (View_Object)											//RJS 21May98
							View_Object->SetToParachuteView(NULL);				//RJS 06Jun99
					}
				}

				adptr->CANOPY1 = BS_DEAD;
			}
			else
			{
				if (ac->nationality == Manual_Pilot.ControlledAC2->nationality)//RJS 17Mar99
				{
					AirStruc*	buddy = ac->FindABuddyWithPlayerGivenPriority(); //RDH 11/05/99
					if (buddy)											//RDH 11/05/99
						_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_EJECTREPLYSTUCK,MSG_EJECTREPLY, launcher, launcher, buddy)); //RDH 11/05/99
				}
			}
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchGroupThug
//Author		Robert Slater
//Date			Mon 2 Mar 1998
//
//Description	Bashes up-to two items in a group
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::LaunchGroupThug(	item*		launcher,
									ShapeNum	theshape,
									int			prevgroupno,
									int			prevdep,
									int			nextdep,
									Coords3D	posPrev,
									Coords3D	posNext,
									UWord		panimoff,
									UWord		nanimoff,	
									ItemPtr		theShooter	)	//RJS 05Jul99
{
	TransientItem*	newitem;
	SLong			thetime,t1, t2;
	UByte			disable1, disable2;
	WorldStuff*	worldptr = mobileitem::currworld;
	SLong			tph,tnh;


	prevdep *= 3000;
	prevdep /= 127;

	nextdep *= 3000;
	nextdep /= 127;

	if (prevdep < 0)
	{
		t1 = -prevdep;
		disable1 = 1;
	}
	else
	{
		disable1 = 0;
		t1 = prevdep;
	}

	if (nextdep < 0)
	{
		disable2 = 1;
		t2 = -nextdep;
	}
	else
	{
		t2 = nextdep;
		disable2 = 0;
	}

	// Vary the times a bit...
	tph = t1>>2;
	tnh = t2>>2;
	t1 = ((3*t1)>>2) + Math_Lib.rnd(tph);
	t2 = ((3*t2)>>2) + Math_Lib.rnd(tnh);

	if (t1 > t2)
		thetime = t1;
	else
		thetime = t2;

	newitem = SimplifiedSpriteLaunch(	launcher,	
										theshape,		
										thetime,	
										MOBILE_THUG);
	
	if (newitem)
	{
		ThugAnimData	*adptr = (ThugAnimData*) newitem->Anim;

		if (adptr)
		{
			adptr->prevcount = t1;
			adptr->nextcount = t2;
			adptr->disableprev = disable1;
			adptr->disablenext = disable2;
			adptr->pXPos = posPrev.X;
			adptr->pYPos = posPrev.Y;
			adptr->pZPos = posPrev.Z;
			adptr->nXPos = posNext.X;
			adptr->nYPos = posNext.Y;
			adptr->nZPos = posNext.Z;
			adptr->panimoff = panimoff;
			adptr->nanimoff = nanimoff;
		}

		newitem->Launcher = theShooter;		//RJS 05Jul99
		newitem->Target = launcher;			//RJS 05Jul99

		AddTransientItemToWorld(newitem,*worldptr);
	}
}

////////////////////////////////////////////////////////////////////////////////
//
//					Common launch code for transients
//
////////////////////////////////////////////////////////////////////////////////

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SimplifiedSpriteLaunch
//Author		Paul.
//Date			Fri 26 Apr 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
TransientItemPtr
TransObj::SimplifiedSpriteLaunch(	Item* launcher,
									ShapeNum shape,
									SLong lifetime,
									AutoMoveCodeTypeSelect movecode)
{
	if (!launcher)
		INT3;

	TransientItemPtr newitem = new TransientItem;

	if (newitem)
	{
		transientcounter++;										//PD 24Jul96
		newitem->DrawOffset = 0;								//RJS 27Nov98
		newitem->Target = NULL;									//RJS 18Feb98
		newitem->Launcher = launcher;
		newitem->nexttogo = NULL;
		newitem->nextmobile = NULL;
		newitem->nexttrans = NULL;
		newitem->waypoint = NULL;

		newitem->hdg =
			newitem->pitch =
			newitem->roll	= ANGLES_0Deg;

		newitem->Next = NULL;

		newitem->World = launcher->World;

		newitem->velx =
			newitem->vely =
			newitem->velz =
			newitem->velhori = 0;

//DeadCode PD 08Oct96		newitem->collisiontime = 0;								//PD 10Sep96

		newitem->shape = shape;

		if (shape<1 || shape>EMPTY)
			_Error.EmitSysErr("Sprite launch (%d)",shape);

		newitem->LaunchTime = lifetime;

		newitem->movecode = movecode;
		newitem->TransRandom = 0;
		newitem->isOwned = 0;									//RJS 29Mar99
		newitem->TimeOfLaunch = View_Object->TimeOfDay();		//RJS 19May99

		(void )SHAPE.SetAnimData(newitem,0);					//RDH 23Sep96

		newitem->TransientItem::AddToList();
	}
	return (newitem);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		RelativeSpriteLaunch
//Author		Robert Slater
//Date			Fri 27 Nov 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
TransientItemPtr
TransObj::RelativeSpriteLaunch(	Item* launcher,
								ShapeNum parentshape,
								ShapeNum shape,
								SLong lifetime,
								AutoMoveCodeTypeSelect movecode)
{
	TransientItemPtr newitem = new TransientItem;

	if (newitem)
	{
		transientcounter++;								

		ShapeDescPtr	sdptr = (ShapeDescPtr) SHAPESTUFF.GetShapePtr(parentshape);
		
		newitem->DrawOffset = sdptr->Size<<2;		//make it a quarter size...
		newitem->Launcher = launcher;
		newitem->nexttogo = NULL;
		newitem->nextmobile = NULL;
		newitem->nexttrans = NULL;
		newitem->waypoint = NULL;

		if ((launcher->Status.size >= MovingSize) && (launcher->Status.size != TRANSIENTSIZE))
			newitem->Target = launcher;									
		else
			newitem->Target = NULL;									

		newitem->hdg =
			newitem->pitch =
			newitem->roll	= ANGLES_0Deg;

		newitem->Next = NULL;

		newitem->World = launcher->World;

		newitem->velx =
			newitem->vely =
			newitem->velz =
			newitem->velhori = 0;

		newitem->shape = shape;

		newitem->LaunchTime = lifetime;

		newitem->movecode = movecode;
		newitem->TransRandom = 0;
		newitem->isOwned = 0;									//RJS 29Mar99
		newitem->TimeOfLaunch = View_Object->TimeOfDay();		//RJS 19May99

		(void )SHAPE.SetAnimData(newitem,0);

		newitem->TransientItem::AddToList();
	}
	return (newitem);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchUnguidedMissile
//Author		Paul.
//Date			Fri 26 Apr 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
TransientItemPtr
TransObj::LaunchUnguidedMissile(	mobileitem* launcher,
									ShapeNum shape,
									SLong lifetime,
									AutoMoveCodeTypeSelect	movecode,
									Bool	inheritanimdata	)
{
	TransientItemPtr newitem = new TransientItem;

	if (newitem)
	{
		transientcounter++;
		newitem->DrawOffset = 0;								//RJS 27Nov98
		newitem->Target = NULL;									//RJS 18Feb98
		newitem->Launcher = launcher;
		newitem->nexttogo = NULL;
		newitem->nextmobile = NULL;
		newitem->nexttrans = NULL;
		newitem->waypoint = NULL;

		if (launcher->Status.size >= RotatedSize)
		{
			newitem->hdg = launcher->hdg;
			newitem->pitch = launcher->pitch;
			newitem->roll = launcher->roll;
		}
		else
		{
			newitem->hdg = ANGLES_0Deg;
			newitem->pitch = ANGLES_0Deg;
			newitem->roll = ANGLES_0Deg;
		}

		newitem->Next = NULL;

		newitem->World = launcher->World;

		if (launcher->Status.size >= MobileSize)
		{
			newitem->velx = launcher->velx;
			newitem->vely = launcher->vely;
			newitem->velz = launcher->velz;
			newitem->velhori = launcher->velhori;
		}
		else
		{
			newitem->velx = 0;
			newitem->vely = 0;
			newitem->velz = 0;
			newitem->velhori = 0;
		}

//DeadCode PD 08Oct96		newitem->collisiontime = 0;								//PD 10Sep96

		newitem->shape = shape;

		newitem->LaunchTime = lifetime;

		newitem->movecode = movecode;
		newitem->TransRandom = 0;
		newitem->isOwned = 0;									//RJS 29Mar99
		newitem->TimeOfLaunch = View_Object->TimeOfDay();		//RJS 19May99

		if (inheritanimdata == FALSE)
			SHAPE.SetAnimData(newitem,0);						//RJS 13Jul98
		else													//RJS 13Jul98
		{														//RJS 13Jul98
			animptr	srcanim = launcher->Anim;					//RJS 21Apr99
			newitem->Anim = launcher->Anim;						//RJS 21Apr99
			newitem->Anim = SHAPE.CopyAnimData(srcanim,shape);	//RJS 21Apr99
		}

		newitem->TransientItem::AddToList();
	}
	return (newitem);
}
///////////////////////////////////////////////////////////////////
//
// This version adds to world as well...
//
//
//
//
TransientItemPtr
TransObj::LaunchUnguidedMissile(	item* launcher,
									ShapeNum shape,
									SLong lifetime,
									AutoMoveCodeTypeSelect	movecode,
									Coords3D	&xyz,
									ANGLES		hdg,
									ANGLES		pitch,
									SWord		velx,
									SWord		vely,
									SWord		velz,
									SWord		velh,
									SWord		vel,
									Nationality nat
									)
{
	TransientItemPtr newitem = new TransientItem;

	if (newitem)
	{
		transientcounter++;
		newitem->DrawOffset = 0;								//RJS 27Nov98
		newitem->Target = NULL;									//RJS 18Feb98
		newitem->nationality = nat;
		newitem->Launcher = launcher;
		newitem->nexttogo = NULL;
		newitem->nextmobile = NULL;
		newitem->nexttrans = NULL;
		newitem->waypoint = NULL;

		newitem->hdg = hdg;
		newitem->pitch = pitch;
		newitem->roll = ANGLES_0Deg;

		newitem->Next = NULL;

		newitem->World = xyz;

		newitem->velx = velx;
		newitem->vely = vely;
		newitem->velz = velz;

		newitem->velhori = velh;
		newitem->vel = vel;

//DeadCode PD 08Oct96		newitem->collisiontime = 0;								//PD 10Sep96

		newitem->shape = shape;

		newitem->LaunchTime = lifetime;

		newitem->movecode = movecode;
		newitem->TransRandom = 0;
		newitem->isOwned = 0;									//RJS 29Mar99
		newitem->TimeOfLaunch = View_Object->TimeOfDay();		//RJS 19May99

		(void )SHAPE.SetAnimData(newitem);
		if (movecode == MOBILE_PUFFTRAVEL)						//RJS 30Apr99
		{														//RJS 30Apr99
			MinAnimData*	mad = (MinAnimData*)newitem->Anim;	//RJS 30Apr99
			mad->IsInvisible = 1;								//RJS 30Apr99
		}														//RJS 30Apr99

		newitem->TransientItem::AddToList();

		AddTransientItemToWorld(newitem, *newitem->currworld);				//JIM 25Sep96
	}
	return (newitem);
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchGuidedMissile
//Author		Paul.
//Date			Fri 26 Apr 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
TransientItemPtr
TransObj::LaunchGuidedMissile(	mobileitem* launcher,
								itemptr		target,
								ShapeNum	shape,
								SLong		lifetime,
								AutoMoveCodeTypeSelect	movecode)
{
	TransientItemPtr newitem = new TransientItem;

	if (newitem)
	{
		transientcounter++;										//PD 24Jul96
		newitem->DrawOffset = 0;								//RJS 27Nov98
		newitem->Launcher = launcher;
		newitem->Target = target;

		newitem->nexttogo = NULL;
		newitem->nextmobile = NULL;
		newitem->nexttrans = NULL;
		newitem->waypoint = NULL;

		newitem->hdg = launcher->hdg;
		newitem->pitch = launcher->pitch;
		newitem->roll = launcher->roll;

		newitem->Next = NULL;

		newitem->World = launcher->World;

		newitem->velx = launcher->velx;
		newitem->vely = launcher->vely;
		newitem->velz = launcher->velz;

		newitem->velhori = launcher->velhori;

//DeadCode PD 08Oct96		newitem->collisiontime = 0;								//PD 10Sep96

		newitem->shape = shape;

		newitem->LaunchTime = lifetime;

		newitem->movecode = movecode;
		newitem->TransRandom = 0;
		newitem->isOwned = 0;									//RJS 29Mar99
		newitem->TimeOfLaunch = View_Object->TimeOfDay();		//RJS 19May99

		(void )SHAPE.SetAnimData(newitem,0);					//RDH 23Sep96

		newitem->TransientItem::AddToList();
	}
	return (newitem);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchSuperLauncher
//Author		Robert Slater
//Date			Mon 22 Sep 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
TransientItemPtr
TransObj::LaunchSuperLauncher(	item*		launcher,
								ShapeNum	weapshape,
								SLong		lifetime,
								AutoMoveCodeTypeSelect	movecode,
								Coords3D	&xyz,
								ANGLES		hdg,				//PD 13Nov97
								ANGLES		pitch,				//PD 13Nov97
								SWord		velx,
								SWord		vely,
								SWord		velz,
								SWord		velh,
								SWord		vel,
								Nationality nat,
								SWord		weapindex,
								SWord		weapindex2,
								SWord		bulletdelay,
								SWord		noclones,
								SWord		lchtype,
								WorldStuff	&worldptr,
								Bool		isArmed	)			//RJS 27May99
{
	TransientItemPtr	newitem = new TransientItem;
	if (newitem)
	{
		transientcounter++;
		newitem->DrawOffset = 0;								//RJS 27Nov98
		newitem->Target = NULL;									//RJS 18Feb98
		newitem->nationality = nat;
		newitem->Launcher = launcher;
		newitem->nexttogo = NULL;
		newitem->nextmobile = NULL;
		newitem->nexttrans = NULL;
		newitem->waypoint = NULL;

		newitem->hdg = hdg;
		newitem->pitch = pitch;
		newitem->roll = ANGLES_0Deg;

		newitem->Next = NULL;
		newitem->World = xyz;

		newitem->velx = velx;
		newitem->vely = vely;
		newitem->velz = velz;

		newitem->velhori = velh;
		newitem->vel = vel;

		newitem->shape = weapshape;
		newitem->LaunchTime = lifetime;
		newitem->movecode = movecode;
		newitem->TransRandom = 0;
		newitem->isOwned = 0;								//RJS 29Mar99
		newitem->TimeOfLaunch = View_Object->TimeOfDay();		//RJS 19May99

		(void )SHAPE.SetAnimData(newitem);

		newitem->TransientItem::AddToList();

		AddTransientItemToWorld(newitem, worldptr);

		bool	isAC = false;									//RJS 16Jun99
		if (newitem->Launcher->Status.size == AIRSTRUCSIZE)		//RJS 29Mar99
		{
			MissileAnimData*	adptr = (MissileAnimData*) newitem->Anim;

			adptr->lastmissile = (ULong) ((AirStrucPtr)newitem->Launcher)->weap.currentbullet;
			adptr->novirtualguns = ((AirStrucPtr)newitem->Launcher)->classtype->noGuns;//RJS 29Mar99
			if (adptr->lastmissile)
			{
				TransientItemPtr	tmpitm = (TransientItemPtr)adptr->lastmissile;
				if (tmpitm->isDeleted)// || tmpitm->Status.deadtime)				//RJS 03Jun99
					adptr->lastmissile = NULL;									//RJS 03Jun99
				else															//RJS 03Jun99
					tmpitm->isOwned = 1;										//RJS 03Jun99
			}

			((AirStrucPtr)newitem->Launcher)->weap.currentbullet = newitem;

			isAC = true;										//RJS 16Jun99
		}

		if (!isArmed)											//RJS 27May99
			newitem->Status.deadtime = 1;						//RJS 27May99
		
		newitem->isArmed = 1;								//RJS 09Jul99	

		if (noclones)
			LaunchCloneGun((mobileitem*)launcher,newitem,nat,noclones,weapindex,weapindex2,bulletdelay,lchtype,worldptr);//RJS 21Jul98
		else
		{
			if (isAC)											//RJS 16Jun99
			{
				ShapeDescPtr	sdptr = SHAPESTUFF.GetShapePtr(launcher->shape);
				if (sdptr->AnimDataSize == AIRCRAFTANIM)
				{
					AircraftAnimData*	ladptr= (AircraftAnimData*) launcher->Anim;//RJS 16Jun99
					ladptr->shooting = 0;
				}
			}
		}
	}
	return (newitem);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GeneralItemDamage
//Author		Robert Slater
//Date			Wed 24 Jul 1996
//
//Description	Launches relevant death animation for a shape
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::GeneralItemDamage(mobileitem* launcher,
									mobileitem*	missile,
									WorldStuff&	worldptr,
									SByte	groupindex,
									Bool	accollision)
{
//DeadCode RJS 20Nov98	DeathNum		deadtype;
//DeadCode RJS 20Nov98	UWord			randdam;
//DeadCode RJS 20Nov98	UByte			vulnerability;
//DeadCode RJS 20Nov98	UByte			missilepower = 1;
//DeadCode RJS 20Nov98	ULong			destruction;
//DeadCode RJS 20Nov98	ShapeNum		shapehit;									//RJS 14Oct96
//DeadCode RJS 20Nov98	MyGroundVector		hitvector;									//RJS 21Nov96
//DeadCode RJS 20Nov98	ShapeDescPtr	sdptr;
//DeadCode RJS 20Nov98
//DeadCode RJS 20Nov98	MinAnimData* mad =
//DeadCode RJS 20Nov98				(MinAnimData* )launcher->Anim;	//RJS 01Aug96
//DeadCode RJS 20Nov98
//DeadCode RJS 20Nov98	mad = (MinAnimData* ) SHAPE.GetGroupItemAnim(launcher,shapehit,groupindex,&hitvector);//RJS 21Nov96
//DeadCode RJS 20Nov98	BalloonAnimData*	banim = (BalloonAnimData*) launcher->Anim;//RDH 17Dec96
//DeadCode RJS 20Nov98
//DeadCode RJS 20Nov98	if (!accollision)
//DeadCode RJS 20Nov98	{
//DeadCode RJS 20Nov98		randdam = Math_Lib.rnd();								//RJS 16Oct96
//DeadCode RJS 20Nov98		missilepower = SHAPESTUFF.GetShapeStrength(missile->shape);
//DeadCode RJS 20Nov98		vulnerability = SHAPESTUFF.GetShapeStrength(shapehit);	//RJS 14Oct96
//DeadCode RJS 20Nov98
//DeadCode RJS 20Nov98		if ( (mad->itemstate != ALIVE) || (vulnerability == 0) )//RJS 10Dec96
//DeadCode RJS 20Nov98			destruction = 5000;
//DeadCode RJS 20Nov98		else
//DeadCode RJS 20Nov98		{
//DeadCode RJS 20Nov98			destruction = vulnerability * randdam;				//RJS 16Oct96
//DeadCode RJS 20Nov98			destruction >>= 14;									//RJS 10Dec96
//DeadCode RJS 20Nov98		}
//DeadCode RJS 20Nov98	}
//DeadCode RJS 20Nov98	else
//DeadCode RJS 20Nov98		destruction = 0;
//DeadCode RJS 20Nov98
//DeadCode RJS 20Nov98	if (destruction < missilepower)								//RJS 16Oct96
//DeadCode RJS 20Nov98	{
//DeadCode RJS 20Nov98		if (groupindex > -1)
//DeadCode RJS 20Nov98		{
//DeadCode RJS 20Nov98			missile->World.X = hitvector.gx;						//RJS 21Nov96
//DeadCode RJS 20Nov98			missile->World.Y = hitvector.gy;						//RJS 21Nov96
//DeadCode RJS 20Nov98			missile->World.Z = hitvector.gz;						//RJS 21Nov96
//DeadCode RJS 20Nov98		}
//DeadCode RJS 20Nov98
//DeadCode RJS 20Nov98		sdptr = SHAPESTUFF.GetShapePtr(shapehit);
//DeadCode RJS 20Nov98		deadtype = (DeathNum) sdptr->DeathType;
//DeadCode RJS 20Nov98
//DeadCode RJS 20Nov98 //DeadCode RJS 27Feb97		switch (deadtype)
//DeadCode RJS 20Nov98 //DeadCode RJS 27Feb97		{
//DeadCode RJS 20Nov98 //DeadCode RJS 27Feb97			case DEFAULT:
//DeadCode RJS 20Nov98 //DeadCode RJS 27Feb97				LaunchScatteredFire(missile,shapehit,worldptr);	//RJS 06Dec96
//DeadCode RJS 20Nov98 //DeadCode RJS 27Feb97				break;
//DeadCode RJS 20Nov98 //DeadCode RJS 27Feb97			case BIGEXPLOSION:
//DeadCode RJS 20Nov98 //DeadCode RJS 27Feb97				_Miles.PlaySample((FileNum) (FIL_SFX_EXPLOSION_GROUND+Math_Lib.rnd(5)), (ItemBasePtr) launcher);//RJS 05Dec96
//DeadCode RJS 20Nov98 //DeadCode RJS 27Feb97				LaunchExplosion(missile,worldptr);
//DeadCode RJS 20Nov98 //DeadCode RJS 27Feb97				break;
//DeadCode RJS 20Nov98 //DeadCode RJS 27Feb97			case SMALLEXPLOSION:
//DeadCode RJS 20Nov98 //DeadCode RJS 27Feb97				LaunchMiniExplosion(missile,worldptr);
//DeadCode RJS 20Nov98 //DeadCode RJS 27Feb97				break;
//DeadCode RJS 20Nov98 //DeadCode RJS 27Feb97			case GROUNDDEBRIS:
//DeadCode RJS 20Nov98 //DeadCode RJS 27Feb97				LaunchGroundDebris(missile,worldptr);
//DeadCode RJS 20Nov98 //DeadCode RJS 27Feb97				break;
//DeadCode RJS 20Nov98 //DeadCode RJS 27Feb97			case SMALLDEBRIS:
//DeadCode RJS 20Nov98 //DeadCode RJS 27Feb97			case SMALLSPARK:
//DeadCode RJS 20Nov98 //DeadCode RJS 27Feb97				LaunchSpark(missile,worldptr);
//DeadCode RJS 20Nov98 //DeadCode RJS 27Feb97				break;
//DeadCode RJS 20Nov98 //DeadCode RJS 27Feb97			case GROUNDRICOCHET:
//DeadCode RJS 20Nov98 //DeadCode RJS 27Feb97				LaunchRicochet(missile,worldptr);
//DeadCode RJS 20Nov98 //DeadCode RJS 27Feb97				break;
//DeadCode RJS 20Nov98 //DeadCode RJS 27Feb97			case SMALLFIRE:
//DeadCode RJS 20Nov98 //DeadCode RJS 27Feb97 //DeadCode RJS 09Dec96				LaunchFire(launcher,worldptr);					//RJS 16Oct96
//DeadCode RJS 20Nov98 //DeadCode RJS 27Feb97				LaunchScatteredFire(missile,shapehit,worldptr);	//RJS 09Dec96
//DeadCode RJS 20Nov98 //DeadCode RJS 27Feb97				_Miles.PlaySample(FIL_SFX_WOOD_BREAK1, (ItemBasePtr) missile);//RJS 09Dec96
//DeadCode RJS 20Nov98 //DeadCode RJS 27Feb97				break;
//DeadCode RJS 20Nov98 //DeadCode RJS 27Feb97			case BIGFIRE:
//DeadCode RJS 20Nov98 //DeadCode RJS 27Feb97				LaunchGroundExplosion(missile,worldptr);		//RJS 09Oct96
//DeadCode RJS 20Nov98 //DeadCode RJS 27Feb97				break;
//DeadCode RJS 20Nov98 //DeadCode RJS 27Feb97			case ATEAM:
//DeadCode RJS 20Nov98 //DeadCode RJS 27Feb97				LaunchDelayedExplosion(launcher,worldptr);
//DeadCode RJS 20Nov98 //DeadCode RJS 27Feb97				break;
//DeadCode RJS 20Nov98 //DeadCode RJS 27Feb97			case BURSTBALLOON:
//DeadCode RJS 20Nov98 //DeadCode RJS 27Feb97				banim->groundheight = Land_Scape.GetGroundLevel((itemptr)launcher);//RDH 17Dec96
//DeadCode RJS 20Nov98 //DeadCode RJS 27Feb97				_Miles.PlaySample(FIL_SFX_EXPLOSION_BALLOON, (ItemBasePtr) launcher);//RJS 22Nov96
//DeadCode RJS 20Nov98 //DeadCode RJS 27Feb97				LaunchBigExplosion(launcher,worldptr);
//DeadCode RJS 20Nov98 //DeadCode RJS 27Feb97				LaunchMovingSmoke(launcher,worldptr);
//DeadCode RJS 20Nov98 //DeadCode RJS 27Feb97				break;
//DeadCode RJS 20Nov98 //DeadCode RJS 27Feb97 //DeadCode RJS 02Dec96			case ZEPPELINDEATH:
//DeadCode RJS 20Nov98 //DeadCode RJS 27Feb97 //DeadCode RJS 02Dec96				_Miles.PlaySample(FIL_SFX_EXPLOSION_BALLOON, (ItemBasePtr) launcher);//RJS 22Nov96
//DeadCode RJS 20Nov98 //DeadCode RJS 27Feb97 //DeadCode RJS 02Dec96				LaunchBigExplosion(launcher,worldptr);
//DeadCode RJS 20Nov98 //DeadCode RJS 27Feb97 //DeadCode RJS 02Dec96				LaunchMovingSmoke(launcher,worldptr);
//DeadCode RJS 20Nov98 //DeadCode RJS 27Feb97 //DeadCode RJS 02Dec96				break;
//DeadCode RJS 20Nov98 //DeadCode RJS 27Feb97			case CHATEAUDEATH:
//DeadCode RJS 20Nov98 //DeadCode RJS 27Feb97 //DeadCode RJS 20Nov96				LaunchGroundExplosion(missile,worldptr);
//DeadCode RJS 20Nov98 //DeadCode RJS 27Feb97 //DeadCode RJS 20Nov96				launcher->shape = CHTAU3;						//RJS 30Oct96
//DeadCode RJS 20Nov98 //DeadCode RJS 27Feb97				break;
//DeadCode RJS 20Nov98 //DeadCode RJS 27Feb97			case SMALLCOLLAPSE:									//RJS 17Oct96
//DeadCode RJS 20Nov98 //DeadCode RJS 27Feb97				LaunchDustRing(missile,worldptr);				//RJS 17Oct96
//DeadCode RJS 20Nov98 //DeadCode RJS 27Feb97				LaunchTroops(launcher,missile->World.X,missile->World.Y,missile->World.Z,worldptr,Math_Lib.rnd(3));//RJS 07Nov96
//DeadCode RJS 20Nov98 //DeadCode RJS 27Feb97				break;
//DeadCode RJS 20Nov98 //DeadCode RJS 27Feb97			case BIGCOLLAPSE:									//RJS 17Oct96
//DeadCode RJS 20Nov98 //DeadCode RJS 27Feb97				_Miles.PlaySample(FIL_SFX_DEBRIS_COLLAPSE, (ItemBasePtr) missile);//RJS 22Nov96
//DeadCode RJS 20Nov98 //DeadCode RJS 27Feb97				LaunchDustRing(missile,worldptr);				//RJS 17Oct96
//DeadCode RJS 20Nov98 //DeadCode RJS 27Feb97				LaunchMushroomCloud(missile,worldptr);			//RJS 07Nov96
//DeadCode RJS 20Nov98 //DeadCode RJS 27Feb97				LaunchTroops(launcher,missile->World.X,missile->World.Y,missile->World.Z,worldptr,Math_Lib.rnd(4));//RJS 07Nov96
//DeadCode RJS 20Nov98 //DeadCode RJS 27Feb97				break;											//RJS 17Oct96
//DeadCode RJS 20Nov98 //DeadCode RJS 27Feb97			case AMMOBOXES:										//RJS 17Oct96
//DeadCode RJS 20Nov98 //DeadCode RJS 27Feb97				LaunchAmmoBoxes(missile,launcher,groupindex,worldptr);//RJS 07Nov96
//DeadCode RJS 20Nov98 //DeadCode RJS 27Feb97				break;											//RJS 17Oct96
//DeadCode RJS 20Nov98 //DeadCode RJS 27Feb97			case FUELBARRELS:									//RJS 17Oct96
//DeadCode RJS 20Nov98 //DeadCode RJS 27Feb97				LaunchGroundExplosion(missile,worldptr);		//RJS 22Nov96
//DeadCode RJS 20Nov98 //DeadCode RJS 27Feb97				LaunchFuelBarrels(missile,worldptr);			//RJS 22Nov96
//DeadCode RJS 20Nov98 //DeadCode RJS 27Feb97				break;											//RJS 17Oct96
//DeadCode RJS 20Nov98 //DeadCode RJS 27Feb97			case CHICKENS:										//RJS 17Oct96
//DeadCode RJS 20Nov98 //DeadCode RJS 27Feb97				_Miles.PlayOnce(FIL_SFX_HEN_SCUFFLE, (ItemBasePtr) missile);//RJS 22Nov96
//DeadCode RJS 20Nov98 //DeadCode RJS 27Feb97				LaunchBirds(missile,ChickenShape,worldptr);		//RJS 17Oct96
//DeadCode RJS 20Nov98 //DeadCode RJS 27Feb97				break;
//DeadCode RJS 20Nov98 //DeadCode RJS 27Feb97			case TANKDEATH:										
//DeadCode RJS 20Nov98 //DeadCode RJS 27Feb97				if (missile->shape == BOMB)
//DeadCode RJS 20Nov98 //DeadCode RJS 27Feb97				{
//DeadCode RJS 20Nov98 //DeadCode RJS 27Feb97					_Miles.PlaySample((FileNum) (FIL_SFX_EXPLOSION_DISTANT1+Math_Lib.rnd(2)), (ItemBasePtr) missile);//RJS 22Nov96
//DeadCode RJS 20Nov98 //DeadCode RJS 27Feb97					LaunchSmoulder(missile,worldptr);
//DeadCode RJS 20Nov98 //DeadCode RJS 27Feb97					_Miles.StopSample(FIL_SFX_TANK_LOOP1,launcher);//RJS 20Nov96
//DeadCode RJS 20Nov98 //DeadCode RJS 27Feb97				}
//DeadCode RJS 20Nov98 //DeadCode RJS 27Feb97				break;											
//DeadCode RJS 20Nov98 //DeadCode RJS 27Feb97			case BRIDGEDEATH:									
//DeadCode RJS 20Nov98 //DeadCode RJS 27Feb97				_Miles.PlayOnce(FIL_SFX_DEBRIS_WATER, (ItemBasePtr) missile);//RJS 22Nov96
//DeadCode RJS 20Nov98 //DeadCode RJS 27Feb97				break;
//DeadCode RJS 20Nov98 //DeadCode RJS 27Feb97			case TRAINDEATH:									//RJS 09Dec96
//DeadCode RJS 20Nov98 //DeadCode RJS 27Feb97				_Miles.PlaySample((FileNum) (FIL_SFX_EXPLOSION_DISTANT1+Math_Lib.rnd(2)), (ItemBasePtr) missile);//RJS 09Dec96
//DeadCode RJS 20Nov98 //DeadCode RJS 27Feb97				LaunchSmoulder(missile,worldptr,TRUE);			//RJS 09Dec96
//DeadCode RJS 20Nov98 //DeadCode RJS 27Feb97				break;											//RJS 09Dec96
//DeadCode RJS 20Nov98 //DeadCode RJS 27Feb97		}
//DeadCode RJS 20Nov98
//DeadCode RJS 20Nov98		if (((TransientItem*)missile)->Launcher==Manual_Pilot.ControlledAC2)//PD 07Dec96
//DeadCode RJS 20Nov98			if (View_Object)
//DeadCode RJS 20Nov98				View_Object->PossDirectorAction(missile);
//DeadCode RJS 20Nov98		mad->itemstate = DEAD;									//RJS 16Oct96
//DeadCode RJS 20Nov98
//DeadCode RJS 20Nov98		if (	launcher->Status.deadtime == FALSE				//JIM 05Dec96
//DeadCode RJS 20Nov98			&&	(	groupindex == -1							//JIM 05Dec96
//DeadCode RJS 20Nov98				||	SHAPE.GetGroupDeathToll(launcher)			//JIM 05Dec96
//DeadCode RJS 20Nov98			)	)												//JIM 05Dec96
//DeadCode RJS 20Nov98		{														//JIM 05Dec96
//DeadCode RJS 20Nov98 //DeadCode RDH 16Dec96			ShapeDescPtr	sdptr = SHAPESTUFF.GetShapePtr(shapehit);//JIM 05Dec96
//DeadCode RJS 20Nov98
//DeadCode RJS 20Nov98			sdptr = SHAPESTUFF.GetShapePtr(launcher->shape);	//RJS 07Feb97
//DeadCode RJS 20Nov98			launcher->Status.deadtime = sdptr->DeadTime;		//JIM 05Dec96
//DeadCode RJS 20Nov98			launcher->Status.deadscale = sdptr->DeadScale;		//JIM 05Dec96
//DeadCode RJS 20Nov98 //DeadCode JIM 22Apr97			launcher->uniqueID.deaded = TRUE;					//JIM 10Dec96
//DeadCode RJS 20Nov98
//DeadCode RJS 20Nov98
//DeadCode RJS 20Nov98 //DEAD			if (	launcher->uniqueID.count==Miss_Man.camp.players_wpset.mainobjective
//DeadCode RJS 20Nov98 //DEAD				||	launcher->uniqueID.count==Miss_Man.camp.players_wpset.subobjective
//DeadCode RJS 20Nov98 //DEAD				||	launcher->uniqueID.count==Miss_Man.camp.players_wpset.wp1
//DeadCode RJS 20Nov98 //DEAD				||	launcher->uniqueID.count==Miss_Man.camp.players_wpset.wp2
//DeadCode RJS 20Nov98 //DEAD				||	launcher->uniqueID.count==Miss_Man.camp.players_wpset.wp3
//DeadCode RJS 20Nov98 //DEAD				)
//DeadCode RJS 20Nov98 //DEAD			{
//DeadCode RJS 20Nov98 //DEAD//TEMP				if (Persons_2.TargLog==NULL)
//DeadCode RJS 20Nov98 //DEAD//TEMP					Persons_2.TargLog=Persons_2.eventloglist=new EventLog(Persons_2.eventloglist);
//DeadCode RJS 20Nov98 //DEAD
//DeadCode RJS 20Nov98 //DEAD				int	count=+1;
//DeadCode RJS 20Nov98 //DEAD				if (missile->Status.size==TRANSIENTSIZE)
//DeadCode RJS 20Nov98 //DEAD				{
//DeadCode RJS 20Nov98 //DEAD					TransientItemPtr t=*missile;
//DeadCode RJS 20Nov98 //DEAD					if (t->Launcher==NULL || t->Launcher->Status.size<FORMATIONSIZE)
//DeadCode RJS 20Nov98 //DEAD						count=+1;								//JIM 18Dec96
//DeadCode RJS 20Nov98 //DEAD					else
//DeadCode RJS 20Nov98 //DEAD					{
//DeadCode RJS 20Nov98 //DEAD						FormationItemPtr f=*t->Launcher;
//DeadCode RJS 20Nov98 //DEAD						if (f->nationality==GR_NAT_FRIEND)
//DeadCode RJS 20Nov98 //DEAD						{
//DeadCode RJS 20Nov98 //DEAD							count=+1;
//DeadCode RJS 20Nov98 //DEAD						}
//DeadCode RJS 20Nov98 //DEAD						else
//DeadCode RJS 20Nov98 //DEAD							count=-1;
//DeadCode RJS 20Nov98 //DEAD					}
//DeadCode RJS 20Nov98 //DEAD				}
//DeadCode RJS 20Nov98 //DEAD				if (count>0)
//DeadCode RJS 20Nov98 //DEAD				{
//DeadCode RJS 20Nov98 //DEAD//TEMP					Persons_2.AddMessage(UserMsg::GOHOME,TEXT_OBJECTIVEDESTROYED,launcher);
//DeadCode RJS 20Nov98 //DEAD					MMC.specialeventbits |= FRIENDLYDESTROYEDTARGET;
//DeadCode RJS 20Nov98 //DEAD				}
//DeadCode RJS 20Nov98 //DEAD				else
//DeadCode RJS 20Nov98 //DEAD					MMC.specialeventbits |= ENEMYDESTROYEDTARGET;
//DeadCode RJS 20Nov98 //DEAD
//DeadCode RJS 20Nov98 //DEAD//TEMP				Persons_2.UpdateLog(Persons_2.TargLog,count,EventLog::KILLEDSTATIC);
//DeadCode RJS 20Nov98 //DEAD//TEMP				Persons_2.TargLog->name=_Text.ConvSnip0(launcher->uniqueID.count);
//DeadCode RJS 20Nov98 //DEAD			}
//DeadCode RJS 20Nov98 //DEAD			else
//DeadCode RJS 20Nov98 //DeadCode JIM 10Dec96				if (launcher->uniqueID.deaded==FALSE)
//DeadCode RJS 20Nov98 //DeadCode JIM 10Dec96				{
//DeadCode RJS 20Nov98				if (launcher->Status.size==FORMATIONSIZE)		//RDH 25Oct96
//DeadCode RJS 20Nov98				{
//DeadCode RJS 20Nov98 //DeadCode RDH 12Dec96					((FormationItem*)launcher)->BreakForm();	//RDH 25Oct96
//DeadCode RJS 20Nov98 //DeadCode JIM 10Dec96					if (launcher->Status.size>=FORMATIONSIZE)
//DeadCode RJS 20Nov98 //DeadCode JIM 10Dec96					{
//DeadCode RJS 20Nov98 //TEMP					if (Persons_2.TruckLog==NULL)
//DeadCode RJS 20Nov98 //TEMP						Persons_2.TruckLog=Persons_2.eventloglist=new EventLog(Persons_2.eventloglist);
//DeadCode RJS 20Nov98 //TEMP					if (((FormationItem*)launcher)->nationality==GR_NAT_FRIEND)//JIM 10Dec96
//DeadCode RJS 20Nov98 //TEMP						Persons_2.UpdateLog(Persons_2.TruckLog,-1,EventLog::KILLEDTRUCK);//JIM 10Dec96
//DeadCode RJS 20Nov98 //TEMP					else										//JIM 10Dec96
//DeadCode RJS 20Nov98 //TEMP						Persons_2.UpdateLog(Persons_2.TruckLog,+1,EventLog::KILLEDTRUCK);//JIM 10Dec96
//DeadCode RJS 20Nov98 //DeadCode JIM 10Dec96					}											//JIM 10Dec96
//DeadCode RJS 20Nov98				}
//DeadCode RJS 20Nov98			if (launcher->Status.size==FORMATIONSIZE)
//DeadCode RJS 20Nov98			{
//DeadCode RJS 20Nov98				((FormationItem*)launcher)->BreakForm();		//RDH 12Dec96
//DeadCode RJS 20Nov98			}
//DeadCode RJS 20Nov98		}														//JIM 05Dec96
//DeadCode RJS 20Nov98																//JIM 05Dec96
//DeadCode RJS 20Nov98		if (deadtype == ANIM_AMMOBOXES)								//RJS 07Nov96
//DeadCode RJS 20Nov98			mad->itemstate = DAMMAGED;							//RJS 04Dec96
//DeadCode RJS 20Nov98 //TempCode JIM 30Nov96		if (deadtype == AMMOBOXES)								//RJS 07Nov96
//DeadCode RJS 20Nov98 //TempCode JIM 30Nov96			mad->itemstate = ALIVE;								//RJS 07Nov96
//DeadCode RJS 20Nov98	}
//DeadCode RJS 20Nov98	else
//DeadCode RJS 20Nov98	{
//DeadCode RJS 20Nov98 //DeadCode RJS 07Feb97		deadtype = deathanims[shapehit - 1];					//RJS 14Oct96
//DeadCode RJS 20Nov98		sdptr = SHAPESTUFF.GetShapePtr(shapehit);				//RJS 07Feb97
//DeadCode RJS 20Nov98		deadtype = (DeathNum) sdptr->DeathType;							//RJS 07Feb97
//DeadCode RJS 20Nov98
//DeadCode RJS 20Nov98
//DeadCode RJS 20Nov98 //DEAD		if (	launcher->uniqueID.count==Miss_Man.camp.players_wpset.mainobjective//JIM 05Dec96
//DeadCode RJS 20Nov98 //DEAD			||	launcher->uniqueID.count==Miss_Man.camp.players_wpset.subobjective//JIM 05Dec96
//DeadCode RJS 20Nov98 //DEAD			||	launcher->uniqueID.count==Miss_Man.camp.players_wpset.wp1//JIM 05Dec96
//DeadCode RJS 20Nov98 //DEAD			||	launcher->uniqueID.count==Miss_Man.camp.players_wpset.wp2//JIM 05Dec96
//DeadCode RJS 20Nov98 //DEAD			||	launcher->uniqueID.count==Miss_Man.camp.players_wpset.wp3//JIM 05Dec96
//DeadCode RJS 20Nov98 //DEAD			)													//JIM 05Dec96
//DeadCode RJS 20Nov98 //DEAD		{														//JIM 05Dec96
//DeadCode RJS 20Nov98 //DEAD//TEMP			if (Persons_2.TargLog==NULL)
//DeadCode RJS 20Nov98 //DEAD//TEMP				Persons_2.TargLog=Persons_2.eventloglist=new EventLog(Persons_2.eventloglist);
//DeadCode RJS 20Nov98 //DEAD//TEMP			Persons_2.UpdateLog(Persons_2.TargLog,1,EventLog::DAMAGEDSTATIC);
//DeadCode RJS 20Nov98 //DEAD//TEMP			Persons_2.TargLog->name=_Text.ConvSnip0(launcher->uniqueID.count);
//DeadCode RJS 20Nov98 //DEAD		}
//DeadCode RJS 20Nov98 //DEAD		else
//DeadCode RJS 20Nov98 //DEAD			if (launcher->Status.size==FORMATIONSIZE)
//DeadCode RJS 20Nov98 //DEAD			{
//DeadCode RJS 20Nov98 //DEAD//TEMP				if (Persons_2.TruckLog==NULL)
//DeadCode RJS 20Nov98 //DEAD//TEMP					Persons_2.TruckLog=Persons_2.eventloglist=new EventLog(Persons_2.eventloglist);
//DeadCode RJS 20Nov98 //DEAD//TEMP				if (((FormationItem*)launcher)->nationality==GR_NAT_FRIEND)//JIM 10Dec96
//DeadCode RJS 20Nov98 //DEAD//TEMP					Persons_2.UpdateLog(Persons_2.TruckLog,-1,EventLog::DAMAGEDTRUCK);//JIM 10Dec96
//DeadCode RJS 20Nov98 //DEAD//TEMP				else											//JIM 10Dec96
//DeadCode RJS 20Nov98 //DEAD//TEMP					Persons_2.UpdateLog(Persons_2.TruckLog,+1,EventLog::DAMAGEDTRUCK);//JIM 10Dec96
//DeadCode RJS 20Nov98 //DEAD			}
//DeadCode RJS 20Nov98 //DEAD
//DeadCode RJS 20Nov98	}
//DeadCode RJS 20Nov98	if (launcher->Status.size==FORMATIONSIZE && missile->Status.size==TRANSIENTSIZE)
//DeadCode RJS 20Nov98		if (Manual_Pilot.ControlledAC2==((TransientItemPtr)missile)->Launcher)
//DeadCode RJS 20Nov98			Art_Int.PlayerHitConvoy(*launcher);

}

////////////////////////////////////////////////////////////////////////////////
//
//						Transient item movecodes
//
////////////////////////////////////////////////////////////////////////////////

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MobileBullet
//LastModified:	PD 12Sep96
//Author		Paul.
//Date			Fri 26 Apr 1996									//JIM 29Oct96
//
//Description	Must do collision test before first movement....
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void TransObj::MobileBullet(TransientItemPtr transit,WorldStuff& world)
{

//	if (transit->shape<0 || transit->shape>200)
//		_Error.EmitSysErr("Bad shape number in bullet");

	if ((transit->LaunchTime-=Timer_Code.FRAMETIME)<0)			//DAW 31Jul96
		transit->LaunchTime=0;
	else
	{
		// While frametime is in 50ths
		if ((transit->LaunchTime & 0x06)==0)					//RJS 03Jul98
		{
			Coords3D	hitcoords;
			UByte		theArea;								//RJS 28Apr99
			SLong	groundheight = GetGroundLevel(transit,theArea);//RJS 28Apr99

			if (!transit->Status.deadtime)
			{
				if (transit->World.Y<=groundheight)
				{
//DeadCode RJS 28Apr99					UByte	theArea = Three_Dee.GetLandType();		//MS 30Nov98

					hitcoords = transit->World;						//RJS 10Nov98
					hitcoords.Y = groundheight;						//RJS 10Nov98

					DoImpactGround(transit,hitcoords,theArea);		//MS 30Nov98

					MissileAnimData*	adptr = (MissileAnimData*)transit->Anim;
					adptr->IsInvisible = 1;
					transit->Status.deadtime = 1;

					if (adptr->lastmissile)
					{
						TransientItem*	olditm = (TransientItem*) adptr->lastmissile;

						olditm->isOwned = 0;
						adptr->lastmissile = 0;
					}
				}
				else
				{
					//Test for collision with other
					//items
					itemptr	 hititem;
					int	gindex;										//RJS 10Nov98

					hititem=BoxCol::NineSectorCol(transit,hitcoords,gindex);

					if (hititem)	//_Collide.TransCollTest((MovingItemPtr )transit, hititem, hitcoords, gindex))//RDH 26Nov96
					{
						MinAnimData*	mad = (MinAnimData*)transit->Anim;
						mad->IsInvisible = 1;
						transit->Status.deadtime = 1;
					}
				}
			}
//DeadCode DAW 04Jun99 			else
//DeadCode DAW 04Jun99 			 	transit->LaunchTime=0;							//RJS 29Mar99
		}

		if (transit->LaunchTime>0)	
			GAndFriction(transit,0);	//OrdinaryDrag);		//JIM 24Sep96
	}

	if (transit->LaunchTime<=0)
	{
//Dead		if (!transit->Status.deadtime)				//RJS 29Mar99
//DEad		{
			MissileAnimData*	adptr = (MissileAnimData*) transit->Anim;
			if (adptr->lastmissile)
			{
				TransientItem*	olditm = (TransientItem*) adptr->lastmissile;

				olditm->isOwned = 0;
				adptr->lastmissile = 0;
			}
//Dead		}

		if (transit->Launcher->Status.size == AIRSTRUCSIZE)		//DAW 04Jun99
		{														//DAW 04Jun99
			AirStrucPtr	ac = (AirStrucPtr)transit->Launcher;	//DAW 04Jun99
			if (ac->weap.currentbullet == transit)				//DAW 04Jun99
				ac->weap.currentbullet = NULL;					//DAW 04Jun99
		}														//DAW 04Jun99

		AddTransientItemToDeadList(transit);
	}
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MobilePuffTravel
//Author		Paul.
//Date			Fri 26 Apr 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void TransObj::MobilePuffTravel(TransientItemPtr transit,WorldStuff& world)
{
	int timeleft=transit->LaunchTime;

	if (timeleft)
	{
		if ((transit->LaunchTime-=Timer_Code.FRAMETIME)<0)		//DAW 31Jul96
			transit->LaunchTime=0;

		//move the bullet
		GAndFriction(transit,0);
	}
	else
	{
		SLong	groundheight = GetGroundLevel(transit);
		if (transit->World.Y > groundheight)
		{
			SeenFlak(transit);

			LaunchFlak(transit,world);
			AddTransientItemToDeadList(transit);
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MobileBombDrop
//Author		Robert Slater
//Date			Wed 24 Jul 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::MobileBombDrop(TransientItemPtr transit,WorldStuff& world)
{
	int timeleft=transit->LaunchTime;

	if (timeleft>0)
	{
		if ((transit->LaunchTime-=Timer_Code.FRAMETIME)<0)		//DAW 31Jul96
			transit->LaunchTime=0;

		if (transit->TransRandom > timeleft)
		{
			_Miles.PlaySample(FIL_SFX_BOMB_WHISTLE, (ItemBasePtr) transit);//RJS 22Nov96
			transit->TransRandom = 0;
		}

		//Test for collision with the ground, but not every move cycle
		// While frametime is in 50ths							//RJS 21Jul98
		if ((transit->LaunchTime & 0x06)==0)					//RJS 21Jul98
		{
			bool	isArmed;
			if ((LIFETIME_BOMB-timeleft)>125)					//RJS 15Jun99
				isArmed = true;
			else
				isArmed = false;

			Coords3D hitcoords;
			SLong	groundheight;
			UByte	theArea;									//RJS 28Apr99
			groundheight = GetGroundLevel(transit,theArea);		//RJS 28Apr99

			if (transit->World.Y<=groundheight)					//RJS 10Jun99
			{
				hitcoords = transit->World;
				hitcoords.Y = groundheight + METRES01;

				if (isArmed)									//RJS 10Jun99
					DoImpactGround(transit,hitcoords,theArea);	//MS 30Nov98
				else
					LaunchDustRing(transit,world);				//RJS 11Jun99

				transit->World.Y = hitcoords.Y;
				_Miles.StopSample(FIL_SFX_BOMB_WHISTLE,(ItemBasePtr) transit);

				transit->LaunchTime = 0;

				if ((transit->shape == BOMB29) || (transit->shape == BMB129))//RJS 17Jun99
					LaunchCarpetStrike(transit,world);
			}
			else
			{
				//Bomb is armed after 2secs of falling...
				if (isArmed)
				{
					//Test for collision with other
					//items

					itemptr	 hititem;
					int	gindex;										//RJS 10Nov98
					
					hititem=BoxCol::NineSectorCol(transit,hitcoords,gindex);//RDH 26Nov96
					if (hititem)									//RJS 17May99
					{
						//We've hit the item 'hititem' the impact coordinates
						//are in 'hitvector'

						_Miles.StopSample(FIL_SFX_BOMB_WHISTLE,(ItemBasePtr) transit);//RJS 06Dec96

//Dead					transit->vely=transit->velx=transit->velz=transit->velhori=0;

						transit->LaunchTime = 0;
						if (SHAPESTUFF.GetShapeDamageType(transit->shape)==DMT_FIRE)	//RJS 19Feb99
						{
							Coords3D	oldcoords = transit->World;

							transit->World = hitcoords;
							LaunchNapalmImpacted(transit,world);
							transit->World = oldcoords;
						}
						else
						{
							if ((transit->shape == BOMB29) || (transit->shape == BMB129))//RJS 17Jun99
								LaunchCarpetStrike(transit,world);
						}
					}
				}
			}
		}

		//move the bomb
		if (transit->LaunchTime>0)	
			GAndFriction(transit,0);					//RJS 04May99
	}
	else
	{
		AddTransientItemToDeadList(transit);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MobileFuelDrop
//Author		Robert Slater
//Date			Thu 28 May 1998
//
//Description	Fuel tank movecode, with realistic tumble dry spin.
//
//				Starts to whistle at 20 m/s
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::MobileFuelDrop(TransientItemPtr transit,WorldStuff& world)
{
	int timeleft=transit->LaunchTime;
	if (timeleft>0)
	{
		SWord	randmask = transit->TransRandom;
		SWord	nosound = randmask & 1;

		if ((transit->LaunchTime-=Timer_Code.FRAMETIME)<0)
			transit->LaunchTime=0;

		randmask >>= 1;

		Angles	angdelta = (Angles)randmask;

		transit->pitch += angdelta;

//DeadCode RJS 07Dec98		GAndFrictionFixedPitch(transit,OrdinaryDrag<<1);		//RJS 27Aug98
		GAndFrictionFixedPitch(transit,0);						//RJS 07Dec98

		//Test for collision with the ground, but not every move cycle
		// While frametime is in 50ths							//RJS 21Aug98
		if ((transit->LaunchTime & 0x06)==0)					//RJS 21Aug98
		{
			UByte	theArea;
			SLong	groundheight = GetGroundLevel(transit,theArea);//RJS 28Apr99

			if (transit->World.Y <= groundheight)				//RJS 21Aug98
			{
//DeadCode RJS 28Apr99				UByte	theArea = Three_Dee.GetLandType();		//MS 30Nov98

				Coords3D	hitpos = transit->World;			//RJS 10Nov98
				hitpos.Y = groundheight + METRES01;				//RJS 10Nov98
																//RJS 10Nov98
				DoImpactGround(transit,hitpos,theArea);			//MS 30Nov98
																//RJS 10Nov98
				_Miles.StopSample(FIL_SFX_BOMB_WHISTLE,transit);//RJS 10Nov98
																//RJS 10Nov98
				transit->LaunchTime = 0;						//RJS 10Nov98
			}
			else
			{
				if (	(nosound == 1)
					&&	(transit->vely < -50)		)
				{
					_Miles.PlaySample(FIL_SFX_BOMB_WHISTLE,transit);
					transit->TransRandom = 0 + (randmask << 1);
				}
			}
		}
	}
	else
		AddTransientItemToDeadList(transit);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MobileDeadACPart
//Author		Paul.
//Date			Mon 29 Apr 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void TransObj::MobileDeadACPart(TransientItemPtr transit,WorldStuff& worldptr)
{
	int timeleft=transit->LaunchTime;

	if (timeleft>0)
	{
		SWord	frametime;

		frametime = Timer_Code.FRAMETIME;						//DAW 31Jul96

		if ((transit->LaunchTime-=frametime)<0)
			transit->LaunchTime=0;

		//move the deadacpart

		UWord	ltrnd;
		SByte	tmp;
		ANGLES	angdelta;

		ltrnd = transit->TransRandom;

		tmp = (ltrnd & 0x03)<<6;

		ltrnd >>=2;

		angdelta = (Angles)(tmp*frametime);

		transit->roll += angdelta;

		tmp = (ltrnd & 0x03)<<6;

		ltrnd >>=2;

		angdelta = (Angles)(tmp*frametime);

		transit->hdg += angdelta;

		tmp = (ltrnd & 0x03)<<6;

		ltrnd >>=2;

		angdelta = (Angles)(tmp*frametime);

		transit->pitch += angdelta;

		GAndFriction(transit,OrdinaryDrag,OrdinaryDrag);		//RJS 12Aug96

		//Test for collision with the ground, but not every move cycle
		// While frametime is in 50ths							//RJS 21Aug98
		if ((transit->LaunchTime & 0x06)==0)					//RJS 21Aug98
		{
			UByte	theArea;
			SLong	groundheight = GetGroundLevel(transit,theArea);//RJS 28Apr99
			if (transit->World.Y <= groundheight)
			{
				Coords3D	hitpos = transit->World;			//RJS 10Nov98
				hitpos.Y = groundheight;						//RJS 10Nov98

				DoImpactGround(transit,hitpos,theArea);			//MS 30Nov98
				transit->LaunchTime = 0;
			}
			else
			{
				if (BoxCol::NineSectorColPiloted(transit))		//RJS 17May99
					transit->LaunchTime=0;						//RJS 17May99
			}
		}
	}
	else
	{
		AddTransientItemToDeadList(transit);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MobileSmokeTrail
//Author		Paul.
//Date			Tue 30 Apr 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void TransObj::MobileSmokeTrail(TransientItemPtr transit,WorldStuff& world)
{
	SLong	timeleft=transit->LaunchTime;
//Deadcode	MoveGunAnimData		*adptr2 = (MoveGunAnimData*) transit->Anim;
	if (transit->Target->Status.size == AirStrucSize)
	{
		AircraftAnimData	*adptr = (AircraftAnimData*) ((ItemPtr)transit->Target)->Anim;

		if (adptr->hasdust == TRUE)								//RJS 16May99
		{
			transit->World = transit->Target->World;		//RJS 16May99
			transit->uniqueID.changed = TRUE;			//RJS 09Dec98
		}
		else
			AddTransientItemToDeadList(transit);
	}
	else
		AddTransientItemToDeadList(transit);

//DeadCode RJS 24Jun97	if (timeleft && (transit->Target->shape != PDEATH) && (transit->Target->shape != WRECK))//RJS 06Nov96
//DeadCode RJS 24Jun97	{
//DeadCode RJS 24Jun97		SWord	frametime;
//DeadCode RJS 24Jun97
//DeadCode RJS 24Jun97		frametime = Timer_Code.FRAMETIME;						//DAW 31Jul96
//DeadCode RJS 24Jun97
//DeadCode RJS 24Jun97		if ((transit->LaunchTime-=frametime)<0)
//DeadCode RJS 24Jun97			transit->LaunchTime=0;
//DeadCode RJS 24Jun97
//DeadCode RJS 24Jun97		//Follow the target
//DeadCode RJS 24Jun97
//DeadCode RJS 24Jun97		transit->World.X = transit->Target->World.X;
//DeadCode RJS 24Jun97		transit->World.Y = transit->Target->World.Y;
//DeadCode RJS 24Jun97		transit->World.Z = transit->Target->World.Z;
//DeadCode RJS 24Jun97
//DeadCode RJS 24Jun97		//Launch a piece of smoke if it's
//DeadCode RJS 24Jun97		//the right time
//DeadCode RJS 24Jun97
//DeadCode RJS 24Jun97		SWord launchtime = (SWord )transit->TransRandom;
//DeadCode RJS 24Jun97
//DeadCode RJS 24Jun97		launchtime-=frametime;
//DeadCode RJS 24Jun97
//DeadCode RJS 24Jun97		if (launchtime<=0)
//DeadCode RJS 24Jun97		{
//DeadCode RJS 24Jun97			//Time to launch some smoke
//DeadCode RJS 24Jun97
//DeadCode RJS 24Jun97			TransientItem*	newitem;
//DeadCode RJS 24Jun97
//DeadCode RJS 24Jun97			newitem = LaunchUnguidedMissile(	transit,
//DeadCode RJS 24Jun97												SmokinShape,
//DeadCode RJS 24Jun97												LIFETIME_SMOKE,MOBILE_GANDF);//RJS 29Oct96
//DeadCode RJS 24Jun97			if (newitem)
//DeadCode RJS 24Jun97			{
//DeadCode RJS 24Jun97				newitem->TransRandom = 0;
//DeadCode RJS 24Jun97				newitem->World.X += (Math_Lib.rnd(40) - 20);
//DeadCode RJS 24Jun97				newitem->World.Y += (Math_Lib.rnd(40) - 20);
//DeadCode RJS 24Jun97				newitem->velhori = 0;							//RJS 29Oct96
//DeadCode RJS 24Jun97				newitem->vely = 0;								//RJS 29Oct96
//DeadCode RJS 24Jun97
//DeadCode RJS 24Jun97				AddTransientItemToWorld(newitem,world);
//DeadCode RJS 24Jun97
//DeadCode RJS 24Jun97				ExplodeAnimData* adptr;									//PD 08May96
//DeadCode RJS 24Jun97				adptr = (ExplodeAnimData* )newitem->Anim;			//RJS 31Jul96
//DeadCode RJS 24Jun97				adptr->frameno = 0;									//RJS 05Jul96
//DeadCode RJS 24Jun97
//DeadCode RJS 24Jun97				if (Math_Lib.rnd() <16*1024-TransientItem::transcount*10)
//DeadCode RJS 24Jun97				{
//DeadCode RJS 24Jun97					newitem = LaunchUnguidedMissile(transit,SPARK,
//DeadCode RJS 24Jun97												LIFETIME_SMOKE,MOBILE_RICOCHET);
//DeadCode RJS 24Jun97					
//DeadCode RJS 24Jun97					if (newitem)
//DeadCode RJS 24Jun97					{
//DeadCode RJS 24Jun97						newitem->hdg += (ANGLES) (ANGLES_180Deg - Math_Lib.rnd(ANGLES_45Deg) + ANGLES_20Deg);
//DeadCode RJS 24Jun97						newitem->velhori = 200 + Math_Lib.rnd(200);
//DeadCode RJS 24Jun97						newitem->vely = Math_Lib.rnd(100) - 50;
//DeadCode RJS 24Jun97						AddTransientItemToWorld(newitem,world);
//DeadCode RJS 24Jun97					}
//DeadCode RJS 24Jun97				}
//DeadCode RJS 24Jun97
//DeadCode RJS 24Jun97			}
//DeadCode RJS 24Jun97
//DeadCode RJS 24Jun97 //DeadCode RJS 08Jul96			launchtime = SmokeLaunchDelay;
//DeadCode RJS 24Jun97 //DeadCode RJS 31Jul96			launchtime = 12;
//DeadCode RJS 24Jun97			launchtime = (launchtime+3)&3;
//DeadCode RJS 24Jun97			launchtime+=(TransientItem::transcount>>4);	//every 16=1cs	//48=3cs
//DeadCode RJS 24Jun97
//DeadCode RJS 24Jun97
//DeadCode RJS 24Jun97		}
//DeadCode RJS 24Jun97		transit->TransRandom = (UWord )launchtime;
//DeadCode RJS 24Jun97	}
//DeadCode RJS 24Jun97	else
//DeadCode RJS 24Jun97	{
//DeadCode RJS 24Jun97		//Kill the launcher here
//DeadCode RJS 24Jun97		
//DeadCode RJS 24Jun97 //DeadCode RJS 12Aug96		KillLauncher(transit->Launcher,world);
//DeadCode RJS 24Jun97
//DeadCode RJS 24Jun97		AddTransientItemToDeadList(transit);
//DeadCode RJS 24Jun97	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MobileGAndF
//Author		Paul.
//Date			Tue 30 Apr 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void TransObj::MobileGAndF(TransientItemPtr transit,WorldStuff& world)
{
	SLong	timeleft = transit->LaunchTime;

	if (timeleft)
	{
		if ((transit->LaunchTime-=Timer_Code.FRAMETIME)<0)		//DAW 31Jul96
			transit->LaunchTime=0;

		GAndFriction(transit,OrdinaryDrag);
		if (transit->TransRandom == 1)
			transit->pitch = ANGLES_0Deg;

		// While frametime is in 50ths
		if ((transit->LaunchTime & 0x06)==0)					//RJS 17Nov98
		{
			SLong	groundheight = GetGroundLevel(transit);		//RJS 14Apr99
			if (transit->World.Y <= groundheight)			//RJS 10Dec98
				AddTransientItemToDeadList(transit);		//RJS 10Dec98
		}
	}
	else
		AddTransientItemToDeadList(transit);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MobileGroundExp
//Author		Paul.
//Date			Wed 1 May 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void TransObj::MobileGroundExp(TransientItemPtr transit,WorldStuff& world)
{
	SLong	timeleft = transit->LaunchTime;

	if (timeleft)
	{
		_Miles.PlayLooped(FIL_SFX_SMALL_FIRE_LOOP, (ItemBasePtr) transit);//RJS 22Nov96

		SWord	frametime;

		frametime = Timer_Code.FRAMETIME;						//DAW 31Jul96

		if ((transit->LaunchTime-=frametime)<0)
			transit->LaunchTime=0;

		//Launch a piece of smoke if it's
		//the right time

//		SWord launchtime = (SWord )transit->TransRandom;
//
//		launchtime-=frametime;
//
//		if (launchtime<=0)
//		{
//			//Time to launch some smoke
//
//			TransientItem*	newitem;
//
//			newitem = SimplifiedSpriteLaunch(	transit,
//												BigSmokeShape,	//PD 09May96
//												LIFETIME_SMOKE,MOBILE_STATIONARY);//RJS 20Apr98
//			if (newitem)
//			{
//				//Give the smoke particle some vertical velocity
//
//				UWord	randomfactor;
//				SLong	vvel;
//
//				randomfactor = Math_Lib.rnd();
//
//				newitem->vely = SmokeBaseVel + ((randomfactor * SmokeVariableVertVel * 2)>>16);
//				newitem->pitch= ANGLES_90Deg;
//
//				newitem->World.Y += 500;						//RJS 18Sep96
//
//				newitem->hdg = (Angles)(Math_Lib.rnd());
//
//				SWord	sin_ang,cos_ang;
//
////DeadCode RJS 07Feb97				Math_Lib.high_sin_cos((ANGLES )newitem->hdg,sin_ang,cos_ang);
//
//				randomfactor = Math_Lib.rnd();
//
//				newitem->velhori = ((randomfactor * SmokeVariableHorzVel)>>16);

//DeadCode RJS 07Feb97				newitem->velx = (newitem->velhori * sin_ang)/ANGLES_FRACT;
//DeadCode RJS 07Feb97
//DeadCode RJS 07Feb97				newitem->velz = (newitem->velhori * cos_ang)/ANGLES_FRACT;
//
//				AddTransientItemToWorld(newitem,world);
//			}

//DeadCode RJS 11Jul97			//Drive the shape animation								//PD 08May96
//DeadCode RJS 11Jul97
//DeadCode RJS 11Jul97			ExplodeAnimData* adptr;									//PD 08May96
//DeadCode RJS 11Jul97
//DeadCode RJS 11Jul97			adptr = (ExplodeAnimData* )transit->Anim;				//PD 08May96
//DeadCode RJS 11Jul97
//DeadCode RJS 11Jul97			adptr->frameno++;										//PD 08May96
//DeadCode RJS 11Jul97
//DeadCode RJS 11Jul97			if (adptr->frameno>3)									//PD 08May96
//DeadCode RJS 11Jul97				adptr->frameno = 0;									//PD 08May96
//
//			launchtime = SmokeLaunchDelay+((3*TransientItem::transcount)>>4);
//		}
//		transit->TransRandom = (UWord )launchtime;
	}
	else
	{
		AddTransientItemToDeadList(transit);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MobileMovingSmoke
//Author		Robert Slater
//Date			Mon 2 Sep 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void TransObj::MobileMovingSmoke(TransientItemPtr transit,WorldStuff& world)
{
	SLong	timeleft = transit->LaunchTime;

//DeadCode RJS 16Sep98	if (timeleft && (transit->Launcher->shape != EMPTY))		//RDH 17Dec96
//DeadCode RJS 16Sep98	{
//DeadCode RJS 16Sep98		_Miles.PlayLooped(FIL_SFX_FIREBURN_LOOP, (ItemBasePtr) transit);//RJS 22Nov96
//DeadCode RJS 16Sep98
//DeadCode RJS 16Sep98		SWord	frametime;
//DeadCode RJS 16Sep98
//DeadCode RJS 16Sep98		frametime = Timer_Code.FRAMETIME;						//DAW 31Jul96
//DeadCode RJS 16Sep98
//DeadCode RJS 16Sep98		if ((transit->LaunchTime-=frametime)<0)
//DeadCode RJS 16Sep98			transit->LaunchTime=0;
//DeadCode RJS 16Sep98
//DeadCode RJS 16Sep98		//Launch a piece of smoke if it's
//DeadCode RJS 16Sep98		//the right time
//DeadCode RJS 16Sep98
//DeadCode RJS 16Sep98		SWord launchtime = (SWord )transit->TransRandom;
//DeadCode RJS 16Sep98
//DeadCode RJS 16Sep98		launchtime-=frametime;
//DeadCode RJS 16Sep98
//DeadCode RJS 16Sep98		if (launchtime<=0)
//DeadCode RJS 16Sep98		{
//DeadCode RJS 16Sep98			//Time to launch some smoke
//DeadCode RJS 16Sep98
//DeadCode RJS 16Sep98			TransientItem*	newitem;
//DeadCode RJS 16Sep98
//DeadCode RJS 16Sep98			newitem = SimplifiedSpriteLaunch(	transit,
//DeadCode RJS 16Sep98												BigSmokeShape,	//PD 09May96
//DeadCode RJS 16Sep98												LIFETIME_SMOKE,MOBILE_GANDF);
//DeadCode RJS 16Sep98			if (newitem)
//DeadCode RJS 16Sep98			{
//DeadCode RJS 16Sep98				UWord	randomfactor;
//DeadCode RJS 16Sep98				SLong	vvel;
//DeadCode RJS 16Sep98				newitem->TransRandom = 0;
//DeadCode RJS 16Sep98
//DeadCode RJS 16Sep98 //DeadCode RJS 19Feb98				ExplodeAnimData* adptr;									//PD 08May96
//DeadCode RJS 16Sep98 //DeadCode RJS 19Feb98				adptr = (ExplodeAnimData* )newitem->Anim;			//RJS 31Jul96
//DeadCode RJS 16Sep98 //DeadCode RJS 19Feb98				adptr->frameno = 0;	
//DeadCode RJS 16Sep98
//DeadCode RJS 16Sep98				newitem->World.X = transit->Launcher->World.X;
//DeadCode RJS 16Sep98				newitem->World.Y = transit->Launcher->World.Y + 50;
//DeadCode RJS 16Sep98				newitem->World.Z = transit->Launcher->World.Z;
//DeadCode RJS 16Sep98
//DeadCode RJS 16Sep98				randomfactor = Math_Lib.rnd();
//DeadCode RJS 16Sep98
//DeadCode RJS 16Sep98				newitem->vely = SmokeBaseVel + ((randomfactor * SmokeVariableVertVel)>>16);//RJS 02Sep96
//DeadCode RJS 16Sep98				newitem->pitch= ANGLES_90Deg;
//DeadCode RJS 16Sep98
//DeadCode RJS 16Sep98				newitem->hdg = (Angles)(Math_Lib.rnd());
//DeadCode RJS 16Sep98
//DeadCode RJS 16Sep98				SWord	sin_ang,cos_ang;
//DeadCode RJS 16Sep98
//DeadCode RJS 16Sep98				Math_Lib.high_sin_cos((ANGLES )newitem->hdg,sin_ang,cos_ang);
//DeadCode RJS 16Sep98
//DeadCode RJS 16Sep98				randomfactor = Math_Lib.rnd();
//DeadCode RJS 16Sep98
//DeadCode RJS 16Sep98				newitem->velhori = ((randomfactor * SmokeVariableHorzVel)>>16);
//DeadCode RJS 16Sep98
//DeadCode RJS 16Sep98				newitem->velx = (newitem->velhori * sin_ang)/ANGLES_FRACT;
//DeadCode RJS 16Sep98
//DeadCode RJS 16Sep98				newitem->velz = (newitem->velhori * cos_ang)/ANGLES_FRACT;
//DeadCode RJS 16Sep98
//DeadCode RJS 16Sep98				AddTransientItemToWorld(newitem,world);
//DeadCode RJS 16Sep98			}
//DeadCode RJS 16Sep98
//DeadCode RJS 16Sep98			launchtime = SmokeLaunchDelay;
//DeadCode RJS 16Sep98		}
//DeadCode RJS 16Sep98		transit->TransRandom = (UWord )launchtime+(TransientItem::transcount>>4);
//DeadCode RJS 16Sep98	}
//DeadCode RJS 16Sep98	else
//DeadCode RJS 16Sep98	{
//DeadCode RJS 16Sep98		AddTransientItemToDeadList(transit);
//DeadCode RJS 16Sep98	}

	if (timeleft)
	{
		SWord	frametime = Timer_Code.FRAMETIME;
		SWord	testvel;
		UWord	deadshape = UWord(transit->pitch);

		if ((transit->LaunchTime-=frametime)<0)		//DAW 31Jul96
			transit->LaunchTime=0;

		// Use half the amount of gravitational effect...
		// ... and keep floating...
		if ((transit->LaunchTime & 6)==0)
		{
//			if (transit->vely > (frametime<<2))
//				transit->vely -= (frametime>>1);

			UWord	thistime = UWord(transit->roll);
			if (thistime)
			{
				UWord	timepassed = thistime - timeleft;
				if (timepassed > transit->TransRandom)
				{
					if (deadshape)
					{
						TransientItem*	newitem;
						newitem = LaunchUnguidedMissile(transit,
														(ShapeNum)deadshape,
														800,
														MOBILE_MOVSMK);

						if (newitem)
						{
							newitem->roll = (Angles) 0;
							newitem->pitch = (Angles) 0;
							AddTransientItemToWorld(newitem, world);
						}
					}

					transit->LaunchTime = 0;
				}
			}
			else
			{
				if (transit->vely > (frametime<<2))
					transit->vely -= (frametime>>1);
			}
		}

		if (deadshape == 0)
		{
			// Drag is 1
			testvel = (transit->velhori * frametime)>>12;
			transit->velhori -= testvel;
		}
		else
		{
/*			if (transit->velhori > 20)
			{
				testvel = (transit->velhori * frametime)>>12;
				transit->velhori -= testvel;
			}*/
		}

		// ApplyVelocities, without pitch nobble
		transit->World.Y += (transit->vely * frametime)/10;

		SLong	temp = (frametime * transit->velhori)/10;
		SWord	sin_ang,cos_ang;
		Math_Lib.high_sin_cos(transit->hdg,sin_ang,cos_ang);
		transit->World.X += (temp*sin_ang)/ANGLES_FRACT;
		transit->World.Z += (temp*cos_ang)/ANGLES_FRACT;

		transit->uniqueID.changed = TRUE;
		// ApplyVelocities, without pitch nobble

		AddWindDrift(transit);
	}
	else
		AddTransientItemToDeadList(transit);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MobileExplosion
//Author		Paul.
//Date			Wed 1 May 1996
//
//Description	Actually burns whatever it is over
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void TransObj::MobileExplosion(TransientItemPtr transit,WorldStuff& world)
{
	SLong	timeleft = transit->LaunchTime;
	if (timeleft)
	{
		if ((transit->LaunchTime-=Timer_Code.FRAMETIME)<0)
			transit->LaunchTime=0;

		if ((timeleft & 0x06)==0)
		{
			_Miles.PlayLooped(FIL_SFX_NAPALM_SIZZLE,transit);
			if (!transit->Status.deadtime)						//RJS 19Feb99
			{
				itemptr		hititem;
				Coords3D	hitcoords;
				int			gindex;

				hititem=BoxCol::NineSectorCol(transit,hitcoords,gindex);
				if (hititem)
					LaunchSmallThug(transit,hititem,NapalmThugShape,gindex,timeleft*2);
			}
		}

		UWord	smkdelay = transit->TransRandom >> 8;
		UWord	tottime = transit->TransRandom & 0xFF;
		SWord	smoketime = smkdelay;
		smoketime -= Timer_Code.FRAMETIME;
		if ((smoketime < 0) && tottime)
		{
			SLong	tdist = tottime - timeleft;					//DAW 07Apr99
			if (transit->Status.Drawn)							//DAW 07Apr99
			{
				ShapeDescPtr	sdptr = SHAPESTUFF.GetShapePtr(transit->shape);
				SLong	width,length;
				SLong	area;
				SLong	i,nosmoke;
				SLong	maxx, maxz,minx,minz;
				SWord	sin_ang,cos_ang;
				SLong	xoff,zoff,xoff2,zoff2;
				SLong	currlength,currwidth,rlength,rwidth;
				SLong	clength,cwidth;
				ShapeNum	theShape;							//DAW 07Apr99
				SLong		theMovement;						//DAW 07Apr99

				if ((timeleft & 0x06)==0)						//DAW 07Apr99
				{
					theShape = FireballShape;		//distant napalm smoke
					theMovement = MOBILE_MOVSMK;
				}
				else
				{
					theShape = DSTNAP;		//near napalm smoke
					theMovement = MOBILE_STATIONARY;
				}

				width = sdptr->sx<<5;
				length = sdptr->sz<<5;

				// travel the length of the napalm...
				length = (tdist*length) / tottime;
				width = (tdist*width) / tottime;

				clength = length >> 1;
				cwidth = width >> 1;

				TransientItemPtr	newitem;
				newitem = SimplifiedSpriteLaunch(	transit,
													theShape,	//DAW 07Apr99
													550,
													(AutoMoveCodeTypeSelect)theMovement);//DAW 07Apr99

				if (newitem)
				{
					newitem->velhori = 0;
					newitem->vely = 50;
					newitem->World.X += Math_Lib.rnd(width) - cwidth;
					newitem->World.Z += Math_Lib.rnd(length) - clength;
					newitem->World.Y = GetGroundLevel(newitem) + 250;//RJS 14Apr99
					newitem->roll = (Angles) 0;
					newitem->pitch = (Angles) 0;
					AddTransientItemToWorld(newitem, world);
				}
			}

			transit->TransRandom = 0;
			smoketime = 40 - ((40 * tdist) / tottime);
		}

		transit->TransRandom = UWord(smoketime);
		transit->TransRandom <<= 8;
		transit->TransRandom |= tottime;
	}
	else
	{
		TransientItem*	newitem;
		if (WithinVisibleRange(transit->World,300000))				//RJS 30Apr99
		{
			SWord			lifetime = transit->pitch;
			SLong			scatterno,size1;
			ShapeDescPtr	sdptr = SHAPESTUFF.GetShapePtr(transit->shape);
			ShapeDescPtr	sdptr2 = SHAPESTUFF.GetShapePtr(SmallFireShape);
			SLong			size2 = (sdptr2->sx<<4) * (sdptr2->sz<<4);
//Dead			TransientItem*	newitem;
			SLong			wx,wz;
			SLong			sizex,sizez;
			SLong			sizex2,sizez2;
			SLong			i;

			size1 = (sdptr->sx<<4) * (sdptr->sz<<4);
			scatterno = size1 / size2;
			scatterno = (lifetime * scatterno)/240;

			sizex = sdptr->sx<<4;
			sizez = sdptr->sz<<4;

			sizex2 = (lifetime * sizex) / 240;
			sizez2 = (lifetime * sizez) / 240;

			sizex = sizex2 >> 1;
			sizez = sizez2 >> 1;

			scatterno = (scatterno>>1) + Math_Lib.rnd(scatterno>>1);

			for (i = 0; i < 3; i++)							//RJS 05May99
			{
				newitem = SimplifiedSpriteLaunch(	transit,
													LargeScatFireShape,//DAW 11May99
													1500,
													MOBILE_STATIONARY);//RJS 20Apr98
				if (newitem)
				{
					wx = (sizex*Math_Lib.rnd()) - sizex2;
					wz = (sizez*Math_Lib.rnd()) - sizez2;

					newitem->World.X += wx;
					newitem->World.Z += wz;
					newitem->World.Y = GetGroundLevel(newitem);		//RJS 14Apr99

					AddTransientItemToWorld(newitem, world);
				}
			}
		}

		// Launch scorch mark...
		if (!transit->Status.deadtime && transit->Target)			//RJS 11May99
		{
			//Only really want to add 1...
			newitem = SimplifiedSpriteLaunch(	transit,
												SCORCH,
												6000,
												MOBILE_STATIONARY);
			if (newitem)
			{
				newitem->hdg = transit->hdg;
				newitem->pitch = transit->pitch;
				newitem->roll = transit->roll;

				AddTransientItemToWorld(newitem, world);
			}
		}

		AddTransientItemToDeadList(transit);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MobileTimerExplosion
//Author		Robert Slater
//Date			Thu 22 Jan 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void TransObj::MobileTimerExplosion(TransientItemPtr transit,WorldStuff& worldptr)
{
	SLong	timeleft = transit->LaunchTime;

	if (timeleft)
	{
		if ((transit->LaunchTime-=Timer_Code.FRAMETIME)<0)
			transit->LaunchTime=0;
	}
	else
	{
		LaunchMiniExplosion(transit,worldptr);

		AddTransientItemToDeadList(transit);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MobileMiniExplosion
//Author		Martin Alderton
//Date			Tue 27 Feb 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void TransObj::MobileFlare(TransientItemPtr transit,WorldStuff& worldptr)
{
	int timeleft=transit->LaunchTime;
	if (timeleft>0)
	{
		if ((transit->LaunchTime-=Timer_Code.FRAMETIME)<0)
			transit->LaunchTime=0;

		//Test for collision with the ground, but not every move cycle
		// While frametime is in 50ths
		if ((transit->LaunchTime & 0x06)==0)
		{
			Coords3D hitcoords;
			SLong	groundheight;
			UByte	theArea;

			groundheight = GetGroundLevel(transit,theArea);

			if (transit->World.Y<=groundheight)
			{
				transit->World.Y = groundheight;
				transit->LaunchTime = 0;

				SLandLight lightDef;
				lightDef.pos=transit->World;
				lightDef.color.r=0xFF00;
				lightDef.color.g=0xFF00;
				lightDef.color.b=0xFF00;
				lightDef.timer=50;	//half a second
				lightDef.range=25000;	//quarter km

				Land_Scape.AddLight(&lightDef);
				LaunchSmallFlash(transit,worldptr);
				LaunchSmoulder(transit,worldptr);
			}
		}

		//move the bomb
		if (transit->LaunchTime>0)	
			GAndFriction(transit,0);
	}
	else
		AddTransientItemToDeadList(transit);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MobileGroundDebris
//Author		Robert Slater
//Date			Fri 21 Jun 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::MobileGroundDebris(TransientItemPtr transit, WorldStuff& worldptr)
{
	SLong	timeleft = transit->LaunchTime;

	if (timeleft)
	{
		if ((transit->LaunchTime-=Timer_Code.FRAMETIME)<0)
			transit->LaunchTime=0;

		if (transit->shape == PLUME2)
		{
			SWord	oldvy = transit->vely;

			GAndFriction(transit,OrdinaryDrag);

			if ((transit->vely <= 0) && (oldvy > 0))
				transit->velhori /= 2;
		}
		else
			GAndFriction(transit,OrdinaryDrag);

		//Test for collision with the ground
		if ((timeleft & 0x06)==0)
		{
			SLong	groundheight = GetGroundLevel(transit);		//RJS 14Apr99

			if (transit->World.Y < groundheight)
			{
				transit->World.Y = groundheight;
				if (transit->shape == NapalmFingerShape)				//RJS 09Dec98
					LaunchGuidedBurning(transit,worldptr);
				else
				{
					if (transit->shape != BoxShape)
						_Miles.PlaySample(FIL_SFX_DEBRIS_SHOWER, (ItemBasePtr) transit);//RJS 05Dec96
					else
						_Miles.PlaySample(FIL_SFX_DEBRIS_THUD1, (ItemBasePtr) transit);//RJS 05Dec96
				}

				AddTransientItemToDeadList(transit);
			}
			else
			{
				UWord	transpants = SWord(transit->TransRandom);
				if (transpants)
				{
					UWord	pitchover = transpants & 0xFF;
					UWord	rollover = (transpants & 0xFF00)>>8;

					transit->roll += (Angles)rollover;
					transit->pitch += (Angles)pitchover;
				}
			}
		}
	}
	else
	{
		AddTransientItemToDeadList(transit);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MobileFire
//Author		Robert Slater
//Date			Mon 1 Jul 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::MobileFire(TransientItemPtr transit, WorldStuff& world)
{
	SLong	timeleft = transit->LaunchTime;

	if (timeleft)
	{
		_Miles.PlayLooped(FIL_SFX_SMALL_FIRE_LOOP, (ItemBasePtr) transit);//RJS 22Nov96

		SWord	frametime;
		frametime = Timer_Code.FRAMETIME;		

		if ((transit->LaunchTime-=frametime)<0)
			transit->LaunchTime=0;

		SWord launchtime = (SWord )transit->TransRandom;
		launchtime-=frametime;

		if (transit->Target)
		{
			transit->World.X = transit->Target->World.X + SWord(transit->hdg);
			transit->World.Y = transit->Target->World.Y + SWord(transit->pitch);
			transit->World.Z = transit->Target->World.Z + SWord(transit->roll);
			transit->uniqueID.changed = TRUE;			//RJS 09Dec98
		}

/*		if (launchtime<=0)
		{
			TransientItem*	newitem;

			newitem = SimplifiedSpriteLaunch(	transit,
												SmokinShape,
												LIFETIME_SMOKE,MOBILE_STATIONARY);//RJS 20Apr98
			if (newitem)
			{
				//Give the smoke particle some vertical velocity

				UWord	randomfactor;
				SLong	vvel;

				randomfactor = Math_Lib.rnd();

				newitem->vely = SmokeBaseVel + ((randomfactor * SmokeVariableVertVel * 2)>>16);
				newitem->pitch= ANGLES_90Deg;

				newitem->World.Y += 500;						//RJS 18Sep96

				newitem->hdg = (Angles)(Math_Lib.rnd());

				SWord	sin_ang,cos_ang;

				Math_Lib.high_sin_cos((ANGLES )newitem->hdg,sin_ang,cos_ang);

				randomfactor = Math_Lib.rnd();

				newitem->velhori = ((randomfactor * SmokeVariableHorzVel)>>16);

				AddTransientItemToWorld(newitem,world);
			}

			//Drive the shape animation								//PD 08May96

//DeadCode RJS 19Feb98			ExplodeAnimData* adptr;									//PD 08May96
//DeadCode RJS 19Feb98
//DeadCode RJS 19Feb98			adptr = (ExplodeAnimData* )transit->Anim;				//PD 08May96
//DeadCode RJS 19Feb98			adptr->frameno++;										//PD 08May96
//DeadCode RJS 19Feb98
//DeadCode RJS 19Feb98			if (adptr->frameno>7)									//PD 08May96
//DeadCode RJS 19Feb98				adptr->frameno = 0;									//PD 08May96

			launchtime = SmokeLaunchDelay+(TransientItem::transcount>>4);
		}
		transit->TransRandom = (UWord )launchtime;*/
	}
	else
	{
		AddTransientItemToDeadList(transit);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MobileTroop
//Author		Robert Slater
//Date			Mon 1 Jul 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::MobileTroop(TransientItemPtr transit, WorldStuff&)
{
	SLong	timeleft = transit->LaunchTime;
	if (timeleft)
	{
		SWord	frametime = Timer_Code.FRAMETIME;
		SWord	timedist;
		SLong	dx, dy, dz;
		SWord	thehdg;
		SWord	newhdg;
		SWord	hdg2;					
		SLong	distance;


		TroopAnimData*	adptr = (TroopAnimData*) transit->Anim;		//RJS 08Nov96

		if ((transit->LaunchTime-=frametime)<0)
			transit->LaunchTime=0;

		timedist = SWord(transit->TransRandom);
		timedist -= frametime;
		if (timedist < 0)
		{
			transit->TransRandom = 50;

			if (adptr->homing)
			{
				dx = adptr->xpos - transit->World.X;			//RJS 26Nov96
				dy = adptr->ypos - transit->World.Y;			//RJS 26Nov96
				dz = adptr->zpos - transit->World.Z;			//RJS 26Nov96

				distance = Math_Lib.distance3d(dx,dy,dz);		//RJS 16Nov98
				thehdg = Math_Lib.arctan(dx,dz);				//RJS 16Nov98

				if (adptr->oncourse == FALSE)
				{
					hdg2 = transit->hdg;				
					newhdg = (thehdg - hdg2) >> 1;				//RJS 16Nov98

					if (newhdg == 0)
					{
						adptr->oncourse = TRUE;
						transit->hdg = (Angles) thehdg;
					}
					else
					{
						hdg2 += newhdg;							//RJS 16Nov98
						transit->hdg = (Angles) hdg2;			//RJS 21Nov96
					}
				}

				if (distance < 100)								//RJS 16Nov98
					transit->LaunchTime = 0;					//RJS 16Nov98
			}
			else
				transit->hdg = (Angles) (transit->hdg + Math_Lib.rnd(ANGLES_45Deg) - ANGLES_22Deg);//RJS 16Nov98
		}
		else
			transit->TransRandom = UWord(timedist);

		UWord	voxrand = Math_Lib.rnd();
		if (voxrand > 65000)
		{
			voxrand = ((65536 - voxrand)*3)/536;
			if (transit->shape != BlokeFireShape)
				_Miles.PlayOnce((FileNum)(FIL_SFX_VOCAL_ENEMY1 + voxrand),transit,48,FIL_SFX_VOCAL_ENEMY1,FIL_SFX_VOCAL_ENEMY4);
			else
				_Miles.PlayOnce((FileNum)(FIL_SFX_YELP1 + voxrand),transit,48,FIL_SFX_YELP1,FIL_SFX_YELP4);
//DeadCode DAW 25Jun99 			_Miles.PlayOnce((FileNum)(FIL_SFX_VOCAL_ENEMY1 + voxrand),transit,48,FIL_SFX_VOCAL_ENEMY1,FIL_SFX_VOCAL_ENEMY4);
		}

		ApplyVelocities((mobileitem*) transit);

		transit->pitch = ANGLES_0Deg;

		if ((timeleft & 0x06)==0)
			transit->World.Y = GetGroundLevel(transit);			//RJS 14Apr99
	}
	else
		AddTransientItemToDeadList(transit);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MobileParachute
//Author		Robert Slater
//Date			Tue 2 Jul 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void TransObj::MobileParachute(TransientItemPtr transit, WorldStuff&	world)
{
	SLong	timeleft = transit->LaunchTime;
	SLong	timedist;

	if (timeleft)
	{
		if ((transit->LaunchTime-=Timer_Code.FRAMETIME)<0)
			transit->LaunchTime=0;

//DeadCode RJS 31May99 		if ((transit->shape == DUMY18) || (transit->shape == CHUTE2))
		//must be the chute...
		if (!transit->isOwned)									//DAW 31May99
		{
			TransientItemPtr	transitmaster = (TransientItemPtr) transit->Target;
			if (transitmaster)
			{
				SWord				randno = transitmaster->TransRandom;
				if (randno < 0)
				{
					if (transit->TransRandom == 0)
					{
						SHAPE.ResetAnimData_NewShape(transit,CHUTE2);	//This should also reset the morph time...
						transit->TransRandom = 1;												//RJS 16Nov98
						transit->LaunchTime = 300;		//give chute 3 secs to collapse
						transit->World = transitmaster->World;		//RJS 23Apr99
						transit->uniqueID.changed = TRUE;			//RJS 23Apr99
					}
				}
			}
		}
		else
		{
			if (transit->TransRandom != 65535)
			{
				UByte	theArea;
				SLong	groundheight = GetGroundLevel(transit,theArea);//RJS 29Apr99

				if (transit->TransRandom > 0)
				{
					SWord	thepitch = transit->pitch;
					SWord	theroll = transit->roll;
					SWord	abspitch = thepitch;
					SWord	absroll = theroll;
					SWord	pinc = 0;
					SWord	rinc = 0;
					bool	doneone = false;

					GAndFriction(transit,OrdinaryDrag);

					pinc = 128;									//RJS 29Apr99
					if (abspitch < 0)							//RJS 21Apr99
					{											//RJS 21Apr99
						abspitch = -abspitch;					//RJS 21Apr99
						pinc = -pinc;							//RJS 21Apr99
					}											//RJS 21Apr99
																//RJS 21Apr99
					rinc = 128;									//RJS 29Apr99
					if (absroll < 0)							//RJS 21Apr99
					{											//RJS 21Apr99
						absroll = -absroll;						//RJS 21Apr99
						rinc = -rinc;							//RJS 21Apr99
					}											//RJS 21Apr99
																//RJS 21Apr99
					if (abspitch > pinc)						//RJS 21Apr99
					{
						thepitch -= pinc;
						doneone = true;
					}

					if (absroll > rinc)							//RJS 21Apr99
					{
						theroll -= rinc;
						doneone = true;
					}

					transit->pitch = (Angles) thepitch;
					transit->roll = (Angles) theroll;

					if ((transit->vely < -200) && (doneone==false))
					{
						TransientItem*	newitem;
						ParachuteAnimData* adptr = (ParachuteAnimData*) transit->Anim;
						bool				dropChair = true;
						
						if (adptr->OTHER)
							dropChair = false;

						SHAPE.ResetAnimData_NewShape(transit,PCHUTE);	//This should also reset the morph time...

						if (((AirStrucPtr)transit->Launcher)->AcIsPlayer())
							View_Object->Quit3D(2000);							//RJS 11May99

						transit->roll = ANGLES_0Deg;
						transit->TransRandom = 0;
			
						_Miles.PlayOnce(FIL_SFX_PARACHUTE_OPEN,transit);

						//Launch the chute...
						newitem = LaunchGuidedMissile(	transit,
														transit,
														DUMY18,
														transit->LaunchTime,
														MOBILE_PARACHUTE	);
						if (newitem)
						{
							//Place in binary tree seperately!
							MinAnimData*	mad = (MinAnimData*)newitem->Anim;
							mad->IsInvisible = 1;

							//allow both chute and bloke to point to each other...
							transit->Target = newitem;
							transit->isOwned = 1;				//RJS 06Jul99

							newitem->TransRandom = 0;
							AddTransientItemToWorld(newitem, world);
						}

						//drop empty seat...
						if (dropChair)									//RJS 10May99
						{
							newitem = LaunchUnguidedMissile(	transit,
																DUMY19,
																600,
																MOBILE_GANDF);
							if (newitem)
							{
								ParachuteAnimData* adptr = (ParachuteAnimData*) newitem->Anim;
								adptr->BLOKEON = 255;

								AddTransientItemToWorld(newitem, world);
							}
						}
					}
				}
				else
				{
					GAndFriction(transit,RetardedDrag,OrdinaryDrag);//RJS 05May99
					transit->pitch = ANGLES_0Deg;				//RJS 23Mar99

					_Miles.PlayLooped(FIL_SFX_PARACHUTE_LOOP,transit);
				}

				AddWindDrift(transit);									//RJS 07Jan97

				if (transit->World.Y <= groundheight)
				{
					UWord	randpoo = Math_Lib.rnd() >> 16;

					transit->World.Y = groundheight;

					if (transit->Target)			//does it have chute?
						_Miles.PlayOnce((FileNum)(FIL_SFX_PARACHUTE_OOF1 + randpoo),transit);
					else
						_Miles.PlayOnce(FIL_SFX_YELP5,transit);

					switch (theArea)
					{
					case AT_sea:
					case AT_river:
					case AT_washShore:
						_Miles.PlayOnce(FIL_SFX_RICOCHET_WATER,transit);
						LaunchSplashSmall((mobileitem*)transit,world);
						break;
					default:
						_Miles.PlayOnce(FIL_SFX_PARACHUTE_LAND_GROUND,transit);
						LaunchDustRing(transit,world);
						break;
					}

					if (transit->shape == PCHUTE)
						transit->pitch = ANGLES_270Deg;

					transit->LaunchTime = 300;
	
					transit->TransRandom = 65535;
				}
			}
		}
	}
	else
	{
		//This bit has been re-written!							//RJS 31May99
		//Again...
		bool		killnow = true;								//RJS 25May99
		ShapeDescPtr	sdptr = SHAPESTUFF.GetShapePtr(transit->shape);//RJS 06Jul99
		if (sdptr->AnimDataSize == PARACHUTEANIM)		//must be the pilot//RJS 06Jul99
		{
			//Does he have an active chute?
			if (transit->Target)
			{
				//Kill the chute...
				TransientItem*	targ = (TransientItem*) *transit->Target;
				targ->Target = NULL;
				targ->LaunchTime = 0;
				targ->isOwned = 0;								//RJS 06Jul99

				transit->Target = NULL;
			}

			AirStrucPtr	theLauncher = (AirStrucPtr)*transit->Launcher;
			if (theLauncher->AcIsPlayer())
			{
				//Exit the 3d....
				killnow = false;
				View_Object->Quit3D(0);
			}
			else
				transit->isOwned = 0;
		}
		else
		{
			//Does the chute have a pilot?
			if (transit->Target)								//RJS 06Jul99
			{
				TransientItem*	targ = (TransientItem*) *transit->Target;
			
				killnow = false;

				targ->Target = NULL;
				targ->LaunchTime = 0;

				transit->Target = NULL;
				transit->isOwned = 0;
			}
		}

		if (killnow)
			AddTransientItemToDeadList(transit);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MobileBarage
//Author		Robert Slater
//Date			Fri 5 Jul 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void TransObj::MobileBarage(TransientItemPtr transit, WorldStuff&	world)
{
	// All re-jigged by ROB											//RJS 05Oct98
	SLong	timeleft = transit->LaunchTime;							//RJS 05Oct98
	SWord	frametime = Timer_Code.FRAMETIME;						//RJS 05Oct98

	if (timeleft)													
	{
		if ((transit->LaunchTime-=frametime)<0)
			transit->LaunchTime=0;
	}
	else
	{
		SLong	groundheight = GetGroundLevel(transit) + METRES01;//RJS 14Apr99

		transit->World.Y = groundheight;						//RDH 29Nov98

		_Miles.PlaySample((FileNum) (FIL_SFX_EXPLOSION_TANK+Math_Lib.rnd(3)), (ItemBasePtr) transit);//RJS 22Nov96
		if (transit->Status.Drawn == 1)							//RJS 05Oct98
		{														//RJS 05Oct98
			if (Math_Lib.rnd() > 32768)							//MS 30Nov98
				LaunchSmallFlash((mobileitem*)transit,world);	//RJS 08Dec98
			else
			{
				LaunchFlash((mobileitem*)transit,0,world);		//MS 30Nov98
				LaunchDirtMedium((mobileitem*)transit,world);	//MS 30Nov98
			}
		}

		AddTransientItemToDeadList(transit);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MobileDelayedExplosion
//Author		Robert Slater
//Date			Fri 5 Jul 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void TransObj::MobileDelayedExplosion(TransientItemPtr transit, WorldStuff& worldptr)
{
	SLong	timeleft = transit->LaunchTime;
	SWord	frametime;

	frametime = Timer_Code.FRAMETIME;							//DAW 31Jul96

	if (timeleft && transit->Target)
	{
		transit->World.X = transit->Target->World.X;
		transit->World.Y = transit->Target->World.Y;
		transit->World.Z = transit->Target->World.Z;			//RJS 03Dec96
		transit->uniqueID.changed = TRUE;			//RJS 09Dec98

		if ((transit->LaunchTime-=frametime)<0)
			transit->LaunchTime=0;
	}
	else
	{
		// Is it a dummy explosion, or a live explosion?..
		switch (transit->TransRandom)
		{
			case 1:
				AddTransientItemToDeadList(transit);
				break;
			case 2:
			{
				// Launch explosive!!
				TransientItem*	newitem = SimplifiedSpriteLaunch(	transit->Launcher,
																	ExplosionThugShape,
																	0,
																	MOBILE_DELEXP	);
				if (newitem)
				{
					//Inherit old target as well as coords...
					newitem->Target = transit->Target;			//RJS 24Jun99
					newitem->World = transit->Target->World;
					newitem->TransRandom = 3;		//Detonate!!

					AddTransientItemToWorld(newitem,worldptr);
				}

				AddTransientItemToDeadList(transit);
				break;
			}
			case 3:
			{
				// Ignite explosive!!
				BoxCol::SpecificCollision(transit,transit->Target);
				AddTransientItemToDeadList(transit);
			}
			break;
			case 4:
			{
				AirStrucPtr	ac = (AirStrucPtr)*transit->Target;
				if (!_Replay.Playback)
					ExplodeAC(ac,ac,worldptr);
				else
				{
					LaunchBigExplosion(ac,worldptr,ac->shape);
					LaunchFingers(ac,worldptr);
				}

				LaunchFire(ac,worldptr);

				AddTransientItemToDeadList(transit);
			}
			break;
			default:
			{
				if (WithinVisibleRange(transit->World,300000))	//RJS 30Apr99
				{
					MinAnimData*	mad = (MinAnimData*) transit->Anim;
					mad->IsInvisible = 0;

					_Miles.PlaySample((FileNum) (FIL_SFX_EXPLOSION_GROUND+Math_Lib.rnd(5)), (ItemBasePtr) transit);//RJS 05Dec96

					transit->LaunchTime = 100;
					transit->TransRandom = 1;

					LaunchSkinDebris(transit,worldptr);
				}
			}
			break;
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MobileFlak
//Author		Robert Slater
//Date			Fri 5 Jul 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void TransObj::MobileFlak(TransientItemPtr transit, WorldStuff& worldptr)
{
	//All rewritten by Rob										//RJS 29Apr99
	SLong	timeleft = transit->LaunchTime;
	if (timeleft)
	{
		if ((transit->LaunchTime-=Timer_Code.FRAMETIME)<0)
			transit->LaunchTime=0;

		AddWindDrift(transit);
	}
	else
	{
//DEADCODE DAW 06/05/99		ShapeNum		theShape = ((TransientItem*)transit->Launcher)->shape;
		TransientItem*	newitem;

		newitem = SimplifiedSpriteLaunch(transit,transit->shape,250,MOBILE_STATIONARY);//RJS 06May99
		if (newitem)
		{
			_Miles.PlaySample((FileNum)(FIL_SFX_FLAK1+Math_Lib.rnd(3)),newitem);

			AddTransientItemToWorld(newitem,worldptr);
		}

		AddTransientItemToDeadList(transit);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MobileSparkTrail
//Author		Robert Slater
//Date			Fri 5 Jul 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void TransObj::MobileSparkTrail(TransientItemPtr transit, WorldStuff& worldptr)
{
	SLong	timeleft = transit->LaunchTime;
	if (timeleft)
	{
		SWord	frametime = Timer_Code.FRAMETIME;
		if ((transit->LaunchTime-=frametime)<0)
			transit->LaunchTime=0;

		if (transit->TmpLaunchTime && (transit->TmpLaunchTime != 65535))//RJS 19May99
		{														//RJS 14May99
			timeleft = transit->TmpLaunchTime;					//RJS 19May99
			timeleft -= frametime;								//RJS 14May99
			if (timeleft < 0)									//RJS 14May99
				timeleft = 0;									//RJS 14May99
																//RJS 14May99
			transit->TmpLaunchTime = timeleft;					//RJS 19May99
		}														//RJS 14May99
	}
	else
	{
		if (transit->Target)
		{
			mobileitem*	parent = (mobileitem*) transit->Target;

			if (	(parent->movecode == MOBILE_NOPPILOT)		//RJS 28Jun99
				||	(parent->movecode == AUTO_RESURRECT)		//RJS 28Jun99
				||	(transit->TmpLaunchTime==0)				)	//RJS 28Jun99
				AddTransientItemToDeadList(transit);
			else
			{
				if (WithinVisibleRange(parent->World,100000))	//RJS 30Apr99
				{
					UWord	theShape = transit->TransRandom & 0x7FFF;

					// Throw sparks, or dirt...
					SLong	maxlife = Math_Lib.rnd(100) * (MPH100 - parent->velhori);
					maxlife /= MPH100;
					maxlife += ((MPH100-parent->velhori)*50)/MPH100;
					if (maxlife < 0)
						maxlife = Math_Lib.rnd(30);

					transit->LaunchTime = maxlife;

					maxlife = transit->pitch;
					maxlife>>=1;
					maxlife += Math_Lib.rnd(maxlife);

					TransientItemPtr	newitem;
					newitem = SimplifiedSpriteLaunch(	parent,
														(ShapeNum)theShape,
														maxlife,
														MOBILE_GANDF);

					if (newitem)
					{
						if ((transit->TransRandom & 0x8000)==0)
						{
							//we are above ground...
							if (transit->hdg)
							{
								newitem->vely = 100 + Math_Lib.rnd(100);
								newitem->velhori = 200 - newitem->vely;
								newitem->hdg = (Angles)(Math_Lib.rnd(ANGLES_180Deg) - parent->hdg);
							}
							else
							{
								newitem->velhori = Math_Lib.rnd(100);
								newitem->hdg = (Angles)(Math_Lib.rnd(ANGLES_90Deg) - parent->hdg - ANGLES_45Deg);
								newitem->movecode = MOBILE_STATIONARY;
							}
						}
						else
						{
							//just let float on the ground...
							newitem->movecode = MOBILE_STATIONARY;
							newitem->World.Y += 200;
						}

						AddTransientItemToWorld(newitem,worldptr);
					}
				}
			}
		}
		else
			AddTransientItemToDeadList(transit);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MobileRicochetSmoke
//Author		Robert Slater
//Date			Thu 5 Sep 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void TransObj::MobileRicochetSmoke(TransientItemPtr transit, WorldStuff& worldptr)
{
	SLong	timeleft = transit->LaunchTime;

	if (timeleft)
	{
		SWord	frametime;

		frametime = Timer_Code.FRAMETIME;						

		if ((transit->LaunchTime-=frametime)<0)
			transit->LaunchTime=0;

//DeadCode MS 30Nov98		if (transit->TransRandom == 0)							//RJS 20Apr98
//DeadCode MS 30Nov98		{
//DeadCode MS 30Nov98			//Test for collision with the ground
//DeadCode MS 30Nov98			SLong	groundheight = Land_Scape.GetGroundLevel((itemptr)transit);
//DeadCode MS 30Nov98
//DeadCode MS 30Nov98			if (transit->World.Y < groundheight)
//DeadCode MS 30Nov98			{
//DeadCode MS 30Nov98				transit->TransRandom = 1;
//DeadCode MS 30Nov98				transit->World.Y = groundheight;
//DeadCode MS 30Nov98			}
//DeadCode MS 30Nov98		}

		if (transit->velhori)									//RDH 30Mar99
			GAndFriction(transit,0);							//RDH 30Mar99
	}
	else
	{
		AddTransientItemToDeadList(transit);
	}
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MobileGuidedExplosion
//Author		Robert Slater
//Date			Mon 8 Jul 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void TransObj::MobileGuidedExplosion(TransientItemPtr transit, WorldStuff& worldptr)
{
	SLong	timeleft = transit->LaunchTime;
	SWord	frametime;

	frametime = Timer_Code.FRAMETIME;							//DAW 31Jul96

	if (timeleft && transit->Target)
	{
		transit->World.X = transit->Target->World.X;
		transit->World.Y = transit->Target->World.Y;
		transit->World.Z = transit->Target->World.Z;
		transit->uniqueID.changed = TRUE;			//RJS 09Dec98

		if ((transit->LaunchTime-=frametime)<0)
			transit->LaunchTime=0;

		SLong	groundheight;
		groundheight = GetGroundLevel(transit);					//RJS 14Apr99

		if (transit->World.Y<=groundheight)
			transit->World.Y = groundheight;
	}
	else
		AddTransientItemToDeadList(transit);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MobileGuidedBurning
//Author		Robert Slater
//Date			Mon 8 Jul 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void TransObj::MobileGuidedBurning(TransientItemPtr transit, WorldStuff& worldptr)
{
	SLong		timeleft = transit->LaunchTime;					//RJS 16Nov98
	ItemPtr		thetarget = transit->Target;						//RJS 16Nov98
	
	if (timeleft)
	{
		_Miles.PlayLooped(FIL_SFX_SMALL_FIRE_LOOP, (ItemBasePtr) transit);//RJS 22Nov96
		SWord	frametime;

		frametime = Timer_Code.FRAMETIME;						//DAW 31Jul96

		if ((transit->LaunchTime-=frametime)<0)
			transit->LaunchTime=0;

		transit->World.X = thetarget->World.X - 50;					//RJS 23Jul96
		transit->World.Y = thetarget->World.Y + 30;					//RJS 23Jul96
		transit->World.Z = thetarget->World.Z + 70;					//RJS 23Jul96
		transit->uniqueID.changed = TRUE;			//RJS 09Dec98

		//Test for collision with the ground

		SLong	groundheight;

		groundheight = GetGroundLevel(transit);					//RJS 14Apr99

		if (transit->World.Y<groundheight)
			transit->World.Y = groundheight;
	}
	else
		AddTransientItemToDeadList(transit);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MobileGuidedFire
//Author		Robert Slater
//Date			Tue 9 Jul 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void TransObj::MobileGuidedFire(TransientItemPtr transit, WorldStuff& worldptr)
{
	SLong	timeleft = transit->LaunchTime;

	if (timeleft && transit->Target)
	{
		_Miles.PlayLooped((FileNum) FIL_SFX_FIREBURN_LOOP, (ItemBasePtr) transit);//RJS 22Nov96

		SWord	frametime;

		frametime = Timer_Code.FRAMETIME;						//DAW 31Jul96

		if ((transit->LaunchTime-=frametime)<0)
			transit->LaunchTime=0;

		transit->World.X = transit->Target->World.X;
		transit->World.Y = transit->Target->World.Y;
		transit->World.Z = transit->Target->World.Z;
		transit->uniqueID.changed = TRUE;			//RJS 09Dec98

		//Test for collision with the ground

		SLong	groundheight;

		groundheight = GetGroundLevel(transit);					//RJS 14Apr99

		if (transit->World.Y<groundheight)
			transit->World.Y = groundheight;
	}
	else
		AddTransientItemToDeadList(transit);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MobileATeam
//Author		Robert Slater
//Date			Wed 10 Jul 1996
//
//Description	Throw an exploded object in the air 'A Team' style
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void TransObj::MobileATeam(TransientItemPtr transit, WorldStuff& worldptr)
{
	ItemPtr	theLauncher = transit->Launcher;
	UWord	animoff = transit->TransRandom;
	SLong	timeleft = transit->LaunchTime;
	if (timeleft)
	{
		SWord	frametime = Timer_Code.FRAMETIME;

		if ((transit->LaunchTime-=frametime)<0)
			transit->LaunchTime=0;

		// Are we already on the ground?
		if ((animoff & 0x8000)==0)
		{
			SWord	oldhdg = transit->hdg;

			transit->hdg = (Angles) transit->velx;

			GAndFrictionFixedPitch(transit,OrdinaryDrag);

			transit->hdg = (Angles) oldhdg;

			SWord	hdgmag,pitchmag;

			hdgmag = transit->velz >> 8;
			pitchmag = transit->velz & 0xFF;

			transit->roll += (Angles) hdgmag;
			transit->pitch += (Angles) pitchmag;

			if ((transit->LaunchTime & 0x06)==0)
			{
				UByte	theArea;
				SLong	groundheight = GetGroundLevel(transit,theArea);//RJS 28Apr99
				if (transit->World.Y <= groundheight)
				{
//DeadCode RJS 28Apr99					UByte	theArea = Three_Dee.GetLandType();		//RJS 27Nov98

					Coords3D	hitcoords;

					transit->World.Y = groundheight;
					transit->TransRandom |= 0x8000;

					hitcoords = transit->World;

					DoImpactGround(transit,hitcoords,theArea);	//MS 30Nov98

					ShapeDescPtr	sdptr = SHAPESTUFF.GetShapePtr(theLauncher->shape);
					if (SHAPESTUFF.GetShapeScale(sdptr) != SHP_GRP)
					{
						// oooh... we can properly nobble its world coords...

						theLauncher->World = transit->World;
						theLauncher->uniqueID.changed = TRUE;
						if (theLauncher->Status.size >= RotatedSize)
						{
							rotitem*	tmpitm = (rotitem*) theLauncher;

							tmpitm->hdg = transit->hdg;
							tmpitm->pitch = transit->pitch;
							tmpitm->roll = transit->roll;
						}

						transit->LaunchTime = 0;	//kill now
					}
				}
			}
		}

//		if ((theLauncher->Status.size >= MovingSize) && (Math_Lib.rnd() > 62000))
//		{
//			TransientItemPtr	newitem;
//			newitem = SimplifiedSpriteLaunch((mobileitem*)transit,SMKFIR,200,MOBILE_STATIONARY);
//			if (newitem)
//				AddTransientItemToWorld(newitem,worldptr);
//		}
	}
	else
	{
		MinAnimData*	mad;
		animptr			adptr = theLauncher->Anim;				//RJS 21Apr99

		adptr += (animoff & 0x7FFF);							//RJS 21Apr99

		mad = (MinAnimData*) adptr;								//RJS 21Apr99
		mad->IsInvisible = 0;	//Turn the element back on...

		// If it can move, it probably still contains fuel...
		if ((mad->itemstate != DEAD) && (theLauncher->Status.size >= MovingSize))
		{
			ShapeDescPtr	sdptr = SHAPESTUFF.GetShapePtr(theLauncher->shape);

			theLauncher->Status.deadtime = sdptr->DeadTime;
			theLauncher->Status.deadscale = sdptr->DeadScale;
			theLauncher->Status.deaded = TRUE;		//RJS 27Feb98

			LaunchDelayedExplosion((mobileitem*)theLauncher,worldptr);
		}

		AddTransientItemToDeadList(transit);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MobileDustRing
//Author		Robert Slater
//Date			Sun 13 Oct 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::MobileDustRing(TransientItemPtr transit, WorldStuff& world)
{
//DeadCode RJS 20Apr98	SLong			timeleft=transit->LaunchTime;
//DeadCode RJS 20Apr98	UByte			count;
//DeadCode RJS 20Apr98
//DeadCode RJS 20Apr98	if (timeleft)
//DeadCode RJS 20Apr98	{
//DeadCode RJS 20Apr98		SWord	frametime;
//DeadCode RJS 20Apr98		SLong	groundheight;
//DeadCode RJS 20Apr98
//DeadCode RJS 20Apr98		frametime = Timer_Code.FRAMETIME;						
//DeadCode RJS 20Apr98
//DeadCode RJS 20Apr98		if ((transit->LaunchTime-=frametime)<0)
//DeadCode RJS 20Apr98			transit->LaunchTime=0;
//DeadCode RJS 20Apr98	}
//DeadCode RJS 20Apr98	else
//DeadCode RJS 20Apr98		AddTransientItemToDeadList(transit);
}

//DeadCode JIM 28Nov96 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode JIM 28Nov96 //Procedure		MobileShockwave
//DeadCode JIM 28Nov96 //Author		Robert Slater
//DeadCode JIM 28Nov96 //Date			Wed 16 Oct 1996
//DeadCode JIM 28Nov96 //
//DeadCode JIM 28Nov96 //Description	Similar to bullet
//DeadCode JIM 28Nov96 //
//DeadCode JIM 28Nov96 //Inputs		
//DeadCode JIM 28Nov96 //
//DeadCode JIM 28Nov96 //Returns	
//DeadCode JIM 28Nov96 //
//DeadCode JIM 28Nov96 //------------------------------------------------------------------------------
//DeadCode JIM 28Nov96 void	TransObj::MobileShockwave(TransientItemPtr transit, WorldStuff& world)
//DeadCode JIM 28Nov96 {
//DeadCode JIM 28Nov96	if ((transit->LaunchTime-=Timer_Code.FRAMETIME)<0)	
//DeadCode JIM 28Nov96		transit->LaunchTime=0;
//DeadCode JIM 28Nov96	else
//DeadCode JIM 28Nov96	{
//DeadCode JIM 28Nov96		if ((transit->LaunchTime & 0x03)==0)			
//DeadCode JIM 28Nov96		{
//DeadCode JIM 28Nov96			SLong	groundheight;
//DeadCode JIM 28Nov96
//DeadCode JIM 28Nov96			groundheight = Land_Scape.GetGroundLevel((itemptr)transit);
//DeadCode JIM 28Nov96
//DeadCode JIM 28Nov96			if (transit->World.Y<=groundheight)
//DeadCode JIM 28Nov96				transit->World.Y = groundheight;
//DeadCode JIM 28Nov96
//DeadCode JIM 28Nov96			//Test for collision with other
//DeadCode JIM 28Nov96			//items
//DeadCode JIM 28Nov96
//DeadCode JIM 28Nov96			itemptr	 hititem;
//DeadCode JIM 28Nov96 //DeadCode RDH 26Nov96			vector	 hitvector;
//DeadCode JIM 28Nov96 //DeadCode RDH 26Nov96			SByte	gindex;
//DeadCode JIM 28Nov96			Coords3D	hitcoords;
//DeadCode JIM 28Nov96			int	gindex;
//DeadCode JIM 28Nov96
//DeadCode JIM 28Nov96		if ((transit->LaunchTime & 0x03)==0)					//PD 08Oct96
//DeadCode JIM 28Nov96			if (!transit->Status.deadtime)
//DeadCode JIM 28Nov96			{
//DeadCode JIM 28Nov96				hititem=BoxCol::NineSectorCol(transit,hitcoords,gindex);
//DeadCode JIM 28Nov96				if (hititem)	//_Collide.TransCollTest((MovingItemPtr )transit, hititem, hitvector, gindex))//RDH 26Nov96
//DeadCode JIM 28Nov96				{
//DeadCode JIM 28Nov96					transit->World=hitcoords;
//DeadCode JIM 28Nov96 //DeadCode RDH 26Nov96					transit->World.X = hitvector.a;			
//DeadCode JIM 28Nov96 //DeadCode RDH 26Nov96					transit->World.Y = hitvector.b;			
//DeadCode JIM 28Nov96 //DeadCode RDH 26Nov96					transit->World.Z = hitvector.c;			
//DeadCode JIM 28Nov96
//DeadCode JIM 28Nov96					MissileHitSomething(hititem,transit,world,gindex);
//DeadCode JIM 28Nov96					transit->velhori >>= 1;
//DeadCode JIM 28Nov96				}
//DeadCode JIM 28Nov96			}												
//DeadCode JIM 28Nov96		}
//DeadCode JIM 28Nov96
//DeadCode JIM 28Nov96		if (transit->LaunchTime>0)	
//DeadCode JIM 28Nov96			ApplyVelocities(transit);
//DeadCode JIM 28Nov96	}
//DeadCode JIM 28Nov96
//DeadCode JIM 28Nov96	if (transit->LaunchTime<=0)
//DeadCode JIM 28Nov96		AddTransientItemToDeadList(transit);
//DeadCode JIM 28Nov96 }

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MobileBird
//Author		Robert Slater
//Date			Thu 17 Oct 1996
//
//Description	Realistic movecode for a bird
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::MobileBird(TransientItemPtr transit, WorldStuff& world)
{
	TransientItemPtr	newitem;						
	SLong			timeleft=transit->LaunchTime;

	if (timeleft)
	{
//DeadCode RJS 19Feb98		ExplodeAnimData* adptr;								
		SWord	frametime = Timer_Code.FRAMETIME;
		SLong	groundheight = GetGroundLevel(transit);			//RJS 14Apr99
		UByte	maxframe;

		if ((transit->LaunchTime-=frametime)<0)
			transit->LaunchTime=0;

//DeadCode RJS 19Feb98		adptr = (ExplodeAnimData* )transit->Anim;
//DeadCode RJS 19Feb98		adptr->frameno++;

		GAndFriction(transit,OrdinaryDrag);

		if (transit->shape == BirdShape)
		{
			maxframe = 3;

			if (transit->World.Y <= groundheight)
			{
				transit->World.Y = groundheight + 50;
				transit->vely = 50 + Math_Lib.rnd(100);
			}

			if (transit->vely < -50)
				transit->vely = 50 + Math_Lib.rnd(100);
		}
		else
		{
			maxframe = 1;

			if (transit->World.Y < groundheight)
				transit->World.Y = groundheight;
		}

//DeadCode RJS 19Feb98		if (adptr->frameno > maxframe)
//DeadCode RJS 19Feb98			adptr->frameno = 0;
	}
	else
		AddTransientItemToDeadList(transit);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MobileAmmoBoxes
//Author		Robert Slater
//Date			Thu 17 Oct 1996
//
//Description	Sends sparks, then blows up
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::MobileAmmoBoxes(TransientItemPtr transit, WorldStuff& world)
{
	TransientItemPtr	newitem;						
	SLong			timeleft=transit->LaunchTime;
	UByte			count;

	if (timeleft)
	{
		SWord	frametime;
		SLong	groundheight;
		UWord	triggerspark;

		frametime = Timer_Code.FRAMETIME;						

		if ((transit->LaunchTime-=frametime)<0)
			transit->LaunchTime=0;

		// throw sparks...

//DeadCode RJS 28May99 		triggerspark = Math_Lib.rnd();
//DeadCode RJS 28May99 
//DeadCode RJS 28May99 		if (triggerspark > 60000+(TransientItem::transcount<<4))
		if (Save_Data.desiredfps <= realFrameTime)				//RJS 11Jun99
		{
			newitem = SimplifiedSpriteLaunch((mobileitem*)transit,SparkShape,300,MOBILE_DEBRIS);//RJS 28May99
			if (newitem)
			{
				newitem->hdg = (Angles) Math_Lib.rnd();			
				newitem->vely = 100 + Math_Lib.rnd(100);		
				newitem->velhori = 100 + Math_Lib.rnd(100);			
				newitem->TransRandom = 0;							

				AddTransientItemToWorld(newitem,world);

				_Miles.PlaySample((FileNum) (FIL_SFX_RICOCHET_HARD_SURFACE4+Math_Lib.rnd(4)), (ItemBasePtr) newitem);//RJS 22Nov96
			}
		}
	}
	else
	{
		animptr			duffptr = transit->Launcher->Anim;
		duffptr += transit->TransRandom;

		ShapeNum		shapehit = (ShapeNum) UWord(transit->pitch);	//RJS 20Nov98
		ShapeNum		shapethrow = (ShapeNum) UWord(transit->roll);	//RJS 20Nov98
//		MyGroundVector	gvector;								//RJS 21Nov96
		MinAnimData*	adptr = (MinAnimData* ) duffptr;
//		ShapeDescPtr	sdptr = SHAPESTUFF.GetShapePtr(shapehit);
//		SLong			halfboxes = ((sdptr->Size << 4) / 176) / 2;
		SLong			noboxes = 2 + Math_Lib.rnd(4);

		adptr->itemstate = DEAD;								//RJS 20Nov98

		LaunchBigExplosion((mobileitem*)transit,world,shapehit);//RJS 08Nov96
		_Miles.PlaySample((FileNum) (FIL_SFX_EXPLOSION_AIR1+Math_Lib.rnd(3)), (ItemBasePtr) transit);//RJS 22Nov96

		if (Save_Data.desiredfps > realFrameTime)					//RJS 28May99
			noboxes = 1;										//RJS 28May99

		for (count = 0; count < noboxes; count++)
		{
			newitem = SimplifiedSpriteLaunch(	transit,
												shapethrow,
												LIFETIME_DEBRISLNCHR,
												MOBILE_DEBRIS);
			if (newitem)
			{
				newitem->hdg = (Angles) Math_Lib.rnd();				//RJS 16Aug96
				newitem->roll = (Angles) Math_Lib.rnd();			//RJS 16Aug96
				newitem->pitch = (Angles) Math_Lib.rnd();			//RJS 16Aug96
				newitem->vely = 100 + Math_Lib.rnd(100);			//RJS 16Aug96
				newitem->velhori = 50 + Math_Lib.rnd(50);			//RJS 16Aug96
				newitem->TransRandom = Math_Lib.rnd();				//RJS 16Aug96
				AddTransientItemToWorld(newitem,world);
			}
		}

		AddTransientItemToDeadList(transit);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MobileBigExplosion
//Author		Robert Slater
//Date			Mon 12 Aug 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::MobileBigExplosion(TransientItemPtr transit, WorldStuff& world)
{
	SLong	timeleft = transit->LaunchTime;
	ItemPtr	pTarget = transit->Target;

	if (timeleft)
	{
//DeadCode DAW 28Jun99 		_Miles.PlayLooped((FileNum) FIL_SFX_FIREBURN_LOOP, (ItemBasePtr) transit);//RJS 22Nov96

		SWord	frametime = Timer_Code.FRAMETIME;						//RJS 16Nov98

		if ((transit->LaunchTime-=frametime)<=0)				//RJS 07Aug97
			transit->LaunchTime=0;								//RJS 07Aug97

		if (pTarget)											//RJS 16Nov98
		{														//DAW 03Sep98
			transit->World.Y = pTarget->World.Y;				//RJS 16Nov98
			transit->World.X = pTarget->World.X;				//RJS 16Nov98
			transit->World.Z = pTarget->World.Z;				//RJS 16Nov98
			transit->uniqueID.changed = TRUE;			//RJS 09Dec98

			_Miles.PlayLooped((FileNum) FIL_SFX_FIREBURN_LOOP, pTarget);//RJS 27Jun99
		}														//DAW 03Sep98
	}
	else
	{
//DeadCode RJS 28Jun99 		if (pTarget)											//RJS 16Nov98
//DeadCode RJS 28Jun99 		{														//RJS 16Nov98
//DeadCode RJS 28Jun99 			if (pTarget->shape == PDEATH)						//RJS 16Nov98
//DeadCode RJS 28Jun99 				LaunchFire((mobileitem*)pTarget,world);			//RJS 16Nov98
//DeadCode RJS 28Jun99 		}														//RJS 16Nov98

		AddTransientItemToDeadList(transit);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MobileMushroomCloud
//Author		Robert Slater
//Date			Wed 6 Nov 1996
//
//Description	Nothing to do with mushroom clouds.....
//
//				Is actually a dummy bomb movecode...	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::MobileDummyBomb(TransientItemPtr transit, WorldStuff& world)
{
	SLong	timeleft = transit->LaunchTime;
	if (timeleft)
	{
		SWord	frametime = Timer_Code.FRAMETIME;

		if ((transit->LaunchTime-=frametime)<0)
			transit->LaunchTime=0;

		GAndFriction(transit,OrdinaryDrag);

		if (transit->TransRandom > timeleft)
		{
			_Miles.PlaySample(FIL_SFX_BOMB_WHISTLE,transit);
			transit->TransRandom = 0;
		}

		// While frametime is in 50ths
		if ((transit->LaunchTime & 0x06)==0)	
		{
			//Test for collision with the ground

			SLong	groundheight = GetGroundLevel(transit);		//RJS 14Apr99
			if (transit->World.Y<groundheight)
			{
				transit->World.Y = groundheight;
				transit->LaunchTime = 0;
				_Miles.PlaySample((FileNum) (FIL_SFX_EXPLOSION_TANK+Math_Lib.rnd(3)), (ItemBasePtr) transit);//RJS 03Dec96
				//Launch flash??...
			}
		}
	}
	else
		AddTransientItemToDeadList(transit);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MobileVapourTransient
//Author		Robert Slater
//Date			Tue 27 May 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::MobileVapourTransient(TransientItemPtr	transit, WorldStuff&	world)
{
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MobileRocket
//Author		Robert Slater
//Date			Wed 4 Jun 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::MobileRocket(TransientItemPtr	transit, WorldStuff&	world)
{
//DeadCode MS 30Nov98	SLong	timeleft = transit->LaunchTime;
//DeadCode MS 30Nov98	if (timeleft)
//DeadCode MS 30Nov98	{
//DeadCode MS 30Nov98		if ((transit->LaunchTime-=Timer_Code.FRAMETIME)<0)
//DeadCode MS 30Nov98			transit->LaunchTime = 0;
//DeadCode MS 30Nov98
//DeadCode MS 30Nov98		if ((transit->LaunchTime & 0x06)==0)					//RJS 09Nov98
//DeadCode MS 30Nov98		{
//DeadCode MS 30Nov98			itemptr		hititem;
//DeadCode MS 30Nov98			Coords3D	hitcoords;
//DeadCode MS 30Nov98			int			gindex;
//DeadCode MS 30Nov98
//DeadCode MS 30Nov98			if (transit->Status.deadtime == 0)					
//DeadCode MS 30Nov98			{
//DeadCode MS 30Nov98				hititem=BoxCol::NineSectorCol(transit,hitcoords,gindex);
//DeadCode MS 30Nov98				if (hititem)
//DeadCode MS 30Nov98				{
//DeadCode MS 30Nov98					transit->LaunchTime=0;								
//DeadCode MS 30Nov98					transit->TransRandom = 2;
//DeadCode MS 30Nov98				}
//DeadCode MS 30Nov98				else
//DeadCode MS 30Nov98				{
//DeadCode MS 30Nov98					SLong	groundheight = Land_Scape.GetGroundLevel(transit);
//DeadCode MS 30Nov98					if (transit->World.Y<=groundheight)
//DeadCode MS 30Nov98					{
//DeadCode MS 30Nov98						UByte	theArea = Three_Dee.GetLandType();//MS 30Nov98
//DeadCode MS 30Nov98
//DeadCode MS 30Nov98						transit->LaunchTime=0;								
//DeadCode MS 30Nov98						transit->TransRandom = 2;
//DeadCode MS 30Nov98
//DeadCode MS 30Nov98						hitcoords = transit->World;
//DeadCode MS 30Nov98						hitcoords.Y = groundheight+METRES01;
//DeadCode MS 30Nov98																			
//DeadCode MS 30Nov98						DoImpactGround(transit,hitcoords,theArea);//MS 30Nov98
//DeadCode MS 30Nov98					}
//DeadCode MS 30Nov98				}
//DeadCode MS 30Nov98			}
//DeadCode MS 30Nov98		}														//RJS 09Nov98
//DeadCode MS 30Nov98
//DeadCode MS 30Nov98		if (transit->LaunchTime)
//DeadCode MS 30Nov98		{
//DeadCode MS 30Nov98			switch (transit->TransRandom)
//DeadCode MS 30Nov98			{
//DeadCode MS 30Nov98				case 0:
//DeadCode MS 30Nov98				case 2:
//DeadCode MS 30Nov98					GAndFriction(transit,OrdinaryDrag);
//DeadCode MS 30Nov98					break;
//DeadCode MS 30Nov98				case 1:
//DeadCode MS 30Nov98					SLong	velx, vely, velz, velhori;
//DeadCode MS 30Nov98					SWord	sin_ang, cos_ang;
//DeadCode MS 30Nov98					SLong	accel = 16;				// crap val
//DeadCode MS 30Nov98
//DeadCode MS 30Nov98					Math_Lib.high_sin_cos((ANGLES )transit->pitch,sin_ang,cos_ang);
//DeadCode MS 30Nov98					vely = (accel * sin_ang)>>15;
//DeadCode MS 30Nov98					velhori = (accel * cos_ang)>>15;
//DeadCode MS 30Nov98
//DeadCode MS 30Nov98					transit->vely += vely;
//DeadCode MS 30Nov98					transit->velhori += velhori;
//DeadCode MS 30Nov98
//DeadCode MS 30Nov98					Math_Lib.high_sin_cos((ANGLES )transit->hdg,sin_ang,cos_ang);
//DeadCode MS 30Nov98
//DeadCode MS 30Nov98					velx = (transit->velhori * sin_ang)>>15;
//DeadCode MS 30Nov98					velz = (transit->velhori * cos_ang)>>15;
//DeadCode MS 30Nov98
//DeadCode MS 30Nov98					transit->velx = velx;
//DeadCode MS 30Nov98					transit->velz = velz;
//DeadCode MS 30Nov98
//DeadCode MS 30Nov98					GAndFriction(transit,OrdinaryDrag);
//DeadCode MS 30Nov98
//DeadCode MS 30Nov98					break;
//DeadCode MS 30Nov98			}
//DeadCode MS 30Nov98		}
//DeadCode MS 30Nov98	}
//DeadCode MS 30Nov98	else
//DeadCode MS 30Nov98	{
//DeadCode MS 30Nov98		switch (transit->TransRandom)
//DeadCode MS 30Nov98		{
//DeadCode MS 30Nov98		case 0:
//DeadCode MS 30Nov98		{
//DeadCode MS 30Nov98			MoveGunAnimData	*adptr = (MoveGunAnimData*)transit->Anim;
//DeadCode MS 30Nov98			WeapAnimData*	weapon = (WeapAnimData*) &adptr->weaponlaunchers[0];
//DeadCode MS 30Nov98
//DeadCode MS 30Nov98			SHAPE.InitTrailFields((UByteP)weapon,0,5000,LT_FUEL);
//DeadCode MS 30Nov98
//DeadCode MS 30Nov98			transit->LaunchTime = 500;
//DeadCode MS 30Nov98			transit->TransRandom = 1;
//DeadCode MS 30Nov98
//DeadCode MS 30Nov98			_Miles.PlayOnce(FIL_SFX_MISSILE2, transit);
//DeadCode MS 30Nov98			LaunchVapourStream((UByteP)weapon,transit->shape);
//DeadCode MS 30Nov98			break;
//DeadCode MS 30Nov98		}
//DeadCode MS 30Nov98		case 1:
//DeadCode MS 30Nov98		{
//DeadCode MS 30Nov98			transit->LaunchTime = 3000;
//DeadCode MS 30Nov98			transit->TransRandom = 2;
//DeadCode MS 30Nov98			break;
//DeadCode MS 30Nov98		}
//DeadCode MS 30Nov98		default:
//DeadCode MS 30Nov98		{
//DeadCode MS 30Nov98			AddTransientItemToDeadList(transit);
//DeadCode MS 30Nov98			break;
//DeadCode MS 30Nov98		}
//DeadCode MS 30Nov98		}
//DeadCode MS 30Nov98	}

	SLong	timeleft = transit->LaunchTime;
	if (timeleft)
	{
		if ((transit->LaunchTime-=Timer_Code.FRAMETIME)<0)
			transit->LaunchTime = 0;

		if ((transit->LaunchTime & 0x06)==0)					
		{
			itemptr		hititem;
			Coords3D	hitcoords;
			int			gindex;

			if (transit->Status.deadtime == 0)					
			{
				hititem=BoxCol::NineSectorCol(transit,hitcoords,gindex);
				if (hititem)
				{
					transit->LaunchTime=0;								
//DeadCode RJS 26Feb99					transit->TransRandom = 2;
				}
				else
				{
					UByte	theArea;
					SLong	groundheight = GetGroundLevel(transit,theArea);//RJS 28Apr99
					if (transit->World.Y<=groundheight)
					{
//DeadCode RJS 28Apr99						UByte	theArea = Three_Dee.GetLandType();//MS 30Nov98

						transit->LaunchTime=0;								
//DeadCode RJS 26Feb99						transit->TransRandom = 2;

						hitcoords = transit->World;
						hitcoords.Y = groundheight+METRES01;
																			
						DoImpactGround(transit,hitcoords,theArea);//MS 30Nov98
					}
				}
			}
		}														//RJS 09Nov98

		SWord	burntime = SWord(transit->TransRandom);			//RJS 26Feb99
		if (!burntime)											//RJS 15Jun99
			GAndFriction(transit,0);							//RJS 26Feb99
		else													//RJS 26Feb99
		{														//RJS 26Feb99
			ApplyVelocities(transit);							//RJS 26Feb99

			burntime -= Timer_Code.FRAMETIME;					//RJS 15Jun99
			if (burntime <= 0)									//RJS 15Jun99
			{													//RJS 15Jun99	
				burntime = 0;									//RJS 15Jun99
				SHAPE.DetatchAllVapourStreams(transit,400);		//RJS 15Jun99
			}													//RJS 15Jun99
			transit->TransRandom = UWord(burntime);				//RJS 26Feb99
		}														//RJS 26Feb99
	}
	else
		AddTransientItemToDeadList(transit);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴|컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MobileCloneGun
//Author		Robert Slater
//Date			Mon 22 Sep 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::MobileCloneGun(TransientItemPtr transit, WorldStuff& world)
{
	SLong	timeleft = transit->LaunchTime;

	if (timeleft)
	{
		//Kill some time....

		if ((transit->LaunchTime-=Timer_Code.FRAMETIME)<0)
			transit->LaunchTime=0;
	}
	else
	{
		CloneAnimData*		adptr = (CloneAnimData*) transit->Anim;
		mobileitem			*theShooter = (mobileitem*)adptr->originitm;

		SLong	clonesleft = transit->TransRandom;
		if (clonesleft)
		{
//Dead			CloneAnimData*		adptr = (CloneAnimData*) transit->Anim;
			Coords3D			weappos;
			SLong				index = adptr->weapindex;
			SLong				index2 = adptr->weapindex2;
			WeapAnimData*		weapanim;
			UWord				mvel,mdelay,mburst;				//RDH 31Jul98
//Dead			mobileitem			*theShooter = (mobileitem*)adptr->originitm;
			SLong				velx,vely,velz,velh,vel;//rjs
			ANGLES				hdg,pitch;
			AutoMoveCodeTypeSelect	mcode;
			SLong				theLifetime;
			ShapeNum			theShape = (ShapeNum) adptr->shapename;
			SWord				muzPitch = 0;	// Maybe defined in airstruc
			LnchrType			launchmask = (LnchrType)(adptr->lnchtype & LT_MASK);//RJS 09Jul99
			
			vel = transit->vel;
//DeadCode CSB 26/03/99				if (theShooter->Status.size>=MOBILESIZE)
//DeadCode CSB 26/03/99				{
//DeadCode CSB 26/03/99					SWord	sin_ang,cos_ang;
//DeadCode CSB 26/03/99					SLong	totalvel = theShooter->vel + ;
//DeadCode CSB 26/03/99	
//DeadCode CSB 26/03/99					velh = theShooter->velhori;
//DeadCode CSB 26/03/99					vely = theShooter->vely;
//DeadCode CSB 26/03/99	
//DeadCode CSB 26/03/99					muzPitch += (SWord) theShooter->pitch;			//RJS 21Jul98
//DeadCode CSB 26/03/99	
//DeadCode CSB 26/03/99					hdg = theShooter->hdg;
//DeadCode CSB 26/03/99					pitch = (Angles) muzPitch;						//RJS 21Jul98
//DeadCode CSB 26/03/99					Math_Lib.high_sin_cos(pitch,sin_ang,cos_ang);
//DeadCode CSB 26/03/99	
//DeadCode CSB 26/03/99					temp = (vel * sin_ang)>>ANGLES_SHIFT; vely += temp;
//DeadCode CSB 26/03/99					temp = (vel * cos_ang)>>ANGLES_SHIFT; velh += temp;
//DeadCode CSB 26/03/99	
//DeadCode CSB 26/03/99					Math_Lib.high_sin_cos(hdg,sin_ang,cos_ang);
//DeadCode CSB 26/03/99	
//DeadCode CSB 26/03/99					velx = (velh * sin_ang)>>ANGLES_SHIFT;
//DeadCode CSB 26/03/99					velz = (velh * cos_ang)>>ANGLES_SHIFT;
//DeadCode CSB 26/03/99				}
//DeadCode CSB 26/03/99				else
//DeadCode CSB 26/03/99				{
//DeadCode CSB 26/03/99					velh = transit->velhori;
//DeadCode CSB 26/03/99					vely = transit->vely;
//DeadCode CSB 26/03/99					velx = transit->velx;
//DeadCode CSB 26/03/99					velz = transit->velz;
//DeadCode CSB 26/03/99					hdg = transit->hdg;
//DeadCode CSB 26/03/99					pitch = transit->pitch;
//DeadCode CSB 26/03/99				}				

			switch (launchmask)							//RJS 09Jul99
			{
				case LT_BOMB:
					theLifetime = LIFETIME_BOMB;
					mcode = MOBILE_BOMBDROP;
					break;
				case LT_ROCKET:
					theLifetime = LIFETIME_ROCKET;
					mcode = MOBILE_ROCKET;
					break;

				default:
					theLifetime = LIFETIME_BULLET;
					mcode = MOBILE_BULLET;
					break;
			}

			weapanim = SHAPE.GetWeaponLauncher((itemptr)theShooter,index,weappos.X,weappos.Y,weappos.Z,mvel,mdelay,mburst,launchmask);//RJS 09Jul99
			if (weapanim && (weapanim->LoadedStores > 0))
			{
				//Block for B29 GUNS
				if (	(theShooter->Status.size>=MOBILESIZE)	//RJS 09Jul99
					&&	((weapanim->LauncherType & LT_MASK) != LT_MOVEGUN)	)	//RJS 09Jul99
				{
					if (theShooter->Status.size>=AIRSTRUCSIZE)
					{
						AirStrucPtr AC = (AirStrucPtr)theShooter;
						SWord bhdg, bpitch, bvel;						
						AC->CalcBulletVel(mvel, bhdg, bpitch, bvel);
						hdg   = (Angles)bhdg;
						pitch = (Angles)bpitch;
						vel   = bvel;

						SWord sin_ang,cos_ang;
						Math_Lib.high_sin_cos(pitch,sin_ang,cos_ang);
						vely = (vel * sin_ang)>>ANGLES_SHIFT;
						velh = (vel * cos_ang)>>ANGLES_SHIFT;

						Math_Lib.high_sin_cos(hdg,sin_ang,cos_ang);
						velx = (velh * sin_ang)>>ANGLES_SHIFT;
						velz = (velh * cos_ang)>>ANGLES_SHIFT;
					}
					else
					{
						SWord	sin_ang,cos_ang;
						SLong	totalvel = theShooter->vel + mvel;

						muzPitch += (SWord) theShooter->pitch;			//RJS 21Jul98

						hdg = theShooter->hdg;
						pitch = (Angles) muzPitch;						//RJS 21Jul98
						Math_Lib.high_sin_cos(pitch,sin_ang,cos_ang);

						vely = (totalvel * sin_ang)>>ANGLES_SHIFT;
						velh = (totalvel * cos_ang)>>ANGLES_SHIFT;

						Math_Lib.high_sin_cos(hdg,sin_ang,cos_ang);

						velx = (velh * sin_ang)>>ANGLES_SHIFT;
						velz = (velh * cos_ang)>>ANGLES_SHIFT;

						vel = totalvel;
					}
				}
				else
				{
					velh = transit->velhori;
					vely = transit->vely;
					velx = transit->velx;
					velz = transit->velz;
					hdg = transit->hdg;
					pitch = transit->pitch;
				}

				Bool	isArmed;								//RJS 27May99
				if (transit->Status.deadtime)					//RJS 27May99
					isArmed = FALSE;							//RJS 27May99
				else											//RJS 27May99
					isArmed = TRUE;								//RJS 27May99

				LaunchSuperLauncher(theShooter,
									theShape,
									theLifetime+Math_Lib.rnd(30)|3,
									mcode,
									weappos,
									hdg,
									pitch,
									velx,
									vely,
									velz,
									velh,
									vel,
									transit->nationality,
									index,			
									index2,
									adptr->delay,				//RJS 21Jul98
									clonesleft-1,
									adptr->lnchtype,
									world,
									isArmed);					//RJS 27May99

				weapanim->LoadedStores--;
			}
		}

		transit->isOwned = 0;									//RJS 09Jul99

		AddTransientItemToDeadList(transit);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MobileNapalm
//Author		Robert Slater
//Date			Thu 22 Jan 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::MobileNapalm(TransientItemPtr transit, WorldStuff& world)
{
	SLong	timeleft = transit->LaunchTime;

	if (timeleft)
	{
		if ((transit->LaunchTime-=Timer_Code.FRAMETIME)<0)
			transit->LaunchTime=0;
	}
	else
	{
		TransientItemPtr newitem = SimplifiedSpriteLaunch(	transit,
															DUMY12,
															240,
															MOBILE_BURNIT);//RJS 18Nov98

		if (newitem)											//RJS 09Feb98
		{
			Three_Dee.pMigLand->GetShadowAngles(newitem->World,newitem->hdg,newitem->pitch,newitem->roll);

			newitem->Status.deadtime = (UByte)transit->Status.deadtime;//RJS 13May99
			newitem->Target = transit->Target;				//RJS 11May99
			newitem->Launcher = transit->Launcher;			//RJS 05May99
			newitem->pitch = transit->pitch;
			newitem->TransRandom = 50 << 8;
			newitem->TransRandom |= 240;
			newitem->hdg = transit->hdg;
			AddTransientItemToWorld(newitem,world);			//RJS 09Feb98
		}

		AddTransientItemToDeadList(transit);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MobileDoDamage
//Author		Robert Slater
//Date			Wed 18 Feb 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void TransObj::MobileDoDamage(TransientItemPtr transit,WorldStuff& world)
{

	if ((transit->LaunchTime-=Timer_Code.FRAMETIME)<0)			
		transit->LaunchTime=0;
	else
	{
		transit->TransRandom += Timer_Code.FRAMETIME;
		if ((transit->LaunchTime & 0x06)==0)					//RJS 09Nov98
		{
			if (transit->Status.deadtime == 0)					
			{
				ShapeDescPtr	sdptr = SHAPESTUFF.GetShapePtr(transit->shape);
				if (sdptr->AnimDataSize == MISSILEANIM)
				{
					MissileAnimData*	adptr = (MissileAnimData*) transit->Anim;
					if (adptr->hitstrength)
						adptr->frameno = transit->TransRandom;
				}

				ItemPtr		hititem;
				Coords3D	hitcoords;
				int		gindex;

				hititem=BoxCol::NineSectorCol(transit,hitcoords,gindex);
//DeadCode RJS 23Jun99 				if (hititem)
//DeadCode RJS 23Jun99 					transit->LaunchTime=0;								
			}
		}
	}

	if (transit->LaunchTime<=0)
		AddTransientItemToDeadList(transit);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MobileThuggery
//Author		Robert Slater
//Date			Mon 2 Mar 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void TransObj::MobileThuggery(TransientItemPtr transit,WorldStuff& world)
{
	ThugAnimData	*adptr = (ThugAnimData*) transit->Anim;

	if ((transit->LaunchTime-=Timer_Code.FRAMETIME)<0)			
		transit->LaunchTime=0;
	else
	{
		SWord	ptime, ntime;
		Bool	scared = TRUE;

		ptime = adptr->prevcount;
		ntime = adptr->nextcount;

		if ((transit->LaunchTime & 0x06)==0)					//RJS 09Mov98
		{
			GrpMinAnimData*	mad;
			ItemPtr			theVictim = (ItemPtr)transit->Target;	//RJS 05Jul99

			// Wait until last half a sec to start twatting...
			if (transit->TransRandom && (ptime < 16))
			{
				transit->uniqueID.changed = TRUE;			//RJS 09Dec98
				transit->World.X = adptr->pXPos;
				transit->World.Y = adptr->pYPos;
				transit->World.Z = adptr->pZPos;
				transit->TransRandom = 0;
				scared = FALSE;

				animptr	tmpanim = theVictim->Anim;	//RJS 05Jul99
//DeadCode AMM 05Jul99 				animptr	tmpanim = transit->Launcher->Anim;
				tmpanim += adptr->panimoff;

				mad = (GrpMinAnimData*) tmpanim;
			}
			else
			{
				// Wait until last half a sec to start twatting...
				if (ntime < 16)
				{
					transit->uniqueID.changed = TRUE;			//RJS 09Dec98
					transit->World.X = adptr->nXPos;
					transit->World.Y = adptr->nYPos;
					transit->World.Z = adptr->nZPos;
					transit->TransRandom = 1;
					scared = FALSE;
				
					animptr	tmpanim = theVictim->Anim;	 //RJS 05Jul99
//DeadCode AMM 05Jul99 					animptr	tmpanim = transit->Launcher->Anim;
					tmpanim += adptr->nanimoff;
		
					mad = (GrpMinAnimData*) tmpanim;
				}
			}

			if (!scared && (mad->itemstate != DEAD))
			{
				itemptr		hititem;

				hititem=BoxCol::SpecificCollision(transit,theVictim);//RJS 05Jul99	
//DeadCode AMM 05Jul99 				hititem=BoxCol::SpecificCollision(transit,transit->Launcher);
			}
		}

		ptime -= Timer_Code.FRAMETIME;
		ntime -= Timer_Code.FRAMETIME;
		if (ptime < 0)
			ptime = 0;

		if (ntime < 0)
			ntime = 0;

		adptr->prevcount = ptime;
		adptr->nextcount = ntime;
	}

	if (transit->LaunchTime<=0)
		AddTransientItemToDeadList(transit);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MobileSmallThug
//Author		Robert Slater
//Date			Thu 3 Dec 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void TransObj::MobileSmallThug(TransientItemPtr transit,WorldStuff& world)
{
	ThugAnimData	*adptr = (ThugAnimData*) transit->Anim;

	if ((transit->LaunchTime-=Timer_Code.FRAMETIME)<0)			
		transit->LaunchTime=0;
	else
	{
		if ((transit->LaunchTime & 0x06)==0)					//RJS 09Mov98
		{
			animptr	tmpanim = transit->Target->Anim;			//DAW 23Apr99
			tmpanim += adptr->panimoff;							//DAW 23Apr99
																//DAW 23Apr99
			MinAnimData*	mad = (MinAnimData*) tmpanim;		//RJS 26Apr99

			if (mad->itemstate != DEAD)							//RJS 26Apr99
			{
				itemptr		hititem;

				hititem=BoxCol::SpecificCollision(transit,transit->Target);
			}
			else
				transit->LaunchTime = 0;
		}
	}

	if (transit->LaunchTime<=0)
		AddTransientItemToDeadList(transit);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AutoSpiral2Ground
//Author		Paul.
//Date			Wed 1 May 1996
//
//Description	A/c death spiral
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void AirStruc::AutoSpiral2Ground(WorldStuff& world)
{
	SWord	frametime = Timer_Code.FRAMETIME;					//DAW 31Jul96
	SLong	groundheight;										//DAW 03Sep98
//DeadCode DAW 03Sep98	if (shape != CRATER)
//DeadCode DAW 03Sep98	{
//DeadCode DAW 03Sep98		SLong	groundheight;
//DeadCode DAW 03Sep98
//DeadCode DAW 03Sep98		Trans_Obj.GAndFriction((mobileitem* )this,OrdinaryDrag);
//DeadCode DAW 03Sep98
//DeadCode DAW 03Sep98		groundheight = Land_Scape.GetGroundLevel((itemptr)this);
//DeadCode DAW 03Sep98
//DeadCode DAW 03Sep98		if (World.Y<=groundheight)
//DeadCode DAW 03Sep98		{
//DeadCode DAW 03Sep98			World.Y = groundheight;
//DeadCode DAW 03Sep98
//DeadCode DAW 03Sep98			velx =
//DeadCode DAW 03Sep98				vely =
//DeadCode DAW 03Sep98				velz =
//DeadCode DAW 03Sep98				velhori = 0;
//DeadCode DAW 03Sep98
//DeadCode DAW 03Sep98			if (shape == WRECK)
//DeadCode DAW 03Sep98			{
//DeadCode DAW 03Sep98				pitch = ANGLES_0Deg;							//RJS 21Nov96
//DeadCode DAW 03Sep98				roll = ANGLES_0Deg;								//RJS 21Nov96
//DeadCode DAW 03Sep98				shape = CRATER;
//DeadCode DAW 03Sep98
//DeadCode DAW 03Sep98				if (this == Manual_Pilot.ControlledAC2)
//DeadCode DAW 03Sep98				{
//DeadCode DAW 03Sep98					_Miles.StopEngine();
//DeadCode DAW 03Sep98					Manual_Pilot.controlmode=Manual_Pilot.PILOTDEAD;
//DeadCode DAW 03Sep98					GR_Quit3DNow=CRASHED_DEAD;
//DeadCode DAW 03Sep98					Trans_Obj.View_Object->SetToDeathView();				//RDH 02Sep98
//DeadCode DAW 03Sep98				}
//DeadCode DAW 03Sep98
//DeadCode DAW 03Sep98 // in here when burning wreck hits ground, i.e. after collision	//AMM 20Feb97
//DeadCode DAW 03Sep98 // or if plane has burst into flames after being shot			//AMM 20Feb97
//DeadCode DAW 03Sep98 // score has already been set									//AMM 20Feb97
//DeadCode DAW 03Sep98
//DeadCode DAW 03Sep98				if(_DPlay.Implemented)
//DeadCode DAW 03Sep98				{
//DeadCode DAW 03Sep98 // crash into ground after spiralling to ground
//DeadCode DAW 03Sep98
//DeadCode DAW 03Sep98					_DPlay.item2place=ST_CRATER;
//DeadCode DAW 03Sep98					_DPlay.SendKill(*this,GR_Quit3DNow,PIDC_FIRECRATER,NULL);//AMM 16Jun97
//DeadCode DAW 03Sep98					_DPlay.ResurrectMe(*this,TRUE);
//DeadCode DAW 03Sep98				}
//DeadCode DAW 03Sep98
//DeadCode DAW 03Sep98				Trans_Obj.LaunchFire(*this,*currworld);
//DeadCode DAW 03Sep98			}
//DeadCode DAW 03Sep98			else
//DeadCode DAW 03Sep98			{
//DeadCode DAW 03Sep98				if (this == Manual_Pilot.ControlledAC2)			//RJS 12Sep97
//DeadCode DAW 03Sep98				{												//RJS 12Sep97
//DeadCode DAW 03Sep98					_Miles.StopEngine();						//RJS 12Sep97
//DeadCode DAW 03Sep98					GR_Quit3DNow=CRASHED_DEAD;					//RJS 12Sep97
//DeadCode DAW 03Sep98					
//DeadCode DAW 03Sep98					Trans_Obj.View_Object->SetToDeathView();				//RDH 02Sep98
//DeadCode DAW 03Sep98																//RJS 12Sep97
//DeadCode DAW 03Sep98					if(_DPlay.Implemented)						//RJS 12Sep97
//DeadCode DAW 03Sep98					{											//RJS 12Sep97
//DeadCode DAW 03Sep98						_DPlay.item2place=ST_CRATER;			//RJS 12Sep97
//DeadCode DAW 03Sep98						_DPlay.SendKill(*this,GR_Quit3DNow,PIDC_FIRECRATER,NULL);//RJS 12Sep97
//DeadCode DAW 03Sep98						_DPlay.ResurrectMe(*this,TRUE);			//RJS 12Sep97
//DeadCode DAW 03Sep98					}											//RJS 12Sep97
//DeadCode DAW 03Sep98					else										//RJS 12Sep97
//DeadCode DAW 03Sep98						Manual_Pilot.DeathSequenceOverride(*this,AUTO_CRASHROLL);//RDH 02Sep98
//DeadCode DAW 03Sep98 //						Manual_Pilot.ControlledAC2->movecode = AUTO_CRASHROLL;//RJS 12Sep97
//DeadCode DAW 03Sep98				}												//RJS 12Sep97
//DeadCode DAW 03Sep98			}
//DeadCode DAW 03Sep98		}
//DeadCode DAW 03Sep98		else
//DeadCode DAW 03Sep98		{
//DeadCode DAW 03Sep98			AircraftAnimData*	adptr;
//DeadCode DAW 03Sep98
//DeadCode DAW 03Sep98			adptr = (AircraftAnimData *)Anim;
//DeadCode DAW 03Sep98
//DeadCode DAW 03Sep98			UWord	lcldamflag;
//DeadCode DAW 03Sep98
//DeadCode DAW 03Sep98 //DeadCode RJS 09Jun97			lcldamflag = adptr->dammageflags;
//DeadCode DAW 03Sep98
//DeadCode DAW 03Sep98			//Check the state of the wings
//DeadCode DAW 03Sep98
//DeadCode DAW 03Sep98			SWord lrstate=0,tstate=0;			//try initialising variables - it stops bugs
//DeadCode DAW 03Sep98
//DeadCode DAW 03Sep98
//DeadCode DAW 03Sep98
//DeadCode DAW 03Sep98			// Calculate lift using new damage flags...........
//DeadCode DAW 03Sep98			// In a bit.......
//DeadCode DAW 03Sep98
//DeadCode DAW 03Sep98
//DeadCode DAW 03Sep98
//DeadCode DAW 03Sep98 //DeadCode RJS 13Mar97			lrstate = adptr->BOTLEFTWING + adptr->TOPLEFTWING;
//DeadCode DAW 03Sep98 //DeadCode RJS 13Mar97
//DeadCode DAW 03Sep98 //DeadCode RJS 13Mar97 //DeadCode RJS 21Feb97			lrstate = (lcldamflag >> BF_LBWing) & BS_DEAD;
//DeadCode DAW 03Sep98 //DeadCode RJS 13Mar97 //DeadCode RJS 21Feb97			lrstate += (lcldamflag >> BF_LTWing) & BS_DEAD;
//DeadCode DAW 03Sep98 //DeadCode RJS 13Mar97
//DeadCode DAW 03Sep98 //DeadCode RJS 13Mar97			tstate = lrstate;
//DeadCode DAW 03Sep98 //DeadCode RJS 13Mar97
//DeadCode DAW 03Sep98 //DeadCode RJS 13Mar97			lrstate -= adptr->BOTRIGHTWING;
//DeadCode DAW 03Sep98 //DeadCode RJS 13Mar97			lrstate -= adptr->TOPRIGHTWING;
//DeadCode DAW 03Sep98 //DeadCode RJS 13Mar97
//DeadCode DAW 03Sep98 //DeadCode RJS 13Mar97 //DeadCode RJS 21Feb97			lrstate -= (lcldamflag >> BF_RBWing) & BS_DEAD;
//DeadCode DAW 03Sep98 //DeadCode RJS 13Mar97 //DeadCode RJS 21Feb97			lrstate -= (lcldamflag >> BF_RTWing) & BS_DEAD;
//DeadCode DAW 03Sep98 //DeadCode RJS 13Mar97
//DeadCode DAW 03Sep98 //DeadCode RJS 13Mar97			tstate += adptr->BOTRIGHTWING;
//DeadCode DAW 03Sep98 //DeadCode RJS 13Mar97			tstate += adptr->TOPRIGHTWING;
//DeadCode DAW 03Sep98 //DeadCode RJS 13Mar97
//DeadCode DAW 03Sep98 //DeadCode RJS 13Mar97 //DeadCode RJS 21Feb97			tstate += (lcldamflag >> BF_RBWing) & BS_DEAD;
//DeadCode DAW 03Sep98 //DeadCode RJS 13Mar97 //DeadCode RJS 21Feb97			tstate += (lcldamflag >> BF_RTWing) & BS_DEAD;
//DeadCode DAW 03Sep98
//DeadCode DAW 03Sep98			//if lrstate>0 dammage to the left of the a/c is
//DeadCode DAW 03Sep98			//more severe than the dammage to the right
//DeadCode DAW 03Sep98			//this means more lift on the right and so
//DeadCode DAW 03Sep98			//the aircraft spirals anti-clockwise
//DeadCode DAW 03Sep98
//DeadCode DAW 03Sep98			//also, -6 <= lrstate <= +6
//DeadCode DAW 03Sep98
//DeadCode DAW 03Sep98			//and, 0 <= tstate <= 12
//DeadCode DAW 03Sep98
//DeadCode DAW 03Sep98			//Use lrstate to modify roll
//DeadCode DAW 03Sep98
//DeadCode DAW 03Sep98			// Scale down from 512 to 6 first....
//DeadCode DAW 03Sep98
//DeadCode DAW 03Sep98			//NOT INITIALISED!!!
//DeadCode DAW 03Sep98			lrstate /= 85;										//RJS 21Feb97
//DeadCode DAW 03Sep98
//DeadCode DAW 03Sep98			int	das;
//DeadCode DAW 03Sep98
//DeadCode DAW 03Sep98			ANGLES	arse = DeathAngleStep;
//DeadCode DAW 03Sep98
//DeadCode DAW 03Sep98			das = arse;
//DeadCode DAW 03Sep98
//DeadCode DAW 03Sep98			ANGLES	rollanglestep = (Angles)((lrstate*das*frametime)/10);
//DeadCode DAW 03Sep98
//DeadCode DAW 03Sep98			roll += rollanglestep;
//DeadCode DAW 03Sep98
//DeadCode DAW 03Sep98			_Miles.PlayLooped((FileNum) FIL_SFX_FIREBURN_LOOP, (ItemBasePtr) *this);//RJS 22Nov96
//DeadCode DAW 03Sep98		}
//DeadCode DAW 03Sep98	}

	Trans_Obj.GAndFriction((mobileitem* )this,OrdinaryDrag);

	groundheight = Trans_Obj.GetGroundLevel(*this);						//RJS 14Apr99
	if (World.Y<=groundheight)
	{
		World.Y = groundheight;
		Trans_Obj.LandedEffect(*this,_Collide.NOSE_TOUCH);
	}
	else
	{
		AircraftAnimData*	adptr = (AircraftAnimData *)Anim;
		SWord lstate,rstate;	
		UWord	rollstep = ANGLES_5Deg;

		lstate = adptr->LEFTWINGIN;
		rstate = adptr->RIGHTWINGIN;

		if (lstate > rstate)
			rollstep = (rollstep * lstate)/BS_DEAD;
		else
			rollstep = (-rollstep * rstate)/BS_DEAD;

		roll = (Angles) (roll + rollstep);

		_Miles.PlayLooped((FileNum) FIL_SFX_FIREBURN_LOOP, (ItemBasePtr) *this);//RJS 22Nov96
	}
}

/////////////////////////////////////////////////////////////////////////////////
//
//	Common transient move code
//
/////////////////////////////////////////////////////////////////////////////////

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GAndFriction
//Author		Paul.
//Date			Mon 29 Apr 1996
//				//RDH 23Jul96 modified drag
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void TransObj::GAndFriction(mobileitem* itm,SWord dragfactor,SWord dragfacy)
{
	SWord	frametime;

	frametime = Timer_Code.FRAMETIME;							//DAW 31Jul96

	//Vertical velocity first

	SLong	testvel;
	SLong	testvely;											//RJS 04Jul96
	SLong	fractionpoo = (itm->timeofday<<1)&127;		//RJS 03Jun97

	SLong	deltax, deltay;

	testvel = itm->vely;
//rdh	testvel -= 2;	//(frametime * TenMetresPerSec)/100;

//vel units are mm/cs
//frametime is in cs
// g = 10m/s/s = 10 * 1000 / (100 * 100) mm/cs/cs = 1 mm/cs/cs
// delta vel = frame time in cs * g
	testvel -= frametime;

	if (testvel>TerminalVelocity)
		itm->vely=TerminalVelocity;
	else
		itm->vely = (SWord )testvel;

	//Calculate new horizontal velocity using v = kut
	//where k = drag factor
	//		t = 1 second

//	testvel = (itm->velhori * frametime)/0x1000;				
//	testvely = (itm->vely * frametime)/0x90;					//RJS 07Aug96

	testvel = (itm->velhori * frametime * dragfactor)>>12;		//RJS 22Apr99
	testvely = (itm->vely * frametime * dragfacy)/0x90;			//RJS 22Apr99

	deltax = (itm->velhori * (frametime<<7/10)+fractionpoo)>>7;
	deltay = (itm->vely * (frametime<<7/10)+fractionpoo)>>7;

	itm->velhori -= testvel;									//RJS 22Apr99
	itm->vely -= testvely;										//RJS 22Apr99

	ApplyVelocities(itm);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GAndFrictionFixedPitch
//Author		Robert Slater
//Date			Fri 29 May 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void TransObj::GAndFrictionFixedPitch(mobileitem* itm,SWord dragfactor,SWord dragfacy)
{
	SWord	frametime = Timer_Code.FRAMETIME;			
	SLong	testvel;
	SLong	testvely;											
	SLong	fractionpoo = (itm->timeofday<<1)&127;	

	SLong	deltax, deltay;
	SWord	sin_ang,cos_ang;

	testvel = itm->vely;
	testvel -= 2;


	if (testvel>TerminalVelocity)
		itm->vely=TerminalVelocity;
	else
		itm->vely = (SWord )testvel;

	//Calculate new horizontal velocity using v = kut
	//where k = drag factor
	//		t = 1 second

	testvel = (itm->velhori * frametime)>>12;	
	testvely = (itm->vely * frametime)/0x90;				

	deltax = (itm->velhori * (frametime<<7/10)+fractionpoo)>>7;
	deltay = (itm->vely * (frametime<<7/10)+fractionpoo)>>7;

	if (dragfactor)
		itm->velhori -= (dragfactor*testvel);		

	if (dragfacy)
		itm->vely -= (dragfacy*testvely);

	itm->World.Y += (itm->vely * frametime)/10;

	testvel = (frametime * itm->velhori)/10;

	if (testvel>TerminalVelocity)	testvel = TerminalVelocity;

	Math_Lib.high_sin_cos((ANGLES )itm->hdg,sin_ang,cos_ang);

	itm->World.X += (testvel*sin_ang)/ANGLES_FRACT;
	itm->World.Z += (testvel*cos_ang)/ANGLES_FRACT;
	itm->uniqueID.changed = TRUE;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		NoGravityAndFriction
//Author		Robert Slater
//Date			Thu 18 Jun 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void TransObj::NoGravityAndFriction(mobileitem* itm,SWord dragfactor)
{
	SWord	frametime = Timer_Code.FRAMETIME;			
	SLong	testvel = (itm->velhori * frametime)>>12;					

	if (dragfactor)
		itm->velhori -= (dragfactor*testvel);	

	ApplyVelocities(itm);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AddWindDrift
//Author		Robert Slater
//Date			Tue 7 Jan 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void TransObj::AddWindDrift(item* itm)
{
//rdh need to change to MiG Alley wind

//	temp = frametime * MMC.wind.speed;
//	temp /= 10;
//
//	Math_Lib.high_sin_cos((ANGLES )MMC.wind.direction,sin_ang,cos_ang);
//
//	itm->World.X += (temp*sin_ang)/ANGLES_FRACT;
//	itm->World.Z += (temp*cos_ang)/ANGLES_FRACT;

	SLong	height = itm->World.Y;
	SLong	vx, vy, vz;

	if (MMC.Sky.GetWind(height,vx,vy,vz))	//RJS 02Nov98
	{
		itm->World.X += vx;									//RJS 30Apr99
		itm->World.Y += vy;									//RJS 30Apr99
		itm->World.Z += vz;									//RJS 30Apr99
	}

	itm->uniqueID.changed = TRUE;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ApplyVelocities
//Author		Paul.
//Date			Mon 29 Apr 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void TransObj::ApplyVelocities(mobileitem* itm)
{
	SWord	frametime;

	frametime = Timer_Code.FRAMETIME;							//DAW 31Jul96

	itm->pitch = Math_Lib.arctan(itm->vely,itm->velhori);

	itm->World.Y += (itm->vely * frametime)/10;

	SLong	temp;

	temp = (frametime * itm->velhori)/10;

	if (temp>TerminalVelocity)	temp = TerminalVelocity;

	SWord	sin_ang,cos_ang;

	Math_Lib.high_sin_cos((ANGLES )itm->hdg,sin_ang,cos_ang);

	itm->World.X += (temp*sin_ang)/ANGLES_FRACT;

	itm->World.Z += (temp*cos_ang)/ANGLES_FRACT;

	itm->uniqueID.changed = TRUE;

}

/////////////////////////////////////////////////////////////////////////////////
//
//				Item collision with missile code.
//
/////////////////////////////////////////////////////////////////////////////////

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MissileHitSomething
//Author		Paul.
//Date			Mon 29 Apr 1996
//
//Description
//	
//	NB. All the special effects and damage are taken care of externally RJS 27Feb98
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void TransObj::MissileHitSomething(	itemptr			hititem,
									TransientItemPtr	missile,
									WorldStuff&			world,
									SByte				groupindex)
{
	return;

/*	SWord	inwingpos;											//RDH 03Oct96

	switch (hititem->Status.size)
	{
		//We've hit an aircraft
		case AirStrucSize:
			{
				UWord				anydamage = Math_Lib.rnd(RndValMAX);//RDH 06Oct96
				UWord				damagechance = RND50PC;
				itemptr				lasthitter = missile->Launcher;
				AircraftAnimData*	adptr;
				Bool				alreadydead = FALSE;

				adptr = (AircraftAnimData* )hititem->Anim;
				((AirStrucPtr)hititem)->lasthitter = lasthitter->uniqueID;

				if (lasthitter == Manual_Pilot.ControlledAC2)
					_Miles.SequenceAudible(SPOT_PLAYER_MAKES_HIT);
				else
				{
					if (hititem == Manual_Pilot.ControlledAC2)
					{
//						_Miles.SequenceAudible(FIL_MUSIC_DISADVANTAGE);//RJS 25Sep96
//						_Miles.SequenceAudible(SPOT_PLAYER_GETS_HIT);
					}
				}
				if (((AirStrucPtr)hititem)->Status.deadtime)
						alreadydead = TRUE;

				if ((anydamage < damagechance)						//RDH 01Nov96
					||	(lasthitter != Manual_Pilot.ControlledAC2)
						)
				{
//DeadCode RJS 27Feb98					GeneralAircraftDammage((AirStruc* )hititem,world,FALSE,lasthitter);//ARM 02Dec96
					if (lasthitter->Status.size == AirStrucSize)
					{
						if (	(((AirStrucPtr)lasthitter)->IsUsingPilotedAcLog())//JIM 17Mar99
							&&	(((AirStrucPtr)lasthitter)->nationality !=
									((AirStrucPtr)hititem)->nationality)
							)
						{
							Persons_2.UpdateLog(((AirStrucPtr)hititem)->ai.eventlog,0,EventLog::DAMAGED);//RDH 02Oct96
						}
					}		

				}else
				{
					if (lasthitter->Status.size == AirStrucSize)
					{
						if (	(((AirStrucPtr)hititem)->ai.combatskill <= SKILL_REGULAR)
							&&	(((AirStrucPtr)hititem)->ai.morale	>	MORALE_VERYPOOR)
							)
						{//drop morale of low skill pilots on being hit
							((AirStrucPtr)hititem)->ai.morale = ((AirStrucPtr)hititem)->ai.morale -//RDH 02Dec96
																damagechance * MORALE_STAGE / 100;
						}
						if (	(((AirStrucPtr)lasthitter)->IsUsingPilotedAcLog())//RDH 02Oct96
							&&	(((AirStrucPtr)hititem)->ai.eventlog->stage!=EventLog::TAKEOFF)
								)
							Persons_2.UpdateLog(((AirStrucPtr)hititem)->ai.eventlog,0,EventLog::ATTACKED);//JIM 17Mar99
					}

				}


				if (lasthitter->Status.size == AirStrucSize)
				{
					if (	(((AirStrucPtr)hititem)->Status.deadtime)
						&&	(alreadydead == FALSE)
							)
					{
						if (((AirStrucPtr)lasthitter)->ai.eventlog->stage==EventLog::TAKEOFF)//RDH 02Oct96
						{
							if (((AirStrucPtr)lasthitter)->nationality ==
									((AirStrucPtr)hititem)->nationality)
								{
									((AirStrucPtr)lasthitter)->ai.eventlog->losses += 1;
								}else
								{
									Persons_2.UpdateLog(((AirStrucPtr)hititem)->ai.eventlog,1,EventLog::KILLED);//RDH 02Oct96
									if (((AirStrucPtr)hititem)->formpos == 0)
									((AirStrucPtr)hititem)->ai.eventlog->famehit = ((AirStrucPtr)hititem)->ai.eventlog->name;
								}
						}elseif (((AirStrucPtr)hititem)->ai.eventlog->stage==EventLog::TAKEOFF)//RDH 03Oct96
						{
							Persons_2.UpdateLog(((AirStrucPtr)lasthitter)->ai.eventlog,-1,EventLog::KILLED);//RDH 25Oct96

//DeadCode RDH 17Feb97							inwingpos = ( ((AirStrucPtr)hititem)->formpos&InWingMAX) +
//DeadCode RDH 17Feb97											((	((AirStrucPtr)hititem)->formpos&InFormMAX) * Miss_Man.camp.squad.pilotsperflight);
//DeadCode RDH 17Feb97							if (MMC.Active_Pilots[inwingpos].kills >=5)
//DeadCode RDH 17Feb97							{
//DeadCode RDH 17Feb97								((AirStrucPtr)hititem)->ai.eventlog->fameloss = (TextSnip0)MMC.Active_Pilots[inwingpos].name;
//DeadCode RDH 17Feb97
//DeadCode RDH 17Feb97							}elseif (((AirStrucPtr)hititem)->ai.eventlog->fameloss == TEXT_NULL)
//DeadCode RDH 17Feb97								((AirStrucPtr)hititem)->ai.eventlog->fameloss = (TextSnip0)MMC.Active_Pilots[inwingpos].name;
						}									//RDH 03Oct96
					}
					else
					{
						if (alreadydead == FALSE)
							Art_Int.PersonalThreat(*hititem,*lasthitter);
					}
				}
			}
			break;

//DeadCode RJS 27Feb98		//We've hit something else
//DeadCode RJS 27Feb98		default:
//DeadCode RJS 27Feb98			{
//DeadCode RJS 27Feb98				GeneralItemDamage((mobileitem*)hititem,missile,world,groupindex);//RJS 02Oct96
//DeadCode RJS 27Feb98			}
//DeadCode RJS 27Feb98			break;
	}
	*/
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GeneralAircraftDammage
//Author		Paul.
//Date			Thu 18 Apr 1996
//
//Description	Adds some RANDOM dammage to an aircraft
//
//Inputs		
//
//Returns		TRUE if item is dead,
//				FALSE otherwise
//
//------------------------------------------------------------------------------
MATHABLE(BitStates);
void TransObj::GeneralAircraftDammage(AirStruc* ac,
										WorldStuff& worldptr,
										Bool	blowup,
										itemptr	hitter)
{
	UWord		dammagebit;
	ULong		damageflag;
	SLong		temp;
	BitStates	state;
	Bool		noanim;
	UByte		totaldeathcount = 0;
	BitFlags	whichbit;
	ULong		*dflagptr;
	

//DeadCode RJS 09Jun97	return;								// Disabled for new shapes!!!!!
//DeadCode RJS 09Jun97
//DeadCode RJS 09Jun97
//DeadCode RJS 09Jun97	AircraftAnimData* adptr;
//DeadCode RJS 09Jun97	
//DeadCode RJS 09Jun97	adptr = (AircraftAnimData* )ac->Anim;
//DeadCode RJS 09Jun97
//DeadCode RJS 09Jun97	if (blowup)
//DeadCode RJS 09Jun97		totaldeathcount = 0;
//DeadCode RJS 09Jun97	else
//DeadCode RJS 09Jun97		totaldeathcount = BF_TheRest;							//RJS 31Oct96
//DeadCode RJS 09Jun97
//DeadCode RJS 09Jun97	do
//DeadCode RJS 09Jun97	{
//DeadCode RJS 09Jun97		whichbit = (BitFlags) totaldeathcount;					//RJS 27Sep96
//DeadCode RJS 09Jun97
//DeadCode RJS 09Jun97		dammagebit = Math_Lib.rnd();
//DeadCode RJS 09Jun97
//DeadCode RJS 09Jun97		if (!blowup)
//DeadCode RJS 09Jun97		{
//DeadCode RJS 09Jun97			temp = dammagebit * (BF_Fuel+2);					//RJS 07Nov96
//DeadCode RJS 09Jun97			temp >>= 16;										//RJS 21Oct96
//DeadCode RJS 09Jun97
//DeadCode RJS 09Jun97			dammagebit = temp & ~1;										//RJS 30Jul96
//DeadCode RJS 09Jun97
//DeadCode RJS 09Jun97			dflagptr = (ULong*) &(adptr->dammageflags);					//RJS 21Oct96
//DeadCode RJS 09Jun97			damageflag = *dflagptr;										//RJS 21Oct96
//DeadCode RJS 09Jun97
//DeadCode RJS 09Jun97			state = (BitStates )((damageflag>>dammagebit) & BS_DEAD);
//DeadCode RJS 09Jun97
//DeadCode RJS 09Jun97			if ((BitFlags)dammagebit < BF_Pilot)				//RJS 18Oct96
//DeadCode RJS 09Jun97			{
//DeadCode RJS 09Jun97				noanim = FALSE;
//DeadCode RJS 09Jun97 //DeadCode RJS 21Oct96				state = (BitStates )((adptr->dammageflags>>dammagebit) & BS_DEAD);
//DeadCode RJS 09Jun97
//DeadCode RJS 09Jun97				if (	((BitFlags)dammagebit < BF_Tail)		//RJS 13Nov96
//DeadCode RJS 09Jun97					&&	(Math_Lib.rnd() < 32767)		)
//DeadCode RJS 09Jun97					return;
//DeadCode RJS 09Jun97			}
//DeadCode RJS 09Jun97			else
//DeadCode RJS 09Jun97			{
//DeadCode RJS 09Jun97				noanim = TRUE;
//DeadCode RJS 09Jun97 //DeadCode RJS 21Oct96				state = (BitStates )((adptr->damageflags2>>dammagebit) & BS_DEAD);
//DeadCode RJS 09Jun97			}
//DeadCode RJS 09Jun97
//DeadCode RJS 09Jun97			if (state == BS_DAMLV2)								//RJS 09Dec96
//DeadCode RJS 09Jun97			{													//RJS 09Dec96
//DeadCode RJS 09Jun97				if ((BitFlags)dammagebit == BF_Fuel)			//RJS 09Dec96
//DeadCode RJS 09Jun97				{												//RJS 09Dec96
//DeadCode RJS 09Jun97					if (Math_Lib.rnd() > 8000)					//RJS 09Dec96
//DeadCode RJS 09Jun97						state = BS_DAMLV1;						//RJS 09Dec96
//DeadCode RJS 09Jun97				}												//RJS 09Dec96
//DeadCode RJS 09Jun97				else											//RJS 09Dec96
//DeadCode RJS 09Jun97				{												//RJS 09Dec96
//DeadCode RJS 09Jun97					if (Math_Lib.rnd() < 8000)					//RJS 09Dec96
//DeadCode RJS 09Jun97						state = BS_DAMLV1;						//RJS 09Dec96
//DeadCode RJS 09Jun97				}												//RJS 09Dec96
//DeadCode RJS 09Jun97			}													//RJS 09Dec96
//DeadCode RJS 09Jun97		}
//DeadCode RJS 09Jun97		else
//DeadCode RJS 09Jun97		{
//DeadCode RJS 09Jun97			state = (BitStates )((adptr->dammageflags>>whichbit) & BS_DEAD);
//DeadCode RJS 09Jun97			noanim = FALSE;
//DeadCode RJS 09Jun97
//DeadCode RJS 09Jun97			if (state != BS_DEAD)
//DeadCode RJS 09Jun97				state = BS_DAMLV2;
//DeadCode RJS 09Jun97
//DeadCode RJS 09Jun97			totaldeathcount += 2;
//DeadCode RJS 09Jun97			dammagebit = whichbit;								//RJS 27Sep96
//DeadCode RJS 09Jun97		}
//DeadCode RJS 09Jun97
//DeadCode RJS 09Jun97		// come in here
//DeadCode RJS 09Jun97
//DeadCode RJS 09Jun97		if (state!=BS_DEAD)
//DeadCode RJS 09Jun97		{
//DeadCode RJS 09Jun97			state++;
//DeadCode RJS 09Jun97			AcDamageEffects(ac,(BitFlags )dammagebit,state,worldptr);//RJS 08Aug96
//DeadCode RJS 09Jun97
//DeadCode RJS 09Jun97			if (hitter)
//DeadCode RJS 09Jun97			{
//DeadCode RJS 09Jun97				if (hitter == Manual_Pilot.ControlledAC2)
//DeadCode RJS 09Jun97					SetAircraftDammage(ac,worldptr,(BitFlags )dammagebit,state,noanim,FALSE,blowup,TRUE);//ARM 02Dec96
//DeadCode RJS 09Jun97				else
//DeadCode RJS 09Jun97					SetAircraftDammage(ac,worldptr,(BitFlags )dammagebit,state,noanim,FALSE,blowup,FALSE);//ARM 02Dec96
//DeadCode RJS 09Jun97			}
//DeadCode RJS 09Jun97			else
//DeadCode RJS 09Jun97				SetAircraftDammage(ac,worldptr,(BitFlags )dammagebit,state,noanim,FALSE,blowup,FALSE);//ARM 02Dec96
//DeadCode RJS 09Jun97
//DeadCode RJS 09Jun97			if ( (state == BS_DEAD)	&& ((BitFlags )dammagebit != BF_Gear) )//RJS 06Oct96
//DeadCode RJS 09Jun97			{
//DeadCode RJS 09Jun97				if (ac == Manual_Pilot.ControlledAC2)
//DeadCode RJS 09Jun97					_Miles.SequenceAudible(FIL_MUSIC_SPIRALLING);
//DeadCode RJS 09Jun97				else
//DeadCode RJS 09Jun97				{
//DeadCode RJS 09Jun97					_Miles.SequenceAudible(FIL_MUSIC_ADVANTAGE);	//RJS 25Sep96
//DeadCode RJS 09Jun97					_Miles.SequenceAudible(SPOT_PLAYER_MAKES_KILL);
//DeadCode RJS 09Jun97				}
//DeadCode RJS 09Jun97			}
//DeadCode RJS 09Jun97		}
//DeadCode RJS 09Jun97	}while (totaldeathcount < BF_TheRest);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DirectAircraftDamage
//Author		ajhfkjfhskdfh
//Date			Tue 8 Oct 1996
//
//Description	Comms set Aircarft Damage
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void TransObj::DirectAircraftDamage(AirStruc* ac,WorldStuff& worldptr, BitStates state, BitFlags whichbit)
{
	SLong		temp;
	Bool		noanim;

	AircraftAnimData* adptr;
	
	adptr = (AircraftAnimData* )ac->Anim;

	if (whichbit < BF_Pilot)
		noanim = FALSE;
	else
		noanim = TRUE;

	if (state!=BS_DEAD)
	{
		state++;
		AcDamageEffects(ac,whichbit,state,worldptr);//RJS 08Aug96
		SetAircraftDammage(ac,worldptr,whichbit,state,noanim,FALSE,FALSE,FALSE);

		if (state == BS_DEAD)									//RJS 06Sep96
		{
			ShapeDescPtr	sdptr = SHAPESTUFF.GetShapePtr(ac->shape);
			ac->Status.deadtime = sdptr->DeadTime;
			ac->Status.deadscale = sdptr->DeadScale;
//DeadCode JIM 22Apr97			ac->uniqueID.deaded = TRUE;
			ac->BreakForm();
//			if (ac == Manual_Pilot.ControlledAC2)
//				_Miles.SequenceAudible(FIL_MUSIC_SPIRALLING);
		}
	}
}

//TempCode RJS 21Feb97 void TransObj::SetShapeDamage(	ItemPtr	itm,
//TempCode RJS 21Feb97								WorldStuff& worldptr,
//TempCode RJS 21Feb97								UByteP		damageptr,		
//TempCode RJS 21Feb97								BitStates	whatstate,
//TempCode RJS 21Feb97								Bool		nomovecode,
//TempCode RJS 21Feb97								Bool		sendpacket)
//TempCode RJS 21Feb97
//TempCode RJS 21Feb97 {
//TempCode RJS 21Feb97
//TempCode RJS 21Feb97
//TempCode RJS 21Feb97	adptr = (AircraftAnimData* )ac->Anim;
//TempCode RJS 21Feb97
//TempCode RJS 21Feb97	if (	!adptr												
//TempCode RJS 21Feb97		||	(damageptr == &adptr->OTHER)	)					
//TempCode RJS 21Feb97		return;
//TempCode RJS 21Feb97
//TempCode RJS 21Feb97	oldstate = (BitStates) *damageptr;							
//TempCode RJS 21Feb97
//TempCode RJS 21Feb97	if (oldstate == whatstate)
//TempCode RJS 21Feb97		return;													
//TempCode RJS 21Feb97
//TempCode RJS 21Feb97	*damageptr = whatstate;										
//TempCode RJS 21Feb97
//TempCode RJS 21Feb97	if (noanim)													
//TempCode RJS 21Feb97	{
//TempCode RJS 21Feb97		if (whatstate==BS_DEAD)
//TempCode RJS 21Feb97		{
//TempCode RJS 21Feb97			if (ac != Manual_Pilot.ControlledAC2)				
//TempCode RJS 21Feb97				adptr->itemstate = DAMMAGED;					
//TempCode RJS 21Feb97
//TempCode RJS 21Feb97			if (ac->uniqueID.deaded == FALSE)					
//TempCode RJS 21Feb97			{
//TempCode RJS 21Feb97				ac->Status.deadtime = sdptr->DeadTime;
//TempCode RJS 21Feb97				ac->Status.deadscale = sdptr->DeadScale;
//TempCode RJS 21Feb97				ac->uniqueID.deaded = TRUE;
//TempCode RJS 21Feb97				ac->BreakForm();
//TempCode RJS 21Feb97
//TempCode RJS 21Feb97				// Record kill for Comms
//TempCode RJS 21Feb97				_DPlay.StoreKill (ac, NULL, TRUE);
//TempCode RJS 21Feb97			}
//TempCode RJS 21Feb97
//TempCode RJS 21Feb97			if (!nomovecode)				
//TempCode RJS 21Feb97				ac->movecode = AUTO_DEATHSEQUENCE;
//TempCode RJS 21Feb97
//TempCode RJS 21Feb97		}
//TempCode RJS 21Feb97	}
//TempCode RJS 21Feb97	else
//TempCode RJS 21Feb97	{
//TempCode RJS 21Feb97		//If the new state is BS_DEAD then we need to launch a dead a/c part to match the
//TempCode RJS 21Feb97		//missing section
//TempCode RJS 21Feb97
//TempCode RJS 21Feb97		if (whatstate==BS_DEAD)
//TempCode RJS 21Feb97		{
//TempCode RJS 21Feb97			//Kill the item...
//TempCode RJS 21Feb97
//TempCode RJS 21Feb97			if (ac != Manual_Pilot.ControlledAC2)				
//TempCode RJS 21Feb97				adptr->itemstate = DAMMAGED;					
//TempCode RJS 21Feb97
//TempCode RJS 21Feb97			if (	(ac->uniqueID.deaded == FALSE)				
//TempCode RJS 21Feb97				&&	(damageptr != &adptr->GEAR)		)			
//TempCode RJS 21Feb97			{
//TempCode RJS 21Feb97				ac->Status.deadtime = sdptr->DeadTime;
//TempCode RJS 21Feb97				ac->Status.deadscale = sdptr->DeadScale;
//TempCode RJS 21Feb97				ac->uniqueID.deaded = TRUE;
//TempCode RJS 21Feb97				ac->BreakForm();
//TempCode RJS 21Feb97
//TempCode RJS 21Feb97				// Record kill for Comms
//TempCode RJS 21Feb97				_DPlay.StoreKill (ac, NULL, TRUE);
//TempCode RJS 21Feb97			}
//TempCode RJS 21Feb97
//TempCode RJS 21Feb97			//...and launch the dead bit
//TempCode RJS 21Feb97
//TempCode RJS 21Feb97			LaunchDeadACPart(ac,damageptr,worldptr,blowup);		
//TempCode RJS 21Feb97
//TempCode RJS 21Feb97			if (damageptr < &adptr->PROP)						
//TempCode RJS 21Feb97				_Miles.PlayOnce(FIL_SFX_WOOD_BREAK2, (ItemBasePtr) ac);
//TempCode RJS 21Feb97
//TempCode RJS 21Feb97			if (	!nomovecode
//TempCode RJS 21Feb97				&&	(damageptr != &adptr->GEAR))
//TempCode RJS 21Feb97				ac->movecode = AUTO_DEATHSEQUENCE;
//TempCode RJS 21Feb97		}
//TempCode RJS 21Feb97	}
//TempCode RJS 21Feb97 }

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetAircraftDammage
//Author		Paul.
//Date			Thu 18 Apr 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void TransObj::SetAircraftDammage(	AirStruc*	ac,
									WorldStuff& worldptr,
									BitFlags	whichbit,	
									BitStates	whatstate,
									Bool		noanim,
									Bool		nomovecode,
									Bool		blowup,
									Bool		sendpacket)

{
	AircraftAnimData* adptr;
	ShapeDescPtr	sdptr = SHAPESTUFF.GetShapePtr(ac->shape);
	BitStates		oldstate;
	ULong			damageflag;
	ULong			*dflagptr;
	UByteP			damageptr;									//RJS 18Feb97

//DeadCode RJS 13Mar97	adptr = (AircraftAnimData* )ac->Anim;
//DeadCode RJS 13Mar97
//DeadCode RJS 13Mar97	if (	!adptr										
//DeadCode RJS 13Mar97		||	(whichbit == BF_TheRest)	)					
//DeadCode RJS 13Mar97		return;
//DeadCode RJS 13Mar97
//DeadCode RJS 13Mar97	dflagptr = (ULong*) &(adptr->dammageflags);					//RJS 21Oct96
//DeadCode RJS 13Mar97	damageflag = *dflagptr;										//RJS 21Oct96
//DeadCode RJS 13Mar97
//DeadCode RJS 13Mar97	oldstate = (BitStates )((damageflag>>whichbit) & BS_DEAD);	//RJS 21Oct96
//DeadCode RJS 13Mar97	
//DeadCode RJS 13Mar97	if (oldstate == whatstate)
//DeadCode RJS 13Mar97		return;													//RJS 21Oct96
//DeadCode RJS 13Mar97
//DeadCode RJS 13Mar97	//Send damage offset from start of animation data....
//DeadCode RJS 13Mar97	if (sendpacket)							
//DeadCode RJS 13Mar97		_DPlay.NewDamage (ac, oldstate, whichbit);
//DeadCode RJS 13Mar97
//DeadCode RJS 13Mar97	damageflag &= ~(BS_DEAD<<whichbit);							//RJS 21Oct96
//DeadCode RJS 13Mar97	damageflag |= whatstate<<whichbit;							//RJS 21Oct96
//DeadCode RJS 13Mar97
//DeadCode RJS 13Mar97	*dflagptr = damageflag;					//RJS 21Oct96
//DeadCode RJS 13Mar97
//DeadCode RJS 13Mar97	if (noanim)													//RJS 30Jul96
//DeadCode RJS 13Mar97	{
//DeadCode RJS 13Mar97		if (whatstate==BS_DEAD)
//DeadCode RJS 13Mar97		{
//DeadCode RJS 13Mar97			if (ac != Manual_Pilot.ControlledAC2)				//RJS 20Nov96
//DeadCode RJS 13Mar97			{
//DeadCode RJS 13Mar97				//I know this *may* have effects elsewhere.. but it fixes rear gunners//JIM 15Nov96
//DeadCode RJS 13Mar97				adptr->itemstate = DAMMAGED;					//RJS 22Nov96
//DeadCode RJS 13Mar97			}
//DeadCode RJS 13Mar97
//DeadCode RJS 13Mar97			if (ac->uniqueID.deaded == FALSE)					//JIM 23Oct96
//DeadCode RJS 13Mar97			{
//DeadCode RJS 13Mar97				ac->Status.deadtime = sdptr->DeadTime;
//DeadCode RJS 13Mar97				ac->Status.deadscale = sdptr->DeadScale;
//DeadCode RJS 13Mar97				ac->uniqueID.deaded = TRUE;
//DeadCode RJS 13Mar97				ac->BreakForm();
//DeadCode RJS 13Mar97
//DeadCode RJS 13Mar97				// Record kill for Comms
//DeadCode RJS 13Mar97				_DPlay.StoreKill (ac, NULL, TRUE);
//DeadCode RJS 13Mar97			}
//DeadCode RJS 13Mar97
//DeadCode RJS 13Mar97			if (!nomovecode)									//RJS 21Oct96
//DeadCode RJS 13Mar97					ac->movecode = AUTO_DEATHSEQUENCE;				//PD 12Sep96
//DeadCode RJS 13Mar97
//DeadCode RJS 13Mar97		}
//DeadCode RJS 13Mar97	}
//DeadCode RJS 13Mar97	else
//DeadCode RJS 13Mar97	{
//DeadCode RJS 13Mar97		//If the new state is BS_DEAD then we need to launch a dead a/c part to match the
//DeadCode RJS 13Mar97		//missing section
//DeadCode RJS 13Mar97
//DeadCode RJS 13Mar97		if (whatstate==BS_DEAD)
//DeadCode RJS 13Mar97		{
//DeadCode RJS 13Mar97			//Kill the item...
//DeadCode RJS 13Mar97
//DeadCode RJS 13Mar97			if (ac != Manual_Pilot.ControlledAC2)				//RJS 20Nov96
//DeadCode RJS 13Mar97			{
//DeadCode RJS 13Mar97				//I know this *may* have effects elsewhere.. but it fixes rear gunners//JIM 15Nov96
//DeadCode RJS 13Mar97				adptr->itemstate = DAMMAGED;					//RJS 22Nov96
//DeadCode RJS 13Mar97			}
//DeadCode RJS 13Mar97
//DeadCode RJS 13Mar97			if (	(ac->uniqueID.deaded == FALSE)				//RJS 13Feb97
//DeadCode RJS 13Mar97				&&	(damageptr != &adptr->GEAR)		)			//RJS 13Feb97
//DeadCode RJS 13Mar97			{
//DeadCode RJS 13Mar97				ac->Status.deadtime = sdptr->DeadTime;
//DeadCode RJS 13Mar97				ac->Status.deadscale = sdptr->DeadScale;
//DeadCode RJS 13Mar97				ac->uniqueID.deaded = TRUE;
//DeadCode RJS 13Mar97				ac->BreakForm();
//DeadCode RJS 13Mar97
//DeadCode RJS 13Mar97				// Record kill for Comms
//DeadCode RJS 13Mar97				_DPlay.StoreKill (ac, NULL, TRUE);
//DeadCode RJS 13Mar97			}
//DeadCode RJS 13Mar97
//DeadCode RJS 13Mar97			//...and launch the dead bit
//DeadCode RJS 13Mar97
//DeadCode RJS 13Mar97			LaunchDeadACPart(ac,whichbit,worldptr,blowup);
//DeadCode RJS 13Mar97
//DeadCode RJS 13Mar97			if (whichbit < BF_Nose)					
//DeadCode RJS 13Mar97				_Miles.PlayOnce(FIL_SFX_WOOD_BREAK2, (ItemBasePtr) ac);//RJS 22Nov96
//DeadCode RJS 13Mar97
//DeadCode RJS 13Mar97			if (	(whichbit == BF_LBWing)
//DeadCode RJS 13Mar97				||	(whichbit == BF_RBWing)	)
//DeadCode RJS 13Mar97			{
//DeadCode RJS 13Mar97				switch (whichbit)									//RJS 08Aug96
//DeadCode RJS 13Mar97				{
//DeadCode RJS 13Mar97					case BF_LBWing:
//DeadCode RJS 13Mar97						whichbit = BF_LTWing;
//DeadCode RJS 13Mar97					break;
//DeadCode RJS 13Mar97					case BF_RBWing:
//DeadCode RJS 13Mar97						whichbit = BF_RTWing;
//DeadCode RJS 13Mar97					break;
//DeadCode RJS 13Mar97				}
//DeadCode RJS 13Mar97
//DeadCode RJS 13Mar97				SetAircraftDammage(ac,worldptr,whichbit,BS_DEAD,noanim,nomovecode,blowup);//RJS 31Oct96
//DeadCode RJS 13Mar97			}
//DeadCode RJS 13Mar97
//DeadCode RJS 13Mar97			if ((!nomovecode) && (whichbit != BF_Gear))			//RJS 21Oct96
//DeadCode RJS 13Mar97				ac->movecode = AUTO_DEATHSEQUENCE;				//PD 12Sep96
//DeadCode RJS 13Mar97		}
//DeadCode RJS 13Mar97	}

}





//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AcDamageEffects
//Author		Robert Slater
//Date			Fri 2 Aug 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::AcDamageEffects(AirStruc*	ac, BitFlags	whichbit, BitStates	whatstate,WorldStuff&	worldptr)
{
//DeadCode RDH 02Sep98	AirStruc*	acptr = Manual_Pilot.ControlledAC2;				//RJS 13Nov96
//DeadCode RDH 02Sep98
//DeadCode RDH 02Sep98 //we have decided to do this at the end of the mission
//DeadCode RDH 02Sep98 //DeadCode RDH 09Sep96	SWord	moraledec = MORALE_STAGE / 8;
//DeadCode RDH 02Sep98 //DeadCode RDH 09Sep96
//DeadCode RDH 02Sep98 //DeadCode RDH 09Sep96	if (ac->ai.morale > moraledec)
//DeadCode RDH 02Sep98 //DeadCode RDH 09Sep96		ac->ai.morale -= moraledec;
//DeadCode RDH 02Sep98
//DeadCode RDH 02Sep98	switch (whichbit)
//DeadCode RDH 02Sep98	{
//DeadCode RDH 02Sep98		case BF_LBWing:
//DeadCode RDH 02Sep98		case BF_LTWing:
//DeadCode RDH 02Sep98		case BF_RBWing:
//DeadCode RDH 02Sep98		case BF_RTWing:
//DeadCode RDH 02Sep98		case BF_Tail:
//DeadCode RDH 02Sep98		case BF_Gear:
//DeadCode RDH 02Sep98			if (whatstate == BS_DAMLV2)
//DeadCode RDH 02Sep98			{
//DeadCode RDH 02Sep98				_Miles.PlayOnce(FIL_SFX_WOOD_BREAK1, (ItemBasePtr) ac);//RJS 22Nov96
//DeadCode RDH 02Sep98				break;
//DeadCode RDH 02Sep98			}
//DeadCode RDH 02Sep98		case BF_Nose:
//DeadCode RDH 02Sep98		case BF_TheRest:										//RJS 31Oct96
//DeadCode RDH 02Sep98			_Miles.PlaySample((FileNum) (FIL_SFX_RICOCHET_CANVAS1 + Math_Lib.rnd(6)), (ItemBasePtr) ac);//RJS 22Nov96
//DeadCode RDH 02Sep98		break;
//DeadCode RDH 02Sep98		case BF_Pilot:
//DeadCode RDH 02Sep98		{
//DeadCode RDH 02Sep98			AircraftAnimData	*adptr = (AircraftAnimData*) ac->Anim;//RDH 16Dec96
//DeadCode RDH 02Sep98
//DeadCode RDH 02Sep98			if (whatstate == BS_DAMLV2)
//DeadCode RDH 02Sep98				if (ac->ai.morale > MORALE_POOR)
//DeadCode RDH 02Sep98					ac->ai.morale = MORALE_POOR;
//DeadCode RDH 02Sep98
//DeadCode RDH 02Sep98			if (whatstate == BS_DEAD)
//DeadCode RDH 02Sep98			{
//DeadCode RDH 02Sep98				if (ac == Manual_Pilot.ControlledAC2)
//DeadCode RDH 02Sep98				{
//DeadCode RDH 02Sep98					_Miles.PlayOnce(FIL_SFX_DYING_BREATH2, (ItemBasePtr) ac);//RJS 27Nov96
//DeadCode RDH 02Sep98					Manual_Pilot.controlmode=ManualPilot::PILOTDEAD;
//DeadCode RDH 02Sep98 //DeadCode ARM 08Dec96 // ZXCV					if (!_DPlay.Implemented)
//DeadCode RDH 02Sep98						GR_Quit3DNow=CRASHED_DEAD;					//RJS 13Nov96
//DeadCode RDH 02Sep98					if (acptr)
//DeadCode RDH 02Sep98						acptr->fly.redeffect = 1;				//RJS 14Nov96
//DeadCode RDH 02Sep98
//DeadCode RDH 02Sep98					adptr->itemstate = DEAD;					//RDH 16Dec96
//DeadCode RDH 02Sep98				}
//DeadCode RDH 02Sep98				else
//DeadCode RDH 02Sep98					_Miles.PlayOnce(FIL_SFX_DYING_BREATH2, (ItemBasePtr) ac,96);//RJS 27Nov96
//DeadCode RDH 02Sep98			}
//DeadCode RDH 02Sep98			else
//DeadCode RDH 02Sep98			{
//DeadCode RDH 02Sep98				if (ac == Manual_Pilot.ControlledAC2)
//DeadCode RDH 02Sep98					_Miles.PlayOnce((FileNum) (FIL_SFX_YELP1 + Math_Lib.rnd(3)), (ItemBasePtr) ac);//RJS 22Nov96
//DeadCode RDH 02Sep98				else
//DeadCode RDH 02Sep98					_Miles.PlayOnce((FileNum) (FIL_SFX_YELP1 + Math_Lib.rnd(3)), (ItemBasePtr) ac,96);//RJS 27Nov96
//DeadCode RDH 02Sep98			}
//DeadCode RDH 02Sep98
//DeadCode RDH 02Sep98		}
//DeadCode RDH 02Sep98		break;
//DeadCode RDH 02Sep98		case BF_Fuel:
//DeadCode RDH 02Sep98		{
//DeadCode RDH 02Sep98			_Miles.PlaySample((FileNum) (FIL_SFX_RICOCHET_CANVAS1 + Math_Lib.rnd(6)), (ItemBasePtr) ac);//RJS 22Nov96
//DeadCode RDH 02Sep98			switch (whatstate)
//DeadCode RDH 02Sep98			{
//DeadCode RDH 02Sep98				case BS_DAMLV1:									//RJS 27Nov96
//DeadCode RDH 02Sep98				{
//DeadCode RDH 02Sep98					AircraftAnimData*	adptr = (AircraftAnimData*) ac->Anim;
//DeadCode RDH 02Sep98
//DeadCode RDH 02Sep98 //DeadCode RJS 21May97					if (adptr->vapourtrail == 0)
//DeadCode RDH 02Sep98 //DeadCode RJS 23May97						LaunchVapourStream((mobileitem*)ac,worldptr);//RJS 13Nov96
//DeadCode RDH 02Sep98
//DeadCode RDH 02Sep98					break;
//DeadCode RDH 02Sep98				}
//DeadCode RDH 02Sep98				case BS_DEAD:
//DeadCode RDH 02Sep98				{
//DeadCode RDH 02Sep98					if (ac == Manual_Pilot.ControlledAC2)		//RJS 27May97
//DeadCode RDH 02Sep98						if (View_Object)
//DeadCode RDH 02Sep98							View_Object->SetToDeathView(DZ_Slow);		//RJS 27May97
//DeadCode RDH 02Sep98
//DeadCode RDH 02Sep98					_Miles.PlaySample((FileNum) (FIL_SFX_EXPLOSION_OILDRUM1+Math_Lib.rnd(6)), (ItemBasePtr) ac);//RJS 22Nov96
//DeadCode RDH 02Sep98					KillLauncher((itemptr)ac,worldptr);//RJS 21Oct96
//DeadCode RDH 02Sep98				}
//DeadCode RDH 02Sep98				break;
//DeadCode RDH 02Sep98			}
//DeadCode RDH 02Sep98		}
//DeadCode RDH 02Sep98		break;
//DeadCode RDH 02Sep98		case BF_Engine:
//DeadCode RDH 02Sep98		{
//DeadCode RDH 02Sep98			FormationItemPtr flauncher = *ac;					//RJS 02Oct96
//DeadCode RDH 02Sep98
//DeadCode RDH 02Sep98			_Miles.PlaySample((FileNum) (FIL_SFX_RICOCHET_METAL_TWANG + Math_Lib.rnd(4)), (ItemBasePtr) ac);//RJS 02Dec96
//DeadCode RDH 02Sep98
//DeadCode RDH 02Sep98			switch (whatstate)
//DeadCode RDH 02Sep98			{
//DeadCode RDH 02Sep98				case BS_DAMLV2:
//DeadCode RDH 02Sep98				{
//DeadCode RDH 02Sep98					if (ac == Manual_Pilot.ControlledAC2)
//DeadCode RDH 02Sep98						_Miles.KillEngine(flauncher->classtype,2);//RJS 03Dec96
//DeadCode RDH 02Sep98				}
//DeadCode RDH 02Sep98				break;
//DeadCode RDH 02Sep98				case BS_DEAD:
//DeadCode RDH 02Sep98				{
//DeadCode RDH 02Sep98					AircraftAnimData*	adptr = (AircraftAnimData*) ac->Anim;
//DeadCode RDH 02Sep98
//DeadCode RDH 02Sep98					if (ac == Manual_Pilot.ControlledAC2)
//DeadCode RDH 02Sep98						_Miles.KillEngine(flauncher->classtype,0);//RJS 21Oct96
//DeadCode RDH 02Sep98
//DeadCode RDH 02Sep98 //DeadCode RJS 27May97					if (adptr->vapourtrail)
//DeadCode RDH 02Sep98 //DeadCode RJS 27May97					{
//DeadCode RDH 02Sep98 //DeadCode RJS 27May97						if (ac == Manual_Pilot.ControlledAC2)	//RJS 14Nov96
//DeadCode RDH 02Sep98 //DeadCode RJS 27May97							View_Point.SetToDeathView(DZ_Slow);		//RJS 14Nov96
//DeadCode RDH 02Sep98 //DeadCode RJS 27May97
//DeadCode RDH 02Sep98 //DeadCode RJS 27May97						_Miles.PlaySample((FileNum) (FIL_SFX_EXPLOSION_OILDRUM1+Math_Lib.rnd(6)), (ItemBasePtr) ac);//RJS 22Nov96
//DeadCode RDH 02Sep98 //DeadCode RJS 27May97						KillLauncher((itemptr)ac,worldptr);
//DeadCode RDH 02Sep98 //DeadCode RJS 27May97					}
//DeadCode RDH 02Sep98 //DeadCode RJS 27May97					else
//DeadCode RDH 02Sep98 //DeadCode RJS 27May97					{
//DeadCode RDH 02Sep98						_Miles.PlaySample((FileNum) (FIL_SFX_EXPLOSION_DISTANT1+Math_Lib.rnd(2)), (ItemBasePtr) ac);//RJS 22Nov96
//DeadCode RDH 02Sep98						LaunchSmokeTrail((mobileitem*)ac,worldptr);
//DeadCode RDH 02Sep98 //DeadCode RJS 27May97					}
//DeadCode RDH 02Sep98				}
//DeadCode RDH 02Sep98				break;
//DeadCode RDH 02Sep98			}
//DeadCode RDH 02Sep98		}
//DeadCode RDH 02Sep98		break;
//DeadCode RDH 02Sep98	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		KillLauncher
//Author		Paul.
//Date			Wed 1 May 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void TransObj::KillLauncher(itemptr launcher,ItemPtr killer,WorldStuff& world,SByte	gindex,Coords3D*	hitcoords,Bool	airtoair)//JIM 11Mar99
{
	//Brought back from the dead.....
	if (launcher->Status.size==AirStrucSize)
	{
		AirStrucPtr	ac = (AirStrucPtr) launcher;

//DeadCode AMM 31Mar99		if (!(_DPlay.Implemented || _Replay.Record))
		if (!_DPlay.Implemented)								//AMM 31Mar99
			SHAPE.DetatchAllVapourStreams(ac);

		if (Manual_Pilot.DeathSequenceOverride(ac,AUTO_SPIRAL2GROUND)==TRUE)
		{
//DeadCode AMM 31Mar99			if (!(_DPlay.Implemented || _Replay.Record))
			if (!_DPlay.Implemented)							//AMM 31Mar99
				ExplodeAC(ac,killer,world);						//JIM 11Mar99

//DeadCode AMM 24Mar99			else												//AMM 04Mar99
//DeadCode AMM 04Mar99			if (airtoair)										//AMM 08Jan99
			if (_DPlay.Implemented || _Replay.Record)
			{
			// Send ac_collision packet....

				_DPlay.NewKillLauncher(ac->uniqueID.count);
			}
		}
	}
}


/////////////////////////////////////////////////////////////////////////////////
//
//							Weapons code.
//
/////////////////////////////////////////////////////////////////////////////////

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		RechargeWeapons
//Author		Robert Slater
//Date			Wed 11 Jun 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::ReloadWeapons(AirStrucPtr	ac)
{
	AircraftAnimData*	adptr = (AircraftAnimData*) ac->Anim;
	WeapAnimData*	weapon;
	int				index;

	for (index=0; index < 8; index++)
	{
		weapon = &adptr->weaponlaunchers[index];
		if (	weapon
			&& (weapon->LauncherType < LT_FUEL)	)
				weapon->LoadedStores = weapon->Stores;
	}

	if (!Save_Data.gamedifficulty[GD_UNLIMITEDARM])				//RJS 06May99
		SHAPE.ReloadMassAndDrag(ac);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DumpFuel
//Author		Robert Slater
//Date			Wed 11 Jun 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool	TransObj::DumpFuel(AirStrucPtr	ac, WorldStuff& world, Bool byaccident)
{
	SLong	xpos, ypos, zpos;
	AircraftAnimData*	adptr = (AircraftAnimData*) ac->Anim;
	WeapAnimData*	weapon;
	int	index;
	UWord	mvel,mdelay,mburst;									//RDH 31Jul98
	int	failchance;
	Bool	alreadydumped = ac->weap.FuelDumped;				//RJS 03Jun99

	for (index=0; index < 8; index++)
	{
		weapon = &adptr->weaponlaunchers[index];
		if (weapon && (weapon->LauncherType == LT_FUEL))
		{
			weapon = SHAPE.GetWeaponLauncher(ac,index,xpos,ypos,zpos,mvel,mdelay,mburst,LT_FUEL);//RJS 04Feb99
			if (weapon && weapon->LoadedStores && weapon->stationshape)		//must be external launcher
			{
				if ((ac == Persons2::PlayerSeenAC) || (ac == ac->Leader()))//RJS 04Feb99
					failchance = 0;
				else
					failchance = weapon->SubDamage * Math_Lib.rnd();
	
				if (failchance < 1048544)						//RJS 27May98
				{
					if (ac==Persons2::PlayerSeenAC)
					{
						_DPlay.NewBullet(1,index);
					}

					SHAPE.ReduceLauncherLoad(ac,index);
					ac->weap.UseIntFuel = TRUE;							//RJS 23Jun98
					ac->weap.FuelDumped = TRUE;							//RJS 23Jun98

					_Miles.PlayOnce (FIL_SFX_JETTISON_FUEL, (ItemBasePtr) ac,96);
					LaunchWeapon(false,ac,weapon,xpos,ypos,zpos,world,mvel,TRUE);//RJS 27May98
					weapon->LoadedStores = 0;										//RDH 03Aug98
				}
				else
				{
					if (!byaccident && ac->PlayerInGroup())
					{
						_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_HUNGTANK, MSG_STATUSRESPONSE_X, ac, ac, ac->GroupLeader()));
						_Radio.TriggerMsg(MESSAGE_STRUC (SCRIPT_CALLEE_HUNGTANKREPLY, MSG_STATUSRESPONSEREPLY_DELAY_LP_RPT, ac->GroupLeader(), ac, ac));//RDH 18May99
						ac->/*FormationItem::*/BreakForm();		//GO HOME	//CSB 23/05/99	 //JIM 09/09/99
						ac->waypoint = NULL;							//CSB 23/05/99	
						ac->movecode = AUTO_FOLLOWWP;					//CSB 23/05/99	
					}
				}
			}
		}
	}

	return(alreadydumped);										//RJS 03Jun99
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DumpWeapons
//Author		Robert Slater
//Date			Wed 11 Jun 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::DumpWeapons(AirStrucPtr	ac, WorldStuff& world)
{
	if (!Save_Data.gamedifficulty[GD_UNLIMITEDARM])				//RJS 06May99
	{
		SLong	xpos, ypos, zpos;
		AircraftAnimData*	adptr = (AircraftAnimData*) ac->Anim;
		WeapAnimData*	weapon;
		int	index;
		UWord	mvel,mdelay,mburst;									//RDH 31Jul98
		int		failchance;

		// Dump rockets.....
		for (index=0; index < 8; index++)
		{
			weapon = &adptr->weaponlaunchers[index];
			if (weapon)
			{
				if ((weapon->LauncherType & LT_MASK) == LT_ROCKET)
				{
					failchance = weapon->SubDamage * Math_Lib.rnd();
					if (failchance < 1048544)
					{
						weapon = SHAPE.GetWeaponLauncher(ac,index,xpos,ypos,zpos,mvel,mdelay,mburst,LT_ROCKET);//RDH 31Jul98
						if (weapon && weapon->LoadedStores)
						{
							if (ac==Persons2::PlayerSeenAC)		//AMM 21Apr99
							{									//AMM 21Apr99
								_DPlay.NewBullet(1,index);		//AMM 21Apr99
							}									//AMM 21Apr99

							_Miles.PlayOnce (FIL_SFX_JETTISON_FUEL, (ItemBasePtr) ac,96);

							SHAPE.ReduceLauncherLoad(ac,index,weapon->LoadedStores);
							while (weapon->LoadedStores)
							{
								LaunchWeapon(false,ac,weapon,xpos,ypos,zpos,world,mvel,mdelay,TRUE);
								
								weapon = SHAPE.GetWeaponLauncher(ac,index,xpos,ypos,zpos,mvel,mdelay,mburst,LT_ROCKET);
								if (!weapon)
									break;
							}
							ac->weap.StoresDumped = TRUE;
						}
					}
				}
			}
		}

		// Dump bombs.....
		for (index=0; index < 8; index++)
		{
			weapon = &adptr->weaponlaunchers[index];
			if (weapon)
			{
				if ((weapon->LauncherType & LT_MASK) == LT_BOMB)
				{
					failchance = weapon->SubDamage * Math_Lib.rnd();
					if (failchance < 1048544)
					{
						weapon = SHAPE.GetWeaponLauncher(ac,index,xpos,ypos,zpos,mvel,mdelay,mburst,LT_BOMB);//RDH 31Jul98
						if (weapon && weapon->LoadedStores)
						{
							if (ac==Persons2::PlayerSeenAC)		//AMM 21Apr99
							{									//AMM 21Apr99
								_DPlay.NewBullet(1,index);		//AMM 21Apr99
							}									//AMM 21Apr99

							_Miles.PlayOnce (FIL_SFX_JETTISON_FUEL, (ItemBasePtr) ac,96);

							SHAPE.ReduceLauncherLoad(ac,index,weapon->LoadedStores);
							while (weapon->LoadedStores)
							{
								LaunchWeapon(false,ac,weapon,xpos,ypos,zpos,world,mvel,mdelay,TRUE);
							}
						}
					}
				}
			}
		}

		// Dump napalm.....
		for (index=0; index < 8; index++)
		{
			weapon = &adptr->weaponlaunchers[index];
			if (weapon)
			{
				if ((weapon->LauncherType & LT_MASK) == LT_NAPALM)
				{
					failchance = weapon->SubDamage * Math_Lib.rnd();
					if (failchance < 1048544)
					{
						weapon = SHAPE.GetWeaponLauncher(ac,index,xpos,ypos,zpos,mvel,mdelay,mburst,LT_NAPALM);//RDH 31Jul98
						if (weapon && weapon->LoadedStores)
						{
							if (ac==Persons2::PlayerSeenAC)		//AMM 21Apr99
							{									//AMM 21Apr99
								_DPlay.NewBullet(1,index);		//AMM 21Apr99
							}									//AMM 21Apr99

							_Miles.PlayOnce (FIL_SFX_JETTISON_FUEL, (ItemBasePtr) ac,96);

							SHAPE.ReduceLauncherLoad(ac,index,weapon->LoadedStores);
							while (weapon->LoadedStores)
							{
								LaunchWeapon(false,ac,weapon,xpos,ypos,zpos,world,mvel,mdelay,TRUE);
							}
						}
					}
				}
			}
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ReActivateStation
//Author		Robert Slater
//Date			Wed 16 Sep 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
SLong	TransObj::ReActivateStation(AirStrucPtr	ac, UWord &muzVel, UWord &ammotot, UWord	&muzdelay, WorldStuff& world, Bool isUnarmed)//RJS 16Sep98
{
	LnchrType			currentweapon;
	SLong				xpos, ypos, zpos;							
	SLong				usexpos, useypos, usezpos;							
	WeapAnimData*		weapon;
	WeapAnimData*		useweapon;
	AircraftAnimData*	adptr = (AircraftAnimData*) ac->Anim;
	SLong				currindex = adptr->currweapindex;
	SLong				index = -1;								//RJS 16Sep98
	SLong				retval;									//RJS 16Sep98
	SLong				highestammo = 0;
	UWord				mvel,mdelay,mburst;						//RDH 31Jul98
	SWord				foundWeap,noAmmo;

	foundWeap = noAmmo = 0;										//RJS 25Jan99
	ammotot = 0;												//RJS 09Sep98
	muzdelay = 5;												//RJS 23Jul98
	muzVel = 0;													//RJS 16Sep98
	useweapon = NULL;
	currentweapon = (LnchrType) (ac->weap.weapontype & LT_MASK);
	index = 0;
	while (index < 8)
	{
		weapon = SHAPE.GetWeaponLauncher(ac,index,xpos,ypos,zpos,mvel,mdelay,mburst,currentweapon);//RDH 31Jul98
		if (weapon)
		{
			foundWeap++;
			ammotot += weapon->LoadedStores;
			if (weapon->LoadedStores > highestammo)	
			{
				highestammo = weapon->LoadedStores;
				useweapon = weapon;
				usexpos = xpos;
				useypos = ypos;
				usezpos = zpos;
				currindex = index;
				muzdelay = mdelay;
				muzVel = mvel;//RJS 16Sep98
			}
			else
				noAmmo++;
		}
		index++;
	}

	if (useweapon)
	{
		if (ac==Persons2::PlayerSeenAC)
		{
			_DPlay.NewBullet(1,currindex);
			if (!_Replay.Record && Save_Data.gamedifficulty[GD_GUNCAMERAONTRIGGER])//AMM 23Apr99
			{													//AMM 23Apr99
// if next frame we are going to start a record, then first frame will be this
// weapon launch that initiated it

				_Replay.DelayedWeapon=currindex;				//AMM 23Apr99
			}													//AMM 23Apr99

			//If you're on the ground, no damage.
//			if (ac->fly.pModel->GearTouched)					//RJS 10Jun99
//				isUnarmed = TRUE;								//RJS 10Jun99		
		}

//DeadRJS		ammotot -= 1;											//RJS 09Sep98

		retval = currindex;										//RJS 16Sep98
		ammotot -= LaunchWeapon(false,ac,useweapon,usexpos,useypos,usezpos,world,muzVel,muzdelay,isUnarmed);//RJS 11Jun99
	}
	else
	{
		retval = -1;											//RJS 16Sep98
		if ((noAmmo == foundWeap) && Save_Data.gamedifficulty[GD_UNLIMITEDARM])//RJS 06May99	
		{
			//Reload...
			ReloadWeapons(ac);
		}
	}

	adptr->currweapindex = currindex;

	return(retval);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		WeaponSearch
//Author		Robert Slater
//Date			Tue 10 Jun 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::WeaponSearch(AirStrucPtr	ac, WeapSearchType	direction, Bool wrap)
{
	WeapAnimData*	weapon;
	SLong			index, currtype, nextval, thisval;
	SLongP			botptr,topptr;
	AircraftAnimData*	adptr = (AircraftAnimData*) ac->Anim;
	Bool			isOk = FALSE;

	if (direction == Go_Instant)
	{
		currtype = ac->weap.weapontype - 1;
		nextval = ac->weap.weapontype + 1;

		botptr = &currtype;
		topptr = &nextval;
	}
	else
	{
		currtype = ac->weap.weapontype;
		if (direction == Go_Forward)
		{
			botptr = &currtype;
			topptr = &nextval;
			nextval = LT_FUEL;
		}
		else
		{
			botptr = &nextval;
			topptr = &currtype;
			nextval = -1;
		}
	}

	for (index=0; index < 8; index++)
	{
		weapon = &adptr->weaponlaunchers[index];
		if (weapon)
		{
			thisval = weapon->LauncherType;
			if (thisval < LT_FUEL)
			{
				if (	(thisval > *botptr)
					&&	(thisval < *topptr)	)
					nextval = thisval;
			}
		}
	}

	if (	(nextval > -1)
		&&	(nextval < LT_FUEL)	)
		isOk = TRUE;											//RJS 13May99
	else														//RJS 13May99
	{															//RJS 13May99
		if (wrap)												//RJS 13May99
		{														//RJS 13May99
			isOk = TRUE;										//RJS 13May99
			nextval = adptr->weaponlaunchers[0].LauncherType;	//RJS 13May99
		}														//RJS 13May99
	}															//RJS 13May99

	if (isOk)													//RJS 13May99
	{
		if (ac == Manual_Pilot.ControlledAC2)					//RJS 09Sep98
		{
			PolyPitAnimData*	ppitanim = (PolyPitAnimData*) adptr;
			UWord				ammoleft = 0;

			// Another search, for rounds total...
			for (index=0; index < 8; index++)
			{
				weapon = &adptr->weaponlaunchers[index];
				if (weapon && (weapon->LauncherType == nextval))
					ammoleft += weapon->LoadedStores;
			}

			ppitanim->acammoleft = ammoleft;
			ppitanim->acprevammoleft = ammoleft;					//RJS 17Jun99

//Dead			_Miles.PlayOnce (FIL_SFX_GUN_CLICK1, (ItemBasePtr) ac,64);//RJS 13May99
			if (direction != Go_Instant)
			{
				_DamageChat.SayWeapon(nextval);
				_Miles.PlaySample(FIL_SFX_OFFICE_BUTTON3,(ItemPtr)NULL,256);
			}
		}									

		ac->weap.weapontype = nextval;
	}
	else
	{
		if (ac==Manual_Pilot.ControlledAC2)
			_DamageChat.SayWeapon(ac->weap.weapontype);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ControlKeybWeap
//Author		Paul.
//Date			Mon 29 Apr 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void TransObj::ControlKeybWeap(AirStrucPtr ac,WorldStuff& world)
{
	if (	ac													//RJS 10Jun97
		&& (ac->movecode != AUTO_RESURRECT)	)					//RJS 10Jun97
	{
		WeapAnimData*	weapon;										//RJS 29Aug96
		SLong			xpos, ypos, zpos;							//RJS 29Aug96
		UByte			index;										//RJS 29Aug96
		UWord			thisstore;									//RJS 10Sep96
		SWord			frametime = Timer_Code.FRAMETIME;			//RDH 03Oct96
		PolyPitAnimData*	adptr = (PolyPitAnimData *)ac->Anim;//RJS 10Jun97
		LnchrType		currentweapon = (LnchrType)ac->weap.weapontype;	//RJS 10Jun97
		UWord			mdelay;											//RJS 23Jul98
		UWord			ammoleft;								//RJS 09Sep98

		if (adptr->itemstate != ALIVE)
			return;

//DeadCode RJS 03Dec98		if (fakeshootdelay <= 0)
//DeadCode RJS 03Dec98		{
//DeadCode RJS 03Dec98			// Launch fake bullet for gunsight code....
//DeadCode RJS 03Dec98
//DeadCode RJS 03Dec98			fakeshootdelay = 25;
			SHAPE.CalcRadarRange(ac);
//DeadCode MS 30Nov98			LaunchTrackedBullet(ac,world);
//DeadCode RJS 03Dec98		}
//DeadCode RJS 03Dec98		else
//DeadCode RJS 03Dec98			fakeshootdelay -= frametime;

		if (Key_Tests.KeyPress3d(WINGSPANUP) || Key_Tests.KeyHeld3d(WINGSPANUP))
			SHAPE.WingSpanUp();

		if (Key_Tests.KeyPress3d(WINGSPANDOWN) || Key_Tests.KeyHeld3d(WINGSPANDOWN))
			SHAPE.WingSpanDown();

		if (Key_Tests.KeyPress3d(GUNRANGEUP) || Key_Tests.KeyHeld3d(GUNRANGEUP))
			SHAPE.GunRangeUp();

		if (Key_Tests.KeyPress3d(GUNRANGEDOWN) || Key_Tests.KeyHeld3d(GUNRANGEDOWN))
			SHAPE.GunRangeDown();


/*		if (Key_Tests.KeyPress3d(DETAILDIALS))
		{
			SHAPE.ForceDamage(Manual_Pilot.ControlledAC2,&adptr->RIGHTWINGIN,BS_DEAD);
			SHAPE.ForceDamage(Manual_Pilot.ControlledAC2,&adptr->LEFTWINGIN,BS_DEAD);
		}*/


//DeadCode RJS 23Mar99		if (Key_Tests.KeyPress3d(CANOPYEJECT))					//RJS 20Apr98
//DeadCode RJS 23Mar99			LaunchCanopyEject(ac,world);						//RJS 19Feb98

//DeadCode RJS 05May99		if (Key_Tests.KeyPress3d(EJECTPILOT))					//RJS 19Feb98
//DeadCode RJS 05May99		{
//DeadCode RJS 05May99			if (_DPlay.Implemented || _Replay.Record)			//AMM 21Apr99
//DeadCode RJS 05May99			{													//AMM 21Apr99
//DeadCode RJS 05May99				_DPlay.NewSpecial(PIDC_EJECT,0,0,0);			//AMM 21Apr99
//DeadCode RJS 05May99			}													//AMM 21Apr99
//DeadCode RJS 05May99			else												//AMM 21Apr99
//DeadCode RJS 05May99				LaunchCanopyEject(ac,world);						//RJS 19Feb98
//DeadCode RJS 05May99 //DeadCode RJS 23Mar99			LaunchParachute(ac,world);							//RJS 19Feb98
//DeadCode RJS 05May99		}

		if (Key_Tests.KeyPress3d(LASTWEAPON))					
			WeaponSearch(ac,Go_Backward);

		if (Key_Tests.KeyPress3d(NEXTWEAPON))					
			WeaponSearch(ac,Go_Forward);

//Dead#pragma message(__HERE__ "activate weapon cycle key here, when key is available...")
		if (Key_Tests.KeyPress3d(CYCLETHROUGHWEAPONS))
			WeaponSearch(ac,Go_Forward,TRUE);

		AirStrucPtr	buddy;
		if (Key_Tests.KeyPress3d(DUMPFUEL))						
		{
			if (!DumpFuel(ac,world))							//RJS 03Jun99
			{
				if (Manual_Pilot.ControlledAC2->formpos == 0)				//RDH 16/05/99
				{
					buddy = Manual_Pilot.ControlledAC2->FindBuddy();			//RDH 09/05/99
					if (buddy)													//RDH 09/05/99
						OverLay.HotKeyTriggerMessage(SEL_2,SEL_3);
				}
			}
		}

		if (Key_Tests.KeyPress3d(DUMPWEAPONS))					//RJS 27May98
		{
			DumpWeapons(ac,world);								//RDH 28Apr99
			if (Manual_Pilot.ControlledAC2->formpos == 0)				//RDH 16/05/99
			{
				buddy = Manual_Pilot.ControlledAC2->FindBuddy();			//RDH 09/05/99
				if (buddy)													//RDH 09/05/99
	//DEAD				Art_Int.SendMsgAndCall(MESSAGE_STRUC(SCRIPT_JETTISONSTORES,MSG_STATUSREQUEST,ac,NULL,ac), JettisonStores);
						OverLay.HotKeyTriggerMessage(SEL_2,SEL_2);
			}
		}

		if (	Key_Tests.KeyPress3d(RELOADWEAPON))		//RJS 11May99
//DEADCODE RDH 11/05/99			&&	Save_Data.gamedifficulty[GD_RELOADARMS]	)		//RJS 25Jan99
			ReloadWeapons(ac);

		if (Key_Tests.KeyPress3d(VOICETOGGLE))					//RJS 30Jun99
		{														//RJS 30Jun99
			if (Save_Data.gamedifficulty[GD_NOPLAYERVOICE])		//RJS 30Jun99
				Save_Data.gamedifficulty %= GD_NOPLAYERVOICE;	//RJS 30Jun99
			else												//RJS 30Jun99
				Save_Data.gamedifficulty |= GD_NOPLAYERVOICE;	//RJS 30Jun99
		}														//RJS 30Jun99

		if (Key_Tests.KeyPress3d(SHOOT))						//RJS 10Jun97
		{
			ac->weap.currentbullet = NULL;							//RJS 03Jun99
			SLong	timeleft = ac->weap.ShootDelay-frametime;//RJS 10Jun97
			if (timeleft<0)
			{
				if (Save_Data.gamedifficulty[GD_GUNCAMERAONTRIGGER] && !_DPlay.Implemented && !_Replay.Record)//AMM 05Jan99
				{
					_Replay.StartRecordFlag=TRUE;					//AMM 05Jan99
					_Replay.guncameradelay=BULLETDELAY;
				}

				SLong	wpindex = ActivateStation(ac,ammoleft,mdelay,world);//RJS 17Jun99
				if (wpindex == -1)									//RJS 17Jun99
				{
	//				_Miles.SequenceAudible(FIL_MUSIC_GOING_BADLY);
					_Miles.PlaySample (FIL_SFX_GUN_CLICK4, (ItemBasePtr) ac,64);
					_Miles.StopShooting();							//RJS 25May99
				}
				else
					adptr->lastweapindex = wpindex;					//RJS 17Jun99

// in case bomb has dropped - want to keep bomb delay

				if (_Replay.guncameradelay<BULLETDELAY)			//RDH 30Mar99
					_Replay.guncameradelay=BULLETDELAY;			//RDH 30Mar99

				adptr->acammoleft = ammoleft;						//RJS 09Sep98
				adptr->acprevammoleft = ammoleft;					//RJS 17Jun99
				timeleft = mdelay;									//RJS 25Jan99
			}
			ac->weap.ShootDelay = timeleft;
		}
		else
		{
//DeadCode RJS 23Jul98			if (	(	Key_Tests.KeyHeld3d(SHOOT)				//RJS 10Jun97
//DeadCode RJS 23Jul98					 && ((LT_BULLET & LT_MASK)==currentweapon))	//RJS 10Jun97
//DeadCode RJS 23Jul98				||	autobulletcount								)//RJS 10Jun97
			if (Key_Tests.KeyHeld3d(SHOOT))						//RJS 23Jul98
			{
				// cannot drop multiple bombs, causes cock-up
				if ((ac->weap.weapontype & LT_MASK) != LT_BOMB)						//RJS 11May99
				{
					if (Save_Data.gamedifficulty[GD_GUNCAMERAONTRIGGER] && !_DPlay.Implemented && !_Replay.Record)//AMM 05Jan99
					{
						_Replay.StartRecordFlag=TRUE;					//AMM 05Jan99
	//					_Replay.guncameradelay=BULLETDELAY;
					}

	// in case bomb has dropped - want to keep bomb delay

					if (_Replay.guncameradelay<BULLETDELAY)						//AMM 25Jan99
						_Replay.guncameradelay=BULLETDELAY;				//AMM 25Jan99

					//Subsequent shots

					SLong	timeleft = ac->weap.ShootDelay-frametime;//RJS 10Jun97
					if (timeleft<0)
					{
						UWord	mvel;
						SLong	wpindex = ReActivateStation(ac,mvel,ammoleft,mdelay,world);//RJS 16Feb00
						if (wpindex == -1)									//RJS 16Feb00
						{
							adptr->shooting = 0;							//RJS 17Jun99
							ReduceBulkStores(ac,(UByteP)adptr);				//RJS 17Jun99

							_Miles.StopShooting();							//RJS 25May99

	//						_Miles.SequenceAudible(FIL_MUSIC_GOING_BADLY);
	//						_Miles.PlaySample (FIL_SFX_GUN_CLICK4, (ItemBasePtr) ac,64);
						}
						else
						{
// To guard against coming into the 3D with the shoot key held...
							if (adptr->lastweapindex == 0xFF)				//RJS 16Feb00
							{
								adptr->lastweapindex = wpindex;
								adptr->acprevammoleft = ammoleft;
							}
						}

						adptr->acammoleft = ammoleft;						//RJS 09Sep98
						timeleft = mdelay;

	//					if (autobulletcount--<0)
	//						autobulletcount=0;
					}
					ac->weap.ShootDelay = timeleft;
				}
			}
			else											//RJS 16Sep98
			{
				ReduceBulkStores(ac,(UByteP)adptr);						//RJS 17Jun99

				adptr->shooting = 0;							//RJS 06Jun99

				_Miles.StopShooting();							//RJS 12Apr99
				ac->weap.currentbullet = NULL;					//RJS 29Mar99
				ac->weap.ShootDelay = 0;						//RJS 20Apr99
				if (ac->weap.weapforce)							//RJS 20Apr98
					ac->SetWeaponForce();						//RJS 16Sep98

				if (_Replay.Record
				&& Save_Data.gamedifficulty[GD_GUNCAMERAONTRIGGER]
				&& !Save_Data.gamedifficulty[GD_GUNCAMERAATSTART])
				{
					if (!_Replay.guncameradelay--)
					{
//DeadCode AMM 02Jul99 						_Replay.clearreplaybuffers=true;
// done in stop record
//DeadCode AMM 08Jul99 						_Replay.ClearReplayBuffers();			//AMM 02Jul99
						_Replay.StopRecord();
					}
				}
			}
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		TestForItem2Kill
//Author		Paul.
//Date			Fri 3 May 1996
//
//Description	Demo routine - tests for a value in uiddeathitem and
//				kills the item using the method set in deathtype
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void TransObj::TestForItem2Kill(WorldStuff& world)
{
	if (uiddeathitem)
	{
		MinAnimData* adptr;

		UniqueID	tmpuid = (UniqueID )uiddeathitem;

		itemptr		tmpitem;

		mobileitem	launcher;

		tmpitem = (itemptr )MobileItem::currworld->ConvertPtrUID(tmpuid);

		adptr = (MinAnimData *)tmpitem->Anim;

		launcher.World = tmpitem->World;

		switch ((DeathType )deathtype)
		{
			case DT_BigGround:
				LaunchGroundExplosion(launcher,world);
				adptr->itemstate=DEAD;
				break;
			case DT_GroundSmoke:
				LaunchGroundExplosion(launcher,world);
				adptr->itemstate=DEAD;
				break;
			case DT_AirDelay:
				LaunchSmokeTrail((mobileitem* )tmpitem,world);
				break;
			case DT_AirInstant:
				KillLauncher((itemptr )tmpitem,tmpitem,world);	//JIM 11Mar99
				break;
		}
	}
	uiddeathitem = 0;
	deathtype = 0;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		PilotedACHit
//Author		Robert Slater
//Date			Mon 14 Oct 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void TransObj::PilotedACHit()
{
	TargetSize	tsz = Save_Data.targetsize;
	Save_Data.targetsize = TS_MIN;

	if (	Save_Data.gamedifficulty[GD_COLLISIONS]				//RJS 25Jan99
		&&	!(Manual_Pilot.ControlledAC2->Status.deadtime)
		&&	(!View_Point ||!((ViewPoint*)View_Point)->Accel())
//DEADCODE DAW 28/03/99		&&	!Timer_Code.accel
//#pragma warnmsg("Paul: test for accel")
		)
	{
//DeadCode RJS 20May99 		itemptr	 hititem;
//DeadCode RJS 20May99 		Coords3D	hitcoords;
//DeadCode RJS 20May99 		int	gindex;
//DeadCode RJS 20May99 		WorldStuff&	world = *Manual_Pilot.ControlledAC2->currworld;

		BoxCol::NineSectorColThisPiloted(Manual_Pilot.ControlledAC2);//RJS 20May99
	}

	Save_Data.targetsize = tsz;									//PD 29Sep96
}




//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CommsACHit
//Author		Andrew McRae
//Date			Tue 8 Oct 1996
//
//Description	Comms equivalent of PilotedACHit()
//
//Inputs		Aircraft ptr and hit object.
//
//Returns	
//
//------------------------------------------------------------------------------
//DeadCode AMM 28Apr99 void TransObj::CommsACHit (AirStrucPtr hititem1, itemptr hititem2)
//DeadCode AMM 28Apr99 {
//DeadCode AMM 28Apr99
//DeadCode AMM 28Apr99	WorldStuff&	world = *hititem1->currworld;
//DeadCode AMM 28Apr99
//DeadCode AMM 28Apr99	if (	(hititem1 == Manual_Pilot.ControlledAC2)
//DeadCode AMM 28Apr99		||	(hititem2 == Manual_Pilot.ControlledAC2)	)
//DeadCode AMM 28Apr99		View_Object->SetToDeathView();							//RDH 02Sep98
//DeadCode AMM 28Apr99
//DeadCode AMM 28Apr99	if (	(hititem1->shape != WRECK)
//DeadCode AMM 28Apr99		&&	(hititem1->shape != CRATER)
//DeadCode AMM 28Apr99		&&	(hititem1->shape != PDEATH)	)
//DeadCode AMM 28Apr99		 KillLauncher((itemptr)hititem1,hititem1,world);		//JIM 11Mar99
//DeadCode AMM 28Apr99
//DeadCode AMM 28Apr99	if (	(hititem2->shape != WRECK)
//DeadCode AMM 28Apr99		&&	(hititem2->shape != CRATER)
//DeadCode AMM 28Apr99		&&	(hititem2->shape != PDEATH)	)
//DeadCode AMM 28Apr99		 KillLauncher((itemptr)hititem2,hititem2,world);		//JIM 11Mar99
//DeadCode AMM 28Apr99
//DeadCode AMM 28Apr99
//DeadCode AMM 28Apr99 //DeadCode AMM 01Jun98 #ifdef LOGENTRY
//DeadCode AMM 28Apr99 //DeadCode AMM 01Jun98						_DPlay.LogEntry ("CommsACHit");
//DeadCode AMM 28Apr99 //DeadCode AMM 01Jun98 #endif
//DeadCode AMM 28Apr99 //DeadCode AMM 01Jun98
//DeadCode AMM 28Apr99 //DeadCode AMM 01Jun98	WorldStuff&	world = *Me->currworld;
//DeadCode AMM 28Apr99 //DeadCode AMM 01Jun98
//DeadCode AMM 28Apr99 //DeadCode AMM 01Jun98	MinAnimData* mad =
//DeadCode AMM 28Apr99 //DeadCode AMM 01Jun98		(MinAnimData* )Me->Anim;//RJS 05Sep96
//DeadCode AMM 28Apr99 //DeadCode AMM 01Jun98
//DeadCode AMM 28Apr99 //DeadCode AMM 01Jun98	if (mad->itemstate != DEAD)
//DeadCode AMM 28Apr99 //DeadCode AMM 01Jun98		 KillLauncher((itemptr)Me,world);//RJS 05Sep96
//DeadCode AMM 28Apr99 //DeadCode AMM 01Jun98
//DeadCode AMM 28Apr99 //DeadCode AMM 01Jun98	mad = (MinAnimData* )hititem->Anim;
//DeadCode AMM 28Apr99 //DeadCode AMM 01Jun98
//DeadCode AMM 28Apr99 //DeadCode AMM 01Jun98	if (mad->itemstate != DEAD)
//DeadCode AMM 28Apr99 //DeadCode AMM 01Jun98		KillLauncher((itemptr)hititem,world);
//DeadCode AMM 28Apr99 //DeadCode AMM 01Jun98
//DeadCode AMM 28Apr99 //DeadCode AMM 01Jun98	gindex = gindex;
//DeadCode AMM 28Apr99 //DeadCode AMM 01Jun98
//DeadCode AMM 28Apr99 }

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ExecuteAnimation
//Author		Robert Slater
//Date			Mon 18 Jan 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::ExecuteAnimation(	ItemPtr				itm,
									UWord				hitshape,
									ItemPtr				hitter,
									HitEffectRecord&	hitstruc,
									WorldStuff&		worldptr)
{



}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ExecuteAnimation
//Author		Robert Slater
//Date			Thu 27 Feb 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::ExecuteAnimation(	ItemPtr		itm,
									ItemPtr		theShooter,
									UWord		hitshape,
									Coords3D	hitCoords,
									WorldStuff&	worldptr,
									SLong		val,
									SLong		randval,
									UByteP		weapptr,
									Coords3D	hitterCoords,	//RJS 02Dec98
									Coords3D	grpCoords,		//RJS 02Dec98
									SLong		damagestrength,	//RJS 07Dec98
									SByte		groupindex)
{
	DeathNum	animnum = (DeathNum) val;
	ShapeNum	shapehit = (ShapeNum)hitshape;					//RJS 16Nov98
	Coords3D	oldcoords = itm->World;
	mobileitem*		hitpositm = (mobileitem*) itm;		// Crap fix ... use hitcoords
	SLong		grounddist;
	Bool		noDirt = FALSE;

//DeadCode RJS 11Jun99 //DeadCode RJS 11Jun99 	if (WithinVisibleRange(hitCoords,SHAPESTUFF.GetShapePtr(shapehit)->MaxDrawRange))//RJS 30Apr99
//DeadCode RJS 11Jun99 //if (WithinVisibleRange(hitCoords,400000))					//RJS 11Jun99
//DeadCode RJS 11Jun99 	{
		hitpositm->World = hitCoords;								//RJS 02Dec98

		switch ((int)animnum)												//JIM 29/03/99
		{
			case ANIM_BIGEXPLOSION:
				if (WithinVisibleRange(hitCoords,400000))		//RJS 11Jun99
				{
					_Miles.PlaySample((FileNum) (FIL_SFX_EXPLOSION_GROUND+Math_Lib.rnd(5)), (ItemBasePtr) itm);//RJS 05Dec96
					LaunchExplosion(hitpositm,worldptr);
				}
				break;
			case ANIM_SMALLEXPLOSION:
			{
				if (WithinVisibleRange(hitCoords,400000))		//RJS 11Jun99
				{
					ShapeNum	oldshape = hitpositm->shape;
					hitpositm->shape = shapehit;
					LaunchSparkDebris(hitpositm,worldptr);		//Temporary...
					LaunchMiniExplosion(hitpositm,worldptr);//rjs 28aug98
					hitpositm->World = grpCoords;
					LaunchScatteredFire(hitpositm,shapehit,worldptr);
					hitpositm->World = hitCoords;
					hitpositm->shape = oldshape;
				}
				break;
			}
			case ANIM_GROUNDDEBRIS:
				if (WithinVisibleRange(hitCoords,200000))		//RJS 11Jun99
					LaunchDirtyFingers(hitpositm,worldptr);		//RJS 11Jun99
				break;
			case ANIM_SMALLDEBRIS:
			case ANIM_SMALLSPARK:
				if (WithinVisibleRange(hitCoords,50000))		//RJS 11Jun99
					LaunchSpark(hitpositm,worldptr);			//RJS 11Jun99
				break;
			case ANIM_GROUNDRICOCHET:
				if (	WithinVisibleRange(hitCoords,20000)			 //RJS 01Jul99
					||	(theShooter == Manual_Pilot.ControlledAC2)	)//RJS 01Jul99
					LaunchRicochetSmoke(hitpositm,RicochetSmokeShape,worldptr);//RJS 26Apr99
				break;
			case ANIM_WOODRICOCHET:
				if (	WithinVisibleRange(hitCoords,20000)			 //RJS 01Jul99
					||	(theShooter == Manual_Pilot.ControlledAC2)	)//RJS 01Jul99
					LaunchRicochetSmoke(hitpositm,WSMOKE,worldptr);		//RJS 26Apr99
				break;
			case ANIM_SMALLFIRE:
				LaunchGuidedBurning(hitpositm,worldptr);		//RJS 11Jun99
				_Miles.PlaySample(FIL_SFX_WOOD_BREAK1, (ItemBasePtr) hitpositm);
				break;
			case ANIM_BIGFIRE:
				if (WithinVisibleRange(hitCoords,400000))		//RJS 11Jun99
					LaunchGroundExplosion(hitpositm,worldptr);	//RJS 11Jun99
				break;
			case ANIM_ATEAM:
				LaunchDelayedExplosion((mobileitem*)itm,worldptr);
				break;
			case ANIM_BIGIMPACTNODIRT:
			case ANIM_SMALLIMPACTNODIRT:
			{
				if (WithinVisibleRange(hitCoords,400000))		//RJS 11Jun99
				{
					UWord	oldshape = hitpositm->shape;

					hitpositm->shape = (ShapeNum) hitshape;

					_Miles.PlaySample((FileNum) (FIL_SFX_EXPLOSION_TANK+Math_Lib.rnd(3)), hitpositm);
					if (damagestrength > 26)
						LaunchFlash(hitpositm,0,worldptr);
					else
						LaunchSmallFlash(hitpositm,worldptr);

					hitpositm->World.X = grpCoords.X;
					hitpositm->World.Z = grpCoords.Z;

					LaunchMushroomCloud(hitpositm,damagestrength,worldptr);

					hitpositm->shape = (ShapeNum) oldshape;
				}
			}
			break;
			case ANIM_SMALLIMPACTEXPLODE:	
			{
				if (WithinVisibleRange(hitCoords,400000))		//RJS 11Jun99
				{
					SLong	glevel = grpCoords.Y;						//RJS 07Dec98
					UWord	oldshape = hitpositm->shape;
					ShapeDescPtr	sdptr = SHAPESTUFF.GetShapePtr(shapehit);

					hitpositm->shape = (ShapeNum) hitshape;
					_Miles.PlaySample((FileNum) (FIL_SFX_EXPLOSION_TANK+Math_Lib.rnd(3)), hitpositm);
					if (damagestrength > 26)
						LaunchFlash(hitpositm,0,worldptr);
					else
						LaunchSmallFlash(hitpositm,worldptr);			//RJS 08Dec98

					hitpositm->World.X = grpCoords.X;
					hitpositm->World.Z = grpCoords.Z;
					LaunchDebris(hitpositm,DebrisDirtShape,2,(damagestrength * sdptr->Size)/100,worldptr);
					LaunchMushroomCloud(hitpositm,damagestrength,worldptr);
					LaunchExplosion(hitpositm,worldptr);				//MS 10Dec98
					hitpositm->shape = (ShapeNum) oldshape;
					grounddist = hitpositm->World.Y - glevel;
					if (grounddist < 300)		// 3 metres
					{
						hitpositm->World.Y = glevel;
						LaunchShockwave(hitpositm,worldptr);
					}
				}
			}
			break;
			case ANIM_DEFAULT:
			case ANIM_SMALLCOLLAPSE:
			{
				if (WithinVisibleRange(hitCoords,160000))		//RJS 11Jun99
				{
					hitpositm->World.Y = grpCoords.Y;
					LaunchDustRing(hitpositm,worldptr);
					LaunchGuidedFire(hitpositm,worldptr);
				}
			}
			break;
			case ANIM_BIGIMPACTEXPLODE:
			{
				if (WithinVisibleRange(hitCoords,320000))		//RJS 11Jun99
				{
					SLong	glevel = grpCoords.Y;						//RJS 07Dec98

					_Miles.PlaySample((FileNum) (FIL_SFX_EXPLOSION_TANK+Math_Lib.rnd(3)), hitpositm);
					LaunchFlash(hitpositm,0,worldptr);
					LaunchExplosion(hitpositm,worldptr);
					LaunchDebris(hitpositm,DebrisDirtShape,2,16,worldptr);

					UWord	oldshape = hitpositm->shape;
					hitpositm->shape = shapehit;
					LaunchMushroomCloud(hitpositm,damagestrength,worldptr);
					hitpositm->shape = (ShapeNum)oldshape;

					grounddist = hitpositm->World.Y - glevel;
					if (grounddist < 300)		// 3 metres
					{
						LaunchDirtyBuildingFingers(hitpositm,Math_Lib.rnd(),worldptr);// lets have some dirt//MS 30Nov98
		//DeadCode MS 10Dec98				LaunchDirtLarge(hitpositm,worldptr);

						hitpositm->World.Y = glevel;
						LaunchShockwave(hitpositm,worldptr);
					}
				}
			}
			break;
			case ANIM_BIGCOLLAPSE:
			{
				if (WithinVisibleRange(hitCoords,400000))		//RJS 11Jun99
				{
					hitpositm->World.Y = grpCoords.Y;
					_Miles.PlaySample(FIL_SFX_DEBRIS_COLLAPSE,hitpositm);
					LaunchDustRing(hitpositm,worldptr);	
					LaunchSmoulder(hitpositm,worldptr);
				}
			}
			break;											
			case ANIM_AMMOBOXES:										
				LaunchIgniteAmmoBoxes(hitpositm,groupindex,worldptr);//RJS 20Nov98
				break;											
			case ANIM_THROWBOXES:										
				LaunchAmmoBoxes(hitpositm,groupindex,hitterCoords,damagestrength,worldptr);		//RJS 26Apr99
				break;
			case ANIM_FUELBARRELS:									
				LaunchGroundExplosion(hitpositm,worldptr);		
				LaunchFuelBarrels(hitpositm,worldptr);			
				break;											
			case ANIM_CHICKENS:
				if (WithinVisibleRange(hitCoords,100000))		//RJS 11Jun99
				{
					_Miles.PlayOnce(FIL_SFX_HEN_SCUFFLE, (ItemBasePtr) hitpositm);
					LaunchBirds(hitpositm,ChickenShape,worldptr);
				}
				break;
			case ANIM_TANKDEATH:
				if (WithinVisibleRange(hitCoords,400000))		//RJS 11Jun99
				{
					if (hitpositm->shape == BOMB)
					{
						_Miles.PlaySample((FileNum) (FIL_SFX_EXPLOSION_DISTANT1+Math_Lib.rnd(2)), (ItemBasePtr) hitpositm);
						LaunchSmoulder(hitpositm,worldptr);
						_Miles.StopSample(FIL_SFX_TANK_LOOP1,itm);
					}
				}
				break;											
			case ANIM_BRIDGEDEATH:									
				hitpositm->World = oldcoords;
				LaunchBridgeElement(itm,grpCoords,groupindex,worldptr);//RJS 26Feb99
				break;
			case ANIM_TRAINDEATH:									
				_Miles.PlaySample((FileNum) (FIL_SFX_EXPLOSION_DISTANT1+Math_Lib.rnd(2)), (ItemBasePtr) hitpositm);
				LaunchSmoulder(hitpositm,worldptr,TRUE);			
				break;
			case ANIM_FUELDAMAGE:
			{
				WeapAnimData*	weapon = (WeapAnimData*) weapptr;
				if ((weapon->LauncherType==LT_FUEL) || (weapon->LauncherType==LT_INTFUEL))
					weapon->pitch = -1;

	//DeadCode RJS 25Mar99			SHAPE.InitTrailFields(weapptr,0,32000,LT_FUEL);		//RJS 02Apr98
				SHAPE.LogFuelDamage(itm,weapptr,itm);				//RJS 21Jan99
				LaunchVapourStream(weapptr,shapehit);				//RJS 17Sep97
				shititem = itm;
			}
			break;
			case ANIM_WEAPONDAMAGE:									
				break;
			case ANIM_TURBULANCE:
				if (!_Replay.Playback)
				{
					if (itm->Status.size == AirStrucSize)									//RJS 18Jan99
					{																		//RJS 18Jan99
						AirStrucPtr	ac = (AirStrucPtr) itm;									//RJS 18Jan99
						ac->fly.pModel->SetLocalGust(oldcoords,hitCoords,damagestrength*10);//RJS 29Jun99
					}																		//RJS 18Jan99
					else
					{
						// Ateam effect code... but just move the object, don't throw??

					}
				}
				break;
			case ANIM_DROPGEAR:										//RJS 07Sep98
				SHAPE.KillGear(itm);								//RJS 07Sep98
				break;												//RJS 07Sep98
			case ANIM_TOTALDESTRUCTION:
			{
				hitpositm->World = oldcoords;
				KillLauncher(hitpositm,theShooter,worldptr,groupindex,&hitCoords);//JIM 11Mar99
				break;
			}
			case ANIM_NAPALM:
				if (WithinVisibleRange(hitCoords,400000))		//RJS 11Jun99
				{
					// Singe and scatter fires...
					LaunchScatteredFire(hitpositm,shapehit,worldptr);
				}
				break;
			case ANIM_BLOKESEXPLODE:
			{
				if (WithinVisibleRange(hitCoords,100000))		//RJS 11Jun99
				{
//DeadCode RJS 01Jul99 					if (Math_Lib.rnd()>40000)
//DeadCode RJS 01Jul99 					{
//DeadCode RJS 01Jul99 						ShapeDescPtr		sdptr = SHAPESTUFF.GetShapePtr(shapehit);
//DeadCode RJS 01Jul99 						ULong				size = sdptr->Size << 4;
//DeadCode RJS 01Jul99 						UWord				maxtroops = size / 163;
//DeadCode RJS 01Jul99 
//DeadCode RJS 01Jul99 						if (maxtroops > randval)	//RJS 10Dec98
						UWord	maxtroops = randval;			//RJS 01Jul99

						_Miles.PlayOnce((FileNum) (FIL_SFX_YELP1 + Math_Lib.rnd(5)),hitpositm);
						LaunchDebris(hitpositm,BlokeFlyingShape,0,maxtroops,worldptr,TRUE);
//DeadCode RJS 01Jul99 					}
				}
				break;
			}
			case ANIM_BLOKESNAPALM:
			{
				if (WithinVisibleRange(hitCoords,200000))		//RJS 11Jun99
				{
//DeadCode RJS 01Jul99 					ShapeDescPtr		sdptr = SHAPESTUFF.GetShapePtr(shapehit);
//DeadCode RJS 01Jul99 					ULong				size = sdptr->Size << 4;
//DeadCode RJS 01Jul99 					UWord				maxtroops = size / 128;
//DeadCode RJS 01Jul99 
//DeadCode RJS 01Jul99 					if (maxtroops > randval)	//RJS 10Dec98
					UWord	maxtroops = randval;				//RJS 01Jul99

					hitpositm->World = oldcoords;
					_Miles.PlayOnce((FileNum) (FIL_SFX_YELP1 + Math_Lib.rnd(5)),hitpositm);
					LaunchTroops(hitpositm,BlokeFireShape,hitCoords,worldptr,maxtroops);
				}
			}
			break;
			case ANIM_BLOKES:
			{
				if (WithinVisibleRange(hitCoords,200000))		//RJS 11Jun99
				{
//DeadCode RJS 01Jul99 					ShapeDescPtr		sdptr = SHAPESTUFF.GetShapePtr(shapehit);
//DeadCode RJS 01Jul99 					ULong				size = sdptr->Size << 4;
//DeadCode RJS 01Jul99 					UWord				maxtroops = size / 128;
//DeadCode RJS 01Jul99 
//DeadCode RJS 01Jul99 					if (maxtroops > randval)	//RJS 10Dec98
					UWord	maxtroops = randval;				//RJS 01Jul99

					hitpositm->World = oldcoords;
					LaunchTroops(hitpositm,BlokeRunShape,hitCoords,worldptr,maxtroops);
				}
			}
			break;
			case ANIM_TOSS:
			{
				if (groupindex == -1)								//RJS 06Dec98
					hitpositm->World = grpCoords;					//RJS 06Dec98

				LaunchTossedShape(hitpositm,groupindex,hitterCoords,damagestrength,worldptr);//RJS 06Dec98
				break;
			}
			case ANIM_DEBRISDIRT:
			{
				if (WithinVisibleRange(hitCoords,100000))		//RJS 11Jun99
				{
					ShapeDescPtr		sdptr = SHAPESTUFF.GetShapePtr(shapehit);
					ULong				size = 4 + ((sdptr->Size << 4) * damagestrength)/6324;//MS 10Dec98

					LaunchDebris(hitpositm,DebrisDirtShape,2,size,worldptr);
				}
			}
			break;
			case ANIM_DEBRISMECH:
			{
				if (WithinVisibleRange(hitCoords,100000))		//RJS 11Jun99
				{
					ShapeDescPtr		sdptr = SHAPESTUFF.GetShapePtr(shapehit);
					ULong				size = 4 + ((sdptr->Size << 4)*damagestrength)/6324;//MS 10Dec98

					LaunchDebris(hitpositm,DebrisMechShape,0,size,worldptr);
				}
			}
			break;
			case ANIM_DEBRISWOOD:
			{
				if (WithinVisibleRange(hitCoords,100000))		//RJS 11Jun99
				{
					ShapeDescPtr		sdptr = SHAPESTUFF.GetShapePtr(shapehit);
					ULong				size = 4 + ((sdptr->Size << 4)*damagestrength)/6324;//MS 10Dec98
			
					LaunchDebris(hitpositm,DebrisWoodShape,2,size,worldptr);
				}
			}
			break;
			case ANIM_DEBRISBRICK:
			{
				if (WithinVisibleRange(hitCoords,100000))		//RJS 11Jun99
				{
					ShapeDescPtr		sdptr = SHAPESTUFF.GetShapePtr(shapehit);
					ULong				size = 4 + ((sdptr->Size << 4)*damagestrength)/6324;//MS 10Dec98

					LaunchDebris(hitpositm,DebrisBrickShape,2,size,worldptr);
					LaunchDirtyBuildingFingers(hitpositm,Math_Lib.rnd(),worldptr);// lets have some dirt
				}
			}
			break;
			case ANIM_TIMEBOMB:
			{
				AircraftAnimData*	adptr = (AircraftAnimData*) hitpositm->Anim;

				ULong	animoffset = ULong(&adptr->ENGINELEFTIN) - ULong(adptr);

				LaunchTimeBomb(hitpositm,animoffset,worldptr);
			}
			break;
			case ANIM_DUSTCLOUD:
				if (WithinVisibleRange(hitCoords,100000))		//RJS 11Jun99
				{
					ShapeNum	oldshape = hitpositm->shape;			//RJS 18Jun99
					hitpositm->shape = shapehit;

					LaunchMushroomCloud(hitpositm,damagestrength,worldptr);

					hitpositm->shape = oldshape;
				}
				break;
			case ANIM_TUMBLE:									
			{
				hitpositm->World = oldcoords;
				LaunchCollapse(itm,grpCoords,groupindex,worldptr);
			}
			break;
			case ANIM_SMALLFLASH:
				if (WithinVisibleRange(hitCoords,400000))		//RJS 11Jun99
					LaunchSnapFlash(hitpositm,worldptr);		//RJS 28Jun99
				break;
			case ANIM_SINK:
				hitpositm->World = oldcoords;
				LaunchBoatSink(itm,grpCoords,groupindex,worldptr);
				break;
			case ANIM_FUELEXPLOSION:
				if (WithinVisibleRange(hitCoords,200000))		//RJS 11Jun99
				{
					hitpositm->World = grpCoords;
					LaunchFingers(hitpositm,worldptr);
					LaunchTransientTrail(hitpositm,FireballShape,500,FALSE,worldptr,400);
				}
				break;
		}

		hitpositm->World = oldcoords;
//DeadCode RJS 11Jun99 	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchSmokeCloud
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
void TransObj::LaunchSmokeCloud(mobileitem *launcher,ShapeNum	theShape,COORDS3D	pos,WorldStuff &worldptr)
{
	TransientItem*	newitem;

	newitem = SimplifiedSpriteLaunch(launcher,theShape,6000,MOBILE_STATIONARY);
	if (newitem)
	{
		newitem->World = pos;
		newitem->TransRandom = 0;

		AddTransientItemToWorld(newitem,worldptr);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchDirtSmall
//Author		Robert Slater
//Date			Fri 21 Aug 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::LaunchDirtSmall(mobileitem* launcher,WorldStuff& worldptr, bool dosound)
{
	TransientItem*	newitem = SimplifiedSpriteLaunch(launcher,BULGND,170,MOBILE_STATIONARY);
	if (newitem)
	{
		if (dosound)
			_Miles.PlaySample((FileNum)(FIL_SFX_RICOCHET_SOFT_SURFACE1+Math_Lib.rnd(2)),newitem);
		AddTransientItemToWorld(newitem, worldptr);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchDirtMedium
//Author		Robert Slater
//Date			Fri 21 Aug 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::LaunchDirtMedium(mobileitem* launcher,WorldStuff& worldptr)
{
	if (WithinVisibleRange(launcher->World,400000))				//RJS 30Apr99
	{
		if (Save_Data.desiredfps <= realFrameTime)				//RJS 11Jun99
		{
			TransientItem*	newitem;									//MS 10Dec98
																		//MS 10Dec98
			newitem = SimplifiedSpriteLaunch(launcher,DRTYX,400,MOBILE_STATIONARY);//MS 10Dec98
			if (newitem)												//MS 10Dec98
				AddTransientItemToWorld(newitem, worldptr);				//MS 10Dec98
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchDirtLarge
//Author		Robert Slater
//Date			Fri 21 Aug 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::LaunchDirtLarge(mobileitem* launcher,WorldStuff& worldptr)
{
	if (WithinVisibleRange(launcher->World,400000))				//RJS 30Apr99
	{
		TransientItemPtr	newitem;								//MS 10Dec98
		ANGLES				hdg,pitch,roll;							//MS 10Dec98
																	//MS 10Dec98
		Three_Dee.pMigLand->GetShadowAngles(launcher->World,hdg,pitch,roll);//MS 10Dec98
																	//MS 10Dec98
		newitem = SimplifiedSpriteLaunch(launcher,DRTYX,400,MOBILE_STATIONARY);//MS 10Dec98
		if (newitem)												//MS 10Dec98
			AddTransientItemToWorld(newitem, worldptr);				//MS 10Dec98
																	//MS 10Dec98
		newitem = SimplifiedSpriteLaunch(launcher,MUSHY,400,MOBILE_STATIONARY);//MS 10Dec98
		if (newitem)												//MS 10Dec98
		{															//MS 10Dec98
			newitem->hdg = hdg;										//MS 10Dec98
			newitem->pitch = pitch;									//MS 10Dec98
			newitem->roll = roll;									//MS 10Dec98
																	//MS 10Dec98
			AddTransientItemToWorld(newitem, worldptr);				//MS 10Dec98
		}															//MS 10Dec98
																	//MS 10Dec98
		newitem = SimplifiedSpriteLaunch(	launcher,				//MS 10Dec98
											ExplosionShockShape,	//MS 10Dec98
											100,MOBILE_STATIONARY);	//MS 10Dec98
		if (newitem)												//MS 10Dec98
		{															//MS 10Dec98
	//DeadCode RJS 21Apr99		SLong	glevel = GetGroundLevel(launcher) + METRES01;	//RJS 14Apr99
	//DeadCode RJS 21Apr99																//MS 10Dec98
	//DeadCode RJS 21Apr99		newitem->World.Y = glevel;								//MS 10Dec98
			newitem->World.Y += METRES01;							//RJS 21Apr99
			newitem->hdg = hdg;										//MS 10Dec98
			newitem->pitch = pitch;									//MS 10Dec98
			newitem->roll = roll;									//MS 10Dec98
																	//MS 10Dec98
			AddTransientItemToWorld(newitem, worldptr);				//MS 10Dec98
		}															//MS 10Dec98
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchSplashSmall
//Author		Robert Slater
//Date			Fri 21 Aug 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::LaunchSplashSmall(mobileitem* launcher,WorldStuff& worldptr)
{
	TransientItem*	newitem = SimplifiedSpriteLaunch(launcher,BULWAT,200,MOBILE_STATIONARY);
	if (newitem)
	{
		_Miles.PlaySample(FIL_SFX_RICOCHET_WATER,newitem);
		AddTransientItemToWorld(newitem, worldptr);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchSplashMedium
//Author		Robert Slater
//Date			Fri 21 Aug 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::LaunchSplashMedium(mobileitem* launcher,WorldStuff& worldptr)
{
	if (WithinVisibleRange(launcher->World,300000))				//RJS 30Apr99
	{
		TransientItem*	newitem = SimplifiedSpriteLaunch(launcher,SPLASH,700,MOBILE_STATIONARY);
		if (newitem)
			AddTransientItemToWorld(newitem, worldptr);

		_Miles.PlayOnce(FIL_SFX_COLLISION_WATER,launcher);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchSplashLarge
//Author		Robert Slater
//Date			Fri 21 Aug 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::LaunchSplashLarge(mobileitem* launcher,WorldStuff& worldptr)
{
	if (WithinVisibleRange(launcher->World,300000))				//RJS 30Apr99
	{
		TransientItem*	newitem;

		newitem = SimplifiedSpriteLaunch(launcher,GNDEXP,400,MOBILE_STATIONARY);
		if (newitem)
			AddTransientItemToWorld(newitem, worldptr);

		_Miles.PlayOnce(FIL_SFX_COLLISION_WATER,launcher);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchDustRingBig
//Author		Robert Slater
//Date			Fri 21 Aug 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::LaunchDustRingBig(mobileitem* launcher,WorldStuff& worldptr)
{
	if (WithinVisibleRange(launcher->World,200000))				//RJS 30Apr99
	{
		TransientItem*	newitem;

		newitem = SimplifiedSpriteLaunch(	launcher,
											GRNDD6,
											400,MOBILE_STATIONARY);	//RJS 27Apr98

		if (newitem)
		{
			_Miles.PlaySample(FIL_SFX_DEBRIS_SHOWER,newitem);
			AddTransientItemToWorld(newitem, worldptr);
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DoImpactGround
//Author		Robert Slater
//Date			Fri 21 Aug 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::DoImpactGround(ItemPtr	launcher, Coords3D	impactpos,UByte	areatype)
{
	WorldStuff	*world = mobileitem::currworld;
	UWord		HitStrength = SHAPESTUFF.GetShapeDamageStrength(launcher->shape);//RJS 22Jan98
	UWord		HitDamageType = SHAPESTUFF.GetShapeDamageType(launcher->shape);//RJS 22Jan98
	AreaType	theArea = (AreaType)areatype;								//RJS 27Nov98
	Coords3D	oldpos = launcher->World;

	launcher->World = impactpos;

	SLandLight lightDef;
	lightDef.pos=impactpos;
	lightDef.color.r=0xFF00;
	lightDef.color.g=0xFF00;
	lightDef.color.b=0xFF00;
	lightDef.timer=50;	//half a second
	lightDef.range=25000;	//quarter km

	switch (HitDamageType)
	{
	case DMT_BULLET:
	{
		if (WithinVisibleRange(impactpos,160000))				//RJS 30Apr99
		{
			switch (theArea)
			{
			case AT_sea:
			case AT_river:
			case AT_washShore:
//DeadCode RJS 06Jul99 				_Miles.PlayOnce(FIL_SFX_RICOCHET_WATER,launcher);
				LaunchSplashSmall((mobileitem*)launcher,*world);
				break;
			case AT_hardRock:									//RJS 06Jul99
			case AT_highRock:
			case AT_lowRock:
			case AT_snowyRock:
			case AT_city:
				LaunchDirtSpark((mobileitem*)launcher,*world);	//RJS 06Jul99
				break;
			default:
				LaunchDirtSmall((mobileitem*)launcher,*world);
				break;
			}
		}
	}
	break;
	case DMT_FIRE:
	{
		//Impact toggle...
		if (	View_Object
			&&	(launcher->Status.size == TRANSIENTSIZE)
			&&	(((TransientItemPtr)launcher)->Launcher == Manual_Pilot.ControlledAC2))
			View_Object->PossDirectorAction(launcher->World);	//DAW 22Jun99

		Land_Scape.AddLight(&lightDef);

		switch (theArea)
		{
		case AT_sea:
		case AT_river:
		case AT_washShore:
			_Miles.PlayOnce(FIL_SFX_DEBRIS_WATER2,launcher);
			LaunchSplashMedium((mobileitem*)launcher,*world);
			break;
		default:
			LaunchNapalmStrike((mobileitem* )launcher,*world);
			break;
		}
	}
	break;
	case DMT_EXPLOSION:
	{
		//Impact toggle...
		if (	View_Object
			&&	(launcher->Status.size == TRANSIENTSIZE)
			&&	(((TransientItemPtr)launcher)->Launcher == Manual_Pilot.ControlledAC2))
			View_Object->PossDirectorAction(launcher->World);	//DAW 22Jun99

		Land_Scape.AddLight(&lightDef);

		LaunchShockwave((mobileitem*)launcher,*world);
		LaunchRealShockwave((mobileitem*)launcher,HitStrength,*world);//RJS 02Dec98

		switch (theArea)
		{
		case AT_sea:
		case AT_river:
		case AT_washShore:
		{
			if (HitStrength > 24)
			{
				_Miles.PlayOnce(FIL_SFX_COLLISION_WATER,launcher);
				LaunchSplashLarge((mobileitem*)launcher,*world);
			}
			else
			{
				_Miles.PlayOnce(FIL_SFX_DEBRIS_WATER2,launcher);
				LaunchSplashMedium((mobileitem*)launcher,*world);
			}
		}
		break;
//		case AT_washShore:
//		{
//			if (HitStrength > 24)
//			{
//				_Miles.PlayOnce(FIL_SFX_COLLISION_WATER,launcher);
//				LaunchSplashLarge((mobileitem*)launcher,*world);
//			}
//			else
//			{
//				_Miles.PlayOnce(FIL_SFX_DEBRIS_WATER2,launcher);
//				LaunchSplashMedium((mobileitem*)launcher,*world);
//			}
//		}
//		break;
		default:
		{
			Land_Scape.AddLight(&lightDef);

			LaunchFlash((mobileitem*)launcher,HitStrength,*world);		//RJS 20Jan99

			_Miles.PlaySample((FileNum) (FIL_SFX_EXPLOSION_TANK+Math_Lib.rnd(3)), launcher);//RJS 10Nov98

//DeadCode AM 01Dec98			if (HitStrength > 24)
//DeadCode AM 01Dec98			{
//DeadCode AM 01Dec98				LaunchDirtyFingers((mobileitem*)launcher,*world);
//DeadCode AM 01Dec98				LaunchDirtLarge((mobileitem*)launcher,*world);
//DeadCode AM 01Dec98			}
//DeadCode AM 01Dec98			else
//DeadCode AM 01Dec98			{
//DeadCode AM 01Dec98				if (HitStrength > 16)
//DeadCode AM 01Dec98					LaunchDirtyFingers((mobileitem*)launcher,*world);
//DeadCode AM 01Dec98				else
			LaunchDirtMedium((mobileitem*)launcher,*world);
//Dead			if (((TransientItem*)launcher)->Launcher == Manual_Pilot.ControlledAC2)
				LaunchCrater((mobileitem*)launcher,*world);
//DeadCode AM 01Dec98			}
		}
		break;
		}
	}
	break;
	default:
	{
		switch (theArea)
		{
		case AT_sea:
		case AT_river:
		case AT_washShore:
			LaunchSplashMedium((mobileitem*)launcher,*world);
			break;
		default:
		{
			ShapeDescPtr	sdptr = SHAPESTUFF.GetShapePtr(launcher->shape);
			SLong			impactsize = sdptr->Size << 4;

			if (launcher->Status.size == TRANSIENTSIZE)
			{
				TransientItem*	mobptr = (TransientItem*) launcher;
				SLong		vel = mobptr->vely;

				if (vel < 0) vel = -vel;

				impactsize *= vel;
				impactsize /= 10;
			}

			if (impactsize < 100)
				LaunchDustRing((mobileitem*)launcher,*world);
			else
			{
				Land_Scape.AddLight(&lightDef);

//				if (impactsize < 1000)
					LaunchDustRingBig((mobileitem*)launcher,*world);
//				else
//					LaunchDirtMedium((mobileitem*)launcher,*world);
			}
		}
		break;
		}
	}
	break;
	}

	launcher->World = oldpos;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LandedEffect
//Author		Robert Slater
//Date			Mon 24 Aug 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::LandedEffect(AirStrucPtr	ac, SLong	landed,Bool send,Bool musthit)
{
//DeadRJS08Jan99	if (!Save_Data.gamedifficulty[GD_GROUNDCOLLISIONS])	return;
	UByte		theArea;
	WorldStuff	*world = mobileitem::currworld;
	SLong		gheight = GetGroundLevel(ac,theArea);					//RJS 14Apr99
//Dead	AreaType	theArea = (AreaType)Three_Dee.GetLandType();
	ULong		oldmovecode;
	Bool		onWater = FALSE;
	Bool		onSparky = FALSE;								//RJS 11Dec98
	Bool		doEffect = TRUE;
	Bool		doSpecial = (Bool) !ac->IsHealthyMovecode(oldmovecode);
	Bool		haddamage,isPlayer;								//RJS 11Jun99
																//RJS 11Jun99
	if (ac->lasthitter.count)									//RJS 11Jun99
		haddamage = TRUE;										//RJS 11Jun99
	else														//RJS 11Jun99
		haddamage = FALSE;										//RJS 11Jun99

	HitTheDeck = true;											//RDH 09May99

	if (ac==Manual_Pilot.ControlledAC2)
	{
		isPlayer = TRUE;										//RJS 11Jun99
		if (Manual_Pilot.controlmode==ManualPilot::PILOTDEAD)	//RJS 20Apr99
			doSpecial = TRUE;

		if (!Save_Data.gamedifficulty[GD_GROUNDCOLLISIONS])			//RJS 08Jan99
		{
			ac->World.Y = gheight;
			doEffect = FALSE;
			if (!doSpecial)
			{
				AircraftAnimData*	adptr = (AircraftAnimData*) ac->Anim;

				if (	(!adptr->acleglowerl && !adptr->LEFTWHEEL)//DAW 19May99
					&&	(!adptr->acleglowerr && !adptr->RIGHTWHEEL)	)//DAW 19May99
					ac->World.Y -= ac->fly.pModel->GearList->pos0.y;
				else
					ac->World.Y += 200;							//DAW 01Jul99

				ac->fly.pModel->Pos.y = ac->World.Y;
			}
		}
	}
	else
		isPlayer = FALSE;										//RJS 11Jun99

	// Block normal ground collisions, but keep special ones (ie. if you are already dead)
	if (!doSpecial && !doEffect)								//RJS 08Jan99
		return;

	if (_DPlay.Implemented || _Replay.Record)					//RJS 29Oct98
	{
		UByte b1,b2;

		b1=(((UWord)landed)>>8)&255;
		b2=((UWord)landed)&255;

		if (send
			&& ac==Persons2::PlayerSeenAC) // AMM01Oct98 etc
			_DPlay.NewSpecial(PIDC_LANDEDEFFECT,b1,b2,theArea);
	}

	switch (theArea)
	{
		case AT_sea:
		case AT_river:
		case AT_washShore:
			onWater = TRUE;
			break;
		case AT_softRock:										//RJS 11Dec98
		case AT_hardRock:										//RJS 11Dec98
		case AT_sandyRock:										//RJS 11Dec98
		case AT_highRock:										//RJS 11Dec98
		case AT_lowRock:										//RJS 11Dec98
		case AT_snowyRock:										//RJS 11Dec98
		case AT_city:										//RJS 11Dec98
			onSparky = TRUE;									//RJS 11Dec98
			break;												//RJS 11Dec98
	}

	if (!doSpecial)												//RJS 08Jan99
	{
		AircraftAnimData	*adptr = (AircraftAnimData*) ac->Anim;
		if (onWater == TRUE)
		{
			adptr->hasdust = TRUE;
			Manual_Pilot.DeathSequenceOverride(ac,AUTO_HITWATER);

			_Miles.PlayOnce(FIL_SFX_COLLISION_WATER,ac);

			switch (landed)
			{
			case _Collide.PROP_TOUCH:
			case _Collide.NOSE_TOUCH:
			{
//DeadCode MS 10Dec98				TransientItem*	newitem;
//DeadCode MS 10Dec98				newitem = SimplifiedSpriteLaunch(ac,DUMY13,400,MOBILE_GANDF);
//DeadCode MS 10Dec98				if (newitem)												
//DeadCode MS 10Dec98				{									
//DeadCode MS 10Dec98					newitem->vely = 150;						
//DeadCode MS 10Dec98					newitem->TransRandom = 1;				
//DeadCode MS 10Dec98					AddTransientItemToWorld(newitem,*world);	
//DeadCode MS 10Dec98				}						
				
				KillLauncher(ac,ac,*world);
				if (View_Object && (ac==Manual_Pilot.ControlledAC2))
					View_Object->SetToDeathView(DEATH_SKID);

				ac->vel = 0;
			}
			break;
			case _Collide.RIGHT_WING_TOUCH:
				SHAPE.ForceDamage(ac,ac,&adptr->RIGHTWINGIN,BS_DEAD);//JIM 11Mar99
				LaunchWaterTrail(ac,*world);
				if (View_Object && (ac==Manual_Pilot.ControlledAC2))
					View_Object->SetToDeathView(DEATH_SKID);
			break;
			case _Collide.LEFT_WING_TOUCH:
				SHAPE.ForceDamage(ac,ac,&adptr->LEFTWINGIN,BS_DEAD);//JIM 11Mar99
				LaunchWaterTrail(ac,*world);
				if (View_Object && (ac==Manual_Pilot.ControlledAC2))
					View_Object->SetToDeathView(DEATH_SKID);
			break;
			default:
			{
				LaunchWaterTrail(ac,*world);
				if (View_Object && (ac==Manual_Pilot.ControlledAC2))
				{
					if (haddamage)
						Persons2::UpdatePlayerLog	(ac,EventLog::CRASHLANDTOOFAST);
					else
						Persons2::UpdatePlayerLog	(ac,EventLog::BENTWING);

					View_Object->SetToDeathView(DEATH_SKID);
				}
				break;
			}
			}

			LaunchSplashMedium(ac,*world);
		}
		else
		{
			// Are any wheels damaged?
//DeadCode DAW 28Jun99 			if (adptr->LEFTWHEEL ||	adptr->RIGHTWHEEL || adptr->FRONTWHEEL || adptr->BACKWHEEL)
//DeadCode DAW 28Jun99 				landed = _Collide.LANDED_BELLY;

			if (landed == _Collide.LANDED_OK)
			{
//DeadCode RJS 11Jun99 				// Perhaps throw up a bit of dirt...
//DeadCode RJS 11Jun99 
//DeadCode RJS 11Jun99 				adptr->hasdust = FALSE;
//DeadCode RJS 11Jun99 				if (!adptr->justlanded)
//DeadCode RJS 11Jun99 				{
//DeadCode RJS 11Jun99 					adptr->justlanded = TRUE;
//DeadCode RJS 11Jun99 					_Miles.PlayOnce(FIL_SFX_TYRE_SCREECH1,ac);
//DeadCode RJS 11Jun99 				}
			}
			else
			{
//DeadRJS06Dec98				LaunchDirtMedium(ac,*world);
				LaunchMushroomCloud(ac,10,*world);

				switch (landed)
				{
				case _Collide.PROP_TOUCH:
				case _Collide.NOSE_TOUCH:
				case _Collide.RIGHT_WING_TOUCH:
				case _Collide.LEFT_WING_TOUCH:
				{
					ac->World.Y = gheight;					//RJS 27Nov98
					ac->pitch = ANGLES_0Deg;
					ac->roll = ANGLES_0Deg;

					SHAPE.DetatchAllVapourStreams(ac);			//RJS 04Dec98

//DeadCode MS 10Dec98					TransientItem*	newitem;
//DeadCode MS 10Dec98					newitem = SimplifiedSpriteLaunch(ac,DUMY13,400,MOBILE_GANDF);
//DeadCode MS 10Dec98					if (newitem)												
//DeadCode MS 10Dec98					{									
//DeadCode MS 10Dec98						newitem->vely = 150;						
//DeadCode MS 10Dec98						newitem->TransRandom = 1;				
//DeadCode MS 10Dec98						AddTransientItemToWorld(newitem,*world);	
//DeadCode MS 10Dec98					}						

					Manual_Pilot.DeathSequenceOverride(ac,AUTO_NOPPILOT);

					ExplodeAC(ac,ac,*world);					//JIM 11Mar99
//DeadCode RJS 30Mar99					ac->shape = PDEATH;

					if (View_Object && (ac==Manual_Pilot.ControlledAC2))
						View_Object->SetToDeathView(DEATH_NORMAL);

					SHAPE.ResetAnimData_NewShape(ac,PDEATH,0,true);//RJS 21Apr99
					MinAnimData*	mad = (MinAnimData*)ac->Anim;//RJS 18May99
					mad->itemstate = DEAD;						//RJS 28Apr99

					LaunchFire(ac,*world);						//RJS 28Jun99
				}
				break;
//DeadCode RJS 04Dec98				case _Collide.RIGHT_WING_TOUCH:
//DeadCode RJS 04Dec98					Manual_Pilot.DeathSequenceOverride(ac,AUTO_CRASHROLL);
//DeadCode RJS 04Dec98					adptr->hasdust = TRUE;
//DeadCode RJS 04Dec98					LaunchDustTrail2(ac,*world); // Maybe sparks, if on hard ground...
//DeadCode RJS 04Dec98					SHAPE.ForceDamage(ac,&adptr->RIGHTWINGIN,BS_DEAD);
//DeadCode RJS 04Dec98					if (View_Object && (ac==Manual_Pilot.ControlledAC2))
//DeadCode RJS 04Dec98						View_Object->SetToDeathView(DEATH_SKID);
//DeadCode RJS 04Dec98				break;
//DeadCode RJS 04Dec98				case _Collide.LEFT_WING_TOUCH:
//DeadCode RJS 04Dec98					Manual_Pilot.DeathSequenceOverride(ac,AUTO_CRASHROLL);
//DeadCode RJS 04Dec98					adptr->hasdust = TRUE;
//DeadCode RJS 04Dec98					LaunchDustTrail2(ac,*world); // Maybe sparks, if on hard ground...
//DeadCode RJS 04Dec98					SHAPE.ForceDamage(ac,&adptr->LEFTWINGIN,BS_DEAD);
//DeadCode RJS 04Dec98					if (View_Object && (ac==Manual_Pilot.ControlledAC2))
//DeadCode RJS 04Dec98						View_Object->SetToDeathView(DEATH_SKID);
//DeadCode RJS 04Dec98				break;
				default:
				{
					if (ac->vel < MPH100)						//RJS 11Dec98
					{
						_Miles.PlayOnce(FIL_SFX_COLLISION_GROUND4,ac);
						if (onSparky)
							LaunchTransientTrail(ac,SparkShape,4,TRUE,*world,65536,TRUE);
						else
						{
							adptr->hasdust = TRUE;
							LaunchDustTrail2(ac,*world);
						}

						if (View_Object && (ac==Manual_Pilot.ControlledAC2))
						{
							if (haddamage)
								Persons2::UpdatePlayerLog	(ac,EventLog::CRASHLANDTOOFAST);
							else
								Persons2::UpdatePlayerLog	(ac,EventLog::BENTWING);

							View_Object->SetToDeathView(DEATH_SKID);
						}
					}
					else
					{
						if (isPlayer)
							Persons2::UpdatePlayerLog	(ac,EventLog::FATALCRASH);

						_Miles.PlayOnce(FIL_SFX_COLLISION_GROUND3,ac);
						LaunchFakeDelayedExplosion(ac,*world);

						SHAPE.DetatchAllVapourStreams(ac);
						if (!onSparky)
						{
							adptr->hasdust = TRUE;
							LaunchDustTrail2(ac,*world);
						}

						LaunchTransientTrail(ac,SmallFireballShape,300,FALSE,*world,65536);
						LaunchCrater(ac,*world);								//RJS 13May99
					}

					Manual_Pilot.DeathSequenceOverride(ac,AUTO_CRASHSKID);
					if (View_Object && (ac==Manual_Pilot.ControlledAC2))
						View_Object->SetToDeathView(DEATH_SKID);
				}
				break;
				}
			}
		}
	}
	else
	{
		if (oldmovecode != AUTO_NOPPILOT)	//Strange if it is!
		{
			ac->pitch = ANGLES_0Deg;							//DAW 03Sep98
			ac->roll = ANGLES_0Deg;								//DAW 03Sep98

			if (onWater)
			{
				AircraftAnimData	*adptr = (AircraftAnimData*) ac->Anim;
				adptr->ENGINELEFTIN = BS_DEAD;			//Make fire invisible

				LaunchSplashMedium(ac,*world);
			}
			else
			{
				//This is if the guy hits the deck but was already fatally wounded...
				MinAnimData*	mad = (MinAnimData*)ac->Anim;
				if (!mad->IsInvisible)
				{
					ExplodeAC(ac,ac,*world);					//RJS 18May99
					LaunchFire(ac,*world);
				}
				else
					LaunchDustRingBig(ac,*world);

				Manual_Pilot.DeathSequenceOverride(ac,AUTO_NOPPILOT);
				if (View_Object && (ac==Manual_Pilot.ControlledAC2))//RDH 02Sep98
					View_Object->SetToDeathView();				//RDH 02Sep98

				SHAPE.ResetAnimData_NewShape(ac,PDEATH,0,true);//RJS 21Apr99
				mad->itemstate = DEAD;							//RJS 18May99
			}

			//Is this really an aircraft??
			if (oldmovecode != 0xFFFFFFFF)
			{
				ac->vel = 0;
				if (onWater)		//Fiddle movecode dirty, and sink
					ac->movecode = AUTO_HITWATER;
				else
					ac->movecode = AUTO_NOPPILOT;
			}
		}
	}

	HitTheDeck = false;											//RDH 09May99
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchBubbles
//Author		Robert Slater
//Date			Tue 25 Aug 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::LaunchBubbles(mobileitem* launcher,SLong	dist,WorldStuff& worldptr)
{
	if (WithinVisibleRange(launcher->World,200000))				//RJS 30Apr99
	{
		if (Math_Lib.rnd() > 32000)
		{
			TransientItem*	newitem;
			SLong			rdist;
			ANGLES			theAngle = (Angles)Math_Lib.rnd();
			SLong			xdist, zdist;
			SWord			sin_ang, cos_ang;

			dist = (Math_Lib.rnd() * dist)>>16;

			Math_Lib.high_sin_cos(theAngle,sin_ang,cos_ang);

			xdist = (dist * cos_ang)>>ANGLES_SHIFT;
			zdist = (dist * sin_ang)>>ANGLES_SHIFT;

			newitem = SimplifiedSpriteLaunch(	launcher,
												SDUST,
												100,MOBILE_STATIONARY);	//RJS 27Apr98

			if (newitem)
			{
				newitem->World.X += xdist;
				newitem->World.Z += zdist;
				newitem->World.Y = 0;				//Sea level...

				AddTransientItemToWorld(newitem, worldptr);
			}

			_Miles.PlayOnce(FIL_SFX_BUBBLES,launcher);
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchWaterTrail
//Author		Robert Slater
//Date			Tue 25 Aug 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::LaunchWaterTrail(	mobileitem* launcher,
									WorldStuff& worldptr	)
{
	TransientItem*	newitem = LaunchGuidedMissile(	launcher,
													(itemptr )launcher,
													WATSHP,
													LIFETIME_SMOKETRAIL,
													MOBILE_SMOKETRAIL);
	if (newitem)
	{
		MoveGunAnimData*	adptr = (MoveGunAnimData*)newitem->Anim;
		WeapAnimData*		weapon = (WeapAnimData*) &adptr->weaponlaunchers[0];

		SHAPE.InitTrailFields((UByteP)weapon,0,32000,LT_DUST);	

		LaunchVapourStream((UByteP)weapon,WATSHP);	

		AddTransientItemToWorld(newitem, worldptr);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchFingers
//Author		Dave Whiteside
//Date			Thu 3 Sep 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::LaunchFingers(	mobileitem* launcher,
									WorldStuff& worldptr	)
{
	if (WithinVisibleRange(launcher->World,100000))				//RJS 20May99
	{
		TransientItem*	newitem;
		MoveGunAnimData*	adptr;
		WeapAnimData*		weapon;
		UWord	newhdg;
		UWord	newpitch;
		SWord	sin_ang, cos_ang;
		SWord	sin_ang2, cos_ang2;
		SLong	vel;
		SLong	velhori,vely;
		SLong	temp;
		SLong	count,maxfingers;								//RJS 28May99
		SWord	pitchover;

		if (Save_Data.desiredfps > realFrameTime)					//RJS 28May99
			maxfingers = 2;
		else
			maxfingers = 5;


		for (count = 0; count < maxfingers; count++)
		{
			newitem = SimplifiedSpriteLaunch(launcher,			
											FIREB,	
											700,MOBILE_DEBRIS);
			if (newitem)
			{
				adptr = (MoveGunAnimData*)newitem->Anim;
				weapon = (WeapAnimData*) &adptr->weaponlaunchers[0];

				SHAPE.InitTrailFields((UByteP)weapon,0,32000,LT_FUEL);

				LaunchVapourStream((UByteP)weapon,FIREB);	

				newhdg = Math_Lib.rnd();
				newpitch = (Math_Lib.rnd()*13653) >> 16;	//75 degrees
				vel = 150 + ((Math_Lib.rnd()*250)>>16);

				Math_Lib.high_sin_cos((Angles)newpitch,sin_ang,cos_ang);

				temp = (vel * sin_ang)>>ANGLES_SHIFT;	vely = temp;
				temp = (vel * cos_ang)>>ANGLES_SHIFT;	velhori = temp;

				newitem->hdg = (Angles) newhdg;			
				newitem->vely = vely;		
				newitem->velhori = velhori;		
				newitem->roll = ANGLES_0Deg;
				newitem->pitch = (Angles) newpitch;

				// max of 70degrees rotation per second (assuming fifty frames/sec)
				pitchover = Math_Lib.rnd()>>8;
				newitem->TransRandom = pitchover;

				AddTransientItemToWorld(newitem,worldptr);
			}
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchSmokePuff2
//Author		Robert Slater
//Date			Wed 16 Sep 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::LaunchSmokePuff2(mobileitem*	launcher,
									Coords3D		*posP,
									ShapeNum		theShape,
									UWord		deathShape,
									SLong		velhori,
									SLong		vely,
									SWord		hdg,
									SLong		lifetime,
									SLong		maxlife,
									WorldStuff&	worldptr)
{
	TransientItem*	newitem;
	newitem = SimplifiedSpriteLaunch(	launcher,
										theShape,
										lifetime,
										MOBILE_MOVSMK);
	
	if (newitem)
	{
		newitem->World = *posP;
		newitem->World.Y += 200;
		newitem->velhori = velhori;
		newitem->vely = vely;
		newitem->hdg = (Angles) hdg;
		newitem->TransRandom = (maxlife * 6)>>3;
		newitem->roll = (Angles) UWord(lifetime);
		newitem->pitch = (Angles) deathShape;

		AddTransientItemToWorld(newitem, worldptr);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ActivateStation
//Author		Robert Slater
//Date			Tue 16 Sep 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
SLong	TransObj::ActivateStation(AirStrucPtr	ac, UWord &ammotot, UWord	&muzdelay, WorldStuff& world)
{
	SLong	index = -1;												
	UWord	muzVel;	
//Dead	Bool	retval = FALSE;
	SLong	weapon = ac->weap.weapontype;							//RJS 01Apr99

	if ((weapon & LT_MASK) == LT_BULLET)							//RJS 01Apr99
		ac->FrightenBogie();										//RJS 01Apr99
	else
	{

		//drop a pair of bombs always...
		if ((weapon & LT_MASK) == LT_BOMB)									//RJS 11May99
		{
			Bool unArmed;
			if (weapon == LT_NAPALM)
				unArmed = TRUE;
			else
				unArmed = FALSE;

			index = ReActivateStation(ac,muzVel,ammotot,muzdelay,world,unArmed);
			if (index > -1)												
			{															
				SLong	massGone = SHAPE.ReduceLauncherLoad(ac,index);	
																		
				ac->SetWeaponForce(massGone,muzVel,muzdelay);			
//Dead				retval = TRUE;
			}
			else
				return -1;			//allow full reload...
		}
	}

	index = ReActivateStation(ac,muzVel,ammotot,muzdelay,world);
	if (index > -1)												
	{															
		//trigger radio message to tell others to drop...
		if ((weapon & LT_MASK) != LT_BULLET)							//RJS 01Apr99
			OverLay.DecisionMessage(FACMsg,6,ac,ac->ai.unfriendly,ac,FALSE);	//RJS 09Jun99

		SLong	massGone = SHAPE.ReduceLauncherLoad(ac,index);	
																
		ac->SetWeaponForce(massGone,muzVel,muzdelay);			
//Dead		retval = TRUE;
	}				
	
	return(index);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DummyLandedEffect
//Author		Robert Slater
//Date			Wed 28 Oct 1998
//
//Description	For replay...
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::DummyLandedEffect(AirStrucPtr	ac, SLong	landed,UByte atype)
{
	WorldStuff			*world = mobileitem::currworld;
	AreaType			theArea = (AreaType)Three_Dee.GetLandType();
	Bool				onWater = FALSE;
	AircraftAnimData	*adptr = (AircraftAnimData*) ac->Anim;
	ULong oldmovecode;
	Bool		onSparky = FALSE;								//RJS 16May99

//	if (theArea!=atype)
//		_Error.SayAndQuit("Different area types");

	theArea=(AreaType)atype;
	switch (theArea)											//RJS 16May99
	{															//RJS 16May99
		case AT_sea:											//RJS 16May99
		case AT_river:											//RJS 16May99
		case AT_washShore:										//RJS 16May99
			onWater = TRUE;										//RJS 16May99
			break;												//RJS 16May99
		case AT_softRock:										//RJS 16May99
		case AT_hardRock:										//RJS 16May99
		case AT_sandyRock:										//RJS 16May99
		case AT_highRock:										//RJS 16May99
		case AT_lowRock:										//RJS 16May99
		case AT_snowyRock:										//RJS 16May99
		case AT_city:											//RJS 16May99
			onSparky = TRUE;									//RJS 16May99
			break;												//RJS 16May99
	}															//RJS 16May99

	if (ac->IsHealthyMovecode(oldmovecode))
	{
		if (onWater == TRUE)
		{
			adptr->hasdust = TRUE;
			Manual_Pilot.DeathSequenceOverride(ac,AUTO_HITWATER);
			_Miles.PlayOnce(FIL_SFX_COLLISION_WATER,ac);

			switch (landed)
			{
			case _Collide.PROP_TOUCH:
			case _Collide.NOSE_TOUCH:
			{
//DeadCode MS 10Dec98				TransientItem*	newitem;
//DeadCode MS 10Dec98				newitem = SimplifiedSpriteLaunch(ac,DUMY13,400,MOBILE_GANDF);
//DeadCode MS 10Dec98				if (newitem)												
//DeadCode MS 10Dec98				{									
//DeadCode MS 10Dec98					newitem->vely = 150;						
//DeadCode MS 10Dec98					newitem->TransRandom = 1;				
//DeadCode MS 10Dec98					AddTransientItemToWorld(newitem,*world);	
//DeadCode MS 10Dec98				}						
			
				KillLauncher(ac,ac,*world);						//JIM 11Mar99
			}
			break;
			case _Collide.RIGHT_WING_TOUCH:
				SHAPE.ForceDamage(ac,ac,&adptr->RIGHTWINGIN,BS_DEAD);//JIM 11Mar99
				LaunchWaterTrail(ac,*world);
			break;
			case _Collide.LEFT_WING_TOUCH:
				SHAPE.ForceDamage(ac,ac,&adptr->LEFTWINGIN,BS_DEAD);//JIM 11Mar99
				LaunchWaterTrail(ac,*world);
			break;
			default:
				LaunchWaterTrail(ac,*world);
				break;
			}

			LaunchSplashMedium(ac,*world);
		}
		else
		{
			// Are any wheels damaged?
//DeadCode DAW 28Jun99 			if (adptr->LEFTWHEEL ||	adptr->RIGHTWHEEL || adptr->FRONTWHEEL || adptr->BACKWHEEL)
//DeadCode DAW 28Jun99 				landed = _Collide.LANDED_BELLY;

			if (landed == _Collide.LANDED_OK)
			{
				// Perhaps throw up a bit of dirt...

				adptr->hasdust = FALSE;
				if (!adptr->justlanded)
				{
					adptr->justlanded = TRUE;
					_Miles.PlayOnce(FIL_SFX_TYRE_SCREECH1,ac);
				}
			}
			else
			{
//DeadCode RJS 20Apr99				LaunchDirtMedium(ac,*world);
				LaunchMushroomCloud(ac,10,*world);				//RJS 20Apr99

				switch (landed)
				{
				case _Collide.PROP_TOUCH:
				case _Collide.NOSE_TOUCH:
				case _Collide.RIGHT_WING_TOUCH:
				case _Collide.LEFT_WING_TOUCH:
				{
					SHAPE.DetatchAllVapourStreams(ac);
					LaunchBigExplosion(ac,*world,ac->shape);
					LaunchFingers(ac,*world);

					Manual_Pilot.DeathSequenceOverride(ac,AUTO_NOPPILOT);

					LaunchFire(ac,*world);						//RJS 28Jun99
				}
				break;
//DeadCode RJS 20Apr99				case _Collide.RIGHT_WING_TOUCH:
//DeadCode RJS 20Apr99					Manual_Pilot.DeathSequenceOverride(ac,AUTO_CRASHROLL);
//DeadCode RJS 20Apr99					adptr->hasdust = TRUE;
//DeadCode RJS 20Apr99					LaunchDustTrail2(ac,*world); // Maybe sparks, if on hard ground...
//DeadCode RJS 20Apr99					SHAPE.ForceDamage(ac,ac,&adptr->RIGHTWINGIN,BS_DEAD);//JIM 11Mar99
//DeadCode RJS 20Apr99				break;
//DeadCode RJS 20Apr99				case _Collide.LEFT_WING_TOUCH:
//DeadCode RJS 20Apr99					Manual_Pilot.DeathSequenceOverride(ac,AUTO_CRASHROLL);
//DeadCode RJS 20Apr99					adptr->hasdust = TRUE;
//DeadCode RJS 20Apr99					LaunchDustTrail2(ac,*world); // Maybe sparks, if on hard ground...
//DeadCode RJS 20Apr99					SHAPE.ForceDamage(ac,ac,&adptr->LEFTWINGIN,BS_DEAD);//JIM 11Mar99
//DeadCode RJS 20Apr99				break;
				default:
				{
					if (ac->vel < MPH100)						//RJS 11Dec98
					{
						if (onSparky)
							LaunchTransientTrail(ac,SparkShape,4,TRUE,*world,65536,TRUE);
						else
						{
							adptr->hasdust = TRUE;
							LaunchDustTrail2(ac,*world);
						}
					}
					else
					{
						LaunchFakeDelayedExplosion(ac,*world);

						SHAPE.DetatchAllVapourStreams(ac);
						if (!onSparky)
						{
							adptr->hasdust = TRUE;
							LaunchDustTrail2(ac,*world);
						}

						LaunchTransientTrail(ac,SmallFireballShape,300,FALSE,*world,65536);
						LaunchCrater(ac,*world);								//RJS 13May99
					}

					Manual_Pilot.DeathSequenceOverride(ac,AUTO_CRASHSKID);
				}
				break;
				}
			}
		}
	}
	else
	{
		if (_Replay.Playback)
		{
			if (onWater)
			{
				AircraftAnimData	*adptr = (AircraftAnimData*) ac->Anim;
				adptr->ENGINELEFTIN = BS_DEAD;			//Make fire invisible

				LaunchSplashMedium(ac,*world);
			}
			else
			{
//DeadCode RJS 20Apr99				LaunchDirtMedium(ac,*world);
				KillLauncher(ac,ac,*world);						//JIM 11Mar99
//DeadCode RJS 21Apr99				SHAPE.ResetAnimData_NewShape(ac,PDEATH);		//RJS 30Mar99
//DeadCode RDH 30Mar99				ac->shape = PDEATH;
				LaunchFire(ac,*world);
			}

			//Is this really an aircraft??
			if (oldmovecode != 0xFFFFFFFF)
			{
				if (onWater)		//Fiddle movecode dirty, and sink
					_Replay.ReplayDeathMode = RDEATH_SKID;
				else
					_Replay.ReplayDeathMode = RDEATH_NULL;
			}
		}
		else
		{
			if (oldmovecode != AUTO_NOPPILOT)	//Strange if it is!
			{
				ac->pitch = ANGLES_0Deg;							//DAW 03Sep98
				ac->roll = ANGLES_0Deg;								//DAW 03Sep98

				if (onWater)
				{
					AircraftAnimData	*adptr = (AircraftAnimData*) ac->Anim;
					adptr->ENGINELEFTIN = BS_DEAD;			//Make fire invisible

					LaunchSplashMedium(ac,*world);
				}
				else
				{
//DeadCode RJS 20Apr99					LaunchDirtMedium(ac,*world);
					KillLauncher(ac,ac,*world);					//JIM 11Mar99
					if (View_Object && (ac==Manual_Pilot.ControlledAC2))//RDH 02Sep98
						View_Object->SetToDeathView();				//RDH 02Sep98
//DeadCode RJS 21Apr99					SHAPE.ResetAnimData_NewShape(ac,PDEATH);		//RJS 30Mar99
//DeadCode RDH 30Mar99					ac->shape = PDEATH;
					LaunchFire(ac,*world);
				}

				//Is this really an aircraft??
				if (oldmovecode != 0xFFFFFFFF)
				{
					ac->vel = 0;
					if (onWater)		//Fiddle movecode dirty, and sink
						ac->movecode = AUTO_HITWATER;
					else
						ac->movecode = AUTO_NOPPILOT;
				}
			}
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchBridgeElement
//Author		Robert Slater
//Date			Fri 30 Oct 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::LaunchBridgeElement(	ItemPtr	launcher,
										Coords3D& noncorrectedgrpcoords,
										SWord	groupindex,
										WorldStuff&	worldptr)
{
	MyGroundVector	pos;
	ShapeNum		shapehit;
	UWord			ghdg;
	MinAnimData		*mad = (MinAnimData*) SHAPE.GetGroupItemAnimHdg(launcher,shapehit,groupindex,&pos,ghdg);
	UWord			animoffset = launcher->Anim.Offset(mad);//((UByteP)mad) - ((UByteP)&launcher->Anim[0]);

	if (mad)
	{
		mad->IsInvisible = 1;//Turn off the original bridge element...

		TransientItem*	newitem;
		newitem = SimplifiedSpriteLaunch(	launcher,
											shapehit,
											1000,
											MOBILE_DEADBRIDGE);
		
		if (newitem)
		{
			newitem->World = noncorrectedgrpcoords;
			newitem->TransRandom = animoffset & 0x0FFF;
			newitem->hdg = (Angles) ghdg;

			SWord	roll,pitch;
			UWord	rp = 0;

			roll = Math_Lib.rnd();
			pitch = Math_Lib.rnd();

			// top 4 bits are for pitch and roll variations...
			if (roll < 0)
			{
				//-ve
				if (roll < -16384)
					rp = 3;			//fast
				else
					rp = 2;			//slow
			}
			else
			{
				//+ve
				if (roll > 16384)
					rp = 1;			//fast
				else
					rp = 0;			//slow

			}

			rp <<= 2;

			if (pitch < 0)
			{
				//-ve
				if (pitch < -16384)
					rp |= 3;			//fast
				else
					rp |= 2;			//slow
			}
			else
			{
				//+ve
				if (pitch > 16384)
					rp |= 1;			//fast
				else
					rp |= 0;			//slow

			}

			newitem->TransRandom |= (rp << 12);

			MinAnimData*	el_mad = (MinAnimData*) newitem->Anim;
			el_mad->itemstate = DEAD;

			AddTransientItemToWorld(newitem, worldptr);
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MobileDeadBridge
//Author		Robert Slater
//Date			Fri 30 Oct 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::MobileDeadBridge(TransientItemPtr transit, WorldStuff& world)
{
	SLong	timeleft = transit->LaunchTime;
	UWord	roff = transit->TransRandom;

	if (timeleft)
	{
		if ((transit->LaunchTime-=Timer_Code.FRAMETIME)<0)
			transit->LaunchTime=0;

		SWord	roll,pitch;
		roll = roff & 0xF000;
		roll >>= 12;
		pitch = roll & 3;

		roll >>= 2;

		//after 4 secs, should have tilted 90deg...
		if (roll < 0)
			roll--;
		else
			roll++;

		roll *= 40;

		if (pitch < 0)
			pitch--;
		else
			pitch++;

		pitch *= 30;

		transit->roll += (Angles) roll;	
		transit->pitch += (Angles) pitch;

		GAndFrictionFixedPitch(transit,RetardedDrag,OrdinaryDrag);

		if ((transit->LaunchTime & 0x06)==0)
		{
			SLong	groundheight = GetGroundLevel(transit);		//RJS 14Apr99
			if (transit->World.Y <= groundheight)
			{
				transit->World.Y = groundheight;
				transit->LaunchTime=0;

				LaunchSplashLarge(transit,world);
			}
		}
	}
	else
	{
		// Remove the transient bridge element, and turn on the real bridge element to dead....
		MinAnimData*	mad;
		animptr			adptr = transit->Launcher->Anim;		//RJS 21Apr99
																//RJS 21Apr99
		adptr += (roff & 0x0FFF);								//RJS 21Apr99

		mad = (MinAnimData*) adptr;								//RJS 21Apr99
		mad->IsInvisible = 0;//Turn the element back on in its new home splashing about in the water...

		AddTransientItemToDeadList(transit);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchDirtyFingers
//Author		Robert Slater
//Date			Mon 9 Nov 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::LaunchDirtyFingers(mobileitem*	launcher, WorldStuff&	worldptr)
{
	if (Save_Data.desiredfps <= realFrameTime)					//RJS 11Jun99
	{
		TransientItem*		newitem;
		MoveGunAnimData*	adptr;
		WeapAnimData*		weapon;
		UWord	newhdg;
		UWord	newpitch;
		SWord	sin_ang, cos_ang;
		SWord	sin_ang2, cos_ang2;
		SLong	vel;
		SLong	velhori,vely;
		SLong	temp;
		SLong	count;
		SLong	groundheight = GetGroundLevel(launcher) + METRES01;	//RJS 14Apr99
		SLong	fingercnt = 3 + Math_Lib.rnd(4);

		for (count = 0; count < fingercnt; count++)
		{
			newitem = SimplifiedSpriteLaunch(launcher,			
											PLUME2,
											350,MOBILE_DEBRIS);
			if (newitem)
			{
				adptr = (MoveGunAnimData*)newitem->Anim;
				weapon = (WeapAnimData*) &adptr->weaponlaunchers[0];

				SHAPE.InitTrailFields((UByteP)weapon,0,-1,LT_MUDDY);

				LaunchVapourStream((UByteP)weapon,PLUME2);	

				newhdg = Math_Lib.rnd();

	//			newitem->World.Y = groundheight;
				newitem->hdg = (Angles) newhdg;			
				newitem->vely = 100 + Math_Lib.rnd(200);		
				newitem->velhori = 50 + Math_Lib.rnd(70);
				newitem->roll = ANGLES_0Deg;
				AddTransientItemToWorld(newitem,worldptr);
			}
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		TwatWithWeapon
//Author		Robert Slater
//Date			Mon 9 Nov 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::TwatWithWeapon(ItemPtr	trg, ShapeNum	theShape, SByte gindex, WorldStuff&	worldptr)
{
	TransientItem*	newitem = NULL;

	switch ((int)theShape)
	{
		case DUMY10:
		case BMB500:
			newitem = LaunchUnguidedMissile(Manual_Pilot.ControlledAC2,theShape,LIFETIME_BOMB,MOBILE_BOMBDROP);
			break;
		case BULLET:
			newitem = LaunchUnguidedMissile(Manual_Pilot.ControlledAC2,theShape,LIFETIME_BULLET,MOBILE_BULLET);
			break;
		case ROCKET:
			newitem = LaunchUnguidedMissile(Manual_Pilot.ControlledAC2,theShape,LIFETIME_BOMB,MOBILE_ROCKET);
			break;
	}

	if (newitem)
	{
		newitem->World.X = trg->World.X;						
		newitem->World.Y = trg->World.Y + (METRES01 * 100);						
		newitem->World.Z = trg->World.Z;						

		newitem->vely = 0;
		newitem->velhori = 0;
		newitem->velx = 0;
		newitem->velz = 0;

		//Shit fix to knock the centre of a bridge...
//		newitem->World.X += 1000;
//		newitem->World.Z += 1000;

		AddTransientItemToWorld(newitem, worldptr);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchFlash
//Author		Robert Slater
//Date			Mon 16 Nov 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::LaunchFlash(mobileitem*	launcher, UByte	damsize, WorldStuff&	worldptr)
{
	TransientItem*		newitem;
	
//DeadCode MS 30Nov98	newitem = SimplifiedSpriteLaunch((mobileitem*)launcher,EXPLO,3,MOBILE_STATIONARY);
	newitem = SimplifiedSpriteLaunch((mobileitem*)launcher,FLASH,30,MOBILE_STATIONARY);
	if (newitem)
	{
		newitem->DrawOffset = 4096;
		AddTransientItemToWorld(newitem,worldptr);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchFingersFire
//Author		Robert Slater
//Date			Mon 16 Nov 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::LaunchFingersFire(mobileitem* launcher,
									WorldStuff& worldptr	)
{
	if (WithinVisibleRange(launcher->World,200000))				//RJS 30Apr99
	{
		TransientItem*	newitem;
		UWord	newhdg;
		SLong	vel;
		SLong	vely;
		SLong	count;
		SLong	cntrand = 3 + Math_Lib.rnd(4);
		SLong	groundheight = GetGroundLevel(launcher) + 250;		//RJS 14Apr99

		if (launcher->Status.size == AirStrucSize)
			vely = 150;
		else
			vely = 0;

		if (Save_Data.desiredfps > realFrameTime)					//RJS 28May99
			cntrand = 2;										//RJS 28May99

		for (count = 0; count < cntrand; count++)
		{
			newitem = LaunchUnguidedMissile(launcher,			
											NapalmFingerShape,	
											1000,MOBILE_DEBRIS);
			if (newitem)
			{
				WeapAnimData*	weapon;
				MoveGunAnimData* adptr = (MoveGunAnimData*)newitem->Anim;

				weapon = (WeapAnimData*) &adptr->weaponlaunchers[0];

				SHAPE.InitTrailFields((UByteP)weapon,0,32000,LT_FUEL);

				LaunchVapourStream((UByteP)weapon,NapalmFingerShape);

				newhdg = Math_Lib.rnd();

				vel = 200 + Math_Lib.rnd(150);

				newitem->World.Y = groundheight;
				newitem->hdg = (Angles) newhdg;			
				newitem->vely = 350-vel;		
				newitem->velhori = vel;		
				AddTransientItemToWorld(newitem,worldptr);
			}
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchTossedShape
//Author		Robert Slater
//Date			Tue 17 Nov 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::LaunchTossedShape(mobileitem*	launcher, SByte	groupindex,Coords3D hittercoords,SLong strength, WorldStuff&	worldptr)
{
	if (WithinVisibleRange(launcher->World,300000))				//RJS 30Apr99
	{
		if (launcher->Status.size != TransientSize)
		{
			MyGroundVector	pos;
			UWord			realhdg;
			ShapeNum		shapehit;
			MinAnimData		*mad = (MinAnimData*) SHAPE.GetGroupItemAnimHdg(launcher,shapehit,groupindex,&pos,realhdg);
			UWord			animoffset = launcher->Anim.Offset(mad);// ((UByteP)mad) - ((UByteP)&launcher->Anim[0]);
			SLong			shpsize;

			if (mad)
			{
				ShapeDescPtr	sdptr = SHAPESTUFF.GetShapePtr(shapehit);
				shpsize = sdptr->Size << 4;

				if (shpsize < 1000)
				{
					SLong	dx,dz,dist;
					SWord	thehdg;

					// Throw from the direction the weapon came from...
					dx = pos.gx - hittercoords.X;
					dz = pos.gz - hittercoords.Z;

					thehdg = Math_Lib.arctan(dz,dx);
					if (dx > 0)
						thehdg = ANGLES_90Deg - thehdg;
					else
						thehdg = ANGLES_270Deg - thehdg;

					//50m is minimum toss damage...
					if (strength > 0)
					{
						SLong	vely,maxvel,thesize;
						SLong	maxtoss;
						SLong	hdgintercept = SWord(UWord(thehdg) - realhdg);
						SLong	pitchintercept;
						SWord	pitchmag,hdgmag,hpmag;

						dist = Math_Lib.distance3d(dx,dz,0);
						dist -= shpsize;
						if (dist < 0)
							dist = 0;

						hdgintercept <<= 8;
						hdgintercept /= ANGLES_90Deg;
						if (hdgintercept > 256)
						{
							hdgintercept = 0;
							pitchintercept = 256 - hdgintercept;
						}
						else
							pitchintercept = 256 - hdgintercept;

						pitchmag = (pitchintercept * 127)>>8;		//max of 90degree flip in 1 sec ish
						hdgmag = (hdgintercept * 127)>>8;

						hpmag = hdgmag << 8;
						hpmag |= pitchmag;

						maxtoss = 5000 - dist;
						thesize = 1000 - shpsize;

						maxvel = (500 * strength) / 31;	//31 is max strength..
						maxvel *= thesize;
						maxvel /= 1000;

						if (launcher->Status.size == FORMATIONSIZE)//RJS 23Jun99
						{
 							if (	!launcher->Status.deadtime )
//DEADCODE JIM 09/09/99 								&&	(launcher->movecode != AUTO_NOPPILOT)	)//RJS 01Jul99
 								FormationItemPtr(*launcher)->BreakForm(); //JIM 09/09/99
						}

						// 60degree throw max...
						if (maxtoss > 0)
						{
							vely = (maxtoss * maxvel * 6) / 9;
							vely /= 5000;
						}
						else
							vely = 0;

						mad->IsInvisible = 1;//Turn off the original element...

						TransientItem*	newitem;
						newitem = SimplifiedSpriteLaunch(	launcher,
															shapehit,
															1000,
															MOBILE_ATEAM);
				
						if (newitem)
						{
							newitem->World.X = pos.gx;
							newitem->World.Y = pos.gy;
							newitem->World.Z = pos.gz;
							newitem->TransRandom = animoffset;
							newitem->hdg = (Angles) realhdg;
							newitem->vely = vely;
							newitem->velhori = maxvel - vely;

							newitem->velx = thehdg;
							newitem->velz = pitchmag;

							MinAnimData*	el_mad = (MinAnimData*) newitem->Anim;
							el_mad->itemstate = mad->itemstate;

							if (launcher->Status.size >= MobileSize)
							{
								launcher->movecode = AUTO_NOPPILOT;
								if (launcher==Persons2::PlayerSeenAC)	//shouldn't be, but it's late, ok?
									Persons2::PlayerGhostAC->movecode=AUTO_NOPPILOT;
							}

							AddTransientItemToWorld(newitem, worldptr);
						}
					}
				}
			}
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MobileCollapse
//Author		Robert Slater
//Date			Wed 18 Nov 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::MobileCollapse(TransientItemPtr transit, WorldStuff& world)
{
	SLong	timeleft = transit->LaunchTime;
	UWord	roff = transit->TransRandom;

	if (timeleft)
	{
		if ((transit->LaunchTime-=Timer_Code.FRAMETIME)<0)
			transit->LaunchTime=0;

		SWord	roll,pitch;
		roll = roff & 0xF000;
		roll >>= 12;
		pitch = roll & 3;

		roll >>= 2;

		//after 4 secs, should have tilted 90deg...
		if (roll < 0)
			roll--;
		else
			roll++;

		roll *= 81;

		if (pitch < 0)
			pitch--;
		else
			pitch++;

		pitch *= 60;

		transit->roll += (Angles) roll;	
		transit->pitch += (Angles) pitch;

		GAndFrictionFixedPitch(transit,RetardedDrag,OrdinaryDrag);

		if ((transit->LaunchTime & 0x06)==0)
		{
			UByte	theArea;
			SLong	groundheight = GetGroundLevel(transit,theArea);//RJS 28Apr99
			if (transit->World.Y <= groundheight)
			{
//DeadCode RJS 28Apr99				UByte	theArea = Three_Dee.GetLandType();		//RJS 27Nov98

				Coords3D	hitcoords;

				transit->World.Y = groundheight;
				transit->LaunchTime=0;

				hitcoords = transit->World;

				DoImpactGround(transit,hitcoords,theArea);
			}
		}
	}
	else
	{
		MinAnimData*	mad;
		animptr			adptr = transit->Launcher->Anim;		//RJS 21Apr99
																//RJS 21Apr99
		adptr += (roff & 0x0FFF);								//RJS 21Apr99
																//RJS 21Apr99
		mad = (MinAnimData*) adptr;								//RJS 21Apr99
		mad->IsInvisible = 0;//Turn the element back on in its new home splashing about in the water...

		AddTransientItemToDeadList(transit);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchDirtyBuildingFingers
//Author		Mark Shaw (Yeah, right!)
//Date			Mon 30 Nov 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::LaunchDirtyBuildingFingers(mobileitem*	launcher, UWord	direction, WorldStuff&	worldptr)
{
	if (Save_Data.desiredfps <= realFrameTime)					//RJS 11Jun99
	{
		if (WithinVisibleRange(launcher->World,300000))				//RJS 30Apr99
		{
			TransientItem*		newitem;
			MoveGunAnimData*	adptr;
			WeapAnimData*		weapon;
			UWord	newhdg;
			UWord	newpitch;
			SWord	sin_ang, cos_ang;
			SWord	sin_ang2, cos_ang2;
			SLong	vel;
			SLong	velhori,vely;
			SLong	temp;
			SLong	count;
			SLong	fingercnt = 3 + Math_Lib.rnd(4);

			for (count = 0; count < fingercnt; count++)
			{
				newitem = SimplifiedSpriteLaunch(launcher,			
												PLUME2,
												350,MOBILE_DEBRIS);
				if (newitem)
				{
					adptr = (MoveGunAnimData*)newitem->Anim;
					weapon = (WeapAnimData*) &adptr->weaponlaunchers[0];

					SHAPE.InitTrailFields((UByteP)weapon,0,-1,LT_MUDDY);

					LaunchVapourStream((UByteP)weapon,PLUME2);	

					newhdg = direction + (Math_Lib.rnd(ANGLES_180Deg) - ANGLES_90Deg);

					newitem->hdg = (Angles) newhdg;			
					newitem->vely = 100 + Math_Lib.rnd(100);		
					newitem->velhori = 150 + Math_Lib.rnd(70);
					newitem->roll = ANGLES_0Deg;
					AddTransientItemToWorld(newitem,worldptr);
				}
			}
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchSmallThug
//Author		Robert Slater
//Date			Thu 3 Dec 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::LaunchSmallThug(	item*		launcher,
									item*		destination,
									ShapeNum	theshape,
									SLong		gindex,
									SLong		lifeleft	)
{
	TransientItem*	newitem;
	WorldStuff*		worldptr = mobileitem::currworld;
	ShapeNum		shapehit;
	MyGroundVector	pos;
	MinAnimData		*mad = (MinAnimData*) SHAPE.GetGroupItemAnim(destination,shapehit,gindex,&pos);
	UWord			animoffset = destination->Anim.Offset(mad);//(UByteP)mad - (UByteP)&destination->Anim[0];

	newitem = SimplifiedSpriteLaunch(	destination,	
										theshape,		
										lifeleft,	
										MOBILE_SMALLTHUG);
	
	if (newitem)
	{
		mad->IsBullied = 1;

		ThugAnimData	*adptr = (ThugAnimData*) newitem->Anim;

		if (adptr)
			adptr->panimoff = animoffset;

		if (launcher->Status.size == TRANSIENTSIZE)								//RJS 18Jun99
			newitem->Launcher = ((TransientItemPtr)launcher)->Launcher;
		else
			newitem->Launcher = launcher;

		newitem->Target = destination;
		newitem->World.X = pos.gx;
		newitem->World.Y = pos.gy;
		newitem->World.Z = pos.gz;

		AddTransientItemToWorld(newitem,*worldptr);
	}
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		
//Author		RDH 02/03/99
//Date			
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::ChooseMusic(AirStrucPtr	ac)
{
	if (ac==Manual_Pilot.ControlledAC2)					
	{
			_Miles.SequenceAudible(MOOD_DOOMED);		//RDH 01/03/99
	}else if (ac->PlayerInGroup())
	{
			_Miles.SequenceAudible(FIL_MUSIC_SAD);		//RDH 01/03/99
	}else
	{
		if (ac->nationality == Manual_Pilot.ControlledAC2->nationality)
			_Miles.SequenceAudible(MOOD_ANGRY);		//RDH 01/03/99
		else
			_Miles.SequenceAudible(MOOD_HOPEFUL);		//RDH 01/03/99
	}

}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ExplodeAC
//Author		Robert Slater
//Date			Fri 4 Dec 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::ExplodeAC(AirStrucPtr	ac, ItemPtr killer, WorldStuff&	worldptr,Bool setdamage)
{
	AircraftAnimData*	adptr = (AircraftAnimData*) ac->Anim;							//RJS 20May99
	if (!adptr->IsInvisible && (ac->shape != PDEATH))									//RJS 20May99
	{
		ChooseMusic(ac);
//Dead RJS 20May99		AircraftAnimData*	adptr = (AircraftAnimData*) ac->Anim;
		SWord	sin_ang,cos_ang;								
		SLong	vely, velhori, velx, velz;						
																
		// Explode!!... kill speed so we can see effects!!	
		
		if (!(_DPlay.Implemented || _Replay.Record || _Replay.Playback))
		{
// I dont think so - altering vel outside movecode screws deltas

			ac->vel /= 4;											
		}

		Math_Lib.high_sin_cos(ac->pitch,sin_ang,cos_ang);		
																
		vely = (ac->vel * sin_ang)>>ANGLES_SHIFT;				
		velhori = (ac->vel * cos_ang)>>ANGLES_SHIFT;			
																
		Math_Lib.high_sin_cos(ac->hdg,sin_ang,cos_ang);			
																
		velx = (velhori * sin_ang)>>ANGLES_SHIFT;				
		velz = (velhori * cos_ang)>>ANGLES_SHIFT;				
																
		ac->vely = vely;										
		ac->velhori = velhori;									
		ac->velx = velx;										
		ac->velz = velz;										
																
		// Explode!!
		LaunchBigExplosion(ac,worldptr,ac->shape);
		LaunchFingers(ac,worldptr);
		LaunchTransientTrail(ac,FireballShape,500,FALSE,worldptr,400);

#ifndef NDEBUG
#ifdef COLTRACE
	UWord cw=GETFPCW();
	::AfxTrace("...EXPLODED!: 0x00%x\n",ac);
	SETFPCW(cw);
#endif
#endif


		if (ac==Manual_Pilot.ControlledAC2)					
		{
			if (HitTheDeck)										//RJS 11Jun99
				Persons2::UpdatePlayerLog	(ac,EventLog::FATALCRASH);//RJS 11Jun99

			_Miles.StopEngine();							
															
			if (View_Object)
			{
				SLong	groundheight = GetGroundLevel(ac);		//RJS 14Apr99
				if ((ac->World.Y-groundheight) > 50000) // max height
					View_Object->SetToDeathView(DEATH_AIRTOAIR);
				else
					View_Object->SetToDeathView(DEATH_AIRTOGROUND);
			}
		}

		if (setdamage)
		{
			SHAPE.ForceDamage(ac,killer,&adptr->TAIL,BS_DEAD,32);//JIM 11Mar99
			SHAPE.ForceDamage(ac,killer,&adptr->FIN,BS_DEAD,32);//JIM 11Mar99
			SHAPE.ForceDamage(ac,killer,&adptr->RIGHTWINGOUT,BS_DEAD,32);//JIM 11Mar99
			SHAPE.ForceDamage(ac,killer,&adptr->LEFTWINGOUT,BS_DEAD,32);//JIM 11Mar99
			SHAPE.ForceDamage(ac,killer,&adptr->LEFTWINGIN,BS_DEAD,32);//JIM 11Mar99
			SHAPE.ForceDamage(ac,killer,&adptr->RIGHTWINGIN,BS_DEAD,32);//JIM 11Mar99
		}

		adptr->PILOTLEFT = BS_DEAD;
		adptr->PILOTRIGHT = BS_DEAD;
		if (ac->nationality == Manual_Pilot.ControlledAC2->nationality)
		{
			if (!HitTheDeck)									//RDH 09May99
				_DamageChat.PlayerSideBlewUp(ac);
			else
				_DamageChat.PlayerSidePiledIn(ac);
		}
		else
		{
			bool	migdead = false;
			if (ac->classtype->phrasename == PHRASE_MIGS)
				migdead = true;

			_DamageChat.OtherSideBlewUp((AirStrucPtr)*killer,(AirStrucPtr)*ac,migdead);			//RJS 20May99
		}

		adptr->IsInvisible = 1;	//RJS 11Dec98
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchGunDot
//Author		Robert Slater
//Date			Mon 7 Dec 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::LaunchGunDot(mobileitem*	launcher, WorldStuff&	worldptr)
{
	TransientItem*	newitem;

	newitem = SimplifiedSpriteLaunch(	launcher,	
										SPARK,		
										10,	
										MOBILE_STATIONARY);
	
	if (newitem)
		AddTransientItemToWorld(newitem,worldptr);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchSmallFlash
//Author		Robert Slater
//Date			Tue 8 Dec 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void TransObj::LaunchSmallFlash(mobileitem* launcher,WorldStuff& worldptr,Bool heightfix)
{
	TransientItem*	newitem;

	newitem = RelativeSpriteLaunch(launcher,launcher->shape,EXPLO,20,MOBILE_BIGEXP);//RJS 20Apr98
	if (newitem)
	{
		if (heightfix)											//RJS 05May99
			newitem->World.Y += 200;							//RJS 05May99

		if ((launcher->Status.size >= MovingSize) && (launcher->Status.size != TransientSize))//RJS 16Nov98
			newitem->Target = launcher;							//RJS 16Nov98

		_Miles.PlaySample((FileNum) (FIL_SFX_EXPLOSION_OILDRUM1+Math_Lib.rnd(5)), newitem);
		AddTransientItemToWorld(newitem,worldptr);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchSparkTrail
//Author		Robert Slater
//Date			Fri 11 Dec 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void TransObj::LaunchTransientTrail(mobileitem* launcher,
									ShapeNum	theShape,
									SLong		maxlife,
									Bool		throwit,
									WorldStuff& worldptr,
									SLong		totaltime,
									Bool		onGround	)
{
	TransientItem*	newitem;

	newitem = LaunchGuidedMissile(launcher,launcher,ShockwaveShape,Math_Lib.rnd(50),MOBILE_RICOCHET);
	if (newitem)
	{
		if (totaltime < 65536)									//RJS 14May99
			newitem->TmpLaunchTime = totaltime;					//RJS 19May99
		else													//RJS 14May99
			newitem->TmpLaunchTime = 65535;						//RJS 19May99

		newitem->TransRandom = theShape;	//the shape...
		newitem->hdg = (Angles) throwit;		//We can throw in all directions...
		newitem->pitch = (Angles) maxlife;	//Max lifetime...
		if (onGround)
			newitem->TransRandom |= 0x8000;

		AddTransientItemToWorld(newitem,worldptr);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		KillLauncherComms
//Author		Andy McMaster
//Date			Fri 8 Jan 1999
//
//Description	Explode effect... once received ac_collision packet.
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void TransObj::KillLauncherComms(AirStrucPtr	ac)
{
	WorldStuff	*world = mobileitem::currworld;

	SHAPE.DetatchAllVapourStreams(ac);

//DeadCode AMM 24Mar99	if (ac==Persons2::PlayerSeenAC)
//DeadCode AMM 24Mar99	{
	if (!_Replay.Record)
	{
//DeadCode AMM 15Apr99		if (Manual_Pilot.DeathSequenceOverride(ac,AUTO_SPIRAL2GROUND,true))
		{
			// what is the killer??
			ExplodeAC(ac,ac,*world,FALSE);						//JIM 11Mar99
		}
	}
	else
	{
		ExplodeAC(ac,ac,*world,FALSE);						
	}

//DeadCode AMM 24Mar99	}
//DeadCode AMM 24Mar99	else
//DeadCode AMM 24Mar99	{
//DeadCode AMM 24Mar99		ExplodeAC(ac,*world,FALSE);
//DeadCode AMM 24Mar99	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchJunk
//Author		Robert Slater
//Date			Fri 15 Jan 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::LaunchJunk(	mobileitem*	launcher,
								ShapeNum	theShape,
								Coords3D&	pos,
								WorldStuff&	worldptr		)
{
	TransientItem*	newitem;

	newitem = SimplifiedSpriteLaunch(	launcher,
										theShape,
										50,
										MOBILE_GANDF);
	if (newitem)
	{
		newitem->hdg = (Angles) (launcher->hdg + Math_Lib.rnd(ANGLES_30Deg) - ANGLES_15Deg);
		newitem->pitch = (Angles) Math_Lib.rnd();
		newitem->vely = launcher->vely;
		newitem->velhori = launcher->velhori;

		AddTransientItemToWorld(newitem,worldptr);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchTimeBomb
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
void	TransObj::LaunchTimeBomb(ItemPtr	launcher,ULong animoffset,WorldStuff& worldptr)
{
	animptr	AnimPtr = launcher->Anim;
	ULong	currdam = AnimPtr[(int)animoffset];
	ULong	maxtime = (15000*(BS_DEAD-currdam))/(BS_DEAD-BS_DAMLV2);//5 mins...

	TransientItem*	newitem;
	newitem = SimplifiedSpriteLaunch(	launcher,
										EMPTY,
										maxtime + Math_Lib.rnd(maxtime),
										MOBILE_SCALEFIST	);
	if (newitem)
	{
		MinAnimData*	mad = (MinAnimData*) newitem->Anim;
		mad->IsInvisible = 1;

		newitem->TransRandom = animoffset;
		newitem->DrawOffset = (newitem->LaunchTime / 2);

		AddTransientItemToWorld(newitem,worldptr);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MobileScaleFist
//Author		Robert Slater
//Date			Wed 10 Feb 1999
//
//Description	Twats a specific damage anim byte over a period of time...
//				(at the moment, twice...)
//				(assumes it has been triggered at BS_DAMLV2)
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void TransObj::MobileScaleFist(TransientItemPtr transit,WorldStuff&)
{
	SWord	frametime = Timer_Code.FRAMETIME;

	SLong	timeleft = transit->LaunchTime;
	if (timeleft)
	{
		transit->LaunchTime -= frametime;
		if (transit->LaunchTime <= transit->DrawOffset)
		{
			animptr	animPtr = transit->Launcher->Anim;
			UWord	damval = animPtr[transit->TransRandom];

			damval += ((BS_DEAD-BS_DAMLV2)/2);

			transit->DrawOffset = 0;

			SHAPE.ForceDamage(transit->Launcher,transit->Launcher,&animPtr[transit->TransRandom],(BitStates)damval,32);//JIM 11Mar99
		}
	}
	else
	{
		animptr	animPtr = transit->Launcher->Anim;				//RJS 21Apr99

		SHAPE.ForceDamage(transit->Launcher,transit->Launcher,&animPtr[transit->TransRandom],BS_DEAD,32);//RJS 21Apr99

		AddTransientItemToDeadList(transit);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AddTransientItemToTrailList
//Author		Robert Slater
//Date			Thu 18 Feb 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::AddTransientItemToTrailList(TransientItemPtr	newitem)
{
	SLong				newslot = StaticTrailIndex;
//Dead	TransientItemPtr	slist = StaticTrailList[newslot];

	while (StaticTrailList[newslot].item)						//RJS 13May99
	{
		if (newslot < MaxTrails)								//RJS 06Apr99
			newslot++;
		else
			break;
	}

	while (StaticTrailList[newslot].item)						//RJS 13May99
	{
		if (newslot > 0)
			newslot--;
		else
			break;
	}
#ifndef NDEBUG
#pragma message("AddTransientItemToTrailList debug!!")
	for (int index=0; index < MaxTrails; index++)
	{
		//Should NEVER get here!!!!
		if (StaticTrailList[index].item==newitem)				//RJS 13May99
			INT3;
	}
#endif

	StaticTrailIndex = newslot;
	if (StaticTrailList[StaticTrailIndex].item==NULL)			//RJS 13May99
	{
		StaticTrailList[StaticTrailIndex].item = newitem;		//RJS 13May99
		StaticTrailList[StaticTrailIndex].time = View_Object->TimeOfDay();//RJS 13May99
		StaticTrailCnt++;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		RemoveTransientItemFromTrailList
//Author		Robert Slater
//Date			Thu 18 Feb 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::RemoveTransientItemFromTrailList(TransientItemPtr	deaditem)
{
	SLong	index;
	for (index=0; index < MaxTrails; index++)					//RJS 08Apr99
	{
		if (StaticTrailList[index].item == deaditem)			//RJS 13May99
		{
			StaticTrailList[index].item = NULL;					//RJS 13May99
			StaticTrailList[index].time = 0xFFFFFFFF;			//RJS 13May99
			StaticTrailIndex = index;			//next free slot...
			StaticTrailCnt--;					
			break;
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CleanUpTrailList
//Author		Robert Slater
//Date			Thu 18 Feb 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::CleanUpTrailList()
{
	SmokeTrailAnimData*		adptr;
	SLong	index;
	for (index=0; index < MaxTrails; index++)					//RJS 06Apr99
	{
//DeadCode DAW 21Jun99 		if (StaticTrailList[index].item)						//RJS 13Jun99
//DeadCode DAW 21Jun99 		{
//DeadCode DAW 21Jun99 			Coords3DList*	apoint;
//DeadCode DAW 21Jun99 #ifndef	NDEBUG
//DeadCode DAW 21Jun99 #ifdef	MEMTRACE
//DeadCode DAW 21Jun99 	UWord cw=GETFPCW();
//DeadCode DAW 21Jun99 	::AfxTrace("TRANSKILL:\n");
//DeadCode DAW 21Jun99 	SETFPCW(cw);
//DeadCode DAW 21Jun99 #endif
//DeadCode DAW 21Jun99 #endif
//DeadCode DAW 21Jun99 			adptr = (SmokeTrailAnimData*) StaticTrailList[index].item->Anim;
//DeadCode DAW 21Jun99 			apoint = (Coords3DList*) adptr->thelist;
//DeadCode DAW 21Jun99 			apoint->Wipe();
//DeadCode DAW 21Jun99 
//DeadCode DAW 21Jun99 			adptr->thelist = NULL;
//DeadCode DAW 21Jun99 		}

		StaticTrailList[index].item = NULL;						//RJS 13May99
		StaticTrailList[index].time = 0xFFFFFFFF;				//RJS 13May99
	}

	StaticTrailCnt = 0;											//RJS 18Feb99
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ScanTrailListAndSave
//Author		Robert Slater
//Date			Thu 18 Feb 1999
//
//Description	For replay blocks...
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::ScanTrailListAndSave()
{
//DeadCode DAW 06Apr99	SLong	index;
//DeadCode DAW 06Apr99	for (index=0; index < MaxTransients; index++)
//DeadCode DAW 06Apr99	{
//DeadCode DAW 06Apr99
//DeadCode DAW 06Apr99
//DeadCode DAW 06Apr99	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchReplayTrail
//Author		Robert Slater
//Date			Thu 18 Feb 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::LaunchReplayTrail(Coords3D&			cpos,
									UByteP				usmkptr,
									UByteP				thelist	)
{
	ReplaySmlSmkStruc*	smkptr = (ReplaySmlSmkStruc*) usmkptr;
	TransientItemPtr	newitem;
	newitem = SimplifiedSpriteLaunch(	(MobileItemPtr)Persons2::ConvertPtrUID((UniqueID)smkptr->uniqueid),
										SMKSHP,	
										smkptr->lifetime,
										MOBILE_STATIONARY);

	if (newitem)
	{
		WorldStuff*			worldptr = mobileitem::currworld;
		SmokeTrailAnimData*	adptr = (SmokeTrailAnimData*) newitem->Anim;

		newitem->World.X = cpos.X;
		newitem->World.Y = cpos.Y;
		newitem->World.Z = cpos.Z;

		adptr->weaponlaunchers[0].hdg = -1;
		adptr->weaponlaunchers[0].pitch = -1;
		adptr->weaponlaunchers[0].LauncherType = LT_VAPOUR;	//RJS 13Apr99
		adptr->nopoints = smkptr->nopoints;
		adptr->thelist = (ULong) thelist;
		adptr->lifetime = smkptr->lifetime;
		adptr->SmkDescIndex = smkptr->smkindex;
		adptr->currTime = smkptr->currTime;						//RJS 16Jun99

		AddTransientItemToTrailList(newitem);
		AddTransientItemToWorld(newitem,*worldptr);

		trailcounter++;											//DAW 06Apr99
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchNapalmImpacted
//Author		Robert Slater
//Date			Fri 19 Feb 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::LaunchNapalmImpacted(mobileitem* launcher,WorldStuff& worldptr)
{
	TransientItem*	newitem;
	int				dx, dz, thedist;
	SWord			hdg = launcher->hdg;
	SWord			sin_ang,cos_ang;
	int				i;
	SLong			wx, wz, noblobs;
	SWord			timedelay = 0;

	wx = launcher->World.X;
	wz = launcher->World.Z;

	thedist = 750;
	
	Math_Lib.high_sin_cos((Angles)hdg,sin_ang,cos_ang);

	newitem = SimplifiedSpriteLaunch((mobileitem*)launcher,EXPLO,20,MOBILE_STATIONARY);
	if (newitem)
	{
		newitem->DrawOffset = 100;
		AddTransientItemToWorld(newitem,worldptr);
	}

	newitem = SimplifiedSpriteLaunch(	launcher,			
										DUMY12,				
										240,			
										MOBILE_BURNIT);		
	if (newitem)											
	{
//DeadCode RJS 21Apr99		newitem->World.Y = GetGroundLevel(newitem);				//RJS 14Apr99

		Three_Dee.pMigLand->GetShadowAngles(newitem->World,newitem->hdg,newitem->pitch,newitem->roll);

		newitem->Status.deadtime = 1;	// no collision...

		newitem->TransRandom = 50 << 8;
		newitem->TransRandom |= 240;

		if (launcher->Status.size == TRANSIENTSIZE)								//RJS 05May99
			newitem->Launcher = ((TransientItemPtr)launcher)->Launcher;			//RJS 05May99

		AddTransientItemToWorld(newitem,worldptr);			
	}

//	LaunchFingersFire(launcher,worldptr);

	if (Save_Data.desiredfps <= realFrameTime)					//RJS 11Jun99
	{
		int				count;
		for (count = 0; count < 8; count++)			
		{
			newitem = SimplifiedSpriteLaunch(launcher,SPARK,LIFETIME_DEBRISLNCHR,MOBILE_GANDF);//RJS 23Nov98
			if (newitem)
			{
				SLong	vely = 150 + Math_Lib.rnd(150);

				newitem->hdg = (Angles) Math_Lib.rnd();			
				newitem->vely = vely;							
				newitem->velhori = 300 - vely;					

				AddTransientItemToWorld(newitem,worldptr);
			}
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MobileCanopy
//Author		Robert Slater
//Date			Tue 23 Mar 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void TransObj::MobileCanopy(TransientItemPtr transit, WorldStuff&	world)
{
	SLong	timeleft = transit->LaunchTime;
	if (timeleft)
	{
		if ((transit->LaunchTime-=Timer_Code.FRAMETIME)<0)
			transit->LaunchTime=0;

		SWord	pitch = transit->pitch + 100;

		transit->pitch = (Angles) pitch;

		
	}
	else
	{
		if (transit->TransRandom == 1)
		{
			transit->TransRandom = 0;
			transit->LaunchTime = 500;

			LaunchParachute((mobileitem*)transit->Launcher,world);
		}
		else
			AddTransientItemToDeadList(transit);
	}
}

void	TransObj::LaunchCollapse(	ItemPtr	launcher,
									Coords3D& noncorrectedgrpcoords,
									SWord	groupindex,
									WorldStuff&	worldptr)
{
	MyGroundVector	pos;
	ShapeNum		shapehit;
	UWord			ghdg;
	MinAnimData		*mad = (MinAnimData*) SHAPE.GetGroupItemAnimHdg(launcher,shapehit,groupindex,&pos,ghdg);
	UWord			animoffset = launcher->Anim.Offset(mad);//((UByteP)mad) - ((UByteP)&launcher->Anim);

	if (mad)
	{
		mad->IsInvisible = 1;//Turn off the original bridge element...

		TransientItem*	newitem;
		newitem = SimplifiedSpriteLaunch(	launcher,
											shapehit,
											1000,
											MOBILE_COLLAPSE);
		
		if (newitem)
		{
			newitem->World = noncorrectedgrpcoords;
			newitem->TransRandom = animoffset & 0x0FFF;
			newitem->hdg = (Angles) ghdg;

			SWord	roll,pitch;
			UWord	rp = 0;

			roll = Math_Lib.rnd();
			pitch = Math_Lib.rnd();

			// top 4 bits are for pitch and roll variations...
			if (roll < 0)
				rp = 2;			//slow
			else
			{
				//+ve
				if (roll > 16384)
					rp = 0;			//slow
			}

			rp <<= 2;

			if (pitch < 0)
			{
				rp |= 2;			//slow
			}
			else
			{
				rp |= 0;			//slow
			}

			newitem->TransRandom |= (rp << 12);

			MinAnimData*	el_mad = (MinAnimData*) newitem->Anim;
			el_mad->itemstate = DEAD;

			AddTransientItemToWorld(newitem, worldptr);
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetGroundLevel
//Author		Robert Slater
//Date			Wed 14 Apr 1999
//
//Description	Used for transient items
//
//				... with a max height test optimisation
//				Added repeat location optimisation.						//JIM 23/04/99
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
static int lastsector=0;
static int lastheight=0;
SLong	TransObj::GetGroundLevel(ItemBase*	itm)
{
	SLong	height = 0;	//HIGHESTGROUND;
//DeadCode DAW 01Jul99 	int newsect=0;
//DeadCode DAW 01Jul99 	//landscape block size = 512*256 cm= 128Kcm= 1.3km
//DeadCode DAW 01Jul99 	int sectx=itm->World.X>>17;
//DeadCode DAW 01Jul99 	int sectz=itm->World.Z&0xfffe0000;
//DeadCode DAW 01Jul99 	newsect=sectx+sectz;
//DeadCode DAW 01Jul99 	if (newsect==lastsector && lastheight<itm->World.Y + METRES500)
//DeadCode DAW 01Jul99 	{
//DeadCode DAW 01Jul99 //		return lastheight;
//DeadCode DAW 01Jul99 	}
	if (itm->World.Y < HIGHESTGROUND)
		height = Land_Scape.GetGroundLevel(itm->World);
//DEADCODE DAW 05/05/99	else
//DEADCODE DAW 05/05/99		height=HIGHESTGROUND;
//DeadCode DAW 01Jul99 	lastsector=newsect;
//DeadCode DAW 01Jul99 	lastheight=height;
	return (height);
}

SLong	TransObj::GetGroundLevel(ItemBase*	itm,UByte&	theArea)
{
	SLong	height = 0;	//HIGHESTGROUND;
//DeadCode DAW 01Jul99 	int newsect=0;
//DeadCode DAW 01Jul99 	//landscape block size = 512*256 cm= 128Kcm= 1.3km
//DeadCode DAW 01Jul99 	int sectx=itm->World.X>>17;
//DeadCode DAW 01Jul99 	int sectz=itm->World.Z&0xfffe0000;
//DeadCode DAW 01Jul99 	newsect=sectx+sectz;
//DeadCode DAW 01Jul99 	if (newsect==lastsector && lastheight<itm->World.Y + METRES500)
//DeadCode DAW 01Jul99 	{
//DeadCode DAW 01Jul99 //		return lastheight;
//DeadCode DAW 01Jul99 	}
	if (itm->World.Y < HIGHESTGROUND)
	{
		height = Land_Scape.GetGroundLevel(itm->World,&theArea);//DAW 04May99
		theArea &= AT_MASK;
	}

//DeadCode DAW 01Jul99 	lastsector=newsect;
//DeadCode DAW 01Jul99 	lastheight=height;
	return (height);
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchAmmoBoxes
//Author		Robert Slater
//Date			Mon 26 Apr 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::LaunchAmmoBoxes(mobileitem* launcher,UByte gindex,Coords3D &hittercoords,SLong strength,WorldStuff& worldptr)
{
	MyGroundVector	pos;
	ShapeNum		shapehit;
	TransientItem*	newitem;
	UWord			realhdg;
	MinAnimData*	mad = (MinAnimData*) SHAPE.GetGroupItemAnimHdg(launcher,shapehit,gindex,&pos,realhdg);
	ShapeDescPtr	sdptr = SHAPESTUFF.GetShapePtr(shapehit);
	SLong			halfboxes = ((sdptr->Size << 4) / 176) / 2;
	SLong			noboxes = halfboxes + Math_Lib.rnd(halfboxes);
	SLong			count;
	SLong			shpsize = sdptr->Size << 4;
	SLong			dx,dz,dist;
	SWord			thehdg;

	// Throw from the direction the weapon came from...
	dx = pos.gx - hittercoords.X;
	dz = pos.gz - hittercoords.Z;

	thehdg = Math_Lib.arctan(dz,dx);
	if (dx > 0)
		thehdg = ANGLES_90Deg - thehdg;
	else
		thehdg = ANGLES_270Deg - thehdg;

	mad->itemstate = DEAD;

	//50m is minimum toss damage...
	if (strength > 0)
	{
		SLong	vely,maxvel,thesize;
		SLong	maxtoss;
		SLong	hdgintercept = SWord(UWord(thehdg) - realhdg);
		SLong	pitchintercept;
		SWord	pitchmag,hdgmag,hpmag;

		dist = Math_Lib.distance3d(dx,dz,0);
		dist -= shpsize;
		if (dist < 0)
			dist = 0;

		hdgintercept <<= 8;
		hdgintercept /= ANGLES_90Deg;
		if (hdgintercept > 256)
		{
			hdgintercept = 0;
			pitchintercept = 256 - hdgintercept;
		}
		else
			pitchintercept = 256 - hdgintercept;

		pitchmag = (pitchintercept * 127)>>8;		//max of 90degree flip in 1 sec ish
		hdgmag = (hdgintercept * 127)>>8;

		hpmag = hdgmag << 8;
		hpmag |= pitchmag;

		maxtoss = 5000 - dist;
		thesize = 1000 - shpsize;

		maxvel = (500 * strength) / 31;	//31 is max strength..
		maxvel *= thesize;
		maxvel /= 1000;

		// 60degree throw max...
		if (maxtoss > 0)
		{
			vely = (maxtoss * maxvel * 6) / 9;
			vely /= 5000;
		}
		else
			vely = 0;

		if (Save_Data.desiredfps > realFrameTime)					//RJS 28May99
			noboxes = 2;

		for (count = 0; count < noboxes; count++)
		{
			newitem = SimplifiedSpriteLaunch(	launcher,
												CLUSTA,					//RJS 26May99
												LIFETIME_DEBRISLNCHR,
												MOBILE_DEBRIS);
			if (newitem)
			{
				newitem->World.X = pos.gx;
				newitem->World.Y = pos.gy;
				newitem->World.Z = pos.gz;

				newitem->TransRandom = Math_Lib.rnd();
				newitem->hdg = (Angles) (thehdg + Math_Lib.rnd(ANGLES_90Deg) - ANGLES_45Deg);
				newitem->vely = vely;
				newitem->velhori = maxvel - vely;

				AddTransientItemToWorld(newitem,worldptr);
			}
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		WithinVisibleRange
//Author		Robert Slater
//Date			Fri 30 Apr 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool	TransObj::WithinVisibleRange(Coords3D&	pos, SLong maxrange)
{
	if (View_Point)												//RJS 05May99
	{
		SLong	deltax = pos.X - View_Point->World.X;
		SLong	deltay = pos.Y - View_Point->World.Y;
		SLong	deltaz = pos.Z - View_Point->World.Z;

		deltax = (deltax<0)?-deltax:deltax;
		deltay = (deltay<0)?-deltay:deltay;
		deltaz = (deltaz<0)?-deltaz:deltaz;

		if (	(deltax < maxrange)
			&&	(deltay < maxrange)
			&&	(deltaz < maxrange)	)
			return TRUE;
	}

	return FALSE;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchBoatSink
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
void	TransObj::LaunchBoatSink(ItemPtr		launcher,
								 Coords3D&		noncorrectedgrpcoords,
								 SWord		groupindex,
								 WorldStuff&	worldptr)
{
	MyGroundVector	pos;
	ShapeNum		shapehit;
	UWord			ghdg;
	MinAnimData		*mad = (MinAnimData*) SHAPE.GetGroupItemAnimHdg(launcher,shapehit,groupindex,&pos,ghdg);
	UWord			animoffset = launcher->Anim.Offset(mad);

	if (mad)
	{
		mad->IsInvisible = 1;

		TransientItem*	newitem;
		newitem = SimplifiedSpriteLaunch(	launcher,
											shapehit,
											1000,
											MOBILE_SINK);
		
		if (newitem)
		{
			newitem->World = noncorrectedgrpcoords;
			newitem->TransRandom = animoffset & 0x0FFF;
			newitem->hdg = (Angles) ghdg;

			SWord	roll,pitch;
			UWord	rp = 0;

			roll = Math_Lib.rnd();
			pitch = Math_Lib.rnd();

			// top 4 bits are for pitch and roll variations...
			if (roll < 0)
			{
				//-ve
				if (roll < -16384)
					rp = 3;			//fast
				else
					rp = 2;			//slow
			}
			else
			{
				//+ve
				if (roll > 16384)
					rp = 1;			//fast
				else
					rp = 0;			//slow

			}

			rp <<= 2;

			if (pitch < 0)
			{
				//-ve
				if (pitch < -16384)
					rp |= 3;			//fast
				else
					rp |= 2;			//slow
			}
			else
			{
				//+ve
				if (pitch > 16384)
					rp |= 1;			//fast
				else
					rp |= 0;			//slow

			}

			newitem->TransRandom |= (rp << 12);

			MinAnimData*	el_mad = (MinAnimData*) newitem->Anim;
			el_mad->itemstate = DEAD;

			AddTransientItemToWorld(newitem, worldptr);
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		KillOldestTrail
//Author		Robert Slater
//Date			Thu 13 May 1999
//
//Description	We only care if the launcher is an ac
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool	TransObj::KillOldestTrail(ItemPtr	itm)
{
	if (itm->Status.size == AIRSTRUCSIZE)
	{
		SLong	index;
		ULong	oldest = 0xFFFFFFFF;
		SLong	killindex = -1;

		for (index=0; index < MaxTrails; index++)
		{
			if (StaticTrailList[index].time < oldest)
			{
				oldest = StaticTrailList[index].time;
				killindex = index;
			}
		}

		if (killindex > -1)
		{
			AddTransientItemToDeadList(StaticTrailList[killindex].item);
			StaticTrailList[killindex].time = 0xFFFFFFFF;
			return TRUE;
		}
	}

	return FALSE;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchFakeDelayedExplosion
//Author		Robert Slater
//Date			Sun 16 May 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::LaunchFakeDelayedExplosion(mobileitem*	launcher, WorldStuff&	worldptr	)
{
	SLong			delay;
	TransientItem*	newitem;

	delay = 150 + Math_Lib.rnd(150);

	newitem = LaunchGuidedMissile(launcher,launcher,
									InvisibleLauncher,delay,MOBILE_DELEXP);

	if (newitem)
	{
		// this means it really will explode...
		newitem->TransRandom = 4;		

		AddTransientItemToWorld(newitem, worldptr);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchCarpetStrike
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
void	TransObj::LaunchCarpetStrike(mobileitem*	launcher, WorldStuff&	worldptr	)
{
	ShapeNum	theShape;											//RJS 17Jun99
	SLong		strikecnt;
	SLong		lifetime;
	if (launcher->shape == BOMB29)									//RJS 17Jun99
	{
		//500lb strike
		theShape = BMB100;
		strikecnt = 16;
		lifetime = 300;
	}
	else
	{
		//1000lb strike
		theShape = BMB500;
		strikecnt = 8;
		lifetime = 150;
	}

	TransientItem*	newitem;
	newitem = LaunchUnguidedMissile(	launcher,				
										theShape,					//RJS 17Jun99
										lifetime,					//RJS 17Jun99
										MOBILE_CARPETBOMB	);

	if (newitem)
	{
		MinAnimData*	mad = (MinAnimData*) newitem->Anim;
		mad->IsInvisible = 1;

		if (launcher->Status.size == TRANSIENTSIZE)
			newitem->Launcher = ((TransientItem*)launcher)->Launcher;

		newitem->TmpLaunchTime = lifetime / strikecnt;	  //means each bomber has dropped 34 bombs
		newitem->TransRandom = newitem->TmpLaunchTime;
		newitem->isArmed = 1;												//RJS 10Jun99

		AddTransientItemToWorld(newitem, worldptr);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		PointBlokes
//Author		Robert Slater
//Date			Tue 1 Jun 1999
//
//Description	Actually sets blokes going.
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::PointBlokes(ItemPtr	launcher, ShapeNum troopshape, Coords3D&	realpos, SLong	maxtroops, Coords3D*	placelist, SLong placecnt)
{
	bool	lowpriority = false;								//RJS 11Jun99
	if (Save_Data.desiredfps > realFrameTime)					//RJS 11Jun99
	{															//RJS 11Jun99
		maxtroops = 1 + (maxtroops>>1);							//RJS 11Jun99
		lowpriority = true;										//RJS 11Jun99
	}															//RJS 11Jun99

	SLong			count;
	TroopAnimData*	adptr;
	Bool			dim;
	SLong			groundheight = Land_Scape.GetGroundLevel(realpos);
	TransientItem*	newitem;
	SLong			randindex;

	if (placecnt && placelist)
		dim = FALSE;
	else
		dim = TRUE;

	for (count = 0; count < maxtroops; count++)
	{
		newitem = SimplifiedSpriteLaunch(launcher,troopshape,LIFETIME_TROOP,MOBILE_TROOP);
		if (newitem)
		{
			adptr = (TroopAnimData*) newitem->Anim;
			adptr->oncourse = FALSE;								//RJS 10Jun99
			adptr->homing = FALSE;									//RJS 10Jun99
			if (!dim)
			{
				randindex = placecnt-Math_Lib.rnd(maxtroops);
				if (randindex < 0)
					randindex = placecnt-1;

				adptr->xpos = placelist[randindex].X;								
				adptr->ypos = placelist[randindex].Y;
				adptr->zpos = placelist[randindex].Z;
//DeadCode RJS 11Jun99 					adptr->oncourse = FALSE;

				// Someone might panic!!!!!... headless chicken code
				if (Math_Lib.rnd()<60000)							//RJS 10Jun99
					adptr->homing = TRUE;							//RJS 10Jun99
			}
//DeadCode RJS 11Jun99 				else
//DeadCode RJS 11Jun99 				{
//DeadCode RJS 11Jun99 					adptr->oncourse = FALSE;
//DeadCode RJS 11Jun99 					adptr->homing = FALSE;
//DeadCode RJS 11Jun99 				}
	
			// 5 metre spread around...
			newitem->World.X = realpos.X + Math_Lib.rnd(1000) - 500;
			newitem->World.Y = groundheight;								
			newitem->World.Z = realpos.Z + Math_Lib.rnd(1000) - 500;

			UWord		randval = Math_Lib.rnd();				//RJS 10Jun99
			newitem->hdg = (Angles) randval;					//RJS 10Jun99
			newitem->vely = 0;
			newitem->velhori = 100 + ((20*randval)>>16);		//RJS 10Jun99
			newitem->TransRandom = 50;

			if (lowpriority)									//RJS 11Jun99
				newitem->TimeOfLaunch -= 3000;	//30 secs older	//RJS 11Jun99

			AddTransientItemToWorld(newitem, *newitem->currworld);
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ReduceBulkStores
//Author		Robert Slater
//Date			Thu 17 Jun 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::ReduceBulkStores(AirStrucPtr	ac, UByteP	aptr)
{
	if (!Save_Data.gamedifficulty[GD_UNLIMITEDARM])
	{
		PolyPitAnimData*	adptr = (PolyPitAnimData*) aptr;
		SLong	loss = adptr->acprevammoleft - adptr->acammoleft;
		if (loss > 0)												//RJS 21Jun99
		{
			SLong		lastknownstation = adptr->lastweapindex;
			if (lastknownstation != 0xFF)
			{
				SLong		count;
				SLong		index;
				LnchrType	currentweapon = (LnchrType) (adptr->weaponlaunchers[lastknownstation].LauncherType & LT_MASK);
				SLong		massGone;
				SLong		stationpass[8];
				SLong		tmpstation = lastknownstation;
				SLong		stationlist[8];
				SLong		stationcnt = 0;
				SLong		tmpstatcnt;

				adptr->acprevammoleft = adptr->acammoleft;

				for (index = 0; index < 8; index++)
				{
					stationpass[index] = 0;
					if ((adptr->weaponlaunchers[index].LauncherType & LT_MASK) == currentweapon)
						stationlist[stationcnt++] = index;
				}

				count = 0;
				if (stationcnt)											//RJS 21Jun99
				{
					while (count < loss)
					{
						for (tmpstatcnt = 0; tmpstatcnt < stationcnt; tmpstatcnt++)
						{
							index = stationlist[tmpstatcnt];
							if (index == tmpstation)	 //already deducted	on 1st pass
								tmpstation = -1;
							else
							{
								if (index > tmpstation)
								{
									stationpass[index]++;
									count++;
									if (count == loss)
										break;
								}
							}
						}
					}

					for (tmpstatcnt = 0; tmpstatcnt < stationcnt; tmpstatcnt++)
					{
						index = stationlist[tmpstatcnt];
						count = stationpass[index];
						if (count)
						{
							//Deduct this amount of stores from this station...

							SHAPE.ReduceLauncherLoad(ac,index,count);
						}
					}
				}
			}
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchReplayWeapon
//Author		Andy McMaster
//Date			Wed 23 Jun 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TransObj::LaunchReplayWeapon(UByteP	armeddata)
{
	ArmedTransient*		at = (ArmedTransient*)armeddata;
	TransientItemPtr	newitem;
	mobileitem*			launcher = (mobileitem*) Persons2::ConvertPtrUID((UniqueID)at->launcher);


 	newitem = SimplifiedSpriteLaunch(	launcher,
										(ShapeNum)at->shape,
										at->lifetime,
										(AutoMoveCodeTypeSelect)at->movecode);
	if (newitem)
	{
		newitem->World.X = at->Pos.X;
		newitem->World.Y = at->Pos.Y;
		newitem->World.Z = at->Pos.Z;

		newitem->hdg=at->hdg;									//AMM 24Jun99
		newitem->pitch=at->pitch;								//AMM 24Jun99

		newitem->velx = at->velx;
		newitem->vely = at->vely;
		newitem->velz = at->velz;
		newitem->velhori = at->velhori;
		newitem->isArmed = 1;
		if (at->strength)
		{
			MissileAnimData*	adptr = (MissileAnimData*)newitem->Anim;
			adptr->hitstrength = at->strength;

			newitem->TransRandom = 50 - at->lifetime;
		}
		else													//AMM 24Jun99
		{														//AMM 24Jun99
			newitem->TransRandom = at->transrandom;				//AMM 24Jun99
			if (at->trailindex)									//AMM 24Jun99
			{													//AMM 24Jun99
				MoveGunAnimData*	adptr = (MoveGunAnimData*)newitem->Anim;//AMM 24Jun99
				adptr->weaponlaunchers[0].hdg = at->trailindex;	//AMM 24Jun99
				adptr->weaponlaunchers[0].pitch = -1;			//AMM 24Jun99
				adptr->weaponlaunchers[0].LauncherType = LT_FUEL;//AMM 24Jun99
			}													//AMM 24Jun99
		}														//AMM 24Jun99

		newitem->Status.deadtime = at->deadtime;

		AddTransientItemToWorld(newitem,*newitem->currworld);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchSnapFlash
//Author		Robert Slater
//Date			Tue 29 Jun 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void TransObj::LaunchSnapFlash(mobileitem* launcher,WorldStuff& worldptr)
{
	TransientItem*	newitem;

	newitem = RelativeSpriteLaunch(launcher,launcher->shape,SmallFlashShape,20,MOBILE_BIGEXP);
	if (newitem)
	{
		if ((launcher->Status.size >= MovingSize) && (launcher->Status.size != TransientSize))
			newitem->Target = launcher;

		_Miles.PlaySample((FileNum) (FIL_SFX_EXPLOSION_OILDRUM1+Math_Lib.rnd(5)), newitem);
		AddTransientItemToWorld(newitem,worldptr);
	}

	LaunchSparkDebris(launcher,worldptr);
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LaunchDirtSpark
//Author		Robert Slater
//Date			Tue 6 Jul 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void TransObj::LaunchDirtSpark(mobileitem* launcher,WorldStuff& worldptr, bool dosound)
{
	TransientItem*	newitem;

	newitem = SimplifiedSpriteLaunch(launcher,RicochetSmokeShape,30,MOBILE_STATIONARY);
	if (newitem)
		AddTransientItemToWorld(newitem,worldptr);

	newitem = SimplifiedSpriteLaunch(launcher,BULGND,170,MOBILE_STATIONARY);
	if (newitem)
	{
		if (dosound)
			_Miles.PlaySample((FileNum)(FIL_SFX_RICOCHET_HARD_SURFACE1+Math_Lib.rnd(4)),newitem);
		AddTransientItemToWorld(newitem, worldptr);
	}
}
