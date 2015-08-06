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
//Filename       aaa.cpp
//System         
//Author         Jim Taylor
//Date           Fri 13 Sep 1996
//Description    Anti aircraft artillary and other artillary
//
//	Basic premise is that each AAA gun can spot and shoot at one enemy a/c
//	or ground object.
//
//	Each AAA item contains a number of aaa guns.
//
//	All the AAA items are in a list.
//
//	There will be 2 lists
//
//	AAASleepList	contains all aaa sites this will be processed at a rate so 
//					that each site is processed once per time skip (1/2 sec?).
//					This processing a quick search for a potential target
//					up to 13 miles (2 000 000cm)away. If there is such a target the site is 
//					added to the live list.
//
//	AAALiveList		contains aaa sites that can see things, or nearly see things
//					i.e. there is a target item within a long range.
//					The live AAA sites are processed each second or 1/2.
//
//
//	How are these lists made up?
//			LiveList:
//					link-list of array of 32 entries per link
//					entry number at top
//					same entry in each array is processed each 3cs
//			Sleep list:
//					same link-list structure, but circularised
//------------------------------------------------------------------------------

#include	"dosdefs.h"
extern	void	CheckE3();
#include	"worldinc.h"
#include	"mymath.h"
#include	"ranges.h"
#include	"myangles.h"
#include	"3dcom.h"
	#define F_COMMON
	#define F_GRAFIX
	#define F_BATTLE
#include	"files.g"
#include	"mytime.h"
#include	"text.h"
#include	"persons2.h"
#include	"transite.h"
#include	"enumbits.m"
#include	"landscap.h"
#include	"flymodel.h"
#include	"miles.h"
#include	"aaa.h"
#include	"ai.h"
#include	"shpinstr.h"
#include	"globrefs.h"
#include	"rchatter.h"
#include "viewsel.h"
#include "winmove.h"
//DeadCode PD 6Nov97 #pragma dump_object_model AircraftAnimData;

//MATHABLE(ANGLES);
//extern	ULong	GR_NAT_FRIEND;
//extern	ULong	GR_NAT_ENEMY;
#pragma  warning(disable:4355)
CON	LiveList::LiveList(WorldStuff* w):
	sleeplist(*this),sleeplistbackup(*this)
#pragma  warning(default:4355)
{
	WorldSearch world(w);
	ItemPtr i;
	while ((i=world.Next())!=NULL)
	{
		DOLAUNCHER_PTR d=(DOLAUNCHER_PTR)SHAPE.GetLauncherPos(i->shape,0);
		if ( d && (d->lnchrtype & LT_MASK) == LT_MOVEGUN )
			sleeplist+=i;
	}
//	sleeplist.AddItemEvents(EventRec::eventbase);
}

DES		AaaMainList::~AaaMainList()
{
	AaaSubList	*tmp,*tmp2;
	tmp=aaalist;
	do
	{
		tmp2=tmp->next;
		delete tmp;
		tmp=tmp2;
	}
	while (tmp!=aaalist);
//DeadCode JIM 06Oct96 	delete tmp;
}


//DEADCODE JIM 17/03/99 void	SleepList::AddItemEvents(EventRec* evlist)
//DEADCODE JIM 17/03/99 {
//DEADCODE JIM 17/03/99 	while (evlist)
//DEADCODE JIM 17/03/99 	{
//DEADCODE JIM 17/03/99 		if (evlist->attitem && (evlist->attitem->Status.size==ITEMSIZE || evlist->attitem->Status.size==MOBILESIZE))
//DEADCODE JIM 17/03/99 			operator+=(*evlist->attitem);
//DEADCODE JIM 17/03/99 		evlist=evlist->eventlink;
//DEADCODE JIM 17/03/99 	}
//DEADCODE JIM 17/03/99 }


void	AaaMainList::operator	+=(ItemPtr i)
{
AaaSubList	*sl=aaalist;
int	index;
	for (index=0;index<SUBLISTSIZE;index++)
		if (sl _[index]==NULL)
		{
			break;
		}
	if (index==SUBLISTSIZE && sl->next!=sl)
	do
	{
		sl=sl->next;
		for (index=0;index<SUBLISTSIZE;index++)
			if (sl _[index]==NULL)
			{
				aaalist=sl;
				break;
			}
	}	while	(sl!=aaalist);
	if (index!=SUBLISTSIZE)
	{
		index=(index+Math_Lib.rnd(SUBLISTSIZE-index));
		while (sl _[index])	index--;
	}
	else
	{
		sl=new AaaSubList;
		sl->next=aaalist->next;
		aaalist->next=sl;
		aaalist=sl;
		index=Math_Lib.rnd(SUBLISTSIZE);
	}
	sl _[index]=i;
}

void	AaaMainList::operator -=(ItemPtr i)
{
AaaSubList	*sl=aaalist;
int	index;
	for (index=0;index<SUBLISTSIZE;index++)
		if (sl _[index]==i)
		{
			break;
		}
	if (index==SUBLISTSIZE && sl->next!=sl)
	do
	{
		sl=sl->next;
		for (index=0;index<SUBLISTSIZE;index++)
			if (sl [0][index]==i)
			{
				aaalist=sl;
				break;
			}
	}	while	(sl!=aaalist);

	if (index!=SUBLISTSIZE)	
	{
		sl [0][index]=NULL;
		if (sl!=sl->next) //only 1 record
		{
			for (index=0;index<SUBLISTSIZE;index++)
				if (sl _[index])
					return;
			//ok.. can delete array record!
			AaaSubList	*s2=sl;
			while (sl->next!=aaalist)
				sl=sl->next;
			sl->next=s2->next;
	 		delete s2;
			aaalist=sl;
		}
	}
}


enum	AaaGunTypes
{
	AAA_HITSTATICS,
	AAA_ANTIAIRCRAFT,
	AAA_ANTITANK,
	AAA_BARAGE,
	AAA_BARAGEGUN
};

struct	AaaParams
{
	AaaGunTypes				guntype;
	Nationality				nat;
	ANGLESInst					minhdg,hdgrange,
							minpitch,pitchrange;
	ANGLESInst					turnpersec;							//JIM 05Dec96
	SLong					minalt,altrange,flatrange;
	SWord					reloadtime;
	UWord					muzzelvel;
	SLong					lifetime;
	ShapeNum				shapenum;
	AutoMoveCodeTypeSelect	movecode;
	FileNum					sfx;								//RJS 22Nov96
	Bool					doinaccel;
};

#define	SPECIALLIFE	0x70000000

