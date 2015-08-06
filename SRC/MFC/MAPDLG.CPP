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

// MapDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MIG.h"
#include "MapDlg.h"
#include "messages.h"
#include "fileman.h"
#include "MIGView.h"
#include "node.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#ifndef	THIS_FILE_DEFINED
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif

/////////////////////////////////////////////////////////////////////////////
// CMapDlg dialog

CMapDlg::CMapDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMapDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMapDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_LButtonDown=FALSE;
	m_buttonid=0;
	m_hintid=0;
	TargetSelectSink=NULL;
}


void CMapDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMapDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMapDlg, CDialog)
	//{{AFX_MSG_MAP(CMapDlg)
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_TIMER()
	ON_WM_DESTROY()
//	ON_WM_MOUSEWHEEL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMapDlg message handlers

/* Attempt to create a template

BOOL CMapDlg::Create(CWnd * pParentWnd)
{
	int	nItems=1;
	
	int	nBufferSize;

	nBufferSize = sizeof(DLGTEMPLATE) + 6 + nItems * (sizeof(DLGITEMTEMPLATE) + 10);

	unsigned char * pBuffer = new unsigned char [nBufferSize];

	DLGTEMPLATE*	lpTmplt = (DLGTEMPLATE*)pBuffer;

	lpTmplt->style = WS_CHILD | WS_CAPTION;
	lpTmplt->dwExtendedStyle = 0;
	lpTmplt->cdit = nItems;
	lpTmplt->x = 0;
	lpTmplt->y = 0;
	lpTmplt->cx = 100;
	lpTmplt->cy = 100;

	WORD * lpZeros = (WORD*)(pBuffer+sizeof(DLGTEMPLATE));

	lpZeros[0] = lpZeros[1] = lpZeros[2] = 0;

	DLGITEMTEMPLATE * lpDIT;

	lpDIT = (DLGITEMTEMPLATE *)&lpZeros[3];

	lpDIT->style = BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE;
	lpDIT->dwExtendedStyle = 0;
	lpDIT->x = 50;
	lpDIT->y = 50;
	lpDIT->cx = 15;
	lpDIT->cy = 15;
	lpDIT->id = IDC_BUTTON1;
	
//	lpDit = (DLGITEMTEMPLATE*)((unsigned char *)lpDIT+10);

	WORD * lpMoreZeros = (WORD*)((unsigned char *)lpDIT+sizeof(DLGTEMPLATE));
	lpMoreZeros[0] = 0xFFFF;
	lpMoreZeros[1] = 0x0080;
	lpMoreZeros[2] = lpMoreZeros[3] = lpMoreZeros[4] = 0x0000;

	ASSERT( CreateIndirect(lpTmplt, pParentWnd));
	return TRUE;

}
*/

