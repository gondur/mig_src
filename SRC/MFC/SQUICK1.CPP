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

// SQuick1.cpp : implementation file
//

#include "stdafx.h"
//#include "mig.h"
//#include "SQuick1.h"
#include	"mathasm.h"
#include	"bitfield.h"
#include "FullPane.h"
#include "RRadio.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#ifndef THIS_FILE_DEFINED
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif

/////////////////////////////////////////////////////////////////////////////
// CSQuick1 dialog
typedef	 QuickFields	Q;
typedef	 QuickFields::QFD	QFD;
//QuickDef	CSQuick1::quickdef=
//{
//	{	{	{	{1,4,0,20000,IDS_SDETAIL4}	}	},
//		{	{	{9,2,0,20000,IDS_SDETAIL5,Q::QFD_MIG_PLAYER_ONLY},
//				{10,3,0,4000,IDS_SDETAIL6,Q::QFD_MIG_PLAYER_ONLY}	},
//			{	{9,2,0,5000,IDS_SDETAIL7,Q::QFD_MIG_PLAYER_ONLY},
//				{10,1,0,6000,IDS_SDETAIL8,Q::QFD_MIG_PLAYER_ONLY}	}	}	},
//	0,0,0,0,
//	0,0,0,0,
//	{ IDS_BRIDGE,IDS_SUPPLYPOINT,IDS_AIRFIELD,IDS_AIRFIELD	},
//	{	{UID_Null,UID_Null,UID_Null,UID_Null},
//		{UID_Null,UID_Null,UID_Null,UID_Null},
//		{UID_Null,UID_Null,UID_Null,UID_Null},
//		{UID_Null,UID_Null,UID_Null,UID_Null}	},
//	UID_Null
//};
#ifndef QFDFIELD
#define QFDFIELD
MAKEFIELD(QFD,0,Q::QFD_LAST);
#endif

QFDField	CSQuick1::nonplayer;
CSQuick1::CSQuick1(CWnd* pParent /*=NULL*/)
	: RowanDialog(CSQuick1::IDD, pParent)
{
	wassingle=false;
	if (currquickmiss==-1)
	{
//done in SetQuickState		Miss_Man.currcampaignnum = MissMan::SCRAMBLECAMPAIGN;		//RDH 16Apr96
//		Miss_Man.camp = Miss_Man.campaigntable[MissMan::SCRAMBLECAMPAIGN];

// done elsewhere AMM 24Nov98
//		MMC.Sky.SetMissionConditions ();

		currquickmiss=0;
		quickdef=quickmissions[currquickmiss];
	}
	Todays_Packages[0].packagetarget=UID_NULL;	//flag that there are no packages!
	//{{AFX_DATA_INIT(CSQuick1)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	quickdef.parent=this;
	nonplayer=0;
	nonplayer	|=Q::QFD_BOMBER_AUTO_ONLY;
	nonplayer	|=Q::QFD_MIG_AUTO_ONLY;
	nonplayer	|=Q::QFD_FIXED_AUTO;
	nonplayer	|=Q::QFD_FIXED_NUM_AUTO;
	nonplayer	|=Q::QFD_BOMBER_PLAYER_AUTO_IS_AUTO;
	nonplayer	|=Q::QFD_MIG_PLAYER_AUTO_IS_AUTO;
}