AaaParams	aaaguntypelist[]=
{
	//	guntype,nat
	//	minhdg,hdgrange,					minpitch,pitchrange,		turnpercs	
	//	minalt,altrange,					flatrange					reloadtime	
	//	muzzvel,lifetime,					shape,movecode				soundfx
	//	doinaccel

	{	AAA_ANTIAIRCRAFT,NAT_RED,	//red large bore flak
		ANGLES_0Deg,ANGLES_FIDDLEMAX,		ANGLES_30Deg,ANGLES_60Deg,	ANGLES_30Deg,//MS 11Dec96
		METRES1000,FT_25000,				METRES5000,		100*10,
		5*1000,SPECIALLIFE,BFLAK,MOBILE_PUFFTRAVEL,			FIL_NULL,
		FALSE
		},		//life of -1 means use est life

	{	AAA_ANTIAIRCRAFT,NAT_RED,	//red large bore flak (short range)
		ANGLES_0Deg,ANGLES_FIDDLEMAX,		ANGLES_30Deg,ANGLES_60Deg,	ANGLES_30Deg,//MS 11Dec96
		METRES1000,FT_12000,				METRES5000,		100*10,
		5*1000,SPECIALLIFE,WFLAK,MOBILE_PUFFTRAVEL,			FIL_NULL,
		FALSE
		},		//life of -1 means use est life

	{	AAA_ANTIAIRCRAFT,NAT_BLUE,	//blue large bore flak
		ANGLES_0Deg,ANGLES_FIDDLEMAX,		ANGLES_30Deg,ANGLES_60Deg,	ANGLES_30Deg,//MS 11Dec96
		METRES1000,METRES3000,				METRES5000,		100*10,
		5*1000,SPECIALLIFE,BFLAK,MOBILE_PUFFTRAVEL,			FIL_NULL,
		FALSE
		},		//life of -1 means use est life

	{	AAA_ANTIAIRCRAFT,NAT_RED,	//red small bore flak 12mil
		ANGLES_0Deg,ANGLES_FIDDLEMAX,		ANGLES_0Deg,ANGLES_80Deg,	ANGLES_170Deg,//JIM 05Dec96
		FT_100,FT_4000,				FT_5000,		50,
		6000,100*4,DSPARK,MOBILE_BULLET,					FIL_SFX_GUN_RIFLE_SHOT1,
//TempCode MS 30Mar99 		5*1000,100*4,DSPARK,MOBILE_BULLET,								FIL_SFX_GUN_RIFLE_SHOT1,
		FALSE
		},

	{	AAA_ANTIAIRCRAFT,NAT_RED,	//red small bore flak 37mil
		ANGLES_0Deg,ANGLES_FIDDLEMAX,		ANGLES_0Deg,ANGLES_80Deg,	ANGLES_170Deg,//JIM 05Dec96
		FT_100,FT_4300,				FT_5000,		50,
		6000,100*4,FLMONN,MOBILE_BULLET,					FIL_SFX_MIG_CANNON_LOOP1,
//TempCode MS 30Mar99 		5*1000,100*4,DSPARK,MOBILE_BULLET,								FIL_SFX_GUN_RIFLE_SHOT1,
		FALSE
		},

	{	AAA_ANTIAIRCRAFT,NAT_BLUE,	//blue small bore flak
		ANGLES_0Deg,ANGLES_FIDDLEMAX,		ANGLES_0Deg,ANGLES_60Deg,	ANGLES_170Deg,//JIM 05Dec96
		0,FT_12000,				METRES2000,		50,
		6000,100*2,DSPARK,MOBILE_BULLET,					FIL_SFX_GUN_RIFLE_SHOT1,
		FALSE
		},

	{	AAA_BARAGE,NAT_RED,			//ground effect (non fatal)	//RJS 31Mar99
		ANGLES_0Deg,ANGLES_FIDDLEMAX,		ANGLES_330Deg,ANGLES_120Deg,	ANGLES_10Deg,	//RJS 05Oct98
//TempCode MS 02Sep99 		-METRES100,METRES200,				METRES500,		500,				//Shoot every 5secs
		-METRES100,METRES200,				METRES1000,		500,				//Shoot every 5secs
		800,SPECIALLIFE,DSPARK,MOBILE_BULLET,									FIL_SFX_GUN_TANK2,//RJS 05Oct98
		FALSE																					//RJS 05Oct98
		},

	{	AAA_BARAGEGUN,NAT_RED,		//red ground gun (non fatal)																//RJS 09Dec98
		ANGLES_0Deg,ANGLES_FIDDLEMAX,		ANGLES_300Deg,ANGLES_160Deg,	ANGLES_10Deg,
		-METRES500,METRES800,				160000,		500,
		800,SPECIALLIFE,DSPARK,MOBILE_BOMBDROP,								FIL_SFX_GUN_TANK2,
		FALSE
		},

	{	AAA_BARAGEGUN,NAT_BLUE,		//blue ground gun (non fatal)																//RJS 09Dec98
		ANGLES_0Deg,ANGLES_FIDDLEMAX,		ANGLES_300Deg,ANGLES_160Deg,	ANGLES_10Deg,
		-METRES500,METRES800,				160000,		500,
		5*800,SPECIALLIFE,DSPARK,MOBILE_BOMBDROP,								FIL_SFX_GUN_TANK2,
		FALSE
		},

//DeadCode RJS 08Apr99 	{	AAA_ANTIAIRCRAFT,NAT_RED,	//rear gunners red
//DeadCode RJS 08Apr99 		ANGLES_90Deg,ANGLES_180Deg,		ANGLES_350Deg,ANGLES_50Deg,			ANGLES_150Deg,//JIM 05Dec96
//DeadCode RJS 08Apr99 		-METRES50,METRES300,				METRES300,		50,
//DeadCode RJS 08Apr99 		5*1200,100*1,BULLET,MOBILE_BULLET,									FIL_SFX_GUN_TANK1,
//DeadCode RJS 08Apr99 		TRUE
//DeadCode RJS 08Apr99 		},
//DeadCode RJS 08Apr99 
//DeadCode RJS 08Apr99 	{	AAA_ANTIAIRCRAFT,NAT_BLUE,	//rear gunners blue
//DeadCode RJS 08Apr99 		ANGLES_90Deg,ANGLES_180Deg,		ANGLES_350Deg,ANGLES_50Deg,			ANGLES_150Deg,//JIM 05Dec96
//DeadCode RJS 08Apr99 		-METRES50,METRES300,				METRES300,		50,
//DeadCode RJS 08Apr99 		5*1200,100*1,BULLET,MOBILE_BULLET,									FIL_SFX_GUN_TANK1,
//DeadCode RJS 08Apr99 		TRUE
//DeadCode RJS 08Apr99 		},

	{	AAA_ANTIAIRCRAFT,NAT_BLUE,	//turret gunners top (forward)
		-ANGLES_90Deg,ANGLES_180Deg,		ANGLES_350Deg,ANGLES_50Deg,			ANGLES_150Deg,
		-METRES50,METRES300,				METRES300,		50,
		5*1200,100*1,BULLET,MOBILE_BULLET,									FIL_SFX_MACHINE_GUN_LOOP2,
		TRUE
		},

	{	AAA_ANTIAIRCRAFT,NAT_BLUE,	//turret gunners bottom (forward)
		-ANGLES_90Deg,ANGLES_180Deg,		ANGLES_300Deg,ANGLES_50Deg,			ANGLES_150Deg,
		-METRES50,METRES300,				METRES300,		50,
		5*1200,100*1,BULLET,MOBILE_BULLET,									FIL_SFX_MACHINE_GUN_LOOP2,
		TRUE
		},

	{	AAA_ANTIAIRCRAFT,NAT_BLUE,	//turret gunners top (rear)
		ANGLES_90Deg,ANGLES_180Deg,		ANGLES_350Deg,ANGLES_50Deg,			ANGLES_150Deg,
		-METRES50,METRES300,				METRES300,		50,
		5*1200,100*1,BULLET,MOBILE_BULLET,									FIL_SFX_MACHINE_GUN_LOOP2,
		TRUE
		},

	{	AAA_ANTIAIRCRAFT,NAT_BLUE,	//turret gunners bottom (rear)
		ANGLES_90Deg,ANGLES_180Deg,		ANGLES_300Deg,ANGLES_50Deg,			ANGLES_150Deg,
		-METRES50,METRES300,				METRES300,		50,
		5*1200,100*1,BULLET,MOBILE_BULLET,									FIL_SFX_MACHINE_GUN_LOOP2,
		TRUE
		}

};

