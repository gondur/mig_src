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

// DosBut.cpp : implementation file
//

#include "stdafx.h"
#include "mig.h"
#include "DosBut.h"
#include "MigView.h"
#include "overlay.h"
#define F_COMMON
#define F_SOUNDS
#define F_BATTLE
#undef F_GRAFIX
#include "files.g"

#ifdef _DEBUG
#define new DEBUG_NEW
#ifndef THIS_FILE_DEFINED
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif
/////////////////////////////////////////////////////////////////////////////
// DossierButtons dialog


DossierButtons::DossierButtons(int uid,CWnd* pParent /*=NULL*/)
	: RowanDialog(DossierButtons::IDD, pParent)
{
	SetProjSpecific(-1,uid);
	//{{AFX_DATA_INIT(DossierButtons)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void DossierButtons::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);



//	CRButton*	but = GetDlgItem(IDC_AUTHORISE);
//	int	pack=Todays_Packages.FindPackage();
//	if  (		(MMC.indebrief)
//			||	(pack < 0)
//		)
//	{
//		but->SetForeColor(RGB(80,80,80));
//		but->SetDisabled(true);
//	}
//	else
//	{
//		but->SetForeColor(RGB(255,255,0));
//		but->SetDisabled(false);
//	}

	
	//{{AFX_DATA_MAP(DossierButtons)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	DDX_Control(pDX,IDC_AUTHORISE	,m_IDC_AUTHORISE);
	DDX_Control(pDX,IDC_CENTRE		,m_IDC_CENTRE);
	DDX_Control(pDX,IDC_PHOTO 		,m_IDC_PHOTO);
	DDX_Control(pDX,IDC_Zoom		,m_IDC_Zoom);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DossierButtons, CDialog)
	//{{AFX_MSG_MAP(DossierButtons)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DossierButtons message handlers

BEGIN_EVENTSINK_MAP(DossierButtons, CDialog)
    //{{AFX_EVENTSINK_MAP(DossierButtons)
	ON_EVENT(DossierButtons, IDC_AUTHORISE, 1 /* Clicked */, OnClickedAuthorise, VTS_NONE)
	ON_EVENT(DossierButtons, IDC_CENTRE, 1 /* Clicked */, OnClickedCentre, VTS_NONE)
	ON_EVENT(DossierButtons, IDC_PHOTO, 1 /* Clicked */, OnClickedPhoto, VTS_NONE)
	ON_EVENT(DossierButtons, IDC_Zoom, 1 /* Clicked */, OnClickedZoom, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void DossierButtons::OnClickedAuthorise() 
{
	MainToolBar().OpenLoadProfile(wavenum);
	
}

void DossierButtons::OnClickedCentre() 
{
	m_pView->ZoomToUID(UniqueID(wavenum),m_pView->m_zoom);
	RDialog::m_pView->m_mapdlg.ResetIcon((UniqueID)wavenum);
}

void DossierButtons::OnClickedPhoto() 
{
#ifndef NDEBUG
#define PLACEMENT	CRect(0,0,512,384)
#else
#define	PLACEMENT	Place(POSN_CENTRE,POSN_CENTRE, 0, 0)
#endif
//	#define PLACEMENT	CRect(0,0,512,384)
	UniqueID targID=UniqueID(wavenum);
	CString tname=GetTargName(targID);
	OverLay.SetTargName((char*)LPCTSTR(tname));
	OverLay.loader_art=FIL_PHOTOART;	//FIL_PHOTOART_800;
	LogChild(0,MakeTopDialog(PLACEMENT,DialBox(OverLay.loader_art,new Rtestsh1(UniqueID(targID)),EDGES_NOSCROLLBARS)));
	Rtestsh1::Start3d(Rtestsh1::S3D_DONEBACK);
}

void DossierButtons::OnClickedZoom() 
{
	m_pView->ZoomToUID(UniqueID(wavenum),m_pView->m_zoom*2);
	RDialog::m_pView->m_mapdlg.ResetIcon((UniqueID)wavenum);
	
}

BOOL DossierButtons::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
   	SupplyTree::Supply2UID	relation;
	SupplyNode*	node=SupplyTree::FindSupplyNodeForItem((UniqueID)wavenum,&relation);
	int uidband=Persons2::getbandfromUID((UniqueID)wavenum);
	
	bool	canauthorise = true;
	if ((node) && (node->status == BEHINDBLUELINES)) 
		canauthorise = false;
	if(uidband == AmberAirfieldBAND)
	{
		for (int af=0;SupplyTree::airfieldinfo[af].nationality!=NAT_ALIGN;af++)
		{
			if (		(SupplyTree::airfieldinfo[af].airfield == (UniqueID)wavenum)
					&&	(SupplyTree::airfieldinfo[af].nationality == NAT_BLUE)
				)
			{
				canauthorise = false;
				break;
			}

		}
	}

	CRButton*	but = GETDLGITEM(IDC_AUTHORISE);
	int	pack=Todays_Packages.FindPackage();
	if  (		(MMC.indebrief)
			||	(pack < 0)
			||	(		(Todays_Packages.FindSquadExlMedBombers() < 0) //RDH 25/06/99
					&&	(Todays_Packages.CAPAircraftcnt() < 32)						  //RDH 25/06/99
				)	
			||	(!canauthorise)
		)
	{
		but->SetForeColor(RGB(80,80,80));
		but->SetDisabled(true);
	}
	else
	{
		but->SetForeColor(RGB(255,255,0));
		but->SetDisabled(false);
	}


	but = GETDLGITEM(IDC_PHOTO);
	if  (		(uidband == RedRoadBAND)
			||	(uidband == RedRailBand)
		)
	{
		but->SetForeColor(RGB(80,80,80));
		but->SetDisabled(true);
	}
	else
	{
		but->SetForeColor(RGB(255,255,0));
		but->SetDisabled(false);
	}



	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
