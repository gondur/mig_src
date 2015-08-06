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
//Filename       globrefs.cpp
//System         
//Author         Jim Taylor
//Date           Tue 19 Mar 1996
//Description    Main program interface to global refs table
//				There are 2 types of global reference - internal and external
//				Internal references simply communicate information from the
//				battlefield header into the battlefield body.
//				Internal references can also communicate between battlefields,
//				either by generous luck, or in the events system.
//				External references are when the battlefield has access to a
//				variable in the main program. It may be setting the value as a 
//				flag to the program, or reading a value set by the main program.
//				Internal references are declared in this file
//				External references are fixed up in this file using #define 
//				or reference variables to fix the globref name to the real name.
//				I need a mechanism which allows this to be controlled. 
//				I think this definitely means using #defines.
//------------------------------------------------------------------------------

#include	"DosDefs.h"
#include	"files.g"
#include	"node.h"											//DAW 29Jun99
#include	"Makebf.h"
#include	"textref.h"
#include	"Persons2.h"
#include	"viewsel.h"
#include	"transite.h"										//PD 29Apr96
#include	"Miles.h"
//DeadCode DAW 29Jun99 #include	"node.h"
//------------------------------------------------------------------------------
//declare your internal variables and global #defines here:
//Intenal variables that are hidden:
//
enum	{MAX_PACK_TARG=25};
ULong	
		GR_WPP_Rendevous=0,		//set and cleared directly by package routes
		GR_WPP_Ingress=0,
		GR_WPP_Target=0,
		GR_WPP_Regroup=0,
		GR_WPP_Egress=0,
		GR_WPP_Disperse=0,
		GR_WPC_Rendevous=0,
		GR_WPC_Ingress=0,
		GR_WPC_Target=0,
		GR_WPC_Regroup=0,
		GR_WPC_Egress=0,
		GR_WPC_Disperse=0,

		GR_Pack_Targ[MAX_PACK_TARG][2]={0},
		GR_Pack_Sq_Used[SQ_R_NONFLYABLE+1]={0},		//inc Yak
		GR_Pack_Home[8]={0},
		GR_Scram_Alt[8]={0},
		GR_Scram_AC[8]={0},
		GR_Scram_Skill[8]={0},
		GR_Scram_Squad[8]={0},
		GR_Pack_TakeTime[8][3]={0};

//GR_PACK_LAST;

#define refto8(pre,pre2,post)	\
	pre##0##post=pre2 [0],\
	pre##1##post=pre2 [1], \
	pre##2##post=pre2 [2],	\
	pre##3##post=pre2 [3],	 \
	pre##4##post=pre2 [4],	  \
	pre##5##post=pre2 [5],	   \
	pre##6##post=pre2 [6],		\
	pre##7##post=pre2 [7]


#define refto5(pre,pre2,post)	\
	pre##0##post=pre2 [0],\
	pre##1##post=pre2 [1], \
	pre##2##post=pre2 [2],	\
	pre##3##post=pre2 [3],	 \
	pre##4##post=pre2 [4],	  \
	pre##5##post=pre2 [5]

#define	reftoG(pre,pre2)	\
	pre##0=pre2[0],		\
	pre##1=pre2[1],		\
	pre##2=pre2[2]		\

