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

// Paint.cpp : implementation file
//

#include "stdafx.h"
#include "mig.h"
#include "Paint.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#ifndef THIS_FILE_DEFINED
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif

/////////////////////////////////////////////////////////////////////////////
// CPaint dialog


CPaint::CPaint(int squadnum, int pilot,CWnd* pParent /*=NULL*/)
	: RowanDialog(CPaint::IDD, pParent)
{
		SetProjSpecific(-1,-1,squadnum, pilot);

	//{{AFX_DATA_INIT(CPaint)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CPaint::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPaint)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	DDX_Control(pDX,IDC_NOSEART_DEFAULT1,m_IDC_NOSEART_DEFAULT1);
	DDX_Control(pDX,IDC_NOSEART_DEFAULT2,m_IDC_NOSEART_DEFAULT2);
	DDX_Control(pDX,IDC_NOSEART_DEFAULT3,m_IDC_NOSEART_DEFAULT3);
	DDX_Control(pDX,IDC_NOSEART_DEFAULT4,m_IDC_NOSEART_DEFAULT4);
	DDX_Control(pDX,IDC_NOSEART_DEFAULT5,m_IDC_NOSEART_DEFAULT5);
	DDX_Control(pDX,IDC_NOSEART_DEFAULT6,m_IDC_NOSEART_DEFAULT6);
	DDX_Control(pDX,IDC_NOSEART_DEFAULT7,m_IDC_NOSEART_DEFAULT7);
	DDX_Control(pDX,IDC_NOSEART_DEFAULT8,m_IDC_NOSEART_DEFAULT8);
	DDX_Control(pDX,IDC_NOSEART_DEFAULT9,m_IDC_NOSEART_DEFAULT9);
	DDX_Control(pDX,IDC_NOSEART_DEFAULT10,m_IDC_NOSEART_DEFAULT10);
	DDX_Control(pDX,IDC_NOSEART_DEFAULT11,m_IDC_NOSEART_DEFAULT11);
	DDX_Control(pDX,IDC_NOSEART_DEFAULT12,m_IDC_NOSEART_DEFAULT12);
	DDX_Control(pDX,IDC_NOSEART_DEFAULT13,m_IDC_NOSEART_DEFAULT13);
	DDX_Control(pDX,IDC_NOSEART_DEFAULT14,m_IDC_NOSEART_DEFAULT14);
	DDX_Control(pDX,IDC_NOSEART_DEFAULT15,m_IDC_NOSEART_DEFAULT15);
	DDX_Control(pDX,IDC_NOSEART_DEFAULT16,m_IDC_NOSEART_DEFAULT16);
	DDX_Control(pDX,IDC_RRADIO_NOSESELECT,m_IDC_RRADIO_NOSESELECT);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPaint, CDialog)
	//{{AFX_MSG_MAP(CPaint)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPaint message handlers

void CPaint::DrawDecals()
{
	int decals;
	for(int i=0;i<16;i++)
	{ 
 		CRButton* rbutton;
		rbutton=GETDLGITEM(IDC_NOSEART_DEFAULT1+i);
		if (decalsset == 0)
			decals = i + FIL_NOSE_STD_1;
		else
			decals = i + FIL_NOSE_USER_1;

 		rbutton->SetNormalFileNum(decals);
		rbutton->SetPressedFileNum(1);
	}
}

