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

// SGrdClms.cpp : implementation file
//

#include "stdafx.h"
#include "mig.h"
#include "SGrdClms.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#ifndef THIS_FILE_DEFINED
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif

/////////////////////////////////////////////////////////////////////////////
// CSQuickGroundClaims dialog


CSQuickGroundClaims::CSQuickGroundClaims(CWnd* pParent /*=NULL*/)
	: RowanDialog(CSQuickGroundClaims::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSQuickGroundClaims)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CSQuickGroundClaims::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSQuickGroundClaims)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	DDX_Control(pDX,IDC_SDETAIL1,m_IDC_SDETAIL1);
	DDX_Control(pDX,IDC_RSTATICCTRL2,m_IDC_RSTATICCTRL2);
	DDX_Control(pDX,IDC_RSTATICCTRL3,m_IDC_RSTATICCTRL3);
	DDX_Control(pDX,IDC_RSTATICCTRL4,m_IDC_RSTATICCTRL4);
	DDX_Control(pDX,IDC_RSTATICCTRL5,m_IDC_RSTATICCTRL5);
	DDX_Control(pDX,IDC_SDETAIL2,m_IDC_SDETAIL2);
	DDX_Control(pDX,IDC_RSTATICCTRL24,m_IDC_RSTATICCTRL24);
	DDX_Control(pDX,IDC_RSTATICCTRL6,m_IDC_RSTATICCTRL6);
	DDX_Control(pDX,IDC_SDETAIL4,m_IDC_SDETAIL4);
	DDX_Control(pDX,IDC_SCLAIMS_PLAYER_SUPPLYVEHICLE,m_IDC_SCLAIMS_PLAYER_SUPPLYVEHICLE);
	DDX_Control(pDX,IDC_SCLAIMS_PLAYER_SUPPLYPOINT,m_IDC_SCLAIMS_PLAYER_SUPPLYPOINT);
	DDX_Control(pDX,IDC_SCLAIMS_PLAYER_SUPPLYTRAIN,m_IDC_SCLAIMS_PLAYER_SUPPLYTRAIN);
	DDX_Control(pDX,IDC_SCLAIMS_PLAYER_MARSHALLINGYARD,m_IDC_SCLAIMS_PLAYER_MARSHALLINGYARD);
	DDX_Control(pDX,IDC_SCLAIMS_PLAYER_BRIDGE,m_IDC_SCLAIMS_PLAYER_BRIDGE);
	DDX_Control(pDX,IDC_SCLAIMS_PLAYER_AIRFIELDS,m_IDC_SCLAIMS_PLAYER_AIRFIELDS);
	DDX_Control(pDX,IDC_SCLAIMS_PLAYER_ARTILLERYPOSITION,m_IDC_SCLAIMS_PLAYER_ARTILLERYPOSITION);
	DDX_Control(pDX,IDC_SCLAIMS_PLAYER_TROOPCONCENTRATION,m_IDC_SCLAIMS_PLAYER_TROOPCONCENTRATION);
	DDX_Control(pDX,IDC_SCLAIMS_PLAYER_TANK,m_IDC_SCLAIMS_PLAYER_TANK);
	DDX_Control(pDX,IDC_SDETAIL16,m_IDC_SDETAIL16);
	DDX_Control(pDX,IDC_SDETAIL20,m_IDC_SDETAIL20);
	DDX_Control(pDX,IDC_SCLAIMS_UN_SUPPLYVEHICLE,m_IDC_SCLAIMS_UN_SUPPLYVEHICLE);
	DDX_Control(pDX,IDC_SCLAIMS_UN_SUPPLYPOINT,m_IDC_SCLAIMS_UN_SUPPLYPOINT);
	DDX_Control(pDX,IDC_SCLAIMS_UN_SUPPLYTRAIN,m_IDC_SCLAIMS_UN_SUPPLYTRAIN);
	DDX_Control(pDX,IDC_SCLAIMS_UN_MARSHALLINGYARD,m_IDC_SCLAIMS_UN_MARSHALLINGYARD);
	DDX_Control(pDX,IDC_SCLAIMS_UN_BRIDGE,m_IDC_SCLAIMS_UN_BRIDGE);
	DDX_Control(pDX,IDC_SCLAIMS_UN_AIRFIELDS,m_IDC_SCLAIMS_UN_AIRFIELDS);
	DDX_Control(pDX,IDC_SCLAIMS_UN_ARTILLERYPOSITION,m_IDC_SCLAIMS_UN_ARTILLERYPOSITION);
	DDX_Control(pDX,IDC_SCLAIMS_UN_TROOPCONCENTRATION,m_IDC_SCLAIMS_UN_TROOPCONCENTRATION);
	DDX_Control(pDX,IDC_SCLAIMS_UN_TANK,m_IDC_SCLAIMS_UN_TANK);
	DDX_Control(pDX,IDC_SCLAIMS_RED_SUPPLYVEHICLE,m_IDC_SCLAIMS_RED_SUPPLYVEHICLE);
	DDX_Control(pDX,IDC_SCLAIMS_RED_SUPPLYPOINT,m_IDC_SCLAIMS_RED_SUPPLYPOINT);
	DDX_Control(pDX,IDC_SCLAIMS_RED_SUPPLYTRAIN,m_IDC_SCLAIMS_RED_SUPPLYTRAIN);
	DDX_Control(pDX,IDC_SCLAIMS_RED_MARSHALLINGYARD,m_IDC_SCLAIMS_RED_MARSHALLINGYARD);
	DDX_Control(pDX,IDC_SCLAIMS_RED_BRIDGE,m_IDC_SCLAIMS_RED_BRIDGE);
	DDX_Control(pDX,IDC_SCLAIMS_RED_AIRFIELDS,m_IDC_SCLAIMS_RED_AIRFIELDS);
	DDX_Control(pDX,IDC_SCLAIMS_RED_ARTILLERYPOSITION,m_IDC_SCLAIMS_RED_ARTILLERYPOSITION);
	DDX_Control(pDX,IDC_SCLAIMS_RED_TROOPCONCENTRATION,m_IDC_SCLAIMS_RED_TROOPCONCENTRATION);
	DDX_Control(pDX,IDC_SCLAIMS_RED_TANK,m_IDC_SCLAIMS_RED_TANK);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSQuickGroundClaims, CDialog)
	//{{AFX_MSG_MAP(CSQuickGroundClaims)
	ON_WM_PAINT()
	ON_WM_CANCELMODE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSQuickGroundClaims message handlers

