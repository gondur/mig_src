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

// Ready.cpp : implementation file
//

#include "stdafx.h"
#include "mig.h"
#include "migview.h"
#include "Ready.h"
#include "winmove.h"
#include "comms.h"
#include "FullPane.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#ifndef THIS_FILE_DEFINED
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif

/////////////////////////////////////////////////////////////////////////////
// CReadyRoom dialog


CReadyRoom::CReadyRoom(CWnd* pParent /*=NULL*/)
	: RowanDialog(CReadyRoom::IDD, pParent)
{
	//{{AFX_DATA_INIT(CReadyRoom)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CReadyRoom::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CReadyRoom)
	DDX_Control(pDX, IDCX_PLAYERCHAT, m_IDCX_PLAYERCHAT);
	DDX_Control(pDX,IDC_RLIST_UN_PLAYER,m_IDC_RLIST_UN_PLAYER);
	DDX_Control(pDX,IDC_RSTATICCTRL3,m_IDC_RSTATICCTRL3);
	DDX_Control(pDX,IDC_RLIST_INCOMING_CHAT,m_IDC_RLIST_INCOMING_CHAT);
	DDX_Control(pDX,IDC_PLAYERCHAT,m_IDC_PLAYERCHAT);
	DDX_Control(pDX,IDC_RRADIO_DETAILS,m_IDC_RRADIO_DETAILS);
	DDX_Control(pDX,IDC_GAMENAME,m_IDC_GAMENAME);
	DDX_Control(pDX,IDC_RSTATICCTRL24,m_IDC_RSTATICCTRL24);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CReadyRoom, CDialog)
	//{{AFX_MSG_MAP(CReadyRoom)
	ON_WM_TIMER()
	ON_WM_CLOSE()
	ON_WM_DESTROY()
	ON_EN_UPDATE(IDCX_PLAYERCHAT, OnUpdatePlayerchat)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CReadyRoom message handlers

void CReadyRoom::RedrawRadioButtons()
{
	CRRadio* pradio;
	pradio=GETDLGITEM(IDC_RRADIO_DETAILS);
	CRStatic* s = GETDLGITEM(IDC_RSTATICCTRL3);
	

//DeadCode AMM 22Feb99 	if (_DPlay.GameType==DEATHMATCH)
//DeadCode AMM 22Feb99 	{
//DeadCode AMM 22Feb99 		pradio->ShowWindow(SW_HIDE);
//DeadCode AMM 22Feb99 		s->ShowWindow(SW_HIDE);
//DeadCode AMM 22Feb99 
//DeadCode AMM 22Feb99 	}else
//DeadCode AMM 22Feb99 	{
//DeadCode AMM 22Feb99 		pradio->ShowWindow(SW_SHOW);
//DeadCode AMM 22Feb99 		s->ShowWindow(SW_SHOW);
//DeadCode AMM 22Feb99 		pradio->AddButton(RESSTRING(EVERYBODY));
//DeadCode AMM 22Feb99 		pradio->AddButton(RESSTRING(MYSIDEONLY));
//DeadCode AMM 22Feb99 		if (_DPlay.sendtowho==255)
//DeadCode AMM 22Feb99 			pradio->SetCurrentSelection(0);
//DeadCode AMM 22Feb99 		else
//DeadCode AMM 22Feb99 			pradio->SetCurrentSelection(1);
//DeadCode AMM 22Feb99 	}	

//DeadCode AMM 22Feb99 	pradio->ShowWindow(SW_SHOW);
//DeadCode AMM 22Feb99 	s->ShowWindow(SW_SHOW);
//DeadCode AMM 22Feb99 	pradio->AddButton(RESSTRING(EVERYBODY));
//DeadCode AMM 22Feb99 
//DeadCode AMM 22Feb99 	if (_DPlay.GameType!=DEATHMATCH)
//DeadCode AMM 22Feb99 		pradio->AddButton(RESSTRING(MYSIDEONLY));

	if (_DPlay.sendtowho==255 || _DPlay.GameType==DEATHMATCH)
	{
		_DPlay.sendtowho=255;
		pradio->SetCurrentSelection(0);
	}
//DeadCode DAW 27Jun99 		pradio->SetCurrentSelection(0);
	else
	{
		_DPlay.sendtowho=128;
		pradio->SetCurrentSelection(1);
	}
//DeadCode DAW 27Jun99 		pradio->SetCurrentSelection(1);

	CRListBox* rlistbox;
	rlistbox=GETDLGITEM(IDC_RLIST_UN_PLAYER);
	rlistbox->SetHilightRow(-1);



}

