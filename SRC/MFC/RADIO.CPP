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

// Radio.cpp : implementation file
//

#include "stdafx.h"
#include "mig.h"
#include "Radio.h"
#include	"winmove.h"
#include	"comms.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#ifndef THIS_FILE_DEFINED
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif

/////////////////////////////////////////////////////////////////////////////
// CRadio dialog


CRadio::CRadio(CWnd* pParent /*=NULL*/)
	: RowanDialog(CRadio::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRadio)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CRadio::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRadio)
	DDX_Control(pDX, IDCX_PLAYERMESSAGE8, m_IDCX_PLAYERMESSAGE8);
	DDX_Control(pDX, IDCX_PLAYERMESSAGE7, m_IDCX_PLAYERMESSAGE7);
	DDX_Control(pDX, IDCX_PLAYERMESSAGE6, m_IDCX_PLAYERMESSAGE6);
	DDX_Control(pDX, IDCX_PLAYERMESSAGE5, m_IDCX_PLAYERMESSAGE5);
	DDX_Control(pDX, IDCX_PLAYERMESSAGE4, m_IDCX_PLAYERMESSAGE4);
	DDX_Control(pDX, IDCX_PLAYERMESSAGE3, m_IDCX_PLAYERMESSAGE3);
	DDX_Control(pDX, IDCX_PLAYERMESSAGE2, m_IDCX_PLAYERMESSAGE2);
	DDX_Control(pDX, IDCX_PLAYERMESSAGE1, m_IDCX_PLAYERMESSAGE1);
	DDX_Control(pDX,IDC_PLAYERMESSAGE1,m_IDC_PLAYERMESSAGE1);
	DDX_Control(pDX,IDC_PLAYERMESSAGE2,m_IDC_PLAYERMESSAGE2);
	DDX_Control(pDX,IDC_PLAYERMESSAGE3,m_IDC_PLAYERMESSAGE3);
	DDX_Control(pDX,IDC_PLAYERMESSAGE4,m_IDC_PLAYERMESSAGE4);
	DDX_Control(pDX,IDC_PLAYERMESSAGE5,m_IDC_PLAYERMESSAGE5);
	DDX_Control(pDX,IDC_PLAYERMESSAGE6,m_IDC_PLAYERMESSAGE6);
	DDX_Control(pDX,IDC_PLAYERMESSAGE7,m_IDC_PLAYERMESSAGE7);
	DDX_Control(pDX,IDC_PLAYERMESSAGE8,m_IDC_PLAYERMESSAGE8);
	DDX_Control(pDX,IDC_PLAYERMESSAGE9,m_IDC_PLAYERMESSAGE9);
	DDX_Control(pDX,IDC_PLAYERMESSAGE10,m_IDC_PLAYERMESSAGE10);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRadio, CDialog)
	//{{AFX_MSG_MAP(CRadio)
	ON_WM_TIMER()
	ON_WM_DESTROY()
	ON_EN_UPDATE(IDCX_PLAYERMESSAGE1, OnUpdatePlayermessage1)
	ON_EN_UPDATE(IDCX_PLAYERMESSAGE2, OnUpdatePlayermessage2)
	ON_EN_UPDATE(IDCX_PLAYERMESSAGE3, OnUpdatePlayermessage3)
	ON_EN_UPDATE(IDCX_PLAYERMESSAGE4, OnUpdatePlayermessage4)
	ON_EN_UPDATE(IDCX_PLAYERMESSAGE5, OnUpdatePlayermessage5)
	ON_EN_UPDATE(IDCX_PLAYERMESSAGE6, OnUpdatePlayermessage6)
	ON_EN_UPDATE(IDCX_PLAYERMESSAGE7, OnUpdatePlayermessage7)
	ON_EN_UPDATE(IDCX_PLAYERMESSAGE8, OnUpdatePlayermessage8)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRadio message handlers

void CRadio::OnTimer(UINT nIDEvent) 
{
	if (nIDEvent==radio_timer && _DPlay.PlayerCreated)
	{
		_DPlay.UIUpdateMainSheet();
	}

	CDialog::OnTimer(nIDEvent);
}