void CMapDlg::OnClickItem(int m_buttonid)
{
#ifndef	MIG_DEMO_VER

//	RDialog::MakeTopDialog(CRect(100,100,0,0),
//		DialList(DialBox(FIL_NULL,
	typedef	HideEdgeControl::EdgeCtrl	Edge;
	typedef	HideEdgeControl	EDGE;
	_Miles.UIPlaySample(FIL_SFX_OFFICE_PAPER3);					//RDH 12Apr99
//DeadCode RJS 12Mar99 	_Miles.ProcessInterfaceSpot();		//RJS 17Nov98				  //RDH 03/03/99

	if (TargetSelectSink)
	{
		CMainFrame* main=(CMainFrame*)AfxGetMainWnd();
		Save_Data.mapfilters |= FILT_MAINWP;
		Save_Data.mapfilters |= FILT_SUBWP;
		main->m_toolbar1.SetFiltersFromSaveGame();
		Invalidate();

		TargetSelectSink->RefreshData(m_buttonid);
	}
	else
	if (m_buttonid>=WayPointBAND && m_buttonid<WayPointBANDEND)
	{
		int pack, wave, g;
		if (Profile::GetPackageFromWP((UniqueID)m_buttonid, pack, wave, g))
		{
//DEADCODE RDH 19/03/99 			RDialog::m_pView->SetHiLightInfo(pack,  wave, g, (UniqueID)m_buttonid);

			//we need to reset the highlight before opening dialogue
			//so that correct wp info is shown
			if (!MMC.indebrief)										  //RDH 24/06/99
			{
				RDialog::m_pView->SetHiLightInfo(pack,  wave, g, (UniqueID)m_buttonid); //RDH 25/03/99
				CMissionFolder::Make();
				CMissionFolder::OpenOneProfile(pack);
			}
//DEADCODE RDH 25/03/99 			RDialog::m_pView->SetHiLightInfo(pack,  wave, g, (UniqueID)m_buttonid); //RDH 19/03/99
//			CProfile* p;
//			RDialog::MakeTopDialog(CRect(50,450,0,0),
//				DialBox(FIL_MAP_PROFILE,p=new CProfile(true, pack))//,Edges(EDGE::ALIGN_MIN + EDGE::ACTIONS_SPLITTER,EDGE::ALIGN_MIN,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE))
//				);
//			p->SetWaveTabs(wave, true, -1);
		}

	}else
	{
		Invalidate();
		MainToolBar().OpenDossier((UniqueID)m_buttonid);
//		CTargetDossier::MakeSheet(CRect(180,180,0,0),(UniqueID)m_buttonid);
	}
#endif #ifndef	MIG_DEMO_VER

}

void CMapDlg::OnDragItem(int m_buttonid)
{
#ifndef	MIG_DEMO_VER

//	RDialog::MakeTopDialog(CRect(100,100,0,0),
//		DialList(DialBox(FIL_NULL,
	ItemBasePtr p=Persons2::ConvertPtrUID(UniqueID(m_buttonid));
	switch (p->Status.size)
	{
	case WAYPOINTSIZE:
		{
			int pack, wave, g;
			if (Profile::GetPackageFromWP((UniqueID)m_buttonid, pack, wave, g))
			{
				info_waypoint* w=*p;
				if (w->World.X<METRES250KM)								w->World.X=METRES250KM;
				if (w->World.X>METRES500KM+METRES500KM-METRES20KM)		w->World.X=METRES500KM+METRES500KM-METRES20KM;
				if (w->World.Z<METRES100KM+METRES20KM)					w->World.Z=METRES100KM+METRES20KM;
				if (w->World.Z>METRES500KM+METRES500KM+METRES150KM)		w->World.Z=METRES500KM+METRES500KM+METRES150KM;

				Coords3D c=w->World;
				Todays_Packages[pack].SetTargetGlobrefs();			  //JIM 16/03/99
				Todays_Packages[pack].RecalcPrimaryPositions();		  //JIM 16/03/99
				if (wave)
					Todays_Packages[pack].RecalcSecondaryPositions(wave);
				if (w->target.Evaluate()!=ENABLE_COMPLEX_VAL)
					c-=Persons2::ConvertPtrUID(UniqueID(w->target.Evaluate()));
				Todays_Packages[pack].SetTargetGlobrefs();
				Todays_Packages[pack].RecalcPrimaryPositions();
				w->position.RecalcDeltasToMatch(c);
				if (!wave)
					Todays_Packages[pack].RecalcRoutePositions();
				else
					Todays_Packages[pack].RecalcSecondaryPositions(wave);
				int fuel;
				Invalidate();										  //JIM 16/03/99

				Todays_Packages[pack].CalcWPTimes(wave);
				if (w->applygroup==ENABLE_COMPLEX_VAL)
				{
					for (g = 0; g < 3; g++)
					{
						info_airgrp* ag;
						ag=*Persons2::ConvertPtrUID(Todays_Packages[pack][wave][g].uid);
						if (ag)
							if (!(Todays_Packages[pack].CalcFuel(wave,g,UID_NULL, fuel)))
								RDialog::RMessageBox(IDS_BINGOWARNINGTITLE, IDS_BINGOWARNING,NULL,IDS_OK);
					}
				}else if (!(Todays_Packages[pack].CalcFuel(wave,w->applygroup,UID_NULL, fuel)))
								RDialog::RMessageBox(IDS_BINGOWARNINGTITLE, IDS_BINGOWARNING,NULL,IDS_OK);
				if (CProfile::wavetabs)
				{
					CMissionFolder::Make();
					CMissionFolder::OpenOneProfile(pack);
				}
			}
		}
	break;
	}
#endif #ifndef	MIG_DEMO_VER

//	typedef	HideEdgeControl::EdgeCtrl	Edge;
//	typedef	HideEdgeControl	EDGE;
//	CTargetDossier::MakeSheet(CRect(180,180,0,0),(UniqueID)m_buttonid);
}

