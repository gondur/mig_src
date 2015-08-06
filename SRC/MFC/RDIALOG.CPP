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

// RDialog.cpp : implementation file
//

#include "stdafx.h"
#include "MIG.h"
//#include "RDEmpty.h"
//#include "font.h"
//#include "rbutton.h"
//#include "rtabs.h"
//#include "rspltbar.h"
//#include "rdialog.h"
#include "messages.h"
#include "fileman.h"
#include "MIGView.h"
#include "hintbox.h"
#include "miles.h"
#include "3dcode.h"
#include "listbx.h"
#include "rscrlbar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#ifndef	THIS_FILE_DEFINED
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif
/////////////////////////////////////////////////////////////////////////////
int		RDialog::actscrw=0,
		RDialog::actscrh=0,
		RDialog::borderwidth=0,
		RDialog::fontdpi=0;
RMdlDlg* RDialog::m_pMessageBox=NULL;
CHintBox* RDialog::m_pHintBox=NULL;
bool	RDialog::m_moving=FALSE;
CMIGView* RDialog::m_pView=NULL;
CListBx* RDialog::m_pListBox=NULL;

RDialog* RDialog::skip = NULL;
extern CDC g_OffScreenDC;
//extern CFont* (g_AllFonts[][4]);
//IMPLEMENT_DYNAMIC (RDialog,CDialog)

/////////////////////////////////////////////////////////////////////////////
// RDialog dialog
// Construction:
RDialog::RDialog(int IID,CWnd* pParent /*=NULL*/)
	: CDialog(IID, pParent),
	MY_IID(IID)
{
	m_pfileblock=NULL;
	//{{AFX_DATA_INIT(RDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	 
	artnum=FIL_NULL;
	dragstate=DRAG_INIT;
	currscrw=currscrh=0;
	cursor=IDC_ARROW;
	minsize=RECT_MIN;
	maxsize=RECT_MAX;
	viewsize=CRect(0,0,0,0);
	homesize=CRect(0,0,0,0);
	m_pHorzScrollBar=NULL;
	m_pVertScrollBar=NULL;
	m_ReallyDestroyed=TRUE;
	m_bDrawBackground=FALSE;
}


void RDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(RDialog)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
//	GetClientRect(&viewsize);
//	ClientToScreen(&viewsize);
//	homesize=CRect(0,0,viewsize.Width(),viewsize.Height());
}

void	RDialog::DDX_Control(CDataExchange* pDX,int	dialid,CWnd&	m_dial)
{
	HWND tmp;
	GetDlgItem(dialid,&tmp);
	if (tmp)
		::DDX_Control(pDX,dialid,m_dial);
}

int RDialog::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
//	artnum=OnGetArt();
	GetClientRect(homesize);
	// scale the dialog if necessary due to font size change
//	m_scalingfactor=(float)fontdpi/96;
//	ScaleDialog(1);

//	m_rVertScrollBar.Create(NULL, WS_VISIBLE, CRect(-1,-1,-1,-1), this, 1000);
//	m_rHorzScrollBar.Create(NULL, WS_VISIBLE, CRect(-1,-1,-1,-1), this, 1001);	
//	ShowScrollBar(SB_HORZ,TRUE);
//	ShowScrollBar(SB_VERT,TRUE);
//	CScrollBar* horz=GetScrollBarCtrl(SB_HORZ);
//	CScrollBar* vert=GetScrollBarCtrl(SB_VERT);
//	m_rHorzScrollBar.SubclassWindow(horz->m_hWnd);
//	m_rVertScrollBar.SubclassWindow(vert->m_hWnd);
	return 0;
}

BOOL RDialog::PreCreateWindow(CREATESTRUCT& cs) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CDialog::PreCreateWindow(cs);
}

int RDialog::DoModal() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CDialog::DoModal();
}

///////////////////////////////////////////////////////////////////////
//Initialisation
RDialog*	RDialog::MakeParentDialog(CRect& dialsize,RDialog* parent,DialBox* tree)
{//STATIC
	int	dialxposflag=0,dialyposflag=0;
	if (dialsize.right<0)
	{
		dialxposflag=-dialsize.right;
		if (dialsize.left <= 0) 
			dialsize.right=dialsize.left-1;
		else
			dialsize.right=0;

	}
	if (dialsize.bottom<0)
	{
		dialyposflag=-dialsize.bottom;
		if (dialsize.top <= 0) 
			dialsize.bottom=dialsize.top-1;
		else
			dialsize.bottom=0;
	}
	RDialog* main=new RDEmptyD(parent);
	main->parent=parent;
	main->fchild=main->dchild=main->sibling=NULL;
	main->RECT_NORMAL=dialsize;
	if (parent!=NULL)
	{
		if ((tree->edges->l&EDGE::ACTIONS_MASK)==EDGE::ACTIONS_ARTCHILD)
			main->Create(IDD_EMPTYCHILD,parent);
		else 
			main->Create(main->MY_IID,parent);
	}
	else
	{
//		CFrameWnd* frame=(CFrameWnd*)AfxGetMainWnd();
//		CView* view=frame->GetActiveView();
		if (tree->edges && (tree->edges->l&EDGE::ACTIONS_MASK)==EDGE::ACTIONS_ARTCHILD)
			main->Create(IDD_EMPTYCHILD,m_pView);
		else 
		if (tree->edges && (tree->edges->l&EDGE::OCCLUDE_MASK)==EDGE::OCCLUDE_EXACT)
			main->Create(IDD_EMPTYNOBORDER,m_pView);
		else
			main->Create(main->MY_IID,m_pView);
	}
	// scale the dialog if necessary due to font size change
	if (dialsize.Width()>=640 && dialsize.Height()>=480)		//RJS 08Sep98
		main->m_scalingfactor=1;								//RJS 08Sep98
	else														//RJS 08Sep98
		main->m_scalingfactor=(float)fontdpi/96;				//RJS 08Sep98
	main->ScaleDialog(1);
	if (parent)
	{
		main->sibling=parent->dchild;
		parent->dchild=main;
	}
	main->viewsize=main->viewsize2=main->homesize=main->RECT_NORMAL;

	RDialog* dial=tree->dial;
//	dial->InitArtwork(tree->art);
	dial->parent=main;
	main->fchild=dial;
	dial->fchild=dial->dchild=dial->sibling=NULL;
	dial->RECT_NORMAL=CRect(0,0,dialsize.Width(),dialsize.Height());
	dial->m_ReallyDestroyed=FALSE;
	if (dial->Create(dial->MY_IID,main)!=1)
	{
		main->DestroyWindow();
		return NULL;
	}
	// scale the dialog if necessary due to font size change
	if (dialsize.Width()>=640 && dialsize.Height()>=480)	
		dial->m_scalingfactor=1;							
	else													
		dial->m_scalingfactor=(float)fontdpi/96;
	dial->ScaleDialog(1);
	dial->m_ReallyDestroyed=TRUE;
	CRect rect;
	dial->GetClientRect(rect);
	// if dialsize is meaningless use left and top as coordinates
	if (dialsize.left>=dialsize.right || dialsize.top>=dialsize.bottom)
	{
//		TRACE1("BorderWidth: %d\n",borderwidth);
		dial->RECT_NORMAL=rect;
		if (tree->edges && (tree->edges->l&EDGE::OCCLUDE_MASK)==EDGE::OCCLUDE_EXACT)
			dialsize=CRect(dialsize.left,dialsize.top,dialsize.left+rect.right-1,dialsize.top+rect.bottom-1);
		else
			dialsize=CRect(dialsize.left,dialsize.top,dialsize.left+rect.right-1+borderwidth*2,dialsize.top+rect.bottom+borderwidth*2);
		if (dialxposflag || dialyposflag)
		{
			CRect apppos;
			int delta;
			m_pView->GetWindowRect(apppos);
			if (apppos.Width()<m_pView->m_size.cx) 
				apppos.bottom-=15;
			if (apppos.Height()<m_pView->m_size.cy) 
				apppos.right-=15;
			switch (dialxposflag)
			{
 			case POSN_MIN:
				delta=apppos.left;
				break;
			case POSN_CENTRE:
				delta=apppos.left+(apppos.Width()-dialsize.Width())/2;
				break;
			case POSN_MAX:
				delta=apppos.right-dialsize.Width();
				break;

			}
			dialsize.left+=delta;
			dialsize.right+=delta;
			switch (dialyposflag)
			{
 			case POSN_MIN:
				delta=apppos.top;
				break;
			case POSN_CENTRE:
				delta=apppos.top+(apppos.Height()-dialsize.Height())/2;
				break;
			case POSN_MAX:
				delta=apppos.bottom-dialsize.Height();
				break;
			}
			dialsize.top+=delta;
			dialsize.bottom+=delta;
		}
		main->viewsize=main->viewsize2=main->homesize=main->RECT_NORMAL=dialsize;
	}
	dial->viewsize=dial->viewsize2=dial->RECT_NORMAL;

	if (tree->edges)
		dial->edges=*tree->edges;
	else
		dial->edges.r=dial->edges.b=EDGE::ALIGN_MAX;
	dial->artnum=tree->art;
	main->dragstate=DRAG_DIALOG;
	dial->dragstate=DRAG_NO;
	dial->AddChildren(tree->diallist);
	dial->MoveWindow(&dial->viewsize);		//IDC_BUTTON1
	m_pView->GetWindowRect(rect);
	if (main->viewsize.right>rect.right || main->viewsize.bottom>rect.bottom)
	{					   
		main->viewsize.left=rect.right-main->viewsize.Width();
		main->viewsize.top=rect.bottom-main->viewsize.Height();
		main->viewsize.right=rect.right;
		main->viewsize.bottom=rect.bottom;
	}
	main->SetMinSize(CRect(0,0,main->viewsize.Width(),main->viewsize.Height()));
	main->SetMaxSize(CRect(0,0,main->viewsize.Width(),main->viewsize.Height()));
//	dial->SetMinSize(CRect(0,0,main->viewsize.Width(),main->viewsize.Height()));
//	dial->SetMaxSize(CRect(0,0,main->viewsize.Width(),main->viewsize.Height()));
	main->MoveWindow(&main->viewsize);
	// check if its the top sheet.
/*	dial->m_systemopen.Create(">",BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE | BS_BITMAP,
		CRect(0,0,20,20),dial,2000);
	dial->m_close.Create("X",BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE | BS_BITMAP,
		CRect(rect.right-20,0,rect.right,20),dial,IDCANCEL);
//	if (m_showTick==TRUE) // assumed true for now... do something with rtitle?
//	{
		dial->m_tick.Create("/",BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE | BS_BITMAP,
		CRect(rect.right-40,0,rect.right-20,20),dial,IDOK);
		dial->m_bmpTick.LoadBitmap(IDB_TICK);
		dial->m_tick.SetBitmap(dial->m_bmpTick);
//	}
	dial->m_systemclose.Create(">",BS_PUSHBUTTON | WS_CHILD | BS_BITMAP,
		CRect(0,0,20,20),dial,2003);
	dial->m_maximize.Create(">",BS_PUSHBUTTON | WS_CHILD | BS_BITMAP,
		CRect(20,0,40,20),dial,2004);
	dial->m_minimize.Create(">",BS_PUSHBUTTON | WS_CHILD | BS_BITMAP,
		CRect(40,0,60,20),dial,2005);
	dial->m_help.Create(">",BS_PUSHBUTTON | WS_CHILD | BS_BITMAP,
		CRect(60,0,80,20),dial,2006);
	dial->m_bmpSystemOpen.LoadBitmap(IDB_SYSTEM_OPEN);
	dial->m_bmpClose.LoadBitmap(IDB_CLOSE);
	dial->m_bmpSystemClose.LoadBitmap(IDB_SYSTEM_CLOSE);
	dial->m_bmpMinimize.LoadBitmap(IDB_MINIMISE);
	dial->m_bmpMaximize.LoadBitmap(IDB_MAXIMISE);
	dial->m_bmpHelp.LoadBitmap(IDB_HELP);
	dial->m_systemopen.SetBitmap(dial->m_bmpSystemOpen);
	dial->m_close.SetBitmap(dial->m_bmpClose);
	dial->m_systemclose.SetBitmap(dial->m_bmpSystemClose);
	dial->m_minimize.SetBitmap(dial->m_bmpMinimize);
	dial->m_maximize.SetBitmap(dial->m_bmpMaximize);
	dial->m_help.SetBitmap(dial->m_bmpHelp);*/
//	dial->ShowWindow(SW_SHOW);
//	dial->RedrawWindow();
//	dial->OnSize(SIZE_RESTORED,dial->viewsize.Width(),dial->viewsize.Height()); // resizes everything since fonts change when they become visible
//	LPARAM lParam;
//  	lParam=dial->viewsize.Width()+(dial->viewsize.Height()<<16);
//	dial->PostMessage(WM_SIZE,SIZE_RESTORED,lParam);
	// this is an attempt to resize the window after everything is drawn but it doesnt.
	main->ShowWindow(SW_SHOW);
	return dial;
}
RDialog* RDialog::AddPanel(const DialBox* tree, int X2flag,CRect dialsize)
{
	const DialBox *  b[2]={tree,NULL};
	return AddChildren(b,X2flag,dialsize);
}


