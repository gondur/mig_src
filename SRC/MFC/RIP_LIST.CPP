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

// RIP_List.cpp : implementation file
//

#include "stdafx.h"
#include "mig.h"
#include "RIP_List.h"
#include "rlistbox.h"
#include "mymath.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#ifndef THIS_FILE_DEFINED
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif

/////////////////////////////////////////////////////////////////////////////
// CRIP_List dialog


CRIP_List::CRIP_List(CWnd* pParent /*=NULL*/)
	: RowanDialog(CRIP_List::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRIP_List)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CRIP_List::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRIP_List)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	DDX_Control(pDX,IDC_RLISTBOXCTRL1,m_IDC_RLISTBOXCTRL1);
	DDX_Control(pDX,IDC_RSTATICCTRL1,m_IDC_RSTATICCTRL1);
	DDX_Control(pDX,IDC_RIPDATE,m_IDC_RIPDATE);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRIP_List, CDialog)
	//{{AFX_MSG_MAP(CRIP_List)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRIP_List message handlers

BOOL CRIP_List::OnInitDialog() 
{
	CDialog::OnInitDialog();

	RDialog* parent=(RDialog*)GetParent();
//	parent->SetMaxSize(CRect(0,0,350,350));

	CRStatic*   s;
	s=GETDLGITEM(IDC_RIPDATE);

	
	s->SetString(GetDateName(MMC.ripdate, DATE_LONG));
//	s->SetString(cdate);

	CRListBox* rlistbox;
	rlistbox=GETDLGITEM(IDC_RLISTBOXCTRL1);
	rlistbox->Clear();
	rlistbox->AddColumn(150);
	rlistbox->AddColumn(60);
	rlistbox->AddColumn(70);
	rlistbox->AddColumn(50);

	rlistbox->AddString(RESSTRING(NAME),0);
	rlistbox->AddString(RESSTRING(KILLS),1);
	rlistbox->AddString(RESSTRING(DATE),2);
	rlistbox->AddString(RESSTRING(STATUS),3);
	char buffer[10];

	int i = MMC.nextdeadpilot - 1;
	while (i >= 0)
	{
		rlistbox->AddString(
				MakePilotName(MMC.dead_pilots[i].name),0);
		_itoa(MMC.dead_pilots[i].kills,buffer,10);
		rlistbox->AddString((buffer),1);

		rlistbox->AddString(GetDateName(MMC.dead_pilots[i].lastdate, DATE_SHORT),2);
		rlistbox->AddString(RESLIST(NOTFLYING,MMC.dead_pilots[i].status),3);


		i--;
	}
	i = CASUALTYLIST-1;
	while (i >= MMC.nextdeadpilot)
	{
		if (MMC.dead_pilots[i].lastdate != 0)
		{
			rlistbox->AddString(
				MakePilotName(MMC.dead_pilots[i].name),0);
			_itoa(MMC.dead_pilots[i].kills,buffer,10);
			rlistbox->AddString((buffer),1);

			rlistbox->AddString(GetDateName(MMC.dead_pilots[i].lastdate, DATE_SHORT),2);
			rlistbox->AddString(RESLIST(NOTFLYING,MMC.dead_pilots[i].status),3);
		}

		i--;
	}



//	rlistbox->AddString("20/2/51",0);
//	rlistbox->AddString("20/2/51",0);
//	rlistbox->AddString("20/2/51",0);
//	rlistbox->AddString("M.I.A",1);
//	rlistbox->AddString("W.I.A",1);
//	rlistbox->AddString("K.I.A",1);
//	rlistbox->AddString("Blah Blah",2);
//	rlistbox->AddString("Blah Blah",2);
//	rlistbox->AddString("Blah Blah",2);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
void	CRIP_List::ParentDialClosed(RDialog*,int rv)
{
	OnCancel();
}
