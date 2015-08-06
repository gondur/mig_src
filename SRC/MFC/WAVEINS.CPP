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

// WaveIns.cpp : implementation file
//

#include "stdafx.h"
#include "mig.h"
#include "WaveIns.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#ifndef THIS_FILE_DEFINED
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif
/////////////////////////////////////////////////////////////////////////////
// CWaveInsert dialog


CWaveInsert::CWaveInsert(int pack,int wave,int d,int t, CWnd* pParent /*=NULL*/)
	: RowanDialog(CWaveInsert::IDD, pParent)
{
		SetProjSpecific(pack,wave);
		time = t;
		duty = d;
		if (		(duty == DUTYBARCAP)
				||	(duty == DUTYMIGCAP)
				||	(duty == DUTYESCORT)
			)
			duty = 2;
		if (duty == DC_WW)
			duty = 1;
		else
			duty = 0;
	//{{AFX_DATA_INIT(CWaveInsert)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CWaveInsert::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWaveInsert)
	DDX_Control(pDX, IDCX_TIME, m_IDCX_TIME);
	DDX_Control(pDX,IDC_MAINDUTY,m_IDC_MAINDUTY);
	DDX_Control(pDX,IDC_TIME,m_IDC_TIME);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CWaveInsert, CDialog)
	//{{AFX_MSG_MAP(CWaveInsert)
	ON_EN_UPDATE(IDCX_TIME, OnUpdateTime)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWaveInsert message handlers

BEGIN_EVENTSINK_MAP(CWaveInsert, CDialog)
    //{{AFX_EVENTSINK_MAP(CWaveInsert)
	ON_EVENT(CWaveInsert, IDJ_TITLE, 3 /* OK */, OnOKTitle, VTS_NONE)
	ON_EVENT(CWaveInsert, IDC_MAINDUTY, 1 /* Selected */, OnSelectedMainduty, VTS_I4)
	ON_EVENT(CWaveInsert, IDC_TIME, 2 /* TextChanged */, OnTextChangedTime, VTS_I4)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CWaveInsert::OnOKTitle() 
{
//	maxrows++;
	if (duty == 2)
		duty = DUTYMIGCAP;
	if (duty == 1)
		duty = DC_WW;

	if (Todays_Packages[packnum].MakeWave(wavenum,duty))
	{
		CREdit* edit;
		CString	buffer;
		if (m_IDCX_TIME.m_hWnd)
		{
			m_IDCX_TIME.GetWindowText(buffer);
		}
		else
		{

			edit=GETDLGITEM(IDC_TIME);
			buffer = edit->GetCaption();
		}
		int time = Profile::ValidateTime(&buffer, packnum, wavenum);


		Todays_Packages[packnum][wavenum].targettime = time * 60;
		Todays_Packages[packnum].CalcWPTimes(wavenum);
	}


	RefreshParent();
//	FillWaveRow(wav);
//	SetWaveTabs(wav,-1);
	OnOK();
	
}

void CWaveInsert::OnSelectedMainduty(long ButtonNum) 
{
	duty = ButtonNum;	
}

void CWaveInsert::OnTextChangedTime(LPTSTR text) 
{
//DeadCode RDH 24Jun99 		CREdit* edit;
//DeadCode RDH 24Jun99 		CString	buffer;
//DeadCode RDH 24Jun99 		edit=GETDLGITEM(IDC_TIME);
//DeadCode RDH 24Jun99 		buffer = edit->GetCaption();
//DeadCode RDH 24Jun99 		trunc(text,5);
//DeadCode RDH 24Jun99 		Profile::ValidateTime(&buffer, packnum, wavenum);
	
}

BOOL CWaveInsert::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CRRadio* pradio;

	pradio=GETDLGITEM(IDC_MAINDUTY);
	pradio->AddButton(RESSTRING(L_DUTY_BOMB));
	pradio->AddButton(RESSTRING(DUTY_AAA));
	pradio->AddButton(RESSTRING(DUTY_BARCAP));
	pradio->SetCurrentSelection(duty);

	time = time/60;

	if (m_IDCX_TIME.m_hWnd)
	{
		m_IDCX_TIME.SetWindowText(CSprintf("%02i:%02i",time/60,time%60));
	}
	else
	{
		CREdit* edit=GETDLGITEM(IDC_TIME);
		edit->SetWindowText(CSprintf("%02i:%02i",time/60,time%60));
	}

	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CWaveInsert::OnUpdateTime() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function to send the EM_SETEVENTMASK message to the control
	// with the ENM_UPDATE flag ORed into the lParam mask.
	
	// TODO: Add your control notification handler code here
	
}
