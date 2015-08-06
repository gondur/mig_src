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
//Filename       savebin.cpp
//System         
//Author         Jim Taylor
//Date           Wed 8 Jul 1998
//Description    Saves the package in binary
//------------------------------------------------------------------------------
#include	"dosdefs.h"
#include	"stdio.h"
#define	F_COMMON
#define F_GRAFIX	
#include	"files.g"
#include	"fileman.h"
#include	"node.h"
#include	"makebf.h"
#include	"bfnumber.h"
#include	"persons2.h"
#include	"bstream.h"

#define C	(char)
void	PackageList::SaveBin()
{
	File_Man.DiscardDirList(FIL_RUNTIMEPACK0);
	FileNum	fnum=FIL_RUNTIMEPACK0;
	for (int packs=0;packs<Profile::MAX_PACKS;packs++)
		if (pack[packs][0][0].uid)
		{
			BOStream f(File_Man.namenumberedfile(fnum));
			SaveBin(&packs[pack],f);
			fnum=FileNum(fnum+1);
		}
}


//
// Decodes text header into a profile instance
//[newline],wave,group,squad,flights=callname,takeofftime,arrivaltime,[numchars]
//note wave/group screwup.
static const char* savegroupstringnew="\nW%iG%iS%iF%i=C%iT%iA%i:";
static const char* loadgroupstringold=  "G%iW%iS%iF%i=C%iT%iA%i:%n";
static const char* loadgroupstringnew=  "W%iG%iS%iF%i=C%iT%iA%i:%n";
//
static const Profile::TargetDescript	emptydesc={UID_NULL};

int	Profile::DecodePackage(string packstr,bool decodeprimary)
{
	int results[4];
	int flights=0;
	int offset;
	bool ptarg=false;

	int argsused=sscanf(packstr,"Package battlefield: Duty %i, Takeoff,Target,Egress %05x,%05x,%05x%n",
		results+3,results+0,results+1,results+2,&offset);
	if (argsused<4)
		return 0;
	duty=(DutyType)results[3];
	packagetakeoff=(UniqueID)results[0];
	if (decodeprimary)
		packagetarget=(UniqueID)results[1];
	egressloc=(UniqueID)results[2];

	for (int w=0;w<MAX_WAVES;w++)
		for (int g=0;g<MAX_GROUPS;g++)
		{
			wave[w][g].SetFlights(0);
			for (int f=0;f<MAX_FLIGHTS;f++)
			{
				wave[w][g][f].primary=emptydesc;
				wave[w][g][f].secondary=emptydesc;
			}
		}
	packstr+=offset;
	argsused=sscanf(packstr," Waypoints: %i%n",results+0,&offset);
	if (argsused)
	{
		wpsused=results[0];
		packstr+=offset;
	}
	else
		wpsused=0;
	while (*packstr++!='\n')
	{}
	while (*packstr!=26)
	{
		int w,g,s,f,n,c,t,a;

		int argsused;
		if (packstr[0]=='G')
			argsused=sscanf(packstr,loadgroupstringold,&w,&g,&s,&f,&c,&t,&a,&n);
		else
			argsused=sscanf(packstr,loadgroupstringnew,&w,&g,&s,&f,&c,&t,&a,&n);
		wave[w][g].SetSquad(s);
		wave[w][g].SetFlights(f);
		flights+=f;
		packstr+=n;
		wave[w][g].callname=c;
		wave[w][g].takeofftime=t;
		wave[w].targettime=a;
		for (int i=0;i<4;i++)
		{
			int gl=strtol(packstr,&packstr,16);
			wave[w][g][i].globrefind=gl;
			if (gl)
			{
				int p=strtol(packstr,&packstr,16);
				int s=strtol(packstr,&packstr,16);
				if (p>=0x10000)
				{
					ptarg=true;
					wave[w][g][i].primary.SGT=UniqueID(p>>16);
				}
				else
					wave[w][g][i].primary.SGT=packagetarget;
				wave[w][g][i].primary.band=Persons2::getbandfromUID(UniqueID(p&IllegalSepID));
				wave[w][g][i].primary.SGbandindex=(p&IllegalSepID)-wave[w][g][i].primary.band;
				if (s>=0x10000)
				{
					ptarg=true;
					wave[w][g][i].secondary.SGT=UniqueID(s>>16);
				}
				else
					wave[w][g][i].secondary.SGT=packagetarget;
				wave[w][g][i].secondary.band=Persons2::getbandfromUID(UniqueID(s&IllegalSepID));
				wave[w][g][i].secondary.SGbandindex=(s&IllegalSepID)-wave[w][g][i].secondary.band;
			}
		}
		while (*packstr++!='\n')	{}
	}
	if (ptarg)
		return -flights;
	else
		return flights;		//AddToWorld
}

