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

// WPGround.cpp : implementation file
// This file does ground, aaa, and escort tabs
//
//

#include "stdafx.h"
#include "mig.h"
#include "WPGround.h"
#include "WPshare.h"
#include	"bfnumber.h"
#include	"persons2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#ifndef THIS_FILE_DEFINED
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif

/////////////////////////////////////////////////////////////////////////////
// CWPGround dialog


CWPGround::CWPGround(int pack,int wave,int group,CWnd* pParent /*=NULL*/)
	: RowanDialog(CWPGround::IDD, pParent)
{
	SetProjSpecific(pack,wave,group);
//	currrow=0;
	groupingmode=0;
	comboindex = 0;
	currrow = 0;
	tablewp=NULL;													  //DAW 03/06/99
	tabletype=NULL;													  //DAW 03/06/99

	wpdetail=NULL;
	wpbuttons = NULL;



	//{{AFX_DATA_INIT(CWPGround)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CWPGround::~CWPGround()
{
	delete tablewp;
	delete tabletype;
}
void CWPGround::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWPGround)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	DDX_Control(pDX,IDC_WAYPOINTLIST,m_IDC_WAYPOINTLIST);
	DDX_Control(pDX,IDC_TYPE,m_IDC_TYPE);
	DDX_Control(pDX,IDC_LEVEL,m_IDC_LEVEL);
	//}}AFX_DATA_MAP
	if (Todays_Packages[packnum][wavenum].firstwp)
		Todays_Packages[packnum][wavenum].
			GetKeyTargetWPs(keys[BEFORE],keys[ATTACK1],keys[BETWEEN],keys[ATTACK2],keys[AFTER],keys[POSTRV]);
	if (Todays_Packages[packnum][wavenum].firstwp)
	{
		UniqueID firstwp=
			Todays_Packages[packnum][wavenum].FindWpBetween(keys[BEFORE],keys[POSTRV],groupnum,0,0);
		info_waypoint* wp=*Persons2::ConvertPtrUID(firstwp);
		if (wp)
			if (wp->applyflight!=ENABLE_COMPLEX_VAL)
				if (wp->applyelt!=ENABLE_COMPLEX_VAL)
					groupingmode=2;
				else
					groupingmode=1;
	}

	DescribeTargetRoute();
	if (currrow)
	{
		CRListBox* rlistbox=GETDLGITEM(IDC_WAYPOINTLIST);
		rlistbox->SetHilightRow(currrow+1);
		RefreshDetail(tablewp[currrow]);
	}
}


BEGIN_MESSAGE_MAP(CWPGround, CDialog)
	//{{AFX_MSG_MAP(CWPGround)
	ON_WM_SIZE()
	ON_MESSAGE( WM_SELECTTAB, OnSelectTab)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
/////////////////////////////////////////////////////////////////////////////
// CWPGround message handlers

BEGIN_EVENTSINK_MAP(CWPGround, CDialog)
    //{{AFX_EVENTSINK_MAP(CWPGround)
	ON_EVENT(CWPGround, IDC_WAYPOINTLIST, 1 /* Select */, OnSelectWaypointlist, VTS_I4 VTS_I4)
	ON_EVENT(CWPGround, IDC_TYPE, 1 /* TextChanged */, OnTextChangedType, VTS_BSTR)
	ON_EVENT(CWPGround, IDC_DELETE, 1 /* Clicked */, OnDelete, VTS_NONE)
	ON_EVENT(CWPGround, IDC_INSERT, 1 /* Clicked */, OnInsert, VTS_NONE)
	ON_EVENT(CWPGround, IDC_MOVE, 1 /* Clicked */, OnMove, VTS_NONE)
	ON_EVENT(CWPGround, IDC_LEVEL, 1 /* TextChanged */, OnTextChangedLevel, VTS_BSTR)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void	CWPGround::RefreshDetail(UniqueID u)
{
	if (!wpdetail)
		for (wpdetail=(RowanDialog*)parent->fchild;wpdetail;wpdetail=(RowanDialog*)wpdetail->sibling)
			breakif(wpdetail->packnum!=-1 && wpdetail!=this);
	wpdetail->acnum=u;
	wpdetail->RefreshData(0);
}

