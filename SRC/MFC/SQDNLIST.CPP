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

// Sqdnlist.cpp : implementation file
//

#include "stdafx.h"
#include "mig.h"
#include "Sqdnlist.h"
#include "Pilots.h"
#include "RIP_List.h"
#include "personal.h"
#include "nose_art.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#ifndef THIS_FILE_DEFINED
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif

/////////////////////////////////////////////////////////////////////////////
// CSqdnlist dialog
RDialog*	CSqdnlist::Make()
{
	return	RDialog::MakeTopDialog(
//		CRect(700,400,0,0),
		::Place(POSN_MAX,POSN_MAX),
		DialList(DialBox(FIL_NULL/*IDB_BBC3*/,new CSquads,Edges(EDGE::ALIGN_MIN,EDGE::ALIGN_MIN,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE)),
								HTabBox(FIL_NULL,IdList(IDS_L_SQ_BF_F86A,IDS_SQ_BF_F86B,IDS_L_SQ_BF_F80,IDS_SQ_BF_F84,IDS_SQ_BF_F51),Edges(EDGE::ALIGN_MIN,EDGE::ALIGN_MIN,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE), 
		  							DialList(DialBox(FIL_MAP_SABRESQUADRON,new CSqdnListBack,Edges(EDGE::ALIGN_MIN,EDGE::ALIGN_MIN,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE)),
											DialBox(FIL_NULL,new CSqdnlist(SQ_F86A),Edges(EDGE::ALIGN_MIN,EDGE::ALIGN_MIN,EDGE::ALIGN_MAX,EDGE::ALIGN_MAX)),
											DialBox(FIL_NULL,new CSqdnlistBut(SQ_F86A),Edges(EDGE::ALIGN_MIN,EDGE::ALIGN_MAX,EDGE::ALIGN_MAX,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE))
											),
		  							DialList(DialBox(FIL_MAP_SABRESQUADRON,new CSqdnListBack,Edges(EDGE::ALIGN_MIN,EDGE::ALIGN_MIN,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE)),
											DialBox(FIL_NULL,new CSqdnlist(SQ_F86B),Edges(EDGE::ALIGN_MIN,EDGE::ALIGN_MIN,EDGE::ALIGN_MAX,EDGE::ALIGN_MAX)),
											DialBox(FIL_NULL,new CSqdnlistBut(SQ_F86B),Edges(EDGE::ALIGN_MIN,EDGE::ALIGN_MAX,EDGE::ALIGN_MAX,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE))
											),
		  							DialList(DialBox(FIL_MAP_SHOOTINGSTARSQUADRON,new CSqdnListBack,Edges(EDGE::ALIGN_MIN,EDGE::ALIGN_MIN,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE)),
											DialBox(FIL_NULL,new CSqdnlist(SQ_F80),Edges(EDGE::ALIGN_MIN,EDGE::ALIGN_MIN,EDGE::ALIGN_MAX,EDGE::ALIGN_MAX)),
											DialBox(FIL_NULL,new CSqdnlistBut(SQ_F80),Edges(EDGE::ALIGN_MIN,EDGE::ALIGN_MAX,EDGE::ALIGN_MAX,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE))
											),
		  							DialList(DialBox(FIL_MAP_THUNDERJETSQUADRON,new CSqdnListBack,Edges(EDGE::ALIGN_MIN,EDGE::ALIGN_MIN,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE)),
											DialBox(FIL_NULL,new CSqdnlist(SQ_F84),Edges(EDGE::ALIGN_MIN,EDGE::ALIGN_MIN,EDGE::ALIGN_MAX,EDGE::ALIGN_MAX)),
											DialBox(FIL_NULL,new CSqdnlistBut(SQ_F84),Edges(EDGE::ALIGN_MIN,EDGE::ALIGN_MAX,EDGE::ALIGN_MAX,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE))
											),
		  							DialList(DialBox(FIL_MAP_MUSTANGSQUADRON,new CSqdnListBack,Edges(EDGE::ALIGN_MIN,EDGE::ALIGN_MIN,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE)),
											DialBox(FIL_NULL,new CSqdnlist(SQ_F51),Edges(EDGE::ALIGN_MIN,EDGE::ALIGN_MIN,EDGE::ALIGN_MAX,EDGE::ALIGN_MAX)),
											DialBox(FIL_NULL,new CSqdnlistBut(SQ_F51),Edges(EDGE::ALIGN_MIN,EDGE::ALIGN_MAX,EDGE::ALIGN_MAX,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE))
											)
								)
					  		)				 
					     );



}