UniqueID Persons2::GetNthSGTMember(UniqueID SGT,UniqueIDBand uidband,int count)
{
	info_itemS *p;
	for (int i=uidband;i<IllegalSepID;i++)
		if ((p=*ConvertPtrUID(UniqueID(i)))!=NULL)
			if (p->SGT==SGT)
				if (!count--)
					return UniqueID(i);
	return SGT;
}

int Persons2::GetNOfSGTMember(UniqueID SGT,UniqueIDBand uidband,UniqueID member)
{
	info_itemS *p;
	int count=0;
	for (int i=uidband;i<member;i++)
		if ((p=*ConvertPtrUID(UniqueID(i)))!=NULL)
			if (p->SGT==SGT)
				count++;
	return count;
}

void	Profile::SetTargetUIDs(bool	fixconvoys)
{
	UniqueID	convsrc=UID_NULL,convtrg=UID_NULL;
	UniqueIDBand band=Persons2::getbandfromUID(packagetarget);

	if (band!=RedTrainBAND && band!=RedTruckBAND)	   //never load these!
		SupplyTree::CheckTargetLoaded(packagetarget);
	for (int w=0;w<MAX_WAVES;w++)
		for (int g=0;g<MAX_GROUPS;g++)
		{
//DEADCODE RDH 23/03/99 			wave[w][g].SetSquad(wave[w][g].squadron);
			for (int f=wave[w][g].numflights-1;f>=0;f--)
			{
				if (wave[w][g][f].primary.SGT)
				{
					if (wave[w][g][f].primary.SGT!=packagetarget)
						SupplyTree::CheckTargetLoaded(wave[w][g][f].primary.SGT);
					if (wave[w][g][f].primary.band)
						wave[w][g][f].primary.ID=Persons2::GetNthSGTMember(wave[w][g][f].primary.SGT,wave[w][g][f].primary.band,wave[w][g][f].primary.SGbandindex);
					else
					{
						if (wave[w][g][f].primary.SGT!=convsrc)
							if (fixconvoys)
								if (	Persons2::getbandfromUID(wave[w][g][f].primary.SGT)==RedRoadBAND
									||	Persons2::getbandfromUID(wave[w][g][f].primary.SGT)==RedRailBand
									)
								{
									convsrc=wave[w][g][f].primary.SGT;
									SupplyNode* node= SupplyTree::FindSupplyNodeForNodeItem(convsrc);
									convtrg=node->associated_item;
								}
						if (wave[w][g][f].primary.SGT==convsrc)
							wave[w][g][f].primary.ID=convtrg;
						else
							wave[w][g][f].primary.ID=wave[w][g][f].primary.SGT;
					}
				}
				if (wave[w][g][f].secondary.SGT)
				{
					if (wave[w][g][f].secondary.SGT!=packagetarget)
						SupplyTree::CheckTargetLoaded(wave[w][g][f].secondary.SGT);
					if (wave[w][g][f].secondary.band)
						wave[w][g][f].secondary.ID=Persons2::GetNthSGTMember(wave[w][g][f].secondary.SGT,wave[w][g][f].secondary.band,wave[w][g][f].secondary.SGbandindex);
					else
					{
						if (wave[w][g][f].secondary.SGT!=convsrc)
							if (fixconvoys)
								if (	Persons2::getbandfromUID(wave[w][g][f].secondary.SGT)==RedRoadBAND
									||	Persons2::getbandfromUID(wave[w][g][f].secondary.SGT)==RedRailBand
									)
								{
									convsrc=wave[w][g][f].secondary.SGT;
									SupplyNode* node= SupplyTree::FindSupplyNodeForNodeItem(convsrc);
									convtrg=node->associated_item;
								}
						if (wave[w][g][f].secondary.SGT==convsrc)
							wave[w][g][f].secondary.ID=convtrg;
						else
							wave[w][g][f].secondary.ID=wave[w][g][f].secondary.SGT;
					}
				}
			}
		}
}
//
//
//
//
void	PackageList::SaveBin(Profile* profile,BOStream&file)
{

	file<<CSprintf("Package battlefield: Duty %i, Takeoff,Target,Egress %05x,%05x,%05x Waypoints: %i",
		profile->duty,profile->packagetakeoff,profile->packagetarget,profile->egressloc,profile->wpsused);
	for (int wav=0;wav<Profile::MAX_WAVES;wav++)
		for (int grp=0;grp<Profile::MAX_GROUPS;grp++)
			if (profile[0][wav][grp].uid)
			{
				file<<CSprintf(savegroupstringnew,
					wav,grp,(int)profile[0][wav][grp].squadron,(int)profile[0][wav][grp].numflights,
					profile[0][wav][grp].callname,profile[0][wav][grp].takeofftime,profile[0][wav].targettime);
				for (int fl=0;fl<profile[0][wav][grp].numflights;fl++)
				{	//store all 	  //SGbandindex
					file<<CSprintf("\t%02x",profile[0][wav][grp][fl].globrefind);
					if (profile[0][wav][grp][fl].globrefind)
					{
						if (profile[0][wav][grp][fl].primary.SGT)
							if (profile[0][wav][grp][fl].primary.SGT==profile->packagetarget)
								file<<CSprintf("\t0%04x",
									profile[0][wav][grp][fl].primary.band
									+profile[0][wav][grp][fl].primary.SGbandindex);
							else
								if (profile[0][wav][grp][fl].primary.groupindex==-1)
									file<<CSprintf("\t0%04x0000",profile[0][wav][grp][fl].primary.SGT);
								else
									file<<CSprintf("\t0%04x%04x",profile[0][wav][grp][fl].primary.SGT,
										profile[0][wav][grp][fl].primary.band
										+profile[0][wav][grp][fl].primary.SGbandindex);
						else
							file<<"\t0";
						if (profile[0][wav][grp][fl].secondary.SGT)
							if (profile[0][wav][grp][fl].secondary.SGT==profile->packagetarget)
								file<<CSprintf("\t0%04x",
									profile[0][wav][grp][fl].secondary.band
									+profile[0][wav][grp][fl].secondary.SGbandindex);
							else
								if (profile[0][wav][grp][fl].secondary.groupindex==-1)
									file<<CSprintf("\t0%04x0000",profile[0][wav][grp][fl].secondary.SGT);
								else
									file<<CSprintf("\t0%04x%04x",profile[0][wav][grp][fl].secondary.SGT,
										profile[0][wav][grp][fl].secondary.band
										+profile[0][wav][grp][fl].secondary.SGbandindex);
						else
							file<<"\t0";
					}
				}
			}
	file<<'\n'<<C 26 <<C 0;
	int loopcount=0;	//increase for any fixed fields....
	for (wav=0;wav<Profile::MAX_WAVES;wav++)
		for (int grp=0;grp<Profile::MAX_GROUPS;grp++)
			if (profile[0][wav][grp].uid)
				loopcount++;		//how many air groups?
	file <<C T_bfsave <<C T_linklist <<C loopcount;
	for (wav=0;wav<Profile::MAX_WAVES;wav++)
		if (profile[0][wav][0].uid)
		{
//AirGroup
// T_inform:	
// T_inwing:
// T_duty:	
// T_form:	
// T_pos:		NOT USED - BASE ON SQUAD IF UNDEFINED!!!!
// T_route:		only leader 
// T_itemA:
// T_leader: - new in this position!

			file<<C T_airgrp <<C T_linklist <<C 6;
			SaveRouteBin(&profile[0][wav],file);
			SaveAirItemBin(&profile[0][wav][0],file);
			if (profile[0][wav][1].uid)
			{
				file<<C T_airgrp <<C T_linklist <<C 6;
				file<<C T_leader; Expr::putint(0,file);
				SaveAirItemBin(&profile[0][wav][1],file);
			}
			if (profile[0][wav][2].uid)
			{
				file<<C T_airgrp <<C T_linklist <<C 6;
				file<<C T_leader; Expr::putint(0,file);
				SaveAirItemBin(&profile[0][wav][2],file);
			}
		}
}