bool CMapDlg::AllowDragItem(int m_buttonid)
{
//	RDialog::MakeTopDialog(CRect(100,100,0,0),
//		DialList(DialBox(FIL_NULL,
	if (TargetSelectSink)
		return false;
	return (m_buttonid>=WayPointBAND && m_buttonid<WayPointBANDEND);
}



BOOL CMapDlg::OnEraseBkgnd(CDC* pDC) 
{
//	CRect rect;
//	pDC->GetBoundsRect(&rect,NULL);
//	if (rect.Width()<30 && rect.Height()<30) return TRUE;
	RDialog::m_pView->UpdateBitmaps(pDC);
	return TRUE;
}

/*void CMapDlg::OnPaint() 
{
	PAINTSTRUCT paintstruct;
	CDC* pDC;
	pDC=this->BeginPaint(&paintstruct);
	this->EndPaint(&paintstruct);
}
*/

void	CMapDlg::InvalidateIcon(int px,int py)
{
		InvalidateRect(CRect(px-RDialog::m_pView->m_iconradius-1,py-RDialog::m_pView->m_iconradius-1,px+RDialog::m_pView->m_iconradius+1,py+RDialog::m_pView->m_iconradius+1));
}
void	CMapDlg::InvalidateDragIcon(int ox,int oy,int px,int py)
{	//waypoint is somewhere in there...
		px=min(ox,px);
		py=min(oy,py);
		InvalidateRect(CRect(px-RDialog::m_pView->m_iconradius*2,py-RDialog::m_pView->m_iconradius*2,px+RDialog::m_pView->m_iconradius*2,py+RDialog::m_pView->m_iconradius*2));
}
void	CMapDlg::InvalidateIconText(CDC* pDC,int px,int py,CString s)
{
	CSize size=pDC->GetTextExtent(s);
	InvalidateRect(CRect(px+RDialog::m_pView->m_iconradius,py-RDialog::m_pView->m_iconradius+1,px+RDialog::m_pView->m_iconradius+1+size.cx,py-RDialog::m_pView->m_iconradius+1+size.cy+2));
}

