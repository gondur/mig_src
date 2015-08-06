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

// Bases.cpp : implementation file
//
#include "stdafx.h"
#include "mig.h"

#include "Bases.h"
#include "RRadio.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#ifndef THIS_FILE_DEFINED
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif

/////////////////////////////////////////////////////////////////////////////
// CBases dialog


CBases::CBases(CWnd* pParent /*=NULL*/)
	: RowanDialog(CBases::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBases)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BOOL CBases::AfInUse(int af)
{
 	for (int i=0;i<PILOTABLE_SQUADRONS;i++)
	{
		if (occupiedaf[i] == af)
			return TRUE;
	}
	return(FALSE);

}
void CBases::FillOccupiedAf()
{
	for (int i=0;i<PILOTABLE_SQUADRONS;i++)
		occupiedaf[i] = ENTRYNOTUSED;
	int j = 0;
	for (i=0;i<PILOTABLE_SQUADRONS;i++)
	{
		if (MMC.squad[i].ac_total_avail > 0)
			if (!AfInUse(MMC.squad[i].airfieldindex))
				occupiedaf[j++] = MMC.squad[i].airfieldindex;
	}

}
int CBases::FindFreeSlots(int afnum)
{
	int free =0;
 	for (int i=0;i<PILOTABLE_SQUADRONS;i++)
	{
		if  (	(		(		(MMC.squad[i].airfieldindex == afnum)
							&&	(MMC.squad[i].movetoairfieldindex == -1)
						)
					||	(		(MMC.squad[i].movetoairfieldindex == afnum)
						)
				)
				&&
				(MMC.squad[i].ac_total_avail > 0)

			)
			free++;
	}
	free = SupplyTree::airfieldinfo[afnum].capacity - free;
	return (free);
	
}
void CBases::UpdateAirfieldDisplay(int listindex, int afnum)
{
	char buffer[10];
	CREdtBt* b=GETDLGITEM(IDC_AFBUTTON1+listindex*2);
	b->SetFontNum(-9);
	b->SetCaption(GetTargName(SupplyTree::airfieldinfo[afnum].airfield));


	CRStatic*   s=GETDLGITEM(IDC_AFINFO1+listindex*2);
	CRect rect;
	GetClientRect(rect);
	ClientToScreen(rect);
	CRect currpos;
	s->GetWindowRect(currpos);
	currpos-=rect.TopLeft();
	currpos.right = currpos.left + SupplyTree::airfieldinfo[afnum].capacity * 50;
	s->MoveWindow(currpos);


	int slotsused =  SupplyTree::airfieldinfo[afnum].capacity  - FindFreeSlots(afnum);
	int type = SupplyTree::airfieldinfo[afnum].type;
	if (SupplyTree::airfieldinfo[afnum].type == AFT_PROPONLY)
		s->SetPictureFileNum(FIL_ICON_F51_0_3+slotsused);
	else
		s->SetPictureFileNum(FIL_ICON_F86_0_3+slotsused);
	s->SetString("");
}
void CBases::PositionAfDisplay(int listindex)
{
	currright = 200;
	currbottom = currtop + 30;
	currleft = 8;
	CREdtBt* b=GETDLGITEM(IDC_AFBUTTON1+listindex*2);
	CRect rect;
	GetClientRect(rect);
	ClientToScreen(rect);
	CRect currpos;
	b->GetWindowRect(currpos);
	currpos-=rect.TopLeft();
	currpos.left = currleft;
	currpos.top = currtop;
	currpos.right = currright;
	currpos.bottom = currbottom;
	b->MoveWindow(currpos);

	CRStatic*   s=GETDLGITEM(IDC_AFINFO1+listindex*2);
	s->GetWindowRect(currpos);
	currpos-=rect.TopLeft();
	currpos.left = currright+ 16;
	currpos.top = currtop + 8;
	currpos.right = currright + 200;
	currpos.bottom = currbottom;
	s->MoveWindow(currpos);



	currtop += 34;

}
void CBases::PositionSquadDisplay(int listindex)
{
	currright = 112;
	currbottom = currtop + 24;
	currleft = 24;
	CREdtBt* b=GETDLGITEM(IDC_AFBUTTON1+listindex*2);
	CRect rect;
	GetClientRect(rect);
	ClientToScreen(rect);
	CRect currpos;
	b->GetWindowRect(currpos);
	currpos-=rect.TopLeft();
	currpos.left = currleft;
	currpos.top = currtop;
	currpos.right = currright;
	currpos.bottom = currbottom;
	b->MoveWindow(currpos);

	CRStatic*   s;
	s=GETDLGITEM(IDC_AFINFO1+listindex*2);
	s->GetWindowRect(currpos);
	currpos-=rect.TopLeft();
	currpos.left = currright + 16;
	currpos.top = currtop + 4;
	currpos.right = currright+ 3600;
	currpos.bottom = currbottom;
	s->MoveWindow(currpos);

	currtop += 26;


}
void CBases::AddAirfield(int& listindex, int afnum)
{
	PositionAfDisplay(listindex);
	UpdateAirfieldDisplay(listindex, afnum);
	afuses[listindex++]=afnum;

}
BOOL CBases::MoveValid(int& srcline, int& destline)
{
//	srcline--;
//	destline--;
	while	(		(destline >= 0)
				&&	(afuses[destline] <0)		//ie squadron
			)
			destline--;
	int type = SupplyTree::airfieldinfo[afuses[destline]].type;
	int actype =afuses[srcline];
	int test = afuses[destline];
	if (		(destline < 0)
			||	(SupplyTree::airfieldinfo[afuses[destline]].nationality != NAT_BLUE)			
			||	(		(SupplyTree::airfieldinfo[afuses[destline]].type < AFT_JET)
					&&	(afuses[srcline] >= -4)	//ie not a prop	
				)
			||	(FindFreeSlots(afuses[destline]) <= 0)
		)
			return(FALSE);
	else
			return(TRUE);

}
void CBases::UpdateSquadronMovement(int srcline, int destline)
{
	if (MoveValid(srcline, destline))
	{
		MMC.squad[-afuses[srcline]-1].movetoairfieldindex = afuses[destline];
		DisplaySquadronMovement(srcline, (-afuses[srcline]-1));
//DEADCODE RDH 06/06/99 		UpdateAirfieldDisplay(destline, afuses[destline]);
//DEADCODE RDH 06/06/99 		while	(		(srcline >= 0)
//DEADCODE RDH 06/06/99 				&&	(afuses[srcline] < 0)		//ie squadron
//DEADCODE RDH 06/06/99 			)
//DEADCODE RDH 06/06/99 			srcline--;
//DEADCODE RDH 06/06/99 		if (srcline >= 0)
//DEADCODE RDH 06/06/99 			UpdateAirfieldDisplay(srcline, afuses[srcline]);


		for (int i = 0; i < maxlines;i++)
			if (afuses[i] >= 0)
				UpdateAirfieldDisplay(i, afuses[i]);

	}else
	{
		MMC.squad[(-afuses[srcline] - 1)].movetoairfieldindex = afuses[destline];
		//invalid move dialog
	}
}				