void	PackageList::SaveRouteBin(Profile::Wave* wave,BOStream&file)
{
	int loopcount=0;	//increase for any fixed fields....
	UniqueID wp=wave->firstwp;
	while (wp)
	{
		loopcount++;
		info_waypoint* w=*Persons2::ConvertPtrUID(wp);
		wp=w->nextwp;
	}
	file <<C T_route <<C T_linklist <<C loopcount;
	wp=wave->firstwp;
	while (wp)
	{
		info_waypoint* w=*Persons2::ConvertPtrUID(wp);
		SaveWaypointBin(w,file);
		wp=w->nextwp;
	}
}


void	PackageList::SaveWaypointBin(info_waypoint* wp,BOStream&file)
{	//count more of a problem - some fields optional!
//	T_setUID		 	optional - negative indicates key waypoint
//	T_vel/T_start		optional - default = cruise
//	T_pos				NEED
//	T_target			optional - bombing waypoint
//	T_wpact				optional - default = no action
//	T_rangepc/T_range	NEED
//	T_event				never
//	T_applygroup		optional - ocuur in sequence
//	T_applyflight		optional - ocuur in sequence
//	T_applyelt			optional - ocuur in sequence
//	T_applyac			optional - ocuur in sequence
//
	int loopcount=1;

	if (wp->uid.Evaluate()!=GOT_UNDEFINED_VAL)
		loopcount++;
	if (wp->vel.Evaluate()!=GOT_UNDEFINED_VAL || wp->etas.Evaluate()!=GOT_UNDEFINED_VAL)
		loopcount++;
	if (wp->target.Evaluate()!=GOT_UNDEFINED_VAL)
		loopcount++;
	if (wp->wpact.Evaluate()!=GOT_UNDEFINED_VAL)
		loopcount++;
	if (wp->range.Evaluate()!=GOT_UNDEFINED_VAL)
		loopcount++;

	if (wp->applyac.Evaluate()!=GOT_UNDEFINED_VAL)
		loopcount++;
	if (wp->applyelt.Evaluate()!=GOT_UNDEFINED_VAL)
		loopcount++;
	if (wp->applyflight.Evaluate()!=GOT_UNDEFINED_VAL)
		loopcount++;
	if (wp->applygroup.Evaluate()!=GOT_UNDEFINED_VAL)
		loopcount++;

	file <<C T_waypoint <<C T_linklist <<C loopcount;

	if (wp->uid.Evaluate()!=GOT_UNDEFINED_VAL)
	{	file <<C T_setUID;wp->uid.Save(file,NULL);	}
	if (wp->vel.Evaluate()!=GOT_UNDEFINED_VAL)
	{	file <<C T_vel;wp->vel->Save(file,NULL);	}
	if (wp->etas.Evaluate()!=GOT_UNDEFINED_VAL)
	{	file <<C T_start <<C T_secs;wp->etas.Save(file,NULL);	}
	if (wp->target.Evaluate()!=GOT_UNDEFINED_VAL)
	{	file <<C T_target;wp->target.Save(file,NULL);	}

	file<<C T_pos;wp->position.Save(file,NULL);

	if (wp->wpact.Evaluate()!=GOT_UNDEFINED_VAL)
	{	file <<C T_wpact;wp->wpact.Save(file,NULL);	}
	if (wp->range.Evaluate()!=GOT_UNDEFINED_VAL)
		if (!wp->rangeispercent)
		{	file <<C T_range;wp->range.Save(file,NULL);	}
		else
		{	file <<C T_rangepc;wp->range.Save(file,NULL);	}

	if (wp->applyac.Evaluate()!=GOT_UNDEFINED_VAL)
	{	file <<C T_applyac;wp->applyac.Save(file,NULL);	}
	if (wp->applyelt.Evaluate()!=GOT_UNDEFINED_VAL)
	{	file <<C T_applyelt;wp->applyelt.Save(file,NULL);	}
	if (wp->applyflight.Evaluate()!=GOT_UNDEFINED_VAL)
	{	file <<C T_applyflight;wp->applyflight.Save(file,NULL);	}
	if (wp->applygroup.Evaluate()!=GOT_UNDEFINED_VAL)
	{	file <<C T_applygroup;wp->applygroup.Save(file,NULL);	}
}