void	CWPGround::DescribeTargetRoute()
{
	if (!Todays_Packages[packnum][wavenum].firstwp || !Todays_Packages[packnum][wavenum][groupnum].uid)
		return;
	int	minelt,maxelt;
	int	minfl,maxfl;
	int maxrows;
	switch (groupingmode)
	{
		case 0:
				minelt=maxelt=-1;
				minfl=maxfl=-1;
				maxrows=MAXLISTSIZE;
		break;
		case 1:
				minelt=maxelt=-1;
				minfl=0,maxfl=Todays_Packages[packnum][wavenum][groupnum].numflights-1;
				maxrows=MAXLISTSIZE*(maxfl+1);
		break;
		case 2:
				minelt=0,maxelt=1;
				minfl=0,maxfl=Todays_Packages[packnum][wavenum][groupnum].numflights-1;
				maxrows=MAXLISTSIZE*(maxfl+1)*2;
		break;
	}
	delete[] tabletype;
	delete[] tablewp;
	tabletype=new	TableType[maxrows];
	tablewp=new		UniqueID[maxrows];
	Todays_Packages[packnum][wavenum].
		GetKeyTargetWPs(keys[BEFORE],keys[ATTACK1],keys[BETWEEN],keys[ATTACK2],keys[AFTER],keys[POSTRV]);
	CRListBox* rlistbox=GETDLGITEM(IDC_WAYPOINTLIST);
	rlistbox->Clear();
	int	row=0;
	rlistbox->AddColumn(90);
	rlistbox->AddColumn(20);

//	tabletype[row++]=HEADER;
	maxrows=0;
	for (UniqueID u=keys[BEFORE];u&&u!=keys[POSTRV];u=Profile::Wave::FindWpAfter(u,keys[POSTRV],groupnum,-1,-1))
		maxrows++;
	listfull=(maxrows>LISTFULLSIZE);

	for (int fl=minfl;fl<=maxfl;fl++)
		for (int elt=minelt;elt<=maxelt;elt++)
		{
			char buffer[30];
			{
				if (fl!=-1)
					if (elt!=-1)
						sprintf(buffer,RESSTRING(FL_PC_EL_PC),fl+1,elt+1);
					else
						sprintf(buffer,RESSTRING(FL_PC),fl+1);
				else
					sprintf(buffer,RESSTRING(NONE));
				rlistbox->AddString(buffer,0);
				rlistbox->AddString("",1);
				tabletype[row]=TITLE;
				tablewp[row]=UniqueID(((fl&7)*4)+(elt&3));
				row++;

			}
//want a target arrival time line before
			Describeonewp(rlistbox,keys[BEFORE],MAINROUTE,row++,' ');
			UniqueID u;
			int wpnum=0;
			char wpletter='A';
			u=Profile::Wave::FindWpBetween(keys[BEFORE],keys[ATTACK1],groupnum,fl,elt);
			while (u && u!=keys[ATTACK1])
			{	//extra waypoints before target1
				Describeonewp(rlistbox,u,BEFORE,row++,wpletter++);
				u=Profile::Wave::FindWpAfter(u,keys[ATTACK1],groupnum,fl,elt);
			}
			u=Profile::Wave::FindWpBetween(keys[ATTACK1],keys[BETWEEN],groupnum,fl,elt);
			while (u)
			{	//waypoints at target1
				Describeonewp(rlistbox,u,ATTACK1,row++,wpletter++);
				u=Profile::Wave::FindWpAfter(u,keys[BETWEEN],groupnum,fl,elt);
			}
			u=Profile::Wave::FindWpAfter(keys[BETWEEN],keys[ATTACK2],groupnum,fl,elt);
			while (u && u!=keys[ATTACK2])
			{	//extra waypoints between target1 and target2
				Describeonewp(rlistbox,u,BETWEEN,row++,wpletter++);
				u=Profile::Wave::FindWpAfter(u,keys[ATTACK2],groupnum,fl,elt);
			}
			u=Profile::Wave::FindWpBetween(keys[ATTACK2],keys[AFTER],groupnum,fl,elt);
			if (u!=keys[BETWEEN])									  //JIM 01/06/99
			while (u)
			{	//waypoints at target2
				Describeonewp(rlistbox,u,ATTACK2,row++,wpletter++);
				u=Profile::Wave::FindWpAfter(u,keys[AFTER],groupnum,fl,elt);
			}
			u=Profile::Wave::FindWpAfter(keys[AFTER],keys[POSTRV],groupnum,fl,elt);
			while (u && u!=keys[POSTRV])
			{	//extra waypoints after target2
				Describeonewp(rlistbox,u,AFTER,row++,wpletter++);
				u=Profile::Wave::FindWpAfter(u,keys[POSTRV],groupnum,fl,elt);
			}
//want a target regroup line after
		}
		Describeonewp(rlistbox,keys[POSTRV],POSTRV,row++,' ');
	rlistbox->SetHilightCol(0);
   	if (currrow!=0)
	{
		RefreshDetail(tablewp[currrow]);
		rlistbox->SetHilightRow(currrow);
	}
	SetButtons(currrow);
	if  (		(tabletype[currrow] != MAINROUTE)
			&&	(tabletype[currrow] != POSTRV)
			&&	(tabletype[currrow] != TITLE)
		)
		parent->RefreshData(CWPShare::RADIOENABLE);
	else
		parent->RefreshData(CWPShare::RADIODISABLE);

//want a target disperse line after
//want a landing time after

//DeadCode RDH 01Nov98 	if (!Todays_Packages[packnum][wavenum].firstwp || !Todays_Packages[packnum][wavenum][groupnum].uid)
//DeadCode RDH 01Nov98 		return;
//DeadCode RDH 01Nov98 	int	minelt,maxelt;
//DeadCode RDH 01Nov98 	int	minfl,maxfl;
//DeadCode RDH 01Nov98 
//DeadCode RDH 01Nov98 	switch (groupingmode)
//DeadCode RDH 01Nov98 	{
//DeadCode RDH 01Nov98 		case 0:
//DeadCode RDH 01Nov98 				minelt=maxelt=-1;
//DeadCode RDH 01Nov98 				minfl=maxfl=-1;
//DeadCode RDH 01Nov98 		break;
//DeadCode RDH 01Nov98 		case 1:
//DeadCode RDH 01Nov98 				minelt=maxelt=-1;
//DeadCode RDH 01Nov98 				minfl=0,maxfl=3;
//DeadCode RDH 01Nov98 		break;
//DeadCode RDH 01Nov98 		case 2:
//DeadCode RDH 01Nov98 				minelt=0,maxelt=1;
//DeadCode RDH 01Nov98 				minfl=0,maxfl=3;
//DeadCode RDH 01Nov98 		break;
//DeadCode RDH 01Nov98 	}
//DeadCode RDH 01Nov98 
//DeadCode RDH 01Nov98 	CRListBox* rlistbox=GetDlgItem(IDC_WAYPOINTLIST);
//DeadCode RDH 01Nov98 	rlistbox->Clear();
//DeadCode RDH 01Nov98 	int	currrow=0;
//DeadCode RDH 01Nov98 	rlistbox->AddColumn(120);
//DeadCode RDH 01Nov98 	rlistbox->AddColumn(20);
//DeadCode RDH 01Nov98	rlistbox->AddColumn(thincol);
//DeadCode RDH 01Nov98	rlistbox->AddColumn(thincol);
//DeadCode RDH 01Nov98	rlistbox->AddColumn(thincol);
//DeadCode RDH 01Nov98	rlistbox->AddColumn(thincol);
//DeadCode RDH 01Nov98	rlistbox->AddColumn(thincol);
//DeadCode RDH 01Nov98	rlistbox->AddColumn(thincol);
//DeadCode RDH 01Nov98 
//DeadCode RDH 01Nov98 	rlistbox->AddString(RESSTRING(WAYPOINT),0);
//DeadCode RDH 01Nov98 	rlistbox->AddString(RESSTRING(POSITION),1);
//DeadCode RDH 01Nov98 	rlistbox->AddString(RESSTRING(ALTITUDE),2);
//DeadCode RDH 01Nov98 	rlistbox->AddString(RESSTRING(VELOCITY),3);
//DeadCode RDH 01Nov98 	rlistbox->AddString(RESSTRING(ETA),4);
//DeadCode RDH 01Nov98 	rlistbox->AddString(RESSTRING(ETA),5);
//DeadCode RDH 01Nov98 	rlistbox->AddString(RESSTRING(FUELUSED),6);
//DeadCode RDH 01Nov98 	tabletype[currrow++]=HEADER;
//DeadCode RDH 01Nov98 
//DeadCode RDH 01Nov98 
//DeadCode RDH 01Nov98 	for (int fl=minfl;fl<=maxfl;fl++)
//DeadCode RDH 01Nov98 		for (int elt=minelt;elt<=maxelt;elt++)
//DeadCode RDH 01Nov98 		{
//DeadCode RDH 01Nov98 			char buffer[30];
//DeadCode RDH 01Nov98 			{
//DeadCode RDH 01Nov98 				if (fl!=-1)
//DeadCode RDH 01Nov98 					if (elt!=-1)
//DeadCode RDH 01Nov98 						sprintf(buffer,RESSTRING(FL_PC_EL_PC),fl,elt);
//DeadCode RDH 01Nov98 					else
//DeadCode RDH 01Nov98 						sprintf(buffer,RESSTRING(FL_PC),fl);
//DeadCode RDH 01Nov98 				else
//DeadCode RDH 01Nov98 					sprintf(buffer,RESSTRING(ALLFLIGHTS));
//DeadCode RDH 01Nov98 				rlistbox->AddString(buffer,0);
//DeadCode RDH 01Nov98 				rlistbox->AddString("",1);
//DeadCode RDH 01Nov98				rlistbox->AddString("",2);
//DeadCode RDH 01Nov98				rlistbox->AddString("",3);
//DeadCode RDH 01Nov98				rlistbox->AddString("",4);
//DeadCode RDH 01Nov98 				rlistbox->AddString("",5);
//DeadCode RDH 01Nov98 				rlistbox->AddString("",6);
//DeadCode RDH 01Nov98 				tabletype[currrow]=TITLE;
//DeadCode RDH 01Nov98 				tablewp[currrow]=UniqueID(((fl&7)*4)+(elt&3));
//DeadCode RDH 01Nov98 				currrow++;
//DeadCode RDH 01Nov98 
//DeadCode RDH 01Nov98 			}
//DeadCode RDH 01Nov98 //want a target arrival time line before
//DeadCode RDH 01Nov98 			Describeonewp(rlistbox,keys[BEFORE],MAINROUTE,currrow++,' ');
//DeadCode RDH 01Nov98 			UniqueID u;
//DeadCode RDH 01Nov98 			int wpnum=0;
//DeadCode RDH 01Nov98 			char wpletter='A';
//DeadCode RDH 01Nov98 			u=Profile::Wave::FindWpBetween(keys[BEFORE],keys[ATTACK1],groupnum,fl,elt);
//DeadCode RDH 01Nov98 			while (u && u!=keys[ATTACK1])
//DeadCode RDH 01Nov98 			{
//DeadCode RDH 01Nov98 				Describeonewp(rlistbox,u,BEFORE,currrow++,wpletter++);
//DeadCode RDH 01Nov98 				u=Profile::Wave::FindWpAfter(u,keys[ATTACK1],groupnum,fl,elt);
//DeadCode RDH 01Nov98 			}
//DeadCode RDH 01Nov98 			u=Profile::Wave::FindWpBetween(keys[ATTACK1],keys[BETWEEN],groupnum,fl,elt);
//DeadCode RDH 01Nov98 			while (u)
//DeadCode RDH 01Nov98 			{
//DeadCode RDH 01Nov98 				Describeonewp(rlistbox,u,ATTACK1,currrow++,wpletter++);
//DeadCode RDH 01Nov98 				u=Profile::Wave::FindWpAfter(u,keys[BETWEEN],groupnum,fl,elt);
//DeadCode RDH 01Nov98 			}
//DeadCode RDH 01Nov98 			u=Profile::Wave::FindWpAfter(keys[BETWEEN],keys[ATTACK2],groupnum,fl,elt);
//DeadCode RDH 01Nov98 			while (u && u!=keys[ATTACK2])
//DeadCode RDH 01Nov98 			{
//DeadCode RDH 01Nov98 				Describeonewp(rlistbox,u,BETWEEN,currrow++,wpletter++);
//DeadCode RDH 01Nov98 				u=Profile::Wave::FindWpAfter(u,keys[ATTACK2],groupnum,fl,elt);
//DeadCode RDH 01Nov98 			}
//DeadCode RDH 01Nov98 			u=Profile::Wave::FindWpBetween(keys[ATTACK2],keys[AFTER],groupnum,fl,elt);
//DeadCode RDH 01Nov98 			if (u!=keys[ATTACK1])
//DeadCode RDH 01Nov98 			while (u)
//DeadCode RDH 01Nov98 			{
//DeadCode RDH 01Nov98 				Describeonewp(rlistbox,u,ATTACK2,currrow++,wpletter++);
//DeadCode RDH 01Nov98 				u=Profile::Wave::FindWpAfter(u,keys[AFTER],groupnum,fl,elt);
//DeadCode RDH 01Nov98 			}
//DeadCode RDH 01Nov98 			u=Profile::Wave::FindWpAfter(keys[AFTER],keys[POSTRV],groupnum,fl,elt);
//DeadCode RDH 01Nov98 			while (u && u!=keys[POSTRV])
//DeadCode RDH 01Nov98 			{
//DeadCode RDH 01Nov98 				Describeonewp(rlistbox,u,AFTER,currrow++,wpletter++);
//DeadCode RDH 01Nov98 				u=Profile::Wave::FindWpAfter(u,keys[POSTRV],groupnum,fl,elt);
//DeadCode RDH 01Nov98 			}
//DeadCode RDH 01Nov98 //want a target regroup line after
//DeadCode RDH 01Nov98 		}
//DeadCode RDH 01Nov98 		Describeonewp(rlistbox,keys[POSTRV],POSTRV,currrow++,' ');
//DeadCode RDH 01Nov98 
//DeadCode RDH 01Nov98 //want a target disperse line after
//DeadCode RDH 01Nov98 //want a landing time after
//DeadCode RDH 01Nov98 
}