#define	reftoW(pre,mid,pre2)		\
	reftoG(pre##0##mid,pre2[0]),	\
	reftoG(pre##1##mid,pre2[1]),	\
	reftoG(pre##2##mid,pre2[2]),	\
	reftoG(pre##3##mid,pre2[3]),	\
	reftoG(pre##4##mid,pre2[4]),	\
	reftoG(pre##5##mid,pre2[5]),	\
	reftoG(pre##6##mid,pre2[6]),	\
	reftoG(pre##7##mid,pre2[7])

#define	pair(pre,pre2)	\
	pre##0=pre2[0],		\
	pre##1=pre2[1]

#define	pair04(pre,mid,pre2)	\
	pair(pre##0##mid,pre2##0]),	\
	pair(pre##1##mid,pre2##1]),	\
	pair(pre##2##mid,pre2##2]),	\
	pair(pre##3##mid,pre2##3]),	\
	pair(pre##4##mid,pre2##4])

#define	pair59(pre,mid,pre2)	\
	pair(pre##5##mid,pre2##5]),	\
	pair(pre##6##mid,pre2##6]),	\
	pair(pre##7##mid,pre2##7]),	\
	pair(pre##8##mid,pre2##8]),	\
	pair(pre##9##mid,pre2##9])


typedef	ULong&	ULongRef;

static	ULongRef	
			refto8(GR_Scram_G,GR_Scram_Alt,_Alt),
			refto8(GR_Scram_G,GR_Scram_AC,_AC),
			refto8(GR_Scram_G,GR_Scram_Skill,_Skill),
			refto8(GR_Scram_G,GR_Scram_Squad,_Squad),
			refto5(GR_Pack_Sq,GR_Pack_Sq_Used,_Used),
			refto8(GR_Pack_Sq,GR_Pack_Home,_Home),
			pair04(GR_Pack_Targ_F,_E,GR_Pack_Targ[),
			pair59(GR_Pack_Targ_F,_E,GR_Pack_Targ[),
			pair04(GR_Pack_Targ_F1,_E,GR_Pack_Targ[1),
			pair59(GR_Pack_Targ_F1,_E,GR_Pack_Targ[1),
			pair04(GR_Pack_Targ_F2,_E,GR_Pack_Targ[2),
			reftoW(GR_Pack_TakeTime_W,G,GR_Pack_TakeTime)
			;

#define pass 1
#include	"globrefs.h"
#undef pass
#define pass 2
#include	"globrefs.h"
#undef pass

void	Persons2::ClearGlobrefPackVars()
{
	for (int i=SGR_WPP_Rendevous;i<=SGR_WPC_Disperse;i++)
		if (Persons2::GetLoc(i)==-i)
			Persons2::SetLoc(i,0);

}
void	Persons2::ResetGlobrefPackVars()
{
	for (int i=SGR_WPP_Rendevous;i<=SGR_WPC_Disperse;i++)
		if (Persons2::GetLoc(i)==0)
			Persons2::SetLoc(i,-i);
}
void	Persons2::ClearGlobrefStaticVars()
{
	for (int i=SGR_WPP_Rendevous;i<=SGR_WPC_Disperse;i++)
		Persons2::SetLoc(i,0);
	for (i=E_first_Static;i<E_static_END;i++)
		names[i]=0;

}
void	Persons2::ClearGlobrefGlobalVars()
{
	for (int i=0;i<8;i++)
	{
		GR_Scram_Alt[i]=0,
		GR_Scram_AC[i]=0,
		GR_Scram_Skill[i]=0,
		GR_Scram_Squad[i]=0;
	}
	for (i=0;i<MAX_PACK_TARG;i++)
		GR_Pack_Targ[i][0]=GR_Pack_Targ[i][1]=0;
	for (i=0;i<=SQ_R_NONFLYABLE;i++)
		GR_Pack_Sq_Used[i]=0;
	for (i=E_first_Global;i<E_global_END;i++)
		names[i]=0;
} 

//------------------------------------------------------------------------------
//  References to variables in the main game
//
//#define	myname	yourname,bits,shift
//TEMP
//#define	GR_Cam_ViewTarg		View_Point.bfviewtarg,0,0
//#define	GR_Cam_ViewMode		View_Point.bfviewmode,0,0
//#define	GR_Cam_CutType		View_Point.bfcuttype,0,0	
//#define	GR_Cam_PanRate		View_Point.bfpanrate,0,0	
//#define	GR_Cam_Zoom			View_Point.bfzoom,0,0		
//#define	GR_Cam_Heading		View_Point.bfheading,0,0	
//#define	GR_Cam_Pitch		View_Point.bfpitch,0,0		
//#define	GR_Cam_RollRate		View_Point.bfrollrate,0,0
//#define	GR_Cam_RotateRate	View_Point.bfrotaterate,0,0
//#define	GR_Cam_CamItem 		View_Point.bfcamitem,0,0
//#define	GR_Cam_TrgtItem		View_Point.bftrgtitem,0,0
//#define	GR_Cam_PitchRate	View_Point.bfpitchrate,0,0
//static	ULong
//	GR_Cam_ViewTarg		,
//	GR_Cam_ViewMode		 ,
//	GR_Cam_CutType		  ,
//	GR_Cam_PanRate		   ,
//	GR_Cam_Zoom				,
//	GR_Cam_Heading			 ,
//	GR_Cam_Pitch			  ,
//	GR_Cam_RollRate			   ,
//	GR_Cam_RotateRate			,
//	GR_Cam_CamItem 				 ,
//	GR_Cam_TrgtItem				  ,
//	GR_Cam_PitchRate			   ;
//TEMP
//#define	GR_AutoBulletCount	Trans_Obj.autobulletcount,0,0
//#define	GR_UIDDeathItem		Trans_Obj.uiddeathitem,0,0
//#define	GR_deathtype		Trans_Obj.deathtype,0,0
//static	ULong
//	GR_AutoBulletCount	,
//	GR_UIDDeathItem		 ,
//	GR_deathtype		  ;
//TEMP
//#define GR_Sample_Play		_Miles.soundtoplay.thesample,16,0
//#define GR_Sample_Volume	_Miles.soundtoplay.vol,0,0
//#define GR_Sample_Pan		_Miles.soundtoplay.pan,0,0
//static	ULong
//	GR_Sample_Play	,
//	GR_Sample_Volume,	
//	GR_Sample_Pan	;	

//------------------------------------------------------------------------------
//Make the actual list:
//
#include	"bfrefs.g"


//------------------------------------------------------------------------------
//Code to access
//

void	Persons2::SetLoc(int	locnum,int value)
{
	ULong imask=(((1L<<BFieldGlobalTable[locnum].fieldsize)>>1)-1);
	ULong omask=imask<<BFieldGlobalTable[locnum].fieldshift;
	ULong nmask=~omask;
	ULong i=*(ULong*)BFieldGlobalTable[locnum].reference;
	i&=nmask;
	value&=imask;
	value<<=BFieldGlobalTable[locnum].fieldshift;
	i|=value;
	*(ULong*)BFieldGlobalTable[locnum].reference=i;
}
int BAD_RV=0x80000000;											//AMM 02Jun98
int&	Persons2::GetLoc(int	locnum)
{
	static int i;
	ULong* p=(ULong*)BFieldGlobalTable[locnum].reference;
	if ((!p))
		return BAD_RV;
	i=*p;
	i>>=BFieldGlobalTable[locnum].fieldshift;
	ULong imask=(((1L<<BFieldGlobalTable[locnum].fieldsize)>>1)-1);
	i&=imask;
	return(i);
}

//DeadCode AMM 02Jun98 int	Persons2::GetLoc(int	locnum)
//DeadCode AMM 02Jun98 {
//DeadCode AMM 02Jun98 	ULong i=*(ULong*)BFieldGlobalTable[locnum].reference;
//DeadCode AMM 02Jun98 	i>>=BFieldGlobalTable[locnum].fieldshift;
//DeadCode AMM 02Jun98 	ULong imask=(((1L<<BFieldGlobalTable[locnum].fieldsize)>>1)-1);
//DeadCode AMM 02Jun98 	i&=imask;
//DeadCode AMM 02Jun98 	return(i);
//DeadCode AMM 02Jun98 }
