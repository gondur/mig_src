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
//Filename       persons4.cpp
//System
//Author         Jim Taylor
//Date           Fri 20 Jun 1997
//Description    Version of persons for mission editor
//------------------------------------------------------------------------------
#include <vcl\vcl.h>
#include	"memain.h"

#define	SOURCE

  //	#include	<stdio.h>
	//DON'T WRITE INCLUDE FILES HERE, PUT THEM IN BFCOMMON
	#include	"text.h"
	#include	"dosdefs.h"
	#include	"myerror.h"
//#define	TEXTREF_Included
	#include	"worldinc.h"
 	#include	"myangles.h"
	#include	"uniqueid.h"
	#include	"mymath.h"
	#include	"bfnumber.h"
	#include	"makebf.h"
	#include	"persons2.h"
//	#include	"sqinfo.h"
	#include	"files.g"
//#define	TEXTREF_Included
//	#include	"text.h"
//	#include	"error.h"
	#include	"mymath.h"
	#include	"worldinc.h"
	#include	"bfnumber.h"
//	#include	"bfcommon.h"
	#include	"bfnumber.h"	//intensional double include
	//DON'T WRITE INCLUDE FILES HERE, PUT THEM IN BFCOMMON
//DeadCode JIM 28Mar96 extern	PlaneType&	camel;										//RDH 23Feb96
//Old_Code PD 27Aug96  	MAKEFIELD	(ShapeNum,ShapeNumMIN,ShapeNumMAX);
	extern	ULong	GR_FriendlyScoutType00;
	extern	ULong	GR_GlobalSkillMin;
	extern	ULong	GR_GlobalSkillMax;
	extern	ULong	GR_CWP,GR_CPP;

//##int	Expr::lowestaddr=0x77777777;
//##int	Expr::highestaddr=0;
//##int	Expr::numelts=0;
//##int	Expr::indent=0;
//int	info_debug::lowestaddr=0x77777777;
//int	info_debug::highestaddr=0;
//int	info_debug::numelts=0;

Bool	operator == (TokenCode a,TokenCode b)	{return Bool(int(a)==int(b));}
Nationality		defaultside=NAT_GREEN;

#define EvalOrDefault(field,type,expr,default)				\
		{													\
			int v1;											\
			if ((v1=I.expr.Evaluate())==ENABLE_COMPLEX_VAL)	\
				field=default;								\
			else			   								\
				field=type(v1);								\
		}

