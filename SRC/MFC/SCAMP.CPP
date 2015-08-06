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

// SCamp.cpp : implementation file
//

#include "stdafx.h"
#include "mig.h"
#include "SCamp.h"
#include "rlistbox.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#ifndef THIS_FILE_DEFINED
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif

/////////////////////////////////////////////////////////////////////////////
// CSCampaign dialog


CSCampaign::CSCampaign(CWnd* pParent /*=NULL*/)
	: RowanDialog(CSCampaign::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSCampaign)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CSCampaign::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSCampaign)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	DDX_Control(pDX,IDC_RLIST_CAMPAIGNS,m_IDC_RLIST_CAMPAIGNS);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSCampaign, CDialog)
	//{{AFX_MSG_MAP(CSCampaign)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSCampaign message handlers

BOOL CSCampaign::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CRListBox* rlistbox;
	CString string;

	rlistbox=GETDLGITEM(IDC_RLIST_CAMPAIGNS);
	rlistbox->Clear();
	rlistbox->AddColumn(200);
   	rlistbox->AddColumn(100);

	string.LoadString(IDS_L_SCAMPAIGNSELECT1);
	rlistbox->AddString(string,0);
	string.LoadString(IDS_SCAMPAIGNSELECT2);
	rlistbox->AddString(string,0);
	string.LoadString(IDS_SCAMPAIGNSELECT3);
	rlistbox->AddString(string,0);
	string.LoadString(IDS_SCAMPAIGNSELECT4);
	rlistbox->AddString(string,0);
	string.LoadString(IDS_SCAMPAIGNSELECT5);
	rlistbox->AddString(string,0);

   	string.LoadString(IDS_SCAMPAIGNDATE1);
	rlistbox->AddString(string,1);
	string.LoadString(IDS_SCAMPAIGNDATE2);
	rlistbox->AddString(string,1);
	string.LoadString(IDS_SCAMPAIGNDATE3);
	rlistbox->AddString(string,1);
	string.LoadString(IDS_SCAMPAIGNDATE4);
	rlistbox->AddString(string,1);
	string.LoadString(IDS_SCAMPAIGNDATE5);
	rlistbox->AddString(string,1);
	rlistbox->SetHilightRow(0);
	rlistbox->SetHilightCol(0);



	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


BEGIN_EVENTSINK_MAP(CSCampaign, CDialog)
    //{{AFX_EVENTSINK_MAP(CSCampaign)
	ON_EVENT(CSCampaign, IDC_RLIST_CAMPAIGNS, 1 /* Select */, OnSelectRlistCampaigns, VTS_I4 VTS_I4)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()


int	CSCampaign::SelCamp=0;


void CSCampaign::OnSelectRlistCampaigns(long row, long column) 
{
	FullPanel()->ChangeCamp(row);								//JIM 12Jan99
}
