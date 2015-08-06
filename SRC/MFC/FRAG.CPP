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

// Frag.cpp : implementation file
//

#include "stdafx.h"
#include "mig.h"
#include	"globrefs.h"
#include "winmove.h"
#include "comms.h"
#include "FullPane.h"
#include	"migview.h"


#include "Frag.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#ifndef THIS_FILE_DEFINED
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif
CFragPilot *  CFrag::pilotlines[MaxFragLines+1];
/////////////////////////////////////////////////////////////////////////////
// CFrag dialog
int		CFrag::disppack=0,CFrag::dispgrp=0,CFrag::dispsquad=0, CFrag::comboindex = 0;
bool	CFrag::packmode=true;
CFrag::ComboParams	CFrag::comboparams[MAXCOMBOENTRIES];


//CFrag::CFrag(CWnd* pParent /*=NULL*/)
//	: RowanDialog(CFrag::IDD, pParent)
//{
//	//{{AFX_DATA_INIT(CFrag)
//		// NOTE: the ClassWizard will add member initialization here
//	//}}AFX_DATA_INIT
//	CFragCon();
//}
CFrag::CFrag(int id,CWnd* pParent /*=NULL*/)
	: RowanDialog(id, pParent)
{
	CFragCon();
}

void	CFrag::CFragCon()
{
	for (int i=0;i<=MaxFragLines;i++)
		pilotlines[i]=NULL;
}


void CFrag::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFrag)
	DDX_Control(pDX, IDCX_PLAYERCHAT, m_IDCX_PLAYERCHAT);
	DDX_Control(pDX,IDC_RSTATICCTRL24,m_IDC_RSTATICCTRL24);
	DDX_Control(pDX,IDC_RSTATICCTRL35,m_IDC_RSTATICCTRL35);
	DDX_Control(pDX,IDC_RSTATICCTRL37,m_IDC_RSTATICCTRL37);
	DDX_Control(pDX,IDC_RRADIO_DETAILS,m_IDC_RRADIO_DETAILS);
	DDX_Control(pDX,IDC_ATTACKMETHOD2,m_IDC_ATTACKMETHOD2);
	DDX_Control(pDX,IDC_GRPDESC,m_IDC_GRPDESC);
	DDX_Control(pDX,IDC_PILOTEDFLAG,m_IDC_PILOTEDFLAG);
	DDX_Control(pDX,IDC_UNASSIGN,m_IDC_UNASSIGN);
	DDX_Control(pDX,IDC_UNASSIGNFLAG,m_IDC_UNASSIGNFLAG);
	DDX_Control(pDX,IDC_RLIST_INCOMING_CHAT,m_IDC_RLIST_INCOMING_CHAT);
	DDX_Control(pDX,IDC_PLAYERCHAT,m_IDC_PLAYERCHAT);
	//}}AFX_DATA_MAP
}
void CFrag::FillComboParams(int& comboentry, int type, int pack, int wave, int group)
{
	CFrag::comboparams[comboentry].type = (CFrag::FillType) type;
	CFrag::comboparams[comboentry].pack = pack;
	CFrag::comboparams[comboentry].wave = wave;
	CFrag::comboparams[comboentry++].group = group;

}
bool CFrag::PositionValid(int pilot,CFrag::OneFragDef* params, int numopts)
{
	char i=0;
	bool	acplaced = false;


	while	(		(i < numopts)
				&&	(!acplaced)
			)
	{
		int squadnum = params[i][3];
		int squadflight = params[i][4];
		char k = 0;
		while  (	(k < 4)
				&&	(!acplaced)
				)
		{
			int pos = squadflight * 4 + k;
//			if  (	(		( _DPlay.CurrPlayers > 0)
			if  (	(		( _DPlay.PlayerCreated)
						&&	(DPlay::H2H_Player[pilot].squadron == squadnum)
						&&	(DPlay::H2H_Player[pilot].position == pos)
					)
					||
					(
			 				(MMC.playersquadron == squadnum)
						&&	(MMC.playeracnum == pos)
//DeadCode AMM 14Oct98 						&&	(_DPlay.CurrPlayers == 0)
						&&	(!RFullPanelDial::incomms)			//AMM 14Oct98
					)
				)
				 acplaced = true;

			  k++;
		}
		i++;
	}
	return (acplaced);
}

