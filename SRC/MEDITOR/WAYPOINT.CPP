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

//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop
#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
#include <vcl\Buttons.hpp>
#include <dosdefs.h>
#include <vcl\ExtCtrls.hpp>
#include <vcl\Mask.hpp>
#include <vcl\ComCtrls.hpp>
#include "sampreg.h"
#include "spin.h"

#include "uniqueid.h"
//#include "Route.h"
  #include "bfenum.h"
#include "meMain.h"

//#include "choosebf.h"
//#include "mainevt.h"

#include	"text.h"
#include "strings.h"
#include	"myangles.h"
#include	"bfnumber.h"
#include	"persons2.h"
#include	"mymath.h"
  #include "bfenum.h"
#include "readenum.h"
#include "waypoint.h"




//---------------------------------------------------------------------------
#pragma link "sampreg"
//DeadCode DAW 03Sep97 #pragma link "spin"
#pragma resource "*.dfm"
TWayPointForm *WayPointForm;
//enum	SquadSelect
////The five fully populated flyable blue squadrons must come first in this list,
////then non-flyable blues, then flyable reds, then non-flyable reds
//	{	SQ_B_FLYABLE=0,			SQ_F86A=0,SQ_F86B,SQ_F80,SQ_F84,SQ_F51,
//		SQ_B_NONFLYABLE=5,		SQ_B26=5,SQ_B29,
//		SQ_B_NONFLYSPOT=7,		SQ_T6=7,SQ_4U,
//		SQ_R_FLYABLE=9,			SQ_M15=9,SQ_M15B,
//		SQ_R_NONFLYABLE=11,		SQ_YAK=11,
//		SQ_R_MOREMIGSQUADS=12,	SQ_M15_b=12,SQ_M15_c,SQ_M15_d,SQ_M15_e,
//								SQ_M15B_b=16,SQ_M15B_c,SQ_M15B_d,SQ_M15B_e,
//		SQ_VEHICLES=20, 		SQ_ATruck=20,SQ_ATank
//
//	};

TypeData	typedata[]=
{
//			minvel	crvel	maxvel	bestpitch
/*F86A	0*/		{165,	2000,	3000,	ANGLES_13Deg},
/*F86B	1*/		{165,	2000,	3000,	ANGLES_13Deg},
/*F80 	2*/		{165,	2000,	3000,	ANGLES_13Deg},
/*F84 	3*/		{165,	2000,	3000,	ANGLES_13Deg},
/*B26 	4*/		{125,	1500,	2000,	ANGLES_13Deg},
/*B29 	5*/		{125,	1500,	2000,	ANGLES_13Deg},
/*T6  	6*/		{125,	1500,	2000,	ANGLES_13Deg},
/*U4  	7*/		{125,	1500,	2000,	ANGLES_13Deg},
/*F51 	8*/		{125,	1500,	2000,	ANGLES_13Deg},
/*M15 	9*/		{145,	2500,	3000,	ANGLES_13Deg},
/*M15B 	10*/	{145,	2500,	3000,	ANGLES_13Deg},
/*YAK 	11*/	{125,	2000,	2500,	ANGLES_13Deg},
/*M15B 	12*/	{145,	2500,	3000,	ANGLES_13Deg},
/*M15B 	13*/	{145,	2500,	3000,	ANGLES_13Deg},
/*M15B 	14*/	{145,	2500,	3000,	ANGLES_13Deg},
/*M15B 	15*/	{145,	2500,	3000,	ANGLES_13Deg},
/*M15B 	16*/	{145,	2500,	3000,	ANGLES_13Deg},
/*M15B 	17*/	{145,	2500,	3000,	ANGLES_13Deg},
/*M15B 	18*/	{145,	2500,	3000,	ANGLES_13Deg},
/*M15B 	19*/	{145,	2500,	3000,	ANGLES_13Deg},
/*TRUCK 20*/	{1,		600,	700,	ANGLES_0Deg},
/*TANK	21*/	{1,		300,	400,	ANGLES_0Deg}
};
UWord altitudeeffectdata[] =
			{
				100,
				75,
				50,
				35,
				25,
				10,
				0,
				0,
				0,
				0,
				0,
				0,
				0,
				0,
				0,
				0,
				0,
				0,
				0,
				0,
				0,
				0,
				0,
			0
			};

SLong const 	MAXALTITUDE_CM 	=	2200000;
SLong const 	WORD_FRACT   	=	65536;

static int
AirCraftActionsNoTargetAllowed[]=
{	wpacnoactionno,wpstartloopno,wpstoploopchkno,wpreccyno,wpartspotno,wpbreakloop,-1	},
AirCraftActionsTargetAllowed[]=
{	wpacnoactionno,wpstartloopno,wpstoploopchkno,wpreccyno,wpartspotno,
	wpballoonbustno,wpbombno,wpdivebombstraffeno,wpsecondaryno,wpbreakloop,-1	},
AirCraftLastWPAllowed[]=
{   wpalandingno,-1	},
MobileActionsAllowed[] =
{   wpacnoactionno,wpstartloopno,wpstoploopchkno,wpwaituntildeadno,wpdmbtrknoactno,
	wpdmbtrkstopno,wpteleportnext,-1	},
AirCraftActionsNoTarget[64],
AirCraftActionsTarget[64],
AirCraftLastWP[64],
MobileActions[64];


void	fixlist(int* indexes,int* table,int len)
{
	for (int t2=0;t2<len;t2++)
    	table[t2]=-1;
    for(int count=0;indexes[count]!=-1;count++)
    {
    	if (indexes[count]>=len)
        	MessageBox(NULL,"Error","Table overflowed in waypoints",0);
    	table[indexes[count]]=count;
    }
}

//---------------------------------------------------------------------------
__fastcall TWayPointForm::TWayPointForm(TComponent* Owner)
	: TForm(Owner)
{
	Font->Color = clWindow;
	Font->Color = clWindowText;
	fixlist(AirCraftActionsNoTargetAllowed,AirCraftActionsNoTarget,64);
	fixlist(AirCraftActionsTargetAllowed,AirCraftActionsTarget,64);
	fixlist(AirCraftLastWPAllowed,AirCraftLastWP,64);
	fixlist(MobileActionsAllowed,MobileActions,64);

}
//---------------------------------------------------------------------------
void __fastcall TWayPointForm::NewEventWpPos(int X, int Z)
{

	SLong mx, mz,offset;
	SLong	wx,wz;
	bool xcontrol;
//	MissionEditor->WorldPosition(X,Z);
	info_waypoint* W=*Persons2::ConvertPtrUID(MissionEditor->currwp);
	UniqueID	u1=W->prevwp,
				u2=W->nextwp;
	if (!u1)	u1=MissionEditor->currobj;
	ItemBasePtr I1=Persons2::ConvertPtrUID(u1),
				I2=Persons2::ConvertPtrUID(u2);
//	if (I1->target->Evaluate()!=ENABLE_COMPLEX_VAL)
  //		I1=*Persons2::ConvertPtrUID(UniqueID(I1->target->Evaluate()));
//	if (I2->target->Evaluate()!=ENABLE_COMPLEX_VAL)
  //		I2=*Persons2::ConvertPtrUID(UniqueID(I2->target->Evaluate()));

	wx = I2->World.X - I1->World.X;
	wz = I2->World.Z - I1->World.Z;

	mx = X-I1->World.X;
	mz = Z-I1->World.Z;

	if (Math_Lib.AbsSign(wz)>Math_Lib.AbsSign(wx))
	{
		wx=wz;
		mx=mz;
	}

	offset = mx*100/wx;

	if (offset<1)
		offset=1;

	if (offset>99)
		offset=99;

	if (	W->position->Arguments()==2
		&&	W->position[1]->type==Expr::EXPR_ROT
		&&	W->position[1]->Arguments()==4

	   )
		if (W->position[1][1].complex)
		{
			W->position[1][1][0]=offset;
			if (W->position[1][1][2].Evaluate()>=100-offset)
				W->position[1][1][2]=100-offset;
		}
		else
			W->position[1][1]=offset;

	FindNewWPPos(MissionEditor->currwp);


}
//---------------------------------------------------------------------------
void __fastcall TWayPointForm::FindNewWPPos(UniqueID u)
{
	info_waypoint* W=*Persons2::ConvertPtrUID(MissionEditor->currwp);
	W->position.EvalW(W->World);
/////		newwp->World.Y = 500000;
}

