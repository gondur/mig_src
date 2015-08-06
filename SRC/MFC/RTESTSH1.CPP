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

// Rtestsh1.cpp : implementation file
//

#include "stdafx.h"
#include "MIG.h"
#include "Rtestsh1.h"
#include	"Stub3d.h"
#define	F_GRAFIX
#include	"files.g"
#include	"missman2.h"
#include	"replay.h"
#include	"smack.h"
#include	"persons2.h"
#include	"globrefs.h"
#include	"imagemap.g"
#include	"imagemap.h"
#include	"gameset.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#ifndef THIS_FILE_DEFINED
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif
//extern	ULong	GR_CloudBase,GR_MainObjective,GR_SubObjective,
//				GR_WP1,GR_WP2,GR_WP3,
//				GR_FriendHomeBase,GR_GlobalSkillMin,GR_GlobalSkillMax,
//				GR_NAT_ENEMY,GR_NAT_FRIEND,
//				GR_FriendlyScoutType00;

//extern Replay _Replay;
extern	ULong	GR_Pack_Targ_S3_E0;
static bool once;

//extern	ULong	
//		GR_Scram_Alt[],GR_Scram_AC[],GR_Scram_Skill[],GR_Scram_Squad[],
//		GR_Pack_Sq_Used[];
//extern	ULong
//		GR_Pack_PlayerSquad,
//		GR_Pack_PlayerPos;
View3d*	Rtestsh1::tmpview=NULL;
Inst3d*	Rtestsh1::tmpinst=NULL;
bool	Rtestsh1::tempblockkeys=false;


/////////////////////////////////////////////////////////////////////////////
// Rtestsh1 dialog
int	Rtestsh1::setup3dstatus=0;
Rtestsh1*	Rtestsh1::THISTHIS=NULL;
Rtestsh1::Rtestsh1(CWnd* pParent /*=NULL*/,bool fIsRunning)
	: RowanDialog(IDD, pParent)

{
	THISTHIS=this;
	setup3dstatus=S3D_STARTSETUP;
	nestedcallsblocker=false;
	wasrunning=fIsRunning;
	if (!fIsRunning) 
		tmpinst=NULL;
//	tmpview=NULL;
//	m_actype=PT_F86A;
	once=true;
	trg_uid=UID_Null;
	tempblockkeys=true;

	//{{AFX_DATA_INIT(Rtestsh1)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Rtestsh1
//Author		Paul.   
//Date			Thu 11 Mar 1999
//------------------------------------------------------------------------------
Rtestsh1::Rtestsh1(UniqueID uid,CWnd* pParent,bool)	: RowanDialog(IDD,pParent)

{
	THISTHIS=this;
	setup3dstatus=S3D_STARTSETUP;
	nestedcallsblocker=false;
	once=true;
	tmpinst=NULL;
	trg_uid=uid;
	tempblockkeys=true;

}

void Rtestsh1::OnCancel()
{
	if (!nestedcallsblocker)
	{
		nestedcallsblocker=true;

		Image_Map.UnLoadImageMapPtrs();

		if (tmpinst)
			tmpinst->Paused(TRUE);
		if (tmpview)
		{
			delete tmpview;
			tmpview=NULL;
		}
		CDialog::OnCancel();
		//OnOk does these when deleting inst3d but cancel doesn't delete the inst3d
		AfxGetMainWnd()->ModifyStyle(WS_THICKFRAME,NULL); // Bye bye border!
		AfxGetMainWnd()->ShowWindow(SW_SHOWMAXIMIZED);
//	nestedcallsblocker=false;	//exitting this dialog. Will get auto reset //JIM 15/04/99
	}


}
static int debugcounter=0;
void	Rtestsh1::OnOK()
{
//DEADCODE JIM 15/04/99 Interesting! Hit AltX then Moue debrief. 
//DEADCODE JIM 15/04/99 This comes up after syserr for double delete!
//DEADCODE JIM 15/04/99  	if (debugcounter++)
//DEADCODE JIM 15/04/99 		INT3;

	if (!nestedcallsblocker)
	{
		nestedcallsblocker=true;
		if (tmpinst)
			tmpinst->Paused(TRUE);
		delete tmpview;
		tmpview=NULL;
		delete tmpinst;
		tmpinst=NULL;
		CDialog::OnOK();
//	nestedcallsblocker=false;	//exitting this dialog. Will get auto reset //JIM 15/04/99
	}

}
Rtestsh1::~Rtestsh1()
{
	THISTHIS=NULL;
	setup3dstatus=S3D_STOPPED;
//done in onok or oncancel before we get here!
//	if (tmpinst)
//		tmpinst->Paused(TRUE);
//	delete tmpview;
//	tmpview=NULL;
//	delete tmpinst;
//	tmpinst=NULL;

//	Persons4::StartUpMapWorld();
}

void Rtestsh1::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Rtestsh1)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
	SetMaxSize(CRect(0,0,1600,1200));
}

