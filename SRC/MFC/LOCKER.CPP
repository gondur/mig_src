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

// Locker.cpp : implementation file
//


#include "stdafx.h"
#include "mig.h"
#include "Locker.h"
#include "Visitors.h"
#include "RRadio.h"
#include "winmove.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#ifndef THIS_FILE_DEFINED											  //RDH 17/03/99
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif

/////////////////////////////////////////////////////////////////////////////
// CLockerRoom dialog


CLockerRoom::CLockerRoom(CWnd* pParent /*=NULL*/)
	: RowanDialog(CLockerRoom::IDD, pParent)
{
	currquickmiss = 0;
	//{{AFX_DATA_INIT(CLockerRoom)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CLockerRoom::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLockerRoom)
	DDX_Control(pDX, IDCX_PLAYERCHAT, m_IDCX_PLAYERCHAT);
	DDX_Control(pDX, IDCX_NAME, m_IDCX_NAME);
	DDX_Control(pDX, IDCX_GAME_TITLE, m_IDCX_GAME_TITLE);
	DDX_Control(pDX,IDC_NAME,m_IDC_NAME);
	DDX_Control(pDX,IDC_RSTATICCTRL3,m_IDC_RSTATICCTRL3);
	DDX_Control(pDX,IDC_GAME_TITLE,m_IDC_GAME_TITLE);
	DDX_Control(pDX,IDC_RSTATICCTRL4,m_IDC_RSTATICCTRL4);
	DDX_Control(pDX,IDC_RSTATICCTRL24,m_IDC_RSTATICCTRL24);
	DDX_Control(pDX,IDC_RSTATICCTRL6,m_IDC_RSTATICCTRL6);
	DDX_Control(pDX,IDC_RRADIO_GAMETYPE,m_IDC_RRADIO_GAMETYPE);
	DDX_Control(pDX,IDC_RRADIO_SELECTSIDE,m_IDC_RRADIO_SELECTSIDE);
	DDX_Control(pDX,IDC_RSTATICCTRL7,m_IDC_RSTATICCTRL7);
	DDX_Control(pDX,IDC_PLAYERCHAT,m_IDC_PLAYERCHAT);
	DDX_Control(pDX,IDC_RSTATICCTRL26,m_IDC_RSTATICCTRL26);
	DDX_Control(pDX,IDC_GRPDESC,m_IDC_GRPDESC);
	DDX_Control(pDX,IDC_PILOTEDFLAG,m_IDC_PILOTEDFLAG);
	DDX_Control(pDX,IDC_GAME_TITLECOMBO,m_IDC_GAME_TITLECOMBO);
	DDX_Control(pDX,IDC_DATARATE,m_IDC_DATARATE);
	DDX_Control(pDX,IDC_SCENARIO,m_IDC_SCENARIO);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLockerRoom, CDialog)
	//{{AFX_MSG_MAP(CLockerRoom)
	ON_WM_CLOSE()
	ON_WM_DESTROY()
	ON_EN_UPDATE(IDCX_GAME_TITLE, OnUpdateGameTitle)
	ON_EN_UPDATE(IDCX_NAME, OnUpdateName)
	ON_EN_UPDATE(IDCX_PLAYERCHAT, OnUpdatePlayerchat)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLockerRoom message handlers