RDialog* RDialog::AddPanel(RDialog* dial, int X2flag,CRect rect, FileNum artnum, const Edges& e)
{
	DialBox b(artnum,dial,e);
	return AddPanel(&b,X2flag,rect);
}
/*
    int res=GetCurrentRes();
    if (pdial[dialID]) pdial[dialID]->DestroyPanel();
    dial->Create(dial->MY_IID,this);
    // scale the dialog if necessary due to font size change
    dial->m_scalingfactor=(float)fontdpi/96;
    dial->ScaleDialog(1);
    pdial[dialID]=dial;
    AddPanel(dial,GetDialPosition(dial,dialID),m_currentscreen->resolutions[res]
	    int usedy=homesize.Height();
		dial->viewsize=dial->viewsize2=dial->RECT_NORMAL=rect;
	    dial->MoveWindow(rect);
		dial->parent=this;
	    dial->sibling=fchild;
		fchild=dial;
	    dial->dchild=dial->fchild=NULL;
		dial->dragstate=DRAG_NO;
	    dial->artnum=artnum;
		dial->edges=e;
	    return dial;
	if (m_currentscreen->resolutions[res].dials[dialID].flags & FullScreen::Reso
    else dial->ScaleDialog(1);
    dial->ShowWindow(SW_SHOW);
*/

void RDialog::DestroyPanel()
{
	RDialog** pptr=&parent->fchild;
	while (*pptr!=this)
		pptr=&pptr[0]->sibling;
	pptr[0]=sibling;	//fix list properly!!!
	DestroyWindow();
}

volatile char progress[50]={0};
volatile int progressind=0;

//////////////////////////////////////////////////////////////////////
//
// Function:    AddChildren
// Date:		17/05/99
// Author:		JIM
//
//Description: PANELS WITHIN PANELS
//
//////////////////////////////////////////////////////////////////////
RDialog*	RDialog::AddChildren(const DialBox*const* diallist,int X2flag,CRect& rect)			  
{
	int	usedy=homesize.Height();
	RDialog* dial;

	progressind++;
	progress[progressind]='X';
	for (int i=0;diallist[i];i++)
	{
		progress[progressind]=i;
		dial=diallist[i]->dial;
		if (dial==NULL)	dial = new RDEmptyP;
//		dial->InitArtwork(diallist[i]->art);

		dial->parent=this;
		dial->sibling=fchild;
		fchild=dial;
		dial->dchild=dial->fchild=NULL;
		CRect posn;

//DeadCode JIM 10Jun99 		dial->dragstate=DRAG_NO;
		dial->artnum=diallist[i]->art;
		dial->Create(dial->MY_IID,this);
		dial->m_scalingfactor=(float)fontdpi/96;
		if (X2flag)
			dial->ScaleDialog(2);
		else
			dial->ScaleDialog(1);
		dial->dragstate=DRAG_NO;
		int uid=IDJ_PANEL0+i;
		CWnd* cntrl=GetDlgItem(uid);		//don't know if I should delete this!!!
		if (&rect!=NULL)
		{
			posn=rect;
		}
		else
		if (cntrl==NULL)
		{
			posn.top=usedy;
			posn.left=0;
			posn.right=dial->homesize.Width();
			posn.bottom=usedy+dial->homesize.Height();
//			usedy=posn.bottom;
		}
		else
		{
			cntrl->GetWindowRect(&posn);
			ScreenToClient(&posn);
			cntrl->ShowWindow(SW_HIDE);
		}

		if (posn.right==0)	//indicates use designed w/h
		{
			if (posn.bottom)	//indicates centre on coords
				if (X2flag)		//but coords will double momentarily
				{				//actually, the coords will not be a x2...
								//argh!! it all gets horribly complicated!!!
					posn.left-=dial->viewsize.Width();
					posn.top-=dial->viewsize.Height();
				}
				else
			{
					posn.left-=dial->viewsize.Width()/2;
					posn.top-=dial->viewsize.Height()/2;
				}

			posn.right=posn.left+dial->viewsize.Width();
			posn.bottom=posn.top+dial->viewsize.Height();
//			if (X2flag)		//this is extra, but necessary... why, Dallas?
//			{
//				posn.right=posn.left+dial->viewsize.Width();
//				posn.bottom=posn.top+dial->viewsize.Height();
//			}
		}
		dial->RECT_NORMAL=posn;

		if (posn.top==usedy)
		{	//correction for if dialog placed at bottom of parent...
			dial->RECT_NORMAL.bottom=usedy+dial->homesize.Height();
			usedy=dial->RECT_NORMAL.bottom;
		}

		dial->viewsize=dial->viewsize2=dial->RECT_NORMAL;

		if (diallist[i]->edges)
		{
			dial->edges=*diallist[i]->edges;
			dial->AttachRelevantSplitterBars();
		}
		if (diallist[i]->childtype>=DialMake::TABT)
		{
			dial->homesize=CRect(0,0,0,0);
		}
		dial->MoveWindow(&dial->viewsize);		//IDC_BUTTON1
		CRect tempviewsize=dial->viewsize;
//DeadCode JIM 10Jun99 		dial->m_scalingfactor=(float)fontdpi/96;
//DeadCode JIM 10Jun99 		if (X2flag)
//DeadCode JIM 10Jun99 			dial->ScaleDialog(2);
//DeadCode JIM 10Jun99 		else
//DeadCode JIM 10Jun99 			dial->ScaleDialog(1);
//		dial->MoveWindow(tempviewsize);
		const	DialBox*const* l=diallist[i]->diallist;
		if (diallist[i]->childtype>=DialMake::TABT)
		{
			const HTabBox	*h=(const HTabBox*) diallist[i];
			dial->AddChildren(l,diallist[i]->childtype,h->titles);
		}
		else
			dial->AddChildren(l,X2flag);
	}
	if ((edges.b&EDGE::OCCLUDE_MASK)<EDGE::OCCLUDE_OUTSIDE) //make bigger so can scroll to it.
		homesize.bottom=homesize.top+usedy;
	ShowWindow(SW_SHOW);
	OnSize(SIZE_RESTORED,viewsize.Width(),viewsize.Height()); // calculates height of tabbed sheet and sets sizes

	// count the controls.
	CWnd* firstcontrol;
	CWnd* control = NULL;
	int total=0;
	UINT dlgID;
	control=GetTopWindow();
	while (control)
	{
		total++;
		dlgID=control->GetDlgCtrlID();
		if (dlgID == IDJ_TITLE ||
			dlgID == IDJ_HORZ_SCROLLBAR ||
			dlgID == IDJ_VERT_SCROLLBAR) 
				total--;
		control = control->GetNextWindow();
	}
	if (total==1 && !diallist[0])
	{
		control=GetTopWindow();
		dlgID=control->GetDlgCtrlID();
		while (dlgID == IDJ_TITLE ||
			dlgID == IDJ_HORZ_SCROLLBAR ||
			dlgID == IDJ_VERT_SCROLLBAR) 
		{
			control = control->GetNextWindow();
		}
		// control points to the only control in the dialog box (besides IDJ_TITLE)
		// size to the size of the dialog
//		CRect rect;
//		this->GetClientRect(rect);
		control->MoveWindow(0,0,homesize.Width(),homesize.Height());
	}
	progress[progressind]='-';
	progressind--;
	return dial;
}

//////////////////////////////////////////////////////////////////////
//
// Function:    AddChildren
// Date:		17/05/99
// Author:		JIM
//
//Description: THIS VARIANT DOES TAB SHEETS
//
//////////////////////////////////////////////////////////////////////
void	RDialog::AddChildren(const DialBox*const* diallist,DialMake::ChildType childtype,const IdList* titles)
{
	int	usedy=homesize.Height();
	{
		CRTabs* tabControl;
		tabControl=(CRTabs*)GetDlgItem(IDJ_TABCTRL);
//	ASSERT_KINDOF(CRTabs,tabControl);
		if (childtype==DialMake::TABT) 
			tabControl->SetHorzAlign(TRUE);
		else 
			tabControl->SetHorzAlign(FALSE);
		//delete tabControl;
	}
	for (int i=0;diallist[i];i++)
	{
		RDialog* dial=diallist[i]->dial;
		if (dial==NULL)	dial = new RDEmptyP;
		dial->m_bDrawBackground=true;		//FORCE ARTWORK REDRAW!!!!
//		dial->InitArtwork(diallist[i]->art);
		dial->parent=this;
		dial->sibling=fchild;
		fchild=dial;
		dial->dchild=dial->fchild=NULL;
		CRect posn;
//		GetWindowRect(posn);
//		ScreenToClient(&posn);
		GetClientRect(posn);
		posn.top+=30; // allow space for tabs
//DeadCode JIM 10Jun99 		dial->RECT_NORMAL=posn;
//DeadCode JIM 10Jun99 		dial->dragstate=DRAG_NO;
		dial->artnum=diallist[i]->art;
		dial->Create(dial->MY_IID,this);
		dial->m_scalingfactor=(float)fontdpi/96;
		dial->ScaleDialog(1);
		dial->dragstate=DRAG_NO;
		dial->RECT_NORMAL=posn;
		dial->viewsize=dial->viewsize2=dial->RECT_NORMAL;
		if (diallist[i]->edges)
			dial->edges=*diallist[i]->edges;
		else
			dial->edges=Edges(EDGE::ALIGN_MIN,EDGE::ALIGN_MIN,EDGE::ALIGN_MAX,EDGE::ALIGN_MAX);
//		dial->SetMinSize(RECT_MIN);
//		dial->SetMaxSize(RECT_MAX);
		const	DialBox*const* l=diallist[i]->diallist;
		if (diallist[i]->childtype>=DialMake::TABT)
		{
			dial->homesize=CRect(0,0,0,0);
		}
		dial->MoveWindow(&dial->viewsize);		//IDC_BUTTON1
		CRect tempviewsize=dial->viewsize;
		// scale the dialog if necessary due to font size change
//DeadCode JIM 10Jun99 		dial->m_scalingfactor=(float)fontdpi/96;
//DeadCode JIM 10Jun99 		dial->ScaleDialog(1);
//		dial->MoveWindow(tempviewsize);
		if (diallist[i]->childtype>=DialMake::TABT)
		{
			const HTabBox	*h=(const HTabBox*) diallist[i];
			dial->AddChildren(l,diallist[i]->childtype,h->titles);
		}
		else
			dial->AddChildren(l);
		dial->AttachTabToTabControl(titles->list[i]);//(UINT)titles->list[i]->textnum);
	}
	ShowWindow(SW_SHOW);
	OnSize(SIZE_RESTORED,viewsize.Width(),viewsize.Height()); // calculates height of tabbed sheet and sets sizes
}

//RDialog*	RDialog::SetNotifyClosed(InterSheetProcZ i,RDialog* c)
//{
//	NotifyClosedProc=i;															 
//	NotifyClosedSheet=c;
//	return this;
//}


//////////////////////////////////////////////////////////////////////
//
// Function:    EndDialog
// Date:		17/05/99
// Author:		JIM
//
//Description: 
//
//////////////////////////////////////////////////////////////////////
void RDialog::EndDialog( int nResult )
{
	if (edges.l&EDGE::ACTIONS_ARTCHILD) return;
// Search tree of dialogs from the top and send the message to them all
// except for the original one since it has already received it.

	DialExitFix(nResult);
// So find the top.
	if (dragstate!=DRAG_SHUTDOWN)
	{
		RDialog* top=InDialAncestor();
		if (this==top) 
			;/////top->EndDialog(nResult);
		else
		{
			top->dragstate=DRAG_SHUTDOWN;
			skip=this;
			if (nResult==IDOK)
				top->OnOK();
			else
			if (nResult==IDCANCEL)
				top->OnCancel();
			else
				top->EndDialog(nResult);
		}
		top->DestroyWindow();
		return;
	}
// commence a recursive search...
	else
	for (RDialog* child=fchild;child;child=child->sibling)
	{
		child->dragstate=DRAG_SHUTDOWN;
		if (skip==child)
		{
			child->EndDialog(nResult);
		}
		else
		{
			if (nResult==IDOK)
				child->OnOK();
			else
			if (nResult==IDCANCEL)
				child->OnCancel();
			else
				child->EndDialog(nResult);
		}
	}
}