void CSQuickGroundClaims::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	
	// Do not call CDialog::OnPaint() for painting messages
}

void CSQuickGroundClaims::OnCancelMode() 
{
	CDialog::OnCancelMode();
	
	// TODO: Add your message handler code here
	
}

BOOL CSQuickGroundClaims::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	GETDLGITEM(IDC_SCLAIMS_PLAYER_SUPPLYVEHICLE		)->SetString(CSprintf("%4i",MMC.debrief.playerqmcounts[Debrief::TRUCK]));
	GETDLGITEM(IDC_SCLAIMS_PLAYER_SUPPLYPOINT		)->SetString(CSprintf("%4i",MMC.debrief.playerqmcounts[Debrief::SUPPLY]));
	GETDLGITEM(IDC_SCLAIMS_PLAYER_SUPPLYTRAIN		)->SetString(CSprintf("%4i",MMC.debrief.playerqmcounts[Debrief::TRAIN]));
	GETDLGITEM(IDC_SCLAIMS_PLAYER_MARSHALLINGYARD	)->SetString(CSprintf("%4i",MMC.debrief.playerqmcounts[Debrief::MARTYARD]));
	GETDLGITEM(IDC_SCLAIMS_PLAYER_BRIDGE			)->SetString(CSprintf("%4i",MMC.debrief.playerqmcounts[Debrief::RAILBRIDGE]));
	GETDLGITEM(IDC_SCLAIMS_PLAYER_AIRFIELDS			)->SetString(CSprintf("%4i",MMC.debrief.playerqmcounts[Debrief::AIRFIELD]));
	GETDLGITEM(IDC_SCLAIMS_PLAYER_ARTILLERYPOSITION	)->SetString(CSprintf("%4i",MMC.debrief.playerqmcounts[Debrief::ARTILLERY]));
	GETDLGITEM(IDC_SCLAIMS_PLAYER_TROOPCONCENTRATION)->SetString(CSprintf("%4i",MMC.debrief.playerqmcounts[Debrief::TROOPS]));
	GETDLGITEM(IDC_SCLAIMS_PLAYER_TANK				)->SetString(CSprintf("%4i",MMC.debrief.playerqmcounts[Debrief::TANK]));
	GETDLGITEM(IDC_SCLAIMS_UN_SUPPLYVEHICLE			)->SetString(CSprintf("%4i",MMC.debrief.unqmcounts[Debrief::TRUCK]));
	GETDLGITEM(IDC_SCLAIMS_UN_SUPPLYPOINT			)->SetString(CSprintf("%4i",MMC.debrief.unqmcounts[Debrief::SUPPLY]));
	GETDLGITEM(IDC_SCLAIMS_UN_SUPPLYTRAIN			)->SetString(CSprintf("%4i",MMC.debrief.unqmcounts[Debrief::TRAIN]));
	GETDLGITEM(IDC_SCLAIMS_UN_MARSHALLINGYARD		)->SetString(CSprintf("%4i",MMC.debrief.unqmcounts[Debrief::MARTYARD]));
	GETDLGITEM(IDC_SCLAIMS_UN_BRIDGE				)->SetString(CSprintf("%4i",MMC.debrief.unqmcounts[Debrief::RAILBRIDGE]));
	GETDLGITEM(IDC_SCLAIMS_UN_AIRFIELDS				)->SetString(CSprintf("%4i",MMC.debrief.unqmcounts[Debrief::AIRFIELD]));
	GETDLGITEM(IDC_SCLAIMS_UN_ARTILLERYPOSITION		)->SetString(CSprintf("%4i",MMC.debrief.unqmcounts[Debrief::ARTILLERY]));
	GETDLGITEM(IDC_SCLAIMS_UN_TROOPCONCENTRATION	)->SetString(CSprintf("%4i",MMC.debrief.unqmcounts[Debrief::TROOPS]));
	GETDLGITEM(IDC_SCLAIMS_UN_TANK					)->SetString(CSprintf("%4i",MMC.debrief.unqmcounts[Debrief::TANK]));
	GETDLGITEM(IDC_SCLAIMS_RED_SUPPLYVEHICLE		)->SetString(CSprintf("%4i",MMC.debrief.redqmcounts[Debrief::TRUCK]));
	GETDLGITEM(IDC_SCLAIMS_RED_SUPPLYPOINT			)->SetString(CSprintf("%4i",MMC.debrief.redqmcounts[Debrief::SUPPLY]));
	GETDLGITEM(IDC_SCLAIMS_RED_SUPPLYTRAIN			)->SetString(CSprintf("%4i",MMC.debrief.redqmcounts[Debrief::TRAIN]));
	GETDLGITEM(IDC_SCLAIMS_RED_MARSHALLINGYARD		)->SetString(CSprintf("%4i",MMC.debrief.redqmcounts[Debrief::MARTYARD]));
	GETDLGITEM(IDC_SCLAIMS_RED_BRIDGE				)->SetString(CSprintf("%4i",MMC.debrief.redqmcounts[Debrief::RAILBRIDGE]));
	GETDLGITEM(IDC_SCLAIMS_RED_AIRFIELDS				)->SetString(CSprintf("%4i",MMC.debrief.redqmcounts[Debrief::AIRFIELD]));
	GETDLGITEM(IDC_SCLAIMS_RED_ARTILLERYPOSITION	)->SetString(CSprintf("%4i",MMC.debrief.redqmcounts[Debrief::ARTILLERY]));
	GETDLGITEM(IDC_SCLAIMS_RED_TROOPCONCENTRATION	)->SetString(CSprintf("%4i",MMC.debrief.redqmcounts[Debrief::TROOPS]));
	GETDLGITEM(IDC_SCLAIMS_RED_TANK					)->SetString(CSprintf("%4i",MMC.debrief.redqmcounts[Debrief::TANK]));







	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
