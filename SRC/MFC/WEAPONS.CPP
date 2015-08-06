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

// Weapons.cpp : implementation file
//

#include "stdafx.h"
#include "mig.h"
#include "Weapons.h"
#include "3dinstr.h"
#include	"weappak.h"
#include "bfnumber.h"
#include	"persons2.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#ifndef THIS_FILE_DEFINED
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif

/////////////////////////////////////////////////////////////////////////////
// CWeapons dialog


CWeapons::CWeapons(int pack,int wave,int grp,int flight,CWnd* pParent /*=NULL*/)
	: RowanDialog(CWeapons::IDD, pParent)
{
	SetProjSpecific(pack,wave,grp,flight);
	//{{AFX_DATA_INIT(CWeapons)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	thisacweaps=GetWeapList(pack,wave,grp,flight);

}

lchpak*	CWeapons::GetWeapList(int pack,int wave,int grp,int flight)
{
	return	Todays_Packages[pack][wave][grp].GetWeapList();
}

lchpak*  Profile::Group::GetWeapList()
{
	int sqnum=squadron;
	sqnum=Persons3::Squad2Type(sqnum);
	if (sqnum<PT_F86WEAPPAK)
		sqnum=PT_F86WEAPPAK;
	elseif (sqnum>PT_MIGWEAPPAK)
		sqnum=PT_MIGWEAPPAK;
	return ShpToWeapPak[sqnum-PT_F86WEAPPAK].weappack;
}

int		CWeapons::GetWeapIndex(int pack,int wave,int grp,int flight)
{
	return	Todays_Packages[pack][wave][grp].GetWeapIndex(flight);
}
int	Profile::Group::GetWeapIndex(int flight)
{
	info_airgrp* ag=*Persons2::ConvertPtrUID(uid);
	return ag->bombs.Evaluate(flight);
}
int		CWeapons::GetWeapName(int pack,int wave,int grp,int flight)
{
	lchpak* p=GetWeapList(pack,wave,grp,flight);
	int ind=GetWeapIndex(pack,wave,grp,flight);
	return p[ind].WeapSetName;
}
int		CWeapons::GetExtFuel(int pack,int wave,int grp,int flight)
{
	return	Todays_Packages[pack][wave][grp].GetExtFuel(flight);
}

int		Profile::Group::GetExtFuel(int flight)
{
	lchpak* p=GetWeapList();
	int ind=GetWeapIndex(flight);
	int i = 0;
	int fuel;
	while	(		(i < 4)
				&&	(p[ind].stationlaunchers[i].lnchrtype != LT_FUEL)
			)
			i++;
   if (p[ind].stationlaunchers[i].lnchrtype == LT_FUEL)
	   fuel = p[ind].stationlaunchers[i].ammocount;
   else
	   fuel = 0;
  //MArk tells me that this figure is for one wing
   fuel = 2* fuel;
   return (fuel);
}

//////////////////////////////////////////////////////////////////////////
//Get Stores Drag	//CSB 17/06/99	
int		Profile::Group::GetStoresDrag(int flight)	//CSB 17/06/99	
{
	lchpak* p=GetWeapList();
	int ind=GetWeapIndex(flight);
	return (p[ind].TotalDrag);
	   
}
//////////////////////////////////////////////////////////////////////////


void CWeapons::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWeapons)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	DDX_Control(pDX,IDC_WEAPLIST,m_IDC_WEAPLIST);
	DDX_Control(pDX,IDC_TSQUAD,	m_IDC_TSQUAD);
	DDX_Control(pDX,IDC_TSQUAD2,m_IDC_TSQUAD2);
	DDX_Control(pDX,IDC_TSQUAD3,m_IDC_TSQUAD3);
	DDX_Control(pDX,IDJ_TITLE,m_IDJ_TITLE);

	//}}AFX_DATA_MAP
	CRListBox* rlistbox=GETDLGITEM(IDC_WEAPLIST);
	for (int i=0;thisacweaps[i].stationlaunchers[0].ammocount;i++)
		rlistbox->AddString(LoadResString(thisacweaps[i].WeapSetName),0);
	int weapnum=GetWeapIndex(packnum,wavenum,groupnum,acnum);
	rlistbox->SetHilightRow(weapnum);
	CRStatic* stat=GETDLGITEM(IDC_TSQUAD);
	if (thisacweaps[weapnum].StringResources[0][1])
		stat->SetString(CSprintf(LoadResString(thisacweaps[weapnum].StringResources[0][0]),thisacweaps[weapnum].StringResources[0][1]));
	else
		stat->SetString("");
	stat=GETDLGITEM(IDC_TSQUAD2);
	if (thisacweaps[weapnum].StringResources[1][1])
		stat->SetString(CSprintf(LoadResString(thisacweaps[weapnum].StringResources[1][0]),thisacweaps[weapnum].StringResources[1][1]));
	else
		stat->SetString("");
	stat=GETDLGITEM(IDC_TSQUAD3);
	if (thisacweaps[weapnum].StringResources[2][1])
		stat->SetString(CSprintf(LoadResString(thisacweaps[weapnum].StringResources[2][0]),thisacweaps[weapnum].StringResources[2][1]));
	else
		stat->SetString("");
}

void	CWeapons::OnOK()
{
	info_airgrp* ag=*Persons2::ConvertPtrUID(Todays_Packages[packnum][wavenum][groupnum].uid);
	CRListBox*	l=GETDLGITEM(IDC_WEAPLIST);
	ag->bombs[(int)acnum]=l->GetHilightRow();
	if (acnum==Todays_Packages[packnum][wavenum][groupnum].numflights-1)
		for(int ac=acnum+1;ac<4;ac++)
			ag->bombs[ac]=l->GetHilightRow();

	RefreshParent();
	CDialog::OnOK();
}

BEGIN_MESSAGE_MAP(CWeapons, CDialog)
	//{{AFX_MSG_MAP(CWeapons)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWeapons message handlers

BEGIN_EVENTSINK_MAP(CWeapons, CDialog)
    //{{AFX_EVENTSINK_MAP(CWeapons)
	ON_EVENT(CWeapons, IDC_WEAPLIST, 1 /* Select */, OnSelectWeaplist, VTS_I4 VTS_I4)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CWeapons::OnSelectWeaplist(long weapnum, long column) 
{
	// TODO: Add your control notification handler code here
	CRStatic* stat=GETDLGITEM(IDC_TSQUAD);
	if (thisacweaps[weapnum].StringResources[0][1])
		stat->SetString(CSprintf(LoadResString(thisacweaps[weapnum].StringResources[0][0]),thisacweaps[weapnum].StringResources[0][1]));
	else
		stat->SetString("");
	stat=GETDLGITEM(IDC_TSQUAD2);
	if (thisacweaps[weapnum].StringResources[1][1])
		stat->SetString(CSprintf(LoadResString(thisacweaps[weapnum].StringResources[1][0]),thisacweaps[weapnum].StringResources[1][1]));
	else
		stat->SetString("");
	stat=GETDLGITEM(IDC_TSQUAD3);
	if (thisacweaps[weapnum].StringResources[2][1])
		stat->SetString(CSprintf(LoadResString(thisacweaps[weapnum].StringResources[2][0]),thisacweaps[weapnum].StringResources[2][1]));
	else
		stat->SetString("");
}
void	CWeapons::ParentDialClosed(RDialog*,int rv)
{
	OnOK();
}
BOOL CWeapons::OnInitDialog() 
{
	CDialog::OnInitDialog();

	CRButton* title;
	title = GETDLGITEM(IDJ_TITLE);
	title->SetHelpButton(false);
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