void CBases::DisplaySquadronMovement(int listindex, int sqnum)
{
	CRStatic*   s;
	s=GETDLGITEM(IDC_AFINFO1+listindex*2);

//	CRect rect;
//	GetClientRect(rect);
//	ClientToScreen(rect);
//	CRect currpos;
//	s->GetWindowRect(currpos);
//	currpos-=rect.TopLeft();
//	currpos.left+=8;
//	s->MoveWindow(currpos);

	if	(MMC.squad[sqnum].movetoairfieldindex == -1)
		s->SetString("");
	else if ( MMC.squad[sqnum].movetoairfieldindex == MMC.squad[sqnum].airfieldindex)
	{
		s->SetPictureFileNum(FIL_NULL);
		s->SetString(RESSTRING(MOVECANCELLED));
	}else
	{
		s->SetPictureFileNum(FIL_ICON_ARROW);
		s->SetString("             "+GetTargName(SupplyTree::airfieldinfo[MMC.squad[sqnum].movetoairfieldindex].airfield));
	}


}
void CBases::AddSquadron(int& listindex, int sqnum)
{
	CREdtBt* b;
	b=GETDLGITEM(IDC_AFBUTTON1+listindex*2);
	b->SetFontNum(-7);

//	CRect rect;
//	GetClientRect(rect);
//	ClientToScreen(rect);
//	CRect currpos;
//	b->GetWindowRect(currpos);
//	currpos-=rect.TopLeft();
//	currpos.left+=8;
//	b->MoveWindow(currpos);

	PositionSquadDisplay(listindex);

	b->SetCaption(RESLIST(SQ_BF_F86A,sqnum));
	b->SetDragAndDropID(listindex);
	DisplaySquadronMovement(listindex,sqnum);
	afuses[listindex]=-sqnum-1;
	listindex++;
}

