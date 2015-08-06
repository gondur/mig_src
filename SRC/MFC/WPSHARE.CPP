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

// WPShare.cpp : implementation file
//

#include "stdafx.h"
#include "mig.h"
#include "WPShare.h"
#include "rlistbox.h"
#include	"bfnumber.h"
#include	"persons2.h"
#include "planetyp.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#ifndef THIS_FILE_DEFINED
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif

/////////////////////////////////////////////////////////////////////////////
// CWPShare dialog


CWPShare::CWPShare(int pack,int wave,int group, CWnd* pParent /*=NULL*/)
	: RowanDialog(CWPShare::IDD, pParent)
{
	SetProjSpecific(pack,wave,group);
	if (groupnum <0)
		groupnum = 0;
	wpdetail=NULL;
	wpbuttons = NULL;
	comboindex = 0;
	//{{AFX_DATA_INIT(CWPShare)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CWPShare::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWPShare)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	DDX_Control(pDX,IDC_WAYPOINTLIST,m_IDC_WAYPOINTLIST);
	DDX_Control(pDX,IDC_TYPE,m_IDC_TYPE);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CWPShare, CDialog)
	//{{AFX_MSG_MAP(CWPShare)
	ON_WM_SIZE()
	ON_WM_DESTROY()
	ON_MESSAGE( WM_SELECTTAB, OnSelectTab)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_EVENTSINK_MAP(CWPShare, CDialog)
    //{{AFX_EVENTSINK_MAP(WaypointButtons)
	ON_EVENT(CWPShare, IDC_WAYPOINTLIST, 1 /* Select */, OnSelectWaypointlist, VTS_I4 VTS_I4)
	ON_EVENT(CWPShare, IDC_DELETE, 1 /* Clicked */, OnDelete, VTS_NONE)
	ON_EVENT(CWPShare, IDC_INSERT, 1 /* Clicked */, OnInsert, VTS_NONE)
	ON_EVENT(CWPShare, IDC_MOVE, 1 /* Clicked */, OnMove, VTS_NONE)
	ON_EVENT(CWPShare, IDC_TYPE, 1 /* TextChanged */, OnTextChangedType, VTS_BSTR)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWPShare message handlers