int CFrag::MakeFlights(int numopts, int p, int w, int g, OneFragDef* params)
{
	int	squadnum, squadflight;
	Todays_Packages.GetSquadEntry(p, w, g, squadnum, squadflight);
	int numflights = Todays_Packages.pack[p].wave[w].group[g].numflights;
	for (int i = 0; i < numflights; i++)
	{
		params[numopts][0] = p;
		params[numopts][1] = w;
		params[numopts][2] = g;
		params[numopts][3] = squadnum;
		params[numopts][4] = i+ squadflight;

		numopts++;
	}
	return (numopts);
}
bool CFrag::SquadFlying(int squad)
{
	int pack, wave, group;
	int flight = 0;
	 if(Todays_Packages.GetPackage(pack, wave, group, squad, flight))
		 return (true);
	 else
		 return (false);
}
int CFrag::FillFlightParamswithSquads(int squad, OneFragDef* params)
{
	int pack, wave, group;
	int numopts = 0;

	for (int j=0;j<4;j++)
	{
		 if(Todays_Packages.GetPackage(pack, wave, group, squad, j))
		 {
	 		params[numopts][0] = pack;
			params[numopts][1] = wave;
			params[numopts][2] = group;
			params[numopts][3] = squad;
			params[numopts][4] = j;
			numopts++;

		 }

	}
	return(numopts);
}
int CFrag::FillFlightParams(int i, OneFragDef* params)
{
	int numopts = 0;
	if (CFrag::comboparams[0].type == CFrag::ALLFLIGHTS)
	{
		for (int pack=0;pack<Profile::MAX_PACKS;pack++)
		{
			for (int wave=0;wave<Profile::MAX_WAVES;wave++)
			{
				for (int group=0;group<Profile::MAX_GROUPS;group++)
				{
					UniqueID u=Todays_Packages.pack[pack].wave[wave].group[group].uid;
					if (u)
					{
						numopts = MakeFlights(numopts, pack, wave, group, params);
					}
				}
			}
		}
	}else
	{
		switch	 (CFrag::comboparams[i].type)
		{
			case  CFrag::PACKAGE:
				{
					for (int wave=0;wave<Profile::MAX_WAVES;wave++)
					{
						for (int group=0;group<Profile::MAX_GROUPS;group++)
						{
							UniqueID u=Todays_Packages.pack[CFrag::comboparams[i].pack].wave[wave].group[group].uid;
							if (u)
								numopts = MakeFlights(numopts, CFrag::comboparams[i].pack, wave, group, params);
						}
					}
				   break;
				}
			case  CFrag::WAVE:
				{
					for (int group=0;group<Profile::MAX_GROUPS;group++)
					{
						UniqueID u=Todays_Packages.pack[CFrag::comboparams[i].pack].wave[CFrag::comboparams[i].wave].group[group].uid;
						if (u)
								numopts = MakeFlights(numopts, CFrag::comboparams[i].pack, CFrag::comboparams[i].wave, group, params);
					}
				   break;
				}
			case  CFrag::GROUP:
				{
					UniqueID u=Todays_Packages.pack[CFrag::comboparams[i].pack].wave[CFrag::comboparams[i].wave].group[CFrag::comboparams[i].group].uid;
					if (u)
						numopts = MakeFlights(numopts, CFrag::comboparams[i].pack, CFrag::comboparams[i].wave, CFrag::comboparams[i].group, params);
				   break;
				}

		}
	}

	return	(numopts);
}
char CFrag::FindUniqueCallName(char callname)
{
	bool uniquefound = false;
	int err = 0;
	while (	(!uniquefound)	&&	(err <2))
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
						 )
						unique = false;
					group++;
				}
				wave++;
			}
			i++;
		}
		if (!unique)
		{
			callname++;
			if (callname > Profile::MAX_CALLNAMES)
				callname = 0;
		}else
			uniquefound = true;

		err++;
	}
	return(callname);
}