void CSQuick1::MakeFlightCombo()
{
  CRCombo* combo;
  CRCombo* combo2;
  combo=GETDLGITEM(IDC_FLIGHTNUM);
  combo2 = GETDLGITEM(IDC_ELTNUM);
  CRStatic*   s=GETDLGITEM(IDC_RSTATICCTRL4);

//DeadCode AMM 14Oct98   if (_DPlay.CurrPlayers != 0)
  if (RFullPanelDial::incomms)									//AMM 14Oct98
  {
	combo->ShowWindow(SW_HIDE);
	combo2->ShowWindow(SW_HIDE);
	s->ShowWindow(SW_HIDE);
  }else
  {
  	combo->ShowWindow(SW_SHOW);
  	combo2->ShowWindow(SW_SHOW);
  	s->ShowWindow(SW_SHOW);


	//cockup recovery. If current player position illegal find a legal one!
	if (	nonplayer[quickdef.line[quickdef.plside][quickdef.plwave][quickdef.plgrp].Duty()]
		||	quickdef.line[quickdef.plside][quickdef.plwave][quickdef.plgrp].flights==0
		)
	{	//find lowest numbered group on this side first, but then that side
		bool gotone=false;
		for (int pls=1-quickdef.plside,tries=2;tries--;pls=1-pls)
			for (int w=8;w>=0;w--)
				for (int g=2;g>=0;g--)
					if (!gotone)
					if (quickdef.line[pls][w][g].flights && 
						!nonplayer[quickdef.line[pls][w][g].Duty()])
					{	//if zero flights then not flyable, even if it 'exists'
						quickdef.plside=pls;
						quickdef.plwave=w;
						quickdef.plgrp=g;
						gotone=true;
					}
		if (!gotone)
			INT3;
	}
	if (quickdef.plac/4>=quickdef.line[quickdef.plside][quickdef.plwave][quickdef.plgrp].flights)
	{
		quickdef.plac%=4;
		quickdef.plac+=4*quickdef.line[quickdef.plside][quickdef.plwave][quickdef.plgrp].flights;
		quickdef.plac-=4;
	}

	//fills IDC_FLIGHTNUM & selects it & selects IDC_ELTNUM;

	combo->Clear();
	int line=0;
	int pls=quickdef.plside;
	int ens=1-pls;
	//find an enemy flyable squadron...
	bool gotone=false;
	int w,g;
		for (w=7;w>=0;w--)
			for (g=2;g>=0;g--)
				if (!gotone)
				if (quickdef.line[ens][w][g].flights && 
					!nonplayer[quickdef.line[ens][w][g].Duty()])
				{	//if zero flights then not flyable, even if it 'exists'
					flightlines[0][0]=ens;
					flightlines[0][1]=w;
					flightlines[0][2]=g;
					flightlines[0][3]=-1;
					gotone=true;
				}
	if (gotone)
	{
	   if (ens)
			combo->AddString(RESSTRING(RED));
	   else
			combo->AddString(RESSTRING(UN));
	   line++;
	}
		
	CString myside=pls?RESSTRING(RED):RESSTRING(UN);
	for (w=0;w<8;w++)
		for(g=0;g<3;g++)
			if (quickdef.line[pls][w][g].flights && !nonplayer[quickdef.line[pls][w][g].Duty()])
				if (w!=quickdef.plwave || g!=quickdef.plgrp)
				{
					char buffer[30];
					combo->AddString(CSprintf("%s %s",myside,LoadResString(quickdef.line[pls][w][g].descID)));
					flightlines[line][0]=pls;
					flightlines[line][1]=w;
					flightlines[line][2]=g;
					flightlines[line][3]=-1;
					line++;
				}
				else
				{
					int plflst=line;
					int m=quickdef.line[pls][w][g].flights;
					for (int f=0;f<m;f++)
					{
						combo->AddString(CSprintf("%s %s %s %i",myside,LoadResString(quickdef.line[pls][w][g].descID),RESSTRING(FLIGHT),f+1));
						flightlines[line][0]=pls;
						flightlines[line][1]=w;
						flightlines[line][2]=g;
						flightlines[line][3]=f;
						line++;
					}
					combo->SetIndex(plflst+quickdef.plac/4);
				}
	combo=GETDLGITEM(IDC_ELTNUM);
///    bool wassingle=(combo->GetListboxLength()==1);
	bool nowsingle=((quickdef.line[pls][quickdef.plwave][quickdef.plgrp].duty & QuickFields::QFD_MASK)>=QuickFields::QFD_LONE_PLAYER);
	if (wassingle!=nowsingle)
		if (nowsingle)
		{
			quickdef.plac &=-4;
			combo->Clear()->RESCOMBO(ELTPOS_0,1);
			wassingle=true;
		}
		else
		{
			combo->Clear()->RESCOMBO(ELTPOS_0,4);
			wassingle=false;
		}
	GETDLGITEM(IDC_ELTNUM)->SetIndex(quickdef.plac%4);

  }
}
void CSQuick1::DoDataExchange(CDataExchange* pDX)
{
	quickdef.parent=this;
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSQuick1)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	DDX_Control(pDX,IDC_SDETAIL1,m_IDC_SDETAIL1);
	DDX_Control(pDX,IDC_RSTATICCTRL4,m_IDC_RSTATICCTRL4);
	DDX_Control(pDX,IDC_SDETAIL2,m_IDC_SDETAIL2);
	DDX_Control(pDX,IDC_RSTATICCTRL24,m_IDC_RSTATICCTRL24);
	DDX_Control(pDX,IDC_RSTATICCTRL7,m_IDC_RSTATICCTRL7);
	DDX_Control(pDX,IDC_MISSLISTS,m_IDC_MISSLISTS);
	DDX_Control(pDX,IDC_FLIGHTNUM,m_IDC_FLIGHTNUM);
	DDX_Control(pDX,IDC_ELTNUM,m_IDC_ELTNUM);
	DDX_Control(pDX,IDC_CLOUD,m_IDC_CLOUD);
	DDX_Control(pDX,IDC_WEATHER,m_IDC_WEATHER);
	DDX_Control(pDX,IDC_TARGTYPE,m_IDC_TARGTYPE);
	DDX_Control(pDX,IDC_TARGNAME,m_IDC_TARGNAME);
	DDX_Control(pDX,IDC_RRADIO,m_IDC_RRADIO);
	//}}AFX_DATA_MAP

}