BOOL CBases::AirfieldValid(int afnum)
{
	int		i = 0;
	BOOL	valid = TRUE;
	if	(		(afnum >= 0)
			&&	(afnum < SupplyTree::AIRFIELDSINWORLD)
			&&	(SupplyTree::airfieldinfo[afnum].nationality == NAT_BLUE)
		)
	{
		while (		(i <	DIALOGROWS)
				&&	(valid)
			  )
		{
			if	(afuses[i] == afnum)
				valid = FALSE;
			else
				i++;
		}

	}else
		valid = FALSE;

	return (valid);

}
void CBases::DoDataExchange(CDataExchange* pDX)		//AirFieldInfo
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBases)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	DDX_Control(pDX,IDC_AFBUTTON1,m_IDC_AFBUTTON1);
	DDX_Control(pDX,IDC_AFINFO1,m_IDC_AFINFO1);
	DDX_Control(pDX,IDC_AFBUTTON2,m_IDC_AFBUTTON2);
	DDX_Control(pDX,IDC_AFINFO2,m_IDC_AFINFO2);
	DDX_Control(pDX,IDC_AFBUTTON3,m_IDC_AFBUTTON3);
	DDX_Control(pDX,IDC_AFINFO3,m_IDC_AFINFO3);
	DDX_Control(pDX,IDC_AFBUTTON4,m_IDC_AFBUTTON4);
	DDX_Control(pDX,IDC_AFINFO4,m_IDC_AFINFO4);
	DDX_Control(pDX,IDC_AFBUTTON5,m_IDC_AFBUTTON5);
	DDX_Control(pDX,IDC_AFINFO5,m_IDC_AFINFO5);
	DDX_Control(pDX,IDC_AFBUTTON6,m_IDC_AFBUTTON6);
	DDX_Control(pDX,IDC_AFINFO6,m_IDC_AFINFO6);
	DDX_Control(pDX,IDC_AFBUTTON7,m_IDC_AFBUTTON7);
	DDX_Control(pDX,IDC_AFINFO7,m_IDC_AFINFO7);
	DDX_Control(pDX,IDC_AFBUTTON8,m_IDC_AFBUTTON8);
	DDX_Control(pDX,IDC_AFINFO8,m_IDC_AFINFO8);
	DDX_Control(pDX,IDC_AFBUTTON9,m_IDC_AFBUTTON9);
	DDX_Control(pDX,IDC_AFINFO9,m_IDC_AFINFO9);
	DDX_Control(pDX,IDC_AFBUTTON10,m_IDC_AFBUTTON10);
	DDX_Control(pDX,IDC_AFINFO10,m_IDC_AFINFO10);
	DDX_Control(pDX,IDC_AFBUTTON11,m_IDC_AFBUTTON11);
	DDX_Control(pDX,IDC_AFINFO11,m_IDC_AFINFO11);
	DDX_Control(pDX,IDC_AFBUTTON12,m_IDC_AFBUTTON12);
	DDX_Control(pDX,IDC_AFINFO12,m_IDC_AFINFO12);
	DDX_Control(pDX,IDC_AFBUTTON13,m_IDC_AFBUTTON13);
	DDX_Control(pDX,IDC_AFINFO13,m_IDC_AFINFO13);
	DDX_Control(pDX,IDC_AFBUTTON14,m_IDC_AFBUTTON14);
	DDX_Control(pDX,IDC_AFINFO14,m_IDC_AFINFO14);
	DDX_Control(pDX,IDC_AFBUTTON15,m_IDC_AFBUTTON15);
	DDX_Control(pDX,IDC_AFINFO15,m_IDC_AFINFO15);
	DDX_Control(pDX,IDC_AFBUTTON16,m_IDC_AFBUTTON16);
	DDX_Control(pDX,IDC_AFINFO16,m_IDC_AFINFO16);
	DDX_Control(pDX,IDC_AFBUTTON17,m_IDC_AFBUTTON17);
	DDX_Control(pDX,IDC_AFINFO17,m_IDC_AFINFO17);
	DDX_Control(pDX,IDC_AFBUTTON18,m_IDC_AFBUTTON18);
	DDX_Control(pDX,IDC_AFINFO18,m_IDC_AFINFO18);
	DDX_Control(pDX,IDC_AFBUTTON19,m_IDC_AFBUTTON19);
	DDX_Control(pDX,IDC_AFINFO19,m_IDC_AFINFO19);
	DDX_Control(pDX,IDC_AFBUTTON20,m_IDC_AFBUTTON20);
	DDX_Control(pDX,IDC_AFINFO20,m_IDC_AFINFO20);
	DDX_Control(pDX,IDC_AFBUTTON21,m_IDC_AFBUTTON21);
	DDX_Control(pDX,IDC_AFINFO21,m_IDC_AFINFO21);
	DDX_Control(pDX,IDC_AFBUTTON22,m_IDC_AFBUTTON22);
	DDX_Control(pDX,IDC_AFINFO22,m_IDC_AFINFO22);
	DDX_Control(pDX,IDC_AFBUTTON23,m_IDC_AFBUTTON23);
	DDX_Control(pDX,IDC_AFINFO23,m_IDC_AFINFO23);
	//}}AFX_DATA_MAP

	currleft = 8;currtop = 8;
	CREdtBt* b;
	CRStatic*   s;
	int listindex;
 	for (listindex=0;listindex<DIALOGROWS;listindex++)
	{
		afuses[listindex] = ENTRYNOTUSED;
		CREdtBt* b=GETDLGITEM(IDC_AFBUTTON1+listindex*2);
		b->ShowWindow(SW_SHOW);
		CRStatic*   s=GETDLGITEM(IDC_AFINFO1+listindex*2);
		s->ShowWindow(SW_SHOW);
	}
	   

	FillOccupiedAf();
	int i = 0, j = 0;
		//add occupied af
	listindex=0;
	while	(		(occupiedaf[i] != ENTRYNOTUSED)
				&&	(i < PILOTABLE_SQUADRONS)
			)
	{
		//add airfield
		AddAirfield(listindex, occupiedaf[i]);
		//add squadrons
	 	for (j=0;j<PILOTABLE_SQUADRONS;j++)
			if (MMC.squad[j].ac_total_avail > 0)
				if (MMC.squad[j].airfieldindex == occupiedaf[i])
					AddSquadron(listindex, j);
		 i++;
		 //provide a gap
		currtop += 26;

	}
	//add near airfields
	for (j=0;j<PILOTABLE_SQUADRONS;j++)
	{
		if (AirfieldValid(MMC.squad[j].airfieldindex + 1))
			AddAirfield(listindex, MMC.squad[j].airfieldindex + 1);
		if (AirfieldValid(MMC.squad[j].airfieldindex - 1))
			AddAirfield(listindex, MMC.squad[j].airfieldindex - 1 );
	}// add rest
 	for (j=0;j<SupplyTree::AIRFIELDSINWORLD;j++)
	{
		if	(		(AirfieldValid(j))
				&&	(listindex < DIALOGROWS)
			)
				AddAirfield(listindex, j);
	}
	maxlines = listindex;
	//hide rest of buttons
	while	(listindex<DIALOGROWS)
	{
		CREdtBt* b=GETDLGITEM(IDC_AFBUTTON1+listindex*2);
		b->ShowWindow(SW_HIDE);
		CRStatic*   s=GETDLGITEM(IDC_AFINFO1+listindex*2);
		s->ShowWindow(SW_HIDE);
		listindex++;
	}


}