BOOL CPaint::OnInitDialog() 
{
	CDialog::OnInitDialog();

	CString string;
	CRRadio* pradio;

	pradio=GETDLGITEM(IDC_RRADIO_NOSESELECT);
	string.LoadString(IDS_DEFAULT);
	pradio->AddButton(string);
	string.LoadString(IDS_USER);
	pradio->AddButton(string);	
	if (MMC.Active_Pilots[24*groupnum+acnum].decal < 16)
	{
		decalsset = 0;
		pradio->SetCurrentSelection(0);
	}
	else
	{
		decalsset = 16;
		pradio->SetCurrentSelection(1);
	}
	DrawDecals();


	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BEGIN_EVENTSINK_MAP(CPaint, CDialog)
    //{{AFX_EVENTSINK_MAP(CPaint)
	ON_EVENT(CPaint, IDC_RRADIO_NOSESELECT, 1 /* Selected */, OnSelectedRradioNoseselect, VTS_I4)
	ON_EVENT(CPaint, IDC_NOSEART_DEFAULT1, 1 /* Clicked */, OnClickedNoseartDefault1, VTS_NONE)
	ON_EVENT(CPaint, IDC_NOSEART_DEFAULT10, 1 /* Clicked */, OnClickedNoseartDefault10, VTS_NONE)
	ON_EVENT(CPaint, IDC_NOSEART_DEFAULT11, 1 /* Clicked */, OnClickedNoseartDefault11, VTS_NONE)
	ON_EVENT(CPaint, IDC_NOSEART_DEFAULT12, 1 /* Clicked */, OnClickedNoseartDefault12, VTS_NONE)
	ON_EVENT(CPaint, IDC_NOSEART_DEFAULT13, 1 /* Clicked */, OnClickedNoseartDefault13, VTS_NONE)
	ON_EVENT(CPaint, IDC_NOSEART_DEFAULT14, 1 /* Clicked */, OnClickedNoseartDefault14, VTS_NONE)
	ON_EVENT(CPaint, IDC_NOSEART_DEFAULT15, 1 /* Clicked */, OnClickedNoseartDefault15, VTS_NONE)
	ON_EVENT(CPaint, IDC_NOSEART_DEFAULT16, 1 /* Clicked */, OnClickedNoseartDefault16, VTS_NONE)
	ON_EVENT(CPaint, IDC_NOSEART_DEFAULT2, 1 /* Clicked */, OnClickedNoseartDefault2, VTS_NONE)
	ON_EVENT(CPaint, IDC_NOSEART_DEFAULT3, 1 /* Clicked */, OnClickedNoseartDefault3, VTS_NONE)
	ON_EVENT(CPaint, IDC_NOSEART_DEFAULT4, 1 /* Clicked */, OnClickedNoseartDefault4, VTS_NONE)
	ON_EVENT(CPaint, IDC_NOSEART_DEFAULT5, 1 /* Clicked */, OnClickedNoseartDefault5, VTS_NONE)
	ON_EVENT(CPaint, IDC_NOSEART_DEFAULT6, 1 /* Clicked */, OnClickedNoseartDefault6, VTS_NONE)
	ON_EVENT(CPaint, IDC_NOSEART_DEFAULT7, 1 /* Clicked */, OnClickedNoseartDefault7, VTS_NONE)
	ON_EVENT(CPaint, IDC_NOSEART_DEFAULT8, 1 /* Clicked */, OnClickedNoseartDefault8, VTS_NONE)
	ON_EVENT(CPaint, IDC_NOSEART_DEFAULT9, 1 /* Clicked */, OnClickedNoseartDefault9, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CPaint::OnSelectedRradioNoseselect(long ButtonNum) 
{
	if (decalsset == 0)
		decalsset = 16;
	else
		decalsset = 0;


	DrawDecals();


}
void CPaint::SelectNoseArt(int art)
{
  MMC.Active_Pilots[24*groupnum+acnum].decal = art + decalsset;
  OnOK();

}

void CPaint::OnClickedNoseartDefault1() 
{
	SelectNoseArt(0);
}

void CPaint::OnClickedNoseartDefault10() 
{
	SelectNoseArt(9);
}

void CPaint::OnClickedNoseartDefault11() 
{
	SelectNoseArt(10);
}

void CPaint::OnClickedNoseartDefault12() 
{
	SelectNoseArt(11);
}

void CPaint::OnClickedNoseartDefault13() 
{
	SelectNoseArt(12);
}

void CPaint::OnClickedNoseartDefault14() 
{
	SelectNoseArt(13);
}

void CPaint::OnClickedNoseartDefault15() 
{
	SelectNoseArt(14);
}

void CPaint::OnClickedNoseartDefault16() 
{
	SelectNoseArt(15);
}

void CPaint::OnClickedNoseartDefault2() 
{
	SelectNoseArt(1);
}

void CPaint::OnClickedNoseartDefault3() 
{
	SelectNoseArt(2);
}

void CPaint::OnClickedNoseartDefault4() 
{
	SelectNoseArt(3);
}

void CPaint::OnClickedNoseartDefault5() 
{
	SelectNoseArt(4);
}

void CPaint::OnClickedNoseartDefault6() 
{
	SelectNoseArt(5);
}

void CPaint::OnClickedNoseartDefault7() 
{
	SelectNoseArt(6);
}

void CPaint::OnClickedNoseartDefault8() 
{
	SelectNoseArt(7);
}

void CPaint::OnClickedNoseartDefault9() 
{
	SelectNoseArt(8);
}
void  CPaint::ParentDialClosed(RDialog*,int rv)
{
	OnOK();
}