//---------------------------------------------------------------------------
void __fastcall TWayPointForm::InsertWPAfter(UniqueID	prevu)
//insert wp after oldwp. make new waypoint the CurrWp
{
	if (prevu)
	{
		info_waypoint*	newwp=new info_waypoint;
		newwp->bfieldindex=MissionEditor->bfieldbeingfilled;
///		newwp->uniqueID.sector=FALSE;
		newwp->position.MakeAbsWorldPos();
		MissionEditor->currwp =
			newwp->uniqueID.count=Persons2::assignuid(WayPointBAND);
		MissionEditor->IncWayPointandCheck();
		info_grndgrp*  owner = *Persons2::ConvertPtrUID(MissionEditor->currobj);
		if ((int)owner->Status.size>(int)MOBILESIZE)
			newwp->wpact = wpacnoactionno;
		else
			newwp->wpact = wpdmbtrknoactno;
		info_waypoint*	prevwp=*Persons2::ConvertPtrUID(prevu);
		UniqueID	nextu=prevwp->nextwp;
		ItemBasePtr nextwp;
		if (nextu)
		{
			info_waypoint* tmp=*Persons2::ConvertPtrUID(nextu);
			tmp->prevwp=newwp->uniqueID.count;
			nextwp=tmp;
		}
		else
			nextwp=*Persons2::ConvertPtrUID(MissionEditor->currobj);

		newwp->nextwp=nextu;
		newwp->prevwp=prevu;
		prevwp->nextwp=newwp->uniqueID.count;

		newwp->vel = prevwp->vel;

		newwp->position[0][0]=(prevwp->World.X+nextwp->World.X)/2;
//		newwp->position[0][1]=(prevwp->World.Y+nextwp->World.Y)/2;
		if 	(	(prevwp->World.Y != 0)
			 &&  (prevwp->target.Evaluate() == ENABLE_COMPLEX_VAL)
			 )
			newwp->position[0][1]=prevwp->World.Y;
		else
		{
			if ((int)owner->Status.size>(int)MOBILESIZE)
			newwp->position[0][1]= -100000;
			else
			newwp->position[0][1]= 0;
		}
		newwp->position[0][2]=(prevwp->World.Z+nextwp->World.Z)/2;
		newwp->position.EvalW(newwp->World);
		newwp->owner=prevwp->owner;
		Persons2::tabulateUID(newwp);
		FillRouteList();
 //		MissionEditor->PaintRefresh();
	}

}
//////void  __fastcall TWayPointForm::InitWayPoint(RodsWayPoint* wp)
//////{
//////	wp->eventinfo = NULL;
//////	wp->eventnum = 0;
//////	wp->curreventnum = 0;
//////	wp->WPAction = 0;
//////	wp->fixedoffset = 50;
//////	wp->randomoffset = 50;
//////	wp->encounterrange = 0;
//////	wp->target = NULL;
//////
//////}
//////
////////---------------------------------------------------------------------------
//////RodsWayPoint* __fastcall TWayPointForm::InsertAfter(RodsWayPoint*	oldwp)
//////{
//////	RodsWayPoint*	newwp;
//////	RodsWayPoint*	nextwp;
//////
//////	nextwp = oldwp->next;
//////	newwp = new RodsWayPoint;
//////	InitWayPoint(newwp);
//////
//////	oldwp->next = newwp;
//////
//////	newwp->prev = oldwp;
//////	newwp->next = nextwp;
//////	if (nextwp !=NULL)
//////	{
//////		nextwp->prev = newwp;
//////	}
//////	return (newwp);
//////
//////}
//////
//---------------------------------------------------------------------------
void __fastcall TWayPointForm::InsertWPBefore(UniqueID	nextu)
{

	if (nextu)
	{
		info_waypoint*	newwp=new info_waypoint;
		newwp->bfieldindex=MissionEditor->bfieldbeingfilled;
//DeadCode RDH 11Feb98 		newwp->uniqueID.sector=FALSE;
		newwp->position.MakeAbsWorldPos();
		MissionEditor->currwp =
			newwp->uniqueID.count=Persons2::assignuid(WayPointBAND);
		MissionEditor->IncWayPointandCheck();
		info_grndgrp*  owner = *Persons2::ConvertPtrUID(MissionEditor->currobj);
		if ((int)owner->Status.size>(int)MOBILESIZE)
			newwp->wpact = wpacnoactionno;
		else
			newwp->wpact = wpdmbtrknoactno;
		info_waypoint*	nextwp=*Persons2::ConvertPtrUID(nextu);
		UniqueID	prevu=nextwp->prevwp;
		ItemBasePtr prevwp;
		if (prevu)
		{
			info_waypoint* tmp=*Persons2::ConvertPtrUID(prevu);
			tmp->nextwp=newwp->uniqueID.count;
			prevwp=tmp;
		}
		else
		{
			info_grndgrp*	tmp=*Persons2::ConvertPtrUID(MissionEditor->currobj);
			tmp->wpref=newwp->uniqueID.count;
			prevwp=tmp;
		}
		newwp->prevwp=nextwp->prevwp;
		newwp->nextwp=nextu;
		nextwp->prevwp=newwp->uniqueID.count;

		newwp->vel = nextwp->vel;

		newwp->position[0][0]=(prevwp->World.X+nextwp->World.X)/2;
//		newwp->pos[0][1]=(prevwp->World.Y+nextwp->World.Y)/2;
		if (	(nextwp->World.Y != 0)
			 &&  (nextwp->target.Evaluate() == ENABLE_COMPLEX_VAL)
			)
			newwp->position[0][1]=nextwp->World.Y;
		else
		{
			if ((int)owner->Status.size>(int)MOBILESIZE)
			newwp->position[0][1]= -100000;
			else
			newwp->position[0][1]= 0;
		}
		newwp->position[0][2]=(prevwp->World.Z+nextwp->World.Z)/2;
		newwp->position.EvalW(newwp->World);
		newwp->owner=nextwp->owner;
		Persons2::tabulateUID(newwp);
		FillRouteList();
//		MissionEditor->PaintRefresh();
	}

}