int	CMapDlg::FindMapItem(CPoint point)
{
	int	m_hintid=0;
	int	mwx,mwy;													  //JIM 16/02/99
//	int mwx=		65536*384 +((point.x+RDialog::m_pView->m_scrollpoint.x)*65536)/RDialog::m_pView->m_zoom; //JIM 16/02/99
//	int mwy=		65536*1792-((point.y+RDialog::m_pView->m_scrollpoint.y)*65536)/RDialog::m_pView->m_zoom; //JIM 16/02/99
	int worldicon=RDialog::m_pView->WorldXY(mwx,mwy,point.x,point.y);//m_iconradius*65536/RDialog::m_pView->m_zoom; //JIM 16/02/99
	int mwl=mwx-worldicon;
	int	mwr=mwx+worldicon;
	int	mwt=mwy+worldicon;
	int	mwb=mwy-worldicon;
	UniqueIDField redUIDs;
	SupplyTree::FillNatForUID(redUIDs);
	FileNum  FL_Icon[AmberBattleNodeBANDEND-AmberBattleNodeBAND];
	SupplyTree::FillFLS_Icons(FL_Icon);

	ItemBasePtr p;
	FileNum  f;
	for (int i=UID_Null;i<WayPointBAND;i++)
	{
		p=Persons2::ConvertPtrUID(UniqueID(i));
		if (p)
		{
			f = RDialog::m_pView->DrawIconTest(p, UniqueID(i), false,redUIDs,FL_Icon);
			if (f)
				if (	p->World.X>mwl && p->World.X<mwr &&	p->World.Z>mwb && p->World.Z<mwt )
					m_hintid=i;
		}
	}
	for (i=WayPointBAND;i<WayPointBANDEND;i++)
	{
		p=Persons2::ConvertPtrUID(UniqueID(i));
		if (p)
		{
			f = RDialog::m_pView->DrawIconTest(p, UniqueID(i), false,redUIDs,FL_Icon);
			if (f)
			{
				int wx=p->World.X;
				int wz=p->World.Z;
				SWord s,c;
				UWord ang=(i-WayPointBAND)*ANGLES_50Deg;
				Math_Lib.sin_cos((Angles)ang,s,c);
				wx+=MULSHSIN(s,worldicon,15);
				wz-=MULSHSIN(c,worldicon,15);
				if (	wx>mwl && wx<mwr &&	wz>mwb && wz<mwt )
					m_hintid=i;
			}
		}
	}
	for (i=WayPointBANDEND;i<IllegalSepID;i++)
	{
		p=Persons2::ConvertPtrUID(UniqueID(i));
		if (p)
		{
			f = RDialog::m_pView->DrawIconTest(p, UniqueID(i), false,redUIDs,FL_Icon);
			if (f)
				if (	p->World.X>mwl && p->World.X<mwr &&	p->World.Z>mwb && p->World.Z<mwt )
					m_hintid=i;
		}
	}
	return m_hintid;
}
void CMapDlg::ResetIcon(UniqueID wpuid)
{
	int	oldbuttonid = m_buttonid;
	m_buttonid = wpuid;
	RedrawIcon(oldbuttonid);
}
void CMapDlg::RedrawIcon(int oldbuttonid)
{// doing 2 invalidaterects here removes the very slight flicker...

	ItemBasePtr p;
	int px,py;
	if (m_buttonid)
	{
		p=Persons2::ConvertPtrUID(UniqueID(m_buttonid));
		if (p)
		{
			RDialog::m_pView->ScreenXY(p,px,py,-RDialog::m_pView->m_scrollpoint.x,-RDialog::m_pView->m_scrollpoint.y);
			InvalidateIcon(px,py);

		}
		else m_buttonid=UID_NULL;									  //DAW 07/05/99

	}
	if (oldbuttonid)
	{
		p=Persons2::ConvertPtrUID(UniqueID(oldbuttonid));
		if (p)
		{
			RDialog::m_pView->ScreenXY(p,px,py,-RDialog::m_pView->m_scrollpoint.x,-RDialog::m_pView->m_scrollpoint.y);
			InvalidateIcon(px,py);
		}
		else
			oldbuttonid=UID_NULL;									  //DAW 07/05/99
	}
}
void CMapDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	m_LButtonDown=TRUE;
	m_bDragging=FALSE;
	m_point=point;
	
	int oldbuttonid=m_buttonid;
	m_buttonid=NULL;
	m_buttonid=FindMapItem(point);
	if (m_buttonid == NULL)										//RDH 17Jun99
		m_buttonid = oldbuttonid;								//RDH 17Jun99
	RedrawIcon(oldbuttonid);
	CDialog::OnLButtonDown(nFlags, point);
}