CSqdnlist::CSqdnlist(int squadnum,CWnd* pParent /*=NULL*/)
	: RowanDialog(CSqdnlist::IDD, pParent)
{
	SetProjSpecific(-1,-1,squadnum);

	//{{AFX_DATA_INIT(CSqdnlist)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}
bool CSqdnlist::CommsPlayer(int pos, int& i)
{
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

void CSqdnlist::PrintPilotName(CREdtBt& m_slot,int slot, int pilot)
{
	CREdtBt* b;
	int player;

	b=GETDLGITEM(slot);
	b->SetCaption(MakePilotName(MMC.Active_Pilots[pilot].name));
	b->SetDragAndDropID(IDC_TEXT_F0+slot);
	if (		(MMC.playersquadron == groupnum)
			&&	(MMC.playeracnum == (pilot - groupnum*24))
		)
	{
		b->SetForeColor(RGB(255,255,255));
		b->SetCaption(MMC.PlayerName);
	}else if (CommsPlayer((pilot - groupnum*24), player))
	{
		b->SetForeColor(RGB(0,255,0));
		b->SetCaption(DPlay::H2H_Player[player].name);
	}else
	{
		b->SetForeColor(RGB(255,255,0));
		b->SetCaption(RESSTRING(PILOTNAMES_START + MMC.Active_Pilots[pilot].name.nameref));
		b->SetDragAndDropID(IDC_TEXT_F0+slot);
	}

}
void CSqdnlist::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSqdnlist)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
//	DDX_Control(pDX,	IDC_TEXT_F0,	m_IDC_TEXT_[0]);		

	DDX_Control(pDX,	IDC_BUT_F0,		m_IDC_BUT_F[0]);		
	DDX_Control(pDX,	IDC_BUT_E0F0,	m_IDC_BUT_E[0][0]);		
	DDX_Control(pDX,	IDC_BUT_P0E0F0,	m_IDC_BUT_P[0][0][0]);		
	DDX_Control(pDX,	IDC_BUT_P1E0F0,	m_IDC_BUT_P[1][0][0]);		
	DDX_Control(pDX,	IDC_BUT_E1F0,	m_IDC_BUT_E[1][0]);		
	DDX_Control(pDX,	IDC_BUT_P0E1F0,	m_IDC_BUT_P[0][1][0]);		
	DDX_Control(pDX,	IDC_BUT_P1E1F0,	m_IDC_BUT_P[1][1][0]);		
//	DDX_Control(pDX,	IDC_TEXT_F1,	m_IDC_TEXT_[1]);		
	DDX_Control(pDX,	IDC_BUT_F1,		m_IDC_BUT_F[1]);		
	DDX_Control(pDX,	IDC_BUT_E0F1,	m_IDC_BUT_E[0][1]);		
	DDX_Control(pDX,	IDC_BUT_P0E0F1,	m_IDC_BUT_P[0][0][1]);		
	DDX_Control(pDX,	IDC_BUT_P1E0F1,	m_IDC_BUT_P[1][0][1]);		
	DDX_Control(pDX,	IDC_BUT_E1F1,	m_IDC_BUT_E[1][1]);		
	DDX_Control(pDX,	IDC_BUT_P0E1F1,	m_IDC_BUT_P[0][1][1]);		
	DDX_Control(pDX,	IDC_BUT_P1E1F1,	m_IDC_BUT_P[1][1][1]);		
//	DDX_Control(pDX,	IDC_TEXT_F2,	m_IDC_TEXT_[2]);		
	DDX_Control(pDX,	IDC_BUT_F2	,	m_IDC_BUT_F[2]);		
	DDX_Control(pDX,	IDC_BUT_E0F2,	m_IDC_BUT_E[0][2]);		
	DDX_Control(pDX,	IDC_BUT_P0E0F2,	m_IDC_BUT_P[0][0][2]);		
	DDX_Control(pDX,	IDC_BUT_P1E0F2,	m_IDC_BUT_P[1][0][2]);		
	DDX_Control(pDX,	IDC_BUT_E1F2,	m_IDC_BUT_E[1][2]);		
	DDX_Control(pDX,	IDC_BUT_P0E1F2,	m_IDC_BUT_P[0][1][2]);		
	DDX_Control(pDX,	IDC_BUT_P1E1F2,	m_IDC_BUT_P[1][1][2]);		
//	DDX_Control(pDX,	IDC_TEXT_F3,	m_IDC_TEXT_[3]);		
	DDX_Control(pDX,	IDC_BUT_F3,		m_IDC_BUT_F[3]);		
	DDX_Control(pDX,	IDC_BUT_E0F3,	m_IDC_BUT_E[0][3]);		
	DDX_Control(pDX,	IDC_BUT_P0E0F3,	m_IDC_BUT_P[0][0][3]);		
	DDX_Control(pDX,	IDC_BUT_P1E0F3,	m_IDC_BUT_P[1][0][3]);		
	DDX_Control(pDX,	IDC_BUT_E1F3,	m_IDC_BUT_E[1][3]);		
	DDX_Control(pDX,	IDC_BUT_P0E1F3,	m_IDC_BUT_P[0][1][3]);		
	DDX_Control(pDX,	IDC_BUT_P1E1F3,	m_IDC_BUT_P[1][1][3]);		
//	DDX_Control(pDX,	IDC_TEXT_F4,	m_IDC_TEXT_[4]);		
	DDX_Control(pDX,	IDC_BUT_F4,		m_IDC_BUT_F[4]);		
	DDX_Control(pDX,	IDC_BUT_E0F4,	m_IDC_BUT_E[0][4]);		
	DDX_Control(pDX,	IDC_BUT_P0E0F4,	m_IDC_BUT_P[0][0][4]);		
	DDX_Control(pDX,	IDC_BUT_P1E0F4,	m_IDC_BUT_P[1][0][4]);		
	DDX_Control(pDX,	IDC_BUT_E1F4,	m_IDC_BUT_E[1][4]);		
	DDX_Control(pDX,	IDC_BUT_P0E1F4,	m_IDC_BUT_P[0][1][4]);		
	DDX_Control(pDX,	IDC_BUT_P1E1F4,	m_IDC_BUT_P[1][1][4]);		
//	DDX_Control(pDX,	IDC_TEXT_F5,	m_IDC_TEXT_[5]);		
	DDX_Control(pDX,	IDC_BUT_F5,		m_IDC_BUT_F[5]);		
	DDX_Control(pDX,	IDC_BUT_E0F5,	m_IDC_BUT_E[0][5]);		
	DDX_Control(pDX,	IDC_BUT_P0E0F5,	m_IDC_BUT_P[0][0][5]);		
	DDX_Control(pDX,	IDC_BUT_P1E0F5,	m_IDC_BUT_P[1][0][5]);		
	DDX_Control(pDX,	IDC_BUT_E1F5,	m_IDC_BUT_E[1][5]);		
	DDX_Control(pDX,	IDC_BUT_P0E1F5,	m_IDC_BUT_P[0][1][5]);		
	DDX_Control(pDX,	IDC_BUT_P1E1F5,	m_IDC_BUT_P[1][1][5]);		


}


