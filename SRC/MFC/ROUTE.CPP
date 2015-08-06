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

// Route.cpp : implementation file
//

#include "stdafx.h"
#include "mig.h"
#include "Route.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#ifndef THIS_FILE_DEFINED
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif

/////////////////////////////////////////////////////////////////////////////
// CRoute dialog


CRoute::CRoute(int pack,CWnd* pParent /*=NULL*/)
	: RowanDialog(CRoute::IDD, pParent)
{
	SetProjSpecific(pack);
	radioenabled=true;
	//{{AFX_DATA_INIT(CRoute)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


CRoute::CRoute(int pack,int id,CWnd* pParent /*=NULL*/)
	: RowanDialog(id, pParent)
{
	SetProjSpecific(pack);
}


void CRoute::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRoute)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	DDX_Control(pDX,IDC_MODE,m_IDC_MODE);
	//}}AFX_DATA_MAP

	CRRadio* pradio;
	pradio=GETDLGITEM(IDC_MODE);
	pradio->AddButton(RESSTRING(SUMMARY));
	pradio->AddButton(RESSTRING(DETAIL));
// 	parent->SetMaxSize(CRect(0,0,2000,2000));	


}


BEGIN_MESSAGE_MAP(CRoute, CDialog)
	//{{AFX_MSG_MAP(CRoute)
	ON_WM_ENABLE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRoute message handlers

BEGIN_EVENTSINK_MAP(CRoute, CDialog)
    //{{AFX_EVENTSINK_MAP(CRoute)
	ON_EVENT(CRoute, IDC_MODE, 1 /* Selected */, OnSelectedMode, VTS_I4)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()
void	CRoute::RefreshData(int effect)
{
	CRRadio* pradio;
	pradio=GETDLGITEM(IDC_MODE);
	int setting=pradio->IsWindowEnabled();
	switch (effect)
	{
	case CWPShare::RADIODETAIL:

		pradio->SetCurrentSelection(1);
		OnSelectedMode(1);
	break;
	case CWPShare::RADIOLIST:
		pradio->SetCurrentSelection(0);
		OnSelectedMode(0);
	break;
	case CWPShare::RADIOENABLE:
		pradio->EnableWindow(true);
		radioenabled=true;
	break;
	case CWPShare::RADIODISABLE:
		pradio->EnableWindow(false);
		radioenabled=false;

	break;


	}
}
void CRoute::OnSelectedMode(long ButtonNum) 
{
	// TODO: Add your control notification handler code here
	//OK.. this is the complex bit...
	CRRadio* pradio;
	pradio=GETDLGITEM(IDC_MODE);
 	int setting=pradio->GetCurrentSelection();
	if (!radioenabled)
		pradio->SetCurrentSelection(1-setting);
	else
	{

		RowanDialog	*dlist,*ddet,*dbut;
		for (RowanDialog* ctl=(RowanDialog*)fchild;ctl;ctl=(RowanDialog*)ctl->sibling)
		if (ctl->packnum==-1)	
			dbut=ctl;			//buttons don't know about packages
		else
			if (ctl->acnum==-1)
				dlist=ctl;		//ac num 
			else
				ddet=ctl;
		if (ddet->acnum==0)
		{
	//		CRRadio* pradio;
	//		pradio=(CRRadio*)GetDlgItem(IDC_MODE);
			pradio->SetCurrentSelection(0);
		}
		else
		{
			if (ButtonNum==0)
				ddet->RefreshData(1);
			CRect parentpos;
			GetWindowRect(parentpos);
			CPoint parentoff(parentpos.left,parentpos.top);
			CRect dlistpos;
			dlist->GetWindowRect(dlistpos);
			CRect ddetpos;
			ddet->GetWindowRect(ddetpos);
			dlistpos-=parentoff;
			ddetpos-=parentoff;
			dlist->MoveWindow(ddetpos);
			ddet->MoveWindow(dlistpos);
		}
	}
}

void CRoute::OnEnable(BOOL bEnable) 
{
	CDialog::OnEnable(bEnable);
	
	// TODO: Add your message handler code here
	
}
