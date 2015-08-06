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
//Filename       jimcol.cpp
//System         
//Author         Jim Taylor
//Date           Sun 24 Nov 1996
//Description    Jim's attempt at collision
//
//Missing features:
//1)	Not handling groups. 
//		Separate GroupCol should try quick cube trowout, and then call TestCol,
//		or parhaps a variant that inputs hitpos and shape ptr?
//
//2)	Not sure about units for shape stuff. 
//		Happy with vel scaling - assumed 1.25 * vel = 12 seconds delta
//
//3)	Not got hit box difficulty in. Just scale up the tsize record
//		Really want hardest to be slightly smaller
//
//		It *may* be optimal to make the bullet's size an input integer so that
//		the sector search only looks up the bullet shape once.
//
//------------------------------------------------------------------------------
#include	"dosdefs.h"
#include	"Collided.h"
#include	"worldinc.h"
#include	"shapes.h"
#include	"matrix.h"
#include	"3dcom.h"											//RJS 26Feb97
#include	"boxcol.h"											//RJS 26Feb97
#include	"savegame.h"
#include	"ranges.h"
#include	"winmove.h"											//ARM 01Dec96
#include	"flymodel.h"										//RJS 11Dec96
#include	"miles.h"											//RJS 27Feb97
#include	"transite.h"										//RJS 27Feb97
#include	"shpinstr.h"
#include	"persons2.h"
#include	"ai.h"												//RJS 22Jun98
#include	"replay.h"
#include	"anmradio.h"										//RJS 05Feb99
#include	"speed.h"											//RJS 20May99

//MATHABLE	(ANGLES);