void RDialog::OnOK( )
{
	if (edges.l&EDGE::ACTIONS_ARTCHILD) return;
//F*	TRACE1("Dialog with pointer %d received OK\n",this);
	EndDialog(IDOK);
}
void RDialog::OnCancel( )
{
	if (edges.l&EDGE::ACTIONS_ARTCHILD) return;
//	TRACE1("Dialog with pointer %d received cancel\n",this);
	EndDialog(IDCANCEL);
}
/*
void RDialog::InitArtwork(FileNum art)
{
	artnum=art;
	if (art)
	if(artwork.LoadBitmap(art))
	{
		artwork.GetBitmap(&artworkinfo);
		TRACE1("Artwork created ID: %d\n",art);
//		artwork2.LoadBitmap(art);
//		BITMAP artworkinfo2;
//		artwork2.GetBitmap(&artworkinfo2);
//		if (artworkinfo2.bmBitsPixel>8) // if its an 8 bit image the image is not lightened
//		{
//			// lighten the artwork.  Note all bitmaps are stored at the screen resolution
//			// regardless of the source (so if the screen is 32 bit expects lots
//			// of wasted memory)
//			DWORD dwCount;
//			dwCount=(artworkinfo2.bmWidthBytes*artworkinfo2.bmHeight);
//			UByte* buffer = new UByte[dwCount];
//			int count=artwork2.GetBitmapBits(dwCount,buffer);
//			if (artworkinfo2.bmBitsPixel>=24)
//			{
//				for (int x=0;x<dwCount;x++)
//				{
//					if (buffer[x]>75) buffer[x]-=75;
//					else buffer[x]=0;
//				}
//			}
//			else if (artworkinfo2.bmBitsPixel==16)
//			{
//				UWord* buffer2=(UWord*)buffer;
//				for (int x=0;x<dwCount/2;x++)
//				{
//					UWord colour;
////					colour=buffer2[x] & 0xF800;
//	//				if (colour<(25<<11)) colour+=(6<<11);
////					else colour=(31<<11);
//	//				buffer2[x] = (buffer2[x] & 0x7FF) + colour;
//
////					colour=buffer2[x] & 0x7E0;
//	//				if (colour<(41<<5)) colour+=(12<<5);
//	//				else colour=(63<<5);
//	//				if (colour<(25<<5)) colour+=(6<<5);
//	//				else colour=(31<<5);
//	//				buffer2[x] = (buffer2[x] & 0xF81F) + colour;
//
////					colour=buffer2[x] & 0xF800;
//	//				if (colour<(25<<10)) colour+=(6<<10);
//	//				else colour=(31<<10);
//	//				buffer2[x] = (buffer2[x] & 0x7FF) + colour;
//
//					colour=buffer2[x] & 0xFC00;
//					if (colour<(25<<10)) colour+=(6<<10);
//					else colour=(31<<10);
//					buffer2[x] = (buffer2[x] & 0x3FF) + colour;
//
//					colour=buffer2[x] & 0x3E0;
//					if (colour<(25<<5)) colour+=(6<<5);
//					else colour=(31<<5);
//					buffer2[x] = (buffer2[x] & 0xFC1F) + colour;
//
//					colour=buffer2[x] & 0x1F;
//					if (colour<25) colour+=6;
//					else colour=31;
//					buffer2[x] = (buffer2[x] & 0xFFE0) + colour;
//				}
//			}
//			artwork2.SetBitmapBits(dwCount,buffer);
//			delete buffer;
//		}
	}
	else
	{
		TRACE1("Artwork not created ID: %d\n",art);
	}
}
*/
void RDialog::AttachRelevantSplitterBars()
{
	int seperation;
	CRSpltBar* splitter;
	CRSpltBar* splitterTest;
	CRect dialRect;
	CRect splitterRect;
	GetClientRect(dialRect);
	ClientToScreen(dialRect);
	seperation=INT_MAX;
	splitter=NULL;
	if(edges.r&EDGE::ACTIONS_SPLITTER)
	{
		for (int x=IDJ_DRAG0;x<=IDJ_DRAG5;x++)
		{
			splitterTest=(CRSpltBar*)parent->GetDlgItem(x);
			if (splitterTest)
			{
//				ASSERT_KINDOF(CRSpltBar,splitterTest);
				splitterTest->GetWindowRect(splitterRect);
				if (splitterRect.Height()>splitterRect.Width() &&
					abs(splitterRect.left-dialRect.right)<seperation)
				{

					if (splitterTest->GetTopLeftWindow()==NULL)
					{
						seperation=abs(splitterRect.left-dialRect.right);
						splitter=splitterTest;
						break;	//very dirty... splittertest not deleted!
					}
				}
			}
			//delete splitterTest;
		}
		if (splitter)
		{
			splitter->SetTopLeftWindow((long)this);
		}
		else TRACE0("Failed to find the left edge of an unused vertical splitter bar\n");
		//delete splitter;
	}
	seperation=INT_MAX;
	splitter=NULL;
	if(edges.b&EDGE::ACTIONS_SPLITTER)
	{
		for (int x=IDJ_DRAG0;x<=IDJ_DRAG5;x++)
		{
			splitterTest=(CRSpltBar*)parent->GetDlgItem(x);
			if (splitterTest)
			{
//				ASSERT_KINDOF(CRSpltBar,splitterTest);
				splitterTest->GetWindowRect(splitterRect);
				if (splitterRect.Height()<splitterRect.Width() &&
					abs(splitterRect.top-dialRect.bottom)<seperation)
				{
					if (splitterTest->GetBottomRightWindow()==NULL)
					{
						seperation=abs(splitterRect.top-dialRect.bottom);
						splitter=splitterTest;
						break;
					}
				}
				//delete splitterTest;
			}
		}
		if (splitter)
		{
			splitter->SetBottomRightWindow((long)this);
		}
		else TRACE0("Failed to find the top edge of an unused vertical splitter bar\n");
		//delete splitter;
	}
	seperation=INT_MAX;
	splitter=NULL;
	if(edges.l&EDGE::ACTIONS_SPLITTER)
	{
		for (int x=IDJ_DRAG0;x<=IDJ_DRAG5;x++)
		{
			splitterTest=(CRSpltBar*)parent->GetDlgItem(x);
			if (splitterTest)
			{
//				ASSERT_KINDOF(CRSpltBar,splitterTest);
				splitterTest->GetWindowRect(splitterRect);
				if (splitterRect.Height()>splitterRect.Width() &&
					abs(splitterRect.right-dialRect.left)<seperation)
				{
					if (splitterTest->GetBottomRightWindow()==NULL)
					{
						seperation=abs(splitterRect.right-dialRect.left);
						splitter=splitterTest;
						break;
					}
				}
				//delete splitterTest;
			}
		}
		if (splitter)
		{
			splitter->SetBottomRightWindow((long)this);
		}
		else TRACE0("Failed to find the right edge of an unused vertical splitter bar\n");
		//delete splitter;
	}
	seperation=INT_MAX;
	splitter=NULL;
	if(edges.t&EDGE::ACTIONS_SPLITTER)
	{
		for (int x=IDJ_DRAG0;x<=IDJ_DRAG5;x++)
		{
			splitterTest=(CRSpltBar*)parent->GetDlgItem(x);
			if (splitterTest)
			{
//				ASSERT_KINDOF(CRSpltBar,splitterTest);
				splitterTest->GetWindowRect(splitterRect);
				if (splitterRect.Height()<splitterRect.Width() &&
					abs(splitterRect.bottom-dialRect.top)<seperation)
				{
					if (splitterTest->GetTopLeftWindow()==NULL)
					{
						seperation=abs(splitterRect.bottom-dialRect.top);
						splitter=splitterTest;
						//delete splitterTest;
					}
				}
			}
		}
		if (splitter)
		{
			splitter->SetTopLeftWindow((long)this);
		}
		else TRACE0("Failed to find the bottom edge of an unused vertical splitter bar\n");
		//delete splitter;
	}
}

void RDialog::AttachTabToTabControl(const struct IdEntry *const list)
{
	// find the tab control
	CRTabs* tabControl;
	tabControl=(CRTabs*)parent->GetDlgItem(IDJ_TABCTRL);
	if (tabControl==NULL)
	{
		TRACE0("No tab control exists\n");
		return; // no tab control exists
	}
//	ASSERT_KINDOF(CRTabs,tabControl);
	// set this tab
	CWnd* cntrl = (CWnd*)tabControl->GetFirstTab();
	if (cntrl)
	{ // not the first tab so reize this to size of first tab
		this->ShowWindow(SW_HIDE);
	}
	else
	{
		tabControl->SetFirstTab((long)this);
		this->ShowWindow(SW_SHOW);
	}
	CString text;
	if (list->idtype == IdEntry::T_IDT) text.LoadString(list->textnum);
	else if (list->idtype == IdEntry::T_CHAR) text = list->textstr;

	if (text.IsEmpty())
	{
		CRButton* title;
		title = (CRButton*)GetDlgItem(IDJ_TITLE);
		if (title != NULL)
		{
//			ASSERT_KINDOF(CRTitle,title);
//			tabControl->SetFont(title->GetFont()); // do something with fontnum here...
			tabControl->SetForeColor(title->GetForeColor());
			text=title->GetCaption();
		}
		//delete title;
	}

	tabControl->AddTab(text,(long)this);
	//delete tabControl;
//	TRACE0("Tab successfully added to control\n");
}
////////////////////////////////////////////////////////////////////////
//Optional initialisation
void RDialog::SetMinSize(CRect rect)
{
	if (InDialAncestor()->minsize==RECT_MIN)
	{
		InDialAncestor()->minsize=rect;
	}
}

void RDialog::SetMaxSize(CRect rect)
{
	CRect rect2=InDialAncestor()->maxsize;
	if (InDialAncestor()->maxsize==RECT_MAX)
	{
		InDialAncestor()->maxsize=rect;
	}
}

////////////////////////////////////////////////////////////////////////
BEGIN_MESSAGE_MAP(RDialog, CDialog)
	//{{AFX_MSG_MAP(RDialog)
//	ON_WM_HSCROLL()
//	ON_WM_VSCROLL()
	ON_WM_MOUSEMOVE()
	ON_WM_PAINT()	//MESSAGE(WM_PAINT,OnPaint)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_SETCURSOR()
	ON_WM_SIZE()
	ON_WM_MOVE()
	ON_WM_CREATE()
	ON_WM_NCMOUSEMOVE()
	ON_WM_NCLBUTTONDOWN()
	ON_WM_ERASEBKGND()
	ON_WM_DESTROY()
	ON_MESSAGE( WM_GETARTWORK, OnGetArt)
	ON_MESSAGE( WM_GETXYOFFSET, OnGetXYOffset)
	ON_MESSAGE( WM_GETGLOBALFONT, OnGetGlobalFont)
	ON_MESSAGE( WM_GETFILE, OnGetFile)
	ON_MESSAGE( WM_RELEASELASTFILE, OnReleaseLastFile)
	ON_MESSAGE( WM_GETX2FLAG, OnGetX2Flag)
	ON_MESSAGE( WM_GETOFFSCREENDC, OnGetOffScreenDC)
	ON_MESSAGE( WM_GETHINTBOX, OnGetHintBox)
	ON_MESSAGE( WM_PLAYSOUND, OnPlaySound)
	ON_MESSAGE( WM_GETCOMBODIALOG, OnGetComboDialog)
	ON_MESSAGE( WM_GETCOMBOLISTBOX, OnGetComboListbox)
	ON_MESSAGE( WM_ACTIVEXSCROLL, OnActiveXScroll)
	ON_MESSAGE( WM_GETSTRING, OnGetString)
	ON_WM_GETMINMAXINFO()
	//}}AFX_MSG_MAP
	ON_MESSAGE( WM_COMMANDHELP,OnCommandHelp)

END_MESSAGE_MAP()