void CMapDlg::OnMouseMove(UINT nFlags, CPoint point) 
{
	RDialog::m_pView->m_popupPoint=point;
	int px,py;
	ItemBasePtr p;
	CDC* pDC=GetDC();
	if (m_LButtonDown && !m_bDragging && m_buttonid)
	{
		if (!CRect(m_point.x-3,m_point.y-3,m_point.x+3,m_point.y+3).PtInRect(point))
			if (FindMapItem(m_point) && AllowDragItem(m_buttonid))
		{
			m_bDragging=TRUE;
			SetCapture();
			p=Persons2::ConvertPtrUID(UniqueID(m_buttonid));
			RDialog::m_pView->ScreenXY(p,px,py,-RDialog::m_pView->m_scrollpoint.x,-RDialog::m_pView->m_scrollpoint.y);
			m_point.x=px;
			m_point.y=py;
			InvalidateIconText(pDC,px,py,GetTargName(UniqueID(m_hintid)));
			m_hintid=NULL; // dont display hints while dragging...
		}
	}
	if (m_LButtonDown && m_bDragging && m_buttonid)
	{
		ItemBasePtr p=Persons2::ConvertPtrUID(UniqueID(m_buttonid));
//DEADCODE JIM 16/02/99 		RDialog::m_pView->ScreenXY(p,px,py,-RDialog::m_pView->m_scrollpoint.x,-RDialog::m_pView->m_scrollpoint.y);
		InvalidateRoutes(UniqueID(m_buttonid));

		RDialog::m_pView->WorldXY(p->World,point.x,point.y); //JIM 16/02/99

//DEADCODE JIM 16/02/99 		p->World.X=(65536*(point.x+RDialog::m_pView->m_scrollpoint.x+(384*RDialog::m_pView->m_zoom)))/RDialog::m_pView->m_zoom;
//DEADCODE JIM 16/02/99  		p->World.Z=-65536*(point.y+RDialog::m_pView->m_scrollpoint.y-(1792*RDialog::m_pView->m_zoom))/RDialog::m_pView->m_zoom;
		InvalidateDragIcon(m_point.x,m_point.y,point.x,point.y);
		m_oldpoint=m_point;
		m_point=point;
		InvalidateRoutes(UniqueID(m_buttonid));
	}
	if (!m_LButtonDown)
	{
		// check if mouse pointer is over an icon and if so display
		// the hint text for it
		// first find if we are over one
		int oldhintid=m_hintid;
		m_hintid=NULL;
		m_hintid=FindMapItem(point);
		// doing 2 invalidaterects here removes the very slight flicker...
		if (oldhintid!=m_hintid)
		{
			if (m_hintid)
			{
				p=Persons2::ConvertPtrUID(UniqueID(m_hintid));
				RDialog::m_pView->ScreenXY(p,px,py,-RDialog::m_pView->m_scrollpoint.x,-RDialog::m_pView->m_scrollpoint.y);
				InvalidateIconText(pDC,px,py,GetTargName(UniqueID(m_hintid)));
			}
			if (oldhintid)
			{
				p=Persons2::ConvertPtrUID(UniqueID(oldhintid));
				if (p)
				{
					RDialog::m_pView->ScreenXY(p,px,py,-RDialog::m_pView->m_scrollpoint.x,-RDialog::m_pView->m_scrollpoint.y);
					InvalidateIconText(pDC,px,py,GetTargName(UniqueID(oldhintid)));
				}
			}
		}
	}
	CDialog::OnMouseMove(nFlags, point);
}

void CMapDlg::OnLButtonUp(UINT nFlags, CPoint point) 
{
	ReleaseCapture();
	if (m_LButtonDown)
	{
		m_LButtonDown=FALSE;
		if (m_buttonid)
		{
			if (!m_bDragging)
			{
				if(FindMapItem(point))
					OnClickItem(m_buttonid);
			}
			else
				OnDragItem(m_buttonid);
		}
	}
	CDialog::OnLButtonUp(nFlags, point);
}