#define		MIN_RUNWAYDAMAGE	8								//RJS 10Jun99
	static int n=0;

	Coords3D*	BoxCol::TPos1;
	Coords3D*	BoxCol::TPos2;
	Coords3D*	BoxCol::LastTSize;								//RJS 01Dec98
	int			BoxCol::TTrgSize;
	int			BoxCol::TSizeMul;
	EffectLine	BoxCol::EffectQueue[MaxEffects];
	int			BoxCol::EffectCnt;

	Coords3D	BoxCol::colpos_hitgrp;					//RJS 27Feb97
	Coords3D	BoxCol::colpos_hititem;					//RJS 27Feb97
	Coords3D	BoxCol::colpos_impact;					//RJS 27Feb97

	int			BoxCol::HitterStrength;					//RJS 06Mar97
	ItemPtr		BoxCol::Col_Hitter;						//RJS 07Mar97
	UByte		BoxCol::HitterDamageType;						//RJS 22Jan98
	int			BoxCol::Col_GroupElement;						//RJS 27Feb98
	UByteP		BoxCol::Col_GroupSdptr;							//RJS 27Feb98
	animptr		BoxCol::Col_AnimPtr;							//RJS 21Apr99
	animptr		BoxCol::Col_AnimPrevPtr;						//RJS 21Apr99
	animptr		BoxCol::Col_AnimNextPtr;						//RJS 21Apr99
	UByteP		BoxCol::Col_GroupPrev;							//RJS 03Mar98
	UByteP		BoxCol::Col_GroupNext;							//RJS 03Mar98
	SLong		BoxCol::StaticHitterSize;						//RJS 03Mar98
	ShapeDescPtr BoxCol::StaticTrgSdptr;						//RJS 03Mar98
	Bool		BoxCol::Col_ExplodeIt;							//RJS 30Mar98
	animptr		BoxCol::Col_TokenDepAnim;						//RJS 21Apr99
	ItemPtr		BoxCol::Col_Shooter;							//JIM 11Mar99
	SLong		BoxCol::noGuns;									//RJS 29Mar99
	UWord		BoxCol::Col_HitShape = 0;						//RJS 20May99
	MATRIX		BoxCol::frame1inverse_matrix;					//RJS 15Jun99
	Bool		BoxCol::matrixset;								//RJS 15Jun99
	SLong		BoxCol::StaticHitterSizeSingle;					//RJS 15Jun99
	SLong		BoxCol::pointindex;								//RJS 29Jun99
	Coords3D	BoxCol::colpos_list[MaxEffects];				//RJS 29Jun99
	SLong		BoxCol::ShoveX;									//RJS 29Jun99
	SLong		BoxCol::ShoveY;									//RJS 29Jun99
	SLong		BoxCol::ShoveZ;									//RJS 29Jun99

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		NineSectorCol
//Author		Jim Taylor
//Date			Wed 27 Nov 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
ItemPtr BoxCol::NineSectorCol(MobileItemPtr hitter,Coords3D& hitpos,int& eltnum)
{
	if (hitter->Status.size == TRANSIENTSIZE)					//AMM 27Aug98
	{
		TransientItemPtr	tmpitm = (TransientItemPtr) hitter;
		if (!tmpitm->CollTestEnabled)
			return(NULL);

		Col_Shooter = tmpitm->Launcher;
	}
	else
		Col_Shooter = hitter;

	n++;
	UWord	sector_x,
			sector_y;
	TransientItem*	lastbullet = NULL;							//RJS 29Mar99
	ShapeDescPtr	sdptr = SHAPESTUFF.GetShapePtr(hitter->shape);
	if (sdptr->AnimDataSize == MISSILEANIM)
	{
		MissileAnimData*	adptr = (MissileAnimData*) hitter->Anim;
		if (adptr->hitstrength)			//something to prove...
		{
//DeadCode DAW 23Jun99 			StaticHitterSize = sdptr->Size;
//DeadCode DAW 23Jun99 			HitterStrength = (adptr->hitstrength / 2);				//DAW 01Dec98
//DeadCode DAW 23Jun99 			SLong			newhitsize = (StaticHitterSize* 3);		//DAW 01Dec98
//DeadCode DAW 23Jun99 			SLong			maxsize = newhitsize + StaticHitterSize;//DAW 01Dec98
//DeadCode DAW 23Jun99 																	//DAW 01Dec98
//DeadCode DAW 23Jun99 			if (adptr->frameno)										//DAW 01Dec98
//DeadCode DAW 23Jun99 			{														//DAW 01Dec98
//DeadCode DAW 23Jun99 				newhitsize = (newhitsize * (adptr->frameno + 1));	//DAW 01Dec98
//DeadCode DAW 23Jun99 				StaticHitterSize += (newhitsize >>= 8);				//max frame is 256//DAW 01Dec98
//DeadCode DAW 23Jun99 																	//DAW 01Dec98
//DeadCode DAW 23Jun99 				HitterStrength = ((maxsize - StaticHitterSize) * HitterStrength)/newhitsize;//DAW 01Dec98
//DeadCode DAW 23Jun99 
//DeadCode DAW 23Jun99 				if (HitterStrength>31)
//DeadCode DAW 23Jun99 					HitterStrength=31;
//DeadCode DAW 23Jun99 			}														//DAW 01Dec98
			//Max strength is 4000 lb bomb (64)
			//... blast radius is 40m for 1000 lb bomb
			//... so real radius = (160m * hitstrength)/64;
			//Fall off max radius is 3/2 * blast radius
			//... so max damage radius for 1000 lb bomb is 60m

			SLong	blastsize = (16000 * adptr->hitstrength)>>6;
			if (blastsize)
			{
				SLong	newstrength = adptr->hitstrength;

				//blast lasts for 2 csecs, the rest is fall off...
				if (adptr->frameno > 2)
				{
					//fall of strength is not as strong...
					newstrength *= 3;
					newstrength >>= 2;

					//Fall off time is .5 sec
					SLong	falloffsize = blastsize / 2;
					SLong	blasttime = adptr->frameno;

					newstrength -= (blasttime * newstrength)/50;

					falloffsize *= blasttime;
					falloffsize /= 50;

					blastsize += falloffsize;
				}

				//for replay...
				if (newstrength > 31)	newstrength = 31;
				else
					if (newstrength < 0)	newstrength = 0;

				HitterStrength = newstrength;
				StaticHitterSize = blastsize >> 4;
			}
			else
				HitterStrength = 0;
			
			StaticHitterSizeSingle = StaticHitterSize;				//RJS 15Jun99
			noGuns = 1;
		}
		else
		{
			StaticHitterSizeSingle = (sdptr->sx+sdptr->sy)>>1;		//RJS 15Jun99
			//multiple gun???
			lastbullet = (TransientItem*) adptr->lastmissile;	//RJS 29Mar99
																//RJS 29Mar99
			noGuns = adptr->novirtualguns;						//RJS 29Mar99
			if (noGuns > 1)
				StaticHitterSize = (sdptr->sx+sdptr->sy) + (METRES05>>4);
			else
				StaticHitterSize = StaticHitterSizeSingle;			//RJS 15Jun99

			HitterStrength = SHAPESTUFF.GetShapeDamageStrength(hitter->shape);
		}														//DAW 01Dec98
	}															//DAW 01Dec98
	else														//DAW 01Dec98
	{															//DAW 01Dec98
		StaticHitterSize = StaticHitterSizeSingle = (sdptr->sx+sdptr->sy)>>1;	//RJS 15Jun99
		HitterStrength = SHAPESTUFF.GetShapeDamageStrength(hitter->shape);//DAW 01Dec98
		noGuns = 1;												//RJS 29Mar99
	}															//DAW 01Dec98

	//Only do collision with things that have damage potential...
	if (HitterStrength)														//RJS 18Feb99
	{
		Bool	isPlayer = FALSE;

		if (	(Col_Shooter == Persons2::PlayerSeenAC)						//RJS 27May99
			||	(Col_Shooter == Persons2::PlayerGhostAC)	)
			isPlayer = TRUE;

		hitter->currworld->getsectornos(hitter,sector_x,sector_y);
		int	currentsector = hitter->currworld->GetSector(hitter);					//PD 25Jun96
		ItemPtr trg;
		sector_x--;
		sector_y--;

	//DeadCode DAW 01Dec98 	HitterStrength = SHAPESTUFF.GetShapeDamageStrength(hitter->shape);//RJS 22Jan98
		HitterDamageType = SHAPESTUFF.GetShapeDamageType(hitter->shape);//RJS 22Jan98
		Col_Hitter = hitter;										//RJS 07Mar97
		Col_GroupElement = -1;										//RJS 27Feb98
		if (HitterDamageType == DMT_EXPLOSION)
			Col_ExplodeIt = TRUE;
		else
			Col_ExplodeIt = FALSE;

		for (int i=11;i>0;i--,sector_x++,sector_y-=3)
			for (;i&3;i--,sector_y++)
		{
			Bool hittersector;
			int	thissector=hitter->currworld->makeindex(sector_x,sector_y);
			hittersector=(thissector==currentsector)?TRUE:FALSE;
			trg=hitter->currworld->getfirstitem(thissector);
			trg=SectorCol(hitter,trg,hitpos,eltnum,hittersector,lastbullet,isPlayer);//RJS 27May99
			if (trg)
			{
//DeadCode DAW 15Jun99 #ifndef NDEBUG
//DeadCode DAW 15Jun99 	if (isPlayer)
//DeadCode DAW 15Jun99 	{
//DeadCode DAW 15Jun99 		UWord	cw=GETFPCW();
//DeadCode DAW 15Jun99 		::AfxTrace("GOOD HIT!!: 0x%x\n",trg);
//DeadCode DAW 15Jun99 		SETFPCW(cw);
//DeadCode DAW 15Jun99 	}
//DeadCode DAW 15Jun99 #endif

	//			*(char*)(0xb0000+160*24+100)='C';
				ProcessEffectQueue(trg);
	//			*(char*)(0xb0000+160*24+100)='D';
				return(trg);
			}
		}
	}

	return(NULL);
}
//////////////////////////////////////////////////////////////////////
//
// Function:    TargetAllowed
// Date:		07/04/99
// Author:		JIM
//
//Description: 
//
//////////////////////////////////////////////////////////////////////
static bool	TargetAllowed(MobileItemPtr hitter,ItemPtr trg,SLong strength)
{
	if ((hitter->Status.size!=TRANSIENTSIZE) || (strength < MIN_RUNWAYDAMAGE))//RJS 10Jun99
	{
		int trgid=(trg->uniqueID.count);
		if (trgid<AmberAirfieldBAND)		return true;			//1200-1400
//DEADCODE DAW 26/04/99 #pragma warnmsg("Enable this clause when runways are airfield keys")
		if (trgid<AmberAirfieldBANDEND && !trg->SGT)		return false;			//1200-1400
		if (trgid<AmberBattleNodeBAND)		return true;		//2880-2B00
		if (trgid<AmberBattleNodeBANDEND)	return false;
		if (trgid<RunwaySBAND)				return true;			//1200-1400
		if (trgid<RunwayEBANDEND)			return false;			//1200-1400
//DeadCode RJS 18Jun99 		if (trgid<AfRunwayBAND)				return true;			//1200-1400
//DeadCode RJS 18Jun99 		if (trgid<AfRunwayBANDEND)			return false;			//1200-1400
		return true;
	}
	else
	{
		int trgid=(trg->uniqueID.count);

		if (trgid<AmberBattleNodeBAND)		return true;		//2880-2B00
		if (trgid<AmberBattleNodeBANDEND)	return false;
		if (trgid<RunwaySBAND)				return true;			//1200-1400
		if (trgid<RunwayEBANDEND)			return false;			//1200-1400
		return true;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SectorCol
//Author		R. Hyde 
//Date			Tue 26 Nov 1996
//
//Description	
//Modified		Rejects collision with shapes not in the hitters sector//PD 03Dec96
//
//Inputs		Trg is first entry in a sector list
//
//Returns	
//
//------------------------------------------------------------------------------
ItemPtr BoxCol::SectorCol(	MobileItemPtr hitter,
							ItemPtr trg,
							Coords3D& hitpos,
							int& eltnum,
							Bool hittersector,
							TransientItem* lastbullet,
							Bool			isPlayer	)
{
	ItemBasePtr launcher=NULL;
	if (hitter->Status.size==TRANSIENTSIZE)
		launcher=((TransientItemPtr)*hitter)->Launcher;
	while (trg)
	{
		if (	(trg != Manual_Pilot.ControlledAC2)				//RJS 11Dec96
			|| Save_Data.gamedifficulty[GD_VULNERABLE])			//RJS 11Dec96
		{
			if ((trg->Status.size == AirStrucSize) || (hitter->World.Y < HIGHESTGROUND))//RJS 21May99
			{
				StaticTrgSdptr=SHAPESTUFF.GetShapePtr(trg->shape);	//RJS 03Mar98
 				if (hittersector || SHAPESTUFF.GetShapeScale(StaticTrgSdptr)==SHP_GRP)//RJS 03Mar98
					if (trg->Status.size != AirStrucSize || ((AirStrucPtr)trg)->movecode != AUTO_RESURRECT )
						if (trg!=hitter && trg != launcher && trg->Status.size!=TRANSIENTSIZE)//ARM 10Dec96
							if (TargetAllowed(hitter,trg,HitterStrength))		  //DAW 07/04/99//RJS 10Jun99
								if (GroupCol(hitter,trg,hitpos,eltnum,lastbullet,isPlayer)) 
									return(trg);
			}
		}
		trg=trg->Next;
	}
	return(NULL);
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GroupCol
//Author		Jim Taylor
//Date			Wed 27 Nov 1996
//
//Description	
//
//Inputs		
//
//Returns		EltNum = -1 if non group item!!!!!
//
//------------------------------------------------------------------------------
Bool BoxCol::GroupCol(MobileItemPtr hitter,ItemPtr trg,Coords3D& hitpos,int& eltnum, TransientItem* lastbullet, Bool isPlayer)
{

//DeadCode RJS 03Mar98 	ShapeDescPtr sdptr=SHAPESTUFF.GetShapePtr(trg->shape);
	Col_GroupElement = -1;										//RJS 24Jun99
	if (trg->World.Y==0)
		trg->World.Y=_Collide.AccurateGroundAltitude(trg->World);

	colpos_hititem = hitter->World;								//RJS 02Dec98
	eltnum=-1;													//JIM 27Nov96
	if (SHAPESTUFF.GetShapeScale(StaticTrgSdptr)==SHP_GRP)		//RJS 03Mar98
	{
		UByte *iptr = (UByte *)StaticTrgSdptr + StaticTrgSdptr->liveshpref;//RJS 03Mar98
		int	hitsize = StaticTrgSdptr->Size * 20+METRES50;		//RJS 03Mar98

		if (	trg->World.X-hitter->World.X>hitsize
			||	trg->World.X-hitter->World.X<-hitsize
			)
			return(FALSE);
		if (	trg->World.Z-hitter->World.Z>hitsize
			||	trg->World.Z-hitter->World.Z<-hitsize
			)
			return(FALSE);

		//Make sure they all get set up...						//RJS 21Apr99
		Col_AnimPtr = trg->Anim;								//RJS 21Apr99
		Col_AnimNextPtr = trg->Anim;							//RJS 21Apr99
		Col_AnimPrevPtr = trg->Anim;							//RJS 21Apr99
		Col_TokenDepAnim = trg->Anim;							//RJS 21Apr99
		Col_TokenDepAnim = (UByteP)NULL;						//RJS 21Apr99

		int	groupindex = -1;
		MinAnimData*	mad = (MinAnimData*) trg->Anim;
		Coords3D		centrepoint=trg->World;
		ShapeNum		newshape,
						groupshp=trg->shape;
		SLong			ex,ey,ez;
		UByteP			PrevIptr;
		RotItemPtr		TmpItmPtr = new rotitem;
		SLong			yDelta;									//DAW 01Dec98
		animptr			tmpanim;								//RJS 21Apr99
		Coords3D		testpos;								//DAW 01Dec98
		ULong			tokenoffset;							//RJS 12Feb99
		UByteP			anmstart = (UByteP)mad;					//RJS 12Feb99
		animptr			Tmp_AnimNextPtr = trg->Anim;			//RJS 28Apr99
		bool			doTest;

		TmpItmPtr->World = trg->World;
		TmpItmPtr->Anim = trg->Anim;
		TmpItmPtr->shape = trg->shape;

		TmpItmPtr->roll = ANGLES_0Deg;
		TmpItmPtr->pitch = ANGLES_0Deg;

		Col_GroupPrev = NULL;
		Col_AnimPrevPtr = (UByteP)NULL;									//RJS 02Mar98
		Col_AnimNextPtr = (UByteP)NULL;							//RJS 28Apr99
		Col_GroupSdptr = (UByteP) StaticTrgSdptr;				//RJS 03Mar98

		while(SHAPE.GetGroupElementToken(iptr,newshape,ex,ey,ez,0,&PrevIptr,(SWordP)&TmpItmPtr->hdg,tokenoffset,Col_GroupNext))//RJS 30Jun99
		{
			groupindex++;											

//DeadCode RJS 30Jun99			Col_GroupNext = iptr + 1;
			mad = (MinAnimData*) Tmp_AnimNextPtr;
			Col_AnimPtr = &Tmp_AnimNextPtr;		//only assign new ptr, not size!
//DeadCode RJS 02Jul99 //			tmpanim = Col_AnimPtr;								//DAW 01Dec98
			Tmp_AnimNextPtr += SHAPE.GetElementAnimOffset(newshape);
			Col_AnimNextPtr = &Tmp_AnimNextPtr;
			if ((mad->itemstate != DEAD) && (mad->IsBullied==0))//RJS 03Dec98
			{
				doTest = true;
//DeadCode RJS 15Jun99 				StaticTrgSdptr = SHAPESTUFF.GetShapePtr(newshape);//RJS 03Mar98
//DeadCode RJS 15Jun99 
//DeadCode RJS 15Jun99 				testpos.X = ex+centrepoint.X;					//DAW 01Dec98
//DeadCode RJS 15Jun99 				testpos.Y = ey+centrepoint.Y;					//DAW 01Dec98
//DeadCode RJS 15Jun99 				testpos.Z = ez+centrepoint.Z;					//DAW 01Dec98
//DeadCode RJS 15Jun99 
//DeadCode RJS 15Jun99 				tmpanim = Col_AnimPtr;								//DAW 01Dec98
//DeadCode RJS 15Jun99 												//DAW 01Dec98
//DeadCode RJS 15Jun99 				//Eliminate delta height cock-ups.
//DeadCode RJS 15Jun99 				yDelta = SHAPE.GetElementYDelta(newshape,tmpanim,testpos,centrepoint.Y);//RJS 09Jun99
//DeadCode RJS 15Jun99 				yDelta <<= 4;									//DAW 01Dec98
//DeadCode RJS 15Jun99 
//DeadCode RJS 15Jun99 				TmpItmPtr->World = testpos;						//DAW 01Dec98
//DeadCode RJS 15Jun99 				TmpItmPtr->World.Y += yDelta;					//DAW 01Dec98
//DeadCode RJS 15Jun99 				TmpItmPtr->shape=newshape;

				if (tokenoffset)								//RJS 12Feb99
				{
					// Are we fully protected by daddy?
					Col_TokenDepAnim = (UByteP)anmstart+tokenoffset-1;	//RJS 12Feb99
					if (((MinAnimData*)Col_TokenDepAnim)->itemstate == BS_ALIVE)
					{											//RJS 15Jun99
						Col_TokenDepAnim = (UByteP)NULL;		//RJS 15Jun99
						doTest = false;							//RJS 15Jun99
					}
				}
				else											//RJS 12Feb99
					Col_TokenDepAnim = (UByteP)NULL;					//RJS 30Apr99

				Col_GroupElement = groupindex;					//RJS 27Feb98
				if (doTest)										//RJS 15Jun99
				{
					StaticTrgSdptr = SHAPESTUFF.GetShapePtr(newshape);

					testpos.X = ex+centrepoint.X;
					testpos.Y = ey+centrepoint.Y;
					testpos.Z = ez+centrepoint.Z;

					tmpanim = Col_AnimPtr;
									
					yDelta = SHAPE.GetElementYDelta(newshape,tmpanim,testpos,centrepoint.Y);
					yDelta <<= 4;

					TmpItmPtr->World = testpos;
					TmpItmPtr->World.Y += yDelta;
					TmpItmPtr->shape=newshape;


					Bool hit=TestCol(hitter,TmpItmPtr,trg,hitpos,lastbullet,isPlayer);//RJS 27May99
					if (hit)
					{
						Col_HitShape = newshape;					//RJS 20May99

						TmpItmPtr->Anim = NULL;
						delete TmpItmPtr;
						eltnum=groupindex;
						return(TRUE);
					}
				}
			}
			Col_AnimPrevPtr = (UByteP) mad;							//RJS 02Mar98
			Col_GroupPrev = PrevIptr;
//DeadCode RJS 15Jun99 //			groupindex++;											//RJS 02Oct96
		}
		TmpItmPtr->Anim = NULL;
		delete TmpItmPtr;
		return(FALSE);
	}
	else
	{
		Col_AnimPtr = trg->Anim;								//RJS 27Feb98
		Col_AnimNextPtr = NULL;
		Col_AnimPrevPtr = NULL;

		MinAnimData*	mad = (MinAnimData*) Col_AnimPtr;		//RJS 03Dec98
		if ((mad->IsBullied==0) && (mad->itemstate != DEAD))	//RJS 07Dec98
		{														//RJS 03Dec98
			if (TestCol(hitter,trg,trg,hitpos,lastbullet,isPlayer))	//RJS 27May99
			{
				Col_HitShape = trg->shape;						//RJS 20May99
				return(TRUE);									//RJS 03Dec98
			}
			else												//RJS 03Dec98
				return(FALSE);									//RJS 03Dec98
		}														//RJS 03Dec98
		else													//RJS 03Dec98
			return(FALSE);										//RJS 03Dec98
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		TestCol
//Author		Jim Taylor
//Date			Sun 24 Nov 1996
//
//Description	Test collision of mobile against unknown
//
//Limitations:	Bullet velocity is limited to mach3 - delta <250m
//				Object size limmited to 2.5KM radius in easy throwout
//				Max dist of bullet on any 1 axis is 256Kcm= 2.62 KM
//
//				I don't think the trg shape will ever be a group at this point..
//Inputs		
//
//Returns									        
//
//------------------------------------------------------------------------------
Bool	BoxCol::TestCol(MobileItemPtr 	hitter,
						ItemPtr 		trgTest,
						ItemPtr 		trgReal,
						Coords3D& 		hitpos,
						TransientItem*	lastbullet,
						Bool			isPlayer	)
{
	Bool	isMobile = FALSE;									//RJS 29Mar99
	Bool	isRotated;											//RJS 29Mar99
	Coords3D hit2;
	int i;
	int sh=0;
	int	sizemul = 16;											//RJS 27May99
	if (hitter->Status.size!=TRANSIENTSIZE)
	{
		sh=2;
		i=hitter->velx;
		i-=i>>3;													//DAW 01Dec98
		i>>=sh;
		hit2.X=(hitpos.X=hitter->World.X-trgTest->World.X)+i;		//RJS 16Nov98
		i=hitter->vely;
		i-=i>>3;													//DAW 01Dec98
		i>>=sh;
		hit2.Y=(hitpos.Y=hitter->World.Y-trgTest->World.Y)+i;		//RJS 16Nov98
		i=hitter->velz;
		i-=i>>3;
		i>>=sh;
		hit2.Z=(hitpos.Z=hitter->World.Z-trgTest->World.Z)+i;		//RJS 16Nov98

		if (trgTest->Status.size>=MOBILESIZE)					//RJS 16Nov98
		{
			MobileItemPtr trg2=*trgTest;
			i=trg2->velx;
			i-=i>>3;											//DAW 01Dec98
			i>>=sh;
			hit2.X-=i;
			i=trg2->vely;
			i-=i>>3;											//DAW 01Dec98
			i>>=sh;
			hit2.Y-=i;
			i=trg2->velz;
			i-=i>>3;											//DAW 01Dec98
			i>>=sh;
			hit2.Z-=i;

			isMobile = TRUE;									//RJS 29Mar99
		}
	}
	else
	{
		i=hitter->velx;
		i+=i>>2;													//DAW 01Dec98
		hit2.X=(hitpos.X=hitter->World.X-trgTest->World.X)+i;		//RJS 16Nov98
		i=hitter->vely;
		i+=i>>2;													//DAW 01Dec98
		hit2.Y=(hitpos.Y=hitter->World.Y-trgTest->World.Y)+i;		//RJS 16Nov98
		i=hitter->velz;
		i+=i>>2;
		hit2.Z=(hitpos.Z=hitter->World.Z-trgTest->World.Z)+i;		//RJS 16Nov98

		if (trgTest->Status.size>=MOBILESIZE)					//RJS 16Nov98
		{
			MobileItemPtr trg2=*trgTest;
			i=trg2->velx;
			i+=i>>2;											//DAW 01Dec98
			hit2.X-=i;
			i=trg2->vely;
			i+=i>>2;											//DAW 01Dec98
			hit2.Y-=i;
			i=trg2->velz;
			i+=i>>2;											//DAW 01Dec98
			hit2.Z-=i;

			isMobile = TRUE;									//RJS 29Mar99
		}
		else
			StaticHitterSize = StaticHitterSizeSingle;			//RJS 15Jun99

		//this option is only for aircraft hit by the player...	//RJS 27May99
		if (	(trgReal->Status.size == AIRSTRUCSIZE)			//RJS 27May99
			&&	isPlayer								)		//RJS 27May99
		{
			switch (Save_Data.targetsize)				
			{
				case TS_LARGE:
					sizemul=48;			//rdh9/12/98
					break;
				case TS_MEDIUM:
					sizemul=32;			//rdh9/12/98
					break;
			}
		}
	}




	Coords3D tsize;
//DeadCode RJS 03Mar98 	ShapeDescPtr	sdptr;
//DeadCode RJS 27May99 
//DeadCode RJS 27May99 	int	sizemul;												//DAW 18May99
{
//DeadCode DAW 18May99 	int	sizemul;
//DeadCode RJS 27May99 	if ((hitter->Status.size!=TRANSIENTSIZE) || (trgReal->Status.size != AIRSTRUCSIZE))	//RJS 25May99
//DeadCode RJS 27May99 		sizemul=16;
//DeadCode RJS 27May99 	else
//DeadCode RJS 27May99 		switch (Save_Data.targetsize)								//PD 02Sep96
//DeadCode RJS 27May99 		{
//DeadCode RJS 27May99 			case TS_LARGE:
//DeadCode RJS 27May99 				sizemul=48;			//rdh9/12/98
//DeadCode RJS 27May99 				break;
//DeadCode RJS 27May99 			case TS_MEDIUM:
//DeadCode RJS 27May99 				sizemul=32;			//rdh9/12/98
//DeadCode RJS 27May99 				break;
//DeadCode RJS 27May99 			default:
//DeadCode RJS 27May99 				sizemul=16;			//rdh9/12/98
//DeadCode RJS 27May99 				break;
//DeadCode RJS 27May99 		}															//PD 02Sep96
//DeadCode RJS 27May99 
//DeadCode RJS 27May99 	// fiddle!!!!
//DeadCode RJS 27May99 //	sizemul = 16;

	SLong	side=(StaticHitterSize+StaticTrgSdptr->Size)*sizemul;//RJS 03Mar98


	tsize.X=(StaticTrgSdptr->sx+StaticHitterSize)*sizemul;		//RJS 03Mar98
	tsize.Y=(StaticTrgSdptr->sy+StaticHitterSize)*sizemul;		//RJS 03Mar98
	tsize.Z=(StaticTrgSdptr->sz+StaticHitterSize)*sizemul;		//RJS 03Mar98

	TTrgSize = StaticHitterSize;								//RJS 03Mar98
	TSizeMul = sizemul;

	if (!TestCube(&hitpos,&hit2,side))
		return(FALSE);
}

//DeadCode DAW 15Jun99 #ifndef NDEBUG
//DeadCode DAW 15Jun99 	if (isPlayer)
//DeadCode DAW 15Jun99 	{
//DeadCode DAW 15Jun99 		UWord	cw=GETFPCW();
//DeadCode DAW 15Jun99 		::AfxTrace("HIT OUTER!: 0x%x  %d  %d\n",trgReal,StaticHitterSize,sizemul);
//DeadCode DAW 15Jun99 		SETFPCW(cw);
//DeadCode DAW 15Jun99 	}
//DeadCode DAW 15Jun99 #endif


	MATRIX	viewer_matrix;										//RJS 29Mar99
//DeadCode DAW 17Jun99 	FPMATRIX	fpviewer_matrix;										//RJS 29Mar99

	isRotated = FALSE;
	if (trgTest->Status.size>=ROTATEDSIZE)						//RJS 16Nov98
	{
		RotItemPtr trg2=*trgTest;
		if (trg2->hdg || trg2->pitch || trg2->roll)
		{
			ANGLES		hdgflip,pitchflip,rollflip;					//RJS 29Mar99
			hdgflip = ANGLES_0Deg-trg2->hdg;									//RJS 25Feb97
			pitchflip = ANGLES_0Deg-trg2->pitch;								//RJS 25Feb97
			rollflip = ANGLES_0Deg-trg2->roll;									//RJS 25Feb97

			_matrix.generate(	hdgflip,							//RJS 25Feb97
						 		pitchflip,							//RJS 25Feb97
								rollflip,							//RJS 25Feb97
								&viewer_matrix);									//PD 20Dec95
			int scalefactor;
			scalefactor =16+ _matrix.transform(&viewer_matrix,hitpos.X,hitpos.Y,hitpos.Z);//PD 31Oct95
			hitpos.X>>=scalefactor;
			hitpos.Y>>=scalefactor;
			hitpos.Z>>=scalefactor;
			scalefactor =16+ _matrix.transform(&viewer_matrix,hit2.X,hit2.Y,hit2.Z);//PD 31Oct95
			hit2.X>>=scalefactor;
			hit2.Y>>=scalefactor;
			hit2.Z>>=scalefactor;
			isRotated = TRUE;
//DeadCode DAW 15Jun99 #ifndef NDEBUG
//DeadCode DAW 15Jun99 	if (isPlayer)
//DeadCode DAW 15Jun99 	{
//DeadCode DAW 15Jun99 		UWord	cw=GETFPCW();
//DeadCode DAW 15Jun99 		::AfxTrace("ROTATED!\n");
//DeadCode DAW 15Jun99 		SETFPCW(cw);
//DeadCode DAW 15Jun99 	}
//DeadCode DAW 15Jun99 #endif
		}
	}

	Bool retval = FALSE;												//RJS 10Jun99

	//Passed outer box test...
	// If not hit a mobile, don't fan bullets, cos its cheaper...
	if (!isMobile)
	{
		if (lastbullet)
		{
			//Remove the anim link list reference too!
			MissileAnimData*	adptr = (MissileAnimData*)hitter->Anim;	//RJS 27Apr99
			adptr->lastmissile = 0;										//RJS 27Apr99

			lastbullet->isOwned = 0;
			lastbullet = NULL;
		}
	}
	else
	{
		SLong	randval = Math_Lib.rnd();	
		ShoveX = (randval & 31) - 16;
		randval >>= 5;
		ShoveY = (randval & 31) - 16;
		randval >>= 5;
		ShoveZ = (randval & 31) - 16;
	}

	//Moved from docollision...
	colpos_hitgrp = trgTest->World;								//RJS 18Jun99

	// Do fan...
	matrixset = FALSE;											//RJS 15Jun99
	pointindex = -1;											//RJS 29Jun99
	if (lastbullet && (noGuns > 1))
	{
		SLong		bdeltx,bdelty,bdeltz;
		SLong		h2deltx,h2delty,h2deltz;
		Coords3D	backpos = hitpos;
		Coords3D	h2backpos = hit2;
		Coords3D	hitlastpos;

		i=hitter->velx;
		i+=i>>2;													
		hit2.X=(hitlastpos.X=lastbullet->World.X-trgTest->World.X)+i;		
		i=hitter->vely;
		i+=i>>2;													
		hit2.Y=(hitlastpos.Y=lastbullet->World.Y-trgTest->World.Y)+i;		
		i=hitter->velz;
		i+=i>>2;
		hit2.Z=(hitlastpos.Z=lastbullet->World.Z-trgTest->World.Z)+i;		

		if (isMobile)	
		{
			MobileItemPtr trg2=*trgTest;
			i=trg2->velx;
			i+=i>>2;											
			hit2.X-=i;
			i=trg2->vely;
			i+=i>>2;											
			hit2.Y-=i;
			i=trg2->velz;
			i+=i>>2;											
			hit2.Z-=i;
		}

		if (isRotated)
		{
			SLong scalefactor =16+ _matrix.transform(&viewer_matrix,hitlastpos.X,hitlastpos.Y,hitlastpos.Z);//RJS 29Mar99
			hitlastpos.X>>=scalefactor;
			hitlastpos.Y>>=scalefactor;
			hitlastpos.Z>>=scalefactor;
			scalefactor =16+ _matrix.transform(&viewer_matrix,hit2.X,hit2.Y,hit2.Z);//PD 31Oct95
			hit2.X>>=scalefactor;
			hit2.Y>>=scalefactor;
			hit2.Z>>=scalefactor;
		}

		TTrgSize -= (METRES05>>4);
		TTrgSize >>= 1;
//DeadCode RJS 15Jun99 //		StaticHitterSize -= (METRES05>>4);
//DeadCode RJS 15Jun99 //		StaticHitterSize>>=1;

		bdeltx = (hitlastpos.X - hitpos.X)/noGuns;
		bdelty = (hitlastpos.Y - hitpos.Y)/noGuns;
		bdeltz = (hitlastpos.Z - hitpos.Z)/noGuns;

		h2deltx = (hit2.X - h2backpos.X)/noGuns;
		h2delty = (hit2.Y - h2backpos.Y)/noGuns;
		h2deltz = (hit2.Z - h2backpos.Z)/noGuns;

		EffectCnt = 0;												//RJS 06Jun99
		Bool		tmpretval;															//RJS 10Jun99
		for (int gunno=0; gunno < noGuns; gunno++)
		{
			hitpos = backpos;
			hit2 = h2backpos;

			tmpretval = DoCollision(hitpos,hit2,tsize,trgTest,trgReal,hitter,sizemul);//RJS 10Jun99
			if (tmpretval)																//RJS 10Jun99
				retval = TRUE;															//RJS 10Jun99

			backpos.X += bdeltx;
			backpos.Y += bdelty;
			backpos.Z += bdeltz;

			h2backpos.X += h2deltx;
			h2backpos.Y += h2delty;
			h2backpos.Z += h2deltz;
		}

		lastbullet->isOwned = 0;
		lastbullet = NULL;
		//Remove the anim link list reference too!
		MissileAnimData*	adptr = (MissileAnimData*)hitter->Anim;	//RJS 27Apr99
		adptr->lastmissile = 0;										//RJS 27Apr99
	}
	else
	{
		EffectCnt = 0;												//RJS 06Jun99
		retval = DoCollision(hitpos,hit2,tsize,trgTest,trgReal,hitter,sizemul);//RJS 18May99
	}

	return (retval);

//DeadCode RJS 16Nov98	if (Col_GroupElement > -1)
//DeadCode RDH 30Mar99 	SHAPE.SetGroupDamage(Col_GroupElement,Col_GroupPrev,Col_GroupNext,Col_AnimPrevPtr,Col_AnimNextPtr,Col_TokenDepAnim);//RJS 12Feb99
//DeadCode RDH 30Mar99 
//DeadCode RDH 30Mar99 	Bool retval;
//DeadCode RDH 30Mar99 //	*(char*)(0xb0000+160*24+100)='A';	
//DeadCode RDH 30Mar99 	if (StaticTrgSdptr->CollisionOffset)						//RJS 03Mar98
//DeadCode RDH 30Mar99 	{
//DeadCode RDH 30Mar99 		TPos1 = &hitpos;
//DeadCode RDH 30Mar99 		TPos2 = &hit2;
//DeadCode RDH 30Mar99 		LastTSize = &tsize;										//DAW 01Dec98
//DeadCode RDH 30Mar99 		EffectCnt = 0;
//DeadCode RDH 30Mar99 
//DeadCode RDH 30Mar99 		retval=SHAPE.TestHitBoxes(trgReal,trgTest->shape,Col_AnimPtr,(UByteP)StaticTrgSdptr);//RJS 16Nov98
//DeadCode RDH 30Mar99 	}
//DeadCode RDH 30Mar99 	else
//DeadCode RDH 30Mar99 		retval=TestCol(&hitpos,&hit2,&tsize);
//DeadCode RDH 30Mar99 
//DeadCode RDH 30Mar99 	if (retval)
//DeadCode RDH 30Mar99 	{
//DeadCode RDH 30Mar99 		// Had a hit.....
//DeadCode RDH 30Mar99 
//DeadCode RDH 30Mar99 		SHAPE.FixUpColLog();
//DeadCode RDH 30Mar99 		if (trgTest->Status.size>=ROTATEDSIZE)					//RJS 16Nov98
//DeadCode RDH 30Mar99 		{
//DeadCode RDH 30Mar99 			RotItemPtr trg2=*trgTest;							//RJS 16Nov98
//DeadCode RDH 30Mar99 			MATRIX inverse_matrix;
//DeadCode RDH 30Mar99 
//DeadCode RDH 30Mar99 			_matrix.inverse(hdgflip,							//RJS 25Feb97
//DeadCode RDH 30Mar99 							pitchflip,							//RJS 25Feb97
//DeadCode RDH 30Mar99 							rollflip,							//RJS 25Feb97
//DeadCode RDH 30Mar99 							&inverse_matrix);								//PD 20Dec95
//DeadCode RDH 30Mar99 			int scalefactor;
//DeadCode RDH 30Mar99 			scalefactor =16+ _matrix.transform(&inverse_matrix,hitpos.X,hitpos.Y,hitpos.Z);//PD 31Oct95
//DeadCode RDH 30Mar99 
//DeadCode RDH 30Mar99 			hitpos.X>>=scalefactor;
//DeadCode RDH 30Mar99 			hitpos.Y>>=scalefactor;
//DeadCode RDH 30Mar99 			hitpos.Z>>=scalefactor;
//DeadCode RDH 30Mar99 		}
//DeadCode RDH 30Mar99 		hitpos.X+=trgTest->World.X;								//RJS 16Nov98
//DeadCode RDH 30Mar99 		hitpos.Y+=trgTest->World.Y;								//RJS 16Nov98
//DeadCode RDH 30Mar99 		hitpos.Z+=trgTest->World.Z;								//RJS 16Nov98
//DeadCode RDH 30Mar99 
//DeadCode RDH 30Mar99 		colpos_impact = hitpos;
//DeadCode RDH 30Mar99 		colpos_hitgrp = trgTest->World;							//RJS 16Nov98
//DeadCode RDH 30Mar99 	}
//DeadCode RDH 30Mar99 	else
//DeadCode RDH 30Mar99 	{
//DeadCode RDH 30Mar99 		//near miss...
//DeadCode RDH 30Mar99 		// Had a near miss...
//DeadCode RDH 30Mar99 		if (	(trgTest->Status.size == AirStrucSize)			//RJS 16Nov98
//DeadCode RDH 30Mar99 			&&	(hitter->Status.size == TransientSize)	)				//RJS 22Jun98
//DeadCode RDH 30Mar99 		{
//DeadCode RDH 30Mar99 			if (_Replay.Record || _DPlay.Implemented)
//DeadCode RDH 30Mar99 			{
//DeadCode RDH 30Mar99 // only do near misses of players bullets against AI AC
//DeadCode RDH 30Mar99 
//DeadCode RDH 30Mar99 				if (trgTest!=Persons2::PlayerSeenAC				//RJS 16Nov98
//DeadCode RDH 30Mar99 				&&	!trgTest->uniqueID.commsmove)				//RJS 16Nov98
//DeadCode RDH 30Mar99 				{
//DeadCode RDH 30Mar99 // only store if this players bullet caused nearmiss
//DeadCode RDH 30Mar99 
//DeadCode RDH 30Mar99 					if ((AirStrucPtr)(((TransientItemPtr)hitter)->Launcher)==Persons2::PlayerSeenAC)
//DeadCode RDH 30Mar99 					{
//DeadCode RDH 30Mar99 // dont store if targets ai.unfriendly is player
//DeadCode RDH 30Mar99 						if (((AirStrucPtr)trgTest)->ai.unfriendly!=Persons2::PlayerSeenAC)//AMM12Jan99
//DeadCode RDH 30Mar99 						{
//DeadCode RDH 30Mar99 							_DPlay.NewNearMiss((AirStrucPtr)trgTest,(AirStrucPtr)((TransientItemPtr)hitter)->Launcher);//RJS 16Nov98
//DeadCode RDH 30Mar99 						}
//DeadCode RDH 30Mar99 					}
//DeadCode RDH 30Mar99 					else
//DeadCode RDH 30Mar99 					{
//DeadCode RDH 30Mar99 // dont process if bullet is a comms bullet
//DeadCode RDH 30Mar99 						
//DeadCode RDH 30Mar99 						if (((TransientItemPtr)hitter)->CollTestEnabled)
//DeadCode RDH 30Mar99 						{
//DeadCode RDH 30Mar99 							Art_Int.PersonalThreat((AirStrucPtr)trgTest,(AirStrucPtr)((TransientItemPtr)hitter)->Launcher);//RJS 16Nov98
//DeadCode RDH 30Mar99 						}
//DeadCode RDH 30Mar99 					}
//DeadCode RDH 30Mar99 				}
//DeadCode RDH 30Mar99 			}
//DeadCode RDH 30Mar99 			else
//DeadCode RDH 30Mar99 			{
//DeadCode RDH 30Mar99 				if (!_Replay.Playback)
//DeadCode RDH 30Mar99 				{
//DeadCode RDH 30Mar99 // standard game - do all near misses
//DeadCode RDH 30Mar99 
//DeadCode RDH 30Mar99 					Art_Int.PersonalThreat((AirStrucPtr)trgTest,(AirStrucPtr)((TransientItemPtr)hitter)->Launcher);//RJS 16Nov98
//DeadCode RDH 30Mar99 				}
//DeadCode RDH 30Mar99 				else if ((AirStrucPtr)(((TransientItemPtr)hitter)->Launcher)==Persons2::PlayerSeenAC)
//DeadCode RDH 30Mar99 				{
//DeadCode RDH 30Mar99 // in playback do all near misses not caused by player
//DeadCode RDH 30Mar99 
//DeadCode RDH 30Mar99 					Art_Int.PersonalThreat((AirStrucPtr)trgTest,(AirStrucPtr)((TransientItemPtr)hitter)->Launcher);//RJS 16Nov98
//DeadCode RDH 30Mar99 				}
//DeadCode RDH 30Mar99 			}
//DeadCode RDH 30Mar99 		}
//DeadCode RDH 30Mar99 
//DeadCode RDH 30Mar99 	}
//DeadCode RDH 30Mar99 //DeadCode RDH 01Dec96 	((UByte*)0xB0000)[n]=retval;
//DeadCode RDH 30Mar99 //DeadCode PD 02Dec96 	n+=2;
//DeadCode RDH 30Mar99 //DeadCode PD 02Dec96 	n&=4095;
//DeadCode RDH 30Mar99 
//DeadCode RDH 30Mar99 //	*(char*)(0xb0000+160*24+100)='B';	
//DeadCode RDH 30Mar99 	return(retval);						//RJS 10Nov98
}



//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		TestCube
//Author		Jim Taylor
//Date			Sun 24 Nov 1996
//
//Description	Test collision of line from hit1 to hit 2 on cube at 0,0
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool	BoxCol::TestCube(Coords3D* hit1,Coords3D* hit2,SLong sidelen)
{
	int sl2=-sidelen;
	if (	(hit1->Y<sl2 && hit2->Y<sl2)
		||	(hit1->X<sl2 && hit2->X<sl2)
		||	(hit1->Y>sidelen && hit2->Y>sidelen)
		||	(hit1->Z<sl2 && hit2->Z<sl2)
		||	(hit1->X>sidelen && hit2->X>sidelen)
		||	(hit1->Z>sidelen && hit2->Z>sidelen)
		)
		return(FALSE);
	else
		return(TRUE);
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		TestFace
//Author		Jim Taylor
//Date			Sun 24 Nov 1996
//
//Description	Test if line hit1-hit2 passes through a face of the cuboid
//				and correct all axes accordingly
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
inline Bool 	BoxCol::TestFace(Coords3D* hitter1,Coords3D* hitter2,SLong hit1axis,SLong hit2axis,SLong sizeaxis)
{
	if (hit1axis<-sizeaxis)
		if (hit2axis<-sizeaxis)
			return(FALSE);
		else
		{
			SLong sfact=((ULong)(hit2axis+sizeaxis)<<13)/(ULong)(hit2axis-hit1axis);
			hitter1->X=(((hitter1->X-hitter2->X)*sfact)>>13)+hitter2->X;
			hitter1->Y=(((hitter1->Y-hitter2->Y)*sfact)>>13)+hitter2->Y;
			hitter1->Z=(((hitter1->Z-hitter2->Z)*sfact)>>13)+hitter2->Z;
		}
	elseif (hit1axis>sizeaxis)
		if (hit2axis>sizeaxis)
			return(FALSE);
		else
		{
			SLong sfact=((ULong)(sizeaxis-hit2axis)<<13)/(ULong)(hit1axis-hit2axis);
			hitter1->X=(((hitter1->X-hitter2->X)*sfact)>>13)+hitter2->X;
			hitter1->Y=(((hitter1->Y-hitter2->Y)*sfact)>>13)+hitter2->Y;
			hitter1->Z=(((hitter1->Z-hitter2->Z)*sfact)>>13)+hitter2->Z;
		}
	return(TRUE);
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		TestCol
//Author		Jim Taylor
//Date			Sun 24 Nov 1996
//
//Description	Test collision of line hit1-hit2 against cuboid trgsize at 0,0
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool	BoxCol::TestCol(Coords3D* hit1,Coords3D* hit2,Coords3D* trgsize)
{
	if (!TestFace(hit1,hit2,hit1->Y,hit2->Y,trgsize->Y))
		return(FALSE);
	if (!TestFace(hit1,hit2,hit1->X,hit2->X,trgsize->X))
		return(FALSE);
	if (!TestFace(hit1,hit2,hit1->Z,hit2->Z,trgsize->Z))
		return(FALSE);

	if (hit1->Y<-trgsize->Y || hit1->Y>trgsize->Y)
		return(FALSE);
	if (hit1->X<-trgsize->X || hit1->X>trgsize->X)
		return(FALSE);
	return(TRUE);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		TestFace2
//Author		Robert Slater
//Date			Mon 24 Feb 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
inline Bool 	BoxCol::TestFace2(	Coords3D* hitter1,
									Coords3D* hitter2,
									SLong 	hit1axis,
									SLong 	hit2axis,
									SLong	offset,
									SLong 	sizeaxis)
{
	SLong	minside, maxside;

	sizeaxis += TTrgSize;
	sizeaxis *= TSizeMul;

	minside = offset-sizeaxis;
	maxside = offset+sizeaxis;

	if (hit1axis<minside)
		if (hit2axis<minside)
			return(FALSE);
		else
		{
			SLong sfact=((ULong)(hit2axis-minside)<<13)/(ULong)(hit2axis-hit1axis);
			hitter1->X=(((hitter1->X-hitter2->X)*sfact)>>13)+hitter2->X;
			hitter1->Y=(((hitter1->Y-hitter2->Y)*sfact)>>13)+hitter2->Y;
			hitter1->Z=(((hitter1->Z-hitter2->Z)*sfact)>>13)+hitter2->Z;
		}
	elseif (hit1axis>maxside)
		if (hit2axis>maxside)
			return(FALSE);
		else
		{
			SLong sfact=((ULong)(maxside-hit2axis)<<13)/(ULong)(hit1axis-hit2axis);
			hitter1->X=(((hitter1->X-hitter2->X)*sfact)>>13)+hitter2->X;
			hitter1->Y=(((hitter1->Y-hitter2->Y)*sfact)>>13)+hitter2->Y;
			hitter1->Z=(((hitter1->Z-hitter2->Z)*sfact)>>13)+hitter2->Z;
		}
	return(TRUE);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SmallSideTest
//Author		Robert Slater
//Date			Mon 24 Feb 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool	BoxCol::SmallSideTest(SLong	side, SLong	offset, SLong	sizeaxis)
{
	sizeaxis += TTrgSize;
	sizeaxis *= TSizeMul;

	if (	(side < (offset-sizeaxis))
		||	(side > (offset+sizeaxis))	)
		return(TRUE);

	return(FALSE);
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		TestCol2
//Author		Robert Slater
//Date			Mon 24 Feb 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool	BoxCol::TestCol2(SWord	xoff, SWord	yoff, SWord	zoff,
						 UWord	sx, UWord sy, UWord sz,
						 UWord	succeed)
{
	Coords3D	tmppos1, tmppos2;

	tmppos1 = *TPos1;
	tmppos2 = *TPos2;

	if (!TestFace2(&tmppos1,&tmppos2,tmppos1.Y,tmppos2.Y,yoff,sy))//RJS 01Dec97
		return(FALSE);

	if (!TestFace2(&tmppos1,&tmppos2,tmppos1.X,tmppos2.X,xoff,sx))//RJS 01Dec97
		return(FALSE);

	if (!TestFace2(&tmppos1,&tmppos2,tmppos1.Z,tmppos2.Z,zoff,sz))//RJS 01Dec97
		return(FALSE);
					  
	if (SmallSideTest(tmppos1.Y,yoff,sy))						//RJS 01Dec97
		return(FALSE);

	if (SmallSideTest(tmppos1.X,xoff,sx))						//RJS 01Dec97
		return(FALSE);

	if (succeed == 0)											//RJS 01Dec97
		*TPos1 = tmppos1;

	return(TRUE);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AddEffect
//Author		Robert Slater
//Date			Wed 26 Feb 1997
//
//Description	Updates an effect queue to be processed later
//				(ie. once collision has occurred,
//					 or specific damage has been done)
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	BoxCol::AddEffect(UByte	type, UByte	level, UWord	effno, UWord	randval, UByteP	weapon, SByte grpindex, UWord hitshape)
{
	if (EffectCnt < MaxEffects)											//RJS 06Jun99
	{
		EffectQueue[EffectCnt].pointindex = pointindex;			//RJS 29Jun99
		EffectQueue[EffectCnt].hitshape = hitshape;
		EffectQueue[EffectCnt].grpindex = grpindex;
		EffectQueue[EffectCnt].level = level;
		EffectQueue[EffectCnt].type = type;
		EffectQueue[EffectCnt].effectno = effno;
		EffectQueue[EffectCnt].randval = randval;
		EffectQueue[EffectCnt++].weapptr = weapon;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ProcessEffectQueue
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
void	BoxCol::ProcessEffectQueue(ItemPtr	itm)
{
	if (EffectCnt)
	{
		UByte		damlevel;
		EffectType	type;
		UWord		val;
		UWord		randomval;
		UByteP		weapptr;										//RJS 23May97
		SByte		grpindex;
		UWord		hitshape;										//RJS 16Nov98
		WorldStuff*	worldptr = mobileitem::currworld;
		SLong		ecnt = 0;
//		SLong		gheight = Land_Scape.GetGroundLevel(colpos_hitgrp);//RJS 07Dec98
		HitEffectRecord	hitstruc;

//fucked		colpos_hitgrp.Y = gheight;

		do
		{
			damlevel = EffectQueue[ecnt].level;					//RJS 16Nov98
			type = (EffectType) EffectQueue[ecnt].type;			//RJS 16Nov98
			val = EffectQueue[ecnt].effectno;					//RJS 16Nov98
			randomval = EffectQueue[ecnt].randval;				//RJS 16Nov98
			weapptr = EffectQueue[ecnt].weapptr;				//RJS 16Nov98
			grpindex = EffectQueue[ecnt].grpindex;				//RJS 16Nov98
			hitshape = EffectQueue[ecnt].hitshape;				//RJS 16Nov98

			hitstruc.val = EffectQueue[ecnt].effectno;
			hitstruc.randval = EffectQueue[ecnt].randval;
			hitstruc.weapptr = EffectQueue[ecnt].weapptr;
			hitstruc.groupindex = EffectQueue[ecnt].grpindex;

//#ifndef NDEBUG
//	UWord cw=GETFPCW();
//	::AfxTrace("Do Anim: %d\n",EffectQueue[ecnt].effectno);
//	SETFPCW(cw);
//#endif
			switch (type)
			{
				case FX_SFX:
				{
					val += Math_Lib.rnd(randomval);
					_Miles.PlayOnce((FileNum) val,itm);			//RJS 10May99
					break;
				}

				case FX_VISUAL:
				{
					SLong	pindex = EffectQueue[ecnt].pointindex;	//RJS 29Jun99
//Nice idea, but not just yet...
//TempCode DAW 30Jun99 					hitstruc.hitCoords = colpos_impact;
//TempCode DAW 30Jun99 					hitstruc.hitterCoords = colpos_hititem;
//TempCode DAW 30Jun99 					hitstruc.grpCoords = colpos_hitgrp;
//TempCode DAW 30Jun99 					hitstruc.damagestrength = HitterStrength;
//TempCode DAW 30Jun99 					hitstruc.theShooter = Col_Shooter;			//JIM 11Mar99
					if (pindex > -1)							//RJS 29Jun99
						colpos_impact = colpos_list[pindex];	//RJS 29Jun99

					Trans_Obj.ExecuteAnimation(itm,Col_Shooter,hitshape,colpos_impact,*worldptr,val,randomval,weapptr,colpos_hititem,colpos_hitgrp,HitterStrength,grpindex);//JIM 11Mar99
					break;
				}

				case FX_RADIO:
					_DamageChat.ExecuteRadio(itm,Col_Shooter,hitstruc);//JIM 11Mar99
					break;
			}

			ecnt++;
		}while (ecnt < EffectCnt);

		EffectCnt = 0;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ResetCollisionStuff
//Author		Robert Slater
//Date			Tue 10 Mar 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	BoxCol::ResetCollisionStuff()
{
	Col_GroupElement = -1;
	Col_GroupSdptr = NULL;
	Col_AnimPtr = NULL;
	Col_AnimPrevPtr = NULL;
	Col_AnimNextPtr = NULL;
	Col_GroupPrev = NULL;
	Col_GroupNext = NULL;
	Col_Hitter = NULL;
	Col_Shooter = NULL;
	HitterStrength = 0;
	HitterDamageType = DMT_SHOCKWAVE;							//RJS 06Dec98
	Col_ExplodeIt = FALSE;

	pointindex = -1;											//RJS 29Jun99
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		BashHitter
//Author		Robert Slater
//Date			Wed 18 Mar 1998
//
//Description	Bash two objects together that we know have collided...
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	BoxCol::BashHitter(	MobileItemPtr 	trg,
							ItemPtr  		hitter,
							Coords3D& 		hitpos,
							int 			eltnum,
							Coords3D&		grppos,
							UWord			hitShape	)
{
	//Can the thing you have collided with actually inflict damage?
	ShapeDescPtr	sdptr = SHAPESTUFF.GetShapePtr(hitShape);	//RJS 20May99
	if (sdptr->RealDamageStrength)								//RJS 20May99
	{
		COORDS3D	coords;
		COORDS3D	offset;
		COORDS3D	PushedOffset;			
		SLong		dx, dy, dz;
		SLong		range;
		SLong		minrange = 1000000;
		SLong		thisLauncher = LT_CONTACT;
		SLong		useLauncher;
		SLong		hitterSize;
		SLong		mainDist;
		WorldStuff	*worldP = mobileitem::currworld;


		hitterSize = sdptr->Size << 4;
		dx = hitter->World.X - grppos.X; 
		dy = hitter->World.Y - grppos.Y; 
		dz = hitter->World.Z - grppos.Z; 

		mainDist = Math_Lib.distance3d(dx,dy,dz);
		if (mainDist < hitterSize)
			BounceOrExplode(trg,hitter,eltnum,grppos,(UByteP)sdptr);//RJS 20May99
		else
		{
			// Clipped....
			Persons2::UpdatePlayerLog	(Manual_Pilot.ControlledAC2,EventLog::MIDAIRCOLLISION); //RJS 21Jun99
			while (thisLauncher < CT_DUMMY)
			{
				SHAPE.GetContactPoint(trg,(LnchrType)thisLauncher,coords,offset,PushedOffset);

				dx = coords.X - hitpos.X;
				dy = coords.Y - hitpos.Y;
				dz = coords.Z - hitpos.Z;

				range = Math_Lib.distance3d(dx,dy,dz);
				if (range < minrange)
				{
					minrange = range;
					useLauncher = thisLauncher;
				}

				thisLauncher++;
			}

			AircraftAnimData*	adptr = (AircraftAnimData*) trg->Anim;

			switch (useLauncher)
			{
			case CT_LEFT:
				SHAPE.ForceDamage(trg,hitter,&adptr->LEFTWINGOUT,BS_DEAD);//JIM 11Mar99
				break;
			case CT_RIGHT:
				SHAPE.ForceDamage(trg,hitter,&adptr->RIGHTWINGOUT,BS_DEAD);//JIM 11Mar99
				break;
			case CT_WHLLEFT:
				if (!adptr->acleglowerl)
					SHAPE.ForceDamage(trg,hitter,&adptr->LEFTWINGIN,BS_DEAD);//JIM 11Mar99
				break;
			case CT_WHLRIGHT:
				if (!adptr->acleglowerr)
					SHAPE.ForceDamage(trg,hitter,&adptr->RIGHTWINGIN,BS_DEAD);//JIM 11Mar99
				break;
			case CT_WHLFRONT:
			case CT_FRONT:
				SHAPE.ForceDamage(trg,hitter,&adptr->PROPLEFTIN,BS_DEAD);//RJS 20May99
				BounceOrExplode(trg,hitter,eltnum,grppos,(UByteP)sdptr);//RJS 20May99
				break;
			case CT_WHLBACK:
			case CT_BACK:
				SHAPE.ForceDamage(trg,hitter,&adptr->TAIL,BS_DEAD);	//JIM 11Mar99
				break;
			case CT_BELLY:
				Trans_Obj.KillLauncher(trg,hitter,*worldP,-1,&hitpos,TRUE);//JIM 11Mar99
				break;
			}
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SpecificCollision
//Author		Robert Slater
//Date			Wed 18 Nov 1998
//
//Description	Hits a specific item
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
ItemPtr BoxCol::SpecificCollision(MobileItemPtr hitter,ItemPtr trg)
{
	if (trg)		//extra check...							//DAW 28Jun99
	{
		if (hitter->Status.size == TRANSIENTSIZE)
		{
			TransientItemPtr	tmpitm = (TransientItemPtr) hitter;
			if (!tmpitm->CollTestEnabled)
				return(NULL);

			Col_Shooter = tmpitm->Launcher;			//RJS 05Jul99
		}
		else		//RJS 05Jul99
			Col_Shooter = hitter;		//RJS 05Jul99

		Coords3D	hitpos;
		int			eltnum;

		n++;
		ShapeDescPtr	sdptr = SHAPESTUFF.GetShapePtr(hitter->shape);
		if (sdptr->AnimDataSize == MISSILEANIM)
		{
	//DeadCode DAW 23Jun99 		MissileAnimData*	adptr = (MissileAnimData*) hitter->Anim;
	//DeadCode DAW 23Jun99 		StaticHitterSize = sdptr->Size;
	//DeadCode DAW 23Jun99 		HitterStrength = (adptr->hitstrength / 2);
	//DeadCode DAW 23Jun99 		SLong			newhitsize = (StaticHitterSize* 3);
	//DeadCode DAW 23Jun99 		SLong			maxsize = newhitsize + StaticHitterSize;
	//DeadCode DAW 23Jun99 																
	//DeadCode DAW 23Jun99 		if (adptr->frameno)										
	//DeadCode DAW 23Jun99 		{														
	//DeadCode DAW 23Jun99 			newhitsize = (newhitsize * (adptr->frameno + 1));	
	//DeadCode DAW 23Jun99 			StaticHitterSize += (newhitsize >>= 8);
	//DeadCode DAW 23Jun99 											
	//DeadCode DAW 23Jun99 			HitterStrength = ((maxsize - StaticHitterSize) * HitterStrength)/newhitsize;
	//DeadCode DAW 23Jun99 		}														
			MissileAnimData*	adptr = (MissileAnimData*) hitter->Anim;
			if (adptr->hitstrength)			//something to prove...
			{
				//Max strength is 4000 lb bomb (64)
				//... blast radius is 40m for 1000 lb bomb
				//... so real radius = (160m * hitstrength)/64;
				//Fall off max radius is 3/2 * blast radius
				//... so max damage radius for 1000 lb bomb is 60m

				SLong	blastsize = (16000 * adptr->hitstrength)>>6;
				if (blastsize)
				{
					SLong	newstrength = adptr->hitstrength;

					//blast lasts for 2 csecs, the rest is fall off...
					if (adptr->frameno > 2)
					{
						//fall of strength is not as strong...
						newstrength *= 3;
						newstrength >>= 2;

						//Fall off time is .5 sec
						SLong	falloffsize = blastsize / 2;
						SLong	blasttime = adptr->frameno;

						newstrength -= (blasttime * adptr->hitstrength)/50;

						falloffsize *= blasttime;
						falloffsize /= 50;

						blastsize += falloffsize;
					}

					//for replay...
					if (newstrength > 31)	newstrength = 31;
					else
						if (newstrength < 0)	newstrength = 0;

					HitterStrength = newstrength;
					StaticHitterSize = blastsize >> 4;
				}
				else
					HitterStrength = 0;
			}
			else
			{
				StaticHitterSize = (sdptr->sx+sdptr->sy)>>1;			
				HitterStrength = SHAPESTUFF.GetShapeDamageStrength(hitter->shape);
			}
		}															
		else														
		{															
			StaticHitterSize = (sdptr->sx+sdptr->sy)>>1;			
			HitterStrength = SHAPESTUFF.GetShapeDamageStrength(hitter->shape);
		}												

		//Only do collision if this has damage potential...
		if (HitterStrength)														//RJS 18Feb99
		{
			HitterDamageType = SHAPESTUFF.GetShapeDamageType(hitter->shape);//RJS 07Dec98
			Col_Hitter = hitter;
			Col_GroupElement = -1;			
			if (HitterDamageType == DMT_EXPLOSION)
				Col_ExplodeIt = TRUE;
			else
				Col_ExplodeIt = FALSE;

			if (	(trg != Manual_Pilot.ControlledAC2)
				|| Save_Data.gamedifficulty[GD_VULNERABLE])
			{
				StaticTrgSdptr=SHAPESTUFF.GetShapePtr(trg->shape);

				if (trg->Status.size != AirStrucSize || ((AirStrucPtr)trg)->movecode != AUTO_RESURRECT )
					if (trg!=hitter && trg->Status.size!=TRANSIENTSIZE)
						if (GroupColSpecific(hitter,trg,hitpos,eltnum))	//RJS 03Dec98
						{
							ProcessEffectQueue(trg);
							return(trg);
						}
			}
		}
	}

	return(NULL);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DetailedTest
//Author		Dave Whiteside
//Date			Tue 1 Dec 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool	BoxCol::DetailedTest()
{
//DeadCode DAW 15Jun99 #ifndef NDEBUG
//DeadCode DAW 15Jun99 	if (Col_Shooter == Persons2::PlayerSeenAC)
//DeadCode DAW 15Jun99 	{
//DeadCode DAW 15Jun99 		UWord cw=GETFPCW();
//DeadCode DAW 15Jun99 		::AfxTrace("DETAILED TEST!\n");
//DeadCode DAW 15Jun99 		SETFPCW(cw);
//DeadCode DAW 15Jun99 	}
//DeadCode DAW 15Jun99 #endif

	return(TestCol(TPos1,TPos2,LastTSize));
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GroupColSpecific
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
Bool BoxCol::GroupColSpecific(MobileItemPtr hitter,ItemPtr trg,Coords3D& hitpos,int& eltnum)
{
	Col_GroupElement = -1;										//RJS 24Jun99
	colpos_hititem = hitter->World;								
	eltnum=-1;													
	if (SHAPESTUFF.GetShapeScale(StaticTrgSdptr)==SHP_GRP)		
	{
		UByte 			*iptr = (UByte *)StaticTrgSdptr + StaticTrgSdptr->liveshpref;
		int				groupindex = -1;
		MinAnimData*	mad = (MinAnimData*) trg->Anim;
		Coords3D		centrepoint=trg->World;
		ShapeNum		newshape,
						groupshp=trg->shape;
		SLong			ex,ey,ez;
		UByteP			PrevIptr;
		RotItemPtr		TmpItmPtr = new rotitem;
		SLong			yDelta;									
		animptr			tmpanim;								
		Coords3D		testpos;								
		animptr			Tmp_AnimNextPtr = trg->Anim;			//AMM 02Jul99

		TmpItmPtr->World = trg->World;
		TmpItmPtr->Anim = trg->Anim;
		TmpItmPtr->shape = trg->shape;

		TmpItmPtr->roll = ANGLES_0Deg;
		TmpItmPtr->pitch = ANGLES_0Deg;

		Col_AnimPtr = trg->Anim;								//RJS 21Apr99
		Col_AnimPrevPtr = trg->Anim;							//RJS 21Apr99
		Col_AnimNextPtr = trg->Anim;							//RJS 21Apr99
		Col_TokenDepAnim = trg->Anim;							//RJS 21Apr99
		Col_TokenDepAnim = (UByteP)NULL;						//RJS 21Apr99

		Col_GroupNext = NULL;									//RJS 30Jun99
		Col_GroupPrev = NULL;
		Col_AnimPrevPtr = (UByteP)NULL;									//RJS 21Apr99
		Col_AnimNextPtr = (UByteP)NULL;							//RJS 02Jul99
		Col_GroupSdptr = (UByteP) StaticTrgSdptr;				

		while(SHAPE.GetGroupElement(iptr,newshape,ex,ey,ez,0,&PrevIptr,(SWordP)&TmpItmPtr->hdg,&Col_GroupNext))//RJS 30Jun99
		{
			groupindex++;											
//DeadCode 30 Jun99			Col_GroupNext = iptr + 1;
			mad = (MinAnimData*) Tmp_AnimNextPtr;				//AMM 02Jul99
			Col_AnimPtr = &Tmp_AnimNextPtr;						//AMM 02Jul99
//DeadCode RJS 02Jul99 			tmpanim = Col_AnimPtr;				
			Tmp_AnimNextPtr += SHAPE.GetElementAnimOffset(newshape);
			Col_AnimNextPtr = &Tmp_AnimNextPtr;					//AMM 02Jul99
			if (mad->itemstate != DEAD)				
			{
				StaticTrgSdptr = SHAPESTUFF.GetShapePtr(newshape);

				testpos.X = ex+centrepoint.X;					
				testpos.Y = ey+centrepoint.Y;					
				testpos.Z = ez+centrepoint.Z;					

				tmpanim = Col_AnimPtr;							//AMM 02Jul99

				yDelta = SHAPE.GetElementYDelta(newshape,tmpanim,testpos,centrepoint.Y);	//RJS 09Jun99
				yDelta <<= 4;

				TmpItmPtr->World = testpos;						
				TmpItmPtr->World.Y += yDelta;					
				TmpItmPtr->shape=newshape;

				Col_GroupElement = groupindex;					
				Bool hit=TestCol(hitter,TmpItmPtr,trg,hitpos,NULL,FALSE);	//RJS 27May99
				if (hit)
				{
					Col_HitShape = newshape;					//AMM 02Jul99

					TmpItmPtr->Anim = NULL;
					delete TmpItmPtr;
					eltnum=groupindex;
					return(TRUE);
				}
			}
			Col_AnimPrevPtr = (UByteP) mad;							
			Col_GroupPrev = PrevIptr;
//DeadCode RJS 02Jul99 //			groupindex++;											
		}
		TmpItmPtr->Anim = NULL;
		delete TmpItmPtr;
		return(FALSE);
	}
	else
	{
		Col_AnimPtr = trg->Anim;				 
		MinAnimData*	mad = (MinAnimData*) Col_AnimPtr;
		if (mad->itemstate != DEAD)	//RJS 07Dec98
		{
			if (TestCol(hitter,trg,trg,hitpos,NULL,FALSE))			//RJS 27May99
				return(TRUE);
			else
				return(FALSE);
		}
		else
			return(FALSE);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DoCollision
//Author		Robert Slater
//Date			Mon 29 Mar 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool	BoxCol::DoCollision(Coords3D& hitpos, Coords3D& hit2, Coords3D& tsize, ItemPtr trgTest, ItemPtr trgReal, MobileItem* hitter, SLong	sizemul)
{
	Bool retval;

	SHAPE.SetGroupDamage(Col_GroupElement,Col_GroupPrev,Col_GroupNext,Col_AnimPrevPtr,Col_AnimNextPtr,Col_TokenDepAnim);

	if (!_Replay.Playback && !_Replay.Record)					//RJS 02Jul99
	{															//RJS 02Jul99
		pointindex++;											//RJS 02Jul99
		if (pointindex == MaxEffects)							//RJS 02Jul99
			pointindex = 0;										//RJS 02Jul99
	}															//RJS 02Jul99
	else														//RJS 02Jul99
		pointindex = -1;										//RJS 02Jul99
								
	if (StaticTrgSdptr->CollisionOffset)						//RJS 03Mar98
	{
		TPos1 = &hitpos;
		TPos2 = &hit2;
		LastTSize = &tsize;										//DAW 01Dec98
//DeadArse		EffectCnt = 0;

		retval=SHAPE.TestHitBoxes(trgReal,trgTest->shape,Col_AnimPtr,(UByteP)StaticTrgSdptr);//RJS 16Nov98
	}
	else
		retval=TestCol(&hitpos,&hit2,&tsize);

	if (retval)
	{
		// Had a hit.....

		SHAPE.FixUpColLog();
		if (trgTest->Status.size>=ROTATEDSIZE)
		{
			RotItemPtr	trg2=*trgTest;		  
			if (trg2->hdg || trg2->pitch || trg2->roll)			//RJS 15Jun99
			{													//RJS 15Jun99
				if (!matrixset)									//RJS 15Jun99
				{												//RJS 15Jun99
					ANGLES		hdgflip,pitchflip,rollflip;		//RJS 15Jun99
																//RJS 15Jun99
					hdgflip = ANGLES_0Deg-trg2->hdg;			//RJS 15Jun99
					pitchflip = ANGLES_0Deg-trg2->pitch;		//RJS 15Jun99
					rollflip = ANGLES_0Deg-trg2->roll;			//RJS 15Jun99
																//RJS 15Jun99
					_matrix.inverse(hdgflip,		  			//RJS 15Jun99
									pitchflip,		  			//RJS 15Jun99
									rollflip,		  			//RJS 15Jun99
									&frame1inverse_matrix);		//RJS 15Jun99
																//RJS 15Jun99
					matrixset = TRUE;							//RJS 15Jun99
				}									
				int scalefactor;
				scalefactor =16+ _matrix.transform(&frame1inverse_matrix,hitpos.X,hitpos.Y,hitpos.Z);//RJS 15Jun99

				hitpos.X>>=scalefactor;
				hitpos.Y>>=scalefactor;
				hitpos.Z>>=scalefactor;
			}

			if (sizemul != 16)									//DAW 18May99
			{
				SLong	divvy = sizemul;

				sizemul -= 16;
				sizemul <<= 8;
				sizemul /= divvy;

				hitpos.X *= sizemul;
				hitpos.Y *= sizemul;
				hitpos.Z *= sizemul;

				hitpos.X >>= 8;
				hitpos.Y >>= 8;
				hitpos.Z >>= 8;
			}
		}
		hitpos.X+=trgTest->World.X;
		hitpos.Y+=trgTest->World.Y;
		hitpos.Z+=trgTest->World.Z;

//DeadCode AMM 05Jul99 		colpos_list[pointindex] = colpos_impact = hitpos;		//RJS 29Jun99
		colpos_impact = hitpos;		//RJS 05Jul99
		if (pointindex > -1)									//RJS 05Jul99
			colpos_list[pointindex] = colpos_impact;			//RJS 05Jul99
		ShoveX = 0;												//RJS 29Jun99
		ShoveY = 0;
		ShoveZ = 0;
	}
	else
	{
		if (	!_Replay.Playback								//RJS 02Jul99
			&&	!_Replay.Record									//RJS 02Jul99
			&&	(pointindex > -1)	)							//RJS 02Jul99
			pointindex--;										//RJS 02Jul99

		//near miss...
		// Had a near miss...
		if (	(trgTest->Status.size == AirStrucSize)
			&&	(hitter->Status.size == TransientSize)
			&&	(HitterDamageType != DMT_SHOCKWAVE)		)		//RJS 29Mar99
		{
			if (_Replay.Record || _DPlay.Implemented)
			{
// only do near misses of players bullets against AI AC

				if (trgTest!=Persons2::PlayerSeenAC
				&&	!trgTest->uniqueID.commsmove)  
				{
// only store if this players bullet caused nearmiss

					if ((AirStrucPtr)(((TransientItemPtr)hitter)->Launcher)==Persons2::PlayerSeenAC)
					{
// dont store if targets ai.unfriendly is player
						if (((AirStrucPtr)trgTest)->ai.unfriendly!=Persons2::PlayerSeenAC)//AMM12Jan99
						{
							_DPlay.NewNearMiss((AirStrucPtr)trgTest,(AirStrucPtr)((TransientItemPtr)hitter)->Launcher);//RJS 16Nov98
						}
					}
					else
					{
// dont process if bullet is a comms bullet
						
						if (((TransientItemPtr)hitter)->CollTestEnabled)
						{
							Art_Int.PersonalThreat((AirStrucPtr)trgTest,(AirStrucPtr)((TransientItemPtr)hitter)->Launcher);//RJS 16Nov98
						}
					}
				}
			}
			else
			{
				if (!_Replay.Playback)
				{
// standard game - do all near misses

					Art_Int.PersonalThreat((AirStrucPtr)trgTest,(AirStrucPtr)((TransientItemPtr)hitter)->Launcher);//RJS 16Nov98
				}
				else if ((AirStrucPtr)(((TransientItemPtr)hitter)->Launcher)==Persons2::PlayerSeenAC)
				{
// in playback do all near misses not caused by player

					Art_Int.PersonalThreat((AirStrucPtr)trgTest,(AirStrucPtr)((TransientItemPtr)hitter)->Launcher);//RJS 16Nov98
				}
			}
		}
	}

	return(retval);
}

void	WorldStuff::ClearWorld()
{
	//Go through proper channels....
	_Replay.RemoveAllTransients(TRUE);							//RJS 21Jun99
	Trans_Obj.DeleteAll();	//Just resets trans lists			//PD 11May96

	for (int sn=SECTOR_MAXNUM-1;sn>=0;sn--)
	{
		ItemPtr	next=sectorlist[sn];
		sectorlist[sn]=NULL;
		while (next)
		{
			ItemBasePtr curr=next;
			if (next->World.X==-572662307)
				curr=next;
			next=next->Next;
			delete curr;
		}
	}
	for (int pi=0;pi<PITEMTABLESIZE;pi++)
		pItem[pi]=0;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		NineSectorColPiloted
//Author		Robert Slater
//Date			Mon 17 May 1999
//
//Description	Other items to collide with player only
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
ItemPtr BoxCol::NineSectorColPiloted(MobileItemPtr hitter)
{
	if (hitter->Status.size == TRANSIENTSIZE)	
	{
		TransientItemPtr	tmpitm = (TransientItemPtr) hitter;
		if (!tmpitm->CollTestEnabled)
			return(NULL);

		Col_Shooter = tmpitm->Launcher;
	}
	else
		Col_Shooter = hitter;

	n++;
	UWord	sector_x,
			sector_y;

	ShapeDescPtr	sdptr = SHAPESTUFF.GetShapePtr(hitter->shape);

	StaticHitterSize = (sdptr->sx+sdptr->sy)>>1;
	HitterStrength = SHAPESTUFF.GetShapeDamageStrength(hitter->shape);
	noGuns = 1;									

	//Only do collision with things that have damage potential...
	if (HitterStrength)
	{
		hitter->currworld->getsectornos(hitter,sector_x,sector_y);
		int	currentsector = hitter->currworld->GetSector(hitter);
		ItemPtr trg;
		sector_x--;
		sector_y--;

		HitterDamageType = SHAPESTUFF.GetShapeDamageType(hitter->shape);
		Col_Hitter = hitter;			
		Col_GroupElement = -1;			
		if (HitterDamageType == DMT_EXPLOSION)
			Col_ExplodeIt = TRUE;
		else
			Col_ExplodeIt = FALSE;

		for (int i=11;i>0;i--,sector_x++,sector_y-=3)
			for (;i&3;i--,sector_y++)
		{
			Bool hittersector;
			int	thissector=hitter->currworld->makeindex(sector_x,sector_y);
			hittersector=(thissector==currentsector)?TRUE:FALSE;
			trg=hitter->currworld->getfirstitem(thissector);
			trg=SectorColPiloted(hitter,trg,hittersector);
			if (trg)
			{
				ProcessEffectQueue(trg);
				return(trg);
			}
		}
	}

	return(NULL);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SectorColPiloted
//Author		Robert Slater
//Date			Mon 17 May 1999
//
//Description	Only checks if you've hit the piloted ac
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
ItemPtr BoxCol::SectorColPiloted(	MobileItemPtr hitter,
									ItemPtr trg,
									Bool hittersector	)
{
	if (hitter->Status.size==TRANSIENTSIZE)
	{
		if (((TransientItemPtr)*hitter)->Launcher == Manual_Pilot.ControlledAC2)
			return NULL;
	}

	while (trg)
	{
		if ((trg == Manual_Pilot.ControlledAC2)	&& Save_Data.gamedifficulty[GD_VULNERABLE])
		{
			int			eltnum = -1;
			Coords3D	hitpos;
			StaticTrgSdptr=SHAPESTUFF.GetShapePtr(trg->shape);
	 		if (hittersector && (((AirStrucPtr)trg)->movecode != AUTO_RESURRECT))
				if (GroupCol(hitter,trg,hitpos,eltnum,NULL,FALSE))
					return(trg);
		}
		trg=trg->Next;
	}
	return(NULL);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		NineSectorColThisPiloted
//Author		Robert Slater
//Date			Thu 20 May 1999
//
//Description	It is the player doing the collision!
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
ItemPtr BoxCol::NineSectorColThisPiloted(MobileItemPtr hitter)
{
	Col_Shooter = hitter;

	n++;
	UWord	sector_x,
			sector_y;

	ShapeDescPtr	sdptr = SHAPESTUFF.GetShapePtr(hitter->shape);
	
	StaticHitterSize = (sdptr->sx+sdptr->sy)>>1;
	HitterStrength = SHAPESTUFF.GetShapeDamageStrength(hitter->shape);
	noGuns = 1;								

	//Only do collision with things that have damage potential...
	if (HitterStrength)
	{
		int			eltnum;
		Coords3D	hitpos;

		hitter->currworld->getsectornos(hitter,sector_x,sector_y);
		int	currentsector = hitter->currworld->GetSector(hitter);
		ItemPtr trg;
		sector_x--;
		sector_y--;

		HitterDamageType = SHAPESTUFF.GetShapeDamageType(hitter->shape);
		Col_Hitter = hitter;
		Col_GroupElement = -1;
		if (HitterDamageType == DMT_EXPLOSION)
			Col_ExplodeIt = TRUE;
		else
			Col_ExplodeIt = FALSE;

		for (int i=11;i>0;i--,sector_x++,sector_y-=3)
			for (;i&3;i--,sector_y++)
		{
			Bool hittersector;
			int	thissector=hitter->currworld->makeindex(sector_x,sector_y);
			hittersector=(thissector==currentsector)?TRUE:FALSE;
			trg=hitter->currworld->getfirstitem(thissector);
			trg=SectorCol(hitter,trg,hitpos,eltnum,hittersector,NULL,TRUE);//RJS 27May99
			if (trg)
			{
				ProcessEffectQueue(trg);
				BashHitter(hitter,trg,hitpos,eltnum,colpos_hitgrp,Col_HitShape);
				return(trg);
			}
		}
	}

	return(NULL);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		BounceOrExplode
//Author		Robert Slater
//Date			Thu 20 May 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	BoxCol::BounceOrExplode(	MobileItemPtr 	trg,
									ItemPtr  		hitter,
									int				eltnum,
									Coords3D& 		hitpos,
									UByteP			tmpsdptr	)
{
	ShapeDescPtr	sdptr = (ShapeDescPtr)tmpsdptr;
	Bool			noExplode = TRUE;
	AirStrucPtr		you_ac = (AirStrucPtr) trg;

//DEADCODE DAW 27/01/00 	if ((you_ac == Persons2::PlayerSeenAC) && _Replay.Playback)	//RJS 21May99
	if ((you_ac == Persons2::PlayerSeenAC) && !_Replay.Playback) //AMM 27/01/00
		_DPlay.AddDeltas(Persons2::PlayerSeenAC,FALSE);			//RJS 21May99

	if (trg->vel > MPH15)
	{
		// Full-on collision.....  BANG!
		WorldStuff	*worldP = mobileitem::currworld;

		Persons2::UpdatePlayerLog	(Manual_Pilot.ControlledAC2,EventLog::MIDAIRCOLLISION); //RJS 21Jun99

		Trans_Obj.KillLauncher(trg,hitter,*worldP,-1,&hitpos,TRUE);
		Trans_Obj.KillLauncher(hitter,trg,*worldP,eltnum,&hitpos,TRUE);
		noExplode = FALSE;
	}

	if (sdptr->Type.StopDead)					
	{											
		if (!noExplode)
		{
			you_ac->vel = 0;
			you_ac->vely= 0;
			you_ac->velx= 0;
			you_ac->velz= 0;
			you_ac->velhori = 0;
			you_ac->movecode = AUTO_NOPPILOT;
		}
		else
		{
			//Dust...
			//Metal clang...
			you_ac->fly.pModel->Speed *= -0.5;
			you_ac->fly.pModel->Vel.x *= -0.5;
			you_ac->fly.pModel->Vel.y *= -0.5;
			you_ac->fly.pModel->Vel.z *= -0.5;

			you_ac->vel /= -2;
			you_ac->velx /= -2;
			you_ac->vely /= -2;
			you_ac->velz /= -2;
			you_ac->velhori /= -2;
		}
	}
	else
	{
		you_ac->fly.pModel->Speed *= 0.5;
		you_ac->fly.pModel->Vel.x *= 0.5;
		you_ac->fly.pModel->Vel.y *= 0.5;
		you_ac->fly.pModel->Vel.z *= 0.5;

		you_ac->vel /= 2;
		you_ac->velx /= 2;
		you_ac->vely /= 2;
		you_ac->velz /= 2;
		you_ac->velhori /= 2;

		if (noExplode)
		{
			if (hitter->Status.size >= MOBILESIZE)
			{






			}
		}
	}

//DEADCODE DAW 27/01/00 	if ((you_ac == Persons2::PlayerSeenAC) && _Replay.Playback)	//RJS 21May99
	if ((you_ac == Persons2::PlayerSeenAC) && !_Replay.Playback) //AMM 27/01/00
		_DPlay.AddDeltas(Persons2::PlayerSeenAC,TRUE);			//RJS 21May99
}
