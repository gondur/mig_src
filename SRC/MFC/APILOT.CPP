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

// APilot.cpp : implementation file
//

#include "stdafx.h"
#include "mig.h"
#include "APilot.h"
#include "rcombo.h"
#include "winmove.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#ifndef THIS_FILE_DEFINED
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif

/////////////////////////////////////////////////////////////////////////////
// CAutoPilot dialog


CAutoPilot::CAutoPilot(CWnd* pParent /*=NULL*/)
	: RowanDialog(CAutoPilot::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAutoPilot)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CAutoPilot::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAutoPilot)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	DDX_Control(pDX,IDC_SDETAIL1,m_IDC_SDETAIL1);
	DDX_Control(pDX,IDC_RSTATICCTRL2,m_IDC_RSTATICCTRL2);
	DDX_Control(pDX,IDC_RSTATICCTRL3,m_IDC_RSTATICCTRL3);
	DDX_Control(pDX,IDC_RSTATICCTRL4,m_IDC_RSTATICCTRL4);
	DDX_Control(pDX,IDC_RSTATICCTRL5,m_IDC_RSTATICCTRL5);
	DDX_Control(pDX,IDC_RSTATICCTRL6,m_IDC_RSTATICCTRL6);
	DDX_Control(pDX,IDC_RSTATICCTRL7,m_IDC_RSTATICCTRL7);
	DDX_Control(pDX,IDC_RSTATICCTRL8,m_IDC_RSTATICCTRL8);
	DDX_Control(pDX,IDC_RSTATICCTRL9,m_IDC_RSTATICCTRL9);
	DDX_Control(pDX,IDC_RSTATICCTRL10,m_IDC_RSTATICCTRL10);
	DDX_Control(pDX,IDC_RSTATICCTRL12,m_IDC_RSTATICCTRL12);
	DDX_Control(pDX, IDC_CBO_FILTERING, m_IDC_CBO_FILTERING);
	DDX_Control(pDX, IDC_CBO_TRANSPARENCY, m_IDC_CBO_TRANSPARENCY);
	DDX_Control(pDX, IDC_CBO_TEXTUREQUALITY, m_IDC_CBO_TEXTUREQUALITY);
	DDX_Control(pDX, IDC_CBO_TREES, m_IDC_CBO_TREES);
	DDX_Control(pDX, IDC_CBO_ROUTES, m_IDC_CBO_ROUTES);
	DDX_Control(pDX, IDC_CBO_ACSHADOWS, m_IDC_CBO_ACSHADOWS);
	DDX_Control(pDX, IDC_CBO_ITEMSHADOWS, m_IDC_CBO_ITEMSHADOWS);
	DDX_Control(pDX, IDC_CBO_HORIZONFADE, m_IDC_CBO_HORIZONFADE);
	DDX_Control(pDX, IDC_CBO_HORIZON_DISTANCE, m_IDC_CBO_HORIZON_DISTANCE);
	DDX_Control(pDX, IDC_CBO_CONTOUR_DETAIL, m_IDC_CBO_CONTOUR_DETAIL);

	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAutoPilot, CDialog)
	//{{AFX_MSG_MAP(CAutoPilot)
	ON_WM_DESTROY()
	ON_WM_TIMER()
	ON_WM_CLOSE()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAutoPilot message handlers

//TEMP	SETFIELD(CHAR(filtering,0,1),						IDC_CBO_FILTERING,RESCOMBO(NONE,4),		NOLEVEL)	
//TEMP	SETFIELD(CHAR(textureQuality,0,1),					IDC_CBO_TEXTUREQUALITY,RESCOMBO(BLMHT_BOT,5),NOLEVEL)	


#define OPTIONS	\
	SETFIELD(BIT(detail_3d,DETAIL3D_TRANSSMOKE),		IDC_CBO_TRANSPARENCY,RESCOMBO(OFF,2),	NOLEVEL)\
	SETFIELD(BIT(detail_3d,DETAIL3D_INCONSEQUENTIALS),	IDC_CBO_TREES,RESCOMBO(OFF,2),			NOLEVEL)\
	SETFIELD(BIT(detail_3d,DETAIL3D_ROUTES),			IDC_CBO_ROUTES,RESCOMBO(OFF,2),			NOLEVEL)\
	SETFIELD(BIT(detail_3d,DETAIL3D_AIRCRAFTSHADOWS),	IDC_CBO_ACSHADOWS,RESCOMBO(OFF,2),		NOLEVEL)\
	SETFIELD(BIT(detail_3d,DETAIL3D_ITEMSHADOWS),		IDC_CBO_ITEMSHADOWS,RESCOMBO(OFF,2),	NOLEVEL)\
	SETFIELD(BIT(detail_3d,DETAIL3D_HORIZONFADE),		IDC_CBO_HORIZONFADE,RESCOMBO(DIST_NEAR,2),	NOLEVEL)\
	SETFIELD(BIT(detail_3d,DETAIL3D_HORIZONDIST),		IDC_CBO_HORIZON_DISTANCE,RESCOMBO(DIST_NEAR,2),NOLEVEL)\
	SETFIELD(BIT(detail_3d,DETAIL3D_CONTOURDETAIL),		IDC_CBO_CONTOUR_DETAIL,RESCOMBO(LOWCONTOUR,2),	NOLEVEL)\
	SETFIELD(CHAR(filtering,0,1),						IDC_CBO_FILTERING,RESCOMBO(NONE,4),		NOLEVEL)\
	SETFIELD(CHAR(textureQuality,0,1),					IDC_CBO_TEXTUREQUALITY,RESCOMBO(BLMHT_BOT,5),NOLEVEL)

