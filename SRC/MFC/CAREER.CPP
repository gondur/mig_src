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

// Career.cpp : implementation file
//

#include "stdafx.h"
#include "mig.h"
#include "Career.h"
#include "rlistbox.h"

#include "enumbits.m"
#include "comms.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#ifndef THIS_FILE_DEFINED
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif

/////////////////////////////////////////////////////////////////////////////
// CCareer dialog


CCareer::CCareer(CWnd* pParent /*=NULL*/)
	: RowanDialog(CCareer::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCareer)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CCareer::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCareer)
	DDX_Control(pDX, IDCX_NAME, m_IDCX_NAME);
	DDX_Control(pDX,IDC_NAME,m_IDC_NAME);
	DDX_Control(pDX,IDC_RLISTBOXCTRL1,m_IDC_RLISTBOXCTRL1);
	DDX_Control(pDX,IDC_RSTATICCTRL3,m_IDC_RSTATICCTRL3);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCareer, CDialog)
	//{{AFX_MSG_MAP(CCareer)
	ON_WM_DESTROY()
	ON_EN_UPDATE(IDCX_NAME, OnUpdateName)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCareer message handlers



BOOL CCareer::OnInitDialog() 
{
	CDialog::OnInitDialog();
//	CRSpinBut* spinbut;
//	spinbut=GetDlgItem(IDC_RSPINBUTCTRL2);
//	spinbut->AddString("1");
//	spinbut->AddString("2");
//	spinbut->AddString("3");
//	spinbut->AddString("4");
//	spinbut->AddString("5");
	
	if (m_IDCX_NAME.m_hWnd)
	{
		if	(RFullPanelDial::incomms)
		{
			m_IDCX_NAME.SetWindowText(DPlay::H2H_Player[0].name);
			m_IDCX_NAME.SetReadOnly(TRUE);
		}
		else
		{
			m_IDCX_NAME.SetWindowText(MMC.PlayerName);
			m_IDCX_NAME.SetReadOnly(FALSE);
			m_IDCX_NAME.SetLimitText(PLAYERNAMELEN-1);
		}
	}
	else
	{
		CREdit* editbox;
		editbox=GETDLGITEM(IDC_NAME);
		if	(RFullPanelDial::incomms)
		{
			editbox->SetCaption(DPlay::H2H_Player[0].name);
			editbox->SetEnabled(false);
		}else
		{
			editbox->SetCaption(MMC.PlayerName);
			editbox->SetEnabled(true);
			editbox->SetFocus();
		}
	}
	CRListBox* rlistbox;
	rlistbox=GETDLGITEM(IDC_RLISTBOXCTRL1);
	rlistbox->Clear();
	rlistbox->AddColumn(60);
	rlistbox->AddColumn(60);
	rlistbox->AddColumn(60);
	rlistbox->AddColumn(60);
	rlistbox->AddColumn(2);


	CString string;

	string.LoadString(IDS_L_SQ_BF_F86A);
	rlistbox->AddString(string,0);

	string.LoadString(IDS_L_SQ_BF_F86A);
	rlistbox->AddString(string,0);

	string.LoadString(IDS_SQ_BF_F86B);
	rlistbox->AddString(string,0);

	string.LoadString(IDS_F80);
	rlistbox->AddString(string,0);

	string.LoadString(IDS_F84);
	rlistbox->AddString(string,0);

	string.LoadString(IDS_F51);
	rlistbox->AddString(string,0);

	string.LoadString(IDS_ALL);
	rlistbox->AddString(string,0);

	string.LoadString(IDS_SORTIES);
	rlistbox->AddString(string,1);

	string.LoadString(IDS_COMBATS);
	rlistbox->AddString(string,2);

	string.LoadString(IDS_KILLS);
	rlistbox->AddString(string,3);

	string.LoadString(IDS_PILOT_LOSSES);
	rlistbox->AddString(string,4);

	//sum to get all column
	for (Debrief::PlayerTypes i = Debrief::SORTIES; i <= Debrief::LOSSES; i++)
	{
		int kills = 0;
		for (SquadSelect j = SQ_F86A; j < (SQ_B_NONFLYABLE); j++)
		{
			kills += MMC.debrief.playertotals[j][i];
		}
		MMC.debrief.playertotals[SQ_B_NONFLYABLE][i] = kills;
	}


	  
	for ( i = Debrief::SORTIES; i <= Debrief::LOSSES; i++)
	{
		for (SquadSelect j = SQ_F86A; j < (SQ_B_NONFLYABLE+1); j++)
		{
			int kill = MMC.debrief.playertotals[j][i];
			rlistbox->AddString(CSprintf("%i",kill),i+1);
		}
	}



	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
void CCareer::OnOK()
{
	CREdit* editbox;
	CString	buffer;
	if (m_IDCX_NAME.m_hWnd)
	{
		m_IDCX_NAME.GetWindowText(buffer);
		strcpy(&MMC.PlayerName[0],buffer);
	}
	else
	{
		editbox=&m_IDC_NAME;
//DeadCode DAW 23Nov98 	editbox=GETDLGITEM(IDC_NAME);
		buffer = editbox->GetCaption();

		if (buffer.GetLength() <= (PLAYERNAMELEN - 1))
			strcpy(&MMC.PlayerName[0],buffer);
	}

}
void CCareer::OnDestroy() 
{

	CDialog::OnDestroy();
	
	
}

BEGIN_EVENTSINK_MAP(CCareer, CDialog)
    //{{AFX_EVENTSINK_MAP(CCareer)
	ON_EVENT(CCareer, IDC_NAME, 2 /* TextChanged */, OnTextChangedName, VTS_I4)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CCareer::OnTextChangedName(LPTSTR text) 
{
	trunc(text,PLAYERNAMELEN - 1);		
}

void CCareer::OnUpdateName() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function to send the EM_SETEVENTMASK message to the control
	// with the ENM_UPDATE flag ORed into the lParam mask.
	
	// TODO: Add your control notification handler code here
	
}
