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

// JoyConfg.cpp : implementation file
//

#include "stdafx.h"
#include "mig.h"
#include "JoyConfg.h"
#include "Analogue.h"
#include "RJoyCfg.h"
#include "JoyError.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#ifndef THIS_FILE_DEFINED
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif

extern Analogue _Analogue;

/////////////////////////////////////////////////////////////////////////////
// CJoyConfg dialog


CJoyConfg::CJoyConfg(CWnd* pParent /*=NULL*/)
	: RowanDialog(CJoyConfg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CJoyConfg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
 	AxisUsesField	axes;
 		axes|=AU_AILERON;
 		axes|=AU_ELEVATOR;
// 		axes|=AU_THROTTLE;
 //		axes|=AU_RUDDER;
 	_Analogue.SetAxes(0,axes);

  	pages=_Analogue.PreCalib(0);
	joystickcalibstage=CENTREPRESS;
	m_timerID=0;
}


void CJoyConfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CJoyConfg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CJoyConfg, CDialog)
	//{{AFX_MSG_MAP(CJoyConfg)
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_FIRE, OnFire)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CJoyConfg message handlers

void CJoyConfg::OnPaint() 
{
	CDialog::OnPaint();
	if (m_timerID==0) m_timerID=SetTimer(2398,0,NULL);
	m_bFirePressed=FALSE;
}