void	CWPGround::Describeonewp(CRListBox* listbox,UniqueID u,TableType t,int addrow,char currletter)
{
	info_waypoint*	w=*Persons2::ConvertPtrUID(u);
	char buffer[30];
	if (w->uid.Evaluate()==ENABLE_COMPLEX_VAL)
	{
		char buffer2[30];
		bool simpleform=false;
		if (groupingmode==0 && w->applyflight.Evaluate()==ENABLE_COMPLEX_VAL)
			simpleform=true;
		if (groupingmode==2 && w->applyelt.Evaluate()!=ENABLE_COMPLEX_VAL)
			simpleform=true;
		if (groupingmode==1 && w->applyelt.Evaluate()==ENABLE_COMPLEX_VAL && w->applyflight.Evaluate()!=ENABLE_COMPLEX_VAL)
			simpleform=true;
		int action=w->wpact.Evaluate();
		if (action==ENABLE_COMPLEX_VAL)
			action=wpacnoactionno;
		if (simpleform)
			sprintf(buffer,"%c) %s",currletter,RESLIST(WPACTION_NONE,action));
		else
		{
			if (w->applyelt.Evaluate()!=ENABLE_COMPLEX_VAL)
				sprintf(buffer2,RESSTRING(FL_PC_EL_PC),w->applyflight.Evaluate()+1,w->applyelt.Evaluate()+1);
			else
			if (w->applyflight.Evaluate()!=ENABLE_COMPLEX_VAL)
				sprintf(buffer2,RESSTRING(FL_PC),w->applyflight.Evaluate()+1);
			else
				sprintf(buffer2,RESSTRING(ALL));
			sprintf(buffer,"%c (%s) %s",currletter,buffer2,RESLIST(WPACTION_NONE,action));
		}

		listbox->AddString(buffer,0);
	}
	else
		if (u==keys[BEFORE])
			listbox->AddString(RESSTRING(MAIN_WP_TARGET),0);
		else
		if (u==keys[POSTRV])
			listbox->AddString(RESSTRING(MAIN_WP_REGROUP),0);
		else
			listbox->AddString(RESSTRING(MAIN_WP_DISPERSE),0);
				


		switch	(comboindex)
		{
			case L_POSITION:
			{
//TEMPCODE DAW 26/05/99 #pragma warnmsg("Jim test");
//TEMPCODE DAW 26/05/99 				listbox->AddString(CSprintf("%04x",w->uniqueID.count),1); //JIM 25/05/99
				listbox->AddString(GetAreaName(w),1);
				break;
			}
			case L_ALTITUDE:
			{
				int alt = (w->World.Y*10)/Save_Data.alt.mediummm;
				alt = 100*((alt + 50)/100);
				listbox->AddString(CSprintf("%i%s",alt,LoadResString(Save_Data.alt.mediumabbr)),1);
//DeadCode RDH 01Nov98 	if (w->vel!=0 && w->vel!=ENABLE_COMPLEX_VAL)
//DeadCode RDH 01Nov98 	{
//DeadCode RDH 01Nov98 		sprintf(buffer,"%i",w->vel/5);
//DeadCode RDH 01Nov98 		listbox->AddString(buffer,3);
//DeadCode RDH 01Nov98 	}
//DeadCode RDH 01Nov98 	else
//DeadCode RDH 01Nov98 		listbox->AddString(RESSTRING(CRUISE),3);
				break;
			}
			case L_ETAREL:
			case L_ETA:
			{
				if (		(w->applyflight != ENABLE_COMPLEX_VAL)
						&&	(		(w->applyflight > 0)
								||	(		(w->applyelt != ENABLE_COMPLEX_VAL)
										&&	(w->applyelt > 0)
									)
							)
					)
				{
					listbox->AddString(RESSTRING(NA),1);
				}else
				{
					int t=w->etas/60;
					if (comboindex == L_ETA)
					{
						sprintf(buffer,"%02i:%02i",t/60,t%60);
						listbox->AddString(buffer,1);
					}else
					{
						int targtime=Todays_Packages[packnum][wavenum].targettime/60;
						t-=targtime;
						if (t>=0)
							sprintf(buffer,"+%02i:%02i",t/60,t%60);
						else
							sprintf(buffer,"-%02i:%02i",-t/60,-t%60);
						listbox->AddString(buffer,1);
					}
				}
				break;
			}
		}
	tabletype[addrow]=t;
	tablewp[addrow]=u;
	if (u==Todays_Packages.hiwp)
		currrow=addrow;
}