void CFrag::FragInit()
{
   	int totalflights=0;
	int comboentry = 0;

	struct	FGroups
	{
		int		flights;
	};
	struct	FWaves
	{
		int		flights;
		FGroups	groups[Profile::MAX_GROUPS];	
		
	};

	struct	FPackages
	{
		int		flights;
		FWaves	waves[Profile::MAX_WAVES];	

	};

	FPackages	fpack[Profile::MAX_PACKS];
 	for (int i=0;i<Profile::MAX_PACKS;i++)
		for (int wave=0;wave<Profile::MAX_WAVES;wave++)
			for (int group=0;group<Profile::MAX_GROUPS;group++)
			{
				fpack[i].flights = 0;
				fpack[i].waves[wave].flights = 0;
				fpack[i].waves[wave].groups[group].flights = 0;
			}

	byte callname = 0;
 	for (i=0;i<Profile::MAX_PACKS;i++)
		for (int wave=0;wave<Profile::MAX_WAVES;wave++)
			for (int group=0;group<Profile::MAX_GROUPS;group++)
			{
				UniqueID u=Todays_Packages.pack[i].wave[wave].group[group].uid;
				if  (		(u)
						&&	(Todays_Packages.pack[i][wave][group].callname == -1)
					)
					Todays_Packages.pack[i][wave][group].callname = FindUniqueCallName(callname++);
			}	

 	for (i=0;i<Profile::MAX_PACKS;i++)
		if (Todays_Packages.pack[i][0][0].uid)
		{
			for (int wave=0;wave<Profile::MAX_WAVES;wave++)
				for (int group=0;group<Profile::MAX_GROUPS;group++)
				{
					UniqueID u=Todays_Packages.pack[i].wave[wave].group[group].uid;
					if (u)
					{
						int squadnum = Todays_Packages.pack[i].wave[wave].group[group].squadron;
						int numflights = Todays_Packages.pack[i].wave[wave].group[group].numflights;

						totalflights += numflights;
						fpack[i].flights += numflights;
						fpack[i].waves[wave].flights += numflights;
						fpack[i].waves[wave].groups[group].flights += numflights;

					}
				}
		}

 	for (i=0;i<CFrag::MAXCOMBOENTRIES;i++)
		CFrag::comboparams[i].type = CFrag::NOTUSED;

	int maxflightsallowed = 6;
//	if (_DPlay.CurrPlayers > 0)
	if (_DPlay.PlayerCreated)
		maxflightsallowed = 4;				//comms		

	if (CFrag::packmode)
	{
		if (totalflights <= maxflightsallowed)
			CFrag::comboparams[0].type = CFrag::ALLFLIGHTS;
		else
		{
			 	for (int i=0;i<Profile::MAX_PACKS;i++)
				{
					if 	(fpack[i].flights != 0)
					{
						if (fpack[i].flights <= maxflightsallowed)
						{

							FillComboParams(comboentry, CFrag::PACKAGE, i, -1, -1);
			
						}else
						{
							for (int wave=0;wave<Profile::MAX_WAVES;wave++)
							{
								if 	(fpack[i].waves[wave].flights != 0)
								{
									if (fpack[i].waves[wave].flights <= maxflightsallowed)
									{
										FillComboParams(comboentry, CFrag::WAVE, i, wave, -1);
									}else
									{
										for (int group=0;group<Profile::MAX_GROUPS;group++)
										{
											if 	(fpack[i].waves[wave].groups[group].flights != 0)
												FillComboParams(comboentry, CFrag::GROUP, i, wave, group);

										}
		   							}
								}
							}
						}
					}
				}
		}

	}else
	{
			//set up squad that are flying
		int j = 0;
		//to include yak
	 	for (int i=0;i<=SQ_R_NONFLYABLE;i++)
		{
			if (SquadFlying(i))
			{
				comboparams[j++].pack = i;
			}
		}
	}
	
}

//////////////////////////////////////////////////////////////////////////////////////


BEGIN_MESSAGE_MAP(CFrag, CDialog)
	//{{AFX_MSG_MAP(CFrag)
	ON_WM_TIMER()
	ON_WM_DESTROY()
	ON_EN_UPDATE(IDCX_PLAYERCHAT, OnUpdatePlayerchat)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFrag message handlers