void	PackageList::SaveAirItemBin(Profile::Group* group,BOStream&file)
{
	info_airgrp *a=*Persons2::ConvertPtrUID(group->uid);
// T_route:		done
// T_inform:	
// T_inwing:
// T_duty:	
// T_form:	
	file <<C (T_inwing);a->inwing.Save(file,NULL);
	file <<C (T_inform);a->inform.Save(file,NULL);
	file <<C (T_duty);a->duty.Save(file,NULL);
	if (a->form.Evaluate()<SQUAD_FLATV)
		a->form=SQUAD_FLATV;
	file <<C (T_form);a->form.Save(file,NULL);

// T_itemA:
//	T_setUID:		NEVER
//	T_nation:		ALWAYS
//	T_shape:		NEVER
//	T_type:			ALWAYS - NOW MEANS SQUADRON
//	T_vel:			NEVER
//	T_UIDband:		NEVER
//	T_move:			NEVER
//	T_skill:		NEVER - from pilot skill!
//	T_morale:		NEVER - from pilot skill!
//	T_character:	NEVER - from pilot skill!
//	T_damage:		NEVER - from pilot skill!
//	T_bombs:		ALWAYS = weap package
//	T_target:		NEVER
//	T_attacker:		NEVER
//	T_leader:		now in airgrp!
//	T_follower:		NEVER
//	T_home:			NEVER
//	T_event:		NEVER
//	T_att:			NEVER
//	T_squadron:		NEVER - oops!
//	T_paintscheme	NEVER - from pilot skill!
//					3 fields
//			attmethod,					//NEED TO SAVE if set
//			attpattern,					//NEED TO SAVE
//			radiosilence,				//NEED TO SAVE

	int total=3;
	if (a->attmethod.Evaluate()!=GOT_UNDEFINED_VAL)	total++;
	if (a->attpattern.Evaluate()!=GOT_UNDEFINED_VAL)	total++;
	if (a->radiosilence.Evaluate()!=GOT_UNDEFINED_VAL)	total++;


	file <<C T_itemA <<C T_linklist <<C total;
	file <<C (T_nation);Expr::putint(NAT_BLUE,file);
	file <<C (T_type);a->type.Save(file,NULL);
	file <<C (T_bombs);a->bombs.Save(file,NULL);


	if (a->attmethod.Evaluate()!=GOT_UNDEFINED_VAL)
		file <<C (T_attmethod);a->attmethod.Save(file,NULL);
	if (a->attpattern.Evaluate()!=GOT_UNDEFINED_VAL)
		file <<C (T_attpattern);a->attpattern.Save(file,NULL);
	if (a->radiosilence.Evaluate()!=GOT_UNDEFINED_VAL)
		file <<C (T_radiosilence);a->radiosilence.Save(file,NULL);
}
void EventVal::Save(BOStream& f,char*,int,EnumListNames)
{
	if (complex)
		complex->Save(f,NULL);
	else
		Expr::putint(value,f);

}
void Expr::putint(int i,BOStream& f)
{
	f <<C T_int <<(int) i;
}