BOOL CWPGround::DestroyWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CDialog::DestroyWindow();
}

void CWPGround::OnSelectWaypointlist(long row, long column) 
{
	if (!Todays_Packages[packnum][wavenum].firstwp || !Todays_Packages[packnum][wavenum][groupnum].uid)
		return;
	CRListBox* rlistbox=GETDLGITEM(IDC_WAYPOINTLIST);
	switch 	(tabletype[row])
	{	//HEADER=-2,TITLE=-1,BEFORE=0,ATTACK1,BETWEEN,ATTACK2,AFTER,POSTRV
	case HEADER:
	{
	}
	break;
	case TITLE:
	{
 			parent->RefreshData(CWPShare::RADIODISABLE);
	}
	break;
	case BEFORE:
	case ATTACK1:
	case BETWEEN:
	case ATTACK2:
	case AFTER:
	case MAINROUTE:
	case POSTRV:
	{
			UniqueID u=tablewp[row];
			if (row==currrow)
			{
				if  (		(tabletype[row] != MAINROUTE)
						&&	(tabletype[row] != POSTRV)
					)
	  			parent->RefreshData(CWPShare::RADIODETAIL);
			}
			else
			{
				currrow = row;
				RefreshDetail(u);
				SetButtons(row);
				RDialog::m_pView->SetHiLightInfo(packnum,  wavenum, groupnum, u);
//				RDialog::m_pView->m_mapdlg.ResetIcon(u);
				if  (		(tabletype[row] != MAINROUTE)
						&&	(tabletype[row] != POSTRV)
					)
		  			parent->RefreshData(CWPShare::RADIOENABLE);
				else
		  			parent->RefreshData(CWPShare::RADIODISABLE);



			}

	}
	}
	currrow=row;

}
void	CWPGround::RefreshButtons(int effect)
{
	if (!wpbuttons)
		for (wpbuttons=(RowanDialog*)parent->fchild;wpbuttons;wpbuttons=(RowanDialog*)wpbuttons->sibling)
			breakif(wpbuttons->packnum==-1);
	wpbuttons->RefreshData(effect);
}
void CWPGround::SetButtons(long row)
{
	UniqueID u=tablewp[row+1];

	if (u)
	{
		switch 	(tabletype[row])
		{	//HEADER=-2,TITLE=-1,BEFORE=0,ATTACK1,BETWEEN,ATTACK2,AFTER,POSTRV
			case HEADER:
			{
			}
			break;
			case TITLE:
			{
			}
			break;
			case BEFORE:
			case BETWEEN:
			case AFTER:
			{
				if (!listfull && Todays_Packages.CanAddMoreWaypoints(packnum))
					RefreshButtons(CWPShare::INSONDELON);
				else
					RefreshButtons(CWPShare::INSOFFDELON);
				break;
			}
			case ATTACK1:
			case ATTACK2:
			case MAINROUTE:
			{
				if (!listfull && Todays_Packages.CanAddMoreWaypoints(packnum))
					RefreshButtons(CWPShare::INSONDELOFF);
				else
					RefreshButtons(CWPShare::INSOFFDELOFF);
				break;
			}
			case POSTRV:
			{
				RefreshButtons(CWPShare::INSOFFDELOFF);
				break;
			}
		}
	}
}

