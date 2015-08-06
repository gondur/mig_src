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

// WPBut.cpp : implementation file
//

#include "stdafx.h"
#include "mig.h"
#include "WPBut.h"
#include	<afxpriv2.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#ifndef THIS_FILE_DEFINED
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif

/////////////////////////////////////////////////////////////////////////////
// WaypointButtons dialog


WaypointButtons::WaypointButtons(CWnd* pParent /*=NULL*/)
	: RowanDialog(WaypointButtons::IDD, pParent)
{
	//{{AFX_DATA_INIT(WaypointButtons)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void WaypointButtons::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(WaypointButtons)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	DDX_Control(pDX,IDC_INSERT,m_IDC_INSERT);
	DDX_Control(pDX,IDC_DELETE,m_IDC_DELETE);
	DDX_Control(pDX,IDC_MOVE,m_IDC_MOVE);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(WaypointButtons, CDialog)
	//{{AFX_MSG_MAP(WaypointButtons)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// WaypointButtons message handlers
void WaypointButtons::FireMessageToSibling(int buttonID,int eventid)
{
	//need to find right sibling!!!
	DISPPARAMS	d={0};
	EXCEPINFO	e={0};
	UINT	i=0;
	AFX_EVENT event(AFX_EVENT::event,eventid,&d,&e,&i);
	for (RowanDialog* sib=(RowanDialog*) parent->fchild;sib;sib=(RowanDialog*)sib->sibling)
		if (sib!=this && sib->acnum==-1)
		{	sib->OnCmdMsg(buttonID,CN_EVENT,&event,NULL);
			return;	
		}
}

BEGIN_EVENTSINK_MAP(WaypointButtons, CDialog)
	ON_EVENT_RANGE(WaypointButtons, 1,9999, 1 /* Clicked */, OnClicked, VTS_I4)
    //{{AFX_EVENTSINK_MAP(WaypointButtons)
	ON_EVENT(WaypointButtons, IDC_MOVE, 1 /* Clicked */, OnClickedMove, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()


void WaypointButtons::OnClicked(int id) 
{
	// TODO: Add your control notification handler code here
	FireMessageToSibling(id, 1 /* Clicked */);
	
}

void	WaypointButtons::RefreshData(int effect)
{
	CRButton*	insbut = GETDLGITEM(IDC_INSERT);
	CRButton*	delbut = GETDLGITEM(IDC_DELETE);

	switch (effect)
	{
		case  CWPShare::INSONDELON:
		{
			insbut->SetForeColor(RGB(255,255,0));
			delbut->SetForeColor(RGB(255,255,0));
			insbut->SetDisabled(false);
			delbut->SetDisabled(false);
			break;
		}
		case  CWPShare::INSONDELOFF:
		{
			insbut->SetForeColor(RGB(255,255,0));
			delbut->SetForeColor(RGB(55,55,55));
			insbut->SetDisabled(false);
			delbut->SetDisabled(true);
			break;
		}
		case  CWPShare::INSOFFDELOFF:
		{
			insbut->SetForeColor(RGB(55,55,55));
			delbut->SetForeColor(RGB(55,55,55));
			insbut->SetDisabled(true);
			delbut->SetDisabled(true);
			break;
		}
		case  CWPShare::INSOFFDELON:
		{
			insbut->SetForeColor(RGB(55,55,55));
			delbut->SetForeColor(RGB(255,255,0));
			insbut->SetDisabled(true);
			delbut->SetDisabled(false);
			break;
		}

	}


}

void WaypointButtons::OnClickedMove() 
{
}