BEGIN_EVENTSINK_MAP(RDialog, CDialog)
    //{{AFX_EVENTSINK_MAP(RDialog)
	ON_EVENT(RDialog, IDJ_TITLE, 2 /* Cancel */, OnCancel, VTS_NONE)
	ON_EVENT(RDialog, IDJ_TITLE, 3 /* OK */, OnOK, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

/////////////////////////////////////////////////////////////////////////////
// RDialog message handlers
//Scrolling

void RDialog::OnActiveXScroll(int scrollpos, BOOL horzalign)
{
	if (m_moving) return;
	m_moving=TRUE;
	if (horzalign)
	{
		scrollpos-=homesize.left;
		homesize.left+=scrollpos;
		homesize.right+=scrollpos;
		UpdateTitle();
		ScrollWindow(-scrollpos,0);
		UpdateTitle();
	}
	else
	{
		scrollpos-=homesize.top;
		homesize.top+=scrollpos;
		homesize.bottom+=scrollpos;
		UpdateTitle();
		ScrollWindow(0,-scrollpos);
		UpdateTitle();
	}
}

/*
void RDialog::OnHScroll(UINT type, UINT pos, CScrollBar* bar) 
{
	// TODO: Add your message handler code here and/or call default
	
	CDialog::OnHScroll(type, pos, bar);
	int p2=ModScroll(SB_HORZ,type,pos,bar)-homesize.left;
	homesize.left+=p2;
	homesize.right+=p2;
	UpdateTitle();
	ScrollWindow(-p2,0);
	UpdateTitle();
}

void RDialog::OnVScroll(unsigned int type,unsigned int pos,class CScrollBar * bar)
{
	// TODO: Add your message handler code here and/or call default

	CDialog::OnVScroll(type,pos,bar);
	int p2=ModScroll(SB_VERT,type,pos,bar)-homesize.top;
	homesize.top+=p2;
	homesize.bottom+=p2;
	ScrollWindow(0,-p2);
}

int	RDialog::ModScroll(UINT id,UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	SCROLLINFO	s={sizeof(s),SIF_ALL};
	GetScrollInfo(id,&s);
	switch (nSBCode)
	{
		case SB_LEFT:		//SB_TOP
			nPos=0;
		break;
		case SB_LINEUP:		//SB_LINELEFT       
			nPos=s.nPos-1;
			if (nPos<0)
				nPos=0;
		break;
		case SB_PAGEUP:		//SB_PAGELEFT       
			nPos=s.nPos-s.nPage;
			if (nPos<0)
				nPos=0;
		break;
		case SB_LINEDOWN:	//SB_LINERIGHT      
			nPos=s.nPos+1;
			if (nPos>s.nMax-s.nPage)
				nPos=s.nMax-s.nPage;
		break;
		case SB_PAGEDOWN:	//SB_PAGERIGHT      
			nPos=s.nPos+s.nPage;
			if (nPos>s.nMax-s.nPage)
				nPos=s.nMax-s.nPage;
		break;
		case SB_BOTTOM:		//SB_RIGHT          
			nPos=s.nMax-s.nPage;
		break;
		case SB_THUMBPOSITION:
		case SB_THUMBTRACK:
		break;
		case SB_ENDSCROLL:
			nPos=s.nPos;
	}
	SetScrollPos(id,nPos);
	return nPos;
}
*/
///////////////////////////////////////////////////////////////////////
//Painting

BOOL RDialog::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	
//	return CDialog::OnEraseBkgnd(pDC);	 //FIX!!!  (
	return TRUE;

}

void RDialog::OnPaint() 
{
	if (dragstate==DRAG_INIT)
		return;
	PAINTSTRUCT paintstruct;
	CDC* pDC;
	pDC=BeginPaint(&paintstruct);
	paintstruct.fErase=TRUE;
	BYTE* pData;
	if (!artnum)
		if (parent)
			artnum=OnGetArt();
	if (artnum)
	{
		// see if there are any parents with the same artnum;
		if (!m_bDrawBackground)
		{
			m_bDrawBackground=TRUE;
			RDialog* newparent=this;
			while ((newparent=newparent->parent)!=NULL)
			{
				if (newparent->artnum==artnum)
				{
//TEMPCODE JIM 17/05/99 					m_bDrawBackground=TRUE;
					EndPaint(&paintstruct);
					return;
				}
			}
		}
		fileblock picture(artnum,PalTrans);
		pData=(BYTE*)getdata(picture);
		if (pData && pData[0]=='B' && pData[1]=='M') // checks if its a bitmap file
		{
			// now render it...
			BITMAPFILEHEADER* pFile=(BITMAPFILEHEADER*)pData;
			BITMAPINFO* pInfo=(BITMAPINFO*)(pData+sizeof(BITMAPFILEHEADER));
			pData+=pFile->bfOffBits;
			// check if any of the parents have the same artwork then calculate an offset
			long offsets=OnGetXYOffset();
			SetDIBitsToDevice(pDC->m_hDC,short(offsets & 0x0000FFFF),short((offsets & 0xFFFF0000)>>16),pInfo->bmiHeader.biWidth, pInfo->bmiHeader.biHeight,
				0,0,0,pInfo->bmiHeader.biHeight,pData,pInfo,DIB_RGB_COLORS);

//DEADCODE JIM 19/05/99 //test wipe...
//DEADCODE JIM 19/05/99 			static int	rgb=0;
//DEADCODE JIM 19/05/99 			rgb=(rgb+0x004008)&0x00ffffff;
//DEADCODE JIM 19/05/99 			pDC->FillSolidRect(0,0,2048,2048,COLORREF(rgb));
//DEADCODE JIM 19/05/99 //test wipe...


		}
	}
//	if ( artnum && artworkinfo.bmWidth)
//	{
//		TRACE0("Drawing artwork\n");
//		TRACE2("Left,top: %d %d\n",rect.left,rect.top);
//		TRACE2("Right,bot: %d %d\n",rect.right,rect.bottom);
		// check if any of the parents have the same artwork then calculate an offset
//		long offsets=OnGetXYOffset();
//		CDC memDC;
//		memDC.CreateCompatibleDC(pDC);
//		CBitmap* pOldBitmap;
//		pOldBitmap = memDC.SelectObject(&artwork);
//		pDC->BitBlt(short(offsets & 0x0000FFFF),short((offsets & 0xFFFF0000)>>16),artworkinfo.bmWidth,artworkinfo.bmHeight,&memDC,0,0,SRCCOPY);
//		memDC.SelectObject(pOldBitmap);
//		memDC.DeleteDC();
//	}
	// check if its title sheet
/*
	if (parent != NULL && parent->dragstate==DRAG_DIALOG)
	{
		// check for existance of title
		CRTitle* title;  // will give bad results if IDJ_TITLE is not an RTitle
		title=GETDLGITEM(IDJ_TITLE);
		if (titlenewparent)
		{
//			ASSERT_KINDOF(CRTitle,title);
			CFont* pOldFont;
			TEXTMETRIC tm;
			const CString& strCaption = title->GetCaption();

			// Set the ForeColor property color and transparent background mode into the device context
			COLORREF cr = RGB(0x00,0x00,0x00);
			OleTranslateColor(title->GetForeColor(), NULL, &cr);
			pDC->SetTextColor(cr);
			pDC->SetBkMode(TRANSPARENT);

			// Draw the caption using the stock Font and ForeColor properties
			pOldFont = (CFont*)title->SelStockFont((long)pDC);
			pDC->GetTextMetrics(&tm);
			pDC->SetTextAlign(TA_CENTER | TA_TOP);
			pDC->ExtTextOut((rect.left + rect.right - (20*m_showTick)) / 2, 0,
				ETO_CLIPPED, rect, strCaption, strCaption.GetLength(), NULL);
			pDC->SelectObject(pOldFont);
		}
	}
*/
	EndPaint(&paintstruct);
}

///////////////////////////////////////////////////////////////////////
//Mouse
void RDialog::OnMouseMove(UINT nFlags, CPoint p) 
{  	
//	TRACE3("Window: %d Mouse dx %d,dy %d\n",m_hWnd,p.x,p.y);
//	TRACE0("Detected Mousemove\n");
	if (m_moving) return;
//	m_bChangeCursor=TRUE;
	if (!parent) 
	{
		TRACE0("ERROR: Base sheet is visible!");
		return;
	}
//	TRACE0("Processing Mousemove\n");
//	m_bChangeCursor=FALSE;
//	cursor=IDC_ARROW;
/*	if (parent->dragstate==DRAG_DIALOG)
	{
		if (p.x<5 || p.x>viewsize.right-viewsize.left-5) cursor=IDC_SIZEWE;
		if (p.y<5 || p.y>viewsize.bottom-viewsize.top-5) cursor=IDC_SIZENS;
		if (cursor!=IDC_ARROW)
		{
			if (p.x<5 && p.y<5) cursor=IDC_SIZENWSE;
			if (p.x>viewsize.right-viewsize.left-5 && p.y>viewsize.bottom-viewsize.top-5) cursor=IDC_SIZENWSE;
			if (p.x<5 && p.y>viewsize.bottom-viewsize.top-5) cursor=IDC_SIZENESW;
			if (p.x>viewsize.right-viewsize.left-5 && p.y<5) cursor=IDC_SIZENESW;
		}
	}*/
	int dx=p.x-lastdown.x,dy=p.y-lastdown.y;
	if  (dragstate && dragstate!=DRAG_DIALOG)
	{
		if (dragstate==DRAG_SCROLL)
		{
//			TRACE2("home:%d,%d\n",homesize.right-(2*homesize.left)+currscrw,homesize.bottom-(2*homesize.top)+currscrh);
//			TRACE2(",%d,%d\n",homesize.right,homesize.bottom);
//			TRACE2("view:%d,%d",viewsize.left,viewsize.top);
//			TRACE2(",%d,%d\n",viewsize.right,viewsize.bottom);
//			TRACE2("target: %d,%d\n",viewsize.right-viewsize.left,viewsize.bottom-viewsize.top);
//			TRACE2("SCH %d SCW %d\n",currscrw,currscrh);
			lastdown=p;
			// do some checks here for out of bounds
			// homesize increases as you move it to the left/up so conversion
			// to where down/right is positive is required
//			TRACE2("Original dx %d,dy %d\n",dx,dy);
			if (homesize.left-dx<0)
			{
				dx=homesize.left;
			}
			if (homesize.top-dy<0)
			{
				dy=homesize.top;
			}
			if (homesize.right-(2*homesize.left)+currscrw+dx<viewsize.right-viewsize.left)
			{
//				TRACE0("X deviance detected\n");
				dx=(viewsize.right-viewsize.left)-(homesize.right-(2*homesize.left)+currscrw);
			}
			if (homesize.bottom-(2*homesize.top)+currscrh+dy<viewsize.bottom-viewsize.top)
			{
//				TRACE0("Y deviance detected\n");
				dy=(viewsize.bottom-viewsize.top)-(homesize.bottom-(2*homesize.top)+currscrh);
			}
			if (homesize.Height()+currscrh <= viewsize.Height()) dy=0;
			if (homesize.Width()+currscrw <= viewsize.Width()) dx=0;
			TRACE1("Scrolling %d\n",m_hWnd);
		    ::SetCursor(AfxGetApp()->LoadStandardCursor(IDC_SIZEALL));
			homesize.top-=dy;
			homesize.bottom-=dy;
			homesize.left-=dx;
			homesize.right-=dx;
			ScrollWindow(+dx,+dy);
//			SetScrollPos(SB_VERT,homesize.top);
//			SetScrollPos(SB_HORZ,homesize.left);
			if (m_pVertScrollBar)
				m_pVertScrollBar->SetScrollPos(homesize.top);
			if (m_pHorzScrollBar)
				m_pHorzScrollBar->SetScrollPos(homesize.left);
			m_moving=TRUE;
			UpdateTitle();
		}
		else
		{
			CRect viewsize=parent->viewsize;
			if (dragstate==DRAG_MOVE)
			{
				viewsize.top+=dy;
				viewsize.bottom+=dy;
				viewsize.left+=dx;
				viewsize.right+=dx;
				m_moving=TRUE;
			}
			else
			{
				if (viewsize.Width()+dx>maxsize.Width()) 
					dx=maxsize.Width()-viewsize.Width();
				if (viewsize.Width()+dx<minsize.Width()) 
					dx=minsize.Width()-viewsize.Width();;
				if (viewsize.Height()+dy>maxsize.Height()) 
					dy=maxsize.Height()-viewsize.Height();
				if (viewsize.Height()+dy<minsize.Height()) 
					dy=minsize.Height()-viewsize.Height();

				if (dragstate&DRAG_LEFT)
				{
					viewsize.left+=dx;
				}
				if (dragstate&DRAG_RIGHT)
				{
					viewsize.right+=dx;
					lastdown.x+=dx;
				}
				if (dragstate&DRAG_TOP)
				{
					viewsize.top+=dy;
				}
				if (dragstate&DRAG_BOT)
				{
					viewsize.bottom+=dy;
					lastdown.y+=dy;
				}
				if (parent->viewsize!=viewsize)
				{
					m_moving=TRUE;
				}
			}
//			TRACE("Size dx %d,dy %d\n",viewsize.right,viewsize.bottom);
			parent->MoveWindow(&viewsize);
		}
	}

}