BOOL CFrag::OnInitDialog() 
{
//	m_IDC_ATTACKMETHOD2.SetCircularStyle(TRUE);
	if (m_IDCX_PLAYERCHAT.m_hWnd)
		m_IDCX_PLAYERCHAT.SetLimitText(60);

	if (_DPlay.PlayerCreated)
	{
		DPlay::H2H_Player[_DPlay.mySlot].status=CPS_FRAG;
	}
	CDialog::OnInitDialog();
	CRListBox* rlistbox;

	CRRadio* pradio;

	pradio=GETDLGITEM(IDC_RRADIO_DETAILS);

	
	

//DeadCode AMM 14Oct98 	if  (		(_DPlay.CurrPlayers != 0)
	if  (		(RFullPanelDial::incomms)						//AMM 14Oct98
		&&	(_DPlay.GameType == COMMSCAMPAIGN)
		&&	(_DPlay.Side == FALSE)
		)
	{
		pradio->ShowWindow(SW_HIDE);
		CFrag::packmode = false;
	}else
	{
		pradio->ShowWindow(SW_SHOW);
		CString string;
		string.LoadString(IDS_SQUADRONS);
		pradio->AddButton(string);
		string.LoadString(IDS_MISSION);
		pradio->AddButton(string);
		pradio->SetCurrentSelection(packmode);

	}






  	CRCombo* combo;
	combo=GETDLGITEM(IDC_ATTACKMETHOD2);
	combo->SetCircularStyle(TRUE);

	CRStatic*   rtp ;
	rtp=GETDLGITEM(IDC_GRPDESC);
	CRButton* b;
	b=GETDLGITEM(IDC_PILOTEDFLAG);

	

	char buffer[10];
	CString	name;
	char	wavenum[20];

	int j = 0;



	if (!CFrag::packmode)
	{
		combo->ShowWindow(SW_SHOW);
	 	for (int i=0;i<=SQ_R_NONFLYABLE;i++)
		{
			if (SquadFlying(i))
			{
				combo->AddString(LoadResString(IDS_L_SQ_BF_F86A  + i));
				comboparams[j++].pack = i;
			}
		}
		if (comboindex >= j)
			comboindex = 0;
		combo->SetIndex(comboindex);
	}
	else
	{
		if (comboparams[0].type == ALLFLIGHTS)
		{
			combo->ShowWindow(SW_HIDE);
		}
		else
		{
			combo->ShowWindow(SW_SHOW);
			for (int i=0;i< CFrag::MAXCOMBOENTRIES;i++)
			{
//DeadCode AMM 14Oct98 				if (_DPlay.CurrPlayers == 0)
				if (!RFullPanelDial::incomms || _DPlay.GameType==COMMSCAMPAIGN)					//AMM 14Oct98
				{
//DEADCODE DAW 06/06/99 					name=CSprintf("%s: %s",
//DEADCODE DAW 06/06/99 						Todays_Packages.pack[comboparams[i].pack].packname,
//DEADCODE DAW 06/06/99 						GetTargName(Todays_Packages[comboparams[i].pack].packagetarget));
					name=CSprintf("%i: %s",
						comboparams[i].pack+1,
						GetTargName(Todays_Packages[comboparams[i].pack].packagetarget));
						//Todays_Packages.pack[comboparams[i].pack].packname);
				}else
				{
//DEADCODE JIM 19/01/99 					switch (_DPlay.GameType)
//DEADCODE JIM 19/01/99 					{
//DEADCODE JIM 19/01/99 						case TEAMPLAY:
//DEADCODE JIM 19/01/99 						case DEATHMATCH:
//DEADCODE JIM 19/01/99 						case COMMSQUICKMISSION:
						{

							if (comboparams[i].pack == 0)
								name=RESSTRING(UN);
							else
								name=RESSTRING(RED);

// hey, if you comment out switches, remove the breaks as well!
//DeadCode AMM 11Feb99 							break;
						
						}
//DEADCODE JIM 19/01/99 						case COMMSCAMPAIGN:
//DEADCODE JIM 19/01/99 						{
//DEADCODE JIM 19/01/99 							name=Todays_Packages.pack[comboparams[i].pack].packname;
//DEADCODE JIM 19/01/99 							break;
//DEADCODE JIM 19/01/99 						}
//DEADCODE JIM 19/01/99 
//DEADCODE JIM 19/01/99 					}
				}
				_itoa((CFrag::comboparams[i].wave + 1),wavenum,10);
				switch	 (CFrag::comboparams[i].type)
				{
					case  CFrag::PACKAGE:
					{

						combo->AddString(name);
						j++;
						break;
					}
					case  CFrag::WAVE:
					{
						combo->AddString(name + ", " + RESSTRING(WAVE) + wavenum); //JIM 19/01/99
						j++;
						break;
					}
					case  CFrag::GROUP:
					{
//						_itoa(CFrag::comboparams[i].group,buffer,10);
					combo->AddString(name + ", " + RESSTRING(WAVE) + wavenum  + ", " +  RESSTRING(ATTACK + CFrag::comboparams[i].group)); //JIM 19/01/99
					j++;
					break;
					}
				}
			}
			if (comboindex >= j)									  //RDH 17/06/99
				comboindex = 0;										  //RDH 17/06/99
																	  //RDH 17/06/99
			combo->SetIndex(comboindex);
		}
	}


	
	int pack, wave, group;
	int plflight = MMC.playeracnum/4;
	Todays_Packages.GetPackage(pack, wave, group, 
		MMC.playersquadron, plflight);

	bool	playeronview = false;
	if (CFrag::packmode)
	{
		switch	 (CFrag::comboparams[comboindex].type)
		{
			case  CFrag::PACKAGE:
			{
				if (pack == CFrag::comboparams[comboindex].pack)
					playeronview = true;
					break;
			}
			case  CFrag::WAVE:
			{
				if (		(pack == CFrag::comboparams[comboindex].pack)
						&&	(wave == CFrag::comboparams[comboindex].wave)
					)
					playeronview = true;
				   break;
			}
			case  CFrag::GROUP:
			{		
				if  (		(pack == CFrag::comboparams[comboindex].pack)
						&&	(wave == CFrag::comboparams[comboindex].wave)
						&&	(group == CFrag::comboparams[comboindex].group)
					)
					playeronview = true;
				   break;
			}
		}
	}else
	{
		if (MMC.playersquadron == CFrag::comboparams[comboindex].pack)
					playeronview = true;
	}

	if  (		(playeronview)
			||	(MMC.playersquadron == -1)
		)
	{
		rtp->ShowWindow(SW_HIDE);
		b->ShowWindow(SW_HIDE);
	}
	else
	{
		rtp->ShowWindow(SW_SHOW);
		b->ShowWindow(SW_SHOW);
	}

	rtp=GETDLGITEM(IDC_UNASSIGN);
	b=GETDLGITEM(IDC_UNASSIGNFLAG);

//DeadCode AMM 14Oct98 	if (_DPlay.CurrPlayers == 0)
	if (!RFullPanelDial::incomms)								//AMM 14Oct98
	{
		rtp->ShowWindow(SW_HIDE);
		b->ShowWindow(SW_HIDE);
	}
	else
	{
		strcpy(MMC.PlayerName,_DPlay.PlayerName);
		rtp->ShowWindow(SW_SHOW);
		b->ShowWindow(SW_SHOW);
	}

	if (RFullPanelDial::incomms)
	{
		rlistbox=GETDLGITEM(IDC_RLIST_INCOMING_CHAT);
		if (rlistbox)		
		{
			rlistbox->Clear();
			rlistbox->AddColumn(120);
			rlistbox->AddColumn(300);
		}
	}
//DeadCode AMM 17Nov98 	DPlay::H2H_Player[_DPlay.mySlot].status=CPS_FRAG;

	frag_timer=SetTimer(TIMER_FRAG,0,NULL);
	fragfirsttime=true;

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BEGIN_EVENTSINK_MAP(CFrag, CDialog)
    //{{AFX_EVENTSINK_MAP(CFrag)
	ON_EVENT(CFrag, IDC_PLAYERCHAT, 1 /* ReturnPressed */, OnReturnPressedPlayerchat, VTS_BSTR)
	ON_EVENT(CFrag, IDC_RRADIO_DETAILS, 1 /* Selected */, OnSelectedRradioDetails, VTS_I4)
	ON_EVENT(CFrag, IDC_ATTACKMETHOD2, 1 /* TextChanged */, OnTextChangedAttackmethod2, VTS_BSTR)
	ON_EVENT(CFrag, IDC_PILOTEDFLAG, 1 /* Clicked */, OnClickedPilotedflag, VTS_NONE)
	ON_EVENT(CFrag, IDC_UNASSIGNFLAG, 1 /* Clicked */, OnClickedUnassignflag, VTS_NONE)
	ON_EVENT(CFrag, IDC_PLAYERCHAT, 2 /* TextChanged */, OnTextChangedPlayerchat, VTS_I4)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CFrag::OnSelectedRradioDetails(long ButtonNum) 
{
	if (packmode)
		packmode = false;
	else
		packmode = true;
	comboindex = 0;


	RedrawScreen();

	
}

void CFrag::OnTextChangedAttackmethod2(LPCTSTR text) 
{
  	CRCombo* combo;
	combo=GETDLGITEM(IDC_ATTACKMETHOD2);
	comboindex = combo->GetIndex();	
	RedrawScreen();

}
void CFrag::RedrawScreen()
{
//	RFullPanelDial* fullscreen=(RFullPanelDial*)GetParent();
	DestroyPanel();
	//##need to choose commsfrag if in comms
//	fullscreen->SelectReadyRoom
//DeadCode AMM 14Oct98 	if (_DPlay.CurrPlayers == 0)
	if (!RFullPanelDial::incomms)								//AMM 14Oct98
		FullPanel()->LaunchScreen(&RFullPanelDial::singlefrag);
	else
		FullPanel()->LaunchScreen(&RFullPanelDial::commsfrag);

}
void CFrag::OnClickedPilotedflag() 
{
	int pack, wave, group;
	int plflight = MMC.playeracnum/4;
	Todays_Packages.GetPackage(pack, wave, group, 
		MMC.playersquadron, plflight);

	char i=0, index = -1;

	if (CFrag::packmode)
	{
		while   (	(i<CFrag::MAXCOMBOENTRIES)
				&&	(index == -1)
				)
		{
			switch	 (CFrag::comboparams[i].type)
			{
				case  CFrag::PACKAGE:
				{
					if (pack == CFrag::comboparams[i].pack)
						index = i;
					break;
				}
				case  CFrag::WAVE:
				{
					if (		(pack == CFrag::comboparams[i].pack)
							&&	(wave == CFrag::comboparams[i].wave)
						)
						index = i;
					   break;
				}
				case  CFrag::GROUP:
				{
					if  (		(pack == CFrag::comboparams[i].pack)
							&&	(wave == CFrag::comboparams[i].wave)
							&&	(group == CFrag::comboparams[i].group)
						)
						index = i;
					   break;
				}
			}
			i++;
		}
	}else
	{
		while   (	(i<CFrag::MAXCOMBOENTRIES)
				&&	(index == -1)
				)
		{
			if	(MMC.playersquadron == CFrag::comboparams[i].pack)
				index = i;
			i++;
		}
	}

		
	if (index != -1)
	{
		comboindex = index;
		RedrawScreen();
	}

}

void CFrag::OnClickedUnassignflag() 
{
	int i = 0;
//DeadCode AMM 17Nov98 	while	(		(i < _DPlay.CurrPlayers)
	while	(		(i < MAXPLAYERS)					//AMM 04Nov98
			)
	{
		if  (		(DPlay::H2H_Player[i].squadron == MMC.playersquadron)
				&&	(DPlay::H2H_Player[i].position == MMC.playeracnum)
			)
			{
				DPlay::H2H_Player[i].squadron = -1;

// send update to other players 

			SLOTPOSPACK s;

			s.PacketID=PID_SLOTINFOUPDATE;
			s.squadron=DPlay::H2H_Player[i].squadron;
			s.position=DPlay::H2H_Player[i].position;
			s.PlayerID=_DPlay.myDPlayID;

			_DPlay.SendMessageToAll((char*)&s,sizeof(SLOTPOSPACK));
		}
		i++;
	}

	MMC.playersquadron = -1;
	RedrawScreen();

}
void CFrag::OnReturnPressedPlayerchat(LPCTSTR text)
{
	if (text[0])
	{

		CRListBox* rlistbox;
		CREdit* poo;

		rlistbox=GETDLGITEM(IDC_RLIST_INCOMING_CHAT);

	//DeadCode AMM 05Aug98 	rlistbox->AddString(&_DPlay.PlayerName[0],0);
		rlistbox->AddString((DPlay::H2H_Player+_DPlay.mySlot)->name,0);
		rlistbox->AddString(text,1);
		rlistbox->SetHilightRow(-1) ;							//AMM 10Jul99
	//	_DPlay.UISendDialogue((DPlay::H2H_Player+_DPlay.mySlot),(char*)text);
		_DPlay.UISendDialogue((char*)text);

		_DPlay.AddChatMessageToBuffer((DPlay::H2H_Player+_DPlay.mySlot)->name,(char*)text);

		poo=GETDLGITEM(IDC_PLAYERCHAT);
		poo->SetCaption("");										  //AMM 06/07/99


//DeadCode AMM 07Jul99 		poo->SetWindowText("");
	}
}
void CFrag::OnReturnPressed()
{
	CString text;
	GETDLGITEM(IDCX_PLAYERCHAT)->GetWindowText(text);
	if (!text.IsEmpty())
	{
		CRListBox* rlistbox;
		CREdit* poo;

		rlistbox=GETDLGITEM(IDC_RLIST_INCOMING_CHAT);

	//DeadCode AMM 05Aug98 	rlistbox->AddString(&_DPlay.PlayerName[0],0);
		rlistbox->AddString((DPlay::H2H_Player+_DPlay.mySlot)->name,0);
		rlistbox->AddString(text,1);
		rlistbox->SetHilightRow(-1) ;							//AMM 10Jul99
	//	_DPlay.UISendDialogue((DPlay::H2H_Player+_DPlay.mySlot),(char*)text);
		_DPlay.UISendDialogue((const char*)text);

		_DPlay.AddChatMessageToBuffer((DPlay::H2H_Player+_DPlay.mySlot)->name,(const char*)text);

		GETDLGITEM(IDCX_PLAYERCHAT)->SetWindowText("");
	}


}

void	DPlay::DisplayFragDialogue(char* name, char* text)
{
	CRListBox* rlistbox;
 	rlistbox=(CRListBox*)RDialog::m_pView->m_pfullpane->pdial[0]->GetDlgItem(IDC_RLIST_INCOMING_CHAT);
	if (rlistbox)
	{
 		rlistbox->AddString(name,0);
 		rlistbox->AddString(text,1);
		rlistbox->SetHilightRow(-1) ;								//AMM 10Jul99
	}
	//delete	rlistbox;
}



void CFrag::OnTimer(UINT nIDEvent) 
{
	if (nIDEvent==frag_timer)
	{
		if (_DPlay.PlayerCreated)
		{
			if (fragfirsttime)
			{
				_DPlay.UpdateChatBox();
				fragfirsttime=false;
			}

			_DPlay.UIUpdateMainSheet();

			if (_DPlay.FlyNowFlag)
			{
				if (_DPlay.UINetworkSelectFly())
				{
					KillTimer(frag_timer);

// need to launch quickmissionflight sheet

//					RFullPanelDial* fullscreen=(RFullPanelDial*)GetParent();
  //					FullScreen* fs;
					FullPanel()->OnSelectRlistbox(1,1);
					return;
				}
				else
				{
					_DPlay.FlyNowFlag=FALSE;
					DPlay::H2H_Player[_DPlay.mySlot].status=CPS_FRAG;
					_DPlay.SendInFragMessage();
				}
			}
			else if (_DPlay.UpdateFrag)
			{
				_DPlay.UpdateFrag=FALSE;

				int i = 0;
				while (CFrag::pilotlines[i] != NULL)
				{
					CFrag::pilotlines[i]->CFragPilot::PrintPilotNames();
					i++;
				}
			}
			else if (_DPlay.FragChanged)
			{
// if the frag has changed then leave because reinitisalisation is required 

				_DPlay.FragChanged=false;

//				RFullPanelDial* fullscreen=(RFullPanelDial*)GetParent();
				FullPanel()->OnSelectRlistbox(0,0);				//JIM 12Jan99
				return;
			}
		}
	}
	CDialog::OnTimer(nIDEvent);
}

void CFrag::OnDestroy() 
{
	KillTimer(frag_timer);

	CDialog::OnDestroy();
}

void CFrag::OnTextChangedPlayerchat(LPSTR text) 
{
	// TODO: Add your control notification handler code here
		trunc(text,40);

}

void CFrag::OnUpdatePlayerchat() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function to send the EM_SETEVENTMASK message to the control
	// with the ENM_UPDATE flag ORed into the lParam mask.
	
	// TODO: Add your control notification handler code here
	
}
