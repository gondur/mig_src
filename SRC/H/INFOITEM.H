////////////////////////////////////////////////////////////////////////
//
// Module:      infoitem.h
//
// Created:     17/12/98 by JIM
//
// Description: info_item variants of item
//
////////////////////////////////////////////////////////////////////////
#ifndef	INFOITEM_INCLUDED
#define	INFOITEM_INCLUDED
struct	info_event;
typedef	info_event* info_event_ptr;

////struct	info_debug
////{
////static int highestaddr,lowestaddr,numelts;
////
////	DES	~info_debug()
////		{numelts--;
//////	(*(char*)0xB0002)='d';
////		}
////	CON	info_debug()
////	{		if ((int)this<lowestaddr)
////				lowestaddr=(int)this;
////			if ((int)this>highestaddr)
////				highestaddr=(int)this;
////			numelts++;
//// //	(*(char*)0xB0002)='D';
////// 	(*(char*)0xB0004)='0';
////
////	}
////};
////
struct	info_event_suicide_ptr
{
	info_event_ptr p;
	info_event_suicide_ptr()
	{	p=NULL;
	}
	info_event_suicide_ptr(info_event_ptr q)	{p=q;}
	DES	~info_event_suicide_ptr();
	info_event* operator= (info_event_ptr q)				{return p=q;}
//	info_event_suicide_ptr& operator= (info_event_suicide_ptr& q)		{p=q.p;q.p=NULL;return *this;}
	operator info_event_ptr& ()					{return p;}
	info_event_ptr* operator & ()				{return &p;}
	info_event_ptr operator ->()				{return p;}
	Bool	operator== (int i)				{if (p)	return FALSE;else return TRUE; }
	Bool	operator!= (int i)				{if (p)	return TRUE;else return FALSE; }
};

struct	info_event
#ifdef	BFNUMBER_Included
	   //				:info_debug
{
	SWord	FrFighterSq,FrBomberSq,EnFighterSq,EnBomberSq;
	SWord	used_redac,used_blueac;
	SWord	used_redmob,used_bluemob;
	SWord	used_statics,used_waypoints;
	
	int	usedsetvals,allsetvals;
	info_event()	{	usedsetvals=allsetvals=0;
						used_redac=used_blueac=
							used_redmob=used_bluemob=
								used_statics=used_waypoints=0;
						FrFighterSq=FrBomberSq=EnFighterSq=EnBomberSq=0;
					}
	~info_event()	{usedsetvals=allsetvals=0;}
	EventVar	setvals[MAXEVENTS];
	EventVal	starth;
	EventVal	startm;
	EventVal	starts;
	EventVal	winh;
	EventVal	winm;
	EventVal	wins;
	EventVal	bfields;

	info_event_suicide_ptr next;

}
#endif
;

#ifdef	BFNUMBER_Included
inline DES	info_event_suicide_ptr::~info_event_suicide_ptr()
{
	delete p;
}
#endif
//////////////////////////////////////	//notes on whether saved in airgroups
struct	info_base
#ifdef	BFNUMBER_Included
					:Item
{

///	UniqueID	SGT;	
	UByte	 	bfieldindex;			//no
	UByte 		extra;					//no
EventVal	uid,						//not saved for aircraft	//negative for key waypoints
			position;					//not saved for aircraft
protected:
	info_base()	{SGT=UID_Null;(int&)Next=-1;}


}
#endif
;

struct	info_itemS
#ifdef	BFNUMBER_Included
					:info_base//,info_debug
{
	info_event_suicide_ptr events;
EventVal	band,						//not set up	
			shape,						//not set up
			attitude;					//not set up
		info_itemS()	{Status.size=ITEMSIZE;}
	~info_itemS()
	{}
}
#endif
;
struct	EventVal;

struct	info_waypoint
#ifdef	BFNUMBER_Included
					:info_base//,info_debug
{
	info_event_suicide_ptr events;
UniqueID	prevwp;
UniqueID	nextwp;
UniqueID	owner;
EventVal	useexistingWP;				
EventVal
			etah,						
			etam,						
			etas,						
			vel,						
			target,						
			wpact,
			applygroup,
			applyflight,
			applyelt,
			applyac,
			range;
Bool		rangeispercent;
	info_waypoint()	{rangeispercent=FALSE;prevwp=nextwp=UID_Null;Status.size=WAYPOINTSIZE;
	}
	~info_waypoint()
	{
	}
}
#endif
;

struct	info_grndgrp
#ifdef	BFNUMBER_Included
					:info_itemS
{
UniqueID	wpref;
EventVal	inform,						//saved
			form,						//saved
			nat,						//saved
			type,						//saved
			vel,						//not set up
			damage,						//never
			movecode,					//never
			leader;
		info_grndgrp()	{Status.size=MOBILESIZE;wpref=UID_NULL;}
		~info_grndgrp()
		{
		}
}
#endif
;
struct	info_airgrp
#ifdef	BFNUMBER_Included
					:info_grndgrp
{
SWord		squadron;
EventVal
			inwing,						//saved
			duty,						//saved
			skill,						//never
			morale,						//never
			character,					//never
			bombs,						//always
			target,						//never
			attacker,					//never
			follower,					//never
			homebase,					//never
			squadname,					//not set up
//new fields for mig alley:
			attmethod,					//NEED TO SAVE
			attpattern,					//NEED TO SAVE
			radiosilence,				//NEED TO SAVE
//
			paintrules[5];				//never
int			usedpaintrules;
		info_airgrp()	{Status.size=AIRSTRUCSIZE;squadron=0;usedpaintrules=0;}
	~info_airgrp()		{}
}
#endif
;
struct	EventLog;
typedef	EventLog	*EventLogPtr;

struct	EventEntry
{
 	ULong		launchtime;
	enum		Stage											//RDH 01Dec96
				{	EMPTY,UNSEEN,SEENBYOTHERS,ATTACKEDBYOTHERS,
					SEENBYPLAYERS,HOSTILE,SPOTTEDDOGFIGHT,
					APPROACHED,ATTACKED,DAMAGED,KILLED,TAKEOFF,     //RDH 01Dec96
					BENTWING,FATALCRASH,CRASHLAND,CRASHLANDTOOFAST,
					LANDOK,LANDOKATHOME,MIDAIRCOLLISION,
					DAMAGEDSTATIC,DAMAGEDTRUCK,KILLEDSTATIC,KILLEDTRUCK,
					PARACHUTED,
				};                                               //RDH 01Dec96
	ONLYFIELD(UByte,Stage,stage);
	UByte		hits;	//kills for air groups... hits for damaged ground
	UByte		losses;
	UByte		encsize;

	UWord		place;
	ONLYFIELD(UWord,UniqueID,homebase);
	ONLYFIELD(UByte,PlaneTypeSelect,encounteredtype);
	ONLYFIELD(UByte,PlaneTypeSelect,escorttype);
	
};

#endif