BEGIN_MESSAGE_MAP(CSqdnlist, CDialog)
	//{{AFX_MSG_MAP(CSqdnlist)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSqdnlist message handlers

BEGIN_EVENTSINK_MAP(CSqdnlist, CDialog)
 	ON_EVENT_RANGE(CBases, IDC_TEXT_F0, IDC_BUT_P1E1F5, 1 /* Clicked */, OnClickedSqButtonID, VTS_I4)
	ON_EVENT_RANGE(CBases, IDC_TEXT_F0, IDC_BUT_P1E1F5, 2 /* CanAcceptDrop */, OnCanAcceptDropSqbuttonID, VTS_I4 VTS_I4 VTS_PBOOL)
	ON_EVENT_RANGE(CBases, IDC_TEXT_F0, IDC_BUT_P1E1F5, 3 /* DroppedOn */, OnDroppedOnSqbuttonID, VTS_I4 VTS_I4)

    //{{AFX_EVENTSINK_MAP(CSqdnlist)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void	CSqdnlist::OnClickedSqButtonID(int id)
{
	int butnum=(id-IDC_TEXT_F0);
	assert(butnum>=0 && butnum<48);

	int pilot = 4 * (butnum/8);
	PilotDetails(pilot);

}

void CSqdnlist::OnCanAcceptDropSqbuttonID(int targid,long sourcedropID, BOOL FAR* pReply) 
{
	int butnum=(targid-IDC_TEXT_F0);
	assert(butnum>=0 && butnum<48);
	if (SwapValid(sourcedropID, targid))
		*pReply= true;
	else
		*pReply = false;
}