void CMapDlg::InvalidateRoutes(UniqueID onlythrough)
{
	RDialog::m_pView->PlotRoutes(NULL,onlythrough);
/*	bool	seesubwp = true;
	ItemBasePtr pt1,pt2;

	// invalidates any routes coming in or out of m_buttonid
	// doesnt work
	for (int pack=0;pack<Profile::MAX_PACKS;pack++)
	{
		for (int wave=0;wave<Profile::MAX_WAVES;wave++)
		{
			for (int group=0;group<Profile::MAX_GROUPS;group++)
			{
				UniqueID start=Todays_Packages[pack][wave][group].takeoffAF;
				if (start)
				{
					UniqueID nextwp=Todays_Packages[pack][wave].firstwp;
					InvalidateMovedLine(start,nextwp);
					info_waypoint* wp=*Persons2::ConvertPtrUID(nextwp);
					UniqueID oldwp = nextwp;
					while ((nextwp=wp->nextwp)!=NULL)
					{
						wp=*Persons2::ConvertPtrUID(nextwp);
						if  (		
								(wp->uid !=ENABLE_COMPLEX_VAL) ||
								(wp->applygroup==ENABLE_COMPLEX_VAL) ||
								(		
									(seesubwp) &&
									(wp->applygroup == Todays_Packages.higroup)
								)
							)
						{
							//display subgroup wps as spurs
							InvalidateMovedLine(oldwp,nextwp);
							if  (wp->applyflight==ENABLE_COMPLEX_VAL)
							{
								oldwp=nextwp;
							}
						}
					}
					InvalidateMovedLine(nextwp,start);
				}
			}
		}
	}
	*/
}

void CMapDlg::InvalidateRoute(int	pack, int wave, int	group)
{
	UniqueID start=Todays_Packages[pack][wave][group].takeoffAF;
	bool	seesubwp = true;
	if (start)
	{
		UniqueID nextwp=Todays_Packages[pack][wave].firstwp;
		InvalidateLine(start,nextwp);
		info_waypoint* wp=*Persons2::ConvertPtrUID(nextwp);
		UniqueID oldwp = nextwp;
		while ((nextwp=wp->nextwp)!=NULL)
		{
			wp=*Persons2::ConvertPtrUID(nextwp);
			if  (		
					(wp->uid !=ENABLE_COMPLEX_VAL) ||
					(wp->applygroup==ENABLE_COMPLEX_VAL) ||
					(		
						(seesubwp) &&
						(wp->applygroup == Todays_Packages.higroup)
					)
				)
			{
				//display subgroup wps as spurs
				InvalidateLine(oldwp,nextwp);
				if  (wp->applyflight==ENABLE_COMPLEX_VAL)
				{
					oldwp=nextwp;
				}
			}
		}
		InvalidateLine(nextwp,start);
	}
}

void CMapDlg::InvalidateLine(UniqueID thiswp,UniqueID nextwp)
{
	int px1,py1,px2,py2;
	ItemBasePtr pt1,pt2;
	pt1=Persons2::ConvertPtrUID(UniqueID(thiswp));
	pt2=Persons2::ConvertPtrUID(UniqueID(nextwp));
	if (!pt1 || !pt2) return;
//DEADCODE RDH 18/04/99 	if (thiswp==UID_Japan)
//DEADCODE RDH 18/04/99 		RDialog::m_pView->ScreenXY(pt1->World.X + 40000000,pt1->World.Z - 20000000,px1,py1,-RDialog::m_pView->m_scrollpoint.x,-RDialog::m_pView->m_scrollpoint.y);
//DEADCODE RDH 18/04/99 	else
		RDialog::m_pView->ScreenXY(pt1,px1,py1,-RDialog::m_pView->m_scrollpoint.x,-RDialog::m_pView->m_scrollpoint.y);
//DEADCODE RDH 18/04/99 	if (nextwp==UID_Japan)
//DEADCODE RDH 18/04/99 		RDialog::m_pView->ScreenXY(pt2->World.X + 40000000,pt2->World.Z - 20000000,px2,py2,-RDialog::m_pView->m_scrollpoint.x,-RDialog::m_pView->m_scrollpoint.y);
//DEADCODE RDH 18/04/99 	else
		RDialog::m_pView->ScreenXY(pt2,px2,py2,-RDialog::m_pView->m_scrollpoint.x,-RDialog::m_pView->m_scrollpoint.y);
	InvalidateLine(CPoint(px1,py1),CPoint(px2,py2));
	InvalidateIcon(px1,py1);										  //JIM 02/06/99
}