BOOL CSQuick1::OnInitDialog() 
{
	CDialog::OnInitDialog();
	// TODO: Add extra initialization here

	CRRadio* pradio;
	CString string;

	m_IDC_MISSLISTS.SetCircularStyle(TRUE);
	m_IDC_FLIGHTNUM.SetCircularStyle(TRUE);
	m_IDC_ELTNUM.SetCircularStyle(TRUE);
	m_IDC_TARGTYPE.SetCircularStyle(TRUE);
	m_IDC_TARGNAME.SetCircularStyle(TRUE);



	pradio=GETDLGITEM(IDC_RRADIO);
	string.LoadString(IDS_SCENARIO);
	pradio->AddButton(string);
	string.LoadString(IDS_UN);
	pradio->AddButton(string);
	string.LoadString(IDS_RED);
	pradio->AddButton(string);

	CRCombo* combo;
	combo=GETDLGITEM(IDC_MISSLISTS);
//	combo->RESCOMBO(QUICK_1,20)->SetIndex(currquickmiss);
//DeadCode AMM 12May99 	char i = 0;
//DeadCode AMM 12May99 	while (quickmissions[i].missionname !=NULL)
//DeadCode AMM 12May99 	{
//DeadCode AMM 12May99 		combo->AddString(LoadResString(quickmissions[i].missionname));
//DeadCode AMM 12May99 		i++;
//DeadCode AMM 12May99 	}
//DeadCode AMM 12May99 	combo->SetIndex(currquickmiss);
	char i = 0,j=0;
	while (quickmissions[i].missionname !=NULL)
	{
		bool	missallowed=false;	//incomms should set false
		if (!RFullPanelDial::incomms)							//AMM 12May99
			missallowed=true;									//AMM 12May99
		if (!missallowed)
		{
			missallowed=true;
			for (int s=0;s<2;s++)
				for (int w=0;w<8;w++)
					for (int g=0;g<4;g++)
						if ((quickmissions[i].line[s][w][g].duty & (QuickFields::QFD_MASK-1))==QuickFields::QFD_LONE_PLAYER)
							missallowed=false;
		}
		if (missallowed)
		{
			misslistbackindex[i]=j;
			misslistindex[j]=i;
			j++;
			combo->AddString(LoadResString(quickmissions[i].missionname));
		}
		else
			misslistbackindex[i]=255;
		i++;
	}
	if (misslistbackindex[currquickmiss]!=255)
		combo->SetIndex(misslistbackindex[currquickmiss]);
	else
	{
		currquickmiss=misslistindex[0];
		quickdef=quickmissions[currquickmiss];
		combo->SetIndex(0);
	}
	combo=GETDLGITEM(IDC_ELTNUM);
	combo->RESCOMBO(ELTPOS_0,4);
	wassingle=false;
	ReinitCombo();

//	if (RFullPanelDial::incomms)
	if (_DPlay.PlayerCreated)
	{
		_DPlay.SendInMissionBriefMessage();
		DPlay::H2H_Player[_DPlay.mySlot].status=CPS_MISSIONBRIEF;
	}

	 missbrief_timer=SetTimer(TIMER_MISSIONBRIEF,0,NULL); 

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE

}
void	CSQuick1::ReinitCombo()
{
	quickdef.parent=this;
	MakeFlightCombo();
 	CRRadio*	pradio=GETDLGITEM(IDC_RRADIO);
	pradio->SetCurrentSelection(0);

	CRCombo* combo;
	targtype=0,targentry=0;
	for (int t=0;t<4;t++)
		for (int e=0;e<4;e++)
			if(quickdef.targets[t][e]==quickdef.target)
				targtype=t,targentry=e;
	combo=GETDLGITEM(IDC_TARGTYPE);
	combo->Clear();
	combo->AddString(LoadResString(quickdef.targtypeIDs[0]));
	if (quickdef.targtypeIDs[1])
		combo->AddString(LoadResString(quickdef.targtypeIDs[1]));
	if (quickdef.targtypeIDs[2])
		combo->AddString(LoadResString(quickdef.targtypeIDs[2]));
	if (quickdef.targtypeIDs[3])
		combo->AddString(LoadResString(quickdef.targtypeIDs[3]));
	combo->SetIndex(targtype);
	combo=GETDLGITEM(IDC_TARGNAME);

	//may pull this off as subroutine:
	combo->Clear();
	combo->AddString(GetTargName(quickdef.targets[targtype][0]));
	if (quickdef.targets[targtype][1])
	combo->AddString(GetTargName(quickdef.targets[targtype][1]));
	if (quickdef.targets[targtype][2])
		combo->AddString(GetTargName(quickdef.targets[targtype][2]));
	if (quickdef.targets[targtype][3])
		combo->AddString(GetTargName(quickdef.targets[targtype][3]));
	combo->SetIndex(targentry);

//	combo=GETDLGITEM(IDC_WEATHER);
//	combo->Clear()->RESCOMBO(WEATHER_CLEAR,3)->SetIndex(quickdef.weather);
//	combo=GetDlgItem(IDC_CLOUD);
//	combo->Clear()->MakeNumList(35,5000,1000)->SetIndex(quickdef.cloudbaseK);
	
}