void CWPGround::OnDelete() 
{
	if (!Todays_Packages[packnum][wavenum].firstwp || !Todays_Packages[packnum][wavenum][groupnum].uid)
		return;
	if (tabletype[currrow]!=BEFORE && tabletype[currrow]!=BETWEEN && tabletype[currrow]!=AFTER)
		return;
	// TODO: Add your control notification handler code here
	UniqueID u=tablewp[currrow];
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
				Todays_Packages[packnum][wavenum].firstwp=u;
			delete wp;
			Todays_Packages[packnum].wpsused--;
			Persons2::delUID(u);
//			if (currrow!=1)
//			{
//				currrow--;
//				u=listentries[currrow];
//				RDialog::m_pView->SetHiLightInfo(packnum, wavenum, 0, u);
//				//RDialog::m_pView->m_mapdlg.ResetIcon(u);
//				RefreshDetail(u);
//			}

			RDialog::m_pView->m_mapdlg.Invalidate();

			DescribeTargetRoute();
		}
	}
}



void	CWPGround::RefreshData(int childnum)
{
	switch (childnum)
	{
		case WPDetail::DATA:
		{
			DescribeTargetRoute();
			break;
		}
		case WPDetail::NEXT:
		{
			//change selected option and refresh detail!
			currrow++;
			CRListBox* rlistbox=GETDLGITEM(IDC_WAYPOINTLIST);
			rlistbox->SetHilightRow(currrow);
			RDialog::m_pView->SetHiLightInfo(packnum, wavenum, 0, tablewp[currrow]);
//			RDialog::m_pView->m_mapdlg.ResetIcon(tablewp[currrow]);
			switch 	(tabletype[currrow])
			{
			  	case BEFORE:
				case ATTACK1:
				case BETWEEN:
				case ATTACK2:
				case AFTER:
				{
					RefreshDetail(tablewp[currrow]);
					break;
				}
				default:
				{
					parent->RefreshData(CWPShare::RADIOLIST);
					parent->RefreshData(CWPShare::RADIODISABLE);
					break;
				}
			}
		break;
		}
		case WPDetail::PREV:
		{
			//change selected option and refresh detail!	
			currrow--;
			CRListBox* rlistbox=GETDLGITEM(IDC_WAYPOINTLIST);
			rlistbox->SetHilightRow(currrow);
			RDialog::m_pView->SetHiLightInfo(packnum, wavenum, 0, tablewp[currrow]);
//			RDialog::m_pView->m_mapdlg.ResetIcon(tablewp[currrow]);

			switch 	(tabletype[currrow])
			{
			  	case BEFORE:
				case ATTACK1:
				case BETWEEN:
				case ATTACK2:
				case AFTER:
				{
					RefreshDetail(tablewp[currrow]);
					break;
				}
				default:
				{
					parent->RefreshData(CWPShare::RADIOLIST);
					parent->RefreshData(CWPShare::RADIODISABLE);
					break;
				}
			}
		break;
		}
	}
}