BOOL CWPShare::OnInitDialog() 
{
	CDialog::OnInitDialog();
	// TODO: Add extra initialization here
	Todays_Packages[packnum].RecalcRoutePositions();
	
	//If curr package/wave is not this dialog's package/wave
	//then reset curr package/wave
	UniqueID wpuid = Todays_Packages[packnum].wave[wavenum].firstwp;
	UniqueID trgtuid = UID_NULL;
	while  (		(wpuid)
				&&	(wpuid != Todays_Packages.hiwp)
			)
	{
		info_waypoint* w=*Persons2::ConvertPtrUID(wpuid);
		if (Todays_Packages[packnum][wavenum].targettime == w->etas)
			trgtuid = wpuid;
		wpuid=w->nextwp;
	}
	if  (		(wpuid != Todays_Packages.hiwp)
			||	(wpuid == UID_NULL)
		)

		wpuid = trgtuid;
	RDialog::m_pView->SetHiLightInfo(packnum, wavenum, groupnum, wpuid);
//	RDialog::m_pView->m_mapdlg.ResetIcon(wpuid);




	
//	CRListBox* rlistbox=GetDlgItem(IDC_WAYPOINTLIST);

	FillComboBox();

	DisplayData();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CWPShare::FillComboBox()
{
   	CRCombo* combo;
	combo=GETDLGITEM(IDC_TYPE);

	combo->Clear();
	UniqueID u=Todays_Packages[packnum][wavenum].firstwp;
	info_airgrp* ag1=*Persons2::ConvertPtrUID(Todays_Packages[packnum][wavenum][1].uid);
	info_airgrp* ag2=*Persons2::ConvertPtrUID(Todays_Packages[packnum][wavenum][2].uid);


	int i;
	for (i = 0; i < 4; i++)
		combo->AddString(LoadResString(IDS_L_POSITION+i));

	combo->AddString(LoadResString(IDS_FUELLEFT) + ", " 
		+ LoadResString(Save_Data.mass.abbrtype) );

	if (ag1)
	{
		combo->AddString(LoadResString(IDS_AAAFUEL) + ", " 
			+ LoadResString(Save_Data.mass.abbrtype) );
		i++;
	}
	if (ag2)
	{
		combo->AddString(LoadResString(IDS_ESCORTFUEL)+ ", " 
			+ LoadResString(Save_Data.mass.abbrtype) );
		i++;
	}
	if (comboindex > i)
		comboindex = 0;
	combo->SetIndex(comboindex);
	  
}

void	CWPShare::DisplayData()
{

	UniqueID*	listptr=listentries;
	CRListBox* rlistbox=GETDLGITEM(IDC_WAYPOINTLIST);
	rlistbox->Clear();
	currrow=0;
	int row=0;
	int currtime = 0;
	int	fuel[3];
	if (Todays_Packages[packnum][wavenum][0].uid
		&& Todays_Packages[packnum][wavenum].firstwp)
	{
		rlistbox->AddColumn(100);
		rlistbox->AddColumn(20);
		UniqueID u=Todays_Packages[packnum][wavenum].firstwp;
		info_airgrp* ag[3];
		ag[0]=*Persons2::ConvertPtrUID(Todays_Packages[packnum][wavenum][0].uid);
		ag[1]=*Persons2::ConvertPtrUID(Todays_Packages[packnum][wavenum][1].uid);
		ag[2]=*Persons2::ConvertPtrUID(Todays_Packages[packnum][wavenum][2].uid);
		char buffer[30];
		*listptr++=UID_Null;


		int	currmainwp=1;char currsubwp='A';
		if (Todays_Packages[packnum][wavenum][0].takeoffAF == UID_Japan)
			sprintf(buffer,"%i. %s",currmainwp,RESSTRING(INTERMEDIATE));
		else
			sprintf(buffer,"%i. %s",currmainwp,RESLIST(MAIN_WP_GAP,currmainwp));
		rlistbox->AddString(buffer,0);

		Todays_Packages[packnum].CalcWPTimes(wavenum);
//		currtime=Todays_Packages[packnum][wavenum].starttime;

		int type;
		ClassPtr actype;
		int intfuel;
		for (int i =0; i < 3; i++)
		{
			if (ag[i])
			{
				fuel[i] = CWeapons::GetExtFuel(packnum,wavenum, i, 0);
				type=Persons3::Squad2Type(ag[i]->type);
				actype = Plane_Type_Translate[type][0];
				int intfuel = actype->maxintfuel*1000;   //0.01kg->g
				fuel[i] += intfuel;
				fuel[i] = fuel[i] - 15000000;//allowance for take-off and landing
	
			}
		}


		int g;
		if (comboindex == ESCORTFUEL)
			g = 2;
		else if (comboindex == AAAFUEL)
		{ 	
			if (ag[1])
				g = 1;
			else
				g = 2;
		}else
			g = 0;

//------------------------------------------------------------------------------------
//take off point data
		switch	(comboindex)
		{
			case L_POSITION:
			{
				if (Todays_Packages[packnum][wavenum][0].takeoffAF != UID_NULL)
				{
					rlistbox->AddString(GetTargName(Todays_Packages[packnum][wavenum][0].takeoffAF),1);
				}
				break;
			}
			case L_ALTITUDE:
			{
				rlistbox->AddString("",1);
				break;
			}
			case L_ETAREL:
			case L_ETA:
			{
				int t=Todays_Packages[packnum][wavenum][0].takeofftime/60;
				if (comboindex == L_ETA)
				{
					sprintf(buffer,"%02i:%02i",t/60,t%60);
					rlistbox->AddString(buffer,1);
				}else
				{
					int targtime=Todays_Packages[packnum][wavenum].targettime/60;
					t-=targtime;
					if (t>=0)
						sprintf(buffer,"+%02i:%02i",t/60,t%60);
					else
						sprintf(buffer,"-%02i:%02i",-t/60,-t%60);
					rlistbox->AddString(buffer,1);
				}
				break;
			}
			case FUELLEFT:
			case AAAFUEL:
			case ESCORTFUEL:
			{
				if (Todays_Packages[packnum][wavenum].group[g].squadron < SQ_B_NONFLYABLE)
					rlistbox->AddString(CSprintf("%5i",fuel[g]/ (100*Save_Data.mass.gm)),1);
				else
					rlistbox->AddString(RESSTRING(NA),1);
				break;
			}
		}

//------------------------------------------------------------------------------------
//all other waypoints


		COORDS3D* last;
		COORDS3D* lastwp[3];
		COORDS3D* home;
		info_waypoint* wp;
		last=&Persons2::ConvertPtrUID(Todays_Packages[packnum][wavenum][0].takeoffAF)->World;
		home=last;
		wp=*Persons2::ConvertPtrUID(u);

		while (u)
		{
			if (wp->uid!=GOT_UNDEFINED_VAL)
			{
				currmainwp+=1;currsubwp='A';

				sprintf(buffer,"%i. %s",currmainwp,RESLIST(MAIN_WP_GAP,currmainwp));
			}
			else
			{
				currsubwp++;		//say which groups processed by this sub-waypoint
				sprintf(buffer,"%i. %c",currmainwp,currsubwp-1);
			}
			SWord StoresDrag = 0;														//CSB 17/06/99	
			if  (		(currmainwp <= 4)
					&&	(Save_Data.flightdifficulty [FD_STORESWEIGHTDRAG])							
				)
			{// on way in and we want to account for stores drag
				StoresDrag = Todays_Packages[packnum][wavenum][0].GetStoresDrag(0);
			}
	
			if (currmainwp!=4 || currsubwp=='A')
			{	//4A filled in, other 4 (ie 4B) not 
				*listptr++=u;
				row++;
				rlistbox->AddString(buffer,0);
				if (u == Todays_Packages.hiwp)
					currrow=row;

				switch	(comboindex)
				{
					case L_POSITION:
					{
						CString string, string2;
						string = (GetAreaName(wp));
						if (string.GetLength() > 0)
						{
							string.TrimLeft();
							string2 = string;
							string2.MakeUpper();
							string.SetAt(0, string2.GetAt(0));
							rlistbox->AddString(string,1);
						}
						break;
					}
					case L_ALTITUDE:
					{
						int alt = (wp->World.Y*10)/Save_Data.alt.mediummm;
						alt = 100*((alt + 50)/100);
						sprintf(buffer,"%i%s",alt,LoadResString(Save_Data.alt.mediumabbr));
						rlistbox->AddString(buffer,1);
						break;
					}
					case L_ETAREL:
					case L_ETA:
					{
						int t=wp->etas/60;
						currtime = wp->etas;
						if (comboindex == L_ETA)
						{
							sprintf(buffer,"%02i:%02i",t/60,t%60);
							rlistbox->AddString(buffer,1);
						}else
						{
							int targtime=Todays_Packages[packnum][wavenum].targettime/60;
							t-=targtime;
							if (t>=0)
								sprintf(buffer,"+%02i:%02i",t/60,t%60);
							else
								sprintf(buffer,"-%02i:%02i",-t/60,-t%60);
							rlistbox->AddString(buffer,1);
						}
						break;
					}
					case FUELLEFT:
					case AAAFUEL:
					case ESCORTFUEL:
					{
						fuel[g] -= Profile::CalcFuel(last,&wp->World,ag[0]->type,ag[g]->type, StoresDrag);	 //CSB 18/06/99
						if (Todays_Packages[packnum][wavenum].group[g].squadron < SQ_B_NONFLYABLE)
							rlistbox->AddString(CSprintf("%5i",fuel[g]/ (100*Save_Data.mass.gm)),1);
						else
							rlistbox->AddString(RESSTRING(NA),1);
	
						break;
					}
				}
			}else
			{//target area waypoints
				switch	(comboindex)
				{
					case FUELLEFT:
					case AAAFUEL:
					case ESCORTFUEL:
					{
						if  (		(wp->applygroup == g)
								&&	(!Profile::NonLeadElementSet(wp->applyflight, wp->applyelt))
							)								
							fuel[g] -=Profile::CalcFuel(last,&wp->World,ag[g]->type,ag[g]->type, StoresDrag);	 //CSB 18/06/99);
						break;
					}
				}
			}
			last=&wp->World;
			u=wp->nextwp;
			if (u)
			{
				wp=*Persons2::ConvertPtrUID(u);
				while	(	(		(Profile::NonLeadElementSet(wp->applyflight, wp->applyelt))
								||	(		(wp->applygroup!= ENABLE_COMPLEX_VAL)
										&&	(wp->applygroup != g)
									)
							)
							&&	(u)
						)
				{
					u=wp->nextwp;
					if (u)
						wp=*Persons2::ConvertPtrUID(u);
					
				}
			}

			
		}
		currmainwp+=1;
//------------------------------------------------------------------------------------
//Landing
		sprintf(buffer,"%i. %s",currmainwp,RESLIST(MAIN_WP_GAP,currmainwp));
		rlistbox->AddString(buffer,0);

		switch	(comboindex)
		{
			case L_POSITION:
			{
				if (Todays_Packages[packnum][wavenum][0].takeoffAF != UID_NULL)
				{
					rlistbox->AddString(GetTargName(Todays_Packages[packnum][wavenum][0].takeoffAF),1);
				}
				break;
			}
			case L_ALTITUDE:
			{
				rlistbox->AddString("",1);
				break;
			}
			case L_ETAREL:
			case L_ETA:
			{
				int t=(currtime + Profile::CalcTime(last,home,ag[0]->type,ag[0]->type,0))/60;	//no stores drag on landing
				if (comboindex == L_ETA)
				{
					sprintf(buffer,"%02i:%02i",t/60,t%60);
					rlistbox->AddString(buffer,1);
				}else
				{
					int targtime=Todays_Packages[packnum][wavenum].targettime/60;
					t-=targtime;
					if (t>0)
						sprintf(buffer,"+%02i:%02i",t/60,t%60);
					else
						sprintf(buffer,"-%02i:%02i",-t/60,-t%60);
					rlistbox->AddString(buffer,1);
				}
				break;
			}
					case FUELLEFT:
					case AAAFUEL:
					case ESCORTFUEL:
					{
						fuel[g] -= Profile::CalcFuel(last,home,ag[0]->type,ag[g]->type,0);				//no stores drag CSB 18/06/99
						if (Todays_Packages[packnum][wavenum].group[g].squadron < SQ_B_NONFLYABLE)
							rlistbox->AddString(CSprintf("%5i",fuel[g]/ (100*Save_Data.mass.gm)),1);
						else
							rlistbox->AddString(RESSTRING(NA),1);
	
						break;
					}
		}
		listfull= (listptr==listentries+LISTMAXSIZE);
 		while (listptr!=listentries+LISTMAXSIZE+1)
 			*listptr++=UID_Null;

	}
	else
	{
		rlistbox->AddString(RESSTRING(OFFDUTY),0);
	}
	rlistbox->SetHilightCol(0);
	if (currrow!=0)
	{
		RefreshDetail(listentries[currrow]);
		rlistbox->SetHilightRow(currrow);
	}
	SetButtons(currrow);

}


/*rewritten 10/2/99
void	CWPShare::DisplayData()
{

	UniqueID*	listptr=listentries;
	CRListBox* rlistbox=GETDLGITEM(IDC_WAYPOINTLIST);
	rlistbox->Clear();
	currrow=0;
	int row=0;
	int currtime = 0;
	int	fuel[3];

	if (Todays_Packages[packnum][wavenum][0].uid
		&& Todays_Packages[packnum][wavenum].firstwp)
	{
		rlistbox->AddColumn(100);
		rlistbox->AddColumn(20);
		UniqueID u=Todays_Packages[packnum][wavenum].firstwp;
		info_airgrp* ag[3];
		ag[0]=*Persons2::ConvertPtrUID(Todays_Packages[packnum][wavenum][0].uid);
		ag[1]=*Persons2::ConvertPtrUID(Todays_Packages[packnum][wavenum][1].uid);
		ag[2]=*Persons2::ConvertPtrUID(Todays_Packages[packnum][wavenum][2].uid);
		char buffer[30];
		*listptr++=UID_Null;


		int	currmainwp=1;char currsubwp='A';
		sprintf(buffer,"%i. %s",currmainwp,RESLIST(MAIN_WP_GAP,currmainwp));
		rlistbox->AddString(buffer,0);

		Todays_Packages[packnum].CalcWPTimes(wavenum);
//		currtime=Todays_Packages[packnum][wavenum].starttime;

		int type;
		ClassPtr actype;
		int intfuel;
		for (int i =0; i < 3; i++)
		{
			if (ag[i])
			{
				fuel[i] = CWeapons::GetExtFuel(packnum,wavenum, i, 0);
				type=Persons3::Squad2Type(ag[i]->type);
				actype = Plane_Type_Translate[type][0];
				int intfuel = actype->maxintfuel*1000;   //0.01kg->g
				fuel[i] += intfuel;
			}
		}

		int lastapplygroup = ENABLE_COMPLEX_VAL;
		int lastapplyflight = ENABLE_COMPLEX_VAL;
		int lastapplyelt = ENABLE_COMPLEX_VAL;

		int g;
		if (comboindex == ESCORTFUEL)
			g = 2;
		else if (comboindex == AAAFUEL)
		{ 	
			if (ag[1])
				g = 1;
			else
				g = 2;
		}else
			g = 0;

//------------------------------------------------------------------------------------
//take off point data
		switch	(comboindex)
		{
			case L_POSITION:
			{
				if (Todays_Packages[packnum][wavenum][0].takeoffAF != UID_NULL)
				{
					rlistbox->AddString(GetTargName(Todays_Packages[packnum][wavenum][0].takeoffAF),1);
				}
				break;
			}
			case L_ALTITUDE:
			{
				rlistbox->AddString("",1);
				break;
			}
			case L_ETAREL:
			case L_ETA:
			{
				int t=Todays_Packages[packnum][wavenum][0].takeofftime/60;
				if (comboindex == L_ETA)
				{
					sprintf(buffer,"%02i:%02i",t/60,t%60);
					rlistbox->AddString(buffer,1);
				}else
				{
					int targtime=Todays_Packages[packnum][wavenum].targettime/60;
					t-=targtime;
					if (t>=0)
						sprintf(buffer,"+%02i:%02i",t/60,t%60);
					else
						sprintf(buffer,"-%02i:%02i",-t/60,-t%60);
					rlistbox->AddString(buffer,1);
				}
				break;
			}
			case FUELLEFT:
			case AAAFUEL:
			case ESCORTFUEL:
			{
				if (Todays_Packages[packnum][wavenum].group[g].squadron < SQ_B_NONFLYABLE)
					rlistbox->AddString(CSprintf("%5i",fuel[g]/ (100*Save_Data.mass.gm)),1);
				else
					rlistbox->AddString(RESSTRING(NA),1);
				break;
			}
		}

//------------------------------------------------------------------------------------
//all other waypoints


		COORDS3D* last;
		COORDS3D* lastwp[3];
		COORDS3D* home;
		info_waypoint* wp;
		while (u)
		{
			wp=*Persons2::ConvertPtrUID(u);

			if (currmainwp ==1)
			{
				last=&Persons2::ConvertPtrUID(Todays_Packages[packnum][wavenum][0].takeoffAF)->World;
				home=last;
			}else if (		(Profile::NonLeadElementSet(lastapplyflight, lastapplyelt))
						&&	(wp->applygroup != ENABLE_COMPLEX_VAL)
					)
			{
				 last = lastwp[wp->applygroup];
			}else if (			(wp->applygroup!=ENABLE_COMPLEX_VAL)
						&&		(lastapplygroup != wp->applygroup)
					 )
			{
					 last = lastwp[wp->applygroup];
		 			if (!Profile::NonLeadElementSet(wp->applyflight, wp->applyelt))
						 lastwp[wp->applygroup] = &wp->World;
			}else if (			(wp->applygroup!=ENABLE_COMPLEX_VAL)
						&&		(lastapplygroup == wp->applygroup)
					 )
			{
					if (!Profile::NonLeadElementSet(wp->applyflight, wp->applyelt))
						 lastwp[wp->applygroup] = &wp->World;
			}else if (			(wp->applygroup == ENABLE_COMPLEX_VAL)
						&&		(lastapplygroup != ENABLE_COMPLEX_VAL)
					 )
			{
				last = lastwp[g];
			}


			if (wp->uid!=GOT_UNDEFINED_VAL)
			{
				currmainwp+=1;currsubwp='A';

				sprintf(buffer,"%i. %s",currmainwp,RESLIST(MAIN_WP_GAP,currmainwp));
			}
			else
			{
				currsubwp++;		//say which groups processed by this sub-waypoint
				sprintf(buffer,"%i. %c",currmainwp,currsubwp-1);
			}
			if (currmainwp!=4 || currsubwp=='A')
			{	//4A filled in, other 4 (ie 4B) not 
				*listptr++=u;
				row++;
				rlistbox->AddString(buffer,0);
				if (u == Todays_Packages.hiwp)
					currrow=row;

				switch	(comboindex)
				{
					case L_POSITION:
					{
						rlistbox->AddString(GetAreaName(wp),1);
						break;
					}
					case L_ALTITUDE:
					{
						int alt = (wp->World.Y*10)/Save_Data.alt.mediummm;
						alt = 100*((alt + 50)/100);
						sprintf(buffer,"%i%s",alt,LoadResString(Save_Data.alt.mediumabbr));
						rlistbox->AddString(buffer,1);
						break;
					}
					case L_ETAREL:
					case L_ETA:
					{
						int t=wp->etas/60;
						currtime = wp->etas;
						if (comboindex == L_ETA)
						{
							sprintf(buffer,"%02i:%02i",t/60,t%60);
							rlistbox->AddString(buffer,1);
						}else
						{
							int targtime=Todays_Packages[packnum][wavenum].targettime/60;
							t-=targtime;
							if (t>=0)
								sprintf(buffer,"+%02i:%02i",t/60,t%60);
							else
								sprintf(buffer,"-%02i:%02i",-t/60,-t%60);
							rlistbox->AddString(buffer,1);
						}
						break;
					}
					case FUELLEFT:
					case AAAFUEL:
					case ESCORTFUEL:
					{
						fuel[g] -= Profile::CalcFuel(last,&wp->World,ag[0]->type,ag[g]->type);
						if (Todays_Packages[packnum][wavenum].group[g].squadron < SQ_B_NONFLYABLE)
							rlistbox->AddString(CSprintf("%5i",fuel[g]/ (100*Save_Data.mass.gm)),1);
						else
							rlistbox->AddString(RESSTRING(NA),1);
	
						break;
					}
				}
			}else
			{//target area waypoints
				switch	(comboindex)
				{
					case FUELLEFT:
					case AAAFUEL:
					case ESCORTFUEL:
					{
						if  (		(wp->applygroup == g)
								&&	(!Profile::NonLeadElementSet(wp->applyflight, wp->applyelt))
							)								
							fuel[g] -=Profile::CalcFuel(last,&wp->World,ag[g]->type,ag[g]->type);
						break;
					}
				}
			}
			if (currmainwp==4 && currsubwp=='A')
			{
				lastwp[0] = &wp->World;
				lastwp[1] = &wp->World;
				lastwp[2] = &wp->World;
			}
			last=&wp->World;
			lastapplygroup = wp->applygroup;
			lastapplyflight = wp->applyflight;
			lastapplyelt = wp->applyelt;

			u=wp->nextwp;
			
		}
		currmainwp+=1;
//------------------------------------------------------------------------------------
//Landing
		sprintf(buffer,"%i. %s",currmainwp,RESLIST(MAIN_WP_GAP,currmainwp));
		rlistbox->AddString(buffer,0);

		switch	(comboindex)
		{
			case L_POSITION:
			{
				if (Todays_Packages[packnum][wavenum][0].takeoffAF != UID_NULL)
				{
					rlistbox->AddString(GetTargName(Todays_Packages[packnum][wavenum][0].takeoffAF),1);
				}
				break;
			}
			case L_ALTITUDE:
			{
				rlistbox->AddString("",1);
				break;
			}
			case L_ETAREL:
			case L_ETA:
			{
				int t=(currtime + Profile::CalcTime(last,home,ag[0]->type))/60;
				if (comboindex == L_ETA)
				{
					sprintf(buffer,"%02i:%02i",t/60,t%60);
					rlistbox->AddString(buffer,1);
				}else
				{
					int targtime=Todays_Packages[packnum][wavenum].targettime/60;
					t-=targtime;
					if (t>0)
						sprintf(buffer,"+%02i:%02i",t/60,t%60);
					else
						sprintf(buffer,"-%02i:%02i",-t/60,-t%60);
					rlistbox->AddString(buffer,1);
				}
				break;
			}
					case FUELLEFT:
					case AAAFUEL:
					case ESCORTFUEL:
					{
						fuel[g] -= Profile::CalcFuel(last,home,ag[0]->type,ag[g]->type);
						if (Todays_Packages[packnum][wavenum].group[g].squadron < SQ_B_NONFLYABLE)
							rlistbox->AddString(CSprintf("%5i",fuel[g]/ (100*Save_Data.mass.gm)),1);
						else
							rlistbox->AddString(RESSTRING(NA),1);
	
						break;
					}
		}
 		while (listptr!=listentries+40)
 			*listptr++=UID_Null;

	}
	else
	{
		rlistbox->AddString(RESSTRING(OFFDUTY),0);
	}
	rlistbox->SetHilightCol(0);
	if (currrow!=0)
	{
		RefreshDetail(listentries[currrow]);
		rlistbox->SetHilightRow(currrow);
	}
	SetButtons(currrow);

}
*/


void	CWPShare::RefreshDetail(UniqueID u)
{
	if (!wpdetail)
		for (wpdetail=(RowanDialog*)parent->fchild;wpdetail;wpdetail=(RowanDialog*)wpdetail->sibling)
			breakif(wpdetail->packnum!=-1 && wpdetail!=this);
	wpdetail->acnum=u;
	wpdetail->RefreshData(0);
}
void	CWPShare::RefreshButtons(int effect)
{
	if (!wpbuttons)
		for (wpbuttons=(RowanDialog*)parent->fchild;wpbuttons;wpbuttons=(RowanDialog*)wpbuttons->sibling)
			breakif(wpbuttons->packnum==-1);
	wpbuttons->RefreshData(effect);
}
void CWPShare::SetButtons(long row)
{
	UniqueID u=listentries[row];

			if (u)
			{
				//set the Package current wapyoint as well...

				info_waypoint* wp=*Persons2::ConvertPtrUID(u);
				//enable/disable buttons based on functionality...
				if (wp->uid!=ENABLE_COMPLEX_VAL)
					if (!listfull && Todays_Packages.CanAddMoreWaypoints(packnum))
						RefreshButtons(INSONDELOFF);
					else
						RefreshButtons(INSOFFDELOFF);
				else
					if (!listfull && Todays_Packages.CanAddMoreWaypoints(packnum))
						RefreshButtons(INSONDELON);
					else
						RefreshButtons(INSOFFDELON);

			}
			else
			{
				//disable most buttons for takeoff and landing

				if (row==0 && Todays_Packages.CanAddMoreWaypoints(packnum))
				{	//take-off allows insert

					RefreshButtons(INSONDELOFF);
				}
				else
				{	//landing doesn't
					RefreshButtons(INSOFFDELOFF);
				}
			}

}
void CWPShare::OnSelectWaypointlist(long row, long column) 
{
	// TODO: Add your control notification handler code here
	CRListBox* rlistbox=GETDLGITEM(IDC_WAYPOINTLIST);
//	if (row==0)
//	{
//		if (rlistbox->GetColumnWidth(column)==widecol)
//		{
//			rlistbox->SetColumnWidth(column,thincol);
//			if (column==6)
//				rlistbox->SetColumnWidth(1,widecol);
//			else
//				rlistbox->SetColumnWidth(column+1,widecol);
//		}
//		else
//			rlistbox->SetColumnWidth(column,widecol);
//
//	}
//	else
	{
		if (row==currrow)
		{	//open waypoint details dialog
			//need OnClosed() functionality so only one open at a time
			parent->RefreshData(RADIODETAIL);
		}
		else
		{
			currrow=row;
			UniqueID u=listentries[currrow];
			RefreshDetail(u);
			SetButtons(row);
			RDialog::m_pView->SetHiLightInfo(packnum,  wavenum, 0, u);
//			RDialog::m_pView->m_mapdlg.ResetIcon(u);

		}
	}

}

void CWPShare::OnDelete() 
{
	// TODO: Add your control notification handler code here
	UniqueID u=listentries[currrow];
	if (u)
	{
		info_waypoint* wp=*Persons2::ConvertPtrUID(u);
		if (wp->uid==ENABLE_COMPLEX_VAL)
		{	//I can delete it!
			info_waypoint* wp2=*Persons2::ConvertPtrUID(wp->nextwp);
			if (wp2)
				wp2->prevwp=wp->prevwp;
			wp2=*Persons2::ConvertPtrUID(wp->prevwp);
			if (wp2)
				wp2->nextwp=wp->nextwp;
			else
				Todays_Packages[packnum][wavenum].firstwp=wp->nextwp;
			delete wp;
			Todays_Packages[packnum].wpsused--;
			Persons2::delUID(u);
			if (currrow!=1)
			{
				currrow--;
 				u=listentries[currrow];
				RDialog::m_pView->SetHiLightInfo(packnum, wavenum, 0, u);
				//RDialog::m_pView->m_mapdlg.ResetIcon(u);
				RefreshDetail(u);
			}
			DisplayData();
			m_pView->m_mapdlg.Invalidate();


		}

	}
}

void	CWPShare::RefreshData(int childnum)
{
	switch (childnum)
	{
	case WPDetail::DATA:
		DisplayData();
	break;
	case WPDetail::NEXT:
		if (listentries[currrow+1])
		{
			currrow++;
 			UniqueID u=listentries[currrow];
			RDialog::m_pView->SetHiLightInfo(packnum, wavenum, 0, u);
//			RDialog::m_pView->m_mapdlg.ResetIcon(u);
			RefreshDetail(u);
		}else
			parent->RefreshData(RADIOLIST);
	break;
	case WPDetail::PREV:
		if (currrow!=1)
		{
			currrow--;
 			UniqueID u=listentries[currrow];
			RDialog::m_pView->SetHiLightInfo(packnum, wavenum, 0, u);
//			RDialog::m_pView->m_mapdlg.ResetIcon(u);
			RefreshDetail(u);
		}else
			parent->RefreshData(RADIOLIST);
	break;
	}
}


void CWPShare::OnInsert() 
{
	// TODO: Add your control notification handler code here
	int	relfromcode=SGR_Pack_Takeoff,reltocode=SGR_Pack_Takeoff;
	COORDS3D	*posfrom=NULL,*posto=NULL;
	COORDS3D	*relfrom=NULL,*relto=NULL;
	info_waypoint	*prev=NULL,*next=NULL;

	UniqueID u=listentries[currrow];   //look for prev wp and prev key wp
	if (u)
	{
		info_waypoint *t=
			prev=
				*Persons2::ConvertPtrUID(u);
		if (prev->uid==-SGR_WPP_Target || prev->uid==-SGR_WPC_Target)
		{
			//switch tabs to attack group tab
			CProfile::wavetabs->SelectTab(0);
			return;
		}
		posfrom=&t->World;
		do{
			if (t->uid!=ENABLE_COMPLEX_VAL)
			{
				relfromcode=-t->uid;
				relfrom=&t->World;
				break;
			}
			t=*Persons2::ConvertPtrUID(t->prevwp);
		}while(t);
	}

	u=listentries[currrow+1];		//look for next wp and next key wp
	if (u)
	{
		info_waypoint *t=
			next=
				*Persons2::ConvertPtrUID(u);
		posto=&t->World;
		do{
			if (t->uid!=ENABLE_COMPLEX_VAL)
			{
				reltocode=-t->uid;
				relto=&t->World;
				break;
			}
			t=*Persons2::ConvertPtrUID(t->nextwp);
		}while(t);
	}

	if (!(posfrom&&posto&&relfrom&&relto))
	{
		COORDS3D* p=&Persons2::ConvertPtrUID(Todays_Packages[packnum][0][0].takeoffAF)->World;
		if (!posfrom)
			posfrom=p;
		if (!posto)
			posto=p;
		if (!relfrom)
			relfrom=p;
		if (!relto)
			relto=p;
	}
//Ok.. make a waypoint. 
//Set its position to midway between posfrom and posto
//Set the description of its position to the same place but
//using relto and relfrom to drive it!!!!
	u=Profile::MakeInterceptWP((SavedGlobrefs)relfromcode,(SavedGlobrefs)reltocode,50,UID_Null,SGR_BLANK);
	Todays_Packages[packnum].wpsused++;
	info_waypoint* w=*Persons2::ConvertPtrUID(u);
	w->World.X=(posfrom->X+posto->X)/2;
	w->World.Y=(posfrom->Y+posto->Y)/2;
	w->World.Z=(posfrom->Z+posto->Z)/2;
	w->position.RecalcDeltasToMatch(w->World);
	if (next)
	{
		w->nextwp=listentries[currrow+1];
		next->prevwp=u;
	}
	else
		w->nextwp=UID_Null;

	if (prev)
	{
		w->prevwp=listentries[currrow];
		prev->nextwp=u;
	}
	else
	{
		Todays_Packages[packnum][wavenum].firstwp=u;
		w->prevwp=UID_Null;	
	}
//	u=listentries[currrow];
	RDialog::m_pView->SetHiLightInfo(packnum, wavenum, 0, u);
//	RDialog::m_pView->m_mapdlg.ResetIcon(u);
	RDialog::m_pView->m_mapdlg.Invalidate();

	RefreshDetail(u);
	Todays_Packages[packnum].CalcWPTimes(wavenum);
	DisplayData();
	//make inserted one current hilight
}

void CWPShare::OnMove() 
{
	if (listentries[currrow])
	RDialog::m_pView->ZoomToUID(UniqueID(listentries[currrow]),RDialog::m_pView->m_zoom);
	
}

void CWPShare::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	CRect rect3;
	GetClientRect(rect3);
	rect3.top+=30;
	CRListBox* rlistbox;
	rlistbox=GETDLGITEM(IDC_WAYPOINTLIST);
	if (rlistbox->m_hWnd)
		rlistbox->MoveWindow(rect3);
	
}


void CWPShare::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	
}

//BEGIN_EVENTSINK_MAP(CWPShare, CDialog)
//    //{{AFX_EVENTSINK_MAP(CWPShare)
//	ON_EVENT(CWPShare, IDC_WAYPOINTLIST, 1 /* Select */, OnSelectWaypointlist, VTS_I4 VTS_I4)
//	//}}AFX_EVENTSINK_MAP
//END_EVENTSINK_MAP()

void CWPShare::OnSelectTab(RDialog* tab)
{
	DisplayData();

}
void CWPShare::OnTextChangedType(LPCTSTR text) 
{
	CRCombo* combo=GETDLGITEM(IDC_TYPE);
	comboindex=combo->GetIndex();

	DisplayData();
	
}
