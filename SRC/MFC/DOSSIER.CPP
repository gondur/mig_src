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

// Dossier.cpp : implementation file
//

#include "stdafx.h"
#include "mig.h"
#include "Dossier.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#ifndef THIS_FILE_DEFINED
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif

/////////////////////////////////////////////////////////////////////////////
// CTargetDossier dialog


CTargetDossier::CTargetDossier(CWnd* pParent /*=NULL*/)
	: RowanDialog(CTargetDossier::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTargetDossier)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CTargetDossier::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTargetDossier)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTargetDossier, CDialog)
	//{{AFX_MSG_MAP(CTargetDossier)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()



RDialog* CTargetDossier::MakeSheet(CRect r,UniqueID item)
{

	info_base* p=*Persons2::ConvertPtrUID(item);
	UniqueID	sgt;
	if (p && p->SGT!=UID_NULL)
		sgt=p->SGT;
	else
	{
		sgt=item;
		item=UID_NULL;
	}
	int uidband;
	uidband=Persons2::getbandfromUID(sgt);
	if (uidband!=RedRailBand && uidband!=RedRoadBAND)
		SupplyTree::CheckTargetLoaded(sgt);
	FileNum backdrop;

	if (	 ( 	(SupplyTree::WestRoute.frontline->forward->suppliee->associated_item == sgt)
			||	(SupplyTree::CentralRoute.frontline->forward->suppliee->associated_item == sgt)
			||	(SupplyTree::EastRoute.frontline->forward->suppliee->associated_item == sgt)
			 )
		)
		backdrop = FIL_MAP_ARMY;
	else
	{
		switch (uidband)
		{
			case		AmberBridgeBAND:
			{
				backdrop = FIL_MAP_CHOKEPOINTS;
				break;
			}
			case		RedRailBand:
			case		RedRoadBAND:
			{
				backdrop = FIL_MAP_TRAFFIC;
				break;
			}
			case		AmberAirfieldBAND:
			{
				backdrop = FIL_MAP_AIRFIELD;
				break;
			}
			default:
			{
				backdrop = FIL_MAP_SUPPLY;
				break;
			}

		}
	}
	
	

	RDialog* rv=
	MakeTopDialog(r,
			DialList(DialBox(backdrop/*IDB_BBC3*/,new CTargetDossier,Edges(EDGE::ALIGN_MIN,EDGE::ALIGN_MIN,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE)),
			
					HTabBox(FIL_NULL,IdList(IDS_DETAILS,IDS_DAMAGE,IDS_NOTES),Edges(EDGE::ALIGN_MIN,EDGE::ALIGN_MIN,EDGE::ALIGN_MAX,EDGE::ALIGN_MAX), 
		  							DialBox(FIL_NULL/*IDB_BBC3*/,new CGeneral(sgt,item)),
		  							DialBox(FIL_NULL/*IDB_BBC3*/,new CDamage(sgt,item)),
		  							DialBox(FIL_NULL/*IDB_BBC3*/,new CNotes(sgt,item))
							),
					DialBox(FIL_NULL,new DossierButtons(sgt),Edges(EDGE::ALIGN_MIN,EDGE::ALIGN_MAX,EDGE::ALIGN_MAX,EDGE::ALIGN_MAX))
			  		)
			     );
	if (item)
	 	((CRTabs*)rv->fchild->sibling->GetDlgItem(IDJ_TABCTRL))->SelectTab(1);

	return rv;
}

BOOL CTargetDossier::OnInitDialog() 
{
	CDialog::OnInitDialog();
	

//	RDialog* parent=(RDialog*)GetParent();
//	parent->SetMaxSize(CRect(0,0,350,350));
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