BOOL CReadyRoom::OnInitDialog() 
{
	CDialog::OnInitDialog();
//	m_timer=SetTimer(2364,0,NULL);
	
	CRListBox* rlistbox;
	CString string;

	if (_DPlay.UpdateMission)
	{
		_DPlay.SendCSQuickStrucToPlayers(FALSE);
		_DPlay.UpdateMission=FALSE;
	}

// create dplay session if host

	Bool res;
	if (m_IDCX_PLAYERCHAT.m_hWnd)
		m_IDCX_PLAYERCHAT.SetLimitText(60);
	if (_DPlay.UIPlayerType==PLAYER_HOST && !_DPlay.PlayerCreated)
	{
		if (_DPlay.Lobbied)
		{
			res=_DPlay.LobbyConnect();
		}
		else
		{
			res=_DPlay.UINewPlayer(&_DPlay.PlayerName[0],&_DPlay.SessionName[0]);
		}
//DeadCode DAW 28Oct99 		res=_DPlay.UINewPlayer(&_DPlay.PlayerName[0],&_DPlay.SessionName[0]);

		if (res)
		{
			res=_DPlay.SetUpPlayerInfo(&_DPlay.PlayerName[0]);

			if (!res)
			{
//DeadCode AMM 14Dec98 				MessageBox("Could not set up player","Warning",MB_OK);
				RMessageBox(IDS_MIGALLEY,IDS_COULDNTSETUPPLAYER,NULL,IDS_OK);

				_DPlay.LeaveCommsFlag=TRUE;
			}
		}
		else
		{
//DeadCode AMM 14Dec98 			MessageBox("Could not create session or player","Warning",MB_OK);
			RMessageBox(IDS_MIGALLEY,IDS_NOTSESSION,NULL,IDS_OK);

// dont create ready room - leave

			_DPlay.LeaveCommsFlag=TRUE;
		}
	}

	if (_DPlay.GameType==COMMSQUICKMISSION) // && _DPlay.Host)
	{
//DeadCode AMM 05May99 		strncpy(_DPlay.GameName,RESLIST(QUICK_1,CSQuick1::currquickmiss),59);
//DeadCode AMM 05May99 		_DPlay.GameName[59]=NULL;
		_DPlay.GameIndex=CSQuick1::currquickmiss;
	}

//DeadCode AMM 05Aug98 	ULong n;
//DeadCode AMM 05Aug98 
//DeadCode AMM 05Aug98 	rlistbox=(CRListBox*)this->GetDlgItem(IDC_RLIST_UN_PLAYER);
//DeadCode AMM 05Aug98 	rlistbox->Clear();
//DeadCode AMM 05Aug98 	rlistbox->AddColumn(30);
//DeadCode AMM 05Aug98 	rlistbox->AddColumn(150);
//DeadCode AMM 05Aug98 	rlistbox->AddColumn(50);
//DeadCode AMM 05Aug98 	rlistbox->AddColumn(30);
//DeadCode AMM 05Aug98 	rlistbox->AddColumn(30);
//DeadCode AMM 05Aug98 
//DeadCode AMM 05Aug98 	string.LoadString(IDS_UN);
//DeadCode AMM 05Aug98 	rlistbox->AddString(string,0);
//DeadCode AMM 05Aug98 	rlistbox->AddString("1",0);
//DeadCode AMM 05Aug98 	rlistbox->AddString("2",0);
//DeadCode AMM 05Aug98 	rlistbox->AddString("3",0);
//DeadCode AMM 05Aug98 	rlistbox->AddString("4",0);
//DeadCode AMM 05Aug98 	rlistbox->AddString("5",0);
//DeadCode AMM 05Aug98 	rlistbox->AddString("6",0);
//DeadCode AMM 05Aug98 	rlistbox->AddString("7",0);
//DeadCode AMM 05Aug98 	rlistbox->AddString("8",0);
//DeadCode AMM 05Aug98 
//DeadCode AMM 05Aug98 	string.LoadString(IDS_NAME);
//DeadCode AMM 05Aug98 	rlistbox->AddString(string,1);
//DeadCode AMM 05Aug98 
//DeadCode AMM 05Aug98 	string.LoadString(IDS_AIRCRAFT);
//DeadCode AMM 05Aug98 	rlistbox->AddString(string,2);
//DeadCode AMM 05Aug98 
//DeadCode AMM 20Jul98 	rlistbox->AddString("Eric Cartman",1);
//DeadCode AMM 20Jul98 	rlistbox->AddString("Kyle",1);
//DeadCode AMM 20Jul98 	rlistbox->AddString("Stan",1);
//DeadCode AMM 20Jul98 	rlistbox->AddString("Kenny",1);
//DeadCode AMM 20Jul98 	rlistbox->AddString("Mr Hankey",1);
//DeadCode AMM 20Jul98 	rlistbox->AddString("Eric Cartman",1);
//DeadCode AMM 20Jul98 	rlistbox->AddString("Kyle",1);
//DeadCode AMM 20Jul98 	rlistbox->AddString("Stan",1);
//DeadCode AMM 05Aug98 
//DeadCode AMM 05Aug98 	for (n=0;n<MAXPLAYERS;n++)
//DeadCode AMM 05Aug98 	{
//DeadCode AMM 05Aug98 		if ((DPlay::H2H_Player+n)->MyTeam==TS_UN)
//DeadCode AMM 05Aug98 		{
//DeadCode AMM 05Aug98 			string.LoadString(IDS_NAME);
//DeadCode AMM 05Aug98 			rlistbox->AddString((DPlay::H2H_Player+n)->name,1);
//DeadCode AMM 05Aug98 			string.LoadString(IDS_AIRCRAFT);
//DeadCode AMM 05Aug98 			rlistbox->AddString("F 86",2);
//DeadCode AMM 05Aug98 		}
//DeadCode AMM 05Aug98 	}	
//DeadCode AMM 05Aug98 
//DeadCode AMM 20Jul98 	string.LoadString(IDS_AIRCRAFT);
//DeadCode AMM 20Jul98 	rlistbox->AddString(string,2);
//DeadCode AMM 20Jul98 	rlistbox->AddString("F 86",2);
//DeadCode AMM 20Jul98 	rlistbox->AddString("F 86",2);
//DeadCode AMM 20Jul98 	rlistbox->AddString("F 86",2);
//DeadCode AMM 20Jul98 	rlistbox->AddString("F 86",2);
//DeadCode AMM 20Jul98 	rlistbox->AddString("F 86",2);
//DeadCode AMM 20Jul98 	rlistbox->AddString("F 86",2);
//DeadCode AMM 20Jul98 	rlistbox->AddString("F 86",2);
//DeadCode AMM 20Jul98 	rlistbox->AddString("F 86",2);
//DeadCode AMM 05Aug98 
//DeadCode AMM 05Aug98 	string.LoadString(IDS_KILLS);
//DeadCode AMM 05Aug98 	rlistbox->AddString(string,3);
//DeadCode AMM 05Aug98 
//DeadCode AMM 05Aug98 	string.LoadString(IDS_LOSSES);
//DeadCode AMM 05Aug98 	rlistbox->AddString(string,4);
//DeadCode AMM 05Aug98 
//DeadCode AMM 05Aug98 	rlistbox=(CRListBox*)this->GetDlgItem(IDC_RLIST_RED_PLAYER);
//DeadCode AMM 05Aug98 	rlistbox->Clear();
//DeadCode AMM 05Aug98 	rlistbox->AddColumn(30);
//DeadCode AMM 05Aug98 	rlistbox->AddColumn(150);
//DeadCode AMM 05Aug98 	rlistbox->AddColumn(50);
//DeadCode AMM 05Aug98 	rlistbox->AddColumn(30);
//DeadCode AMM 05Aug98 	rlistbox->AddColumn(30);
//DeadCode AMM 05Aug98 
//DeadCode AMM 05Aug98 	string.LoadString(IDS_RED);
//DeadCode AMM 05Aug98 	rlistbox->AddString(string,0);
//DeadCode AMM 05Aug98 	rlistbox->AddString("1",0);
//DeadCode AMM 05Aug98 	rlistbox->AddString("2",0);
//DeadCode AMM 05Aug98 	rlistbox->AddString("3",0);
//DeadCode AMM 05Aug98 	rlistbox->AddString("4",0);
//DeadCode AMM 05Aug98 	rlistbox->AddString("5",0);
//DeadCode AMM 05Aug98 	rlistbox->AddString("6",0);
//DeadCode AMM 05Aug98 	rlistbox->AddString("7",0);
//DeadCode AMM 05Aug98 	rlistbox->AddString("8",0);
//DeadCode AMM 05Aug98 
//DeadCode AMM 05Aug98 	string.LoadString(IDS_NAME);
//DeadCode AMM 05Aug98 	rlistbox->AddString(string,1);
//DeadCode AMM 05Aug98 
//DeadCode AMM 05Aug98 	string.LoadString(IDS_AIRCRAFT);
//DeadCode AMM 05Aug98 	rlistbox->AddString(string,2);
//DeadCode AMM 05Aug98 
//DeadCode AMM 05Aug98 	for (n=0;n<MAXPLAYERS;n++)
//DeadCode AMM 05Aug98 	{
//DeadCode AMM 05Aug98 		if ((DPlay::H2H_Player+n)->MyTeam==TS_COMMIE)
//DeadCode AMM 05Aug98 		{
//DeadCode AMM 05Aug98 			string.LoadString(IDS_NAME);
//DeadCode AMM 05Aug98 			rlistbox->AddString((DPlay::H2H_Player+n)->name,1);
//DeadCode AMM 05Aug98 			string.LoadString(IDS_AIRCRAFT);
//DeadCode AMM 05Aug98 			rlistbox->AddString("MIG",2);
//DeadCode AMM 05Aug98 		}
//DeadCode AMM 05Aug98 	}	
//DeadCode AMM 05Aug98 
//DeadCode AMM 05Aug98 	string.LoadString(IDS_KILLS);
//DeadCode AMM 05Aug98 	rlistbox->AddString(string,3);
//DeadCode AMM 05Aug98 
//DeadCode AMM 05Aug98 	string.LoadString(IDS_LOSSES);
//DeadCode AMM 05Aug98 	rlistbox->AddString(string,4);

	rlistbox=GETDLGITEM(IDC_RLIST_INCOMING_CHAT);
	rlistbox->Clear();
	rlistbox->AddColumn(120);
	rlistbox->AddColumn(30);

//	rlistbox=(CRListBox*)this->GetDlgItem(IDC_RSTATICCTRL4);
//	rlistbox->Clear();
//	rlistbox->AddString(_DPlay.GameName,1);

//DeadCode AMM 20Jul98 	rlistbox->AddString("Stan",0);
//DeadCode AMM 20Jul98 	rlistbox->AddString("Oh, my God! They killed Kenny! You Bastards!",1);

	CRRadio* pradio;
	pradio=GETDLGITEM(IDC_RRADIO_DETAILS);
	CRStatic* s = GETDLGITEM(IDC_RSTATICCTRL3);

	pradio->ShowWindow(SW_SHOW);
	s->ShowWindow(SW_SHOW);
	pradio->AddButton(RESSTRING(EVERYBODY));

	if (_DPlay.GameType!=DEATHMATCH)
		pradio->AddButton(RESSTRING(MYSIDEONLY));

	RedrawRadioButtons();

	_DPlay.MainSheetCount=FALSE;
	_DPlay.FlyNowFlag=FALSE;

	if (!_DPlay.LoadRadioMessages())
	{//initialise messages
		_DPlay.InitMessages();
//DeadCode AMM 18Jan99 		for (int n=0;n<10;n++)
//DeadCode AMM 18Jan99 			strcpy(_DPlay.Messages[_DPlay.mySlot][n],RESSTRING(L_RADIOMSG0+n));
	}
	
	rroom_timer=SetTimer(TIMER_READYROOM,0,NULL); // set sheet up first before starting timer

	_DPlay.SendInReadyRoomMessage();

	if (_DPlay.Host)
	{
		if (_DPlay.GameType==COMMSQUICKMISSION)
		{
// when host enters ready room reset pilots to NOTFLYING because this will 
// be a new game

			for (int p=0;p<PILOTS_PER_CAMPAIGN;p++)
			{
				MMC.Active_Pilots[p]=MMC.Active_Pilots_Init[p];
			}
		}
		_DPlay.SendPilotsStatus(false);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BEGIN_EVENTSINK_MAP(CReadyRoom, CDialog)
    //{{AFX_EVENTSINK_MAP(CReadyRoom)
	ON_EVENT(CReadyRoom, IDC_PLAYERCHAT, 1 /* ReturnPressed */, OnReturnPressedPlayerchat, VTS_BSTR)
	ON_EVENT(CReadyRoom, IDC_RRADIO_DETAILS, 1 /* Selected */, OnSelectedRradioDetails, VTS_I4)
	ON_EVENT(CReadyRoom, IDC_RLIST_UN_PLAYER, 1 /* Select */, OnSelectRlistUnPlayer, VTS_I4 VTS_I4)
	ON_EVENT(CReadyRoom, IDC_PLAYERCHAT, 2 /* TextChanged */, OnTextChangedPlayerchat, VTS_I4)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CReadyRoom::OnReturnPressedPlayerchat(LPCTSTR text) 
{
	if (text[0])
	{
		CRListBox* rlistbox;
		CREdit* poo;

		rlistbox=GETDLGITEM(IDC_RLIST_INCOMING_CHAT);
		if (!strcmp(text,"megashootcheaton"))
		{
			_DPlay.megashootcheat=true;
		}
		else if (!strcmp(text,"megashootcheatoff"))
		{
			_DPlay.megashootcheat=false;
		}
		else if (!strcmp(text,"invulnerablecheaton"))
		{
			_DPlay.megashootcheat=false;
		}
		else if (!strcmp(text,"invulnerablecheatoff"))
		{
			_DPlay.megashootcheat=false;
		}
		else if (!strcmp(text,"liftcheaton"))
		{
			_DPlay.liftcheat=true;
		}
		else if (!strcmp(text,"liftcheatoff"))
		{
			_DPlay.liftcheat=false;
		}
		else
		{
//DeadCode DAW 28Oct99 			rlistbox=GETDLGITEM(IDC_RLIST_INCOMING_CHAT);

	//DeadCode AMM 05Aug98 	rlistbox->AddString(&_DPlay.PlayerName[0],0);
			rlistbox->AddString((DPlay::H2H_Player+_DPlay.mySlot)->name,0);
			rlistbox->AddString(text,1);
	//	_DPlay.UISendDialogue((DPlay::H2H_Player+_DPlay.mySlot),(char*)text);
			_DPlay.UISendDialogue((char*)text);
			_DPlay.AddChatMessageToBuffer((DPlay::H2H_Player+_DPlay.mySlot)->name,(char*)text);
		}
		rlistbox->SetHilightRow(-1) ;							//AMM 10Jul99
		if (m_IDCX_PLAYERCHAT.m_hWnd)
		{
			m_IDCX_PLAYERCHAT.SetWindowText("");

		}
		else
		{
			poo=GETDLGITEM(IDC_PLAYERCHAT);
			poo->SetCaption("");										  //AMM 06/07/99
		}

//DeadCode AMM 07Jul99 		poo->SetWindowText("");
	}
}
void	CReadyRoom::OnOK()
{
	CString buffer;
	m_IDCX_PLAYERCHAT.GetWindowText(buffer);
	OnReturnPressedPlayerchat(buffer);
}

void CReadyRoom::OnTimer(UINT nIDEvent) 
{
// have this first for quick exit in case bad session creation 

	if (_DPlay.LeaveCommsFlag)
	{
		KillTimer(rroom_timer);

// get me outta here asap

		FullPanel()->OnSelectRlistbox(0,0);					
		return;

	}

	if (nIDEvent==rroom_timer && _DPlay.PlayerCreated)
	{
//DeadCode AMM 24Feb99 		if (_DPlay.LeaveCommsFlag)
//DeadCode AMM 24Feb99 		{
//DeadCode AMM 24Feb99 			KillTimer(rroom_timer);
//DeadCode AMM 24Feb99 
//DeadCode AMM 24Feb99 // get me outta here asap
//DeadCode AMM 24Feb99 
//DeadCode AMM 24Feb99 //DeadCode JIM 12Jan99 			RFullPanelDial* fullscreen=(RFullPanelDial*)GetParent();
//DeadCode AMM 24Feb99 			FullPanel()->OnSelectRlistbox(0,0);					//JIM 12Jan99
//DeadCode AMM 24Feb99 			return;
//DeadCode AMM 24Feb99 		}

		if (_DPlay.DisplayInfo)
		{
			_DPlay.DisplayPlayerInfo();
			_DPlay.DisplayInfo=FALSE;
		}

		_DPlay.UIUpdateMainSheet();

//DeadCode AMM 02Dec98 		if (_DPlay.LeaveCommsFlag)
//DeadCode AMM 02Dec98 		{
//DeadCode AMM 02Dec98 // get me outta here asap
//DeadCode AMM 02Dec98 
//DeadCode AMM 02Dec98 			RFullPanelDial* fullscreen=(RFullPanelDial*)GetParent();
//DeadCode AMM 02Dec98 			fullscreen->OnSelectRlistbox(0,0);
//DeadCode AMM 02Dec98 			return;
//DeadCode AMM 02Dec98 		}
//DeadCode AMM 02Dec98 		else if (_DPlay.FlyNowFlag)
		if (_DPlay.FlyNowFlag)
		{
			if (_DPlay.UINetworkSelectFly())
			{
				KillTimer(rroom_timer);

// need to launch quickmissionflight sheet

//DeadCode JIM 12Jan99 				RFullPanelDial* fullscreen=(RFullPanelDial*)GetParent();
// 				FullScreen* fs;
				FullPanel()->OnSelectRlistbox(1,1);
				return;
			}
			else
			{
				_DPlay.FlyNowFlag=FALSE;
				DPlay::H2H_Player[_DPlay.mySlot].status=CPS_READYROOM;
				_DPlay.SendInReadyRoomMessage();
			}
		}
	}
	CDialog::OnTimer(nIDEvent);
}

void CReadyRoom::OnClose() 
{
//	_DPlay.MainSheetCount=FALSE;

	KillTimer(rroom_timer);
	CDialog::OnClose();
}

void	DPlay::DisplayReadyDialogue(char* name, char* text)
{
	CRListBox* rlistbox;
 	rlistbox=(CRListBox*)RDialog::m_pView->m_pfullpane->pdial[0]->GetDlgItem(IDC_RLIST_INCOMING_CHAT);
	if (rlistbox)
	{
	 	rlistbox->AddString(name,0);
 		rlistbox->AddString(text,1);
	}
	rlistbox->SetHilightRow(-1) ;								//AMM 10Jul99
	//delete rlistbox;
}

void	DPlay::DisplayPlayerInfo()
{
// now only called from ready room so dont need check

//DeadCode AMM 17Nov98 	if (DPlay::H2H_Player[_DPlay.mySlot].status!=CPS_READYROOM)
//DeadCode AMM 17Nov98 		return;

	CRListBox* rlistbox;
	CString string;
	ULong n,t;

// may need to update gamename as well

	if (_DPlay.GameType==COMMSQUICKMISSION) 
	{
//DeadCode AMM 05May99 		strncpy(_DPlay.GameName,RESLIST(QUICK_1,CSQuick1::currquickmiss),59);
//DeadCode AMM 05May99 		_DPlay.GameName[59]=NULL;
		_DPlay.GameIndex=CSQuick1::currquickmiss;
	}

	rlistbox=(CRListBox*)RDialog::m_pView->m_pfullpane->pdial[0]->GetDlgItem(IDC_RLIST_UN_PLAYER);
//DeadCode AMM 05Aug98 	rlistbox=(CRListBox*)this->GetDlgItem(IDC_RLIST_UN_PLAYER);
	rlistbox->Clear();
	rlistbox->AddColumn(40);
	rlistbox->AddColumn(140);
	rlistbox->AddColumn(60);
	rlistbox->AddColumn(90);
	rlistbox->AddColumn(50);
	rlistbox->AddColumn(2);

//	string.LoadString(IDS_UN);
	rlistbox->AddString("",0);

	string.LoadString(IDS_NAME);
	rlistbox->AddString(string,1);

	string.LoadString(IDS_AIRCRAFT);
	rlistbox->AddString(string,2);

	string.LoadString(IDS_STATUS);
	rlistbox->AddString(string,3);
	string.LoadString(IDS_KILLS);
	rlistbox->AddString(string,4);

	string.LoadString(IDS_LOSSES);
	rlistbox->AddString(string,5);

	t=1;
	char num[8],num2[8];
	char score[10];

	for (n=0;n<MAXPLAYERS;n++)
	{
		if ((H2H_Player+n)->MyTeam==TS_UN || (H2H_Player+n)->MyTeam==TS_NONE)
		{
			if (_DPlay.GameType==DEATHMATCH)
			{
				_itoa(t++,score,10);
			}
			else
			{
				_itoa(t++,num,10);
				strcpy(score,"UN ");
				strcat(score,num);
			}
			rlistbox->AddString(score,0);
			rlistbox->AddString(H2H_Player[n].name,1);
			rlistbox->AddString(RESLIST(SQ_BF_F86A, H2H_Player[n].squadron), 2);
//DeadCode AMM 14Dec98 			rlistbox->AddString(RESLIST(CPS_QUIT,H2H_Player[n].status),3);
			rlistbox->AddString(RESLIST(CPS_STATUS,H2H_Player[n].status),3);

//create score
			
			if (_DPlay.GameType==DEATHMATCH)
			{
				_itoa((H2H_Player+n)->kills,num,10);
				rlistbox->AddString(num,4);
				_itoa((H2H_Player+n)->deaths,num,10);
				rlistbox->AddString(num,5);
			}
			else
			{
// need form 1/3 etc to indicate kills/team kills etc
				
				_itoa((H2H_Player+n)->kills,num,10);
				if ((H2H_Player+n)->MyTeam==(H2H_Player+mySlot)->MyTeam)
				{
					_itoa(MyTeamKills,num2,10);
				}
				else
				{
					_itoa(EnemyTeamKills,num2,10);
				}
				strcpy(score,num);
				strcat(score,"/");
				strcat(score,num2);
				rlistbox->AddString(score,4);

				_itoa((H2H_Player+n)->deaths,num,10);
				if ((H2H_Player+n)->MyTeam==(H2H_Player+mySlot)->MyTeam)
				{
					_itoa(MyTeamDeaths,num2,10);
				}
				else
				{
					_itoa(EnemyTeamDeaths,num2,10);
				}
				strcpy(score,num);
				strcat(score,"/");
				strcat(score,num2);
				rlistbox->AddString(score,5);
			}

		}
	}


//DeadCode AMM 05Aug98 	rlistbox=(CRListBox*)this->GetDlgItem(IDC_RLIST_RED_PLAYER);
//DeadCode AMM 03Sep98 	rlistbox=(CRListBox*)RDialog::m_pView->m_pfullpane->pdial[0]->GetDlgItem(IDC_RLIST_RED_PLAYER);
//DeadCode AMM 03Sep98 	rlistbox=(CRListBox*)RDialog::m_pView->m_pfullpane->pdial[0]->GetDlgItem(IDC_RLIST_UN_PLAYER);
//DeadCode AMM 03Sep98 	rlistbox->Clear();
//DeadCode AMM 03Sep98 	rlistbox->AddColumn(30);
//DeadCode AMM 03Sep98 	rlistbox->AddColumn(150);
//DeadCode AMM 03Sep98 	rlistbox->AddColumn(50);
//DeadCode AMM 03Sep98 	rlistbox->AddColumn(30);
//DeadCode AMM 03Sep98 	rlistbox->AddColumn(30);
//DeadCode AMM 03Sep98 
//DeadCode AMM 03Sep98 	string.LoadString(IDS_RED);
//DeadCode AMM 03Sep98 	rlistbox->AddString(string,0);
//DeadCode AMM 03Sep98 
//DeadCode AMM 03Sep98 	string.LoadString(IDS_NAME);
//DeadCode AMM 03Sep98 	rlistbox->AddString(string,1);
//DeadCode AMM 03Sep98 
//DeadCode AMM 03Sep98 	string.LoadString(IDS_AIRCRAFT);
//DeadCode AMM 03Sep98 	rlistbox->AddString(string,2);
//DeadCode AMM 03Sep98 
//DeadCode AMM 03Sep98 	string.LoadString(IDS_KILLS);
//DeadCode AMM 03Sep98 	rlistbox->AddString(string,3);
//DeadCode AMM 03Sep98 
//DeadCode AMM 03Sep98 	string.LoadString(IDS_LOSSES);
//DeadCode AMM 03Sep98 	rlistbox->AddString(string,4);

	if (_DPlay.GameType!=DEATHMATCH)
		t=1;

	for (n=0;n<MAXPLAYERS;n++)
	{
		if ((H2H_Player+n)->MyTeam==TS_COMMIE)
		{
			if (_DPlay.GameType==DEATHMATCH)
			{
				_itoa(t++,score,10);
			}
			else
			{
				_itoa(t++,num,10);
				strcpy(score,"Red ");
				strcat(score,num);
			}
			rlistbox->AddString(score,0);
			rlistbox->AddString(H2H_Player[n].name,1);
//DeadCode AMM 13Oct98 			string.LoadString(IDS_NAME);
//DeadCode AMM 13Oct98 			rlistbox->AddString((H2H_Player+n)->name,1);
//DeadCode AMM 13Oct98 			string.LoadString(IDS_AIRCRAFT);
//DeadCode AMM 13Oct98 			rlistbox->AddString("MIG",2);
			rlistbox->AddString(RESLIST(SQ_BF_F86A, H2H_Player[n].squadron), 2);
//DeadCode AMM 14Dec98 			rlistbox->AddString(RESLIST(CPS_QUIT,H2H_Player[n].status),3);
			rlistbox->AddString(RESLIST(CPS_STATUS,H2H_Player[n].status),3);

//create score
			
			if (_DPlay.GameType==DEATHMATCH)
			{
				_itoa((H2H_Player+n)->kills,num,10);
				rlistbox->AddString(num,4);
				_itoa((H2H_Player+n)->deaths,num,10);
				rlistbox->AddString(num,5);
			}
			else
			{
// need form 1/3 etc to indicate kills/team kills etc

				_itoa((H2H_Player+n)->kills,num,10);
				if ((H2H_Player+n)->MyTeam==(H2H_Player+mySlot)->MyTeam)
				{
					_itoa(MyTeamKills,num2,10);
				}
				else
				{
					_itoa(EnemyTeamKills,num2,10);
				}
				strcpy(score,num);
				strcat(score,"/");
				strcat(score,num2);
				rlistbox->AddString(score,4);

				_itoa((H2H_Player+n)->deaths,num,10);
				if ((H2H_Player+n)->MyTeam==(H2H_Player+mySlot)->MyTeam)
				{
					_itoa(MyTeamDeaths,num2,10);
				}
				else
				{
					_itoa(EnemyTeamDeaths,num2,10);
				}
				strcpy(score,num);
				strcat(score,"/");
				strcat(score,num2);
				rlistbox->AddString(score,5);			
			}
		}
	}	
	//delete rlistbox;

	CRStatic* rstatic;

//	rstatic=(CRStatic*)RDialog::m_pView->m_pfullpane->pdial[0]->GetDlgItem(IDC_RSTATICCTRL4);
	rstatic=(CRStatic*)RDialog::m_pView->m_pfullpane->pdial[0]->GetDlgItem(IDC_GAMENAME);
//	CRStatic* rstatic =  GetDlgItem(IDC_GAMENAME);
//	if (_DPlay.GameType==COMMSQUICKMISSION && _DPlay.Host)
//	{
//		rstatic->SetString(RESLIST(QUICK_1, CSQuick1::currquickmiss));
//	}else
//	{
//DeadCode AMM 05May99 		rstatic->SetString(_DPlay.GameName);
//	}
	//delete	rstatic;
	if (_DPlay.GameType==COMMSQUICKMISSION)
		rstatic->SetString(LoadResString(CSQuick1::quickmissions[CSQuick1::currquickmiss].missionname));
	else
		rstatic->SetString(_DPlay.GameName);

}

void CReadyRoom::OnDestroy() 
{
//	_DPlay.MainSheetCount=FALSE;

	KillTimer(rroom_timer);

	CDialog::OnDestroy();
}

void CReadyRoom::OnSelectedRradioDetails(long ButtonNum) 
{
//DeadCode AMM 22Feb99 	if (_DPlay.sendtowho<128)
//DeadCode AMM 22Feb99 	{
//DeadCode AMM 22Feb99 		if (_DPlay.allchat)
//DeadCode AMM 22Feb99 			_DPlay.sendtowho=255;
//DeadCode AMM 22Feb99 		else
//DeadCode AMM 22Feb99 			_DPlay.sendtowho=128;
//DeadCode AMM 22Feb99 	}
//DeadCode AMM 22Feb99 	else
//DeadCode AMM 22Feb99 	if (_DPlay.sendtowho==255 && _DPlay.GameType!=DEATHMATCH)
//DeadCode AMM 22Feb99 	{
//DeadCode AMM 22Feb99 		_DPlay.sendtowho = 128;
//DeadCode AMM 22Feb99 		_DPlay.allchat=false;
//DeadCode AMM 22Feb99 	}
//DeadCode AMM 22Feb99 	else
//DeadCode AMM 22Feb99 	{
//DeadCode AMM 22Feb99 		_DPlay.sendtowho = 255;
//DeadCode AMM 22Feb99 		_DPlay.allchat=true;
//DeadCode AMM 22Feb99 	}

	if (ButtonNum)
		_DPlay.sendtowho=128;
	else
		_DPlay.sendtowho=255;

	RedrawRadioButtons();



}


void CReadyRoom::OnSelectRlistUnPlayer(long row, long column) 
{
	CRRadio* pradio;
	pradio=GETDLGITEM(IDC_RRADIO_DETAILS);
	pradio->SetCurrentSelection(-1);
	_DPlay.SelectPlayerToChatTo(row-1);
	
}

void CReadyRoom::OnTextChangedPlayerchat(LPSTR text) 
{
	// TODO: Add your control notification handler code here
		trunc(text,40);
}

void CReadyRoom::OnUpdatePlayerchat() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function to send the EM_SETEVENTMASK message to the control
	// with the ENM_UPDATE flag ORed into the lParam mask.
	
	// TODO: Add your control notification handler code here
	
}