BEGIN_MESSAGE_MAP(CBases, CDialog)
	//{{AFX_MSG_MAP(CBases)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBases message handlers

BOOL CBases::OnInitDialog() 
{
	CDialog::OnInitDialog();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}



BEGIN_EVENTSINK_MAP(CBases, CDialog)
	ON_EVENT_RANGE(CBases, IDC_AFBUTTON1, IDC_AFBUTTON30, 1 /* Clicked */, OnClickedAfButtonID, VTS_I4)
	ON_EVENT_RANGE(CBases, IDC_AFBUTTON1, IDC_AFBUTTON30, 2 /* CanAcceptDrop */, OnCanAcceptDropAfbuttonID, VTS_I4 VTS_I4 VTS_PBOOL)
	ON_EVENT_RANGE(CBases, IDC_AFBUTTON1, IDC_AFBUTTON30, 3 /* DroppedOn */, OnDroppedOnAfbuttonID, VTS_I4 VTS_I4)
    //{{AFX_EVENTSINK_MAP(CBases)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void	CBases::OnClickedAfButtonID(int id)
{
	int butnum=(id-IDC_AFBUTTON1)/2;
	assert(butnum>=0 && butnum<30);
	OnClickedAfButton(butnum+1);
}
void CBases::OnClickedAfButton(int line)
{
	int entry = afuses[line - 1];

	if (entry >= 0)
	{	
	   MainToolBar().OpenDossier(SupplyTree::airfieldinfo[entry].airfield);

//		if (LoggedChild(0))
//			CloseLoggedChildren();
//		LogChild(0,CTargetDossier::MakeSheet(CRect(180,180,0,0),SupplyTree::airfieldinfo[entry].airfield));
	}else
//		if (LoggedChild(1))
//		{
//	 		CRTabs* tab=(CRTabs*)LoggedChild(1)->fchild->fchild->GetDlgItem(IDJ_TABCTRL);
//			tab->SelectTab(-entry-1);
//		}else
//		{
			MainToolBar().OpenSquads(-entry-1);
//			RDialog* d=CSqdnlist::Make();
//			LogChild(1,d);
//			CRTabs* tab=(CRTabs*)d->fchild->GetDlgItem(IDJ_TABCTRL);
//			tab->SelectTab(-entry-1);
//		}
}

void CBases::OnCanAcceptDropAfbuttonID(int targid,long sourcedropID, BOOL FAR* pReply) 
{
	int butnum=(targid-IDC_AFBUTTON1)/2;
	assert(butnum>=0 && butnum<30);
	int entry = afuses[butnum];
	int source = (int) sourcedropID;
	if (MoveValid(source,butnum))
		*pReply= (entry>=0);
	else
		*pReply = false;
}

void CBases::OnDroppedOnAfbuttonID(int targid,long sourcedropID) 
{
	int butnum=(targid-IDC_AFBUTTON1)/2;
	assert(butnum>=0 && butnum<30);
	int entry = afuses[butnum];
	UpdateSquadronMovement(sourcedropID,butnum);
		
}