void Rtestsh1::OnPaint() 
{
	if (!once)
	{
		CPaintDC dc(this); // device context for painting
		return;
	}
	once=false;
	CDialog::OnPaint();
	CRect rect;
	GetClientRect(rect);
//temp!!!!!!!!!!!!!!!!!!!!!!!	dc.FillSolidRect(rect,RGB(128,128,128));
	Start3d(S3D_DONESHEET);
//	Launch3d(wasrunning);
}

//////////////////////////////////////////////////////////////////////
//
// Function:    Start3d
// Date:		19/06/99
// Author:		JIM
//
//Description: Called from 2 places. After both calls the 3d can be drawn.
//				RV says wether background should be drawn
//
//////////////////////////////////////////////////////////////////////
Rtestsh1::Setup3dStatuses	Rtestsh1::Start3d(Setup3dStatuses stat)
{
	if (setup3dstatus&S3D_STARTSETUP)
	{
		setup3dstatus|=stat;
		if (setup3dstatus==7)
//		if (stat==S3D_DONESHEET)
		{
			setup3dstatus=S3D_GOING;
			THISTHIS->PostMessage( WM_GETSTRING);
			
		}
		return S3D_STARTSETUP;
	}
	return Setup3dStatuses(setup3dstatus);
}

void	Rtestsh1::OnGetString()
{
	Launch3d(wasrunning);
}

void	Rtestsh1::Launch3d(bool flag)
{
	//PROBLEM!!!! MUST NOT do this when running 3d in a window!!!!!!!!!!!!!
	if (gameSettings.m_bFullScreenMode)
		parent->MoveWindow(CRect(-10,-10,1300,1050),FALSE);
	if (tmpinst==NULL)
	{
		if (trg_uid==UID_Null)
		{
		Persons4::ShutDownMapWorld();
		{
//		Miss_Man.currcampaignnum = MissMan::SCRAMBLECAMPAIGN;		//RDH 16Apr96
//		Miss_Man.camp = Miss_Man.campaigntable[MissMan::SCRAMBLECAMPAIGN];
//		Miss_Man.camp.playerbfield =  Scramble_Missions [3]->playerbf; 


			GR_GlobalSkillMin = SKILL_NOVICE;						//RDH 01Oct96
			GR_GlobalSkillMax = SKILL_HERO;							//RDH 01Oct96

			GR_NAT_ENEMY=NAT_RED;
			GR_NAT_FRIEND= NAT_BLUE;
		}
		tmpinst=new Inst3d;
		}
		else
		{
			Persons4::InitViewFromMap(trg_uid);
			tmpinst=new Inst3d(true);
		}
	}
	if (!tmpview)
	{
		tmpview=new View3d(tmpinst,InDialAncestor()->m_hWnd,this);
		if (trg_uid==UID_Null)	tmpview->MakeInteractive(WinMode::WIN,*(CRect*)NULL,false,flag);
		else					tmpview->MakeInteractive(WinMode::WIN,*(CRect*)NULL,true);
	}

//#pragma message("RTestSh1.cpp - paused for profiling")
#ifdef NDEBUG
	if (trg_uid==UID_Null)											  //DAW 18/02/00
		tmpinst->Paused(FALSE);										  //DAW 18/02/00
#endif
	tempblockkeys=false;
}

BEGIN_MESSAGE_MAP(Rtestsh1, CDialog)
	//{{AFX_MSG_MAP(Rtestsh1)
//	ON_BN_CLICKED(IDC_TESTBUTTON, OnTestbutton)
//	ON_BN_CLICKED(ID_B29, OnB29)
//	ON_BN_CLICKED(IDC_ATank, OnATank)
//	ON_BN_CLICKED(IDC_ATruck, OnATruck)
//	ON_BN_CLICKED(IDC_F51, OnF51)
//	ON_BN_CLICKED(IDC_F80, OnF80)
//	ON_BN_CLICKED(IDC_F84, OnF84)
//	ON_BN_CLICKED(IDC_F86E, OnF86e)
//	ON_BN_CLICKED(IDC_MIG15, OnMig15)
//	ON_BN_CLICKED(IDC_ReplayPlayback, OnReplayPlayback)
//	ON_BN_CLICKED(IDC_ReplayRecord, OnReplayRecord)
//	ON_BN_CLICKED(IDC_Comms, OnComms)
	ON_WM_PAINT()
	ON_MESSAGE( WM_GETSTRING, OnGetString)

	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//void Rtestsh1::OnMig15() 
//{
//	m_actype=PT_MIG15;
//	_Replay.tempplane=m_actype;
//}
//
//void Rtestsh1::OnReplayPlayback() 
//{
//	_Replay.Playback=TRUE;
//	_Replay.Record=FALSE;
//}
//
//void Rtestsh1::OnReplayRecord() 
//{
//	_Replay.Record=TRUE;
//	_Replay.Playback=FALSE;
//}
//
//void Rtestsh1::OnComms() 
//{
//	_DPlay.StartCommsSession();
//	
//}