BOOL CRadio::OnInitDialog() 
{
	CREdit* editbox;
	CDialog::OnInitDialog();
	if (m_IDCX_PLAYERMESSAGE1.m_hWnd)
	{
		m_IDCX_PLAYERMESSAGE1.SetWindowText(_DPlay.Messages[_DPlay.mySlot][0]);
		m_IDCX_PLAYERMESSAGE2.SetWindowText(_DPlay.Messages[_DPlay.mySlot][1]);
		m_IDCX_PLAYERMESSAGE3.SetWindowText(_DPlay.Messages[_DPlay.mySlot][2]);
		m_IDCX_PLAYERMESSAGE4.SetWindowText(_DPlay.Messages[_DPlay.mySlot][3]);
		m_IDCX_PLAYERMESSAGE5.SetWindowText(_DPlay.Messages[_DPlay.mySlot][4]);
		m_IDCX_PLAYERMESSAGE6.SetWindowText(_DPlay.Messages[_DPlay.mySlot][5]);
		m_IDCX_PLAYERMESSAGE7.SetWindowText(_DPlay.Messages[_DPlay.mySlot][6]);
		m_IDCX_PLAYERMESSAGE8.SetWindowText(_DPlay.Messages[_DPlay.mySlot][7]);
		m_IDCX_PLAYERMESSAGE1.SetLimitText(RADIOMESSAGELEN-1);
		m_IDCX_PLAYERMESSAGE2.SetLimitText(RADIOMESSAGELEN-1);
		m_IDCX_PLAYERMESSAGE3.SetLimitText(RADIOMESSAGELEN-1);
		m_IDCX_PLAYERMESSAGE4.SetLimitText(RADIOMESSAGELEN-1);
		m_IDCX_PLAYERMESSAGE5.SetLimitText(RADIOMESSAGELEN-1);
		m_IDCX_PLAYERMESSAGE6.SetLimitText(RADIOMESSAGELEN-1);
		m_IDCX_PLAYERMESSAGE7.SetLimitText(RADIOMESSAGELEN-1);
		m_IDCX_PLAYERMESSAGE8.SetLimitText(RADIOMESSAGELEN-1);
	}
	else
	{
		editbox=GetDlgItem(IDC_PLAYERMESSAGE1);
		editbox->SetCaption(_DPlay.Messages[_DPlay.mySlot][0]);

		editbox=GetDlgItem(IDC_PLAYERMESSAGE2);
		editbox->SetCaption(_DPlay.Messages[_DPlay.mySlot][1]);

		editbox=GetDlgItem(IDC_PLAYERMESSAGE3);
		editbox->SetCaption(_DPlay.Messages[_DPlay.mySlot][2]);

		editbox=GetDlgItem(IDC_PLAYERMESSAGE4);
		editbox->SetCaption(_DPlay.Messages[_DPlay.mySlot][3]);

		editbox=GetDlgItem(IDC_PLAYERMESSAGE5);
		editbox->SetCaption(_DPlay.Messages[_DPlay.mySlot][4]);

		editbox=GetDlgItem(IDC_PLAYERMESSAGE6);
		editbox->SetCaption(_DPlay.Messages[_DPlay.mySlot][5]);

		editbox=GetDlgItem(IDC_PLAYERMESSAGE7);
		editbox->SetCaption(_DPlay.Messages[_DPlay.mySlot][6]);

		editbox=GetDlgItem(IDC_PLAYERMESSAGE8);
		editbox->SetCaption(_DPlay.Messages[_DPlay.mySlot][7]);
	}
//	editbox=GetDlgItem(IDC_PLAYERMESSAGE9);
//	editbox->SetCaption(_DPlay.Messages[_DPlay.mySlot][8]);
  
//	editbox=GetDlgItem(IDC_PLAYERMESSAGE10);
//	editbox->SetCaption(_DPlay.Messages[_DPlay.mySlot][9]);

	radio_timer=SetTimer(TIMER_RADIO,0,NULL);

	_DPlay.SendInRadioMessage();
	DPlay::H2H_Player[_DPlay.mySlot].status=CPS_RADIO;
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
void CRadio::OnOK() 
{

// get messages and put into comms text

	CREdit* editbox;
	CString	buffer;

	if (m_IDCX_PLAYERMESSAGE1.m_hWnd)
	{
	   m_IDCX_PLAYERMESSAGE1.GetWindowText(buffer);	strcpy(_DPlay.Messages[_DPlay.mySlot][0],buffer);
	   m_IDCX_PLAYERMESSAGE2.GetWindowText(buffer);	strcpy(_DPlay.Messages[_DPlay.mySlot][1],buffer);
	   m_IDCX_PLAYERMESSAGE3.GetWindowText(buffer);	strcpy(_DPlay.Messages[_DPlay.mySlot][2],buffer);
	   m_IDCX_PLAYERMESSAGE4.GetWindowText(buffer);	strcpy(_DPlay.Messages[_DPlay.mySlot][3],buffer);
	   m_IDCX_PLAYERMESSAGE5.GetWindowText(buffer);	strcpy(_DPlay.Messages[_DPlay.mySlot][4],buffer);
	   m_IDCX_PLAYERMESSAGE6.GetWindowText(buffer);	strcpy(_DPlay.Messages[_DPlay.mySlot][5],buffer);
	   m_IDCX_PLAYERMESSAGE7.GetWindowText(buffer);	strcpy(_DPlay.Messages[_DPlay.mySlot][6],buffer);
	   m_IDCX_PLAYERMESSAGE8.GetWindowText(buffer);	strcpy(_DPlay.Messages[_DPlay.mySlot][7],buffer);

	}
	else
	{
		editbox=GetDlgItem(IDC_PLAYERMESSAGE1);
		buffer = editbox->GetCaption();
		strcpy(_DPlay.Messages[_DPlay.mySlot][0],buffer);

		editbox=GetDlgItem(IDC_PLAYERMESSAGE2);
		buffer = editbox->GetCaption();
		strcpy(_DPlay.Messages[_DPlay.mySlot][1],buffer);

		editbox=GetDlgItem(IDC_PLAYERMESSAGE3);
		buffer = editbox->GetCaption();
		strcpy(_DPlay.Messages[_DPlay.mySlot][2],buffer);

		editbox=GetDlgItem(IDC_PLAYERMESSAGE4);
		buffer = editbox->GetCaption();
		strcpy(_DPlay.Messages[_DPlay.mySlot][3],buffer);

		editbox=GetDlgItem(IDC_PLAYERMESSAGE5);
		buffer = editbox->GetCaption();
		strcpy(_DPlay.Messages[_DPlay.mySlot][4],buffer);

		editbox=GetDlgItem(IDC_PLAYERMESSAGE6);
		buffer = editbox->GetCaption();
		strcpy(_DPlay.Messages[_DPlay.mySlot][5],buffer);

		editbox=GetDlgItem(IDC_PLAYERMESSAGE7);
		buffer = editbox->GetCaption();
		strcpy(_DPlay.Messages[_DPlay.mySlot][6],buffer);

		editbox=GetDlgItem(IDC_PLAYERMESSAGE8);
		buffer = editbox->GetCaption();
		strcpy(_DPlay.Messages[_DPlay.mySlot][7],buffer);
	}
//	editbox=GetDlgItem(IDC_PLAYERMESSAGE9);
//	buffer = editbox->GetCaption();
//	strcpy(_DPlay.Messages[_DPlay.mySlot][8],buffer);

//	editbox=GetDlgItem(IDC_PLAYERMESSAGE10);
//	buffer = editbox->GetCaption();
//	strcpy(_DPlay.Messages[_DPlay.mySlot][9],buffer);
	_DPlay.SaveRadioMessages();
}
void CRadio::OnDestroy() 
{
	KillTimer(radio_timer);
	CDialog::OnDestroy();
}

BEGIN_EVENTSINK_MAP(CRadio, CDialog)
    //{{AFX_EVENTSINK_MAP(CRadio)
	ON_EVENT(CRadio, IDC_PLAYERMESSAGE10, 2 /* TextChanged */, OnTextChangedPlayermessage10, VTS_I4)
	ON_EVENT(CRadio, IDC_PLAYERMESSAGE1, 2 /* TextChanged */, OnTextChangedPlayermessage1, VTS_I4)
	ON_EVENT(CRadio, IDC_PLAYERMESSAGE2, 2 /* TextChanged */, OnTextChangedPlayermessage2, VTS_I4)
	ON_EVENT(CRadio, IDC_PLAYERMESSAGE3, 2 /* TextChanged */, OnTextChangedPlayermessage3, VTS_I4)
	ON_EVENT(CRadio, IDC_PLAYERMESSAGE4, 2 /* TextChanged */, OnTextChangedPlayermessage4, VTS_I4)
	ON_EVENT(CRadio, IDC_PLAYERMESSAGE5, 2 /* TextChanged */, OnTextChangedPlayermessage5, VTS_I4)
	ON_EVENT(CRadio, IDC_PLAYERMESSAGE6, 2 /* TextChanged */, OnTextChangedPlayermessage6, VTS_I4)
	ON_EVENT(CRadio, IDC_PLAYERMESSAGE7, 2 /* TextChanged */, OnTextChangedPlayermessage7, VTS_I4)
	ON_EVENT(CRadio, IDC_PLAYERMESSAGE8, 2 /* TextChanged */, OnTextChangedPlayermessage8, VTS_I4)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CRadio::OnTextChangedPlayermessage10(LPTSTR text) 
{
	// TODO: Add your control notification handler code here
	
}

void	DPlay::InitMessages()
{
	for (int n=0;n<NUMRADIOMESSAGES;n++)
		strcpy(Messages[mySlot][n],RESSTRING(L_RADIOMSG0+n));
}

void CRadio::OnTextChangedPlayermessage1(LPTSTR text) 
{
		trunc(text,RADIOMESSAGELEN - 1);
}

void CRadio::OnTextChangedPlayermessage2(LPTSTR text) 
{
		trunc(text,RADIOMESSAGELEN - 1);
}

void CRadio::OnTextChangedPlayermessage3(LPTSTR text) 
{
		trunc(text,RADIOMESSAGELEN - 1);
	
}

void CRadio::OnTextChangedPlayermessage4(LPTSTR text) 
{
		trunc(text,RADIOMESSAGELEN - 1);
	
}

void CRadio::OnTextChangedPlayermessage5(LPTSTR text) 
{
		trunc(text,RADIOMESSAGELEN - 1);
	
}

void CRadio::OnTextChangedPlayermessage6(LPTSTR text) 
{
		trunc(text,RADIOMESSAGELEN - 1);
	
}

void CRadio::OnTextChangedPlayermessage7(LPTSTR text) 
{
		trunc(text,RADIOMESSAGELEN - 1);
	
}

void CRadio::OnTextChangedPlayermessage8(LPTSTR text) 
{
		trunc(text,RADIOMESSAGELEN - 1);
	
}

void CRadio::OnUpdatePlayermessage1() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function to send the EM_SETEVENTMASK message to the control
	// with the ENM_UPDATE flag ORed into the lParam mask.
	
	// TODO: Add your control notification handler code here
	
}

