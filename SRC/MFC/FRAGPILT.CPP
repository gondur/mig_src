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

// FragPilt.cpp : implementation file
//

#include "stdafx.h"
#include "mig.h"
#include "FragPilt.h"
#include	"node.h"
#include	"globrefs.h"
#include "winmove.h"
#include "comms.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#ifndef THIS_FILE_DEFINED
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif

/////////////////////////////////////////////////////////////////////////////
// CFragPilot dialog


CFragPilot::CFragPilot(int*pack,CWnd* pParent /*=NULL*/)
	: RowanDialog(CFragPilot::IDD, pParent)
{
	SetProjSpecific(pack[0],pack[1],pack[2]);
	squadnum = pack[3];
	squadflight = pack[4];

	if (!CFrag::packmode)
		Todays_Packages.GetPackage(packnum, wavenum, groupnum, squadnum, squadflight);

//	beenselected=false;
	//{{AFX_DATA_INIT(CFragPilot)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
//	if (packnum+wavenum+groupnum+acnum==0)
//		beenselected=true;
}


void CFragPilot::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFragPilot)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	DDX_Control(pDX,IDC_FRAG_ROLE,m_IDC_FRAG_ROLE);
	DDX_Control(pDX,IDC_FRAG_ID,m_IDC_FRAG_ID);
	DDX_Control(pDX,IDC_FRAG_WAVE,m_IDC_FRAG_WAVE);
	DDX_Control(pDX,IDC_FRAG_CALLNAME,m_IDC_FRAG_CALLNAME);
	DDX_Control(pDX,IDC_PLAYERCHAT,m_IDC_PLAYERCHAT);
	DDX_Control(pDX,IDC_PLAYERCHAT2,m_IDC_PLAYERCHAT2);
	DDX_Control(pDX,IDC_PLAYERCHAT3,m_IDC_PLAYERCHAT3);
	DDX_Control(pDX,IDC_PLAYERCHAT4,m_IDC_PLAYERCHAT4);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFragPilot, CDialog)
	//{{AFX_MSG_MAP(CFragPilot)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFragPilot message handlers