void RDialog::OnLButtonDown(UINT nFlags, CPoint p) 
{
	// TODO: Add your message handler code here and/or call default
//	TRACE0("Received LBUTTONDOWN\n");
	if (!parent || edges.l&EDGE::ACTIONS_ARTCHILD) return;
	SetCapture();
	lastdown=p;
	int ds=0;
	if (parent->dragstate!=DRAG_DIALOG)
	{
		// check if the dialog is scrollable...
		if (viewsize.Width()>=homesize.Width() && viewsize.Height()>=homesize.Height())
		{
			ReleaseCapture();
			RDialog* newparent=parent;
			while(TRUE)
			{
				ASSERT(newparent); // this might happen if the topmost parent isnt a DRAG_DIALOG
				if (newparent->parent->dragstate==DRAG_DIALOG)
				{
					newparent->dragstate=DRAG_MOVE;
//					TRACE0("Set Drag Move 1\n");
					break;
				}
				else if (newparent->viewsize.Width()<newparent->homesize.Width() || newparent->viewsize.Height()<newparent->homesize.Height())
				{
					newparent->dragstate=DRAG_SCROLL;
				    ::SetCursor(AfxGetApp()->LoadStandardCursor(IDC_SIZEALL));
					break;
				}
				else newparent=newparent->parent;
			}
			newparent->SetCapture();
			CRect rect;
			CRect newparentrect;
			GetClientRect(rect);
			ClientToScreen(rect);
			newparent->GetClientRect(newparentrect);
			newparent->ClientToScreen(newparentrect);
			newparent->lastdown=p-newparentrect.TopLeft()+rect.TopLeft();
		}
		else
		{
			ds=DRAG_SCROLL;
			// change to a hand using OEM?
		    ::SetCursor(AfxGetApp()->LoadStandardCursor(IDC_SIZEALL));
	//	    ::SetCursor(AfxGetApp()->LoadOEMCursor(OIC_HAND));
		}
	}
	else
	{
/*		if (lastdown.x<5)
		{
			ds+=DRAG_LEFT;
		}
		else
		if (lastdown.x>viewsize.right-viewsize.left-5)
		{
			ds+=DRAG_RIGHT;
		}
		if (lastdown.y<5)
		{
			ds+=DRAG_TOP;
		}
		else
		if (lastdown.y>viewsize.bottom-viewsize.top-5)
		{
			ds+=DRAG_BOT;
		}*/
//		if (!ds)
//			if (	lastdown.x>viewsize.right-viewsize.left-20
//				&&	lastdown.y>viewsize.bottom-viewsize.top-20
//				)
//				ds+=DRAG_BOT+DRAG_RIGHT;
//			else
//		lastdown+=CPoint(borderwidth,borderwidth);
		ds=DRAG_MOVE;
//		TRACE0("Set Drag Move 2\n");
	}
	dragstate=DragSide(ds);

}

void RDialog::OnNcMouseMove(UINT nHitTest, CPoint point) 
{
//	m_bChangeCursor=FALSE;
	CDialog::OnNcMouseMove(nHitTest, point);
}

void RDialog::OnNcLButtonDown(UINT nHitTest, CPoint p) 
{
	// TODO: Add your message handler code here and/or call default
	
	CDialog::OnNcLButtonDown(nHitTest, p);
	ScreenToClient(&p);

	
	lastdown=p;
	int ds=0;
	if (parent && parent->dragstate==DRAG_DIALOG)
	{
		CRect client;
		GetClientRect(&client);
		if (lastdown.x>client.Width() && lastdown.y>client.Height()	)
		{
			ds=DRAG_BOT+DRAG_RIGHT;
			SetCapture();
			dragstate=DragSide(ds);
		}
	}
	//WIBNI: on child sheet, command is passed up to parent if align max
	//or to splitter bar if align splitter

}

void RDialog::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
//	CDialog::OnLButtonUp(nFlags, point);
	ReleaseCapture();
	dragstate=DRAG_NO;
	CRect client;
	this->GetClientRect(client);
	if (point.x>client.Width() && point.y>client.Height())
	{
		OnNcMouseMove(NULL, point); 
	}

}

BOOL RDialog::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	// TODO: Add your message handler code here and/or call default
//    if (m_bChangeCursor)
//	{
//		::SetCursor(AfxGetApp()->LoadStandardCursor(cursor));
//		return true;
//	}
//	else 
		return CDialog::OnSetCursor(pWnd, nHitTest, message);
}
///////////////////////////////////////////////////////////////////
//Moving dialog
void RDialog::OnSize(UINT t, int w, int h) 
{
	CDialog::OnSize(t,w,h);
	// TODO: Add your message handler code here
	if (dragstate==DRAG_INIT)
		return;
	CRect cl;
	GetWindowRect(cl);
	CRect clientrect;
	GetClientRect(clientrect);
	w+=(cl.Width()-clientrect.Width());
	h+=(cl.Height()-clientrect.Height());
	//code for scroll bars here!
	int oldw=viewsize.Width();
	int oldh=viewsize.Height();
	viewsize.right=viewsize.left+w;
	viewsize.bottom=viewsize.top+h;
	if (dragstate==DRAG_DIALOG)
	{
		homesize.right=w;
		homesize.bottom=h;
	}
	else
	{
		int	dx=0,dy=0;

		if (viewsize.Width()>=homesize.Width() && viewsize.Height()>=homesize.Height())
		{
			if (currscrh)
			{
				if (m_pHorzScrollBar)
					m_pHorzScrollBar->ShowWindow(SW_HIDE);
				currscrh=0;
				viewsize.bottom+=15;
			}
			if (currscrw)
			{
				if (m_pVertScrollBar)
					m_pVertScrollBar->ShowWindow(SW_HIDE);
				currscrw=0;
				viewsize.right+=15;
			}
//			ShowScrollBar(SB_HORZ,FALSE);
//			ShowScrollBar(SB_VERT,FALSE);
		}
		else
		{
			int oldcurrscrh=currscrh;
			int oldcurrscrw=currscrw;
			if (viewsize.Width()>=homesize.Width() || edges.b&EDGE::OCCLUDE_INSIDE)
				currscrh=0;
			else
//				currscrh=-actscrh;
				currscrh=15;
			if (viewsize.Height()-currscrh>=homesize.Height() || edges.r&EDGE::OCCLUDE_INSIDE)
				currscrw=0;
			else
//				currscrw=-actscrw;
				currscrw=15;
			if (viewsize.Width()-currscrw>=homesize.Width() || edges.b&EDGE::OCCLUDE_INSIDE)
				currscrh=0;
			else
//				currscrh=-actscrh;
				currscrh=15;
			if (currscrw && !oldcurrscrw)
				viewsize.right-=15;
			else if (!currscrw && oldcurrscrw)
				viewsize.right+=15;
			if (currscrh && !oldcurrscrh)
				viewsize.bottom-=15;
			else if (!currscrh && oldcurrscrh)
				viewsize.bottom+=15;
			if (currscrw)
			{
//				SCROLLINFO s={sizeof(SCROLLINFO),SIF_ALL,0,homesize.Height(),h-currscrh,homesize.top,0};
//				SetScrollInfo(SB_VERT,&s,TRUE);
//				ShowScrollBar(SB_VERT,TRUE);
				if (!m_pVertScrollBar)
				{
					m_pVertScrollBar=new CRScrlBar;
					m_pVertScrollBar->Create(NULL, WS_VISIBLE, CRect(-1,-1,-1,-1), parent, IDJ_VERT_SCROLLBAR);
					m_pVertScrollBar->SetParentPointer((long)this);
					m_pVertScrollBar->SetUseMessagesInsteadOfEvents(TRUE);
				}
				m_pVertScrollBar->SetScrollPos(homesize.top);
				m_pVertScrollBar->SetPageSize(viewsize.Height());
				m_pVertScrollBar->SetMaxValue(homesize.Height()-viewsize.Height());
				m_pVertScrollBar->MoveWindow(viewsize.right,viewsize.top,15,viewsize.Height());
				m_pVertScrollBar->ShowWindow(SW_SHOW);
			}
			else
			{
//				ShowScrollBar(SB_VERT,FALSE);
				if (m_pVertScrollBar)
					m_pVertScrollBar->ShowWindow(SW_HIDE);
			}
			if (currscrh)
			{
//				SCROLLINFO s={sizeof(SCROLLINFO),SIF_ALL,0,homesize.Width(),w
//					-currscrw,homesize.left,0};
//				SetScrollInfo(SB_HORZ,&s,TRUE);
//				ShowScrollBar(SB_HORZ,TRUE);
				if (!m_pHorzScrollBar)
				{
					m_pHorzScrollBar=new CRScrlBar;
					m_pHorzScrollBar->Create(NULL, WS_VISIBLE, CRect(-1,-1,-1,-1), parent, IDJ_HORZ_SCROLLBAR);
					m_pHorzScrollBar->SetHorzAlign(TRUE);
					m_pHorzScrollBar->SetParentPointer((long)this);
					m_pHorzScrollBar->SetUseMessagesInsteadOfEvents(TRUE);
				}
				m_pHorzScrollBar->MoveWindow(viewsize.left,viewsize.bottom,viewsize.Width(),15);
				m_pHorzScrollBar->ShowWindow(SW_SHOW);
			}
			else
			{
//				ShowScrollBar(SB_HORZ,FALSE);
				if (m_pHorzScrollBar)
					m_pHorzScrollBar->ShowWindow(SW_HIDE);
			}
		}
		if (homesize.left<0)
		{
			dx=homesize.left;
		}
		if (homesize.top<0)
		{
			dy=homesize.top;
		}
		if (homesize.right-(2*homesize.left)+currscrw<viewsize.right-viewsize.left)
		{
			dx=(viewsize.right-viewsize.left)-(homesize.right-(2*homesize.left)+currscrw);
		}
		if (homesize.bottom-(2*homesize.top)+currscrh<viewsize.bottom-viewsize.top)
		{
			dy=(viewsize.bottom-viewsize.top)-(homesize.bottom-(2*homesize.top)+currscrh);
		}
		if (homesize.Height()+currscrh <= viewsize.Height())
		{
			dy=homesize.top;
		}
		if (homesize.Width()+currscrw <= viewsize.Width())
		{
			dx=homesize.left;
		}
		homesize.top-=dy;
		homesize.bottom-=dy;
		homesize.left-=dx;
		homesize.right-=dx;
		ScrollWindow(+dx,+dy);
//		SetScrollPos(SB_VERT,homesize.top);
//		SetScrollPos(SB_HORZ,homesize.left);
		if (m_pVertScrollBar)
			m_pVertScrollBar->SetScrollPos(homesize.top);
		if (m_pHorzScrollBar)
			m_pHorzScrollBar->SetScrollPos(homesize.left);
	}

	for (RDialog* child=fchild;child;child=child->sibling)
	{
		bool moved=false;
		CRect cviewsize=child->viewsize;
		CRect cviewsize2=child->viewsize2;
		moved|=OnSizeAxis(oldw,w,cviewsize2.left,child->edges.l);
		moved|=OnSizeAxis(oldw,w,cviewsize.left,child->edges.l);
		moved|=OnSizeAxis(oldw,w,cviewsize2.right,child->edges.r);
		moved|=OnSizeAxis(oldw,w,cviewsize.right,child->edges.r);
//		if (cviewsize2.Width()>child->maxsize.Width())
//			cviewsize.right=cviewsize.left+child->maxsize.Width();
//		if (cviewsize2.Width()<child->minsize.Width()) 
//			cviewsize.right=cviewsize.left+child->minsize.Width();

		moved|=OnSizeAxis(oldh,h,cviewsize2.top,child->edges.t);
		moved|=OnSizeAxis(oldh,h,cviewsize.top,child->edges.t);
		moved|=OnSizeAxis(oldh,h,cviewsize2.bottom,child->edges.b);
		moved|=OnSizeAxis(oldh,h,cviewsize.bottom,child->edges.b);
//		if (cviewsize2.Height()>child->maxsize.Height())
//			cviewsize.bottom=cviewsize.top+child->maxsize.Height();
//		if (cviewsize2.Height()<child->minsize.Height())
//			cviewsize.bottom=cviewsize.top+child->minsize.Height();
		child->viewsize2=cviewsize2;
		CRect rect;
		child->GetWindowRect(rect);
		CRect rect2;
		GetWindowRect(rect2);
		rect=rect-rect2.TopLeft();
		child->MoveWindow(&cviewsize);
	}
	UpdateTitle();
	CRTabs* tabcontrol;
	tabcontrol=(CRTabs*)GetDlgItem(IDJ_TABCTRL);
	if (tabcontrol!=NULL)
	{
		CRect rect;
		tabcontrol->GetClientRect(rect);
		long height=0;
		long width=0;
		if (tabcontrol->GetHorzAlign())
		{
			height=tabcontrol->CalculateHeight(viewsize.Width());
			tabcontrol->MoveWindow(0,0,viewsize.Width(),height);
		}
		else
		{
			width=tabcontrol->CalcWidestWord();
			tabcontrol->MoveWindow(viewsize.Width()-width,0,width,viewsize.Height());
		}
		// move all the children dialogs...
		for (RDialog* child=fchild;child;child=child->sibling)
		{
			child->MoveWindow(0,height,viewsize.Width()-width,viewsize.Height()-height);
		}
	}
	//delete tabcontrol;
//	MoveWindow(viewsize);
}