class	TrgListProc
{
public:
	AaaGunTypes type;
	AaaMainList::AaaSubList		*base,*base2;		//base+index--> item ptr.: first weap -> nat
	union
	{
		MobileItemPtr	last;		//last->nextmobile --> last: formationitem nationality
		AaaMainList::AaaSubList* start;
		AirStrucPtr*	aclist;
	};
	int	index;
	Nationality	nat;
	CON TrgListProc(AaaGunTypes t,Nationality n,AaaMainList::AaaSubList *s,AaaMainList::AaaSubList *s2)	{ReStart(t,n,s,s2);}
	void ReStart(AaaGunTypes t,Nationality n,AaaMainList::AaaSubList *s,AaaMainList::AaaSubList *s2);
	ItemPtr	Next();
};

void	TrgListProc::ReStart(AaaGunTypes t,Nationality n,AaaMainList::AaaSubList *s,AaaMainList::AaaSubList *s2)
{
	nat=n;
	index=0;
	type=t;
	switch (t)
	{
	case AAA_HITSTATICS:
		base=start=s;
		base2=s2;
		break;
	case AAA_ANTIAIRCRAFT:
		base2=base=NULL;
		aclist=ArtInt::ACArray;
		index=-1;
		break;
	case AAA_ANTITANK:
	case AAA_BARAGE:
	case AAA_BARAGEGUN:
		base2=base=NULL;
		last=mobileitem::MobileList;
		break;
	}
}

ItemPtr	TrgListProc::Next()
{
ItemPtr retval=NULL;
	switch (type)
	{
	case AAA_HITSTATICS:
		{
			if (index==AaaMainList::SUBLISTSIZE)
			{
				if (base->next==start)
					if (base2)
					{
						start=base=base2;base2=NULL;
					}
					else
						return(NULL);
				index=0;
				base=base->next;
			}

			DOLAUNCHER_PTR dlp;
			while (		base[0][index]==NULL
					||	(	base[0][index]->Status.deadtime!=0
						||	( dlp=(DOLAUNCHER_PTR)SHAPE.GetLauncherPos((base[0][index])->shape,0),
							  dlp	?aaaguntypelist[dlp->lnchrtype-LT_MOVEGUN].nat==nat
									:TRUE
							)
				)		)
	   		{
				index++;
				if (index==AaaMainList::SUBLISTSIZE)
				{
					if (base->next==start)
					{
						if (base2)
						{
							start=base=base2;base2=NULL;
						}
						else
							return(NULL);
					}
					index=0;
					base=base->next;
				}
			}
			retval=base[0][index];
			index++;
		}
		break;
	case AAA_ANTIAIRCRAFT:
		{
			do
				index++;
			while (		index<ArtInt::ACARRAYSIZE 
					&& (	aclist[index]==NULL 
						||	aclist[index]->nationality==nat
					)	);
			if (index<ArtInt::ACARRAYSIZE)
				return aclist[index];
			else
				return NULL;

		}
		break;
	case AAA_ANTITANK:
	case AAA_BARAGE:
	case AAA_BARAGEGUN:
		{
			while (		last
					&&	(	last->nationality==nat
						||	last->Status.deadtime!=0
					)	)	//add extra fix for in formation
				last=last->nextmobile;
			retval=last;
			if (last)
				last=last->nextmobile;
		}
		break;
	}
	return retval;
}

void	SleepList::Event()
{
	if (++aaaind==SUBLISTSIZE)
	{
		aaaind=0;
		aaalist=aaalist->next;
		if (aaalist==blockradio)
			blockradio=NULL;
	}
//do summat
	ItemPtr eye=aaalist[0][aaaind];
	if (eye)
	{
		AaaGunTypes guntype=AAA_ANTIAIRCRAFT;

		Nationality	nat=(Nationality)GR_NAT_ENEMY;
		int			range=METRES10KM;

		DOLAUNCHER_PTR d=(DOLAUNCHER_PTR)SHAPE.GetLauncherPos(eye->shape,0);
		if (d)
		{
			AaaParams* a=&aaaguntypelist
							[	d->lnchrtype-LT_MOVEGUN	];
			guntype=a->guntype;
			nat=a->nat;
			range=a->flatrange+METRES2000;
//DEADCODE DAW 26/05/99 		}
			TrgListProc	tlp(guntype,nat,aaalist,Live_List.aaalist);
		//for all ac/gmobiles/aaasites - depending on type of gun
			//if on enemy side - depending on type
				//if not in formation (a/c only - if in form then leader only to test)
			ItemPtr trg=tlp.Next();
			while (trg)
			{
				Coords3D* trgpos=_DPlay.GetGoodACPosition(trg);

					//if quick range < 20KM add to livelist and exit
				if (	Math_Lib.AbsSign(trgpos->X-eye->World.X)<range
					&&	Math_Lib.AbsSign(trgpos->Z-eye->World.Z)<range					)
						{
							//Has altitude been fixed yet?
							if (eye->World.Y == 0)			//RJS 10Dec98
								eye->World.Y = Land_Scape.GetGroundLevel(eye->World);//RJS 10Dec98

							if (eye->Anim==NULL)
								SHAPE.SetAnimData(*eye);
							operator-=(eye);
							Live_List+=eye;
							Coords3D		weapoff;
							int				weapnum=0;
							UWord			mvel,mdelay,mburst;						//RDH 31Jul98
							bool	targetting=false;
							WeapAnimData*	weapanim=SHAPE.GetWeaponLauncher(eye,0,weapoff.X,weapoff.Y,weapoff.Z,mvel,mdelay,mburst,LT_MOVEGUN);//RDH 31Jul98
							if (weapanim)											//RJS 24Jun99
								weapanim->LaunchTime=0;								//RJS 24Jun99

//DeadCode DAW 25Jun99 							weapanim->LaunchTime=0;
							if (d->lnchrtype==LT_RPUFF)
								if (trg->Status.size==AIRSTRUCSIZE)
									if (!blockradio)
										if (AirStrucPtr(*trg)->IsUsingPilotedAcLog() && trg->World.Y>METRES5000)
										{
											TargetIndexes	trgindex;
											int msgalt=trg->World.Y;
											if (msgalt<eye->World.Y+a->minalt+a->altrange)
											{
												MESSAGE_STRUC	tmpmsg(SCRIPT_FLAKREPORT, MSG_FLAKREPORT, NULL, eye, Persons2::PlayerGhostAC,trgindex.SetHeight(msgalt));
												_Miles.SequenceAudible(FIL_MUSIC_FLAK);
												_Radio.TriggerMsg(tmpmsg.SetVoice(VOICE_DENTIST));
												blockradio=aaalist;
											}
										}
							return;/////
						}
				trg=tlp.Next();
			}
		}														//RJS 26May99
//remove from live list if get here (nothing visible)
//DeadCode JIM 15Nov96 	Live_List-=eye;
	}
}