//#define FILTER_OPTION(p1)	\
//	SETFIELD(CHAR(filtering,0,1),						IDC_CBO_FILTERING,RESCOMBO(NONE,(p1)),		NOLEVEL)
//
//#define TEXTURE_OPTION(p1)	\
//	SETFIELD(CHAR(textureQuality,0,1),					IDC_CBO_TEXTUREQUALITY,RESCOMBO(BLMHT_BOT,(p1)),NOLEVEL)

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		OnInitDialog
//Author		Paul.   
//Date			Thu 10 Dec 1998
//------------------------------------------------------------------------------
BOOL CAutoPilot::OnInitDialog()
{
#define	SG2C_DISPLAY	setlevel
#include "sg2combo.h"

	CDialog::OnInitDialog();

	SWord filterOpt;

	if (Save_Data.fSoftware)	filterOpt=1;
//dead	else						filterOpt=4;

//TEMP	FILTER_OPTION(filterOpt)
//TEMP	TEXTURE_OPTION(5)
	OPTIONS
	
	m_IDC_CBO_FILTERING.SetCircularStyle(TRUE);
	m_IDC_CBO_TRANSPARENCY.SetCircularStyle(TRUE);
	m_IDC_CBO_TEXTUREQUALITY.SetCircularStyle(TRUE);
	m_IDC_CBO_TREES.SetCircularStyle(TRUE);
	m_IDC_CBO_ROUTES.SetCircularStyle(TRUE);
	m_IDC_CBO_ACSHADOWS.SetCircularStyle(TRUE);
	m_IDC_CBO_ITEMSHADOWS.SetCircularStyle(TRUE);
	m_IDC_CBO_HORIZONFADE.SetCircularStyle(TRUE);
	m_IDC_CBO_HORIZON_DISTANCE.SetCircularStyle(TRUE);
	m_IDC_CBO_CONTOUR_DETAIL.SetCircularStyle(TRUE);


	ThreeDee2Pref_Timer=SetTimer(TIMER_PREFS3D2,0,NULL);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CAutoPilot::OnDestroy() 
{
	CDialog::OnDestroy();
	
	KillTimer(ThreeDee2Pref_Timer);
}

void CAutoPilot::OnTimer(UINT nIDEvent) 
{
	if (nIDEvent==ThreeDee2Pref_Timer && _DPlay.PlayerCreated)
	{
		_DPlay.UIUpdateMainSheet();
	}

	CDialog::OnTimer(nIDEvent);
}

#define	SG2C_WRITEBACK
#include "sg2combo.h"

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		OnClose
//Author		Paul.   
//Date			Thu 10 Dec 1998
//------------------------------------------------------------------------------
void CAutoPilot::OnClose()
{
	SWord filterOpt;

	if (Save_Data.fSoftware)	filterOpt=1;
	else						filterOpt=4;

//	FILTER_OPTION(filterOpt)
//	TEXTURE_OPTION(5)
	OPTIONS	
	CDialog::OnClose();
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		PreDestroyPanel
//Author		Paul.   
//Date			Thu 10 Dec 1998
//------------------------------------------------------------------------------
void CAutoPilot::PreDestroyPanel()
{
	OPTIONS
}

#define SG2C_CLEANUP
#include "sg2combo.h"

BEGIN_EVENTSINK_MAP(CAutoPilot, CDialog)
    //{{AFX_EVENTSINK_MAP(CAutoPilot)
	ON_EVENT(CAutoPilot, IDC_CBO_FILTERING, 1 /* TextChanged */, OnTextChangedCboFiltering, VTS_BSTR)
	ON_EVENT(CAutoPilot, IDC_CBO_TEXTUREQUALITY, 1 /* TextChanged */, OnTextChangedCboQuality, VTS_BSTR)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CAutoPilot::OnTextChangedCboFiltering(LPCTSTR text)
{

}
void CAutoPilot::OnTextChangedCboQuality(LPCTSTR text)
{

}