void __fastcall TWayPointForm::WpDelClick(TObject *Sender)
{
	WpDelete();
}
void __fastcall TWayPointForm::WpDelete()
{
	if (MissionEditor->currwp)
	{
		info_waypoint* W=*Persons2::ConvertPtrUID(MissionEditor->currwp);
//		if (W->nextwp || W->prevwp)
		//lat wp should not be deleted
		if (W->nextwp)
		{
			info_waypoint* prevwp=NULL;
			if (W->prevwp)
				prevwp=*Persons2::ConvertPtrUID(W->prevwp);
			info_waypoint* nextwp=NULL;
				nextwp=*Persons2::ConvertPtrUID(W->nextwp);
			if (prevwp && prevwp->events && (!nextwp || nextwp->events))
				MessageBeep(MB_ICONEXCLAMATION);
		//	   PlaySound("ID_YELL2",HInstance,SND_ASYNC|SND_RESOURCE);
			else
			if (nextwp && nextwp->events && (!prevwp || prevwp->events))
//			   PlaySound("ID_YELL2",HInstance,SND_ASYNC|SND_RESOURCE);
				MessageBeep(MB_ICONEXCLAMATION);
			else
			{
				WPDelete(MissionEditor->currwp);
				FillRouteList();
				WayPointFormEdits = false;
				RefreshWayPointForm();
 //				MissionEditor->PaintBox->Invalidate();
			}
		}
		else
//			PlaySound("ID_YELL2",HInstance,SND_ASYNC|SND_RESOURCE);
			MessageBeep(MB_ICONEXCLAMATION);
	}
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

void __fastcall TWayPointForm::WPDelete(UniqueID curru)
{

	if (curru)
	{
		info_waypoint* W=*Persons2::ConvertPtrUID(MissionEditor->currwp);
		info_waypoint* prevwp=NULL;
		if (W->prevwp)
			prevwp=*Persons2::ConvertPtrUID(W->prevwp);
		info_waypoint* nextwp=NULL;
			nextwp=*Persons2::ConvertPtrUID(W->nextwp);
		if (prevwp)
		{
			prevwp->nextwp=W->nextwp;
			if (prevwp->events)
			{
				prevwp->position[1][0][1]=W->nextwp;
				ReposEventWp(prevwp->uniqueID.count);
			}
			if ((int)MissionEditor->currwp==(int)curru)
				MissionEditor->currwp=W->prevwp;
		}
		else
		{
			info_grndgrp*	tmp=*Persons2::ConvertPtrUID(MissionEditor->currobj);
			tmp->wpref=W->nextwp;
			if ((int)MissionEditor->currwp==(int)curru)
				MissionEditor->currwp=W->nextwp;
		}
		if (nextwp)
		{
			nextwp->prevwp=W->prevwp;
			if (nextwp->events)
			{
				nextwp->position[0]=W->prevwp;
				nextwp->position[1][0][0]=W->prevwp;
				ReposEventWp(nextwp->uniqueID.count);
			}
		}
		Persons2::delUID(W->uniqueID.count);
		MissionEditor->WayPointCnt--;
		if (MissionEditor->WayPointCnt < 0)
			MissionEditor->WayPointCnt = 0;
		MissionEditor->DisableWPUsageifnecessary();
		delete	W;
	}
}
//---------------------------------------------------------------------------

//////void __fastcall TWayPointForm::InsertWPBefore(RodsWayPoint*	oldwp)
////////insert wp before oldwp. make new waypoint the CurrWp
//////{
//////
//////	RodsWayPoint*	newwp;
//////
//////	newwp = InsertBefore(oldwp);
//////
//////		if (newwp->prev == NULL)
//////		{
//////			FindNewWPPos(newwp,MissionEditor->CurrTransItem->World.X,MissionEditor->CurrTransItem->World.Y,
//////					MissionEditor->CurrTransItem->World.Z,
//////				newwp->next->World.X,newwp->next->World.Y,newwp->next->World.Z,50);
//////		}else
//////		{
//////			if (newwp != NULL)
//////			{
//////				FindNewWPPos(newwp,newwp->prev->World.X,newwp->prev->World.Y,newwp->prev->World.Z,
//////					newwp->next->World.X,newwp->next->World.Y,newwp->next->World.Z,50);
//////			}
//////		}
//////
//////}

//---------------------------------------------------------------------------
void __fastcall TWayPointForm::AddEventButtons()
{
	info_waypoint* W=*Persons2::ConvertPtrUID(MissionEditor->currwp);
//	if (!W->events)
	{
		HelpContext = 41;
		EventData->Visible = false;
		EventMore->Visible = false;

		if (WayPointFormEdits)
		{
			WpAccept->Enabled = true;
			WpUndo->Enabled = true;
		}else
		{
			WpAccept->Enabled = false;
			WpUndo->Enabled = false;
		}

		WpData->Visible = true;
//		if 	(W->nextwp)
//		{
//			info_waypoint* tmp=*Persons2::ConvertPtrUID(W->nextwp);
//			if ((	tmp->events)
//				||(MissionEditor->currobj != (int)MissionEditor->ActiveCampaign.PlayerAcuid)
//				)
//				EventAfter->Enabled = false;
//			else
//				EventAfter->Enabled = true;
//		}
//		else
		{
			EventAfter->Enabled = false;
        }
//		if 	(W->prevwp)
//		{
//			info_waypoint* tmp=*Persons2::ConvertPtrUID(W->prevwp);
//			if ((	tmp->events)
//				||(MissionEditor->currobj != (int)MissionEditor->ActiveCampaign.PlayerAcuid)
//				)
//				EventBefore->Enabled = false;
//			else
//				EventBefore->Enabled = true;
//		}
//		else
			EventBefore->Enabled = false;

   }
//   else
//   {
//		HelpContext = 60;
//		EventData->Visible = true;
//		EventMore->Visible = true;
//		WpData->Visible = false;
//		WpAccept->Enabled = false;
//		WpUndo->Enabled = false;
//		EventAfter->Enabled = false;
//		EventBefore->Enabled = false;
//   }
	if (WayPointFormEdits)
	{
		EventAfter->Enabled = false;
		EventBefore->Enabled = false;
	}
		if ( MissionEditor->WayPointCnt >= MissionEditor->WayPointMax)
		{
			EventAfter->Enabled = false;
			EventBefore->Enabled = false;
		}

}

//---------------------------------------------------------------------------
void __fastcall TWayPointForm::CalcEta(info_waypoint* W)
{
//   int	dist = 500000;
//   int	vel = W->vel.Evaluate();
//   int	time;
//
//   if ( vel == ENABLE_COMPLEX_VAL)			//default set and never been filled in
//   {
//   		vel =545;
//   }
//
//   W->etas = 10 * dist/vel;

}

//---------------------------------------------------------------------------
void __fastcall TWayPointForm::CalcVel(info_waypoint* W)
{
//	int	dist = 500000;
//	int time = W->etas;
//
//	W->vel  = 10 * dist/time;

}

//---------------------------------------------------------------------------
int  __fastcall TWayPointForm::FindVel( int& vel,info_waypoint* W)
{
	info_grndgrp*	tmp=*Persons2::ConvertPtrUID(MissionEditor->currobj);


	int retval = 3;
	int delta = 1;
//	vel = wpvel;
//	vel = W->vel.Evaluate();
	if (vel == ENABLE_COMPLEX_VAL)			//default set and never been filled in
   {
		vel = typedata[tmp->type].cruisevel;
	  retval =1;
   }
   if (		((vel - typedata[tmp->type].cruisevel + delta ) <= (2*delta))
				&&  ((vel - typedata[tmp->type].cruisevel + delta ) >= 0)
		  )
	{
		vel = vel = typedata[tmp->type].cruisevel;
	  retval =1;
	}
	else if (		((vel - typedata[tmp->type].climbvel + delta ) <= (2*delta))
				&&  ((vel - typedata[tmp->type].climbvel + delta ) >= 0)
			)
	{
	  vel = vel = typedata[tmp->type].climbvel;
	  retval =0;
	}
	else 
	{
		int d;
		d = vel - typedata[tmp->type].maxvel;	
		d = d + delta; 
		if (		(d <= (2*delta))
					&&  (d >= 0)
				)
		{
		  vel = vel = typedata[tmp->type].maxvel;
		  retval =2;
		}
		else
		  retval =3;
	}	
	return (retval);
}

//---------------------------------------------------------------------------
void __fastcall TWayPointForm::RefreshWayPointForm()
{
	char buff[50];
	FillRouteList();
	FillWpActionList();
	FillEventRangeList();
   int SpdComboBoxIndex;

   SpeedEdit->OnChange = NULL;
   WPAltEdit->OnChange =  NULL;
   RangeEdit->OnChange =  NULL;
   FixedOffsetEdit->OnChange =  NULL;
   RandomOffsetEdit->OnChange =  NULL;
							   
	info_waypoint* W=*Persons2::ConvertPtrUID(MissionEditor->currwp);
	if (W->events)
	{
		FixedOffsetEdit->Text = IntToStr(W->position[1][1][0]);
		RandomOffsetEdit->Text = IntToStr(W->position[1][1][2]);
		FixedOffsetEdit->Enabled = true;
		RandomOffsetEdit->Enabled = true;
	}else
	{
		FixedOffsetEdit->Enabled = false;
		RandomOffsetEdit->Enabled = false;
	}


//   int	vel;
	SpdComboBoxIndex = FindVel(wpvel,W);

	if (MissionEditor->ShowWPvel)
	{

		SpeedEdit->Visible = true;
		TimeEdit->Visible = false;
//		SpinButton1->Visible = false;
	}else
	{
		EtaUpdate();
		SpeedEdit->Visible = false;
		TimeEdit->Visible = true;
//		SpinButton1->Visible = true;

	   char buff[50];
	   char hrbuff[50];
	   char minbuff[50];   
		int	etam = ((int)etas +30 )/60;
		int	etah = etam/60;
	   etam = etam - etah *60;
	  
	  strcpy(buff,"");
	  if (etah < 10)
		strcat(buff,"0");
					   
	   itoa(etah,hrbuff,10);
	   strcat(buff,hrbuff);
	  
	   strcat(buff,":");
	  if (etam < 10)
		strcat(buff,"0");
	  
	   itoa(etam,minbuff,10);
	   strcat(buff,minbuff);
	   TimeEdit->Text = buff;				   
	}


	int targ=W->target.Evaluate();
	if (targ!=ENABLE_COMPLEX_VAL)
	{
		char*	tmp =  GetList(ENUM_UIDtitle).Translate(targ);
		if (tmp == NULL)
		{
			int text = MissionEditor->GetBandorShapeText(UniqueID(targ));
			LoadString(HInstance,text,buff,sizeof(buff));
			 PositionEdit->Text = buff;
		}else
			 PositionEdit->Text = tmp;
	}else
	{
		PositionEdit->Text = "";
	}

	 if (wprange == ENABLE_COMPLEX_VAL)			//default set and never been filled in
	 {
		info_grndgrp* G=*Persons2::ConvertPtrUID(MissionEditor->currobj);
		if ((int)G->Status.size > (int)MOBILESIZE)
			wprange = 0;
		else
			wprange = 0;
	 }
	 char	wp_range[50];
	char	altitude[50];
	
	 LoadString(HInstance,TEXT_SPD,buff,sizeof(buff));
	 LoadString(HInstance,TEXT_WPRANGE,wp_range,sizeof(wp_range));
	if (targ!=ENABLE_COMPLEX_VAL)
	{
		 LoadString(HInstance,TEXT_RELATIVEALT,altitude,sizeof(altitude));
	}else
	{
		 LoadString(HInstance,TEXT_ALT,altitude,sizeof(altitude));
	}
	  if (MissionEditor->Configure_Units == METRIC)
	  {

		if (MissionEditor->ShowWPvel)
		{
			strcat(buff,"kmh"); 
			SpeedEdit->Text = IntToStr((int)(wpvel*36+18)/100);		//224*8/5000
		}else
		{
			 LoadString(HInstance,TEXT_ETAAT,buff,sizeof(buff));
		
		}   
		WpSpeedBtn->Caption = buff;
		strcat(wp_range,"m"); 
		WpRangeLabel->Caption = wp_range;
		strcat(altitude,"m"); 
		WpAltitudeLabel->Caption = altitude;

		if (targ!=ENABLE_COMPLEX_VAL)
			WPAltEdit->Text = IntToStr(W->World.Y/100);
		else
			WPAltEdit->Text = IntToStr(-W->World.Y/100);
		RangeEdit->Text = IntToStr(wprange/100);

	  }else if (MissionEditor->Configure_Units == IMPERIAL)
	  {
		if (MissionEditor->ShowWPvel)
		{
			SpeedEdit->Text = IntToStr((int)(wpvel*224+112)/1000);
			strcat(buff,"mph");                           
		}else
		{
			 LoadString(HInstance,TEXT_ETAAT,buff,sizeof(buff));
		}   
	WpSpeedBtn->Caption = buff;
		strcat(wp_range,"ft"); 
	WpRangeLabel->Caption = wp_range;
		strcat(altitude,"ft"); 
	  WpAltitudeLabel->Caption = altitude;
	  
		if (targ!=ENABLE_COMPLEX_VAL)
			WPAltEdit->Text = IntToStr((W->World.Y*100-50)/3048);
		else
			WPAltEdit->Text = IntToStr(-(W->World.Y*100-50)/3048);
		RangeEdit->Text = IntToStr((wprange*100+50)/3048);
	  }else
	  {
		if (MissionEditor->ShowWPvel)
		{
			strcat(buff,"kmh"); 
			SpeedEdit->Text = IntToStr((int)(wpvel*36+18)/100);		//224*8/5000
		}else
		{
			 LoadString(HInstance,TEXT_ETAAT,buff,sizeof(buff));
		}   
	WpSpeedBtn->Caption = buff;
		strcat(wp_range,"m"); 
	WpRangeLabel->Caption = wp_range;
		strcat(altitude,"ft"); 
	  WpAltitudeLabel->Caption = altitude;
	  
		if (targ!=ENABLE_COMPLEX_VAL)
			WPAltEdit->Text = IntToStr((W->World.Y*100-50)/3048);
		else
			WPAltEdit->Text = IntToStr(-(W->World.Y*100-50)/3048);
		RangeEdit->Text = IntToStr(wprange/100);
	  }




	if (Persons2::ConvertPtrUID(MissionEditor->currobj)->Status.size==AIRSTRUCSIZE)
	{
		WpAltitudeLabel->Enabled = true;
		WPAltEdit->Enabled = true;
	}else
	{
		WpAltitudeLabel->Enabled = false;
		WPAltEdit->Enabled = false;
	}
//	WayPointFormEdits = false;
	SetMoveOnButtons();

	MissionEditor->FillComboBox(TEXT_MINVEL,
								TEXT_CUSTOM,
											SpdComboBox,
											SpdComboBoxIndex);
   SpeedEdit->OnChange = SpeedEditChange;
   WPAltEdit->OnChange =  WPAltEditChange; 
   RangeEdit->OnChange =  RangeEditChange; 
   FixedOffsetEdit->OnChange =  FixedOffsetEditChange;
   RandomOffsetEdit->OnChange =  RandomOffsetEditChange;

}
//---------------------------------------------------------------------------
void __fastcall TWayPointForm::SetMoveOnButtons()
{

	info_waypoint* W=*Persons2::ConvertPtrUID(MissionEditor->currwp);

	if (WayPointFormEdits)
	{
		RouteListBox->Enabled = false;
		WpNext->Enabled = false;
		WpPrev->Enabled = false;
		EventAfter->Enabled = false;
		EventBefore->Enabled = false;
		WPBefore->Enabled = false;
		WPAfter->Enabled = false;
	}else
	{
//		WpUndo->Enabled = false;
//		WpAccept->Enabled = false;
		RouteListBox->Enabled = true;
		WpNext->Enabled = true;
		WpPrev->Enabled = true;
		if ( MissionEditor->WayPointCnt >= MissionEditor->WayPointMax)
		{
			WPBefore->Enabled = false;
			WPAfter->Enabled = false;
		}else
		{
			WPBefore->Enabled = true;
			WPAfter->Enabled = true;
		}	
	}

	if 	(!W->nextwp)
	{
		WpNext->Enabled = false;
		WPAfter->Enabled = false;
	}

	if 	(!W->prevwp)
		WpPrev->Enabled = false;


	AddEventButtons();

//	MissionEditor->PaintBox->Invalidate();
}

//---------------------------------------------------------------------------

void __fastcall TWayPointForm::WPBeforeClick(TObject *Sender)
{
	InsertWPBefore(MissionEditor->currwp);
	PositionEvents();
	WayPointFormEdits = false;
	RefreshWayPointForm();
//	MissionEditor->PaintBox->Invalidate();

}
//---------------------------------------------------------------------------
void __fastcall TWayPointForm::WPAfterClick(TObject *Sender)
{
	InsertWPAfter(MissionEditor->currwp);
	PositionEvents();
	WayPointFormEdits = false;
	RefreshWayPointForm();
//	MissionEditor->PaintBox->Invalidate();
}
//---------------------------------------------------------------------------


void __fastcall TWayPointForm::EventAfterClick(TObject *Sender)
{
//events	InsertWPAfter(MissionEditor->currwp);
//events	info_waypoint* W=*Persons2::ConvertPtrUID(MissionEditor->currwp);
//events	W->events=new	info_event;
//events	UniqueID	up,un=W->nextwp;
//events	if (W->prevwp)
//events		up=W->prevwp;
//events	else
//events		up=W->owner;
//events	W->pos.MakeIcptIPCWorldPos(up,un);
//events	W->pos[1][1]=new	RndExpr;
//events	W->pos[1][1][0]=50;
//events	W->pos[1][1][2]=0;
//events	W->range = 400000;
//events
//events	if (W->nextwp)
//events	{
//events		info_waypoint*	nextwp=*Persons2::ConvertPtrUID(W->nextwp);
//events		W->vel = nextwp->vel;
//events	}
//events	WayPointFormEdits = false;
//events	RefreshWayPointForm();
//events//	MissionEditor->PaintBox->Invalidate();
//events
//events	EventForm->SetEventVars(&W->events);
//events
}
//---------------------------------------------------------------------------
void __fastcall TWayPointForm::EventBeforeClick(TObject *Sender)
{
//events	InsertWPBefore(MissionEditor->currwp);
//events	info_waypoint* W=*Persons2::ConvertPtrUID(MissionEditor->currwp);
//events	W->events=new	info_event;
//events	UniqueID	up,un=W->nextwp;
//events	if (W->prevwp)
//events		up=W->prevwp;
//events	else
//events		up=W->owner;
//events	W->pos.MakeIcptIPCWorldPos(up,un);
//events	W->pos[1][1]=new	RndExpr;
//events	W->pos[1][1][0]=50;
//events	W->pos[1][1][2]=0;
//events	W->range = 400000;
//events
//events	if (W->nextwp)
//events	{
//events		info_waypoint*	nextwp=*Persons2::ConvertPtrUID(W->nextwp);
//events		W->vel = nextwp->vel;
//events	}
//events
//events	WayPointFormEdits = false;
//events	RefreshWayPointForm();
//events//	MissionEditor->PaintBox->Invalidate();
//events
//events	EventForm->SetEventVars(&W->events);
//events

}
//---------------------------------------------------------------------------
void __fastcall TWayPointForm::RouteListBoxChange(TObject *Sender)
{

	SWord	tempindex = RouteListBox->ItemIndex;
	RodsWayPoint*	currwp;


	if (tempindex)
	{
		info_grndgrp* G=*Persons2::ConvertPtrUID(MissionEditor->currobj);
		UniqueID	u=G->wpref;
		MissionEditor->currwp = u;

		while	(--tempindex)
		{
			info_waypoint* W=*Persons2::ConvertPtrUID(MissionEditor->currwp);
			u=W->nextwp;
			MissionEditor->currwp = u;
		}
		WayPointFormEdits = false;
		RefreshWayPointForm();
//		MissionEditor->PaintBox->Invalidate();

	}
	else
	{
		RouteListBox->ItemIndex = 1;
		Close();
		MissionEditor->currwp = UID_Null;
		MissionEditor->ShowItemDialog(Left,Top);
	}

}
//---------------------------------------------------------------------------
void	__fastcall TWayPointForm::ShowWpDialog(int X, int Y)
{

	info_waypoint* W=*Persons2::ConvertPtrUID(MissionEditor->currwp);

//	W->pos.EvalW(W->World);


	int left = WayPointForm->Left;
	int top = WayPointForm->Top;

	MissionEditor->FormCoords(X,Y,WayPointFormId,left,top,
							WayPointForm->Width,WayPointForm->Height);

	WayPointForm->Left = left;
	WayPointForm->Top = top;

	WayPointFormEdits = false;
	SetMoveOnButtons();
	wpvel = W->vel;                      
	wprange = W->range.Evaluate();
   

	RefreshWayPointForm();
	Show();
}


//---------------------------------------------------------------------------
void	__fastcall TWayPointForm::FillWpActionList()
{

	info_grndgrp* G=*Persons2::ConvertPtrUID(MissionEditor->currobj);


	if (!MissionEditor->currwp)
	{
//		info_grndgrp* G=*Persons2::ConvertPtrUID(MissionEditor->currobj);
		MissionEditor->currwp = G->wpref;
	}
	info_waypoint* W=*Persons2::ConvertPtrUID(MissionEditor->currwp);
	int act=W->wpact.Evaluate();
	if (act==ENABLE_COMPLEX_VAL)
		act=0;
//	MissionEditor->FillComboBox(IDS_TEXT_FLYWPACNOACTIONNO,
//								IDS_TEXT_FLYWPTELEPORTNEXT,
//											WPActionComboBox,
//											act);
//
	if ((int)G->Status.size > (int)MOBILESIZE)
	{
		{
			int targ=W->target.Evaluate();
			if (!W->nextwp)
			{
				MissionEditor->PartFillComboBox(ENUM_Action,64,
											WPActionComboBox,
											act,
											AirCraftLastWP);
			}else if (targ!=ENABLE_COMPLEX_VAL)
			{
				MissionEditor->PartFillComboBox(ENUM_Action,64,
											WPActionComboBox,
											act,
											AirCraftActionsTarget);
			}else
			{
				MissionEditor->PartFillComboBox(ENUM_Action,64,
											WPActionComboBox,
											act,
											AirCraftActionsNoTarget);
			}
		}


	}else
	{
			MissionEditor->PartFillComboBox(ENUM_Action,64,
										WPActionComboBox,
										act,
										MobileActions);

	}

		if 	(!W->nextwp)
			WPActionComboBox->Enabled = false;
		else
			WPActionComboBox->Enabled = true;



//    WPActionComboBox->ItemIndex =   MissionEditor->CurrWp->WPAction;
}
//---------------------------------------------------------------------------
void	__fastcall TWayPointForm::FillEventRangeList()
{
//	char buff[50];
//	EventRangeComboBox->Items->Clear();

//	SWord j = 0;
//    int	min =  IDS_TEXT_ENCOUNTERRANGESTANDARD;
//    int	max =  IDS_TEXT_ENCOUNTERRANGE7000;
//	while ((min+j) <= max)
//	{
// 		LoadString(HInstance,min+j,buff,sizeof(buff));
//	    EventRangeComboBox->Items->Add(buff);
 //	    j++;
 //	}

	if (!MissionEditor->currwp)
	{
		info_grndgrp* G=*Persons2::ConvertPtrUID(MissionEditor->currobj);
		MissionEditor->currwp = G->wpref;
	}
	info_waypoint* W=*Persons2::ConvertPtrUID(MissionEditor->currwp);
	int rng=W->range.Evaluate();
	if (rng==ENABLE_COMPLEX_VAL)
		rng=0;
	rng = (rng - 200000)	/100000;

	MissionEditor->FillComboBox(IDS_TEXT_ENCOUNTERRANGE2000,
									IDS_TEXT_ENCOUNTERRANGE7000,
											EventRangeComboBox,
											rng);

//    EventRangeComboBox->ItemIndex =   MissionEditor->CurrWp->encounterrange;
}


//---------------------------------------------------------------------------
void	__fastcall TWayPointForm::FillRouteList()
 {
	char buff[50];
	SWord tempindex = 1,currindex = 1;

	RouteListBox->Items->Clear();
	LoadString(HInstance,TEXT_STARTWP,buff,sizeof(buff));
//DeadCode RDH 16Oct97 	RouteListBox->Items->Add("Start");
	RouteListBox->Items->Add(buff);

	info_grndgrp* G=*Persons2::ConvertPtrUID(MissionEditor->currobj);
	UniqueID	u=G->wpref;
	while (u)
	{
		info_waypoint* W=*Persons2::ConvertPtrUID(u);
		if (W->nextwp)
		{
			if (W->events)
			{
				LoadString(HInstance,TEXT_EVENTINLIST,buff,sizeof(buff));
				RouteListBox->Items->Add(IntToStr((int) tempindex) + buff );
//				RouteListBox->Items->Add(IntToStr((int) tempindex) + " (Event)" );
			}
			else
			{
				LoadString(HInstance,TEXT_WAYPOINTINLIST,buff,sizeof(buff));
				RouteListBox->Items->Add(IntToStr((int) tempindex) + buff );

			//	RouteListBox->Items->Add(IntToStr((int) tempindex) + " (Waypoint)" );
			}
		}
		else
//DeadCode RDH 16Oct97 			RouteListBox->Items->Add("Final");
		{
			LoadString(HInstance,TEXT_FINALWP,buff,sizeof(buff));
			RouteListBox->Items->Add(buff);
		}

		if ((int)MissionEditor->currwp == (int)u)
			RouteListBox->ItemIndex = tempindex;
		u = W->nextwp;
		tempindex++;
#include "strings.h"
	};

 //	if (RouteListBox->ItemIndex <1)
//		EventFromWPLabel->Caption = "Start";
//    else
//	    EventFromWPLabel->Caption = "WP " + IntToStr(RouteListBox->ItemIndex-1);
//    EventToWPLabel->Caption = "WP " + IntToStr(RouteListBox->ItemIndex+1);

 }

void __fastcall TWayPointForm::WPActionComboBoxChange(TObject *Sender)
{
//     MissionEditor->CurrWp->WPAction = WPActionComboBox->ItemIndex;
	WayPointFormEdits = true;
	SetMoveOnButtons();

//	RefreshWayPointForm();
//	MissionEditor->PaintBox->Invalidate();

}
//---------------------------------------------------------------------------
void __fastcall TWayPointForm::WpNextClick(TObject *Sender)
{

	info_waypoint* W=*Persons2::ConvertPtrUID(MissionEditor->currwp);
	if (W->nextwp)
		MissionEditor->currwp  = W->nextwp;

	W=*Persons2::ConvertPtrUID(MissionEditor->currwp);
	wpvel = W->vel;
	wprange = W->range.Evaluate();

	AcMovetoClick(Sender);
	WayPointFormEdits = false;
	RefreshWayPointForm();
//	MissionEditor->PaintBox->Invalidate();

}
//---------------------------------------------------------------------------
void __fastcall TWayPointForm::WpPrevClick(TObject *Sender)
{
	info_waypoint* W=*Persons2::ConvertPtrUID(MissionEditor->currwp);
	if (W->prevwp)
		MissionEditor->currwp  = W->prevwp;

	W=*Persons2::ConvertPtrUID(MissionEditor->currwp);
	wpvel = W->vel;
	wprange = W->range.Evaluate();

	AcMovetoClick(Sender);
	WayPointFormEdits = false;
	RefreshWayPointForm();
//	MissionEditor->PaintBox->Invalidate();


}
//---------------------------------------------------------------------------
void __fastcall TWayPointForm::AcMovetoClick(TObject *Sender)
{
		Coords3D C=Persons2::ConvertPtrUID(MissionEditor->currwp)->World;
		MissionEditor->ScreenPosition((int&)C.X,(int&)C.Z);
		MissionEditor->CentreSetScrollBars(C.X,C.Z);
//		MissionEditor->PaintBox->Invalidate();
}
//---------------------------------------------------------------------------
void __fastcall TWayPointForm::EventMoreClick(TObject *Sender)
{
	info_waypoint* W=*Persons2::ConvertPtrUID(MissionEditor->currwp);
//	if (W->events->bfields.Evaluate()==ENABLE_COMPLEX_VAL)
//	{
///		ChooseBfForm->InitEventInfo(W->events);
//		ChooseBfForm->GoToChooseBf(W->events);
//	}else
//	{
//		EventForm->SetEventVars(&W->events);
//	}


}
//---------------------------------------------------------------------------
void __fastcall TWayPointForm::FixedOffsetEditChange(TObject *Sender)
{

	FixedOffsetEditMade();
}
//---------------------------------------------------------------------------
void __fastcall TWayPointForm::FixedOffsetEditMade()
{

	info_waypoint* W=*Persons2::ConvertPtrUID(MissionEditor->currwp);
//	if (!(FixedOffsetEdit->Text.IsEmpty()))
//	{
//		int base=StrToInt(FixedOffsetEdit->Text);
	if (W->events)
	{
		int base = MissionEditor->ValidEdit(FixedOffsetEdit);
	   if (base)
	   {
			int delta=MissionEditor->ValidEdit(RandomOffsetEdit);
			if (base>=100)
				base=99;
			if (base<=0)
				base=1;
			if (delta<=0)
				delta=0;
			if (base+delta>=100)
				delta=100-base;
			W->position[1][1][0]=base;
			W->position[1][1][2]=delta;
			ReposEventWp(MissionEditor->currwp);
			RefreshWayPointForm();
//			MissionEditor->PaintBox->Invalidate();
		 }
	}
}

//---------------------------------------------------------------------------
void __fastcall TWayPointForm::RandomOffsetEditChange(TObject *Sender)
{
	RandomOffsetEditMade();

}

//---------------------------------------------------------------------------
void __fastcall TWayPointForm::RandomOffsetEditMade()
{
	info_waypoint* W=*Persons2::ConvertPtrUID(MissionEditor->currwp);
	if (W->events)
	{
		if (!(RandomOffsetEdit->Text.IsEmpty()))
		{
			int base=MissionEditor->ValidEdit(FixedOffsetEdit);
			int delta=MissionEditor->ValidEdit(RandomOffsetEdit);
			if (delta>=100)
				delta=99;
			if (base<=0)
				base=1;
			if (delta<=0)
				delta=0;
			if (base+delta>=100)
				base=100-delta;
			W->position[1][1][0]=base;
			W->position[1][1][2]=delta;
			ReposEventWp(MissionEditor->currwp);
			RefreshWayPointForm();
//			MissionEditor->PaintBox->Invalidate();
		}
	}

}

//---------------------------------------------------------------------------
void __fastcall TWayPointForm::PositionEvents()
{
	if (MissionEditor->currwp)
	{
		info_waypoint* W=*Persons2::ConvertPtrUID(MissionEditor->currwp);
		if (W->prevwp)
		{
			info_waypoint* P=*Persons2::ConvertPtrUID(W->prevwp);
			if (P->events)
			{
				P->position[1][0][1]=MissionEditor->currwp;
				ReposEventWp(W->prevwp);
			}
		}

		if (W->nextwp)
		{
			info_waypoint* P=*Persons2::ConvertPtrUID(W->nextwp);
			if (P->events)
			{
				P->position[0]=MissionEditor->currwp;
				P->position[1][0][0]=MissionEditor->currwp;
				ReposEventWp(W->nextwp);
			}
		}
	}

}
//---------------------------------------------------------------------------
void __fastcall TWayPointForm::ReposEventWp(UniqueID u)
{
	info_waypoint* W=*Persons2::ConvertPtrUID(u);
	W->position.EvalW(W->World);
}

//---------------------------------------------------------------------------
void __fastcall TWayPointForm::WpAcceptClick(TObject *Sender)
{
//	MissionEditor->MissionEdited=true;
	info_waypoint* W=*Persons2::ConvertPtrUID(MissionEditor->currwp);
	info_grndgrp* G=*Persons2::ConvertPtrUID(MissionEditor->currobj);
	MissionEditor->loadedbfs[G->bfieldindex].changed=true;
	int targ=W->target.Evaluate();

//	if (W->events)
//		W->range = EventRangeComboBox->ItemIndex;
//	else
	{
		if (WPActionComboBox->ItemIndex!=0 || W->wpact.Evaluate()!=ENABLE_COMPLEX_VAL)
		{
			if ((int)G->Status.size > (int)MOBILESIZE)
			{
//					int targ=W->target.Evaluate();

					if (!W->nextwp)
					{
						W->wpact = MissionEditor->FindOrginalIndex(0,64,
												WPActionComboBox->ItemIndex,
												AirCraftLastWP);
					}else if (targ!=ENABLE_COMPLEX_VAL)
					{
						W->wpact = MissionEditor->FindOrginalIndex(0,64,
												WPActionComboBox->ItemIndex,
												AirCraftActionsTarget);
					}else
					{
						W->wpact = MissionEditor->FindOrginalIndex(0,64,
												WPActionComboBox->ItemIndex,
												AirCraftActionsNoTarget);
					}
				if 	(!W->nextwp)
					WPActionComboBox->Enabled = false;
				else
					WPActionComboBox->Enabled = true;

			}else
			{
						W->wpact = MissionEditor->FindOrginalIndex(0,64,
												WPActionComboBox->ItemIndex,
													MobileActions);
			}
		}

			int alt = MissionEditor->ValidEdit(WPAltEdit);
		  if (MissionEditor->Configure_Units == METRIC)
		  {
			W->range = 100 * MissionEditor->ValidEdit(RangeEdit);
//			W->vel = (MissionEditor->ValidEdit(SpeedEdit) * 100+50)/36;


			if (W->position[0].complex && W->position[0]->type==Expr::EXPR_XYZ)
			{
				if (targ!=ENABLE_COMPLEX_VAL)
					W->position[0][1] = alt * 100;
				else
					W->position[0][1] = -alt * 100;
			}else
			{
				if (W->position[1].complex && W->position[1]->type==Expr::EXPR_XYZ)
				{
					if (targ!=ENABLE_COMPLEX_VAL)
						W->position[1][1] = alt * 100;
					else
						W->position[1][1] = -alt * 100;
				}
			}

		  }else if (MissionEditor->Configure_Units == IMPERIAL)
		  {
			W->range = 3048 * MissionEditor->ValidEdit(RangeEdit)/100;
//			W->vel = (MissionEditor->ValidEdit(SpeedEdit) * 1000+500)/224;
			if ((int)W->range == (int)0)
				W->range = 305;

			if (W->position[0].complex && W->position[0]->type==Expr::EXPR_XYZ)
			{
				if (targ!=ENABLE_COMPLEX_VAL)
					W->position[0][1] = alt * 3048/100;
				else
					W->position[0][1] = -alt * 3048/100;
			}else
			{	if (W->position[1].complex && W->position[1]->type==Expr::EXPR_XYZ)
				{
					if (targ!=ENABLE_COMPLEX_VAL)
						W->position[1][1] = alt * 3048/100;
					else
						W->position[1][1] = -alt * 3048/100;
				}
			}
		  }else
		  {
			W->range = 100 * MissionEditor->ValidEdit(RangeEdit);
//			W->vel = (MissionEditor->ValidEdit(SpeedEdit) * 100+50)/36;

			if (W->position[0].complex && W->position[0]->type==Expr::EXPR_XYZ)
			{
				if (targ!=ENABLE_COMPLEX_VAL)
					W->position[0][1] = alt * 3048/100;
				else
					W->position[0][1] = -alt * 3048/100;
			}else
			{
				if (W->position[1].complex && W->position[1]->type==Expr::EXPR_XYZ)
				{
					if (targ!=ENABLE_COMPLEX_VAL)
						W->position[1][1] = alt * 3048/100;
					else
						W->position[1][1] = -alt * 3048/100;
				}
			}
		  }
		W->vel = wpvel;

		W->position.EvalW(W->World);
		if (W->target.Evaluate()!=ENABLE_COMPLEX_VAL)
		{
			Coords3D& c=Persons2::ConvertPtrUID(UniqueID(W->target.Evaluate()))->World;
			W->World.X+=c.X+MissionEditor->zoomiconsize;
			W->World.Z+=c.Z-MissionEditor->zoomiconsize;
		}
	}
	wpvel = W->vel;
	WayPointFormEdits = false;
	SetMoveOnButtons();


}
//---------------------------------------------------------------------------
void __fastcall TWayPointForm::WPAltEditChange(TObject *Sender)
{

	WayPointFormEdits = true;
	SetMoveOnButtons();

}
//---------------------------------------------------------------------------
void __fastcall TWayPointForm::WpUndoClick(TObject *Sender)
{

//	info_waypoint* W=*Persons2::ConvertPtrUID(MissionEditor->currwp);
//	W->vel = wpvel;
//	wprange = W->range;
//	RefreshWayPointForm();
//	WayPointFormEdits = false;
//	SetMoveOnButtons();

	info_waypoint* W=*Persons2::ConvertPtrUID(MissionEditor->currwp);
	W->position.EvalW(W->World);
	if (W->target.Evaluate()!=ENABLE_COMPLEX_VAL)
	{
		Coords3D& c=Persons2::ConvertPtrUID(UniqueID(W->target.Evaluate()))->World;
		W->World.X+=c.X+MissionEditor->zoomiconsize;
		W->World.Z+=c.Z-MissionEditor->zoomiconsize;
	}

	WayPointFormEdits = false;
	ShowWpDialog(0,0);

}
//---------------------------------------------------------------------------
void __fastcall TWayPointForm::PositionButtonClick(TObject *Sender)
{
//	info_waypoint* W=*Persons2::ConvertPtrUID(MissionEditor->currwp);
  //	MissionEditor->UIDLocation=(UniqueID*)&W->target;
//
  //	MissionEditor->SetFindingStaticMode(SETWAYPOINT);

	MissionEditor->draggingdelay=DRAGGINGLEFT;
	Close();
//	MissionEditor->PaintBox->Invalidate();
	MissionEditor->FastClick=false;
}
//---------------------------------------------------------------------------

void __fastcall TWayPointForm::FixedOffsetEditKeyPress(TObject *Sender,
	char &Key)
{
	if (Key == Char(VK_RETURN))
		FixedOffsetEditMade();

}
//---------------------------------------------------------------------------
void __fastcall TWayPointForm::RandomOffsetEditKeyPress(TObject *Sender,
	char &Key)
{
	if (Key == Char(VK_RETURN))
		RandomOffsetEditMade();

}
//---------------------------------------------------------------------------
void __fastcall TWayPointForm::FixedOffsetEditKeyDown(TObject *Sender,
	WORD &Key, TShiftState Shift)
{
	if (Key == Char(VK_RETURN))


		FixedOffsetEditMade();


}
//---------------------------------------------------------------------------
void __fastcall TWayPointForm::FixedOffsetEditKeyUp(TObject *Sender, WORD &Key,
	TShiftState Shift)
{
	if (Key == Char(VK_RETURN))


		FixedOffsetEditMade();

}
//---------------------------------------------------------------------------
void __fastcall TWayPointForm::RandomOffsetEditKeyUp(TObject *Sender, WORD &Key,
	TShiftState Shift)
{
	if (Key == Char(VK_RETURN))
		RandomOffsetEditMade();

}

//---------------------------------------------------------------------------
void __fastcall TWayPointForm::EtaUpdate()
{
	int starttime,legtime;
	int vel;

	info_waypoint* W=*Persons2::ConvertPtrUID(MissionEditor->currwp);
		starttime = LegStartTime(W);
		vel = wpvel;
		FindVel(vel,W);
		legtime = LegTime(vel,W);
		etas = starttime + legtime;
}
//---------------------------------------------------------------------------
void __fastcall TWayPointForm::EtaSpeedBitBtnClick(TObject *Sender)

{
	MissionEditor->ShowWPvel ^=	true;
	RefreshWayPointForm();
   WpSpeedBtn->Default = false;
//	MissionEditor->PaintBox->Invalidate();


}
//---------------------------------------------------------------------------
void __fastcall TWayPointForm::RangeEditChange(TObject *Sender)
{
	WayPointFormEdits = true;
	SetMoveOnButtons();

}
// rdh//---------------------------------------------------------------------------
// rdhvoid __fastcall TWayPointForm::MinEtaEditChange(TObject *Sender)
// rdh{
// rdh
// rdh
// rdh	int etam;
// rdh	int etah;
// rdh   etah = MissionEditor->ValidEdit(HrEtaEdit);
// rdh   etam = MissionEditor->ValidEdit(MinEtaEdit);
// rdh   if (	(!HrEtaEdit->Text.IsEmpty())
// rdh		   &&(!MinEtaEdit->Text.IsEmpty())
// rdh	)
// rdh   {
// rdh	   etas = etah * 3600 + etam * 60;
// rdh		OnEtaChange();
// rdh		WayPointFormEdits = true;
// rdh		SetMoveOnButtons();
// rdh   }
// rdh}
// rdh//---------------------------------------------------------------------------
// rdhvoid __fastcall TWayPointForm::HrEtaEditChange(TObject *Sender)
// rdh{
// rdh	int etam = MissionEditor->ValidEdit(MinEtaEdit);
// rdh	int etah = MissionEditor->ValidEdit(HrEtaEdit);
// rdh
// rdh   if (	(!HrEtaEdit->Text.IsEmpty())
// rdh		   &&(!MinEtaEdit->Text.IsEmpty())
// rdh	)
// rdh   {
// rdh
// rdh	   etas = etah * 3600 + etam * 60;
// rdh
// rdh		OnEtaChange();
// rdh		WayPointFormEdits = true;
// rdh		SetMoveOnButtons();
// rdh   }
// rdh}
//---------------------------------------------------------------------------
void __fastcall TWayPointForm::SpeedEditChange(TObject *Sender)
{
	info_waypoint* W=*Persons2::ConvertPtrUID(MissionEditor->currwp);
	info_grndgrp*	tmp=*Persons2::ConvertPtrUID(MissionEditor->currobj);


	if (MissionEditor->Configure_Units == METRIC)
		wpvel =  (50+100 * (int)StrToInt(SpeedEdit->Text)) /36;
	else if (MissionEditor->Configure_Units == IMPERIAL)
		wpvel =  (500+1000 * (int)StrToInt(SpeedEdit->Text)) /224;
	else
		wpvel =  (50+100 * (int)StrToInt(SpeedEdit->Text)) /36;
                                            

	  
	if ((int)wpvel > (int)typedata[tmp->type].maxvel)
		wpvel = typedata[tmp->type].maxvel; 
	if ((int)wpvel < (int)typedata[tmp->type].climbvel)
		wpvel = typedata[tmp->type].climbvel; 
											
	if ((int)wpvel == (int)typedata[tmp->type].cruisevel)
	wpvel = ENABLE_COMPLEX_VAL;
	  
	WayPointFormEdits = true;
	SetMoveOnButtons();
	RefreshWayPointForm();
//  MissionEditor->PaintBox->Invalidate();
   

}
//---------------------------------------------------------------------------
int __fastcall TWayPointForm::LegStartTime(info_waypoint* W)
{
	int		legtime;
	int		starttime = 1000;//camp MissionEditor->ActiveCampaign.mission[MissionEditor->currmission].timeofday;  
	int 	vel;
   	
	info_grndgrp*  owner = *Persons2::ConvertPtrUID(MissionEditor->currobj);


	info_waypoint*	targetwp;
	if (W->prevwp)
	{
		targetwp =  *Persons2::ConvertPtrUID(W->prevwp);
		if (targetwp->events)									//RDH 03Oct97
			targetwp =  *Persons2::ConvertPtrUID(targetwp->prevwp);//RDH 03Oct97
	}else
	{
	   	targetwp = (info_waypoint*) owner;
	}
	info_waypoint*	startleg;

	startleg = (info_waypoint*) owner;
	info_waypoint* endleg = *Persons2::ConvertPtrUID(owner->wpref);


	while (startleg != targetwp)
	{


		vel = endleg->vel;
		FindVel(vel,endleg);
		legtime = LegTime(vel, endleg);

		starttime += legtime;

		startleg = endleg;
		endleg=*Persons2::ConvertPtrUID(startleg->nextwp);
		if (endleg->events)									//RDH 03Oct97
			endleg =  *Persons2::ConvertPtrUID(endleg->nextwp);//RDH 03Oct97

	}

	return (starttime);
}
//---------------------------------------------------------------------------
void __fastcall TWayPointForm::OnEtaChange()
{
	info_grndgrp*	tmp=*Persons2::ConvertPtrUID(MissionEditor->currobj);
	info_waypoint* W=*Persons2::ConvertPtrUID(MissionEditor->currwp);
	int starttime,legtime;
	
	starttime = LegStartTime(W);

	int requiredlegtime  = (int) etas - starttime;

	int maxlegtime = LegTime(typedata[tmp->type].climbvel,W);
	int minlegtime = LegTime(typedata[tmp->type].maxvel,W);

	if (requiredlegtime  >maxlegtime)
			requiredlegtime  = maxlegtime;
//			form: time requested too long, required ave vel =
//					min ave vel possible for this leg =
//					cruise, best climb =

	if (requiredlegtime <minlegtime)
			requiredlegtime  = minlegtime;
//			form: time requested too short,
//					min time =
//					vel = max

   wpvel =  LegVel(requiredlegtime, W);
   EtaUpdate();
	RefreshWayPointForm();
//   MissionEditor->PaintBox->Invalidate();


}
//---------------------------------------------------------------------------
int __fastcall TWayPointForm::LegTime (int levelvel,info_waypoint* W)
{

	info_grndgrp*  owner = *Persons2::ConvertPtrUID(MissionEditor->currobj);


	int descenttime=0,climbtime=0,flattime=0,totaltime=0;
	double	climbdist,descentdist;

	short sinpitch,cospitch;
	short sinbestclimbpitch,cosbestclimbpitch;

	info_waypoint*	prev;
	if (W->prevwp)
	{
		prev =  *Persons2::ConvertPtrUID(W->prevwp);
		if (prev->events)									//RDH 03Oct97
			prev =  *Persons2::ConvertPtrUID(prev->prevwp);//RDH 03Oct97
	}else
	{
		prev = (info_waypoint*) owner;
	}
	SLong dx =   W->World.X -  prev->World.X;
	SLong dy =   -(W->World.Y	-  prev->World.Y);
	SLong dz =   W->World.Z	-  prev->World.Z;

	if (dx==0 && dz==0)			//JIM sun
		return 0;
		
	Math_Lib.Intercept (dx,dy,dz,Range,HdgIntercept,PitchIntercept);
	Math_Lib.sin_cos(PitchIntercept,sinpitch,cospitch); 	

	int	range = Range;

	SWord bestclimbpitch = (SWord)BestClimbwrtAlt(W);
	Math_Lib.sin_cos(bestclimbpitch,sinbestclimbpitch,cosbestclimbpitch);

//	if ((SWord) PitchIntercept > bestclimbpitch)
//		{
//			form: the aircraft cannot climb as steeply as requested
//			worldy = first worldy + tan best pitch * 2d dist
//		}


	if ((SWord) PitchIntercept > 0)
	{
		climbdist = ANGLES_SHIFT * dy / sinbestclimbpitch;
		climbtime = climbdist/(10*typedata[owner->type].climbvel);
		range = range - climbdist;
	}
	if ((SWord) PitchIntercept < 0)
	{

		descentdist = ANGLES_SHIFT * dy / sinpitch;
		descenttime = descentdist/(typedata[owner->type].maxvel*50/4);
		range = range - descentdist;
	}
	flattime = range/(10*levelvel);

	totaltime = climbtime  + descenttime + flattime;
	return(totaltime);


}


//---------------------------------------------------------------------------
int __fastcall TWayPointForm::LegVel (int requiredtime,info_waypoint* W)
{
   int levelvel;
	info_grndgrp*  owner = *Persons2::ConvertPtrUID(MissionEditor->currobj);


	int descenttime=0,climbtime=0,flattime=0,totaltime=0;
	double	climbdist,descentdist;
                                                        
	short sinpitch,cospitch;
	short sinbestclimbpitch,cosbestclimbpitch;

	info_waypoint*	prev;
	if (W->prevwp)
	{
		prev =  *Persons2::ConvertPtrUID(W->prevwp);
		if (prev->events)									//RDH 03Oct97
			prev =  *Persons2::ConvertPtrUID(prev->prevwp);//RDH 03Oct97
	}else
	{
	   	prev = (info_waypoint*) owner;
	}
	SLong dx =   W->World.X -  prev->World.X;
	SLong dy =   -(W->World.Y	-  prev->World.Y);
	SLong dz =   W->World.Z	-  prev->World.Z;

	Math_Lib.Intercept (dx,dy,dz,Range,HdgIntercept,PitchIntercept);
	Math_Lib.sin_cos(PitchIntercept,sinpitch,cospitch); 	

	int	range = Range;

	SWord bestclimbpitch = (SWord)BestClimbwrtAlt(W);
	Math_Lib.sin_cos(bestclimbpitch,sinbestclimbpitch,cosbestclimbpitch);

//	if ((SWord) PitchIntercept > bestclimbpitch)
//		{
//			form: the aircraft cannot climb as steeply as requested
//			worldy = first worldy + tan best pitch * 2d dist
//		}


	if ((SWord) PitchIntercept > 0)
	{
		climbdist = ANGLES_SHIFT * dy / sinbestclimbpitch;
		climbtime = climbdist/(10*typedata[owner->type].climbvel);
	}
	if ((SWord) PitchIntercept < 0)
	{

		descentdist = ANGLES_SHIFT * dy / sinpitch;
		descenttime = descentdist/(typedata[owner->type].maxvel*50/4);
	}

	flattime = requiredtime - climbtime  - descenttime;

	levelvel = range/(10*flattime);

	return(levelvel);


}



//---------------------------------------------------------------------------
ANGLES __fastcall TWayPointForm::BestClimbwrtAlt(info_waypoint* W)
{
	SWord bestclimbpitch;
	UWord		d1,d2,altitude_1000m,altitudeeffect;
	SLong		altitude_cm;
	info_grndgrp*  owner = *Persons2::ConvertPtrUID(MissionEditor->currobj);
                                       
	info_waypoint*	prev;
	if (W->prevwp)
	{
		prev =  *Persons2::ConvertPtrUID(W->prevwp);
		if (prev->events)									//RDH 03Oct97
			prev =  *Persons2::ConvertPtrUID(prev->prevwp);//RDH 03Oct97
	}else
	{
	   	prev = (info_waypoint*) owner;
	}
	altitude_cm =  -(W->World.Y	+  prev->World.Y) / 2;

	if (altitude_cm < 0)
		altitude_cm = 0;
	if (altitude_cm >MAXALTITUDE_CM)
		altitude_cm = MAXALTITUDE_CM;

	altitude_1000m =	(UWord) (altitude_cm/100000);

	d1 =	altitudeeffectdata[altitude_1000m];
	d2 =	altitudeeffectdata[altitude_1000m+1];
	altitudeeffect  = (SWord) (d1+ (d2-d1) * (altitude_cm - altitude_1000m*100000)/100000);
	bestclimbpitch = typedata[owner->type].bestclimbpitch * altitudeeffect  / 100;
	return ((ANGLES)bestclimbpitch);
}

void __fastcall TWayPointForm::Panel1Click(TObject *Sender)
{
   MaskEdit1->SetFocus();
}
//---------------------------------------------------------------------------
void __fastcall TWayPointForm::WpSpeedBtnClick(TObject *Sender)
{
	MissionEditor->ShowWPvel ^=	true;
	RefreshWayPointForm();
//	MissionEditor->PaintBox->Invalidate();
}
//---------------------------------------------------------------------------
void __fastcall TWayPointForm::SpdComboBoxChange(TObject *Sender)
{

	info_waypoint* W=*Persons2::ConvertPtrUID(MissionEditor->currwp);
	info_grndgrp*	tmp=*Persons2::ConvertPtrUID(MissionEditor->currobj);

	switch	(SpdComboBox->ItemIndex)
	{
		case	0:
		{
			wpvel = typedata[tmp->type].climbvel;
			break;
		}
		case	1:
		{
			wpvel = typedata[tmp->type].cruisevel;
			break;
		}
		case	2:
		{
			wpvel = typedata[tmp->type].maxvel;
			break;
		}
		case	3:
		{
			break;
		}
	}
	RefreshWayPointForm();
	WayPointFormEdits = true;
	SetMoveOnButtons();
}
//---------------------------------------------------------------------------
void __fastcall TWayPointForm::SpinButton1DownClick(TObject *Sender)
{
		  if (MissionEditor->Configure_Units == METRIC)
			wprange = 100 * MissionEditor->ValidEdit(RangeEdit);
		  else if (MissionEditor->Configure_Units == IMPERIAL)
			wprange = 3048 * MissionEditor->ValidEdit(RangeEdit)/100;
		  else 
			wprange = 100 * MissionEditor->ValidEdit(RangeEdit);
	if (wprange > 800000)
		wprange = 800000;		

	WPAltEditExit(Sender);
	if (MissionEditor->ShowWPvel)
	{
		SpeedEdit->Text = IntToStr(StrToInt(SpeedEdit->Text) - 1);
   }else
   {
		etas = etas - 60;
		OnEtaChange();
   }
	WayPointFormEdits = true;
	SetMoveOnButtons();
}
//---------------------------------------------------------------------------
void __fastcall TWayPointForm::SpinButton1UpClick(TObject *Sender)
{
		  if (MissionEditor->Configure_Units == METRIC)
			wprange = 100 * MissionEditor->ValidEdit(RangeEdit);
		  else if (MissionEditor->Configure_Units == IMPERIAL)
			wprange = 3048 * MissionEditor->ValidEdit(RangeEdit)/100;
		  else 
			wprange = 100 * MissionEditor->ValidEdit(RangeEdit);
	if (wprange > 800000)
		wprange = 800000;		

	WPAltEditExit(Sender);
	if (MissionEditor->ShowWPvel)      
	{
		SpeedEdit->Text = IntToStr(StrToInt(SpeedEdit->Text) + 1);
   }else
   {
		etas = etas + 60;
		OnEtaChange();
   }
	WayPointFormEdits = true;
	SetMoveOnButtons();

}
//---------------------------------------------------------------------------
void __fastcall TWayPointForm::EventRangeComboBoxChange(TObject *Sender)
{
	info_waypoint* W=*Persons2::ConvertPtrUID(MissionEditor->currwp);
	W->range = (EventRangeComboBox->ItemIndex * 100000) + 200000;

}
//---------------------------------------------------------------------------
void __fastcall TWayPointForm::WPAltEditExit(TObject *Sender)
{
	info_waypoint* W=*Persons2::ConvertPtrUID(MissionEditor->currwp);

		  if (MissionEditor->Configure_Units == METRIC)
				W->World.Y = -MissionEditor->ValidEdit(WPAltEdit) * 100;
		  else if (MissionEditor->Configure_Units == IMPERIAL)
				W->World.Y = -MissionEditor->ValidEdit(WPAltEdit) * 3048/100;
		  else
				W->World.Y = -MissionEditor->ValidEdit(WPAltEdit) * 3048/100;
	if (W->target.Evaluate() != ENABLE_COMPLEX_VAL)	//RH mon
		W->World.Y=-W->World.Y;	//JT sun
	if (W->World.Y > 500000)
		W->World.Y = 500000;
	if (W->World.Y < -500000)
		W->World.Y = -500000;

	RefreshWayPointForm();

}
//---------------------------------------------------------------------------
void __fastcall TWayPointForm::RangeEditExit(TObject *Sender)
{
		  if (MissionEditor->Configure_Units == METRIC)
			wprange = 100 * MissionEditor->ValidEdit(RangeEdit);
		  else if (MissionEditor->Configure_Units == IMPERIAL)
			wprange = 3048 * MissionEditor->ValidEdit(RangeEdit)/100;
		  else
			wprange = 100 * MissionEditor->ValidEdit(RangeEdit);
	if (wprange > 800000)
		wprange = 800000;
	RefreshWayPointForm();

}
//---------------------------------------------------------------------------
void __fastcall TWayPointForm::ResetTargetAction()
{
	info_waypoint*	W=*Persons2::ConvertPtrUID(MissionEditor->currwp);
	SWord j = 0,newact = 0;
	int act=W->wpact.Evaluate();


	while ((IDS_TEXT_FLYWPACNOACTIONNO+j) <= IDS_TEXT_FLYWPTELEPORTNEXT)
	{
		if	(AirCraftActionsNoTarget[j] != -1)
			if	(j == act)
			newact = j;
		j++;
	}
 if (!newact)
	W->wpact = newact;

	
}

void __fastcall TWayPointForm::WpAcceptMouseUp(TObject *Sender,
	TMouseButton Button, TShiftState Shift, int X, int Y)
{
	WpAcceptClick(Sender);	
}
//---------------------------------------------------------------------------
void __fastcall TWayPointForm::WaypointCloseClick(TObject *Sender)
{
	Close();	
}
//---------------------------------------------------------------------------

