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

// Armyrqst.cpp : implementation file
//

#include "stdafx.h"
#include "mig.h"
#include "Armyrqst.h"
#include "rlistbox.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#ifndef THIS_FILE_DEFINED
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif

/////////////////////////////////////////////////////////////////////////////
// CArmyRequests dialog


CArmyRequests::CArmyRequests(CWnd* pParent /*=NULL*/)
	: RowanDialog(CArmyRequests::IDD, pParent)
{
	//{{AFX_DATA_INIT(CArmyRequests)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CArmyRequests::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CArmyRequests)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	DDX_Control(pDX,IDC_RLISTBOXCTRL1,m_IDC_RLISTBOXCTRL1);
	DDX_Control(pDX,IDC_RLISTBOXCTRL2,m_IDC_RLISTBOXCTRL2);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CArmyRequests, CDialog)
	//{{AFX_MSG_MAP(CArmyRequests)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CArmyRequests* CArmyRequests::MakeSheet(CRect r,UniqueID item,UniqueID  force)
{
	CArmyRequests*	armysheet;
	MakeTopDialog(r,
			DialList(DialBox(FIL_MAP_ARMY/*IDB_BBC3*/,armysheet = new CArmyRequests,Edges(EDGE::ALIGN_MIN,EDGE::ALIGN_MIN,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE)),
			
					HTabBox(FIL_NULL,IdList(IDS_UNFORCES,IDS_REDFORCES),Edges(EDGE::ALIGN_MIN,EDGE::ALIGN_MIN,EDGE::ALIGN_MAX,EDGE::ALIGN_MAX), 
		  							DialBox(FIL_NULL/*IDB_BBC3*/,new CBattleDetail(item,force,0)),
		  							DialBox(FIL_NULL/*IDB_BBC3*/,new CBattleDetail(item,force,1))
							)
			  		)
			     );
return armysheet;
}
void	CArmyRequests::TabSelect(int side)
{
	CRTabs* tab=(CRTabs*)fchild->GetDlgItem(IDJ_TABCTRL);
	CWnd* currentWindow;
	currentWindow=(CWnd*)tab->SelectTab(side);

}
void  CArmyRequests::ParentDialClosed(RDialog*,int rv)
{
	OnOK();
}


/////////////////////////////////////////////////////////////////////////////
// CArmyRequests message handlers