ItemBase *items[(int)IllegalBAND+1];
ItemBase**		Persons2::pItem=items;
BfieldDesc*		Persons2::bfdesc=NULL;
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//
//	THESE make_ routines make the actual items in the world
//
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
CON	Persons2::Persons2(WorldStuff*,ViewPoint*)
{
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴


void	Persons2::FixupRouteOwner(UniqueID	owner,UniqueID route)
{
	while (route)
	{
		info_waypoint* W=*ConvertPtrUID(route);

		if (W->Status.size!=WAYPOINTSIZE)
			W->owner=owner;
		W->pos.EvalW(W->World);
		if (W->target.Evaluate()!=ENABLE_COMPLEX_VAL)
		{
			Coords3D	t;
			UIDExpr	u;
			u.val=W->target.Evaluate();
			u.EvalW(t);
			W->World.X+=t.X+MissionEditor->zoomiconsize;
			W->World.Y+=t.Y;
			W->World.Z+=t.Z-MissionEditor->zoomiconsize;
		}
		W->owner=owner;
		route=W->nextwp;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		make_airgrp
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
void	Persons2::make_airgrp(info_airgrp& I)
{
	if (!justscanning)
	{
		info_airgrp*	J=new info_airgrp;
		*J=I;
		int v1,v2,v3;
		if ((v3=J->nat.Evaluate())==ENABLE_COMPLEX_VAL)
			v3=defaultside;
		if ((v1=J->uid.Evaluate())==ENABLE_COMPLEX_VAL)
			if ((v2=J->band.Evaluate())==ENABLE_COMPLEX_VAL)
				if (v3==(int)NAT_RED)
					J->uniqueID.count=assignuid(RedAcBAND);
				else
					J->uniqueID.count=assignuid(BlueAcBAND);
			else
				J->uniqueID.count=assignuid((UniqueIDBand)v2);
		else
			if (ConvertPtrUID(UniqueID(v1)))
				J->uniqueID.count=assignuid(getbandfromUID(UniqueID(v1)));
			else
				J->uniqueID.count=UniqueID(v1);
		J->bfieldindex=currbfindex;
//		J->uniqueID.sector=loadingmainworld;
		J->uniqueID.changed=FALSE;
//		J->uniqueID.deaded=FALSE;
		J->position.EvalW(J->World);
  //		J->shape=ShapeNum(J->shape.Evaluate());
//		FixupRouteOwner(J->uniqueID.count,J->wpref);
  //		FixupRouteOwner(J->uniqueID.count,J->wpref);
//camp tmp		if (J->inform.Evaluate()==ENABLE_COMPLEX_VAL)
//			MissionEditor->ActiveCampaign.PlayerAcuid = J->uniqueID.count;
		logUID(J);
	}
	else
	{
		int	v3;
		if ((v3=I.nat.Evaluate())==ENABLE_COMPLEX_VAL)
			v3=defaultside;
        if (bfdesc)
			if (I.inwing.Evaluate()==ENABLE_COMPLEX_VAL)
				if (v3==NAT_RED)
					bfdesc->RAC+=12;
				else
					bfdesc->BAC+=12;
			else
				if (v3==NAT_RED)
					bfdesc->RAC+=I.inform.Evaluate();
				else
					bfdesc->BAC+=I.inform.Evaluate();
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		make_waypoint
//Author		Jim Taylor
//Date			Wed 18 Jun 1997
//
//Description
//
//Inputs		if I.useexistingWP then evaluate that to get UID to link in!
//				no other vars will be filled in.
//
//Returns
//
//------------------------------------------------------------------------------
UniqueID	Persons2::make_waypoint(info_waypoint& I)
{
	if (!justscanning)
	{
		info_waypoint*	J=new info_waypoint;
		*J=I;
		int v=I.uid.Evaluate();
		if (v==ENABLE_COMPLEX_VAL)
			v=assignuid(WayPointBAND);
		J->uniqueID.count=UniqueID(v);
		J->bfieldindex=currbfindex;
//		J->uniqueID.sector=loadingmainworld;
		J->uniqueID.changed=FALSE;
 //		J->uniqueID.deaded=FALSE;
		//Position calculated in FixupRouteOwner
		logUID(J);

		if (J->prevwp && J->prevwp!=IllegalSepID)
		{
			info_waypoint* W=*ConvertPtrUID(J->prevwp);
			W->nextwp=UniqueID(v);
			if (W->events
			&&	W->pos.complex
			&&	W->pos.complex->Arguments()==2
			&&  W->pos[1]->type==Expr::EXPR_ROT
			&&  W->pos[1][0]->type==Expr::EXPR_ICPT
			)
			{
			//if coords expr for pos[0] == prev wp == ICPT[0]
			//change to UID of prevwp
			//if coords expr for new wp == ICPT[1]
			//change to UID of new wp
			}
		}
		else
			J->prevwp=UID_Null;
		J->nextwp=UID_Null;
		return UniqueID(v);
	}
	else
		if (bfdesc && justscanning==SCANNAMES)
			bfdesc->WP++;
	return UID_Null;

}

void	Persons2::AddRoute(UniqueID	firstwp)
{
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		make_gndgrp
//Author		Jim Taylor
//Date			Wed 18 Jun 1997
//
//Description
//
//Inputs
//
//Returns
//
//------------------------------------------------------------------------------
void	Persons2::make_gndgrp(info_grndgrp& I)
{
	if (!justscanning)
	{
		info_grndgrp*	J=new info_grndgrp;
		*J=I;
		int v1,v2,v3;
		if ((v3=J->nat.Evaluate())==ENABLE_COMPLEX_VAL)
			v3=defaultside;
		if ((v1=J->uid.Evaluate())==ENABLE_COMPLEX_VAL)
			if ((v2=J->band.Evaluate())==ENABLE_COMPLEX_VAL)
				if (v3==(int)NAT_RED)
					J->uniqueID.count=assignuid(RedAcBAND);
				else
					J->uniqueID.count=assignuid(BlueAcBAND);
			else
				J->uniqueID.count=assignuid((UniqueIDBand)v2);
		else
			if (ConvertPtrUID(UniqueID(v1)))
				J->uniqueID.count=assignuid(getbandfromUID(UniqueID(v1)));
			else
				J->uniqueID.count=UniqueID(v1);
		J->bfieldindex=currbfindex;
//		J->uniqueID.sector=loadingmainworld;
		J->uniqueID.changed=FALSE;
//		J->uniqueID.deaded=FALSE;
		J->position.EvalW(J->World);
//		J->shape=ShapeNum(J->shape.Evaluate());
		logUID(J);
//		FixupRouteOwner(J->uniqueID.count,J->wpref);
  //		FixupRouteOwner(J->uniqueID.count,J->wpref);
	}                                               
	else
		if (justscanning==SCANNAMES)
		{
			int	v3;
			if ((v3=I.nat.Evaluate())==ENABLE_COMPLEX_VAL)
				v3=defaultside;
            if (bfdesc)
				if (v3==NAT_RED)
					bfdesc->RGR+=I.inform.Evaluate();
				else
					bfdesc->BGR+=I.inform.Evaluate();
		}
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		make_itemS
//Author		Jim Taylor
//Date			Wed 18 Jun 1997
//
//Description	Makes object J, a copy of temp object I
//				Fills in item UID and coords
//				Adds item to UID table.
//
//Inputs
//
//Returns
//
//------------------------------------------------------------------------------
void	Persons2::make_itemS(info_itemS& I)
{
//  if ((int)I.uid.Evaluate() != (int)UID_Varneville)				//this is in wrong band so don't load!
//  {
	if (!justscanning)
	{
		info_itemS* J=new info_itemS;
		*J=I;
		int v1,v2;
																	//	if ((v3=J->nat.Evaluate())==ENABLE_COMPLEX_VAL)
																	  //		v3=defaultside;
		if ((v1=J->uid.Evaluate())==ENABLE_COMPLEX_VAL)
			if ((v2=J->band.Evaluate())==ENABLE_COMPLEX_VAL)
				J->uniqueID.count=assignuid(RedVetoedBAND);
			else
				J->uniqueID.count=assignuid((UniqueIDBand)v2);
		else
			if (ConvertPtrUID(UniqueID(v1)))
				J->uniqueID.count=assignuid(getbandfromUID(UniqueID(v1)));
			else
				J->uniqueID.count=UniqueID(v1);
		J->bfieldindex=currbfindex;
//DeadCode RDH 11Feb98 		J->uniqueID.sector=loadingmainworld;
		J->uniqueID.changed=FALSE;
//		J->uniqueID.deaded=FALSE;
		J->position.EvalW(J->World);
		J->shape=ShapeNum(J->shape.Evaluate());
		logUID(J);
	}
	else
		if (bfdesc && justscanning==SCANNAMES)
			bfdesc->ST++;
//  }
//  else
//  {
//
//
//  }
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		make_events
//Author		Jim Taylor
//Date			Wed 18 Jun 1997
//
//Description	Don't need to fill this routine.
//				The event chain is automatically part of the called routine
//
//Inputs
//
//Returns
//
//------------------------------------------------------------------------------
void	Persons2::make_events(info_event*&	I,ItemBasePtr P)
{
	if (justscanning==SELECTSQUAD)
	{
		if (--selectedsquad==0)
		{
			*keptevent=*I;
		}
	}
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		make_setval
//Author		Jim Taylor
//Date			Wed 18 Jun 1997
//
//Description
//
//Inputs
//
//Returns
//
//------------------------------------------------------------------------------
void	Persons2::make_setval(EventVar& es)
{
	if (justscanning)
    	if (bfdesc)
			bfdesc->defrefs[bfdesc->useddefrefs++]=es;
        else;    
	else
		SetLoc(es.index,es.Evaluate());
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		used_globref
//Author		Jim Taylor
//Date			Wed 18 Jun 1997
//
//Description
//
//Returns
//
//------------------------------------------------------------------------------
void	Persons2::used_globref(int index)
{
	if (bfdesc&&justscanning)
	{
		for (int i=0;i<bfdesc->useddefrefs;i++)
			if (bfdesc->defrefs[i].index==index)
				return;
		for (int i=0;i<bfdesc->usedreqrefs;i++)
			if (bfdesc->reqrefs[i]==index)
				return;


		bfdesc->reqrefs[bfdesc->usedreqrefs++]=index;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		make_string
//Author		Jim Taylor
//Date			Wed 18 Jun 1997
//
//Description
//
//Inputs		t is one of:
//						T_comment
//						T_name
//
//Returns
//
//------------------------------------------------------------------------------
void	Persons2::make_string(string src,int len,TokenCode t)
{
	if (!bfdesc)
    	return;
	if (justscanning==SCANNAMES)
	{
		char*	trg=bfdesc->title;
		if (t==T_comment)
			if ((UWord&)bfdesc->description[0])
			{
				trg=bfdesc->news;
				if (len>=DESCRIPT_LEN)
					len=DESCRIPT_LEN-1;

			}
			else
			{
				trg=bfdesc->description;
				if (len>=DESCRIPT_LEN)
					len=DESCRIPT_LEN-1;
			}
		else
		if (t==T_family)
		{
			trg=bfdesc->family;
			if (len>=TITLE_LEN)
				len=TITLE_LEN-1;
		}
		else
			if (len>=TITLE_LEN)
				len=TITLE_LEN-1;
		trg[1]=1;
		strncpy(trg,src,len);
		trg[len]=0;
	}
	else
	if (justscanning==SCANSQUADS)
		SquadAddDesc(src,len,t);

	if (t==T_family && src[0]<='9')
		if (justscanning)
		{
			int	dummy;
//camp tmp			sscanf(src,
//					"%i %i "
//					"%hi %hi "
//					"%c %c "
//					"%hi %hi %hi "
//					"%hi %hi %hi "
//					"%hi %hi "
//					"%hi %hi "
//					"%hi %hi %hi"
//					,
//					&MissionEditor->ActiveCampaign.nextdate,&dummy,
//					&dummy,&dummy,
//					&MissionEditor->ActiveCampaign.nextnat,&dummy,
//					&dummy,&dummy,&dummy,
//						&MissionEditor->ActiveCampaign.nextera,
//						&MissionEditor->ActiveCampaign.nextregion,
//						&dummy,
//					&dummy,&dummy,
//					&dummy,&dummy,
//					&dummy,&dummy,&dummy
//					);
//			MissionEditor->ActiveCampaign.nextnat&=31;
		}
		else
		{	//load mission control record
//camp tmp			MissionData *M=MissionEditor->ActiveCampaign.mission+MissionEditor->currmission;
//			int	dummy;
//			sscanf(src,
//					"%i %i "
//					"%hi %hi "
//					"%c %c "
//					"%hi %hi %hi "
//					"%hi %hi %hi "
//					"%hi %hi "
//					"%hi %hi "
//					"%hi %hi %hi"
//					,
//					&M->missiondate,&M->timeofday,
//					&M->numofsquadronac,&M->numofflightac,
//					&M->PlayerNationality,&M->formationtypeindex,
//					&M->weathernum,&M->windspeed,&M->winddirection,
//					&dummy,&M->region,&M->PlayerAcType,
//					&(UWord&)M->PlayerHomeBase,&(UWord&)M->EnemyHomeBase,
//					&(UWord&)M->MainObjective,&(UWord&)M->SubObjective,
//					&(UWord&)M->WP1,&(UWord&)M->WP2,&(UWord&)M->WP3
//					);
//			M->PlayerNationality&=31;M->formationtypeindex&=31;
		}
}

Bool	Persons2::make_agname(string src,int len,info_airgrp& A)
{
	if (!justscanning)
		if (len==4)
		{
			int	v=(src[1]&15)*100+(src[2]&15)*10+(src[3]&15);
			if (src[0]=='E')
				A.squadron=-v;
			else
				A.squadron=v;
		}
}

Bool	Persons2::make_eventname(string src,int len,info_event& E)
{
	if (justscanning==NAMESQUAD)
		if (selectedsquad--==0)
		{
			strncpy(keptstr,src,len);
			keptstr[len]=0;
		}
	if (!justscanning)
		if (len==4)
		{
			int	v=(src[1]&15)*100+(src[2]&15)*10+(src[3]&15);
			if (src[0]=='F')
				if (E.FrFighterSq)
					E.FrBomberSq=v;
				else
					E.FrFighterSq=v;
			else
			if (src[0]=='E')
				if (E.EnFighterSq)
					E.EnBomberSq=-v;
				else
					E.EnFighterSq=-v;
		}
//	if (justscanning==SELECTSQUAD)
		return TRUE;
//	else
  //	{	//need to generate squad number info here somehow!
	//	return FALSE;
//	}
}



//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//
//	UID/World interface
//
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴


ItemBasePtr		Persons2::ConvertPtrUID(UniqueID tmpUID)
{
	return(pItem[tmpUID]);
}

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
			uidbandmin[uidindex]=uidbandbase[uidindex];
			do{
				tempUID = (UniqueID) uidbandmin[uidindex];
				uidbandmin[uidindex] = (UniqueID)((int)uidbandmin[uidindex] + 1);
			}while (pItem[tempUID] && (int)tempUID<(int)uidbandmax[uidindex]);
		}
		if (tempUID==uidbandmax[uidindex])
		{
			uidbandmin[uidindex]=uidbandbase[uidindex];
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
		_Error.EmitSysErr("UIDband table overlap!");
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

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		logUID
//Author		Jim Taylor
//Date			Wed 18 Jun 1997
//
//Description	puts item in uid lookup
//
//Inputs
//
//Returns
//
//------------------------------------------------------------------------------
void	Persons2::logUID(ItemBasePtr	selecteditem)
{
    tabulateUID(selecteditem);
}
void	Persons2::tabulateUID(ItemBasePtr	selecteditem)

{
//	UidNode			*swapnode, **foundnode, *thenode, *nextnode, **rightmostnode;
	UniqueID		theuid;
  //	Bool			finished = FALSE;
  //	ItemBasePtr		*attackerptr;
  //	UILogType	 	request;

	theuid = selecteditem->uniqueID.count;

	assert(pItem[theuid]==NULL&&"UID already used!");

	assert(pItem[theuid]==0&&"Reused!");
	pItem[theuid] = selecteditem;

}

void	Persons2::delUID(UniqueID u)
{
	pItem[u]=NULL;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//
//	Runtime/endgame routines to getting info on items
//
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ItemStatus
//Author		Jim Taylor
//Date			Mon 30 Sep 1996
//
//Description	get and put statuses of items. Use in State3d destructor.
//
//Inputs		
//
//Returns
//
//------------------------------------------------------------------------------
ITEM_STATUS	Persons2::ItemStatus(UniqueID u,ITEM_STATUS s)
{

//DeadCode JIM 20Jun97 	ItemBasePtr	i=ConvertPtrUID(u);
//DeadCode JIM 20Jun97 	if (i)
//DeadCode JIM 20Jun97 	{
//DeadCode JIM 20Jun97 		ITEM_STATUS	rv=i->Status;
//DeadCode JIM 20Jun97 		i->Status.deadtime=s.deadtime;
//DeadCode JIM 20Jun97 		i->Status.deadscale=s.deadscale;
//DeadCode JIM 20Jun97 		return (rv);
//DeadCode JIM 20Jun97 	}
//	else
	{
		ITEM_STATUS	rv={FALSE};
		return rv;
	}
}

ITEM_STATUS	Persons2::ItemStatus(UniqueID u)
{
//DeadCode JIM 20Jun97 	ItemBasePtr	i=ConvertPtrUID(u);
//DeadCode JIM 20Jun97 	if (i)
//DeadCode JIM 20Jun97 		return (i->Status);
//DeadCode JIM 20Jun97 	else
	{
		ITEM_STATUS	rv={FALSE};
		return rv;
	}
}

ITEM_STATUS	Persons2::ConvoyStatus(UniqueID uid,UniqueID& nextwp,UniqueID& nextwptarg,SLong& livelength)
{
//DeadCode JIM 20Jun97 	FormationItemPtr	f=*ConvertPtrUID(uid);
//DeadCode JIM 20Jun97 	if (f)
//DeadCode JIM 20Jun97 	{
//DeadCode JIM 20Jun97 		livelength=0;
//DeadCode JIM 20Jun97 		WayPointPtr w=f->waypoint;
//DeadCode JIM 20Jun97
//DeadCode JIM 20Jun97 		nextwp=w->uniqueID.count;
//DeadCode JIM 20Jun97 		ItemBasePtr	i=w->target;
//DeadCode JIM 20Jun97 		if (i)
//DeadCode JIM 20Jun97 			nextwptarg=i->uniqueID.count;
//DeadCode JIM 20Jun97 		else
//DeadCode JIM 20Jun97 			nextwptarg=IllegalSepID;
//DeadCode JIM 20Jun97 		while (f)
//DeadCode JIM 20Jun97 		{
//DeadCode JIM 20Jun97 			if (f->Status.deadtime==0)
//DeadCode JIM 20Jun97 			  	livelength++;
//DeadCode JIM 20Jun97 			f=f->follower;
//DeadCode JIM 20Jun97 		}
//DeadCode JIM 20Jun97 		if (i)
//DeadCode JIM 20Jun97 			return (i->Status);
//DeadCode JIM 20Jun97 		else
//DeadCode JIM 20Jun97 			return (w->Status);
//DeadCode JIM 20Jun97 	}
//DeadCode JIM 20Jun97 	else
	{
		ITEM_STATUS	rv={FALSE};
		return rv;
	}
}

void Persons2::InitGamePiece()
{
	FILE* f=fopen("..\\h\\uidtops.g","rt");
	int i;
		fscanf(f,"%x %x",&i,&i);
	int c=-1;
	do
	{
		int i,j=0;
		fscanf(f,"%x %x",&i,&j);
		switch (i)
		{	//patch bands where we can have full spread.
//			case	RedGroundMobileBAND:
  //			case	BlueAcBAND:
	//		case	RedCivilianBAND:
	  //			uidbandmax[c]=i;			
		}
		c++;
		i=fgetc(f);
		uidbandmax[c]=j;
	}	while (c<2||uidbandmax[c]!=0);

	
}

void	Persons2::InitSubPiece()
{
}

void Persons2::EndSubPiece()
{
}
void Persons2::FinishSetPiece()
{
}

typedef void (*ha)(AirStrucPtr,FormationIndex,UByte* colours);
ha	Persons2::Colour_Rule_List[]
		={  NULL };

Bool	Persons2::anyoutstanding()	{return FALSE;}

//##void	Expr::printit(int indent,char name,int value)
//##{
//##}



 //
 //
 //
 //


int			GlobRefExpr::Evaluate(int)		{return Persons2::GetLoc(globrefind);}

UniqueID		UIDExpr::EvalW(Coords3D& c)
{
	ItemBasePtr p=Persons2::ConvertPtrUID(UniqueID(val.Evaluate(0)));
	if (p)
	{
		c=p->World;
		return UID_Null;
	}
	else
		return	UniqueID(val.Evaluate(0));
}
UniqueID		UIDExpr::EvalA(HP& c)
{
	ItemBasePtr p=Persons2::ConvertPtrUID(UniqueID(val.Evaluate(0)));
	if (p && (int)p->Status.size>=(int)HPSIZE)
	{
		hpitem* q=*p;
		c.H=q->hdg;
		c.P=q->pitch;
		return UID_Null;
	}
	return UniqueID(val.Evaluate(0));
}


UniqueID		RotExpr::EvalA(HP& c)
{
	if (icpt.complex)
	{
		HP a;
		UniqueID t=icpt.EvalA(a);
		if (t)	RETURN(t);
		int v1;
		if ((v1=hdg.Evaluate())!=ENABLE_COMPLEX_VAL)
			c.H=Angles(v1)+a.H;
		if ((v1=pitch.Evaluate())!=ENABLE_COMPLEX_VAL)
			c.P=Angles(v1)+a.P;
	}
	else
	{
		int v1;
		if ((v1=hdg.Evaluate())!=ENABLE_COMPLEX_VAL)
			c.H=Angles(v1);
		if ((v1=pitch.Evaluate())!=ENABLE_COMPLEX_VAL)
			c.P=Angles(v1);
	}
	return UID_Null;
}

UniqueID	RotExpr::EvalW(Coords3D& p)
{
	HP a;//={ANGLES_0Deg,ANGLES_0Deg};
	UniqueID	rv;
	if (!!(rv=EvalA(a)))
		RETURN(rv);
	int r=range.Evaluate(-1);
	if (r!=ENABLE_COMPLEX_VAL)
	{
		if (rangeispercent)
		{
			int l=icpt.Evaluate();
			if (l==ENABLE_COMPLEX_VAL)
				return IllegalSepID;		//THIS CAN'T HAPPEN!!!
			else
				if (l<0x100000)
					r=l*r/100;
				else
					r=l/100*r;
		}
		SWord	s,c;
		Math_Lib.sin_cos(a.P,s,c);
		int l=MULSHSIN(r,c,ANGLES_SHIFT);
		p.Y=MULSHSIN(r,s,ANGLES_SHIFT);
		Math_Lib.sin_cos(a.H,s,c);
		p.X=MULSHSIN(l,s,ANGLES_SHIFT);
		p.Z=MULSHSIN(l,c,ANGLES_SHIFT);
		return UID_Null;
	}
	else
		return IllegalSepID;
}

int		RotExpr::Evaluate(int)
{
	int r=range.Evaluate(-1);
	if (r!=ENABLE_COMPLEX_VAL)
		if (rangeispercent)
		{
			int l=icpt.Evaluate();
			if (l==ENABLE_COMPLEX_VAL)
				return l;
			else
				if (l<0x100000)
					return l*r/100;
				else
					return l/100*r;
		}
	return r;
}


UniqueID	IcptExpr::EvalW(Coords3D& c)
{
	Coords3D a,b;
	UniqueID	rv;
	if (objA.complex)
	{
		if (!!(rv=objA.EvalW(a)))
			return (rv);
	}
	else
	{
		UIDExpr u;
		u.val=objA.value;
		if (!!(rv=u.EvalW(a)))
			return rv;
	}

	if (objB.complex)
	{
		if (!!(rv=objB.EvalW(b)))
			return (rv);
	}
	else
	{
		UIDExpr u;
		u.val=objB.value;
		if (!!(rv=u.EvalW(b)))
			return rv;
	}
	c.X=b.X-a.X;
	c.Y=b.Y-a.Y;
	c.Z=b.Z-a.Z;
	return UID_Null;
}

UniqueID		IcptExpr::EvalA(HP& a)
{
	Coords3D d;
	UniqueID rv;
	if (!(rv=EvalW(d)))
	{
		long	range;
		Math_Lib.HighIntercept(d.X,d.Y,d.Z,range,a.H,a.P);
		return UID_Null;
	}
	else
		return rv;

}

int		IcptExpr::Evaluate(int)
{
	Coords3D d;
	if (!EvalW(d))
	{
		HP	a;
		long	range;
		Math_Lib.HighIntercept(d.X,d.Y,d.Z,range,a.H,a.P);
		return range;
	}
	else
		return ENABLE_COMPLEX_VAL;
}

int			RndExpr::Evaluate(int flag)		
{
	int	b=base.Evaluate(0);
	int s=stepsize.Evaluate(0);
	int m=maxsteps.Evaluate(0);
	if (b==ENABLE_COMPLEX_VAL)
		b=0;
	if (s==ENABLE_COMPLEX_VAL)
		s=1;
	if (m==ENABLE_COMPLEX_VAL)
		m=1;		

	if (flag<0)
		return b;
	else		
		return b+s*(m-1);
}

int			SelExpr::Evaluate(int)
{
	int b=base.Evaluate(0);
	if (b==ENABLE_COMPLEX_VAL)
		b=0;
	int s=stepsize.Evaluate(0);
	int m=steps.Evaluate(0);
	if (s==ENABLE_COMPLEX_VAL)
		if (m==ENABLE_COMPLEX_VAL)
			s=0;
		else
			s=1;
	else
	if (m==ENABLE_COMPLEX_VAL)
		m=1;
	return b+s*m;
}

UniqueID		WorldExpr::EvalW(Coords3D& c3)
{
	Coords3D	a={0,0,0},b=a,c=b;
	UniqueID rv=UID_Null;
	if (uniqueID.complex)
		rv=uniqueID.complex->EvalW(a);
	else if (uniqueID.value!=ENABLE_COMPLEX_VAL)
	{
		UIDExpr u;
		u.val=uniqueID;
		rv=u.EvalW(a);
	}
	if (rv)
		return (rv);

	if (deltaisabs && delta.complex && delta.complex->type==EXPR_XYZ)
	{
		XyzExpr* d=(XyzExpr*)delta.complex;
		int v;
		if ((v=d->X.Evaluate(-1))!=ENABLE_COMPLEX_VAL)
			if (v!=0)
			a.X=v;
		if ((v=d->Y.Evaluate(-1))!=ENABLE_COMPLEX_VAL)
			if (v!=0)
			a.Y=v;
		if ((v=d->Z.Evaluate(-1))!=ENABLE_COMPLEX_VAL)
			if (v!=0)
			a.Z=v;
	}
	else
		delta.EvalW(b);
	if (rotate.complex)
		rv=rotate.EvalW(c);
	if (rv)
		return rv;
	c3.X=a.X+b.X+c.X;
	c3.Y=a.Y+b.Y+c.Y;
	c3.Z=a.Z+b.Z+c.Z;

	return UID_Null;
}
  
//
//
//
//
extern error_sayandquit(char *);
 
Error	&	Error::SayAndQuit( char	*error, ... )	
{	
   va_list argptr;
   int cnt;
	char	buffer[1000];
   va_start(argptr, error);
   cnt = vsprintf(buffer, error, argptr);
   va_end(argptr);

	error_sayandquit(buffer);
	return(*this);
}
