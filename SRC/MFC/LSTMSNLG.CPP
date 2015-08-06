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

// LstMsnLg.cpp : implementation file
//

#include "stdafx.h"
#include "mig.h"
#include "LstMsnLg.h"
#include "messengn.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#ifndef THIS_FILE_DEFINED
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif


void	Persons3::ProcessLogList()
{	//sort the eventlog by time and discard any uninteresting entries
	Debrief& debrief=MMC.debrief;
	int	maxevententry=0;
	while (eventloglist)
	{
		if (eventloglist->stage)
		if (eventloglist->stage!=EventEntry::UNSEEN)// || eventloglist->nat!=NAT_BLUE)
		{
			int currentry=maxevententry;
			int testtime=eventloglist->launchtime-eventloglist->stage;
			while (currentry>0 && debrief.sortedevents[currentry-1].launchtime-debrief.sortedevents[currentry-1].stage>testtime)
			{
				debrief.sortedevents[currentry]=debrief.sortedevents[currentry-1];
				currentry--;
			}
			debrief.sortedevents[currentry]=*eventloglist;
			maxevententry++;
		}

		EventLogPtr	tmp=eventloglist;
		eventloglist=tmp->next;
		delete tmp;
	}
	while (maxevententry!=debrief.MAXSORTEDEVENTS)
		debrief.sortedevents[maxevententry++].stage=eventloglist->EMPTY;
}
/////////////////////////////////////////////////////////////////////////////
// CLastMissionLog dialog


CLastMissionLog::CLastMissionLog(CWnd* pParent /*=NULL*/)
	: RowanDialog(CLastMissionLog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLastMissionLog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CLastMissionLog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLastMissionLog)
	DDX_Control(pDX,IDC_RLISTBOXCTRL1,m_IDC_RLISTBOXCTRL1);
	DDX_Control(pDX,IDC_DETAILS,m_IDC_DETAILS);

	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLastMissionLog, CDialog)
	//{{AFX_MSG_MAP(CLastMissionLog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLastMissionLog message handlers

static	CString GetTypeString(int actype)
{
	CString	type;
	if (actype<PT_T6)
		type=RESLIST(F86A,actype);
	else
	if (actype<PT_VEHICLES)
		type=RESLIST(SQ_BS_T6,actype-PT_T6);
	else
		type=RESSTRING(TRUCK);
	return	type;
}

BOOL CLastMissionLog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	CRListBox* rlistbox;
	rlistbox=GETDLGITEM(IDC_RLISTBOXCTRL1);
	rlistbox->Clear();
	rlistbox->AddColumn(40);
	rlistbox->AddColumn(50);
	Debrief& debrief=MMC.debrief;
	int line=0;
	for (int row=0;debrief.sortedevents[row].stage;row++)
	{
		CString	type=GetTypeString(debrief.sortedevents[row].encounteredtype);
		if (debrief.sortedevents[row].escorttype!=PT_BADMAX && debrief.sortedevents[row].escorttype!=debrief.sortedevents[row].encounteredtype)
		{
			type+=" + ";
			type+=GetTypeString(debrief.sortedevents[row].escorttype);
		}
		CString home="";
		if (debrief.sortedevents[row].homebase)
			if (debrief.sortedevents[row].homebase==UID_Japan)
				home=RESSTRING(JAPAN);
			else
				home=LoadResString(IDS_PLACENAMES_START+debrief.sortedevents[row].homebase);
		CString over="";
		if (debrief.sortedevents[row].place)
			over=_MsgBuffer.GetPlaceName(debrief.sortedevents[row].place);

	 	rlistbox->AddString(CSprintf("%02i:%02i",debrief.sortedevents[row].launchtime/360000,(debrief.sortedevents[row].launchtime/6000)%60),0);
		int encsize=debrief.sortedevents[row].encsize;
		if (!encsize)	encsize=1;
		if (debrief.sortedevents[row].homebase)
			rlistbox->AddString(CSprintf(RESSTRING(QUICKFORCE),encsize,type,home),1);
		else
			rlistbox->AddString(CSprintf(RESSTRING(QUICKFORCENOBASE),encsize,type),1);
		rownum[line++]=row;

		if (debrief.sortedevents[row].hits || debrief.sortedevents[row].losses)
		{
			rownum[line++]=row;
			switch (debrief.sortedevents[row].stage)
			{
			case EventEntry::DAMAGEDSTATIC:	
				type=RESSTRING(HITS);
			break;		
			case EventEntry::DAMAGED:
			case EventEntry::DAMAGEDTRUCK:
				type=RESSTRING(HITS);								  //RDH 15/06/99
			break;
			case EventEntry::KILLED:
			case EventEntry::ATTACKEDBYOTHERS:
			case EventEntry::KILLEDTRUCK:
				type=RESSTRING(KILLS);								  //RDH 15/06/99
			break;
			default:
				assert(!"Should not be counting hits on this target type");
			}
			rlistbox->AddString(type,0);
			int unkills,redkills;
			unkills=debrief.sortedevents[row].hits;
			redkills=debrief.sortedevents[row].losses;
			if (debrief.sortedevents[row].encounteredtype<PT_MIG15)
			{
				int un2=redkills;
				redkills=unkills;
				unkills=un2;
			}
			if (unkills)
				if (redkills)
					rlistbox->AddString(CSprintf(RESSTRING(HITSFORAGAINST),redkills,unkills),1);
				else
					rlistbox->AddString(CSprintf("%s: %i",RESSTRING(UNFORCES),unkills),1);
			else
				if (redkills)
					rlistbox->AddString(CSprintf("%s: %i",RESSTRING(REDFORCES),redkills),1);
				else
					rlistbox->AddString(RESSTRING(NONE_SPECIALS),1);
		}
		if (row)
			OnSelectRlistboxctrl1(0,0);

	}
	rownum[line++]=-1;
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BEGIN_EVENTSINK_MAP(CLastMissionLog, CDialog)
    //{{AFX_EVENTSINK_MAP(CLastMissionLog)
	ON_EVENT(CLastMissionLog, IDC_RLISTBOXCTRL1, 1 /* Select */, OnSelectRlistboxctrl1, VTS_I4 VTS_I4)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CLastMissionLog::OnSelectRlistboxctrl1(long row, long column) 
{
	// TODO: Add your control notification handler code here 
	Debrief& debrief=MMC.debrief;
	if (!debrief.sortedevents[row].stage)
		return;														  //JIM 08/06/99
	row=rownum[row];
	CString	type=GetTypeString(debrief.sortedevents[row].encounteredtype);
	if (debrief.sortedevents[row].escorttype!=PT_BADMAX)
	{
		type+=" + ";
		type+=GetTypeString(debrief.sortedevents[row].escorttype);
	}

	CString home="";
	if (debrief.sortedevents[row].homebase)
		if (debrief.sortedevents[row].homebase==UID_Japan)
			home=RESSTRING(JAPAN);
		else
			home=LoadResString(IDS_PLACENAMES_START+debrief.sortedevents[row].homebase);
	CString over="";
	if (debrief.sortedevents[row].place)
		over=_MsgBuffer.GetPlaceName(debrief.sortedevents[row].place);
	if (debrief.sortedevents[row].encsize)
		GETDLGITEM(IDC_DETAILS)->SetString(CSprintf(RESLIST(LOG_EMPTY,debrief.sortedevents[row].stage),
									debrief.sortedevents[row].encsize,type,home,over	));
	else
		GETDLGITEM(IDC_DETAILS)->SetString(CSprintf(RESLIST(LOG_EMPTY,debrief.sortedevents[row].stage),
									type,home,over	));
	
	
}