bool RDialog::OnSizeAxis(int oldw,int neww,long& curr,Edge act)
{
	switch (act&EDGE::ALIGN_MASK)
	{
//	case	EDGE::ALIGN_MIN:
//	case	EDGE::ALIGN_SPLIT:	
//		return false;
	case	EDGE::ALIGN_MAX:
			curr=curr+neww-oldw;
		return true;
	case	EDGE::ALIGN_STRETCH:
			curr=curr*neww/oldw;
		return true;
	}
	return false;
}

void RDialog::OnMove(int x, int y) 
{
	CDialog::OnMove(x, y);
	
	// TODO: Add your message handler code here
	if (dragstate==DRAG_INIT) return;
	x-=viewsize.left;
	y-=viewsize.top;
	viewsize.left+=x;
	viewsize.right+=x;
	viewsize.top+=y;
	viewsize.bottom+=y;
	
}
///////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////
//Close-down
void RDialog::PostNcDestroy() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CDialog::PostNcDestroy();
	DialExitFix(-1);
	if (m_pHorzScrollBar)
	{
		m_pHorzScrollBar->DestroyWindow();
		delete m_pHorzScrollBar;
		m_pHorzScrollBar=NULL;
	}
	if (m_pVertScrollBar)
	{
		m_pVertScrollBar->DestroyWindow();
		delete m_pVertScrollBar;
		m_pVertScrollBar=NULL;
	}
	delete this;
}


void RDialog::OnDestroy() 
{
	CDialog::OnDestroy();

}

FileNum RDialog::OnGetArt()
{
	if (parent && !artnum) 
		return parent->OnGetArt();
	return artnum;
}

long RDialog::OnGetXYOffset()
{
	CRect rect;
	GetClientRect(rect);
	CRect windowrect=rect;
	ClientToScreen(windowrect);
	RDialog* newparent=this;
	short offsetx=0;
	short offsety=0;
	while (newparent->parent)
	{
		if (newparent->parent->artnum==artnum)
		{
			CRect parentrect;
			newparent->parent->GetClientRect(parentrect);
			newparent->parent->ClientToScreen(parentrect);
			offsetx=parentrect.left-windowrect.left;
			offsety=parentrect.top-windowrect.top;
		}
		newparent=newparent->parent;
	}
	// if theres a title on the main parent add an extra offset
	// (providing the artwork is the same as the parent)
	RDialog* top=InDialAncestor();
	if (top->fchild && top->fchild->artnum==artnum)
	{
		CWnd* title;
		title=top->fchild->GetDlgItem(IDJ_TITLE);
		if (title)
		{
//			TRACE0("Detected Title\n");
			CRect titlerect;
			title->GetClientRect(titlerect);
			offsety+=titlerect.Height();
		}
		//delete title;
	}
	offsetx-=homesize.left;
	offsety-=homesize.top;
	return offsetx+(offsety<<16);
}

void RDialog::OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI) 
{
	CDialog::OnGetMinMaxInfo(lpMMI);
	if (dragstate==DRAG_DIALOG)
	{
		lpMMI->ptMaxTrackSize=CPoint(maxsize.Width(),maxsize.Height());
		lpMMI->ptMinTrackSize=CPoint(minsize.Width(),minsize.Height());
	}
}

CFont* RDialog::OnGetGlobalFont(int fontnum)
{
    if (fontnum<0||fontnum>MAXFONTS)
		fontnum=0;
	if (m_scalingfactor>1.5) return g_AllFonts[fontnum][3];
	else return g_AllFonts[fontnum][0];
}

int RDialog::OnGetString(int resourceID,char* workbuffer)
{
	return AfxLoadString(resourceID,workbuffer,(UByte)workbuffer[0]);
}

BYTE* RDialog::OnGetFile(int filenum)
{
	delete m_pfileblock;
	m_pfileblock=NULL;
	if (!(filenum>0x6800 && filenum<0x7100))  //only directories 104..113
		return NULL;
	m_pfileblock=new fileblock((FileNum)filenum,PalTrans);
	return (BYTE*)getdata(m_pfileblock);
}

void RDialog::OnReleaseLastFile()
{
	delete m_pfileblock;
	m_pfileblock=NULL;
}

BOOL RDialog::OnGetX2Flag()
{
	if (m_scalingfactor>1.5) return TRUE;
	else return FALSE;
}

CDC* RDialog::OnGetOffScreenDC()
{
	return &g_OffScreenDC;
}

CRListBox* RDialog::OnGetComboListbox()
{
	if (!m_pListBox)
		m_pListBox=new CListBx;
	if (!m_pListBox->m_hWnd)
		m_pListBox->Create(CListBx::IDD,NULL);
	return (CRListBox*)m_pListBox->GetDlgItem(IDC_RLISTBOXCTRL1);
}

CListBx* RDialog::OnGetComboDialog()
{
	if (!m_pListBox)
		m_pListBox=new CListBx;
	if (!m_pListBox->m_hWnd)
		m_pListBox->Create(CListBx::IDD,NULL);
	return m_pListBox;
}

CHintBox* RDialog::OnGetHintBox()
{
	if (!m_pHintBox)
		m_pHintBox=new CHintBox;
	if (!m_pHintBox->m_hWnd)
		m_pHintBox->Create(CHintBox::IDD,this);
	return m_pHintBox;
}

void RDialog::OnPlaySound(int filenum)
{
	_Miles.UIPlaySample((FileNum)filenum);						//RJS 12Mar99
}