inline void	WarnSmallBore(MobileItem*weapitem,AirStruc*trg)
{
	AirStrucPtr resp=trg->fly.leadflight;
	if (!resp)
		resp=trg->FindBuddy();
	if (resp)
	{
		if (weapitem->SGT)
			_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_FLAKFIRING, MSG_FLAKFIRING, resp, Persons2::ConvertPtrUID(weapitem->SGT), trg));
		else
			_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_FLAKFIRING, MSG_FLAKFIRING, resp, weapitem, trg));
	}

}


void	LiveList::Event()
{
//DeadCode JIM 06Jan97 	CheckE3();
	if (++aaaind==SUBLISTSIZE)
	{
		aaaind=0;
		aaalist=aaalist->next;
		sleeplist.Event();
		sleeplist.Event();
		sleeplist.Event();
	}
//this *will* be fun...
//do summat
//for each mobile launcher in item
	if (aaalist[0][aaaind])
	{
//DeadCode JIM 06Jan97 	CheckE3();
		ItemPtr		weapitem=aaalist[0][aaaind];
		if (weapitem->World.Y==0)
			weapitem->World.Y=Land_Scape.GetGroundLevel(weapitem);
		Coords3D		weapoff;
		int				weapnum=0;
		UWord			mvel,mdelay,mburst;						//RDH 31Jul98
		bool	targetting=false;
		WeapAnimData*	weapanim=SHAPE.GetWeaponLauncher(weapitem,weapnum,weapoff.X,weapoff.Y,weapoff.Z,mvel,mdelay,mburst,LT_MOVEGUN);//RDH 31Jul98
//DeadCode JIM 06Jan97 	CheckE3();
		if (weapanim)
		{
			if (!weapanim->target)
				if (weapanim->LaunchTime)
				{
					weapnum=weapanim->LaunchTime;
					weapanim=SHAPE.GetWeaponLauncher(weapitem,weapnum,weapoff.X,weapoff.Y,weapoff.Z,mvel,mdelay,mburst,LT_MOVEGUN);//RDH 31Jul98
					if (!weapanim)
					{
						weapnum=0;
						weapanim=SHAPE.GetWeaponLauncher(weapitem,weapnum,weapoff.X,weapoff.Y,weapoff.Z,mvel,mdelay,mburst,LT_MOVEGUN);//RDH 31Jul98
						weapanim->LaunchTime=0;
						targetting=true;
					}
				}

			AaaParams* 		aaaparams=&aaaguntypelist[weapanim->LauncherType-LT_MOVEGUN];
			TrgListProc		targlist(aaaparams->guntype,aaaparams->nat,sleeplist.aaalist,aaalist);	//assume all a/c use same detect routines
			Bool nothingthere=TRUE;

			if (	aaaparams->doinaccel 
				||	MobileItem::currworld->vp==NULL 
				|| !MobileItem::currworld->vp->Accel()
				)
			while (weapanim!=NULL)
			{
			//if known target 
				if (weapanim->target)
				{
					targetting=true;
					nothingthere=FALSE;
					{int t=weapanim->LaunchTime	-Timer_Code.FRAMETIME*SUBLISTSIZE;
					if (t>0)
						weapanim->LaunchTime=t;
					else
						weapanim->LaunchTime=0;
					}
					ItemPtr	trg=*MobileItem::currworld->ConvertPtrUID((UniqueID)weapanim->target);
					MobileItemPtr tm;		//used as temp mobile for launcher or target as required
					if (trg)
					{
						if (trg->Status.deadtime)
							weapanim->target=UID_Null;

						SLong	Range;
						ANGLES	HdgIntercept,PitchIntercept;
						if (aaaparams->guntype < AAA_BARAGE)
						{
							// continue to track
							// get intercept
							if (trg->Status.size>=MOBILESIZE)
							{
								tm=*trg;
								int	rnd=Math_Lib.rnd();
								int	vx=0;//tm->velx*(6+rnd&31);
								int	vy=0;//tm->vely*(6+(rnd>>5)&31);
								int	vz=0;//tm->velz*(6+(rnd>>10)&31);
//DeadCode DAW 24Jun99 								int	vx=tm->velx*(6+rnd&31);
//DeadCode DAW 24Jun99 								int	vy=tm->vely*(6+(rnd>>5)&31);
//DeadCode DAW 24Jun99 								int	vz=tm->velz*(6+(rnd>>10)&31);
								Math_Lib.HighIntercept(	trg->World.X+vx-weapoff.X,
														trg->World.Y+vy-weapoff.Y,
														trg->World.Z+vz-weapoff.Z,
														Range,HdgIntercept,PitchIntercept);
								if (	weapitem->Status.size!=AIRSTRUCSIZE
									&& trg->Status.size==AIRSTRUCSIZE
									&&	((AirStrucPtr)*trg)->movecode==AUTO_COMBAT
									&&	((AirStrucPtr)*trg)->ai.unfriendly!=NULL
									)
									weapanim->target=UID_Null;
							}
							else
							{
								Coords3D	t;
								SHAPE.GetLiveElementPos(0,trg,t.X,t.Y,t.Z);
								Math_Lib.HighIntercept(	trg->World.X+t.X-weapoff.X,trg->World.Y+t.Y-weapoff.Y,trg->World.Z+t.Z-weapoff.Z,
														Range,HdgIntercept,PitchIntercept);
							}

							//split muzzel vel into vx,xz,vh,vy
							SWord	muzzelvel=aaaparams->muzzelvel;
							SLong	eta=(Range*10)/muzzelvel;
							if (	eta<aaaparams->lifetime+SECS100
								&& 	(trg->World.Y-weapitem->World.Y > aaaparams->minalt-METRES100)
								&&	(trg->World.Y-weapitem->World.Y < aaaparams->minalt+aaaparams->altrange+METRES100)
								&&	(
										(	weapitem->Status.size>MOBILESIZE
										&&	(UWord)(HdgIntercept+ANGLES_10Deg -(tm=*weapitem)->hdg - aaaparams->minhdg)<(ULong)(ANGLES)aaaparams->hdgrange+ANGLES_20Deg
										&&	(UWord)(PitchIntercept+ANGLES_10Deg -tm->pitch - aaaparams->minpitch)<(ULong)(ANGLES)aaaparams->pitchrange+ANGLES_20Deg
										)
									||	(	weapitem->Status.size<=MOBILESIZE
										&&	(UWord)(HdgIntercept +ANGLES_10Deg - aaaparams->minhdg)<(ULong)(ANGLES)aaaparams->hdgrange+ANGLES_20Deg
										&&	(UWord)(PitchIntercept +ANGLES_10Deg - aaaparams->minpitch)<(ULong)(ANGLES)aaaparams->pitchrange+ANGLES_20Deg
										)
									)

								)
							{
								SWord	sp,cp;
								Math_Lib.high_sin_cos(PitchIntercept,sp,cp);
								SWord	sh,ch;
								Math_Lib.high_sin_cos(HdgIntercept,sh,ch);

								SWord	vy=(sp*muzzelvel)>>ANGLES_SHIFT,
										vh=(cp*muzzelvel)>>ANGLES_SHIFT,
										vx=(sh*vh)>>ANGLES_SHIFT,
										vz=(ch*vh)>>ANGLES_SHIFT;
					
								//range in cm
								//vel in mm/cs
								//eta in cs

								//correction for target movement - Make bullets faster!!!
								if (trg->Status.size>=MOBILESIZE)
								{
									MobileItemPtr	trg2=*trg;
									vx+=trg2->velx;
									vy+=trg2->vely;
									vz+=trg2->velz;
									HdgIntercept=Math_Lib.HighArcTan(vx,vz);
									Math_Lib.high_sin_cos(HdgIntercept,sh,ch);
									if (Math_Lib.AbsSign(vx)>Math_Lib.AbsSign(vz))
										vh=(vx<<ANGLES_SHIFT)/sh;
									else
										vh=(vz<<ANGLES_SHIFT)/ch;
								}
								//want ave vel due gravity
								//avevel = eta * g /2
								//avevel in mm/cs
								// eta in cs
								//g=9.5 m/s/s = 9.5 cm/cs/s
								//gives vel in cm /s
								//*10 gives mm/s
								// /10 gives mm/cs
								//g/2 is 0.475		=31129/65536
								//that is the correct value for gravity. 
								//I am getting 0.2 m/s/.03s
								//=6.6 m/s/s
								//=g/2 = 0.33 = 21845/65536
								vy+=MULSHSIN(eta,21845,16);
								PitchIntercept=Math_Lib.HighArcTan(vy,vh);
								Math_Lib.high_sin_cos(PitchIntercept,sp,cp);
								if (Math_Lib.AbsSign(vh)>Math_Lib.AbsSign(vy))
									muzzelvel=(vh<<ANGLES_SHIFT)/cp;
								else
									muzzelvel=(vy<<ANGLES_SHIFT)/sp;

								if (weapitem->Status.size>=MOBILESIZE)
								{
									tm=*weapitem;
									PitchIntercept-=tm->pitch;
									HdgIntercept-=tm->hdg;
								}

								ANGLES	tang;					//RJS 09Dec98
								int	turnper;					//RJS 09Dec98
								
								turnper=(ANGLES)aaaparams->turnpersec*(Timer_Code.FRAMETIME*SUBLISTSIZE*256/100)>>8;//RJS 09Dec98
								tang=(Angles)turnper;			//RJS 09Dec98
								if (tang>ANGLES_90Deg)			//RJS 09Dec98
									turnper=ANGLES_90Deg;		//RJS 09Dec98

								if (Math_Lib.AbsSign(HdgIntercept-(Angles)weapanim->hdg) > turnper)
								{
									weapanim->hdg+=(Angles)Math_Lib.UseSign(turnper,Math_Lib.GetSign(HdgIntercept-(Angles)weapanim->hdg));

									if (Math_Lib.AbsSign(PitchIntercept-(Angles)weapanim->pitch) > turnper)
										weapanim->pitch+=(Angles)Math_Lib.UseSign(turnper,Math_Lib.GetSign(PitchIntercept-(Angles)weapanim->pitch));
									else
										weapanim->pitch=PitchIntercept;
								}
								else
								{
									weapanim->hdg=HdgIntercept;

									if (Math_Lib.AbsSign(PitchIntercept-(Angles)weapanim->pitch) > turnper)
										weapanim->pitch+=(Angles)Math_Lib.UseSign(turnper,Math_Lib.GetSign(PitchIntercept-(Angles)weapanim->pitch));
									else
									{
										weapanim->pitch=PitchIntercept;
										if (	eta<aaaparams->lifetime-30
											&& 	(trg->World.Y-weapitem->World.Y>aaaparams->minalt)
											&&	(trg->World.Y-weapitem->World.Y<aaaparams->minalt+aaaparams->altrange)
											&&	(UWord)(HdgIntercept - aaaparams->minhdg)<(ANGLES)aaaparams->hdgrange
											&&	(UWord)(PitchIntercept - aaaparams->minpitch)<(ANGLES)aaaparams->pitchrange
											&&  weapanim->LaunchTime==0
											)
										{
						 					//weapon pointed the right way... lets fire!!!!
											//use:
											//	weapoff for position
											//	hdg,pitch from weapanim+weapitem if mobile
											//	if (weapitem.Status.size>=MOBILESIZE)
											//	
											//	muzzelvel local
											//	shapenum, movecode from aaaparams
											//	lifetime from aaaparams. If SPECIALLIFE use eta
											//	
											if (weapitem->Status.size>=MOBILESIZE)
											{
												tm=*weapitem;
												PitchIntercept+=tm->pitch;
												HdgIntercept+=tm->hdg;
											}
											if (aaaparams->lifetime!=SPECIALLIFE)
												eta=aaaparams->lifetime;

											if (trg->Status.size==AIRSTRUCSIZE && weapitem->Status.size==FORMATIONSIZE) //JIM 12/04/99
												WarnSmallBore(*weapitem,*trg);											//JIM 12/04/99

											//Hideous Jim weapon stuff...//RJS 09Dec98
											// Barrage bit moved...//RJS 09Dec98
											_Miles.PlaySample(aaaparams->sfx,weapitem);//RJS 22Nov96
											if (weapitem->Status.size == AIRSTRUCSIZE)//RJS 09Jul99
											{
												//Launch a bullet every 10th of a second
												((AirStrucPtr)weapitem)->weap.currentbullet = NULL;
												SLong	nobullets = aaaparams->reloadtime / 10;

												//Clone gun could potentially be vaped by KillOldest
												Trans_Obj.LaunchSuperLauncher
												(
													weapitem,
													aaaparams->shapenum,
													eta,
													aaaparams->movecode,
													weapoff,
													HdgIntercept,
													PitchIntercept,
													vx,vy,vz,vh,muzzelvel,aaaparams->nat,
													weapnum,				//leftgun
													weapnum,				//rightgun
													10,
													nobullets,
													weapanim->LauncherType,
													*mobileitem::currworld
												);
											}
											else
											{
												//This could potentially be vaped by KillOldest
												Trans_Obj.LaunchUnguidedMissile
												(	weapitem,
													aaaparams->shapenum,
													eta,
													aaaparams->movecode,
													weapoff,
													HdgIntercept,
													PitchIntercept,
													vx,vy,vz,vh,muzzelvel,aaaparams->nat	);
											}

											weapanim->LaunchTime=aaaparams->reloadtime;
										}

									}
								}
							}
							else
								weapanim->target=UID_Null;
						}
						else
						{
							if (weapanim->LaunchTime == 0)
							{
								if (aaaparams->guntype == AAA_BARAGE)
								{
									// Around target...
									Trans_Obj.LaunchBarage(	(mobileitem*)trg,
															aaaparams->reloadtime );

									// Around launcher...
									Trans_Obj.LaunchBarage(	(mobileitem*)weapitem,
															aaaparams->reloadtime );
								}
								else
								{
									SLong	nobullets = 1 + Math_Lib.rnd(5);

									if (trg->Status.size>=MOBILESIZE)
									{
										tm=*trg;
										int	rnd=Math_Lib.rnd();
										int	vx=tm->velx*(6+rnd&31);
										int	vy=tm->vely*(6+(rnd>>5)&31);
										int	vz=tm->velz*(6+(rnd>>10)&31);
										Math_Lib.HighIntercept(	trg->World.X+vx-weapoff.X,
																trg->World.Y+vy-weapoff.Y,
																trg->World.Z+vz-weapoff.Z,
																Range,HdgIntercept,PitchIntercept);
										if (	weapitem->Status.size!=AIRSTRUCSIZE
											&& trg->Status.size==AIRSTRUCSIZE
											&&	((AirStrucPtr)*trg)->movecode==AUTO_COMBAT
											&&	((AirStrucPtr)*trg)->ai.unfriendly!=NULL
											)
											weapanim->target=UID_Null;
									}
									else
									{
										Coords3D	t;
										SHAPE.GetLiveElementPos(0,trg,t.X,t.Y,t.Z);
										Math_Lib.HighIntercept(	trg->World.X+t.X-weapoff.X,trg->World.Y+t.Y-weapoff.Y,trg->World.Z+t.Z-weapoff.Z,
																Range,HdgIntercept,PitchIntercept);
									}

									//split muzzel vel into vx,xz,vh,vy
									SWord	muzzelvel=aaaparams->muzzelvel;
									SLong	eta=(Range*10)/muzzelvel;
									if (	eta<aaaparams->lifetime+SECS100
										&& 	(trg->World.Y-weapitem->World.Y > aaaparams->minalt-METRES100)
										&&	(trg->World.Y-weapitem->World.Y < aaaparams->minalt+aaaparams->altrange+METRES100)
										&&	(
												(	weapitem->Status.size>MOBILESIZE
												&&	(UWord)(HdgIntercept+ANGLES_10Deg -(tm=*weapitem)->hdg - aaaparams->minhdg)<(ULong)(ANGLES)aaaparams->hdgrange+ANGLES_20Deg
												&&	(UWord)(PitchIntercept+ANGLES_10Deg -tm->pitch - aaaparams->minpitch)<(ULong)(ANGLES)aaaparams->pitchrange+ANGLES_20Deg
												)
											||	(	weapitem->Status.size<=MOBILESIZE
												&&	(UWord)(HdgIntercept +ANGLES_10Deg - aaaparams->minhdg)<(ULong)(ANGLES)aaaparams->hdgrange+ANGLES_20Deg
												&&	(UWord)(PitchIntercept +ANGLES_10Deg - aaaparams->minpitch)<(ULong)(ANGLES)aaaparams->pitchrange+ANGLES_20Deg
												)
											)

										)
									{
										SWord	sp,cp;
										Math_Lib.high_sin_cos(PitchIntercept,sp,cp);
										SWord	sh,ch;
										Math_Lib.high_sin_cos(HdgIntercept,sh,ch);

										SWord	vy=(sp*muzzelvel)>>ANGLES_SHIFT,
												vh=(cp*muzzelvel)>>ANGLES_SHIFT,
												vx=(sh*vh)>>ANGLES_SHIFT,
												vz=(ch*vh)>>ANGLES_SHIFT;
							
										//range in cm
										//vel in mm/cs
										//eta in cs

										//correction for target movement
										if (trg->Status.size>=MOBILESIZE)
										{
											MobileItemPtr	trg2=*trg;
											vx+=trg2->velx;
											vy+=trg2->vely;
											vz+=trg2->velz;
											HdgIntercept=Math_Lib.HighArcTan(vx,vz);
											Math_Lib.high_sin_cos(HdgIntercept,sh,ch);
											if (Math_Lib.AbsSign(vx)>Math_Lib.AbsSign(vz))
												vh=(vx<<ANGLES_SHIFT)/sh;
											else
												vh=(vz<<ANGLES_SHIFT)/ch;
										}
										//want ave vel due gravity
										//avevel = eta * g /2
										//avevel in mm/cs
										// eta in cs
										//g=9.5 m/s/s = 9.5 cm/cs/s
										//gives vel in cm /s
										//*10 gives mm/s
										// /10 gives mm/cs
										//g/2 is 0.475		=31129/65536
										//that is the correct value for gravity. 
										//I am getting 0.2 m/s/.03s
										//=6.6 m/s/s
										//=g/2 = 0.33 = 21845/65536
										vy+=MULSHSIN(eta,21845,16);
										PitchIntercept=Math_Lib.HighArcTan(vy,vh);
										Math_Lib.high_sin_cos(PitchIntercept,sp,cp);
										if (Math_Lib.AbsSign(vh)>Math_Lib.AbsSign(vy))
											muzzelvel=(vh<<ANGLES_SHIFT)/cp;
										else
											muzzelvel=(vy<<ANGLES_SHIFT)/sp;

										if (weapitem->Status.size>=MOBILESIZE)
										{
											tm=*weapitem;
											PitchIntercept-=tm->pitch;
											HdgIntercept-=tm->hdg;
										}

										ANGLES	tang;					//RJS 09Dec98
										int	turnper;					//RJS 09Dec98
										
										turnper=(ANGLES)aaaparams->turnpersec*(Timer_Code.FRAMETIME*SUBLISTSIZE*256/100)>>8;//RJS 09Dec98
										tang=(Angles)turnper;			//RJS 09Dec98
										if (tang>ANGLES_90Deg)			//RJS 09Dec98
											turnper=ANGLES_90Deg;		//RJS 09Dec98

										if (Math_Lib.AbsSign(HdgIntercept-(Angles)weapanim->hdg) > turnper)
										{
											weapanim->hdg+=(Angles)Math_Lib.UseSign(turnper,Math_Lib.GetSign(HdgIntercept-(Angles)weapanim->hdg));

											if (Math_Lib.AbsSign(PitchIntercept-(Angles)weapanim->pitch) > turnper)
												weapanim->pitch+=(Angles)Math_Lib.UseSign(turnper,Math_Lib.GetSign(PitchIntercept-(Angles)weapanim->pitch));
											else
												weapanim->pitch=PitchIntercept;
										}
										else
										{
											weapanim->hdg=HdgIntercept;

											if (Math_Lib.AbsSign(PitchIntercept-(Angles)weapanim->pitch) > turnper)
												weapanim->pitch+=(Angles)Math_Lib.UseSign(turnper,Math_Lib.GetSign(PitchIntercept-(Angles)weapanim->pitch));
											else
											{
												weapanim->pitch=PitchIntercept;
												if (	eta<aaaparams->lifetime-30
													&& 	(trg->World.Y-weapitem->World.Y>aaaparams->minalt)
													&&	(trg->World.Y-weapitem->World.Y<aaaparams->minalt+aaaparams->altrange)
													&&	(UWord)(HdgIntercept - aaaparams->minhdg)<(ANGLES)aaaparams->hdgrange
													&&	(UWord)(PitchIntercept - aaaparams->minpitch)<(ANGLES)aaaparams->pitchrange
													)
												{
													//	
													if (weapitem->Status.size>=MOBILESIZE)
													{
														tm=*weapitem;
														PitchIntercept+=tm->pitch;
														HdgIntercept+=tm->hdg;
													}
													if (aaaparams->lifetime!=SPECIALLIFE)
														eta=aaaparams->lifetime;

													_Miles.PlayOnce(aaaparams->sfx,weapitem);//RJS 07Dec98
													Trans_Obj.LaunchSuperLauncher
													(
														weapitem,
														DSPARK,
														eta,
														MOBILE_GANDF,
														weapitem->World,
														HdgIntercept,
														PitchIntercept,
														vx,vy,vz,vh,muzzelvel,aaaparams->nat,
														0,0,
														15,
														nobullets,
														LT_REDGUNBARRAGE,
														*mobileitem::currworld
													);
												}
											}
										}
									}
								}

								weapanim->LaunchTime=(aaaparams->reloadtime>>1) + Math_Lib.rnd(aaaparams->reloadtime>>1);
							}
						}
					}
					else
						weapanim->target=UID_Null;
				}
				else
				{
				//	find target - starting where last launcher left off
					ItemPtr	trg=targlist.Next();
					while (trg)
					{
//DEADCODE DAW 01/06/99 						if (!!(weapitem->World.Y<Land_Scape.CloudAlt())==!!(trg->World.Y<Land_Scape.CloudAlt()))
						if (	weapitem->Status.size==AIRSTRUCSIZE
							|| trg->Status.size!=AIRSTRUCSIZE
							||	((AirStrucPtr)*trg)->movecode!=AUTO_COMBAT
							||	((AirStrucPtr)*trg)->ai.unfriendly==NULL
							)
						//	look for anything within tracking range + rel hdg bias
						{
							Coords3D* trgpos=_DPlay.GetGoodACPosition(trg);

							if (	Math_Lib.AbsSign(trgpos->X-weapitem->World.X)<aaaparams->flatrange
								&&	Math_Lib.AbsSign(trgpos->Z-weapitem->World.Z)<aaaparams->flatrange
								&&	(ULong)(trgpos->Y-weapitem->World.Y-aaaparams->minalt)<(ULong)aaaparams->altrange
								&&	Math_Lib.rnd()<RND10PC
								)
							{
								//can't check the angles easily...	 ANGLESInst
									nothingthere=FALSE;
									targetting=true;
									weapanim->target=trg->uniqueID.count;
									//clean everything up ready to lock and load...
									weapanim->hdg=aaaparams->minhdg+	Angles(ANGLES(aaaparams->hdgrange)/2);
									weapanim->pitch=aaaparams->minpitch+	Angles(ANGLES(aaaparams->pitchrange)/2);
									weapanim->LaunchTime=0;
					;;;;;;;;;;;;;;;;break;
							}
							else
							if (	Math_Lib.AbsSign(trgpos->X-weapitem->World.X)<aaaparams->flatrange+METRES2000
								&&	Math_Lib.AbsSign(trgpos->Z-weapitem->World.Z)<aaaparams->flatrange+METRES2000	)
									nothingthere=FALSE;
						}
						trg=targlist.Next();
					}
					trg=targlist.Next();
				}
				weapnum++;
				weapanim=SHAPE.GetWeaponLauncher(weapitem,weapnum,weapoff.X,weapoff.Y,weapoff.Z,mvel,mdelay,mburst,LT_MOVEGUN);//RDH 31Jul98
				if (weapanim)
					aaaparams=&aaaguntypelist[weapanim->LauncherType-LT_MOVEGUN];
			}
			if (nothingthere)
			{
				operator-=(weapitem);
				sleeplist+=weapitem;
				targetting=true;
			}
		}
		else
		{	//its an event item
			TrgListProc		targlist(AAA_ANTIAIRCRAFT,(Nationality)GR_NAT_ENEMY,NULL,NULL);	//assume all a/c use same detect routines
			ItemPtr	trg=targlist.Next();
			while (trg)
			{
				weapitem->InterceptandRange(trg);
				if (trg->Range</*METRES*/4000000)						//JIM 15Dec96
				{
//TEMP					Persons_2.PossibleEvent(weapitem,trg);
					AaaMainList::operator -=(weapitem);
					sleeplist-=weapitem;
				}
				trg=targlist.Next();
			}
		}
		if (!targetting)
		{
			weapanim=SHAPE.GetWeaponLauncher(weapitem,0,weapoff.X,weapoff.Y,weapoff.Z,mvel,mdelay,mburst,LT_MOVEGUN);//RDH 31Jul98
			if (weapanim && !weapanim->target)
			{
				weapanim->LaunchTime++;
			}
		}
	}
}



