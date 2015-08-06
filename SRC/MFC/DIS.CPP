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

// DIS.cpp : implementation file
//

#include "stdafx.h"
#include "mig.h"
#include "DIS.h"
#include "rlistbox.h"
#include "dis_note.h"
#include "RRadio.h"
#include "mytime.h"
#include	"node.h"
#include "smkdlg.h"
#include "footage.h"
#include "migview.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#ifndef THIS_FILE_DEFINED
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif

/////////////////////////////////////////////////////////////////////////////
// CDIS dialog
char CDIS::intelltime = DAY;
SByte CDIS::currhilight = 0;

CDIS::CDIS(CWnd* pParent /*=NULL*/)
	: RowanDialog(CDIS::IDD, pParent)
{
	intelltime = DAY;
	intelltype = GENERAL;
	//{{AFX_DATA_INIT(CDIS)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDIS::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDIS)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	DDX_Control(pDX,IDC_RLISTBOXCTRL1,m_IDC_RLISTBOXCTRL1);
	DDX_Control(pDX,IDC_VIEWNOTES,m_IDC_VIEWNOTES);
	DDX_Control(pDX,IDC_VIEWFOOTAGE,m_IDC_VIEWFOOTAGE);
	DDX_Control(pDX,IDC_RRADIO_INTELLTYPE,m_IDC_RRADIO_INTELLTYPE);
	DDX_Control(pDX,IDC_RRADIO_INTELLTIME,m_IDC_RRADIO_INTELLTIME);
	DDX_Control(pDX,IDC_INTELLIGENCE,m_IDC_INTELLIGENCE);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDIS, CDialog)
	//{{AFX_MSG_MAP(CDIS)
	ON_WM_TIMER()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDIS message handlers

int	CDIS::FindText()
{
	Debrief::DisLog* dislog;
	int size;

	if (intelltime == ALL)
	{
		dislog = MMC.debrief.alldis;
		size = Debrief::DISISALLTOOMUCH;
	}
	else
	{
		dislog = MMC.debrief.disday;
		size = Debrief::DISISITFORTODAY;
	}
	return(dislog[currindex].msgtextid);


}
FileNum	CDIS::FindSmacker()
{
	Debrief::DisLog* dislog;

	if (intelltime == ALL)
		dislog = MMC.debrief.alldis;
	else
		dislog = MMC.debrief.disday;
//	dislog[currhilight].msgtextid;




	for (int i=0; i < SupplyTree::MAX_DISSMACKERS; i++)
	{
		if (dislog[currindex].msgtextid == SupplyTree::dissmackers[i].idtext)
			return (SupplyTree::dissmackers[i].file);
	}
	return (FIL_NULL);
}
void	CDIS::RedrawList(Debrief::DisLog* dislog, int size)
{
	CRListBox* rlistbox;
	rlistbox=GETDLGITEM(IDC_RLISTBOXCTRL1);

	int i = 0;
	int index = -1;
	currindex = -1;
	while	(		(i < Debrief::DISISITFORTODAY)
				&&	(dislog[i].msgtextid != 0)
			)
	{
		switch (dislog[i].typeflag)
		{
			case	Debrief::DISCARDTARGUID:
			case	Debrief::TARGUID:
			{
				if (intelltype != GENERAL)
				{
					rlistbox->AddString(GetTargName((UniqueID)dislog[i].msgowner),0);
					rlistbox->AddString(RESTABLE(2,DISTITLE_0,dislog[i].msgtextid),1);
					index++;
					if (index == currhilight)
						currindex = i;
				}
				break;
			};
			case	Debrief::DATE:
			{
				bool printdate = true;
				int nexti = i + 1;
				//don't want a table full of date with no entry for the date
				while (nexti != i)
				{
					if (		(intelltype == GENERAL)
							&&	(dislog[nexti].typeflag == Debrief::NAME)
						)
					{
						printdate  = true;
						break;
					}
					if (		(intelltype != GENERAL)
							&&	(		(dislog[nexti].typeflag == Debrief::DISCARDTARGUID)
									||	(dislog[nexti].typeflag == Debrief::TARGUID)
								)
						)
					{
						printdate  = true;
						break;
					}
					if (dislog[nexti].typeflag == Debrief::DATE)
					{
						printdate = false;
						break;
					}
					nexti++;
					if (nexti >= Debrief::DISISITFORTODAY)
						nexti = 0;

				}
				if (printdate)
				{
   					SLong date = MMC.startdate + (dislog[i].msgowner * SECSPERDAY);
					rlistbox->AddString(GetDateName(date, DATE_SHORT),0);
					rlistbox->AddString("",1);
						index++;
						if (index == currhilight)
								currindex = i;
				}
				break;
			};
			case	Debrief::NAME:
			{
				if (intelltype == GENERAL)
				{
//DEADCODE RDH 09/03/99 					if (dislog[i].msgowner != NULL)
//DEADCODE RDH 09/03/99 					{
//DEADCODE RDH 09/03/99 						CString st = LoadResString(dislog[i].msgowner);
//DEADCODE RDH 09/03/99 						rlistbox->AddString(LoadResString(dislog[i].msgowner),0);
//DEADCODE RDH 09/03/99 					}else
//DEADCODE RDH 09/03/99 					{
						rlistbox->AddString("",0);
//DEADCODE RDH 09/03/99 					}
					rlistbox->AddString(RESTABLE(2,DISTITLE_0,dislog[i].msgtextid),1);
					index++;
					if (index == currhilight)
						currindex = i;

				}
				break;
			};
		};
		i++;
	};



}
void	CDIS::Redraw()
{
	Debrief::DisLog* dislog;
	CRListBox* rlistbox;
	rlistbox=GETDLGITEM(IDC_RLISTBOXCTRL1);
	rlistbox->Clear();
	rlistbox->AddColumn(TARGETFIELDWIDTH);
	rlistbox->AddColumn(2);

	CRRadio* pradio;
	pradio=GETDLGITEM(IDC_RRADIO_INTELLTYPE);
	pradio->SetCurrentSelection(intelltype);

	if (intelltime == ALL)	
	{
		dislog = MMC.debrief.alldis;
		RedrawList(dislog, Debrief::DISISALLTOOMUCH);
	}else
	{
		dislog = MMC.debrief.disday;
		RedrawList(dislog, Debrief::DISISITFORTODAY);
	}

	CRButton*	but = GETDLGITEM(IDC_VIEWFOOTAGE);
	if (FindSmacker() != FIL_NULL)
	{
		but->SetForeColor(RGB(255,255,0));
		but->SetDisabled(false);
	}
	else
	{
		but->SetForeColor(RGB(80,80,80));
		but->SetDisabled(true);
	}
	
	but = GETDLGITEM(IDC_VIEWNOTES);
	if  (		(currindex >= 0)
			&&	(dislog[currindex].typeflag != Debrief::DATE)
		)
	{
		but->SetForeColor(RGB(255,255,0));
		but->SetDisabled(false);
	}else
	{
		but->SetForeColor(RGB(80,80,80));
		but->SetDisabled(true);
	}

	but = GETDLGITEM(IDC_INTELLIGENCE);
	if  (		(currindex >= 0)
			&&	(		(dislog[currindex].typeflag == Debrief::TARGUID)
					||	(dislog[currindex].typeflag == Debrief::DISCARDTARGUID)
				)
		)
	{
		but->SetForeColor(RGB(255,255,0));
		but->SetDisabled(false);
	}else
	{
		but->SetForeColor(RGB(80,80,80));
		but->SetDisabled(true);
	}

}