UWord	scalinglookup[512][2][2]=
{
	{{0x0000},{0x0000}},
	{{0x0002},{0x0002}},
	{{0x0003},{0x0003}},
	{{0x0005},{0x0005}},
	{{0x0006},{0x0007}},
	{{0x0008},{0x0008}},
	{{0x0009},{0x000A}},
	{{0x000B},{0x000B}},
	{{0x000C},{0x000D}},
	{{0x000E},{0x000F}},
	{{0x000F},{0x0010}},
	{{0x0011},{0x0012}},
	{{0x0012},{0x0014}},
	{{0x0014},{0x0015}},
	{{0x0015},{0x0017}},
	{{0x0017},{0x0018}},
	{{0x0018},{0x001A}},
	{{0x001A},{0x001C}},
	{{0x001B},{0x001D}},
	{{0x001D},{0x001F}},
	{{0x001E},{0x0021}},
	{{0x0020},{0x0022}},
	{{0x0021},{0x0024}},
	{{0x0023},{0x0025}},
	{{0x0024},{0x0027}},
	{{0x0026},{0x0029}},
	{{0x0027},{0x002A}},
	{{0x0029},{0x002C}},
	{{0x002A},{0x002E}},
	{{0x002C},{0x002F}},
	{{0x002D},{0x0031}},
	{{0x002F},{0x0032}},
	{{0x0030},{0x0034}},
	{{0x0032},{0x0036}},
	{{0x0033},{0x0037}},
	{{0x0035},{0x0039}},
	{{0x0036},{0x003B}},
	{{0x0038},{0x003C}},
	{{0x0039},{0x003E}},
	{{0x003B},{0x003F}},
	{{0x003C},{0x0041}},
	{{0x003E},{0x0043}},
	{{0x003F},{0x0044}},
	{{0x0041},{0x0046}},
	{{0x0042},{0x0048}},
	{{0x0044},{0x0049}},
	{{0x0045},{0x004B}},
	{{0x0047},{0x004C}},
	{{0x0048},{0x004E}},
	{{0x004A},{0x0050}},
	{{0x004B},{0x0051}},
	{{0x004D},{0x0053}},
	{{0x004E},{0x0055}},
	{{0x0050},{0x0056}},
	{{0x0051},{0x0058}},
	{{0x0053},{0x0059}},
	{{0x0054},{0x005B}},
	{{0x0056},{0x005D}},
	{{0x0057},{0x005E}},
	{{0x0059},{0x0060}},
	{{0x005A},{0x0062}},
	{{0x005C},{0x0063}},
	{{0x005D},{0x0065}},
	{{0x005F},{0x0066}},
	{{0x0060},{0x0068}},
	{{0x0062},{0x006A}},
	{{0x0063},{0x006B}},
	{{0x0065},{0x006D}},
	{{0x0066},{0x006F}},
	{{0x0068},{0x0070}},
	{{0x0069},{0x0072}},
	{{0x006B},{0x0073}},
	{{0x006C},{0x0075}},
	{{0x006E},{0x0077}},
	{{0x006F},{0x0078}},
	{{0x0071},{0x007A}},
	{{0x0072},{0x007C}},
	{{0x0074},{0x007D}},
	{{0x0075},{0x007F}},
	{{0x0077},{0x0080}},
	{{0x0078},{0x0082}},
	{{0x007A},{0x0084}},
	{{0x007B},{0x0085}},
	{{0x007D},{0x0087}},
	{{0x007E},{0x0089}},
	{{0x0080},{0x008A}},
	{{0x0081},{0x008C}},
	{{0x0083},{0x008D}},
	{{0x0084},{0x008F}},
	{{0x0086},{0x0091}},
	{{0x0087},{0x0092}},
	{{0x0089},{0x0094}},
	{{0x008A},{0x0096}},
	{{0x008C},{0x0097}},
	{{0x008D},{0x0099}},
	{{0x008F},{0x009A}},
	{{0x0090},{0x009C}},
	{{0x0092},{0x009E}},
	{{0x0093},{0x009F}},
	{{0x0095},{0x00A1}},
	{{0x0096},{0x00A3}},
	{{0x0098},{0x00A4}},
	{{0x0099},{0x00A6}},
	{{0x009B},{0x00A7}},
	{{0x009C},{0x00A9}},
	{{0x009E},{0x00AB}},
	{{0x009F},{0x00AC}},
	{{0x00A1},{0x00AE}},
	{{0x00A2},{0x00B0}},
	{{0x00A4},{0x00B1}},
	{{0x00A5},{0x00B3}},
	{{0x00A7},{0x00B4}},
	{{0x00A8},{0x00B6}},
	{{0x00AA},{0x00B8}},
	{{0x00AB},{0x00B9}},
	{{0x00AD},{0x00BB}},
	{{0x00AE},{0x00BD}},
	{{0x00B0},{0x00BE}},
	{{0x00B1},{0x00C0}},
	{{0x00B3},{0x00C1}},
	{{0x00B4},{0x00C3}},
	{{0x00B6},{0x00C5}},
	{{0x00B7},{0x00C6}},
	{{0x00B9},{0x00C8}},
	{{0x00BA},{0x00CA}},
	{{0x00BC},{0x00CB}},
	{{0x00BD},{0x00CD}},
	{{0x00BF},{0x00CE}},
	{{0x00C0},{0x00D0}},
	{{0x00C2},{0x00D2}},
	{{0x00C3},{0x00D3}},
	{{0x00C5},{0x00D5}},
	{{0x00C6},{0x00D7}},
	{{0x00C8},{0x00D8}},
	{{0x00C9},{0x00DA}},
	{{0x00CB},{0x00DB}},
	{{0x00CC},{0x00DD}},
	{{0x00CE},{0x00DF}},
	{{0x00CF},{0x00E0}},
	{{0x00D1},{0x00E2}},
	{{0x00D2},{0x00E4}},
	{{0x00D4},{0x00E5}},
	{{0x00D5},{0x00E7}},
	{{0x00D7},{0x00E8}},
	{{0x00D8},{0x00EA}},
	{{0x00DA},{0x00EC}},
	{{0x00DB},{0x00ED}},
	{{0x00DD},{0x00EF}},
	{{0x00DE},{0x00F1}},
	{{0x00E0},{0x00F2}},
	{{0x00E1},{0x00F4}},
	{{0x00E3},{0x00F5}},
	{{0x00E4},{0x00F7}},
	{{0x00E6},{0x00F9}},
	{{0x00E7},{0x00FA}},
	{{0x00E9},{0x00FC}},
	{{0x00EA},{0x00FE}},
	{{0x00EC},{0x00FF}},
	{{0x00ED},{0x0101}},
	{{0x00EF},{0x0102}},
	{{0x00F0},{0x0104}},
	{{0x00F2},{0x0106}},
	{{0x00F3},{0x0107}},
	{{0x00F5},{0x0109}},
	{{0x00F6},{0x010B}},
	{{0x00F8},{0x010C}},
	{{0x00F9},{0x010E}},
	{{0x00FB},{0x010F}},
	{{0x00FC},{0x0111}},
	{{0x00FE},{0x0113}},
	{{0x00FF},{0x0114}},
	{{0x0101},{0x0116}},
	{{0x0102},{0x0118}},
	{{0x0104},{0x0119}},
	{{0x0105},{0x011B}},
	{{0x0107},{0x011C}},
	{{0x0108},{0x011E}},
	{{0x010A},{0x0120}},
	{{0x010B},{0x0121}},
	{{0x010D},{0x0123}},
	{{0x010E},{0x0125}},
	{{0x0110},{0x0126}},
	{{0x0111},{0x0128}},
	{{0x0113},{0x0129}},
	{{0x0114},{0x012B}},
	{{0x0116},{0x012D}},
	{{0x0117},{0x012E}},
	{{0x0119},{0x0130}},
	{{0x011A},{0x0132}},
	{{0x011C},{0x0133}},
	{{0x011D},{0x0135}},
	{{0x011F},{0x0136}},
	{{0x0120},{0x0138}},
	{{0x0122},{0x013A}},
	{{0x0123},{0x013B}},
	{{0x0125},{0x013D}},
	{{0x0126},{0x013F}},
	{{0x0128},{0x0140}},
	{{0x0129},{0x0142}},
	{{0x012B},{0x0143}},
	{{0x012C},{0x0145}},
	{{0x012E},{0x0147}},
	{{0x012F},{0x0148}},
	{{0x0131},{0x014A}},
	{{0x0132},{0x014C}},
	{{0x0134},{0x014D}},
	{{0x0135},{0x014F}},
	{{0x0137},{0x0150}},
	{{0x0138},{0x0152}},
	{{0x013A},{0x0154}},
	{{0x013B},{0x0155}},
	{{0x013D},{0x0157}},
	{{0x013E},{0x0159}},
	{{0x0140},{0x015A}},
	{{0x0141},{0x015C}},
	{{0x0143},{0x015D}},
	{{0x0144},{0x015F}},
	{{0x0146},{0x0161}},
	{{0x0147},{0x0162}},
	{{0x0149},{0x0164}},
	{{0x014A},{0x0166}},
	{{0x014C},{0x0167}},
	{{0x014D},{0x0169}},
	{{0x014F},{0x016A}},
	{{0x0150},{0x016C}},
	{{0x0152},{0x016E}},
	{{0x0153},{0x016F}},
	{{0x0155},{0x0171}},
	{{0x0156},{0x0173}},
	{{0x0158},{0x0174}},
	{{0x0159},{0x0176}},
	{{0x015B},{0x0177}},
	{{0x015C},{0x0179}},
	{{0x015E},{0x017B}},
	{{0x015F},{0x017C}},
	{{0x0161},{0x017E}},
	{{0x0162},{0x0180}},
	{{0x0164},{0x0181}},
	{{0x0165},{0x0183}},
	{{0x0167},{0x0184}},
	{{0x0168},{0x0186}},
	{{0x016A},{0x0188}},
	{{0x016B},{0x0189}},
	{{0x016D},{0x018B}},
	{{0x016E},{0x018D}},
	{{0x0170},{0x018E}},
	{{0x0171},{0x0190}},
	{{0x0173},{0x0191}},
	{{0x0174},{0x0193}},
	{{0x0176},{0x0195}},
	{{0x0177},{0x0196}},
	{{0x0179},{0x0198}},
	{{0x017A},{0x019A}},
	{{0x017C},{0x019B}},
	{{0x017D},{0x019D}},
	{{0x017F},{0x019E}},
	{{0x0180},{0x01A0}},
	{{0x0182},{0x01A2}},
	{{0x0183},{0x01A3}},
	{{0x0185},{0x01A5}},
	{{0x0186},{0x01A7}},
	{{0x0188},{0x01A8}},
	{{0x0189},{0x01AA}},
	{{0x018B},{0x01AB}},
	{{0x018C},{0x01AD}},
	{{0x018E},{0x01AF}},
	{{0x018F},{0x01B0}},
	{{0x0191},{0x01B2}},
	{{0x0192},{0x01B4}},
	{{0x0194},{0x01B5}},
	{{0x0195},{0x01B7}},
	{{0x0197},{0x01B8}},
	{{0x0198},{0x01BA}},
	{{0x019A},{0x01BC}},
	{{0x019B},{0x01BD}},
	{{0x019D},{0x01BF}},
	{{0x019E},{0x01C1}},
	{{0x01A0},{0x01C2}},
	{{0x01A1},{0x01C4}},
	{{0x01A3},{0x01C5}},
	{{0x01A4},{0x01C7}},
	{{0x01A6},{0x01C9}},
	{{0x01A7},{0x01CA}},
	{{0x01A9},{0x01CC}},
	{{0x01AA},{0x01CE}},
	{{0x01AC},{0x01CF}},
	{{0x01AD},{0x01D1}},
	{{0x01AF},{0x01D2}},
	{{0x01B0},{0x01D4}},
	{{0x01B2},{0x01D6}},
	{{0x01B3},{0x01D7}},
	{{0x01B5},{0x01D9}},
	{{0x01B6},{0x01DB}},
	{{0x01B8},{0x01DC}},
	{{0x01B9},{0x01DE}},
	{{0x01BB},{0x01DF}},
	{{0x01BC},{0x01E1}},
	{{0x01BE},{0x01E3}},
	{{0x01BF},{0x01E4}},
	{{0x01C1},{0x01E6}},
	{{0x01C2},{0x01E8}},
	{{0x01C4},{0x01E9}},
	{{0x01C5},{0x01EB}},
	{{0x01C7},{0x01EC}},
	{{0x01C8},{0x01EE}},
	{{0x01CA},{0x01F0}},
	{{0x01CB},{0x01F1}},
	{{0x01CD},{0x01F3}},
	{{0x01CE},{0x01F5}},
	{{0x01D0},{0x01F6}},
	{{0x01D1},{0x01F8}},
	{{0x01D3},{0x01F9}},
	{{0x01D4},{0x01FB}},
	{{0x01D6},{0x01FD}},
	{{0x01D7},{0x01FE}},
	{{0x01D9},{0x0200}},
	{{0x01DA},{0x0202}},
	{{0x01DC},{0x0203}},
	{{0x01DD},{0x0205}},
	{{0x01DF},{0x0206}},
	{{0x01E0},{0x0208}},
	{{0x01E2},{0x020A}},
	{{0x01E3},{0x020B}},
	{{0x01E5},{0x020D}},
	{{0x01E6},{0x020F}},
	{{0x01E8},{0x0210}},
	{{0x01E9},{0x0212}},
	{{0x01EB},{0x0213}},
	{{0x01EC},{0x0215}},
	{{0x01EE},{0x0217}},
	{{0x01EF},{0x0218}},
	{{0x01F1},{0x021A}},
	{{0x01F2},{0x021C}},
	{{0x01F4},{0x021D}},
	{{0x01F5},{0x021F}},
	{{0x01F7},{0x0220}},
	{{0x01F8},{0x0222}},
	{{0x01FA},{0x0224}},
	{{0x01FB},{0x0225}},
	{{0x01FD},{0x0227}},
	{{0x01FE},{0x0229}},
	{{0x0200},{0x022A}},
	{{0x0201},{0x022C}},
	{{0x0203},{0x022D}},
	{{0x0204},{0x022F}},
	{{0x0206},{0x0231}},
	{{0x0207},{0x0232}},
	{{0x0209},{0x0234}},
	{{0x020A},{0x0236}},
	{{0x020C},{0x0237}},
	{{0x020D},{0x0239}},
	{{0x020F},{0x023A}},
	{{0x0210},{0x023C}},
	{{0x0212},{0x023E}},
	{{0x0213},{0x023F}},
	{{0x0215},{0x0241}},
	{{0x0216},{0x0243}},
	{{0x0218},{0x0244}},
	{{0x0219},{0x0246}},
	{{0x021B},{0x0247}},
	{{0x021C},{0x0249}},
	{{0x021E},{0x024B}},
	{{0x021F},{0x024C}},
	{{0x0221},{0x024E}},
	{{0x0222},{0x0250}},
	{{0x0224},{0x0251}},
	{{0x0225},{0x0253}},
	{{0x0227},{0x0254}},
	{{0x0228},{0x0256}},
	{{0x022A},{0x0258}},
	{{0x022B},{0x0259}},
	{{0x022D},{0x025B}},
	{{0x022E},{0x025D}},
	{{0x0230},{0x025E}},
	{{0x0231},{0x0260}},
	{{0x0233},{0x0261}},
	{{0x0234},{0x0263}},
	{{0x0236},{0x0265}},
	{{0x0237},{0x0266}},
	{{0x0239},{0x0268}},
	{{0x023A},{0x026A}},
	{{0x023C},{0x026B}},
	{{0x023D},{0x026D}},
	{{0x023F},{0x026E}},
	{{0x0240},{0x0270}},
	{{0x0242},{0x0272}},
	{{0x0243},{0x0273}},
	{{0x0245},{0x0275}},
	{{0x0246},{0x0277}},
	{{0x0248},{0x0278}},
	{{0x0249},{0x027A}},
	{{0x024B},{0x027B}},
	{{0x024C},{0x027D}},
	{{0x024E},{0x027F}},
	{{0x024F},{0x0280}},
	{{0x0251},{0x0282}},
	{{0x0252},{0x0284}},
	{{0x0254},{0x0285}},
	{{0x0255},{0x0287}},
	{{0x0257},{0x0288}},
	{{0x0258},{0x028A}},
	{{0x025A},{0x028C}},
	{{0x025B},{0x028D}},
	{{0x025D},{0x028F}},
	{{0x025E},{0x0291}},
	{{0x0260},{0x0292}},
	{{0x0261},{0x0294}},
	{{0x0263},{0x0295}},
	{{0x0264},{0x0297}},
	{{0x0266},{0x0299}},
	{{0x0267},{0x029A}},
	{{0x0269},{0x029C}},
	{{0x026A},{0x029E}},
	{{0x026C},{0x029F}},
	{{0x026D},{0x02A1}},
	{{0x026F},{0x02A2}},
	{{0x0270},{0x02A4}},
	{{0x0272},{0x02A6}},
	{{0x0273},{0x02A7}},
	{{0x0275},{0x02A9}},
	{{0x0276},{0x02AB}},
	{{0x0278},{0x02AC}},
	{{0x0279},{0x02AE}},
	{{0x027B},{0x02AF}},
	{{0x027C},{0x02B1}},
	{{0x027E},{0x02B3}},
	{{0x027F},{0x02B4}},
	{{0x0281},{0x02B6}},
	{{0x0282},{0x02B8}},
	{{0x0284},{0x02B9}},
	{{0x0285},{0x02BB}},
	{{0x0287},{0x02BC}},
	{{0x0288},{0x02BE}},
	{{0x028A},{0x02C0}},
	{{0x028B},{0x02C1}},
	{{0x028D},{0x02C3}},
	{{0x028E},{0x02C5}},
	{{0x0290},{0x02C6}},
	{{0x0291},{0x02C8}},
	{{0x0293},{0x02C9}},
	{{0x0294},{0x02CB}},
	{{0x0296},{0x02CD}},
	{{0x0297},{0x02CE}},
	{{0x0299},{0x02D0}},
	{{0x029A},{0x02D2}},
	{{0x029C},{0x02D3}},
	{{0x029D},{0x02D5}},
	{{0x029F},{0x02D6}},
	{{0x02A0},{0x02D8}},
	{{0x02A2},{0x02DA}},
	{{0x02A3},{0x02DB}},
	{{0x02A5},{0x02DD}},
	{{0x02A6},{0x02DF}},
	{{0x02A8},{0x02E0}},
	{{0x02A9},{0x02E2}},
	{{0x02AB},{0x02E3}},
	{{0x02AC},{0x02E5}},
	{{0x02AE},{0x02E7}},
	{{0x02AF},{0x02E8}},
	{{0x02B1},{0x02EA}},
	{{0x02B2},{0x02EC}},
	{{0x02B4},{0x02ED}},
	{{0x02B5},{0x02EF}},
	{{0x02B7},{0x02F0}},
	{{0x02B8},{0x02F2}},
	{{0x02BA},{0x02F4}},
	{{0x02BB},{0x02F5}},
	{{0x02BD},{0x02F7}},
	{{0x02BE},{0x02F9}},
	{{0x02C0},{0x02FA}},
	{{0x02C1},{0x02FC}},
	{{0x02C3},{0x02FD}},
	{{0x02C4},{0x02FF}},
	{{0x02C6},{0x0301}},
	{{0x02C7},{0x0302}},
	{{0x02C9},{0x0304}},
	{{0x02CA},{0x0306}},
	{{0x02CC},{0x0307}},
	{{0x02CD},{0x0309}},
	{{0x02CF},{0x030A}},
	{{0x02D0},{0x030C}},
	{{0x02D2},{0x030E}},
	{{0x02D3},{0x030F}},
	{{0x02D5},{0x0311}},
	{{0x02D6},{0x0313}},
	{{0x02D8},{0x0314}},
	{{0x02D9},{0x0316}},
	{{0x02DB},{0x0317}},
	{{0x02DC},{0x0319}},
	{{0x02DE},{0x031B}},
	{{0x02DF},{0x031C}},
	{{0x02E1},{0x031E}},
	{{0x02E2},{0x0320}},
	{{0x02E4},{0x0321}},
	{{0x02E5},{0x0323}},
	{{0x02E7},{0x0324}},
	{{0x02E8},{0x0326}},
	{{0x02EA},{0x0328}},
	{{0x02EB},{0x0329}},
	{{0x02ED},{0x032B}},
	{{0x02EE},{0x032D}},
	{{0x02F0},{0x032E}},
	{{0x02F1},{0x0330}},
	{{0x02F3},{0x0331}},
	{{0x02F4},{0x0333}},
	{{0x02F6},{0x0335}},
	{{0x02F7},{0x0336}},
	{{0x02F9},{0x0338}},
	{{0x02FA},{0x033A}},
	{{0x02FC},{0x033B}},
	{{0x02FD},{0x033D}},
	{{0x02FF},{0x033E}}
};
void RDialog::UpdateTitle()
{
	CWnd* title;
	CRect rect;
	title=GetDlgItem(IDJ_TITLE);
	if (title)
	{
		title->GetClientRect(rect);
		title->MoveWindow(CRect(viewsize.left,-homesize.top,viewsize.right-currscrw+4*(currscrw>0),-homesize.top+rect.Height()));
	}
	//delete title;
}