BOOL CJoyConfg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_instructions.SubclassDlgItem(IDC_INSTRUCTIONS,this);
	m_instructions2.SubclassDlgItem(IDC_INSTRUCTIONS2,this);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CJoyConfg::OnTimer(UINT nIDEvent) 
{
	// Nick the Enum loop thing
if (nIDEvent=m_timerID)
{
  	int	axis;
  	int		numerrs,numwarns;
  	AxisErrors	e1;
	CString instructions;
	int page=0;
	  switch (joystickcalibstage)
	  {
		case CENTREMESSAGE:
		{
	//		for (axis=0;axis<4;axis++)
  	//		_Analogue.GetAxisRequests(page,axis,title,messages[axis],errormsg);
	//	 	SetRedraw(REDRAW_DRAW,instructions);
			m_bFirePressed=FALSE;
			instructions.LoadString(IDS_JOYSTICK1);
			m_instructions.SetText(instructions);
			m_instructions2.SetText("");
			joystickcalibstage = CENTREPRESS;
		}
		case CENTREPRESS:
		{
	  		if(_Analogue.CalibCenter(page,x1,y1,x2,y2) || m_bFirePressed)
			{
				m_bFirePressed=FALSE;
				joystickcalibstage = CENTRERELEASE;
			}
			break;
		}

		case CENTRERELEASE:
		{
	  		numerrs=0;numwarns=0;
	  		for (axis=0;axis<4;axis++)
	  		{
	  			e1=_Analogue.GetAxisStatus(page,axis);
	  			if (e1!=AE_CORRECT && e1!=AE_AUTO)
	  				if (e1&AE_WARNING)
	  					numwarns++;
	  				else
	  					numerrs++;
	  		}
	  		if (numerrs || numwarns)
	  			;;	//dialogue box to restart, or abort/continue
	  
	  		if (!_Analogue.CalibExtreme(page,x1,y1,x2,y2))
	  		{
				joystickcalibstage = EXTREMEMESSAGE;
			}else
			{
//	  			//say "Please release fire..."
//				messages[0] = JOYSTIC_RELEASE;
//			 	SetRedraw(REDRAW_DRAW,instructions);
			instructions.LoadString(IDS_JOYSTICK4);
			m_instructions.SetText(instructions);
			m_instructions2.SetText("");

	  		}
			break;
		}

		case EXTREMEMESSAGE:
		{
//	  		for (axis=0;axis<4;axis++)
//	  			_Analogue.GetAxisRequests(page,axis,title,errormsg,messages[axis]);
//		 	SetRedraw(REDRAW_DRAW,instructions);
			instructions.LoadString(IDS_JOYSTICK2);
			m_instructions.SetText(instructions);
			instructions.LoadString(IDS_JOYSTICK5);
			m_instructions2.SetText(instructions);
			joystickcalibstage = EXTREMEPRESS;

		}
		case EXTREMEPRESS:
		{
	  		//say: "please extremes: messages, then press any button or select Cont"

	  		e1=_Analogue.GetAxisStatus(page,3);		//throttle axis
			if (e1==AE_AUTO)// && messages[3]!=TEXT_NULL)
			{
				joystickcalibstage = EXTREMEPRESSAUTO;
//				messages[3]=TEXT_COOLIEHATENABLED;
//			 	SetRedraw(REDRAW_DRAW,instructions);
			}

	  		if (_Analogue.CalibExtreme(page,x1,y1,x2,y2) || m_bFirePressed)
			{
				m_bFirePressed=FALSE;
				joystickcalibstage = EXTREMERELEASE;
			}
			break;
  		}
		case EXTREMEPRESSAUTO:
		{
	  		if (_Analogue.CalibExtreme(page,x1,y1,x2,y2) || m_bFirePressed)
			{
				m_bFirePressed=FALSE;
				joystickcalibstage = EXTREMERELEASE;
			}
			break;
		}
		case EXTREMERELEASE:
		{
	  		numerrs=0;numwarns=0;
	  		for (axis=0;axis<4;axis++)
	  		{
	  			e1=_Analogue.GetAxisStatus(page,axis);
	  			if (e1!=AE_CORRECT && e1!=AE_AUTO)
	  		  		if (e1&AE_WARNING)
	  					numwarns++;
	  				else
	  					numerrs++;
	  		}
			if (_Analogue.CalibRead(page,x1,y1,x2,y2))
			{
	  			//say "Please release fire..."
//				messages[0] = JOYSTIC_RELEASE;
//			 	SetRedraw(REDRAW_DRAW,instructions);
				instructions.LoadString(IDS_JOYSTICK4);
				m_instructions.SetText(instructions);
				m_instructions2.SetText("");
			}elseif (numerrs != 0)
			{
//				childclosed = (InterSheetProc) IsErrorRestart;		
//				SetRedraw(REDRAW_SHEET);							//RDH 01Jul96
//				ChildSheet(MakeJoyErrorSheet(ScreenXY(ERRORX,ERRORY),*window,is_error,+JOYSTIC_ERROR,FILJOYERRORART,page));
//				KeyboardLastKey=TRUE;
				joystickcalibstage = CALIBERROR;
			}elseif (numwarns != 0)
			{
//				childclosed = (InterSheetProc) IsErrorRestart;		
//				SetRedraw(REDRAW_SHEET);							//RDH 01Jul96
//				ChildSheet(MakeJoyErrorSheet(ScreenXY(ERRORX,ERRORY),*window,is_error,+JOYSTIC_WARNING,FILJOYERRORART,page));
//				KeyboardLastKey=TRUE;
				joystickcalibstage = CALIBWARNING;
			}else
	  		{
				joystickcalibstage = TESTSTICKMESS;
			}

			break;
  		}
 		case CALIBERROR:
 		{
// 			break;
   		}
 		case CALIBWARNING:
 		{
		 	AxisUsesField	axes;
		 	_Analogue.SetAxes(0,axes);
			KillTimer(m_timerID);
			this->EndDialog(0);
			RDialog::MakeTopDialog(CRect(200,200,0,0),
								DialBox(FIL_NULL/*IDB_INTEL*/,new CJoyError)//,Edges(EDGE::ALIGN_MIN + EDGE::ACTIONS_SPLITTER,EDGE::ALIGN_MIN,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE))
							);
			return;
   		}
		case TESTSTICKMESS:
		{
  
//			messages[0] = JOYSTIC_TEST;
//			messages[1] = TEXT_NULL;
//			messages[2] = TEXT_NULL;
//			messages[3] = TEXT_NULL;
//		 	SetRedraw(REDRAW_DRAW,instructions);
	  		//Say: hey, play about a bit, how does it feel?
			instructions.LoadString(IDS_JOYSTICK3);
			m_instructions.SetText(instructions);
			instructions.LoadString(IDS_JOYSTICK5);
			m_instructions2.SetText(instructions);
			joystickcalibstage = TESTSTICK;
			break;
		}
		case TESTSTICK:
		{
	  		if (_Analogue.CalibRead(page,x1,y1,x2,y2) || m_bFirePressed)
	  		{
				m_bFirePressed=FALSE;
				joystickcalibstage = TESTSTICKRELEASE;	//CALIBDONE;
//				messages[0] = JOYSTIC_RELEASE;					//JIM 23Jul96
//				SetRedraw(REDRAW_DRAW,instructions);			//JIM 23Jul96
				instructions.LoadString(IDS_JOYSTICK4);
				m_instructions.SetText(instructions);
				m_instructions2.SetText("");	  
	  		}
			break;
		}
		case TESTSTICKRELEASE:
	  		if (_Analogue.CalibRead(page,x1,y1,x2,y2)) break;

		case CALIBDONE:
		{

		  	page++;
			if (page >= pages)
			{
//				KeyboardLastKey=TRUE;
//				Save_Data =  Temp_Data;
//				PopThisSheet();									//RDH 10Jun96
//				this->PostMessage(IDOK,NULL,NULL);
				KillTimer(m_timerID);
				this->EndDialog(0);
				return;
//DeadCode RDH 10Jun96 				ReturnToJunction ();
			}else
			{
				joystickcalibstage = CENTREMESSAGE;
			}
			break;
		}
		case CALIBFAIL:
		{
	  		if (!_Analogue.CalibRead(page,x1,y1,x2,y2))
	  		{
				joystickcalibstage = CALIBFAIL2;
	  		}
			break;
		}
		case CALIBFAIL2:
		{
//			KeyboardLastKey=TRUE;
			joystickcalibstage = CENTREMESSAGE;
			break;
		}

	}
	CRect rect;
	CRJoyCfg* joystick;
	joystick=GETDLGITEM(IDC_JOYSTICK);
	joystick->GetClientRect(rect);
	rect.right-=32;
	rect.bottom-=32;
//	TRACE3("%d x1: %d y1: %d\n",pages,x1,y1);
//	TRACE2("x2: %d y2: %d\n",x2,y2);
	joystick->SetX(((x1+0x8000)*rect.right)/0x10000);
	joystick->SetY(((y1+0x8000)*rect.bottom)/0x10000);
	joystick=GETDLGITEM(IDC_RUDDER);
	if (x2!=-0x8000) joystick->SetX(((x2+0x8000)*rect.right)/0x10000);
	else 
		joystick->SetY(1000);
	joystick=GETDLGITEM(IDC_THROTTLE);
	if (y2!=-0x8000) joystick->SetY(((y2+0x8000)*rect.bottom)/0x10000);
	else 
		joystick->SetX(1000);

}
CDialog::OnTimer(nIDEvent);
}

void CJoyConfg::OnFire() 
{
	m_bFirePressed=TRUE;
}
