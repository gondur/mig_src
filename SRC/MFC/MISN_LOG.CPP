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

// Misn_log.cpp : implementation file
//

#include "stdafx.h"
#include "mig.h"
#include "Misn_log.h"
#include "rlistbox.h"
#include "mytime.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#ifndef THIS_FILE_DEFINED
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif

/////////////////////////////////////////////////////////////////////////////
// CMisn_log dialog


CMisn_log::CMisn_log(CWnd* pParent /*=NULL*/)
	: RowanDialog(CMisn_log::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMisn_log)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CMisn_log::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMisn_log)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	DDX_Control(pDX,IDC_RLISTBOXCTRL1,m_IDC_RLISTBOXCTRL1);

	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMisn_log, CDialog)
	//{{AFX_MSG_MAP(CMisn_log)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMisn_log message handlers

BOOL CMisn_log::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CString string;

	CRListBox* rlistbox;
	rlistbox=GETDLGITEM(IDC_RLISTBOXCTRL1);
	rlistbox->Clear();
	rlistbox->AddColumn(48);
//DEADCODE RDH 09/06/99 	rlistbox->AddColumn(40);
	rlistbox->AddColumn(TARGETFIELDWIDTH+14);
//can't fit this in	rlistbox->AddColumn(20);
	rlistbox->AddColumn(2);

	string.LoadString(IDS_DATE);
	rlistbox->AddString(string,0);

//DEADCODE RDH 09/06/99 	string.LoadString(IDS_ROLE); can't fit it in
//DEADCODE RDH 09/06/99 	rlistbox->AddString(string,1);

	string.LoadString(IDS_MAIN_WP_TARGET);
	rlistbox->AddString(string,1);

//DEADCODE JIM 10/04/99 	string.LoadString(IDS_AC);
//DEADCODE JIM 10/04/99 	rlistbox->AddString(string,3);

	string.LoadString(IDS_KILLS);
	rlistbox->AddString(string,2);

	int day = MMC.debrief.currlogday;
	int period = MMC.debrief.currperiod;
	while (day >= 0)
	{
		while (period >= 0)
		{
			if (MMC.debrief.playerlog[day][period].target1 != UID_NULL)
			{
				SLong date = MMC.startdate + (day * SECSPERDAY);
				rlistbox->AddString(GetDateName(date, DATE_SHORT),0);
				if (MMC.debrief.playerlog[day][period].target1 != UID_NULL)
					rlistbox->AddString(GetTargName(MMC.debrief.playerlog[day][period].target1), 1);

//DEADCODE JIM 10/04/99 				rlistbox->AddString(RESLIST(SQ_BF_F86A,MMC.debrief.playerlog[day][period].pilotsquad),3);
				int kills = MMC.debrief.playerlog[day][period].kills;	
				rlistbox->AddString(CSprintf("%i",kills),2);	
			}
				period--;
		}
		period = 2;
		day--;

	};

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