BEGIN_MESSAGE_MAP(CSQuick1, CDialog)
	//{{AFX_MSG_MAP(CSQuick1)
	ON_WM_CLOSE()
	ON_WM_DESTROY()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSQuick1 message handlers

BEGIN_EVENTSINK_MAP(CSQuick1, CDialog)
    //{{AFX_EVENTSINK_MAP(CSQuick1)
	ON_EVENT(CSQuick1, IDC_MISSLISTS, 1 /* TextChanged */, OnTextChangedMisslists, VTS_BSTR)
	ON_EVENT(CSQuick1, IDC_FLIGHTNUM, 1 /* TextChanged */, OnTextChangedFlightnum, VTS_BSTR)
	ON_EVENT(CSQuick1, IDC_TARGTYPE, 1 /* TextChanged */, OnTextChangedTargtype, VTS_BSTR)
	ON_EVENT(CSQuick1, IDC_TARGNAME, 1 /* TextChanged */, OnTextChangedTargname, VTS_BSTR)
	ON_EVENT(CSQuick1, IDC_ELTNUM, 1 /* TextChanged */, OnTextChangedEltnum, VTS_BSTR)
	ON_EVENT(CSQuick1, IDC_RRADIO, 1 /* Selected */, OnSelectedRradio, VTS_I4)
	//}}AFX_EVENTSINK_MAP
//	ON_EVENT(CSQuick1, IDC_WEATHER, 1 /* TextChanged */, OnTextChangedWeather, VTS_BSTR)
//	ON_EVENT(CSQuick1, IDC_CLOUD, 1 /* TextChanged */, OnTextChangedCloud, VTS_BSTR)
END_EVENTSINK_MAP()