void CFragPilot::EndDialog( int nResult )	 //should really be OnOk
{
//	if (beenselected)
//	{
//		//this is the code for setting the flyable aircraft
//		GR_Pack_PlayerSquad=Todays_Packages[packnum][wavenum][groupnum].squadron;
//		GR_Pack_PlayerPos=acnum;
//	}
}
void CFragPilot::FindCallName(char index)
{
	char cnt = -1;
	for (char i = 0; i < Profile::MAX_CALLNAMES; i++)
	{
		if (UniqueCallNameOrThisGroups(i))
			cnt++;
		if	(cnt == index)
		{
			Todays_Packages.pack[packnum][wavenum][groupnum].callname = i;
			break;
		}
			
	}
								  
}
BOOL CFragPilot::UniqueCallNameOrThisGroups(char callname)
{
		int i=0;
		bool unique = true;
		while (		(i<Profile::MAX_PACKS)	&& (unique))
		{
			int wave=0;
			while (		(wave<Profile::MAX_WAVES)	&& (unique))
			{
				int group=0;
				while (		(group<Profile::MAX_GROUPS)	&& (unique))
				{
					UniqueID u=Todays_Packages.pack[i].wave[wave].group[group].uid;
					if	(		(u)
							&&	(callname == Todays_Packages.pack[i][wave][group].callname)
							&&	(callname != Todays_Packages.pack[packnum][wavenum][groupnum].callname)
						 )
						unique = false;
					group++;
				}
				wave++;
			}
			i++;
		}
	return(unique);

}
void CFragPilot::FillComboBox()
{
   	CRCombo* combo;
	combo=GETDLGITEM(IDC_FRAG_CALLNAME);

	combo->Clear();
	int cnt = -1, index = 0;
	for (char i = 0; i < Profile::MAX_CALLNAMES; i++)
	{
		if (UniqueCallNameOrThisGroups(i))
		{
			combo->AddString(LoadResString(IDS_PHRASE_NL_CALLER0  + i));
			cnt++;
		}						   
		if	(Todays_Packages.pack[packnum][wavenum][groupnum].callname == i )
			index = cnt;
	}
	combo->SetIndex(index);
	if (RFullPanelDial::incomms)
	{
		if (_DPlay.GameType==COMMSQUICKMISSION
		|| (_DPlay.GameType==COMMSCAMPAIGN && !_DPlay.Host))
		{
			combo->SetEnabled(false);
		}
	}
}
bool CFragPilot::CommsPlayer(int pos, int& i)
{
	if (!RFullPanelDial::incomms)									  //JIM 19/05/99
		return false;												  //JIM 19/05/99
	i = 0;
//DeadCode AMM 17Nov98 	while	(		(i < _DPlay.CurrPlayers)
	while	(		(i < MAXPLAYERS)					//AMM 04Nov98
			)
	{
		if  (		(DPlay::H2H_Player[i].squadron == squadnum)
			&&		(DPlay::H2H_Player[i].position == pos)
			&&		(DPlay::H2H_Player[i].status!=CPS_NONE)

			)
			return (true);
		i++;
	}
	return (false);
}
void CFragPilot::PrintPilotNames()
{
	CREdtBt* b;

//	int	squadnum, squadflight;
//	Todays_Packages.GetSquadEntry(packnum, wavenum, groupnum, squadnum, squadflight);
	int player;

	if	(		(squadnum < SQ_B_NONFLYABLE)
			||	(		(squadnum == SQ_M15)
					||	(squadnum == SQ_M15B)
				)
		)

	{
		for(int i=0;i<4;i++)
		{  
			b=GETDLGITEM(IDC_PLAYERCHAT + i);
			b->ShowWindow(SW_SHOW);

			if (MMC.Active_Pilots[24*squadnum+squadflight*4+i ].status >= IS_DEAD)
			{
				b->SetForeColor(RGB(100,100,100));
				b->SetCaption(RESSTRING(KIA));
			}else if (		(MMC.playersquadron == squadnum)
					&&	(MMC.playeracnum == (squadflight*4 + i))
				)
			{
				b->SetForeColor(RGB(255,255,255));
				b->SetCaption(MMC.PlayerName);
			}else if (CommsPlayer(squadflight*4 + i, player))
			{
				b->SetForeColor(RGB(0,255,0));
				b->SetCaption(DPlay::H2H_Player[player].name);
			}else
			{
				b->SetForeColor(RGB(255,255,0));
				if(		(squadnum == SQ_M15) ||	(squadnum == SQ_M15B)	)
					b->SetCaption(CSprintf(RESSTRING(AIPILOT),squadflight*4+i));
				else
					b->SetCaption(RESSTRING(PILOTNAMES_START + MMC.Active_Pilots[24*squadnum+squadflight*4+i ].name.nameref));
			}
		}
	}else
	{
		for(int i=0;i<4;i++)
		{  
			b=GETDLGITEM(IDC_PLAYERCHAT + i);
			b->ShowWindow(SW_HIDE);
		}
	}

}
BOOL CFragPilot::OnInitDialog() 
{
	CDialog::OnInitDialog();
	char	cwavenum[20];
	

	m_IDC_FRAG_CALLNAME.SetCircularStyle(TRUE);

	CREdtBt* b;
	CRStatic*   s ;
	s=GETDLGITEM(IDC_FRAG_ID);
	if (!CFrag::packmode)
	{
//DeadCode AMM 14Oct98 		if  (		(_DPlay.CurrPlayers != 0)
		if ((RFullPanelDial::incomms)							//AMM 14Oct98
				&&	(_DPlay.GameType != COMMSCAMPAIGN)
			)
		{
			if (packnum == 0)
				s->SetString(RESSTRING(UN));
			else
				s->SetString(RESSTRING(RED));
		}else
			s->SetString(Todays_Packages.pack[packnum].packname);
	}
	else
		s->SetString(LoadResString(IDS_L_SQ_BF_F86A  + squadnum));

	
	_itoa((wavenum+1),cwavenum,10);
	strcat(cwavenum, " (");
	s=GETDLGITEM(IDC_FRAG_WAVE);
	s->SetString(cwavenum + 
		GetTimeName(Todays_Packages[packnum][wavenum][groupnum].takeofftime) + ")");

	s=GETDLGITEM(IDC_FRAG_ROLE);
//DeadCode AMM 14Oct98 	if  (		(_DPlay.CurrPlayers != 0)
	if  (		(RFullPanelDial::incomms)						//AMM 14Oct98
			&&	(_DPlay.GameType != COMMSCAMPAIGN)
		)
	{
		s->SetString(LoadResString(CSQuick1::quickdef.line[packnum][wavenum][groupnum].descID));
		//s->SetString(LoadResString(IDS_ATTACK + groupnum));
	}else
	{
//DEADCODE JIM 10/04/99 		s->SetString(LoadResString(IDS_ATTACK + groupnum));
		info_airgrp* g=
		*Persons2::ConvertPtrUID(Todays_Packages[packnum][wavenum][groupnum].uid);

		s->SetString(RESLIST(DUTY_BOMB,g->duty.Evaluate()/ACTIONSUBCODEMAX));

	}

	PrintPilotNames();

	FillComboBox();

	if (RFullPanelDial::incomms)
	{
		DPlay::H2H_Player[_DPlay.mySlot].status=CPS_FRAG;
		_DPlay.SendInFragMessage();
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BEGIN_EVENTSINK_MAP(CFragPilot, CDialog)
    //{{AFX_EVENTSINK_MAP(CFragPilot)
	ON_EVENT(CFragPilot, IDC_FRAG_CALLNAME, 1 /* TextChanged */, OnTextChangedFragCallname, VTS_BSTR)
	ON_EVENT(CFragPilot, IDC_PLAYERCHAT, 1 /* Clicked */, OnClickedPlayerchat, VTS_NONE)
	ON_EVENT(CFragPilot, IDC_PLAYERCHAT3, 1 /* Clicked */, OnClickedPlayerchat3, VTS_NONE)
	ON_EVENT(CFragPilot, IDC_PLAYERCHAT2, 1 /* Clicked */, OnClickedPlayerchat2, VTS_NONE)
	ON_EVENT(CFragPilot, IDC_PLAYERCHAT4, 1 /* Clicked */, OnClickedPlayerchat4, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CFragPilot::OnTextChangedFragCallname(LPCTSTR text) 
{
  	CRCombo* combo;
	combo=GETDLGITEM(IDC_FRAG_CALLNAME);
	char index = combo->GetIndex();	
	FindCallName(index);
	int i = 0;
	while (CFrag::pilotlines[i] != NULL)
	{
		CFrag::pilotlines[i]->FillComboBox();
		i++;
	}
	
}
void CFragPilot::OnClickedPlayer(int acinflight)
{

//	int	squadnum, squadflight;
//	Todays_Packages.GetSquadEntry(packnum, wavenum, groupnum, squadnum, squadflight);

	int commsplayer;
	int pos = squadflight*4 + acinflight;

	if (MMC.Active_Pilots[24*squadnum+pos].status < IS_DEAD)
	{
		if  (	(		(squadnum<SQ_B_NONFLYABLE && _DPlay.Side)
					||	(squadnum>SQ_B_NONFLYABLE && !_DPlay.Side)
				)
				||
				(!RFullPanelDial::incomms)
			)
		{
	// only allow players to choose ac on their side

			if (		(!CommsPlayer(pos, commsplayer))
					&&	(_DPlay.SlotFree(pos,squadnum))
				)			
			{
				MMC.playersquadron = squadnum;
				MMC.playeracnum = pos;
				DPlay::H2H_Player[_DPlay.mySlot].squadron = squadnum;
				DPlay::H2H_Player[_DPlay.mySlot].position = pos;
			}
		}
	//	else
		//##clicked on comms player so direct chat to H2H_Player[commsplayer]

		int i = 0;
		while (CFrag::pilotlines[i] != NULL)
		{
			CFrag::pilotlines[i]->PrintPilotNames();
			i++;
		}
	}

}

void CFragPilot::OnClickedPlayerchat() 
{
	OnClickedPlayer(0);	
}

void CFragPilot::OnClickedPlayerchat3() 
{
	OnClickedPlayer(2);	
}

void CFragPilot::OnClickedPlayerchat2() 
{
	OnClickedPlayer(1);	
}

void CFragPilot::OnClickedPlayerchat4() 
{
	OnClickedPlayer(3);	
}