BEGIN_EVENTSINK_MAP(CLockerRoom, CDialog)
    //{{AFX_EVENTSINK_MAP(CLockerRoom)
	ON_EVENT(CLockerRoom, IDC_VISITORS, 1 /* Clicked */, OnClickedVisitors, VTS_NONE)
	ON_EVENT(CLockerRoom, IDC_RRADIO_GAMETYPE, 1 /* Selected */, OnSelectedRradioGametype, VTS_I4)
	ON_EVENT(CLockerRoom, IDC_PILOTEDFLAG, 1 /* Clicked */, OnClickedPilotedflag, VTS_NONE)
	ON_EVENT(CLockerRoom, IDC_NAME, 2 /* TextChanged */, OnTextChangedName, VTS_I4)
	ON_EVENT(CLockerRoom, IDC_GAME_TITLE, 2 /* TextChanged */, OnTextChangedGameTitle, VTS_I4)
	ON_EVENT(CLockerRoom, IDC_PLAYERCHAT, 2 /* TextChanged */, OnTextChangedPlayerchat, VTS_I4)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CLockerRoom::OnClickedVisitors() 
{
	RDialog::MakeTopDialog(CRect(50,50,0,0),
								DialBox(FIL_GAMESETUP_1024,new CVisitorsBook)//,Edges(EDGE::ALIGN_MIN + EDGE::ACTIONS_SPLITTER,EDGE::ALIGN_MIN,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE))
							);		
}

void CLockerRoom::RedrawSide()
{
	CRRadio* pradio;
	pradio=GETDLGITEM(IDC_RRADIO_SELECTSIDE);

	if (	(_DPlay.GameType == DEATHMATCH)
		||	(		(_DPlay.GameType == COMMSCAMPAIGN)
//DEADCODE AMM 10/06/99 				&&	(_DPlay.UIPlayerType == PLAYER_HOST)
			)
		)
		pradio->ShowWindow(SW_HIDE);
	else
		pradio->ShowWindow(SW_SHOW);

}
void CLockerRoom::RedrawCombo()
{
	CRStatic* s=GETDLGITEM(IDC_SCENARIO);
	CRCombo* combo;
	combo=GETDLGITEM(IDC_GAME_TITLECOMBO);
	if (_DPlay.GameType == COMMSQUICKMISSION)
	{
		combo->ShowWindow(SW_HIDE);
		s->ShowWindow(SW_HIDE);
	}else 
	{
		combo->ShowWindow(SW_SHOW);
		s->ShowWindow(SW_SHOW);
		combo->Clear();
		if (_DPlay.GameType == DEATHMATCH)
		{
			combo->RESCOMBO(DEATHMATCH0,8)->SetIndex(currquickmiss);
		}else if (_DPlay.GameType == TEAMPLAY)
		{
			combo->RESCOMBO(TEAMPLAY0,8)->SetIndex(currquickmiss);
		}else
		{
			combo->RESCOMBO(SCAMPAIGNSELECT1,5)->SetIndex(currquickmiss);
		}
	}

//DeadCode DAW 01Nov99 	if (_DPlay.UIPlayerType==PLAYER_GUEST)
		combo->SetEnabled(false);
#ifndef	MIG_DEMO_VER
		if (_DPlay.UIPlayerType==PLAYER_HOST)
			combo->SetEnabled(true);
#endif

}