void CSqdnlist::OnDroppedOnSqbuttonID(int targid,long sourcedropID) 
{
	int butnum=(targid-IDC_TEXT_F0);
	assert(butnum>=0 && butnum<48);

	int srcbtn = (sourcedropID - IDC_TEXT_F0)%8;
	int destbtn = (butnum)%8;

	int srcflt = 4*((sourcedropID- IDC_TEXT_F0)/8);
	int destflt = 4*(butnum/8);

	int srcele = 2*((sourcedropID- IDC_TEXT_F0)/4);
	int destele = 2*(butnum/4);

	int srcplt =  srcflt;
	int destplt = destflt;

	if  (		(srcbtn == 4)
			||	(srcbtn == 7)			
		)
		srcplt++;
	if  (		(destbtn == 4)
			||	(destbtn == 7)			
		)
		destplt++;

	if  (		(srcbtn == 6)
			||	(srcbtn == 7)			
		)
		srcplt += 2;
	if  (		(destbtn == 6)
			||	(destbtn == 7)			
		)
		destplt += 2;

	if 	(		(srcbtn == 1)
				&&	(destbtn == 1)
		)
		SwapFlight(srcflt, destflt);
	else if	(		(		(srcbtn == 2)
						||	(srcbtn == 5)						

					)
				&&	(		(destbtn == 2)
						||	(destbtn == 5)						
					)
			)
			SwapElement(srcele, destele);
	else if	(		(		(srcbtn == 3)
						||	(srcbtn == 4)						
						||	(srcbtn == 6)
						||	(srcbtn == 7)						

					)
				&&	(		(destbtn == 3)
						||	(destbtn == 4)						
						||	(destbtn == 6)
						||	(destbtn == 7)						
					)
			)
			 SwapPilot(srcplt, destplt);
		
}


void CSqdnlist::PilotDetails(int pilot)
{
	if (LoggedChild(1))
	{
		CloseLoggedChildren();
	}
	RDialog* d = MakeTopDialog(
		//CRect(180,180,0,0),
		Place(POSN_MIN,POSN_MAX),
				DialList(DialBox(FIL_NULL,new CPilots,Edges(EDGE::ALIGN_MIN,EDGE::ALIGN_MIN,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE)),
			
					HTabBox(FIL_NULL,IdList(IDS_PERSONAL,IDS_AIRCRAFT),Edges(EDGE::ALIGN_MIN,EDGE::ALIGN_MIN,EDGE::ALIGN_MAX,EDGE::ALIGN_MAX), 
		  							DialBox(FIL_MAP_PILOTDETAILS,new CPilotsPersonalDetails(groupnum, pilot)),
		  							DialBox(FIL_MAP_PILOTDETAILS,new CPilotAircraftDetails(groupnum, pilot))
		  						)
					  		)
					     );	
	LogChild(1,d);
 

}
void CSqdnlist::SwapPilot(int src,int dest)			   //HideToolbars
{
	PilotType tmppilot;
	tmppilot = MMC.Active_Pilots[24*groupnum+src];
	MMC.Active_Pilots[24*groupnum+src] = MMC.Active_Pilots[24*groupnum+dest];
	MMC.Active_Pilots[24*groupnum+dest] = tmppilot;

	int flight	= src/4;
	int posn	= src % 4;
	int p=posn;
	if (posn  > 1)
		posn += 4;
	else
		posn += 3;
	PrintPilotName(m_IDC_BUT_P[p%2][p/2][flight],8*flight+posn, 24*groupnum+src);
	flight	= dest/4;
	posn	= dest % 4;
	p=posn;
	if (posn  > 1)
		posn += 4;
	else
		posn += 3;
	PrintPilotName(m_IDC_BUT_P[p%2][p/2][flight],8*flight+posn, 24*groupnum+dest);

}
void CSqdnlist::SwapElement(int src, int dest)
{
	for (int i = 0;i < 2; i++)
		SwapPilot(src+i, dest+i);

}
void CSqdnlist::SwapFlight(int src, int dest)
{
	for (int i = 0;i < 4; i +=2)
		SwapElement(src+i, dest+i);

}
BOOL CSqdnlist::SwapValid(int src, int dest)
{
	int srcbtn = (src - IDC_TEXT_F0)%8;
	int destbtn = (dest - IDC_TEXT_F0)%8;
	if 	((src != dest) 
		&&
		(	(		(srcbtn == 1)
				&&	(destbtn == 1)
			)
			||
			(		(		(srcbtn == 2)
						||	(srcbtn == 5)						

					)
				&&	(		(destbtn == 2)
						||	(destbtn == 5)						
					)

			)
			||
			(		(		(srcbtn == 3)
						||	(srcbtn == 4)						
						||	(srcbtn == 6)
						||	(srcbtn == 7)						

					)
				&&	(		(destbtn == 3)
						||	(destbtn == 4)						
						||	(destbtn == 6)
						||	(destbtn == 7)						
					)

			)
		))
			return (TRUE);
		else
			return(FALSE);
}