//DEADCODE JIM 16/03/99 void CMapDlg::InvalidateMovedLine(UniqueID thiswp,UniqueID nextwp,BOOL japanwp)
//DEADCODE JIM 16/03/99 {
//DEADCODE JIM 16/03/99 
//DEADCODE JIM 16/03/99 	if (thiswp!=m_buttonid && nextwp!=m_buttonid)
//DEADCODE JIM 16/03/99 		return;
//DEADCODE JIM 16/03/99 	if (thiswp!=m_buttonid)
//DEADCODE JIM 16/03/99 	{
//DEADCODE JIM 16/03/99 		UniqueID swap;
//DEADCODE JIM 16/03/99 		swap=thiswp;
//DEADCODE JIM 16/03/99 		thiswp=nextwp;
//DEADCODE JIM 16/03/99 		nextwp=swap;
//DEADCODE JIM 16/03/99 	}
//DEADCODE JIM 16/03/99 	int px2,py2;
//DEADCODE JIM 16/03/99 	ItemBasePtr pt2;
//DEADCODE JIM 16/03/99 	pt2=Persons2::ConvertPtrUID(UniqueID(nextwp));
//DEADCODE JIM 16/03/99 	if (japanwp)
//DEADCODE JIM 16/03/99 		RDialog::m_pView->ScreenXY(pt2->World.X + 40000000,pt2->World.Z - 20000000,px2,py2,-RDialog::m_pView->m_scrollpoint.x,-RDialog::m_pView->m_scrollpoint.y);
//DEADCODE JIM 16/03/99 	else
//DEADCODE JIM 16/03/99 		RDialog::m_pView->ScreenXY(pt2,px2,py2,-RDialog::m_pView->m_scrollpoint.x,-RDialog::m_pView->m_scrollpoint.y);
//DEADCODE JIM 16/03/99 	InvalidateLine(m_point,CPoint(px2,py2));
//DEADCODE JIM 16/03/99 	InvalidateLine(m_oldpoint,CPoint(px2,py2));
//DEADCODE JIM 16/03/99 }

#ifndef	NDEBUG

DebugLineStats	debugboxmem
={{0x00,0x20,0x40,0x60,0x80,0xA0,0xC0,0xE0},0,0};
#endif
void CMapDlg::InvalidateLine(CPoint point1,CPoint point2)
{	// invalidates a line from point1 to point2
	// ideally youd have thought you could use invalidate region
	// however this is very very slow...

	// so instead we invalidate millions of little rectangles...

//	CRect rect(point1.x-1,point1.y-1,point2.x+1,point2.y+1);
//	rect.NormalizeRect();
//	InvalidateRect(rect);
	const RECTSIZE=50;
	CRect clientrect;
	CRect rect;
	CRect intersectrect;
	GetClientRect(clientrect);
	double dx=point2.x-point1.x;
	double dy=point2.y-point1.y;
	int steps;
	if (abs(dx)>abs(dy))
	{
		steps=abs(dx/RECTSIZE)+1;
		if (steps>1)
		{
			dy=dy/steps;
			dx=dx/steps;
		}
	}
	else
	{
		steps=abs(dy/RECTSIZE)+1;
		if (steps>1)
		{
			dy=dy/steps;
			dx=dx/steps;
		}
	}
	int radius=2;
	double x1,y1,x2,y2;
	if (dx>0)
	{
		x1=point1.x-dx/2-radius;
		x2=point1.x+dx/2+radius;
	}
	else
	{
		x2=point1.x-dx/2+radius;
		x1=point1.x+dx/2-radius;
	}
	if (dy>0)
	{
		y1=point1.y-dy/2-radius;
		y2=point1.y+dy/2+radius;
	}
	else
	{
		y2=point1.y-dy/2+radius;
		y1=point1.y+dy/2-radius;
	}
	for (int i=0;i<=steps;i++)
	{
		CRect rect(x1,y1,x2,y2);
		if (intersectrect.IntersectRect(clientrect,rect))
		{
			InvalidateRect(rect);
#ifndef NDEBUG
			debugboxmem.Set(rect);
#endif
		}
		x1+=dx;
		x2+=dx;
		y1+=dy;
		y2+=dy;
	}
#ifndef NDEBUG
	debugboxmem.lastline++;
#endif
}