BOOL CArmyRequests::OnInitDialog() 
{
	CDialog::OnInitDialog();
//DeadCode RDH 04Dec98 	CRListBox* rlistbox;
//DeadCode RDH 04Dec98 	CString string;
//DeadCode RDH 04Dec98 	rlistbox=GETDLGITEM(IDC_RLISTBOXCTRL1);
//DeadCode RDH 04Dec98 	rlistbox->Clear();
//DeadCode RDH 04Dec98 	rlistbox->AddColumn(60);
//DeadCode RDH 04Dec98 	rlistbox->AddColumn(20);
//DeadCode RDH 04Dec98 	rlistbox->AddColumn(100);
//DeadCode RDH 04Dec98 	rlistbox->AddColumn(80);
//DeadCode RDH 04Dec98 	rlistbox->AddColumn(30);

	


//DeadCode RDH 04Dec98 	CRListBox* rlistbox;
//DeadCode RDH 04Dec98 	CString string;
//DeadCode RDH 04Dec98 	rlistbox=GETDLGITEM(IDC_RLISTBOXCTRL1);
//DeadCode RDH 04Dec98 	rlistbox->Clear();
//DeadCode RDH 04Dec98 	rlistbox->AddColumn(60);
//DeadCode RDH 04Dec98 	rlistbox->AddColumn(20);
//DeadCode RDH 04Dec98 	rlistbox->AddColumn(100);
//DeadCode RDH 04Dec98 	rlistbox->AddColumn(80);
//DeadCode RDH 04Dec98 	rlistbox->AddColumn(30);
//DeadCode RDH 04Dec98 
//DeadCode RDH 04Dec98 	string.LoadString(IDS_RED);
//DeadCode RDH 04Dec98 	rlistbox->AddString(string,0);
//DeadCode RDH 04Dec98 	string.LoadString(IDS_TROOPCONCENTRATION);
//DeadCode RDH 04Dec98 	rlistbox->AddString(string,0);
//DeadCode RDH 04Dec98 	string.LoadString(IDS_ARTILLERYPOSITION);
//DeadCode RDH 04Dec98 	rlistbox->AddString(string,0);
//DeadCode RDH 04Dec98 	string.LoadString(IDS_TANK);
//DeadCode RDH 04Dec98 	rlistbox->AddString(string,0);
//DeadCode RDH 04Dec98 	string.LoadString(IDS_TROOPCONCENTRATION);
//DeadCode RDH 04Dec98 	rlistbox->AddString(string,0);
//DeadCode RDH 04Dec98 
//DeadCode RDH 04Dec98 	rlistbox->AddString("Size",1);
//DeadCode RDH 04Dec98 	rlistbox->AddString("2",1);
//DeadCode RDH 04Dec98 	rlistbox->AddString("1",1);
//DeadCode RDH 04Dec98 	rlistbox->AddString("2",1);
//DeadCode RDH 04Dec98 	rlistbox->AddString("1",1);
//DeadCode RDH 04Dec98 
//DeadCode RDH 04Dec98 	string.LoadString(IDS_LOCATION);
//DeadCode RDH 04Dec98 	rlistbox->AddString(string,2);
//DeadCode RDH 04Dec98 	rlistbox->AddString("Reserve",2);
//DeadCode RDH 04Dec98 	rlistbox->AddString("North Hill 295",2);
//DeadCode RDH 04Dec98 	rlistbox->AddString("Hill 295",2);
//DeadCode RDH 04Dec98 	rlistbox->AddString("South River",2);
//DeadCode RDH 04Dec98 
//DeadCode RDH 04Dec98 	string.LoadString(IDS_STATUS);
//DeadCode RDH 04Dec98 	rlistbox->AddString(string,3);
//DeadCode RDH 04Dec98 	rlistbox->AddString("Blocking",3);
//DeadCode RDH 04Dec98 	rlistbox->AddString("Attacking",3);
//DeadCode RDH 04Dec98 	rlistbox->AddString("Emplaced",3);
//DeadCode RDH 04Dec98 	rlistbox->AddString("Retreating",3);
//DeadCode RDH 04Dec98 
//DeadCode RDH 04Dec98 	string.LoadString(IDS_CASREQUESTS);
//DeadCode RDH 04Dec98 	rlistbox->AddString(string,4);
//DeadCode RDH 04Dec98 	rlistbox->AddString("2",4);
//DeadCode RDH 04Dec98 	rlistbox->AddString("1",4);
//DeadCode RDH 04Dec98 	rlistbox->AddString("3",4);
//DeadCode RDH 04Dec98 	rlistbox->AddString("4",4);
//DeadCode RDH 04Dec98 
//DeadCode RDH 04Dec98 	rlistbox=GETDLGITEM(IDC_RLISTBOXCTRL2);
//DeadCode RDH 04Dec98 	rlistbox->Clear();
//DeadCode RDH 04Dec98 	rlistbox->AddColumn(80);
//DeadCode RDH 04Dec98 	rlistbox->AddColumn(20);
//DeadCode RDH 04Dec98 	rlistbox->AddColumn(100);
//DeadCode RDH 04Dec98 	rlistbox->AddColumn(80);
//DeadCode RDH 04Dec98 	rlistbox->AddColumn(30);
//DeadCode RDH 04Dec98 
//DeadCode RDH 04Dec98 	string.LoadString(IDS_RED);
//DeadCode RDH 04Dec98 	rlistbox->AddString(string,0);
//DeadCode RDH 04Dec98 	string.LoadString(IDS_TROOPCONCENTRATION);
//DeadCode RDH 04Dec98 	rlistbox->AddString(string,0);
//DeadCode RDH 04Dec98 	string.LoadString(IDS_ARTILLERYPOSITION);
//DeadCode RDH 04Dec98 	rlistbox->AddString(string,0);
//DeadCode RDH 04Dec98 	string.LoadString(IDS_TANK);
//DeadCode RDH 04Dec98 	rlistbox->AddString(string,0);
//DeadCode RDH 04Dec98 	string.LoadString(IDS_TROOPCONCENTRATION);
//DeadCode RDH 04Dec98 	rlistbox->AddString(string,0);
//DeadCode RDH 04Dec98 
//DeadCode RDH 04Dec98 	rlistbox->AddString("Size",1);
//DeadCode RDH 04Dec98 	rlistbox->AddString("2",1);
//DeadCode RDH 04Dec98 	rlistbox->AddString("1",1);
//DeadCode RDH 04Dec98 	rlistbox->AddString("2",1);
//DeadCode RDH 04Dec98 	rlistbox->AddString("1",1);
//DeadCode RDH 04Dec98 
//DeadCode RDH 04Dec98 	string.LoadString(IDS_LOCATION);
//DeadCode RDH 04Dec98 	rlistbox->AddString(string,2);
//DeadCode RDH 04Dec98 	rlistbox->AddString("Reserve",2);
//DeadCode RDH 04Dec98 	rlistbox->AddString("North Hill 295",2);
//DeadCode RDH 04Dec98 	rlistbox->AddString("Hill 295",2);
//DeadCode RDH 04Dec98 	rlistbox->AddString("South River",2);
//DeadCode RDH 04Dec98 
//DeadCode RDH 04Dec98 	string.LoadString(IDS_STATUS);
//DeadCode RDH 04Dec98 	rlistbox->AddString(string,3);
//DeadCode RDH 04Dec98 	rlistbox->AddString("Blocking",3);
//DeadCode RDH 04Dec98 	rlistbox->AddString("Attacking",3);
//DeadCode RDH 04Dec98 	rlistbox->AddString("Emplaced",3);
//DeadCode RDH 04Dec98 	rlistbox->AddString("Retreating",3);
//DeadCode RDH 04Dec98 
//DeadCode RDH 04Dec98 	string.LoadString(IDS_CASREQUESTS);
//DeadCode RDH 04Dec98 	rlistbox->AddString(string,4);
//DeadCode RDH 04Dec98 	rlistbox->AddString("2",4);
//DeadCode RDH 04Dec98 	rlistbox->AddString("1",4);
//DeadCode RDH 04Dec98 	rlistbox->AddString("3",4);
//DeadCode RDH 04Dec98 	rlistbox->AddString("4",4);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