void CWPGround::OnInsert() 
{
	if (!Todays_Packages[packnum][wavenum].firstwp || !Todays_Packages[packnum][wavenum][groupnum].uid)
		return;
	if (tabletype[currrow]==HEADER || tabletype[currrow]==TITLE || tabletype[currrow]==POSTRV)
		return;
	// TODO: Add your control notification handler code here
	int	relfromcode=SGR_Pack_Takeoff,reltocode=SGR_Pack_Takeoff;
	COORDS3D	*posfrom=NULL,*posto=NULL;
	COORDS3D	*relfrom=NULL,*relto=NULL;
	info_waypoint	*prev=NULL,*next=NULL;
	UniqueID u=tablewp[currrow];
	TableType t=tabletype[currrow];
	switch (t)
	{
		case MAINROUTE:	t=BEFORE;	break;
		case ATTACK1:	t=BETWEEN;	u=keys[t];	break;
		case ATTACK2:	t=AFTER;	u=keys[t];	break;
		case BETWEEN:
		case BEFORE:	
		case AFTER:		break;
	}
	info_waypoint *p=
		prev=
			*Persons2::ConvertPtrUID(u);
	posfrom=&p->World;
	info_waypoint* base=*Persons2::ConvertPtrUID(keys[BEFORE]);

	info_waypoint *n=
		next=
			*Persons2::ConvertPtrUID(p->nextwp);
	posto=&n->World;

//Ok.. make a waypoint. 
//Set its position to midway between posfrom and posto
//Set the description of its position to the same place but
//using relto and relfrom to drive it!!!!
	UniqueID rv;
	info_waypoint* wp0=new info_waypoint;
	Todays_Packages[packnum].wpsused++;

	wp0->range=1000;
	wp0->position.MakeGRRelWorldPos(-base->uid.Evaluate());
	wp0->prevwp=tablewp[currrow];
	wp0->nextwp=p->nextwp;
	wp0->uniqueID.count=
		rv=Persons2::assignuid(WayPointBAND);
	p->nextwp=n->prevwp=rv;
	Persons2::tabulateUID(wp0);
	wp0->World.X=(posfrom->X+posto->X)/2;
	wp0->World.Y=(posfrom->Y+posto->Y)/2;
	wp0->World.Z=(posfrom->Z+posto->Z)/2;
	wp0->position.RecalcDeltasToMatch(wp0->World);
	int row=currrow;
	while (tabletype[row]!=TITLE)	row--;
	row=tablewp[row];
	wp0->applygroup=groupnum;
	if (((row/4)&7)!=7)
		wp0->applyflight=row/4;
	if ((row&3)!=3)
		wp0->applyelt=row&3;

//	RDialog::m_pView->SetHiLightInfo(packnum, wavenum, groupnum, tablewp[currrow]);
	RDialog::m_pView->SetHiLightInfo(packnum, wavenum, groupnum, rv);
//	RDialog::m_pView->m_mapdlg.ResetIcon(u);
	RDialog::m_pView->m_mapdlg.Invalidate();

	Todays_Packages[packnum].CalcWPTimes(wavenum);
	DescribeTargetRoute();

}