/*
	// the polygon technique:
	// this isnt perfect
	CPoint points[6];
	int orientation;
	// figure out the orientation of point1 to point2
	// 0=topright 1=bottomright 2=bottomleft 3=topleft
	if (point1.x<=point2.x && point1.y>=point2.y) orientation=0;
	if (point1.x<=point2.x && point1.y<=point2.y) orientation=1;
	if (point1.x>=point2.x && point1.y<=point2.y) orientation=2;
	if (point1.x>=point2.x && point1.y>=point2.y) orientation=3;
	int i=0;
	if (orientation!=0) 
	{
		points[i]=CPoint(point1.x+2,point1.y-2);
		i++;
	}
	if (orientation!=1) 
	{
		points[i]=CPoint(point1.x+2,point1.y+2);
		i++;
	}
	if (orientation!=2) 
	{
		points[i]=CPoint(point1.x-2,point1.y+2);
		i++;
	}
	if (orientation!=3) 
	{
		points[i]=CPoint(point1.x-2,point1.y-2);
		i++;
	}

	if (orientation!=2) 
	{
		points[i]=CPoint(point2.x+2,point2.y-2);
		i++;
	}
	if (orientation!=3) 
	{
		points[i]=CPoint(point2.x+2,point2.y+2);
		i++;
	}
	if (orientation!=0) 
	{
		points[i]=CPoint(point2.x-2,point2.y+2);
		i++;
	}
	if (orientation!=1) 
	{
		points[i]=CPoint(point2.x-2,point2.y-2);
		i++;
	}
	CRgn region;
	region.CreatePolygonRgn(points,8,WINDING);
	InvalidateRgn(&region);
}
*/




void CMapDlg::OnTimer(UINT nIDEvent) 
{
//DeadCode AMM 03Mar99 	static ULong nextsendtime=timeGetTime()+20000; // every 20 secs

	if (nIDEvent==maptimer && _DPlay.PlayerCreated)
	{
		if (DPlay::H2H_Player[_DPlay.mySlot].status==CPS_MAP)
		{
//DeadCode AMM 03Mar99 			if (timeGetTime()>nextsendtime && _DPlay.Host)
//DeadCode AMM 03Mar99 			{
//DeadCode AMM 03Mar99 				nextsendtime=timeGetTime()+20000;
//DeadCode AMM 03Mar99 				_DPlay.SendSaveGame();
//DeadCode AMM 03Mar99 			}

			_DPlay.UIUpdateMainSheet();
		}
	}
	
	CDialog::OnTimer(nIDEvent);
}

BOOL CMapDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
 	maptimer=SetTimer(TIMER_MAP,0,NULL);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CMapDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	KillTimer(maptimer);
	
}

//DEADCODE JIM 29/05/99 BOOL CMapDlg::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) 
//DEADCODE JIM 29/05/99 {
//DEADCODE JIM 29/05/99 	// TODO: Add your message handler code here and/or call default
//DEADCODE JIM 29/05/99 	
//DEADCODE JIM 29/05/99 	return CDialog::OnMouseWheel(nFlags, zDelta, pt);
//DEADCODE JIM 29/05/99 }