void CRadio::OnUpdatePlayermessage2() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function to send the EM_SETEVENTMASK message to the control
	// with the ENM_UPDATE flag ORed into the lParam mask.
	
	// TODO: Add your control notification handler code here
	
}

void CRadio::OnUpdatePlayermessage3() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function to send the EM_SETEVENTMASK message to the control
	// with the ENM_UPDATE flag ORed into the lParam mask.
	
	// TODO: Add your control notification handler code here
	
}

void CRadio::OnUpdatePlayermessage4() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function to send the EM_SETEVENTMASK message to the control
	// with the ENM_UPDATE flag ORed into the lParam mask.
	
	// TODO: Add your control notification handler code here
	
}

void CRadio::OnUpdatePlayermessage5() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function to send the EM_SETEVENTMASK message to the control
	// with the ENM_UPDATE flag ORed into the lParam mask.
	
	// TODO: Add your control notification handler code here
	
}

void CRadio::OnUpdatePlayermessage6() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function to send the EM_SETEVENTMASK message to the control
	// with the ENM_UPDATE flag ORed into the lParam mask.
	
	// TODO: Add your control notification handler code here
	
}

void CRadio::OnUpdatePlayermessage7() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function to send the EM_SETEVENTMASK message to the control
	// with the ENM_UPDATE flag ORed into the lParam mask.
	
	// TODO: Add your control notification handler code here
	
}

void CRadio::OnUpdatePlayermessage8() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function to send the EM_SETEVENTMASK message to the control
	// with the ENM_UPDATE flag ORed into the lParam mask.
	
	// TODO: Add your control notification handler code here
	
}