void GlobRefExpr::	Save( BOStream& f, char *, int, EnumListNames )
{
	f<<C T_mainprog;
	putint(globrefind,f);
	
}
void UIDExpr::		Save( BOStream& f, char *, int, EnumListNames )
{
	f <<C T_target;
	val->Save(f,NULL);
}
void RndExpr::		Save( BOStream& f, char *, int, EnumListNames )
{
	assert(!"RndExpr::Save");
}
void SelExpr::		Save( BOStream& f, char *, int, EnumListNames )
{
	assert(!"SelExpr::Save");
}
void ListExpr::	Save( BOStream& f, char *, int, EnumListNames )
{
	f<<C T_list <<C T_linklist <<C (1+maxentries);
	index.Save(f,NULL);
	for (int i=0;i<maxentries;i++)
		entries[i].Save(f,NULL);
}
void ListFormExpr::Save( BOStream& f, char *, int, EnumListNames )
{
	f<<C T_list <<C T_linklist <<C (maxentries);
	for (int i=0;i<maxentries;i++)
		entries[i].Save(f,NULL);
}
void WorldExpr::	Save( BOStream& f, char *, int, EnumListNames )
{
	int loopcount=0;
	if (uniqueID.Evaluate()!=GOT_UNDEFINED_VAL)
		loopcount++;
	XyzExpr* xyz=(XyzExpr*)delta.complex;
	bool anyxyzset=
		(	xyz
		&& 	(	(xyz->X.Evaluate()!=GOT_UNDEFINED_VAL && xyz->X.Evaluate())
			||	(xyz->Y.Evaluate()!=GOT_UNDEFINED_VAL && xyz->Y.Evaluate())
			||	(xyz->Z.Evaluate()!=GOT_UNDEFINED_VAL && xyz->Z.Evaluate())
		)	);
	if (anyxyzset && deltaisabs)
	{
		if (xyz->X.Evaluate()!=GOT_UNDEFINED_VAL && xyz->X.Evaluate())
			loopcount++;
		if (xyz->Y.Evaluate()!=GOT_UNDEFINED_VAL && xyz->Y.Evaluate())
			loopcount++;
		if (xyz->Z.Evaluate()!=GOT_UNDEFINED_VAL && xyz->Z.Evaluate())
			loopcount++;
	}
	if (rotate.complex || (!deltaisabs && anyxyzset))
		loopcount++;
	f<<C T_pos <<C T_linklist <<C loopcount;

	if (uniqueID.Evaluate()!=GOT_UNDEFINED_VAL)
	{	f<<C T_target;	uniqueID.Save(f,NULL);	}

	if (anyxyzset && deltaisabs)
	{
		if (xyz->X.Evaluate()!=GOT_UNDEFINED_VAL && xyz->X.Evaluate())
		{	f<<C T_x;xyz->X.Save(f,NULL);	}
		if (xyz->Y.Evaluate()!=GOT_UNDEFINED_VAL && xyz->Y.Evaluate())
		{	f<<C T_y;xyz->Y.Save(f,NULL);	}
		if (xyz->Z.Evaluate()!=GOT_UNDEFINED_VAL && xyz->Z.Evaluate())
		{	f<<C T_z;xyz->Z.Save(f,NULL);	}
	}
	if (rotate.complex || (!deltaisabs && anyxyzset))
	{
		loopcount=0;
		RotExpr* r=(RotExpr*)rotate.complex;
		if (!deltaisabs && anyxyzset)
		{
			if (xyz->X.Evaluate()!=GOT_UNDEFINED_VAL && xyz->X.Evaluate())
				loopcount++;
			if (xyz->Y.Evaluate()!=GOT_UNDEFINED_VAL && xyz->Y.Evaluate())
				loopcount++;
			if (xyz->Z.Evaluate()!=GOT_UNDEFINED_VAL && xyz->Z.Evaluate())
				loopcount++;
		}
		if (r)
		{
			if (r->icpt.complex)
				loopcount++;
			if (r->range.Evaluate()!=GOT_UNDEFINED_VAL)
				loopcount++;
			if (r->hdg.Evaluate()!=GOT_UNDEFINED_VAL)
				loopcount++;
			if (r->pitch.Evaluate()!=GOT_UNDEFINED_VAL)
				loopcount++;
		}
		f <<C T_rel <<C T_linklist <<C loopcount;
		if (!deltaisabs && anyxyzset)
		{
			if (xyz->X.Evaluate()!=GOT_UNDEFINED_VAL && xyz->X.Evaluate())
			{	f<<C T_x;xyz->X.Save(f,NULL);	}
			if (xyz->Y.Evaluate()!=GOT_UNDEFINED_VAL && xyz->Y.Evaluate())
			{	f<<C T_y;xyz->Y.Save(f,NULL);	}
			if (xyz->Z.Evaluate()!=GOT_UNDEFINED_VAL && xyz->Z.Evaluate())
			{	f<<C T_z;xyz->Z.Save(f,NULL);	}
		}
		if (r)
		{
			if (r->icpt.complex)
			{	f<<C T_icpt;r->icpt.Save(f,NULL);	}
				loopcount++;
			if (r->range.Evaluate()!=GOT_UNDEFINED_VAL)
				if (r->rangeispercent)
				{	f<<C T_rangepc;r->range.Save(f,NULL);	}
				else
				{	f<<C T_range;r->range.Save(f,NULL);	}
			if (r->hdg.Evaluate()!=GOT_UNDEFINED_VAL)
			{	f<<C T_hdg;r->hdg.Save(f,NULL);	}
			if (r->pitch.Evaluate()!=GOT_UNDEFINED_VAL)
			{	f<<C T_pitch;r->pitch.Save(f,NULL);	}
		}
	}
}
void XyzExpr::		Save( BOStream& f, char *, int, EnumListNames ){}
void RotExpr::		Save( BOStream& f, char *, int, EnumListNames ){}
void IcptExpr::	Save( BOStream& f, char *, int, EnumListNames )
{
	f<<C T_linklist <<C 2;
	objA.Save(f,NULL);
	objB.Save(f,NULL);
}
void UIDExpr::Save(struct _iobuf *,char *,int,enum EnumListNames)		{}
void WorldExpr::Save(struct _iobuf *,char *,int,enum EnumListNames)		{}
void XyzExpr::Save(struct _iobuf *,char *,int,enum EnumListNames)		{}
void GlobRefExpr::Save(struct _iobuf *,char *,int,enum EnumListNames)	{}
void RndExpr::Save(struct _iobuf *,char *,int,enum EnumListNames)		{}
void SelExpr::Save(struct _iobuf *,char *,int,enum EnumListNames)		{}
void ListExpr::Save(struct _iobuf *,char *,int,enum EnumListNames)		{}
void ListFormExpr::Save(struct _iobuf *,char *,int,enum EnumListNames)	{}
void RotExpr::Save(struct _iobuf *,char *,int,enum EnumListNames)		{}
void IcptExpr::Save(struct _iobuf *,char *,int,enum EnumListNames)		{}