BOOL CLockerRoom::OnInitDialog() 
{
	CDialog::OnInitDialog();
	CRRadio* pradio;
	CString string;
	CREdit*	editbox;

	if (_DPlay.UIPlayerType==PLAYER_HOST)
	{
		_DPlay.GameType=DEATHMATCH;
	}

	m_IDC_GAME_TITLECOMBO.SetCircularStyle(TRUE);

	pradio=GETDLGITEM(IDC_RRADIO_GAMETYPE);



#ifndef	MIG_DEMO_VER

	if (_DPlay.UIPlayerType==PLAYER_HOST)
	{
		string.LoadString(IDS_DEATHMATCH);
		pradio->AddButton(string);
		string.LoadString(IDS_TEAMPLAY);
		pradio->AddButton(string);
		string.LoadString(IDS_QUICKMISSIONCOMM);
		pradio->AddButton(string);
//DEADCODE RDH 22/06/99 		string.LoadString(IDS_CAMPAIGNCOMMS);
//DEADCODE RDH 22/06/99 		pradio->AddButton(string);

		pradio=GETDLGITEM(IDC_RRADIO_SELECTSIDE);
		pradio->AddButton(RESSTRING(UN));
		pradio->AddButton(RESSTRING(RED));


	}
	else
#endif
	{
		switch (_DPlay.GameType)
		{
		case DEATHMATCH:
			string.LoadString(IDS_DEATHMATCH);
			pradio->AddButton(string);
			break;

		case TEAMPLAY:
			string.LoadString(IDS_TEAMPLAY);
			pradio->AddButton(string);
			break;

		case COMMSQUICKMISSION:
			string.LoadString(IDS_QUICKMISSIONCOMM);
			pradio->AddButton(string);
			break;

//DEADCODE RDH 22/06/99 		case COMMSCAMPAIGN:
//DEADCODE RDH 22/06/99 			string.LoadString(IDS_CAMPAIGNCOMMS);
//DEADCODE RDH 22/06/99 			pradio->AddButton(string);
//DEADCODE RDH 22/06/99 			break;

		default :
//DeadCode AMM 14Dec98 			MessageBox("Invalid Game Type",MB_OK);
			_DPlay.GameType=DEATHMATCH;
			break;
		}

		currquickmiss=_DPlay.GameIndex;

		if (_DPlay.GameType!=DEATHMATCH)
		{
			pradio=GETDLGITEM(IDC_RRADIO_SELECTSIDE);
			pradio->AddButton(RESSTRING(UN));
			pradio->AddButton(RESSTRING(RED));
		}
	}
	CRCombo* combo;
	combo=GETDLGITEM(IDC_DATARATE);
	int index;
	index = 6 - _DPlay.RateDivider;
	if (index < 0)
		index = 0;
	if (index > 4)
		index = 4;
	combo->RESCOMBO(BLMHT_BOT,5)->SetIndex(index);

	if (_DPlay.UIPlayerType==PLAYER_GUEST)
		combo->SetEnabled(false);


	RedrawSide();
	RedrawCombo();
	FullPanel()->ResetLoadGameOption();							//JIM 12Jan99

	
	CRStatic* s=GETDLGITEM(IDC_GRPDESC);
	CRButton*  b=GETDLGITEM(IDC_PILOTEDFLAG);
	editbox=GetDlgItem(IDC_GAME_TITLE);

	if (m_IDCX_GAME_TITLE.m_hWnd)
		if (_DPlay.UIPlayerType==PLAYER_GUEST)
		{
			s->ShowWindow(SW_SHOW);
			b->ShowWindow(SW_SHOW);
			m_IDCX_GAME_TITLE.SetReadOnly(TRUE);
		}
		else
		{
			if (_DPlay.Lobbied)
				m_IDCX_GAME_TITLE.SetReadOnly(TRUE);
			else
				m_IDCX_GAME_TITLE.SetLimitText(SESSIONNAMELEN - 1);
			s->ShowWindow(SW_HIDE);
			b->ShowWindow(SW_HIDE);

		}
	else
		if (_DPlay.UIPlayerType==PLAYER_GUEST)
		{
			s->ShowWindow(SW_SHOW);
			b->ShowWindow(SW_SHOW);
			editbox->SetEnabled(false);
	//		editbox->SetWindowText(&_DPlay.SessionName[0]);
		}else
		{
			if (_DPlay.Lobbied)
				editbox->SetEnabled(false);
			else
				editbox->SetEnabled(true);
			s->ShowWindow(SW_HIDE);
			b->ShowWindow(SW_HIDE);
		}

	if (_DPlay.UIPlayerType==PLAYER_HOST && !_DPlay.Lobbied)
	{
		strcpy(_DPlay.SessionName,"MiG Alley");
	}

	if (_DPlay.SessionName[0])
	{
		if (m_IDCX_GAME_TITLE.m_hWnd)
			m_IDCX_GAME_TITLE.SetWindowText(_DPlay.SessionName);
		else
			GETDLGITEM(IDC_GAME_TITLE)->SetWindowText(_DPlay.SessionName);
	}
	if (m_IDCX_PLAYERCHAT.m_hWnd)
		m_IDCX_PLAYERCHAT.SetLimitText(PASSWORDNAMELEN - 1);	
	if (_DPlay.PlayerName[0])
		if (m_IDCX_NAME.m_hWnd)
		{
			m_IDCX_NAME.SetWindowText(_DPlay.PlayerName);
			m_IDCX_NAME.SetLimitText(PLAYERNAMELEN - 1);	
		}
		else
		{
			editbox=GETDLGITEM(IDC_NAME);
//		editbox->SetFontNum(-8);
//		editbox->SetEnabled(FALSE);
			editbox->SetWindowText(_DPlay.PlayerName);
		}

// use _DPlay.RateDivider to set default connection speed (5 options, 2=quickest - 6=slowest)

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CLockerRoom::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	
	CDialog::OnClose();

}
void CLockerRoom::UpDateDPlay()
{																			   
// get info from locker room and put into dplay structures
	CRRadio* radiobox;
	int selection;


	CREdit* editbox;
	CString	buffer;

	editbox=GETDLGITEM(IDC_NAME);
	if (m_IDCX_NAME.m_hWnd)
		m_IDCX_NAME.GetWindowText(buffer);
	else
		buffer = editbox->GetCaption();
	if (buffer.GetLength() <= (PLAYERNAMELEN - 1))
	{
		strcpy(_DPlay.PlayerName,buffer);
		strcpy(MMC.PlayerName,buffer);

	}
	if (m_IDCX_GAME_TITLE.m_hWnd)
	{
		m_IDCX_GAME_TITLE.GetWindowText(buffer);
		strcpy(_DPlay.SessionName,buffer);
	}
	else
	{
		editbox=GETDLGITEM(IDC_GAME_TITLE);
		buffer = editbox->GetCaption();
		if (buffer.GetLength() <= (SESSIONNAMELEN - 1))
			strcpy(_DPlay.SessionName,buffer);
	}
	if (m_IDCX_PLAYERCHAT.m_hWnd)
	{
		m_IDCX_PLAYERCHAT.GetWindowText(buffer);
		strcpy(_DPlay.Password,buffer);
	}
	else
	{
		editbox=GETDLGITEM(IDC_PLAYERCHAT);
		buffer = editbox->GetCaption();
		if (buffer.GetLength() <= (PASSWORDNAMELEN - 1))
			strcpy(_DPlay.Password,buffer);
		else
		{
			strncpy(_DPlay.Password,buffer,10);
			_DPlay.Password[10]='\0';
		}
	}
//		strcpy(_DPlay.Password,buffer);

// put password in save game

//	if (_DPlay.UIPlayerType==PLAYER_HOST)
//		strcpy(Save_Data.CommsPassword,_DPlay.Password);
//		strcpy(MMC.CommsPassword,_DPlay.Password);
		

	CRCombo* combo;
	combo=GETDLGITEM(IDC_GAME_TITLECOMBO);
	int index = combo->GetIndex();
	if (_DPlay.GameType == DEATHMATCH)
	{
		strncpy(_DPlay.GameName,RESLIST(DEATHMATCH0, index),59);
		_DPlay.GameName[59]=NULL;
		CSQuick1::quickdef.MakeDeathMatchMission(index);
	}
	else if (_DPlay.GameType == TEAMPLAY)
	{
		strncpy(_DPlay.GameName,RESLIST(TEAMPLAY0, index),59);
		_DPlay.GameName[59]=NULL;
		CSQuick1::quickdef.MakeTeamPlayMission(index);

	}
//DeadCode AMM 05May99 	else if (_DPlay.GameType == COMMSCAMPAIGN)
//DeadCode AMM 05May99 	{
//DeadCode AMM 05May99 		strncpy(_DPlay.GameName,RESLIST(SCAMPAIGNSELECT1, index),59);
//DeadCode AMM 05May99 		_DPlay.GameName[59]=NULL;
//DeadCode AMM 05May99 	}
//	else
//		strcpy(_DPlay.GameName,"");

	radiobox=GETDLGITEM(IDC_RRADIO_SELECTSIDE);
	selection=radiobox->GetCurrentSelection();

	switch (selection)
	{
	case 0:
		_DPlay.Side=TRUE;
		break;

	case 1:
		_DPlay.Side=FALSE;
		break;

	default:   
		_DPlay.Side=TRUE;
		break;

	}

	_DPlay.SideSelected=true;

	if (_DPlay.GameType==DEATHMATCH)
		_DPlay.Side=TRUE;

	_DPlay.GameIndex=index;

	combo=GETDLGITEM(IDC_DATARATE);
	index = combo->GetIndex();

	_DPlay.RateDivider=6-index;

	if (_DPlay.RateDivider<2)
		_DPlay.RateDivider=2;
	else if (_DPlay.RateDivider>6)
		_DPlay.RateDivider=6;
}