void CWPGround::OnMove() 
{
	if (!Todays_Packages[packnum][wavenum].firstwp || !Todays_Packages[packnum][wavenum][groupnum].uid)
		return;
	// TODO: Add your control notification handler code here
	if (tablewp[currrow])
		RDialog::m_pView->ZoomToUID(UniqueID(tablewp[currrow+1]),RDialog::m_pView->m_zoom);

}



void CWPGround::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	CRect rect3;
	GetClientRect(rect3);
	rect3.top+=30;
	CRListBox* rlistbox;
	rlistbox=GETDLGITEM(IDC_WAYPOINTLIST);
	if (rlistbox->m_hWnd)
		rlistbox->MoveWindow(rect3);
	
}

void CWPGround::OnSelectTab(RDialog* tab)
{
	DescribeTargetRoute();
}

void CWPGround::OnTextChangedType(LPCTSTR text) 
{
 	CRCombo* combo=GETDLGITEM(IDC_TYPE);
	comboindex=combo->GetIndex();
	DescribeTargetRoute();

}

BOOL CWPGround::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CRCombo* combo;
	combo=GETDLGITEM(IDC_TYPE);
	combo->Clear();
	combo->RESCOMBO(POSITION,4)->SetIndex(comboindex);

	combo=GETDLGITEM(IDC_LEVEL);
	combo->Clear();
	combo->RESCOMBO(GROUP,3)->SetIndex(groupingmode);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CWPGround::OnTextChangedLevel(LPCTSTR text) 
{
	CRCombo* combo=GETDLGITEM(IDC_LEVEL);
	groupingmode=combo->GetIndex();
	DescribeTargetRoute();

	
}
