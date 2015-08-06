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

// SqdnLBut.cpp : implementation file
//

#include "stdafx.h"
#include "mig.h"
#include "SqdnLBut.h"
#include "mymath.h"
#include "mytime.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#ifndef THIS_FILE_DEFINED
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif
/////////////////////////////////////////////////////////////////////////////
// CSqdnlistBut dialog


CSqdnlistBut::CSqdnlistBut(int squad,CWnd* pParent /*=NULL*/)
	: RowanDialog(CSqdnlistBut::IDD, pParent)
{
	SetProjSpecific(-1,-1,squad);


	//{{AFX_DATA_INIT(CSqdnlistBut)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CSqdnlistBut::DoDataExchange(CDataExchange* pDX)
{

	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSqdnlistBut)
	DDX_Control(pDX, IDCX_BINGOFUEL, m_IDCX_BINGOFUEL);
	DDX_Control(pDX,IDC_RSTATICCTRL38,m_IDC_RSTATICCTRL38);
	DDX_Control(pDX,IDC_PILOTLOSSES,m_IDC_PILOTLOSSES);
	DDX_Control(pDX,IDC_ROTATEFREQ,m_IDC_ROTATEFREQ);
	DDX_Control(pDX,IDC_RSTATICCTRL39,m_IDC_RSTATICCTRL39);
	DDX_Control(pDX,IDC_RSTATICCTRL60,m_IDC_RSTATICCTRL60);
	DDX_Control(pDX,IDC_AVAILACNUM,m_IDC_AVAILACNUM);
	DDX_Control(pDX,IDC_BINGOFUEL,m_IDC_BINGOFUEL);
	//}}AFX_DATA_MAP


	

}