void	TransObj::SeenFlak(TransientItemPtr transit)
{
	ItemPtr	l=transit->Launcher;
	Nationality	nat=(Nationality)GR_NAT_FRIEND;
	DOLAUNCHER_PTR d=(DOLAUNCHER_PTR)SHAPE.GetLauncherPos(l->shape,0);
	if (d)
	{
		AaaParams* a=&aaaguntypelist
						[	d->lnchrtype-LT_MOVEGUN	];
		nat=a->nat;
		l->despos=transit->World;
		if (nat==GR_NAT_FRIEND)
		{

//TEMP			if (nat!=NAT_RED)
//TEMP				Persons_2.AddMessage(UserMsg::SIGHTED,TEXT_ALLIEDFLAKSIGHTED,l->despos);
//TEMP			else
//TEMP				Persons_2.AddMessage(UserMsg::SIGHTED,TEXT_GERMANFLAKSIGHTED,l->despos);
			if (Manual_Pilot.ControlledAC2->movecode<AUTO_PRECOMBAT)
				_Miles.SequenceAudible(FIL_MUSIC_FLAK);

		}
	}

}

void	LiveList::BackupSleepList()
{
	sleeplistbackup.aaaind=sleeplist.aaaind;
	AaaSubList	*slp,*slb,*sl;
	sl=sleeplist.aaalist;
	slp=NULL;
	slb=NULL;
	if (sl)
	do{
		slb=new AaaSubList;
		*slb=*sl;
		sl=sl->next;
		if (!slp)
			sleeplistbackup.aaalist=slb;
		else
			slp->next=slb;
		slp=slb;
	}while (sl && sl!=sleeplist.aaalist);
	if (sl)
		slb->next=sleeplistbackup.aaalist;

}
int		LiveList::ArchiveLiveList(UWord* archive,int archivesize,int skipsize)
{	//for each entry in live list:
	//	Transmit it's ID and all target IDs
	//
	int lastfullsize=0;
	AaaSubList* list=aaalist;
	int listind=0;
	if (list)
	do{
		if (!list[0][listind])
			if (skipsize)
				skipsize-=1;								 //skipping
			else
				if (lastfullsize==archivesize)
					return -lastfullsize;
				else
					archive[lastfullsize++]=0;					//empty slot
		else
		{
			ItemPtr weapitem=list[0][listind];
		Coords3D		weapoff;
		int				weapnum=0;
		UWord			mvel,mdelay,mburst;						//RDH 31Jul98
			while (SHAPE.GetWeaponLauncher(weapitem,weapnum,weapoff.X,weapoff.Y,weapoff.Z,mvel,mdelay,mburst,LT_MOVEGUN))
				weapnum++;
			if (skipsize)
				skipsize-=weapnum+1;							//skipping
			else
				if (lastfullsize+weapnum+1>archivesize)
					return (-lastfullsize);					//signal list already full
				else
				{											//put entry in list
					archive[lastfullsize++]=weapitem->uniqueID.count;
					WeapAnimData* w;
					weapnum=0;
					for(weapnum=0;((w=SHAPE.GetWeaponLauncher(weapitem,weapnum,weapoff.X,weapoff.Y,weapoff.Z,mvel,mdelay,mburst,LT_MOVEGUN))!=NULL);weapnum++)
						archive[lastfullsize++]=w->target;						
				}
		}
		listind++;
		if (listind==SUBLISTSIZE)
		{
			listind=0;
			list=list->next;

		}
	}while (list && (listind || list!= aaalist));
	return lastfullsize;
}
void	LiveList::RestoreSleepList()
{
	AaaSubList	*slp,*slb,*sl;
	sl=sleeplist.aaalist;	//delete main sleep list
	if (sl)
	do{
		slb=sl->next;
		delete sl;
		sl=slb;
	}while (sl && sl!=sleeplist.aaalist);
	sl=aaalist;
	if (sl)				//delete main live list
	do{
		slb=sl->next;
		delete sl;
		sl=slb;
	}while (sl && sl!=aaalist);
	aaalist=new AaaSubList;
	aaaind=0;

	sleeplist.aaaind=sleeplistbackup.aaaind;
	sl=sleeplistbackup.aaalist;
	slp=NULL;
	slb=NULL;
	if (sl==NULL)
	   sleeplist.aaalist=NULL;
	else
	do{
		slb=new AaaSubList;
		*slb=*sl;
		sl=sl->next;
		if (!slp)
			sleeplist.aaalist=slb;
		else
			slp->next=slb;
		slp=slb;
	}while (sl && sl!= sleeplistbackup.aaalist);
	if (sl)
		slb->next=sleeplist.aaalist;
}
void	LiveList::ApplyLiveList(UWord* archive,int archivesize)
{
	//for each item in archive, 
	//	remove from sleep list, 
	//	add to live list
	//	for each weapanim
	//		set target
	//		reset andgles and shootdelay

	while (archivesize)
	{
		if (aaaind==0)
		{
			bool doit=true;
			if (aaalist[0].next==aaalist)
			{
				int check;
				for (check=0;check<SUBLISTSIZE;check++)
					breakif (aaalist[0][check]);
				if (check==SUBLISTSIZE)
					doit=false;
			}
			if (doit)
			{
				aaaind=0;
				AaaSubList* newlist=new AaaSubList;
				newlist->next=aaalist[0].next;
				aaalist[0].next=newlist;
				aaalist=newlist;
			}
		}

		ItemPtr weapitem;
		if (archive[0])
		{
			weapitem=*Persons2::ConvertPtrUID(UniqueID(archive++[0]));
			archivesize--;
			sleeplist-=weapitem;
			WeapAnimData* w;
			Coords3D		weapoff;
			int				weapnum=0;
			UWord			mvel,mdelay,mburst;						//RDH 31Jul98
			while ((w=SHAPE.GetWeaponLauncher(weapitem,weapnum,weapoff.X,weapoff.Y,weapoff.Z,mvel,mdelay,mburst,LT_MOVEGUN))!=NULL)
			{
				w->target=UniqueID(archive++[0]);
				archivesize--;
				w->hdg=ANGLES_0Deg;
				w->pitch=ANGLES_45Deg;
				weapnum++;
			}
		}
		else
		{
			weapitem=NULL;
			archivesize--;
			archive++;
		}
		aaalist[0][aaaind]=weapitem;
		aaaind++;
		if (aaaind==SUBLISTSIZE)
			aaaind=0;
			
			
	}
}
