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

// nose_art.cpp : implementation file
//

#include "stdafx.h"
#include "mig.h"
#include "nose_art.h"
#include "paint.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#ifndef THIS_FILE_DEFINED
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif

/////////////////////////////////////////////////////////////////////////////
// CPilotsAircraftDetails dialog


CPilotAircraftDetails::CPilotAircraftDetails(int squadnum, int pilot,CWnd* pParent /*=NULL*/)
	: RowanDialog(CPilotAircraftDetails::IDD, pParent)
{
			SetProjSpecific(-1,-1,squadnum, pilot);

	//{{AFX_DATA_INIT(CPilotsAircraftDetails)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CPilotAircraftDetails::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPilotsAircraftDetails)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	DDX_Control(pDX,IDC_NAME_PILOT1,m_IDC_NAME_PILOT1);
	DDX_Control(pDX,IDC_NAME_PILOT2,m_IDC_NAME_PILOT2);
	DDX_Control(pDX,IDC_NAME_PILOT3,m_IDC_NAME_PILOT3);
	DDX_Control(pDX,IDC_NAME_PILOT4,m_IDC_NAME_PILOT4);
	DDX_Control(pDX,IDC_NOSEART_1,m_IDC_NOSEART_1);
	DDX_Control(pDX,IDC_NOSEART_2,m_IDC_NOSEART_2);
	DDX_Control(pDX,IDC_NOSEART_3,m_IDC_NOSEART_3);
	DDX_Control(pDX,IDC_NOSEART_4,m_IDC_NOSEART_4);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPilotAircraftDetails, CDialog)
	//{{AFX_MSG_MAP(CPilotAircraftDetails)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPilotsAircraftDetails message handlers

BEGIN_EVENTSINK_MAP(CPilotAircraftDetails, CDialog)
    //{{AFX_EVENTSINK_MAP(CPilotAircraftDetails)
	ON_EVENT(CPilotAircraftDetails, IDC_NOSEART_1, 1 /* Clicked */, OnClickedNoseart1, VTS_NONE)
	ON_EVENT(CPilotAircraftDetails, IDC_NOSEART_2, 1 /* Clicked */, OnClickedNoseart2, VTS_NONE)
	ON_EVENT(CPilotAircraftDetails, IDC_NOSEART_3, 1 /* Clicked */, OnClickedNoseart3, VTS_NONE)
	ON_EVENT(CPilotAircraftDetails, IDC_NOSEART_4, 1 /* Clicked */, OnClickedNoseart4, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()
void CPilotAircraftDetails::PickNoseArt(int ac)
{
	ac= ac + 4 * (acnum/4);
	if (LoggedChild(1))
	{
		CloseLoggedChildren();
	}
	RDialog* d = MakeTopDialog(
			//CRect(50,50,0,0),
//			Place(POSN_CENTRE,POSN_MAX),
			Place(POSN_CALLER,POSN_CALLER,350,0),

								DialBox(FIL_MAP_PILOTDETAILS,new CPaint(groupnum, ac))//,Edges(EDGE::ALIGN_MIN + EDGE::ACTIONS_SPLITTER,EDGE::ALIGN_MIN,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE))
							);	
	LogChild(1,d);
}

void CPilotAircraftDetails::OnClickedNoseart1() 
{
	PickNoseArt(0);
}

BOOL CPilotAircraftDetails::OnInitDialog() 
{
 	CDialog::OnInitDialog();
	RefreshData();	

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPilotAircraftDetails::OnClickedNoseart2() 
{
	PickNoseArt(1);
}

void CPilotAircraftDetails::OnClickedNoseart3() 
{
	PickNoseArt(2);
}

void CPilotAircraftDetails::OnClickedNoseart4() 
{
	PickNoseArt(3);
}
 bool CPilotAircraftDetails::CommsPlayer(int pos, int& i)
{//repeated in sqdnlist and personal for speed
	if (!RFullPanelDial::incomms)									  //JIM 19/05/99
		return false;												  //JIM 19/05/99
	i = 0;
//	while	(		(i < _DPlay.CurrPlayers)
	while	(		(i < MAXPLAYERS)
			)
	{
		if  (		(DPlay::H2H_Player[i].squadron == groupnum)
			&&		(DPlay::H2H_Player[i].position == pos)

			)
			return (true);
		i++;
	}
	return (false);
}
void CPilotAircraftDetails::RefreshData()
{
	CRStatic*   s;
	int baseac = 4 * (acnum/4);
	int decals;
	int player;
	for(int i=0;i<4;i++)
	{ 
		s=GETDLGITEM(IDC_NAME_PILOT1+i);
		if (		(MMC.playersquadron == groupnum)
				&&	(MMC.playeracnum == (baseac + i - groupnum*24))
			)
			{
				s->SetForeColor(RGB(255,255,255));
				s->SetString(MMC.PlayerName);
			}else if (CommsPlayer((baseac + i - groupnum*24), player))
			{
				s->SetForeColor(RGB(0,255,0));
				s->SetString(DPlay::H2H_Player[player].name);
			}else
			{
				s->SetString(MakePilotName(MMC.Active_Pilots[24*groupnum+i+baseac].name));
			}
		CRButton* rbutton;
		rbutton=GETDLGITEM(IDC_NOSEART_1+i);
		decals = MMC.Active_Pilots[24*groupnum+i+baseac].decal;
		if (decals < 16)
			decals = decals + FIL_NOSE_STD_1;
		else
			decals = decals - 16 + FIL_NOSE_USER_1;
		rbutton->SetNormalFileNum(decals);
		rbutton->SetPressedFileNum(1);
	}
}

void CPilotAircraftDetails::ChildDialClosed(int dialnum,RDialog* child,int rv)
{
	if (rv==IDOK)
	{
		RefreshData();
	}
}
void  CPilotAircraftDetails::ParentDialClosed(RDialog*,int rv)
{
	OnOK();
}
