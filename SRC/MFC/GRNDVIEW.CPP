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

// Grndview.cpp : implementation file
//

#include "stdafx.h"
#include "mig.h"
#include "Grndview.h"
#include "rlistbox.h"	
#include "RRadio.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#ifndef THIS_FILE_DEFINED
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif

/////////////////////////////////////////////////////////////////////////////
// CGrndview dialog


CGrndview::CGrndview(CWnd* pParent /*=NULL*/)
	: RowanDialog(CGrndview::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGrndview)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CGrndview::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGrndview)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	DDX_Control(pDX,IDC_RRADIO_FILTER,m_IDC_RRADIO_FILTER);
	DDX_Control(pDX,IDC_RLIST_GRNDKILL,m_IDC_RLIST_GRNDKILL);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGrndview, CDialog)
	//{{AFX_MSG_MAP(CGrndview)
	ON_WM_CANCELMODE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGrndview message handlers

void CGrndview::OnCancelMode() 
{
	CDialog::OnCancelMode();
	
	// TODO: Add your message handler code here
	
}

void CGrndview::RedrawTables(Debrief::SquadKills period)
{
	CRListBox* l;
	l=GETDLGITEM(IDC_RLIST_GRNDKILL);

	//sum to get all column
	for (Debrief::Types i = Debrief::SUPPLY; i <= Debrief::TANK; i++)
	{
		int kills = 0;
		for (SquadSelect j = SQ_F86A; j < (SQ_B_NONFLYSPOT); j++)
		{
			kills += period[j][i];
		}
		period[SQ_B_NONFLYSPOT][i] = kills;
	}


	for (i = Debrief::SUPPLY; i <= Debrief::TANK; i++)
	{
		for (SquadSelect j = SQ_F86A; j < (SQ_B_NONFLYSPOT+1); j++)
		{
			int kill = period[j][i];
			if (kill != 0)
				l->AddString(CSprintf("%i",kill),j+1);
			else
				l->AddString(CSprintf(" -"),j+1);

		}
	}



}

void CGrndview::ReDrawRadioButtons()
{
	CRRadio* pradio;
	pradio=GETDLGITEM(IDC_RRADIO_FILTER);
	pradio->SetCurrentSelection(MMC.debrief.displayperiod);


}

void CGrndview::ReDrawHeadings()
{
	CRListBox* rlistbox;
	CString string;
	rlistbox=GETDLGITEM(IDC_RLIST_GRNDKILL);
	rlistbox->Clear();
	rlistbox->AddColumn(100);
	rlistbox->AddColumn(52);
	rlistbox->AddColumn(52);
	rlistbox->AddColumn(34);
	rlistbox->AddColumn(34);
	rlistbox->AddColumn(34);
	rlistbox->AddColumn(34);
	rlistbox->AddColumn(34);
	rlistbox->AddColumn(4);

	string.LoadString(IDS_OBJECTIVE);
	rlistbox->AddString(string,0);
	string.LoadString(IDS_SUPPLYPOINT);
	rlistbox->AddString(string,0);
	string.LoadString(IDS_MARSHALLINGYARD);
	rlistbox->AddString(string,0);
	string.LoadString(IDS_RAILBRIDGE);
	rlistbox->AddString(string,0);
	string.LoadString(IDS_ROADBRIDGE);
	rlistbox->AddString(string,0);
	string.LoadString(IDS_SUPPLYTRAIN);
	rlistbox->AddString(string,0);
	string.LoadString(IDS_SUPPLYVEHICLE);
	rlistbox->AddString(string,0);
	string.LoadString(IDS_AIRFIELD);
	rlistbox->AddString(string,0);
	string.LoadString(IDS_TROOPCONCENTRATION);
	rlistbox->AddString(string,0);
	string.LoadString(IDS_ARTILLERYPOSITION);
	rlistbox->AddString(string,0);
	string.LoadString(IDS_TANK);
	rlistbox->AddString(string,0);

	string.LoadString(IDS_L_SQ_BF_F86A);
	rlistbox->AddString(string,1);

	string.LoadString(IDS_SQ_BF_F86B);
	rlistbox->AddString(string,2);

	string.LoadString(IDS_F80);
	rlistbox->AddString(string,3);

	string.LoadString(IDS_F84);
	rlistbox->AddString(string,4);

	string.LoadString(IDS_F51);
	rlistbox->AddString(string,5);

	string.LoadString(IDS_B26);
	rlistbox->AddString(string,6);

	string.LoadString(IDS_B29);
	rlistbox->AddString(string,7);


	string.LoadString(IDS_ALL);
	rlistbox->AddString(string,8);




}
void CGrndview::ReDrawPanel()
{  

	ReDrawRadioButtons();
	ReDrawHeadings();
	switch(MMC.debrief.displayperiod)
	{
	case	Debrief::PERIOD:	
		{
			RedrawTables(MMC.debrief.lastperiod);
			break;
		}
	case	Debrief::DAY:	
		{
			RedrawTables(MMC.debrief.lastday);
			break;
		}
	case	Debrief::TOTAL:	
		{
			RedrawTables(MMC.debrief.total);
			break;
		}
	}

}

BOOL CGrndview::OnInitDialog() 
{
	CDialog::OnInitDialog();

	
	CString string;
	CRRadio* pradio;

	pradio=GETDLGITEM(IDC_RRADIO_FILTER);
	int period = MMC.debrief.currperiod;
	period--;
	if (period < 0)
		period = 2;
	string.LoadString(IDS_L_MORNING + period);
	pradio->AddButton(string);

	if (		(period == 2)
			&&	(MMC.indebrief)
		)
		string.LoadString(IDS_TODAY);
	else
		string.LoadString(IDS_YESTERDAY);
	pradio->AddButton(string);
	string.LoadString(IDS_CAMPAIGN);
	pradio->AddButton(string);


//	ReDrawPanel();
	ReDrawHeadings();
	ReDrawPanel();													  //RDH 08/06/99


	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BEGIN_EVENTSINK_MAP(CGrndview, CDialog)
    //{{AFX_EVENTSINK_MAP(CGrndview)
	ON_EVENT(CGrndview, IDC_RRADIO_FILTER, 1 /* Selected */, OnSelectedRradioFilter, VTS_I4)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CGrndview::OnSelectedRradioFilter(long ButtonNum) 
{
	MMC.debrief.displayperiod = ButtonNum;
	ReDrawPanel();	
	
}