BOOL CDIS::OnInitDialog() 
{
	CDialog::OnInitDialog();
	

	CRButton*	but = GETDLGITEM(IDC_VIEWFOOTAGE);
	currindex = 0;

	ReCalcHiLight();
	Redraw();
	ResetHiLight();
	CRRadio* pradio;
	CString string;

	pradio=GETDLGITEM(IDC_RRADIO_INTELLTYPE);
	string.LoadString(IDS_TARGET);
	pradio->AddButton(string);
	string.LoadString(IDS_GENERAL);
	pradio->AddButton(string);

   	pradio=GETDLGITEM(IDC_RRADIO_INTELLTIME);
	string.LoadString(IDS_LATEST);
	pradio->AddButton(string);
	string.LoadString(IDS_PRIORITY2);
	pradio->AddButton(string);

	RDialog* parent=(RDialog*)GetParent();
	OnClickedViewnotes();
//	parent->SetMaxSize(CRect(0,0,550,400));
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BEGIN_EVENTSINK_MAP(CDIS, CDialog)
    //{{AFX_EVENTSINK_MAP(CDIS)
	ON_EVENT(CDIS, IDC_VIEWNOTES, 1 /* Clicked */, OnClickedViewnotes, VTS_NONE)
	ON_EVENT(CDIS, IDC_RRADIO_INTELLTIME, 1 /* Selected */, OnSelectedRradioIntelltime, VTS_I4)
	ON_EVENT(CDIS, IDC_RRADIO_INTELLTYPE, 1 /* Selected */, OnSelectedRradioIntelltype, VTS_I4)
	ON_EVENT(CDIS, IDC_VIEWFOOTAGE, 1 /* Clicked */, OnClickedViewfootage, VTS_NONE)
	ON_EVENT(CDIS, IDC_RLISTBOXCTRL1, 1 /* Select */, OnSelectRlistboxctrl1, VTS_I4 VTS_I4)
	ON_EVENT(CDIS, IDC_INTELLIGENCE, 1 /* Clicked */, OnClickedIntelligence, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CDIS::OnClickedViewnotes() 
{
	int text = FindText();

	if (LoggedChild(0))
		CloseLoggedChild(0);
	RDialog* d = MakeTopDialog(
		//CRect(100,500,0,0),
		Place(POSN_MIN,POSN_MAX,10,-10),
							DialBox(FIL_MAP_INTELLIGENCE,new CDis_Note(text))//Cdisnotes(text))//,Edges(EDGE::ALIGN_MIN + EDGE::ACTIONS_SPLITTER,EDGE::ALIGN_MIN,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE))
							);		

	LogChild(0,d);
}

void CDIS::OnSelectedRradioIntelltime(long ButtonNum) 
{
	if (ButtonNum == DAY)
		intelltime = DAY;	
	else
		intelltime = ALL;	
	ReCalcHiLight();
	Redraw();
	ResetHiLight();
	OnClickedViewnotes();

}
void CDIS::HiLightLast(Debrief::DisLog* dislog, int size)
{
	int i = 0;
	currhilight = -1;
	while	(		(i < Debrief::DISISITFORTODAY)
				&&	(dislog[i].msgtextid != 0)
			)
	{
		switch (dislog[i].typeflag)
		{
			case	Debrief::DISCARDTARGUID:
			case	Debrief::TARGUID:
			{
				if (intelltype != GENERAL)
					currhilight++;
				break;
			};
			case	Debrief::DATE:
			{
					currhilight++;
				break;
			};
			case	Debrief::NAME:
			{
				if (intelltype == GENERAL)
					 currhilight++;
				break;
			};
		};
		i++;
	};

}
void CDIS::ReCalcHiLight()
{
	Debrief::DisLog* dislog;

	if (intelltime == ALL)	
	{
		dislog = MMC.debrief.alldis;
		HiLightLast(dislog, Debrief::DISISALLTOOMUCH);
	}else
	{
		dislog = MMC.debrief.disday;
		HiLightLast(dislog, Debrief::DISISITFORTODAY);
	}
}

void CDIS::ResetHiLight()
{
	CRListBox* rlistbox;
	rlistbox=GETDLGITEM(IDC_RLISTBOXCTRL1);

	if (currhilight >= 0)
		rlistbox->SetHilightRow(currhilight);

}
void CDIS::OnSelectedRradioIntelltype(long ButtonNum) 
{
	if (ButtonNum == TARGET)
		intelltype = TARGET;	
	else
		intelltype = GENERAL;	
	ReCalcHiLight();
	Redraw();
	ResetHiLight();
	OnClickedViewnotes();
	
}

void CDIS::OnClickedViewfootage() 
{
//	OpenSmack(FindSmacker(),(int)m_hWnd,0,0);
//	m_timerID=SetTimer(1984,1000/12,NULL);
//	LaunchSmacker(1,file);
//	if (file != FIL_NULL)
//	{//play smacker, perphaps you should check that file is really a smacker
//		//Dave's stuff goes here
//	}

	FileNum file = FindSmacker();
	if (file != FIL_NULL)
	{
		if (LoggedChild(1))
			CloseLoggedChild(1);

		RDialog* d = MakeTopDialog(
			//CRect(600,100,0,0),
			Place(POSN_MAX,POSN_MIN,-10,10),
			DialList(DialBox(FIL_MAP_SUPPLY,new CFootage,Edges(EDGE::ALIGN_MIN,EDGE::ALIGN_MIN,EDGE::ALIGN_MAX+EDGE::OCCLUDE_INSIDE,EDGE::ALIGN_MAX+EDGE::OCCLUDE_INSIDE)),
				 DialBox(FIL_NULL,new CSmackerDialog(file),Edges(EDGE::ALIGN_MIN,EDGE::ALIGN_MIN,EDGE::ALIGN_MAX+EDGE::OCCLUDE_INSIDE,EDGE::ALIGN_MAX+EDGE::OCCLUDE_INSIDE))));
		LogChild(1,d);
	}

	
}


void CDIS::OnSelectRlistboxctrl1(long row, long column) 
{
	currhilight = row;
	Redraw();
	ResetHiLight();
	CloseLoggedChildren();
	OnClickedViewnotes();

}

void CDIS::OnTimer(UINT nIDEvent) 
{
	CDialog::OnTimer(nIDEvent);
}

void CDIS::OnDestroy() 
{
	CDialog::OnDestroy();
}

void CDIS::OnClickedIntelligence() 
{

	Debrief::DisLog* dislog;

	if (intelltime == ALL)
		dislog = MMC.debrief.alldis;
	else
		dislog = MMC.debrief.disday;

	UniqueID uid;
	uid = (UniqueID)dislog[currindex].msgowner;
  
	RDialog::m_pView->ZoomToUID(uid,RDialog::m_pView->m_zoom);
	RDialog::m_pView->m_mapdlg.ResetIcon(uid);

	MainToolBar().OpenDossier(uid);
//  		CTargetDossier::MakeSheet(
//		//CRect(180,180,0,0),
//		Place(POSN_MAX,POSN_MIN,-10,10),
//				uid);

	OnOK();
}