void CSQuick1::OnTextChangedMisslists(LPCTSTR text) 
{
	// TODO: Add your control notification handler code here
	//actually need to shut everything down....
//DeadCode DAW 18May99 	currquickmiss=GETDLGITEM(IDC_MISSLISTS)->GetIndex();
	if (!RFullPanelDial::incomms)								//AMM 18May99
		currquickmiss=GETDLGITEM(IDC_MISSLISTS)->GetIndex();
	else														//AMM 18May99
	{															//AMM 18May99
		int i=0,j=0,index=GETDLGITEM(IDC_MISSLISTS)->GetIndex();

		while (quickmissions[i].missionname !=NULL)
		{
			bool	missallowed;

			missallowed=true;
			for (int s=0;s<2;s++)
				for (int w=0;w<8;w++)
					for (int g=0;g<4;g++)
						if ((quickmissions[i].line[s][w][g].duty & (QuickFields::QFD_MASK-1))==QuickFields::QFD_LONE_PLAYER)
							missallowed=false;

			if (missallowed)
			{
				misslistbackindex[i]=j;
				misslistindex[j]=i;
				j++;
				if (!index)
					break;
				index--;
			}
			else
				misslistbackindex[i]=255;
			i++;
		}
		currquickmiss=i;
	}															
	quickdef=quickmissions[currquickmiss];
//DeadCode JIM 12Jan99 	RFullPanelDial* fullscreen=(RFullPanelDial*)GetParent();
	ReinitCombo();
	FullPanel()->QuickMissionDesc();							//JIM 12Jan99
//	DestroyPanel();
//  if (_DPlay.CurrPlayers == 0)
//		fullscreen->LaunchScreen(&fullscreen->quickmission);
//	else
//		fullscreen->LaunchScreen(&fullscreen->commsquick);
//DeadCode AMM 14Oct98   if (_DPlay.CurrPlayers == 0)
//  if (!RFullPanelDial::incomms)									//AMM 14Oct98
//		fullscreen->LaunchScreen(&fullscreen->quickmission);
//	else
//		fullscreen->LaunchScreen(&fullscreen->commsquick);
}

void CSQuick1::OnTextChangedFlightnum(LPCTSTR text) 
{
	int index=GETDLGITEM(IDC_FLIGHTNUM)->GetIndex();
	//ok... this is easy, now... index into flightlines!
	if (	flightlines[index][0]!=quickdef.plside
		||	flightlines[index][1]!=quickdef.plwave
		||	flightlines[index][2]!=quickdef.plgrp
		)
	{
		quickdef.line[quickdef.plside][quickdef.plwave][quickdef.plgrp].dialog->SetIconPressed(false);
		quickdef.plside=flightlines[index][0];
		quickdef.plwave=flightlines[index][1];
		quickdef.plgrp=flightlines[index][2];
		quickdef.line[quickdef.plside][quickdef.plwave][quickdef.plgrp].dialog->SetIconPressed(true);
		if (quickdef.plac>=quickdef.line[quickdef.plside][quickdef.plwave][quickdef.plgrp].flights*4)
			quickdef.plac=quickdef.line[quickdef.plside][quickdef.plwave][quickdef.plgrp].flights*4
							-4+(quickdef.plac%4);
		MakeFlightCombo();
	}
	else
	{
		quickdef.plac=(quickdef.plac%4)+4*(flightlines[index][3]);
	}
}

void CSQuick1::OnTextChangedTargtype(LPCTSTR text) 
{
	// TODO: Add your control notification handler code here
	targtype=GETDLGITEM(IDC_TARGTYPE)->GetIndex();
	targentry=0;
	quickdef.target=quickdef.targets[targtype][targentry];
	CRCombo* combo;
	(combo=GETDLGITEM(IDC_TARGNAME))->Clear();
	//may pull this off as subroutine:
	combo->AddString(GetTargName(quickdef.targets[targtype][0]));
	if (quickdef.targets[targtype][1])
	combo->AddString(GetTargName(quickdef.targets[targtype][1]));
	if (quickdef.targets[targtype][2])
		combo->AddString(GetTargName(quickdef.targets[targtype][2]));
	if (quickdef.targets[targtype][3])
		combo->AddString(GetTargName(quickdef.targets[targtype][3]));
	combo->SetIndex(targentry);
}