BEGIN_MESSAGE_MAP(CSqdnlistBut, CDialog)
	//{{AFX_MSG_MAP(CSqdnlistBut)
	ON_EN_UPDATE(IDCX_BINGOFUEL, OnUpdateBingofuel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSqdnlistBut message handlers

BEGIN_EVENTSINK_MAP(CSqdnlistBut, CDialog)
    //{{AFX_EVENTSINK_MAP(CSqdnlistBut)
	ON_EVENT(CSqdnlistBut, IDC_PILOTLOSSES, 1 /* Clicked */, OnClickedPilotlosses, VTS_NONE)
	ON_EVENT(CSqdnlistBut, IDC_ROTATEFREQ, 1 /* TextChanged */, OnTextChangedRotatefreq, VTS_BSTR)
//DEADCODE RDH 13/02/99 	ON_EVENT(CSqdnlistBut, IDC_FLIGHTTACTICS, 1 /* TextChanged */, OnTextChangedFlighttactics, VTS_BSTR)
//DEADCODE RDH 13/02/99 	ON_EVENT(CSqdnlistBut, IDC_ELEMENTTACTICS, 1 /* TextChanged */, OnTextChangedElementtactics, VTS_BSTR)
	ON_EVENT(CSqdnlistBut, IDC_BINGOFUEL, 2 /* TextChanged */, OnTextChangedBingofuel, VTS_I4)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

//DeadCode RDH 30Mar99 void CSqdnlistBut::MakeNewPilot(int pilot)
//DeadCode RDH 30Mar99 {
//DeadCode RDH 30Mar99 	MMC.Active_Pilots[pilot].name.nameref = Math_Lib.rnd(150);
//DeadCode RDH 30Mar99 }
//DeadCode RDH 30Mar99 void CSqdnlistBut::KillPilot(int pilot, pilotstatus status)
//DeadCode RDH 30Mar99 {
//DeadCode RDH 30Mar99 	
//DeadCode RDH 30Mar99 	if (MMC.dead_pilots[MMC.nextdeadpilot].lastdate != 0)
//DeadCode RDH 30Mar99 			 MMC.ripdate = MMC.dead_pilots[MMC.nextdeadpilot].lastdate;
//DeadCode RDH 30Mar99 	MMC.dead_pilots[MMC.nextdeadpilot].name = MMC.Active_Pilots[pilot].name;
//DeadCode RDH 30Mar99 	MMC.dead_pilots[MMC.nextdeadpilot].kills = MMC.Active_Pilots[pilot].kills;
//DeadCode RDH 30Mar99 	MMC.dead_pilots[MMC.nextdeadpilot].rank = MMC.Active_Pilots[pilot].rank;
//DeadCode RDH 30Mar99 	MMC.dead_pilots[MMC.nextdeadpilot].lastdate = MMC.currdate;
//DeadCode RDH 30Mar99 
//DeadCode RDH 30Mar99 	MMC.dead_pilots[MMC.nextdeadpilot].status =  status;
//DeadCode RDH 30Mar99 
//DeadCode RDH 30Mar99 	MakeNewPilot(pilot);
//DeadCode RDH 30Mar99 
//DeadCode RDH 30Mar99 	MMC.nextdeadpilot++;
//DeadCode RDH 30Mar99 	if	(MMC.nextdeadpilot >= CASUALTYLIST)
//DeadCode RDH 30Mar99 		MMC.nextdeadpilot = 0;
//DeadCode RDH 30Mar99 }

void CSqdnlistBut::OnClickedPilotlosses() 
{
//DEADCODE RDH 25/03/99 	KillPilot(4, (pilotstatus)(2 + Math_Lib.rnd(3)));
//DEADCODE RDH 25/03/99 	KillPilot(6,(pilotstatus)(2 + Math_Lib.rnd(3)));
	MMC.currdate = MMC.currdate + SECSPERDAY;

	if (LoggedChild(1))
	{
		CloseLoggedChildren();
	}
	RDialog* d =MakeTopDialog(
		//CRect(50,50,0,0),
		Place(POSN_CENTRE,POSN_CENTRE,0,0),
								DialBox(FIL_MAP_PILOTLOSSES/*IDB_GENERALS*/,new CRIP_List)//,Edges(EDGE::ALIGN_MIN + EDGE::ACTIONS_SPLITTER,EDGE::ALIGN_MIN,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE))
							);	
	LogChild(1,d);


//	RDialog::MakeTopDialog(CRect(50,50,0,0),
//								DialBox(FIL_MAP_PILOTLOSSES/*IDB_GENERALS*/,new CRIP_List)//,Edges(EDGE::ALIGN_MIN + EDGE::ACTIONS_SPLITTER,EDGE::ALIGN_MIN,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE))
//							);		
	
}

void CSqdnlistBut::OnTextChangedRotatefreq(LPCTSTR text) 
{
 	CRCombo* combo;
	combo=GETDLGITEM(IDC_ROTATEFREQ);
	MMC.squad[groupnum].rotatefreq = 
				combo->GetIndex();
}

//DEADCODE RDH 13/02/99 void CSqdnlistBut::OnTextChangedFlighttactics(LPCTSTR text) 
//DEADCODE RDH 13/02/99 {
//DEADCODE RDH 13/02/99  	CRCombo* combo;
//DEADCODE RDH 13/02/99 	combo=GETDLGITEM(IDC_FLIGHTTACTICS);
//DEADCODE RDH 13/02/99 	MMC.squad[groupnum].flighttactics = 
//DEADCODE RDH 13/02/99 				(AcTactics)combo->GetIndex();
//DEADCODE RDH 13/02/99 	
//DEADCODE RDH 13/02/99 }

//DEADCODE RDH 13/02/99 void CSqdnlistBut::OnTextChangedElementtactics(LPCTSTR text) 
//DEADCODE RDH 13/02/99 {
//DEADCODE RDH 13/02/99  	CRCombo* combo;
//DEADCODE RDH 13/02/99 	combo=GETDLGITEM(IDC_ELEMENTTACTICS);
//DEADCODE RDH 13/02/99 	MMC.squad[groupnum].elementtactics = 
//DEADCODE RDH 13/02/99 				(AcTactics)combo->GetIndex();
//DEADCODE RDH 13/02/99 	
//DEADCODE RDH 13/02/99 }

BOOL CSqdnlistBut::OnInitDialog() 
{
	CDialog::OnInitDialog();

	
	char buffer[10];

  	CRCombo* combo;
	combo=GETDLGITEM(IDC_ROTATEFREQ);
	combo->RESCOMBO(ROTATE0,6)->SetIndex(MMC.squad[groupnum].rotatefreq);

//DEADCODE RDH 13/02/99 	combo=GETDLGITEM(IDC_ELEMENTTACTICS);
//DEADCODE RDH 13/02/99 	combo->RESCOMBO(WELDEDWING,4)->SetIndex(MMC.squad[groupnum].elementtactics);
//DEADCODE RDH 13/02/99 	
//DEADCODE RDH 13/02/99 	combo=GETDLGITEM(IDC_FLIGHTTACTICS);
//DEADCODE RDH 13/02/99 	combo->RESCOMBO(WELDEDWING,4)->SetIndex(MMC.squad[groupnum].flighttactics);
	
	CRStatic*   s;
	s=GETDLGITEM(IDC_AVAILACNUM);
	_itoa(MMC.squad[groupnum].ac_total_avail,buffer,10);

	s->SetString(buffer);

	s=GETDLGITEM(IDC_RSTATICCTRL60);

	s->SetString(LoadResString(IDS_BINGOFUEL) + ", " 
			+ LoadResString(Save_Data.mass.abbrtype) );

	int fuel = MMC.squad[groupnum].bingofuel/(100*Save_Data.mass.gm);
	if (fuel>200)
		fuel = ((fuel + 50)/100)*100;
	if (m_IDCX_BINGOFUEL)
	{
		m_IDCX_BINGOFUEL.SetWindowText(CSprintf("%4i",fuel));
		m_IDCX_BINGOFUEL.SetLimitText(5);
	}
	else
	{
		CREdit* b;
		b=GETDLGITEM(IDC_BINGOFUEL);
		b->SetCaption(CSprintf("%4i",fuel));
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSqdnlistBut::OnTextChangedBingofuel(LPTSTR text) 
{
		CREdit* edit;
///		CString	buffer;
		edit=GETDLGITEM(IDC_BINGOFUEL);
///		buffer = edit->GetCaption();

		trunc(text,4);
		if  (	(strlen(text) > 0 )	&&	(strlen(text) < 5 )	)
		{
			int fuel = atoi(text);
			fuel = fuel * (Save_Data.mass.gm*100);
			if (fuel < 0)
				fuel = 0;
			MMC.squad[groupnum].bingofuel = fuel;
		}
	
}

void CSqdnlistBut::OnUpdateBingofuel() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function to send the EM_SETEVENTMASK message to the control
	// with the ENM_UPDATE flag ORed into the lParam mask.
	
	// TODO: Add your control notification handler code here
	CString text;
	GETDLGITEM(IDCX_BINGOFUEL)->GetWindowText(text);
	int fuel = atoi(text);
	fuel = fuel * (Save_Data.mass.gm*100);
	if (fuel < 0)
		fuel = 0;
	MMC.squad[groupnum].bingofuel = fuel;
}