void CLockerRoom::OnDestroy() 
{
	UpDateDPlay();






//	strcpy(&_DPlay.GameName[0],"deathmatch arena");
	CDialog::OnDestroy();

}

void CLockerRoom::OnSelectedRradioGametype(long ButtonNum) 
{
	if (_DPlay.UIPlayerType==PLAYER_HOST)
	{
		_DPlay.GameType = (GameTypes)ButtonNum;	
		RedrawSide();
		RedrawCombo();
		FullPanel()->ResetLoadGameOption();						//JIM 12Jan99
	}
}

void CLockerRoom::OnClickedPilotedflag() 
{
	UpDateDPlay();
		Bool res;

	if (_DPlay.UIPlayerType==PLAYER_GUEST)
	{	 
//		res=_DPlay.UINewPlayer(&_DPlay.PlayerName[0],&_DPlay.SessionName[0]);
		
//		if (res)
		{
			_DPlay.SendUpdateToVisitorsBook(&_DPlay.PlayerName[0],FALSE);
		}
//		else
//		{
//			MessageBox("Could not create session or player","Warning",MB_OK);
//		}

//		_DPlay.DestroyAndClose(_DPlay.myDPlayID);
	}


	
}

void CLockerRoom::OnTextChangedName(LPTSTR text) 
{
	// TODO: Add your control notification handler code here
//	CString	buffer,buffer2;
//	CREdit* editbox;
//	editbox=GETDLGITEM(IDC_NAME);
//	buffer = editbox->GetCaption();
//	buffer2 = buffer.GetBufferSetLength(PLAYERNAMELEN-1);	
//	editbox->SetWindowText(buffer);
	trunc(text,PLAYERNAMELEN - 1);	
	
}

void CLockerRoom::OnTextChangedGameTitle(LPTSTR text) 
{
	trunc(text,SESSIONNAMELEN - 1);	
	
}

void CLockerRoom::OnTextChangedPlayerchat(LPTSTR text) 
{
	 	trunc(text,PASSWORDNAMELEN -1);
}

void CLockerRoom::OnUpdateGameTitle() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function to send the EM_SETEVENTMASK message to the control
	// with the ENM_UPDATE flag ORed into the lParam mask.
	
	// TODO: Add your control notification handler code here
	
}

void CLockerRoom::OnUpdateName() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function to send the EM_SETEVENTMASK message to the control
	// with the ENM_UPDATE flag ORed into the lParam mask.
	
	// TODO: Add your control notification handler code here
	
}

void CLockerRoom::OnUpdatePlayerchat() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function to send the EM_SETEVENTMASK message to the control
	// with the ENM_UPDATE flag ORed into the lParam mask.
	
	// TODO: Add your control notification handler code here
	
}