void CSQuick1::OnTextChangedTargname(LPCTSTR text) 
{
	// TODO: Add your control notification handler code here
	targentry=GETDLGITEM(IDC_TARGNAME)->GetIndex();
	quickdef.target=quickdef.targets[targtype][targentry];
	
}

//void CSQuick1::OnTextChangedWeather(LPCTSTR text) 
//{
//	// TODO: Add your control notification handler code here
//	quickdef.weather=CRComboPtr(GetDlgItem(IDC_WEATHER))->GetIndex();
//
//}

//void CSQuick1::OnTextChangedCloud(LPCTSTR text) 
//{
//	// TODO: Add your control notification handler code here
//	quickdef.cloudbaseK=CRComboPtr(GetDlgItem(IDC_CLOUD))->GetIndex();
//	
//}

int		QuickDef::SpareFlights(int squad)
{
	int rv=4;
	int w,g;
	for (int s=0;s<2;s++)
		for (w=0;w<8;w++)
			for(g=0;g<3;g++)
				if (line[s][w][g].actype==squad)
					rv-=line[s][w][g].flights;
	return rv;
}

void	QuickDef::FixOtherLines(int squad)	  //IDS_TARGET
{
	int spares=SpareFlights(squad);
	int w,g;
	for (int s=0;s<2;s++)
		for (w=0;w<8;w++)
			for(g=0;g<3;g++)
/////				if (line[s][w][g].actype==squad)
					line[s][w][g].dialog->RecalcFlightsCombo(spares);
}		

void CSQuick1::OnTextChangedEltnum(LPCTSTR text) 
{

	// TODO: Add your control notification handler code here
	quickdef.plac=(quickdef.plac&-4)
					+GETDLGITEM(IDC_ELTNUM)->GetIndex();
	
}

void CSQuick1::OnClose() 
{
}

BOOL CSQuick1::DestroyWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	
// if in comms need to send an update saying that mission has changed	
	return CDialog::DestroyWindow();
}

void CSQuick1::OnDestroy() 
{
	CDialog::OnDestroy();
	
	//Calc ac type and player slot number
	//from quickdef.line[quickdef.plside][quickdef.plwave][quickdef.plgrp] &	 quickdef.plac
	//to MMC.	playersquadron,playeracnum;
	int plsquad=quickdef.line[quickdef.plside][quickdef.plwave][quickdef.plgrp].actype;
	int plind=quickdef.plac;
	int s = quickdef.plside;
	for (int w=0;w<quickdef.plwave;w++)
		for(int g=0;g<3;g++)
				if (quickdef.line[s][w][g].actype==plsquad)
					plind+=quickdef.line[s][w][g].flights*4;
	for(int g=0;g<quickdef.plgrp;g++)
		if (quickdef.line[s][w][g].actype==plsquad)
			plind+=quickdef.line[s][w][g].flights*4;

//DeadCode AMM 17Nov98  	if ( _DPlay.CurrPlayers == 0)
 	if ( !RFullPanelDial::incomms)								//JIM 12Jan99
	{
		MMC.playersquadron=plsquad;
		MMC.playeracnum=plind;
	}

	_DPlay.UpdateMission=TRUE;

	KillTimer(missbrief_timer);
}

void CSQuick1::OnSelectedRradio(long ButtonNum) 
{
	// TODO: Add your control notification handler code here
	switch (ButtonNum)
	{
	case 0:	FullPanel()->QuickMissionDesc();	break;
	case 1:	FullPanel()->QuickMissionBlue();	break;
	case 2:	FullPanel()->QuickMissionRed();	break;
	}
}

void CSQuick1::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	
	if (nIDEvent==missbrief_timer)
	{
		if (_DPlay.PlayerCreated)
		{
			_DPlay.UIUpdateMainSheet();
		}
	}

	CDialog::OnTimer(nIDEvent);
}