BOOL CSqdnlist::OnInitDialog() 
{
	CDialog::OnInitDialog();
	char buffer[10];

	CREdtBt* b;
	CRStatic*   s;

	// example for rod - Woody
	b=GETDLGITEM(IDC_BUT_E[0][0]) ;
	b->SetPictureFileNum(FIL_ICON_FLIGHT1);
	b=GETDLGITEM(IDC_BUT_E[0][1]) ;
	b->SetPictureFileNum(FIL_ICON_FLIGHT1);
	for(int i=0;i<6;i++)
	{  	
		_itoa(i+1,buffer,10);

		b=GETDLGITEM(IDC_BUT_F[i]);
//		b->SetCaption(RESSTRING(FLIGHTNUM) + buffer);
		b->SetDragAndDropID(IDC_TEXT_F0+8*i+1);


		int decal = FIL_ICON_FLIGHT1+i*2;
		if ((MMC.squad[groupnum].ac_total_avail-4*i) <4)
			decal++;
//		CRStatic*   s=GETDLGITEM(IDC_BUT_F[i]);
		b->SetPictureFileNum(decal);

//		for (int e =0; e<2;e++)
//		{
//			s=GETDLGITEM(IDC_ART_E[e][i]);
//		int decal = FIL_ICON_ELEMENT1 + e;
////			if ((MMC.squad[groupnum].ac_total_avail-4*i) <4)
////				decal++;
//			s->SetPictureFileNum(decal);
//		}


//		s=GETDLGITEM(IDC_TEXT_[i]);
//		if ((MMC.squad[groupnum].ac_total_avail-4*i) >=4)
//			s->SetString(RESSTRING(AVAILABLE));
//		else
//			s->SetString(RESSTRING(NOTAVAILABLE));

		b=GETDLGITEM(IDC_BUT_E[0][i]);
//		b->SetCaption(RESSTRING(STRINGE1));
		decal = FIL_ICON_ELEMENT1;
		if ((MMC.squad[groupnum].ac_total_avail-4*i) <4)
			decal++;
		b->SetPictureFileNum(decal);
		b->SetDragAndDropID(IDC_TEXT_F0+8*i+2);
				  
		b=GETDLGITEM(IDC_BUT_E[1][i]);
//		b->SetCaption(RESSTRING(STRINGE2));
		decal = FIL_ICON_ELEMENT2;
		if ((MMC.squad[groupnum].ac_total_avail-4*i) <4)
			decal++;
		b->SetPictureFileNum(decal);
		b->SetDragAndDropID(IDC_TEXT_F0+8*i+5);

		PrintPilotName(m_IDC_BUT_P[0][0][i],8*i+3, 24*groupnum+4*i);
		PrintPilotName(m_IDC_BUT_P[1][0][i],8*i+4, 24*groupnum+4*i+1);

		PrintPilotName(m_IDC_BUT_P[0][1][i],8*i+6, 24*groupnum+4*i+2);
		PrintPilotName(m_IDC_BUT_P[1][1][i],8*i+7, 24*groupnum+4*i+3);

	}
	
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