int	ScaleTranslate(int input,bool isy)
{
	int	high=511,low=0,mid=256,currval=scalinglookup[mid][isy][1];
	if (input>scalinglookup[high][isy][1])
	{
		return (input*scalinglookup[high][isy][0]/scalinglookup[high][isy][1]);
	}
	while (high-low>1)
	{
		if (currval>input)
			high=mid;
		else
		if (currval<input)
			low=mid;
		else
			break;
		mid=(high+low)/2;
		currval=scalinglookup[mid][isy][1];
	}
	if (currval==input)
		return(scalinglookup[mid][isy][0]);			//found exact match
	else
		if (currval==scalinglookup[high][isy][1])
			return scalinglookup[high][isy][0];		//found exact match
		if (currval+1==scalinglookup[high][isy][1])
			return scalinglookup[high][isy][0]-1;		//just under
		else
			if (currval==scalinglookup[low][isy][1]+1)
				return scalinglookup[low][isy][0]+1;	//just over
			else
			if (currval==scalinglookup[low][isy][1])
				return scalinglookup[low][isy][0];	//found exact match
			else
				return scalinglookup[low][isy][0];	//couldn't find near match!
}

int	RDialog::GetFontScaling()
{
//	int rv=GetDialogBaseUnits();
//	return rv*4;
	return 97;
		 
}
void RDialog::ScaleDialog(float factor)
{
	if (!scalinglookup[1][0][1])
		for (int x=0;x<512;x++)
		{
			RECT baseunits={0,0,x,x};
			MapDialogRect(&baseunits);
			scalinglookup[x][0][1]=baseunits.right;
			scalinglookup[x][1][1]=baseunits.bottom;
		}
	// sets the scale of the dialog to this factor.  Useful for
	// negating the FontSize system metric and changing the
	// dialog size at different resolutions as required in the
	// front end.  Watch out for rounding errors mounting up
	// particularly if you go to a very small scale.
	if (m_scalingfactor!=1.0/* && m_scalingfactor!=2.0*/  && scalinglookup[511][0][1]!=scalinglookup[511][0][0])
	{
		m_scalingfactor=factor;
		CRect rect;
		CRect parentrect;
		CWnd* pControl;
		pControl=GetTopWindow();
			Invalidate();
		GetClientRect(parentrect);
		ClientToScreen(parentrect);
		while (pControl)
		{
			// find coords relative to parent window...
			// why they dont have a ClientToParent function I dont know
			pControl->GetWindowRect(rect);
			rect-=parentrect.TopLeft();
//			int id=pControl->GetDlgCtrlID();
	//		if (id>=IDJ_PANEL0 && id<=IDJ_PANEL1)
	//		{
	//			rect.right=rect.left*xfactor+rect.Width();
	//			rect.bottom=rect.top*yfactor+rect.Height();
	//		}
	//		else
			{
				rect.right=ScaleTranslate(rect.right,false);
				rect.bottom=ScaleTranslate(rect.bottom,true);
			}
			rect.left=ScaleTranslate(rect.left,false);
			rect.top=ScaleTranslate(rect.top,true);
			pControl->MoveWindow(rect);
			pControl=pControl->GetNextWindow();
		}
		// size the actual dialog
		RECT_NORMAL.right=	RECT_NORMAL.left+	ScaleTranslate(RECT_NORMAL.Width(),false);
		RECT_NORMAL.bottom=	RECT_NORMAL.top+	ScaleTranslate(RECT_NORMAL.Height(),true);
		homesize.right=		homesize.left+	ScaleTranslate(homesize.Width(),false);
		homesize.bottom=	homesize.top+	ScaleTranslate(homesize.Height(),true);
		GetWindowRect(rect);
		GetParent()->GetClientRect(parentrect);
		GetParent()->ClientToScreen(parentrect);

		rect-=parentrect.TopLeft();
		rect.right=		rect.left+ScaleTranslate(rect.Width(),false);
		rect.bottom=	rect.top+ScaleTranslate(rect.Height(),true);
		MoveWindow(rect.left,rect.top,rect.Width(),rect.Height());
		viewsize=		rect;
	}
	else
//TEMPCODE JIM 18/08/99 	if (factor!=m_scalingfactor)
//TEMPCODE JIM 18/08/99 	{	INT3;
//TEMPCODE JIM 18/08/99 		float divfact=factor/m_scalingfactor;
//TEMPCODE JIM 18/08/99 		m_scalingfactor=factor;
//TEMPCODE JIM 18/08/99 		CRect rect;
//TEMPCODE JIM 18/08/99 		CRect parentrect;
//TEMPCODE JIM 18/08/99 		CWnd* pControl;
//TEMPCODE JIM 18/08/99 		pControl=GetTopWindow();
//TEMPCODE JIM 18/08/99 			Invalidate();
//TEMPCODE JIM 18/08/99 		GetClientRect(parentrect);
//TEMPCODE JIM 18/08/99 		ClientToScreen(parentrect);
//TEMPCODE JIM 18/08/99 		while (pControl)
//TEMPCODE JIM 18/08/99 		{
//TEMPCODE JIM 18/08/99 			// find coords relative to parent window...
//TEMPCODE JIM 18/08/99 			// why they dont have a ClientToParent function I dont know
//TEMPCODE JIM 18/08/99 			pControl->GetWindowRect(rect);
//TEMPCODE JIM 18/08/99 			rect-=parentrect.TopLeft();
//TEMPCODE JIM 18/08/99 //			int id=pControl->GetDlgCtrlID();
//TEMPCODE JIM 18/08/99 	//		if (id>=IDJ_PANEL0 && id<=IDJ_PANEL1)
//TEMPCODE JIM 18/08/99 	//		{
//TEMPCODE JIM 18/08/99 	//			rect.right=rect.left*xfactor+rect.Width();
//TEMPCODE JIM 18/08/99 	//			rect.bottom=rect.top*yfactor+rect.Height();
//TEMPCODE JIM 18/08/99 	//		}
//TEMPCODE JIM 18/08/99 	//		else
//TEMPCODE JIM 18/08/99 			{
//TEMPCODE JIM 18/08/99 				rect.right*=divfact;
//TEMPCODE JIM 18/08/99 				rect.bottom*=divfact;
//TEMPCODE JIM 18/08/99 			}
//TEMPCODE JIM 18/08/99 			rect.left*=divfact;
//TEMPCODE JIM 18/08/99 			rect.top*=divfact;
//TEMPCODE JIM 18/08/99 			pControl->MoveWindow(rect);
//TEMPCODE JIM 18/08/99 			pControl=pControl->GetNextWindow();
//TEMPCODE JIM 18/08/99 		}
//TEMPCODE JIM 18/08/99 		// size the actual dialog
//TEMPCODE JIM 18/08/99 		GetWindowRect(rect);
//TEMPCODE JIM 18/08/99 		GetParent()->GetClientRect(parentrect);
//TEMPCODE JIM 18/08/99 		GetParent()->ClientToScreen(parentrect);
//TEMPCODE JIM 18/08/99 		rect-=parentrect.TopLeft();
//TEMPCODE JIM 18/08/99 		MoveWindow(rect.left,rect.top,rect.Width()*divfact,rect.Width()*divfact);
//TEMPCODE JIM 18/08/99 
//TEMPCODE JIM 18/08/99 		RECT_NORMAL.right=	RECT_NORMAL.left+	RECT_NORMAL.Width()*divfact;
//TEMPCODE JIM 18/08/99 		RECT_NORMAL.bottom=	RECT_NORMAL.top+	RECT_NORMAL.Height()*divfact;
//TEMPCODE JIM 18/08/99 		homesize.right=		homesize.left+	homesize.Width()*divfact;
//TEMPCODE JIM 18/08/99 		homesize.bottom=	homesize.top+	homesize.Height()*divfact;
//TEMPCODE JIM 18/08/99 	}
//TEMPCODE JIM 18/08/99 	else
	{
		CRect rect,parentrect;
		GetWindowRect(rect);
		GetParent()->GetClientRect(parentrect);
		GetParent()->ClientToScreen(parentrect);

		rect-=parentrect.TopLeft();
		MoveWindow(rect.left,rect.top,rect.Width(),rect.Height());
		viewsize=		rect;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Create
//Author		Jim Taylor
//Date			Thu 10 Jun 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
/*BOOL RDialog::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext) //JIM 10Jun99:UPDATED IN PC:
{
	if (CDialog::Create(IDD, pParentWnd) == FALSE)
		return FALSE;
	m_scalingfactor=(float)fontdpi/96;
	ScaleDialog(1);
	return TRUE;
}
*/

void RDialog::PreDestroyPanel()
{
}

int RDialog::RMessageBox(UINT TitleID, UINT MessageID, UINT Button0ID, UINT Button1ID, UINT Button2ID, FileNum art)
{
	if (!m_pMessageBox)
		m_pMessageBox=new RMdlDlg;
	m_pMessageBox->m_TitleID=TitleID;
	m_pMessageBox->m_MessageID=MessageID;
	m_pMessageBox->m_Button0ID=Button0ID;
	m_pMessageBox->m_Button1ID=Button1ID;
	m_pMessageBox->m_Button2ID=Button2ID;
	if (art)
		m_pMessageBox->m_artnum=art;
	else
		m_pMessageBox->m_artnum=FIL_MAP_ARMY;
	OnPlaySound(FIL_SFX_OFFICE_CLANG);							//RDH 12Apr99
//Disable tool bars
#ifndef	MIG_DEMO_VER
	CMainFrame* main=(CMainFrame*)AfxGetMainWnd();
	main->m_titlebar.EnableWindow(FALSE);
	main->m_toolbar1.EnableWindow(FALSE);
	main->m_toolbar2.EnableWindow(FALSE);
	main->m_toolbar3.EnableWindow(FALSE);
	main->m_toolbar4.EnableWindow(FALSE);
	main->m_toolbar5.EnableWindow(FALSE);
	if (main->m_wndSystemBox)
		main->m_wndSystemBox->InDialAncestor()->EnableWindow(FALSE);
#endif #ifndef	MIG_DEMO_VER


	int retval= m_pMessageBox->DoModal();
//Enable tool bars
#ifndef	MIG_DEMO_VER
	main->m_titlebar.EnableWindow(TRUE);
	main->m_toolbar1.EnableWindow(TRUE);
	main->m_toolbar2.EnableWindow(TRUE);
	main->m_toolbar3.EnableWindow(TRUE);
	main->m_toolbar4.EnableWindow(TRUE);
	main->m_toolbar5.EnableWindow(TRUE);
	if (main->m_wndSystemBox)
		main->m_wndSystemBox->InDialAncestor()->EnableWindow(TRUE);
#endif #ifndef	MIG_DEMO_VER
	return retval;

}

LRESULT RDialog::OnCommandHelp(WPARAM w, LPARAM lParam)
{
	CMainFrame* main=(CMainFrame*)AfxGetMainWnd();
	if ((main->disablehelp&1)==0)					//assume every panel has context help
		return CDialog::OnCommandHelp(w,lParam);

	if (MY_IID == IDD_FOOTAGE)
	  return (1);

	if (parent)
		if (
				parent->MY_IID==IDD_EMPTYDIAL
//DEADCODE RDH 24/02/99 			||	
//DEADCODE RDH 24/02/99 			parent->MY_IID==IDD_FULLPANE
			)
			return CDialog::OnCommandHelp(w,lParam);
		else
			return parent->OnCommandHelp(w,lParam);
	else
		return CDialog::OnCommandHelp(w,lParam);
}



LRESULT RDialog::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CDialog::WindowProc(message, wParam, lParam);
}
LRESULT RDialog::OnRegisteredMouseWheel( WPARAM wParam, LPARAM lParam )
{
	return CDialog::OnRegisteredMouseWheel(wParam,lParam );
}
