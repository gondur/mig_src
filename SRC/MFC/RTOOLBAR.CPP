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

// CRToolBar.cpp : implementation file
//

#include "stdafx.h"
#include "mig.h"

#include  <afxpriv.h>

#include "RToolBar.h"
#include "MainFrm.h"
#include "migview.h"
#include "messages.h"
#include "fileman.h"
#include "miles.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#ifndef THIS_FILE_DEFINED
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif

/////////////////////////////////////////////////////////////////////////////
// RToolBar dialog
IMPLEMENT_DYNAMIC(CRToolBar,CDialog);

CRToolBar::CRToolBar(CWnd* pParent /*=NULL*/)
	: CDialog(CRToolBar::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRToolBar)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_init=TRUE;
	//m_nIDHelp=
	if (m_pCtrlSite)
		m_align=4;
}


void CRToolBar::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRToolBar)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
	if (m_pCtrlSite)
		m_align=4;
}

void	CRToolBar::DDX_Control(CDataExchange* pDX,int	dialid,CWnd&	m_dial)
{
	HWND tmp;
	GetDlgItem(dialid,&tmp);
	if (tmp)
		::DDX_Control(pDX,dialid,m_dial);
}


BEGIN_MESSAGE_MAP(CRToolBar, CDialog)
	//{{AFX_MSG_MAP(CRToolBar)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_CREATE()
	ON_WM_ERASEBKGND()
	ON_WM_CANCELMODE()
	ON_WM_CAPTURECHANGED()
	ON_WM_CHAR()
	ON_WM_CLOSE()
	ON_WM_CHARTOITEM()
	ON_MESSAGE( WM_GETFILE, OnGetFile)
	ON_MESSAGE( WM_RELEASELASTFILE, OnReleaseLastFile)
	ON_MESSAGE( WM_GETHINTBOX, OnGetHintBox)
	ON_MESSAGE( WM_PLAYSOUND, OnPlaySound)
	ON_MESSAGE( WM_GETSTRING, OnGetString)
	ON_WM_ENABLE()
	//}}AFX_MSG_MAP
	ON_MESSAGE( WM_COMMANDHELP,OnCommandHelp)

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRToolBar message handlers

void CRToolBar::SetHorzAlign(BOOL bHorzAlign)
{
	if (m_bHorzAlign==bHorzAlign) return;
	m_bHorzAlign=bHorzAlign;
	// rotate all the components on the dialog by swapping their x,y coords
	// its recommended all components be square for this to be effective
	CWnd* pControl;
	pControl=GetTopWindow();
	Invalidate();
	CRect parentrect;
	GetClientRect(parentrect);
	ClientToScreen(parentrect);
	CRect rect;
	while (pControl)
	{
		// find coords relative to parent window...
		// why they dont have a ClientToParent function I dont know
		pControl->GetWindowRect(rect);
		rect-=parentrect.TopLeft();
		pControl->MoveWindow(rect.top,rect.left,rect.Height(),rect.Width());
		pControl=pControl->GetNextWindow();
	}
}

void CRToolBar::Init(CMainFrame * parent, int minlength, int length, int width, UINT nDockBarID, int priority, UINT dockablesides)
{
	// store the information
	if (m_pCtrlSite)
		m_align=4;
	m_pFrame=parent;
	m_pView=(CMIGView*)parent->GetActiveView();
	m_length=length;
	m_width=width;
	m_row=0;
	m_dockablesides=dockablesides;
	ASSERT(m_length>m_width); // length must always be greater than width...
	m_minlength=minlength;
	m_priority=priority;
	// add the toolbar to the end of the appropriate list
	m_index=-1;
	m_bHorzAlign=TRUE;
	m_align=1;
	switch (nDockBarID)
	{
		case AFX_IDW_DOCKBAR_TOP:
		m_pFrame->m_top.AddTail(this);
		m_pList=&m_pFrame->m_top;
		m_index=m_pFrame->m_top.GetCount();
		m_bHorzAlign=TRUE;
		m_align=1;
		break;
		case AFX_IDW_DOCKBAR_LEFT:
		m_pFrame->m_left.AddTail(this);
		m_pList=&m_pFrame->m_left;
		m_index=m_pFrame->m_left.GetCount();
		m_bHorzAlign=FALSE;
		m_align=4;
		break;
		case AFX_IDW_DOCKBAR_RIGHT:
		m_pFrame->m_right.AddTail(this);
		m_pList=&m_pFrame->m_right;
		m_index=m_pFrame->m_right.GetCount();
		m_bHorzAlign=FALSE;
		m_align=2;
		break;
		case AFX_IDW_DOCKBAR_BOTTOM:
		m_pFrame->m_bottom.AddTail(this);
		m_pList=&m_pFrame->m_bottom;
		m_index=m_pFrame->m_bottom.GetCount();
		m_bHorzAlign=TRUE;
		m_align=3;
		break;
	}
	if (m_pCtrlSite)
		m_align=4;
	if (m_index>-1) ModifyStyle(WS_POPUP,WS_CHILD); // Docks it
	m_init=FALSE;
}

void CRToolBar::OnLButtonDown(UINT nFlags, CPoint point) 
{
	if (point.x<48 && point.y<48)
	{

		m_LButtonDown=1;
		SetCapture();
		m_lastdown=point;
		Float();
		SetWindowPos(&wndTop,0,0,0,0,SWP_NOMOVE | SWP_NOSIZE);
		if (m_lastdown.x>m_length-(m_width/2)) m_lastdown.x=m_length-(m_width/2);
		if (m_lastdown.y>m_length-(m_width/2)) m_lastdown.y=m_length-(m_width/2);
		CDialog::OnLButtonDown(nFlags, point);
	}
	else
	if (m_align && !AfxGetApp()->m_pMainWnd->IsZoomed())	//0 means not docked?
	{	//want to start dragging m_pFrame
		m_LButtonDown=2;
		SetCapture();
		m_lastdown=point;
	}
}

void CRToolBar::OnMouseMove(UINT nFlags, CPoint point) 
{
	switch (m_LButtonDown)
	{
	case 1:
	{
		if (RDialog::m_moving==TRUE) return;
		RDialog::m_moving=TRUE;
		CRect rect;
		GetWindowRect(rect);
		int dockside=GetDockSide(point);
		BOOL bNewHorzAlign=m_bHorzAlign;
		if (dockside==1 || dockside==3) bNewHorzAlign=TRUE;
		if (dockside==2 || dockside==4) bNewHorzAlign=FALSE;
		if (dockside>0 && dockside!=m_align) 
		{
			if (m_bHorzAlign!=bNewHorzAlign) m_lastdown=CPoint(m_width/2,m_width/2);
			m_align=dockside;
			Invalidate();
		}
		if (m_bHorzAlign!=bNewHorzAlign) SetHorzAlign(bNewHorzAlign);
		if (m_bHorzAlign)
		{
			rect.right=rect.left+m_length;
			rect.bottom=rect.top+m_width;
		}
		else
		{
			rect.right=rect.left+m_width;
			rect.bottom=rect.top+m_length;
		}
		MoveWindow(rect+point-m_lastdown);
//		MoveWindow(point.x-10,point.y-10,rect.Width(),rect.Height());
	}
	break;
	case 2:
	{
		CMainFrame* w=(CMainFrame*)AfxGetApp()->m_pMainWnd;
		CRect rect;
		w->GetWindowRect(rect);
		CPoint p2=point-m_lastdown;
 		w->MoveWindow(rect+p2);
		w->RePositionLayout(p2.x,p2.y);

////TEMPCODE DAW 07/05/99 		GetWindowRect(rect);
////TEMPCODE DAW 07/05/99 		MoveWindow(rect+point-m_lastdown);
	}
	break;
	}

	CDialog::OnMouseMove(nFlags, point);
}

void CRToolBar::OnLButtonUp(UINT nFlags, CPoint point) 
{
	
	switch (m_LButtonDown)
	{
	case 1:
		{
			m_LButtonDown=FALSE;
			ReleaseCapture();
			int dockside=GetDockSide(point);
			if (dockside>0)
			{
				// for now just add it to the end...
				// ok ok we will insert...
				// first check if we released outside the toolbar area...
				switch (m_align)
				{
					case 1:
					m_pList=&m_pFrame->m_top;
					break;
					case 4:
					m_pList=&m_pFrame->m_left;
					break;
					case 2:
					m_pList=&m_pFrame->m_right;
					break;
					case 3:
					m_pList=&m_pFrame->m_bottom;
					break;
				}
				int insertafter=0;
				CRect rect;
				m_pView->GetWindowRect(rect);
				CRect rect2;
				m_pFrame->GetClientRect(rect2);
				m_pFrame->ClientToScreen(rect2);
				CRect rect3;
				GetClientRect(rect3);
				ClientToScreen(rect3);
				point+=rect3.TopLeft();
				if (!rect2.PtInRect(point)) insertafter=-1; // dragged outside so put at beginning
				if (rect.PtInRect(point)) insertafter=1000; // dragged inside so put at end
				if (insertafter==0) // we didnt so find where we did drag into
				{
					ShowWindow(SW_HIDE);
					CRToolBar* pToolbar=FindToolBar(point);
					ShowWindow(SW_SHOW);
					// if this fails we will assume you mean the end of the top row...
					if (!pToolbar && m_align!=1)
					{
						m_align=1;
						m_pList=&m_pFrame->m_top;
						SetHorzAlign(TRUE);
					}
					if (!pToolbar)
					{
						insertafter=1000;
						POSITION position;
						position=m_pList->GetHeadPosition();
						for (int x=0;x<m_pList->GetCount();x++)
						{
							pToolbar=m_pList->GetNext(position);
							if (pToolbar->m_row==1)
							{
								insertafter=x-1;
								break;
							}
						}
					}
					else
					{
						CRect rect3;
						pToolbar->GetWindowRect(rect3);
						if (rect3.Width()>rect3.Height())
						{
							if (point.x<rect3.left+(pToolbar->m_minlength/2)) insertafter=pToolbar->m_index-2;
							else insertafter=pToolbar->m_index-1;
						}
						else 
						{
							if (point.y<rect3.top+(pToolbar->m_minlength/2)) insertafter=pToolbar->m_index-2;
							else insertafter=pToolbar->m_index-1;
						}
					}
				}
				TRACE1("insertafter=%d\n",insertafter);
				if (insertafter==1000) insertafter=m_pList->GetCount();
				if (insertafter>=0)
				{
					POSITION position;
					position=m_pList->FindIndex(insertafter);
					m_pList->InsertAfter(position,this);
				}
				else
				{
					m_pList->AddHead(this);
				}
				ModifyStyle(WS_POPUP,WS_CHILD); // Docks it
				m_pFrame->RecalcLayout();
			}
		}
		break;
	case 2:
		{
			m_LButtonDown=FALSE;
			ReleaseCapture();
			m_pFrame->RecalcLayout();
		}
		break;

	}
	CDialog::OnLButtonUp(nFlags, point);
}

int CRToolBar::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	m_LButtonDown=FALSE;
	return 0;
}

int CRToolBar::GetDockSide(CPoint point)
{
		// check if were trying to dock and change alignment if we are
		// docking happens when any portion of the window overlaps
		// any part of the dockable area with the horizontal strips
		// taking priority
//		CRect parentrect;
//		m_pFrame->GetWindowRect(parentrect);
		CRect rect;
		m_pFrame->GetWindowRect(rect);
		CRect rect2;
		GetWindowRect(rect2);
		point+=rect2.TopLeft();
		int dockside=0; // 0 none 1 top 2 right 3 bot 4 left
		// To simplify things first check if cursor is inside the main window
		if (point.x>rect.right+m_width ||
			point.x<rect.left-m_width ||
			point.y>rect.bottom+m_width ||
			point.y<rect.top-m_width) return 0;
		if (point.x+m_width>rect.right-m_pFrame->m_borderRect.right) dockside=2;
//		if (rect2.left+m_width>rect.right-m_pFrame->m_borderRect.right) dockside=2;
		if (point.x-m_width<rect.left+m_pFrame->m_borderRect.left) dockside=4;
//		if (rect2.left<rect.left+m_pFrame->m_borderRect.left) dockside=4;
		if (point.y+m_width>rect.bottom-m_pFrame->m_borderRect.bottom) dockside=3;
//		if (rect2.top+m_width>rect.bottom-m_pFrame->m_borderRect.bottom) dockside=3;
		if (point.y-m_width<rect.top+m_pFrame->m_borderRect.top) dockside=1;
//		if (rect2.top<rect.top+m_pFrame->m_borderRect.top) dockside=1;
//		TRACE2("point.x %d point.y %d\n",point.x,point.y);
//		TRACE1("Dockside: %d\n",dockside);
		// is this a valid dockside?
		if (dockside==1 && !(m_dockablesides&CBRS_ALIGN_TOP)) return 0;
		if (dockside==2 && !(m_dockablesides&CBRS_ALIGN_RIGHT)) return 0;
		if (dockside==3 && !(m_dockablesides&CBRS_ALIGN_BOTTOM)) return 0;
		if (dockside==4 && !(m_dockablesides&CBRS_ALIGN_LEFT)) return 0;
		return dockside;
}

BOOL CRToolBar::OnEraseBkgnd(CDC* pDC) 
{
	CRect rect;
	GetWindowRect(rect);
	CRect viewrect;
	m_pFrame->GetWindowRect(viewrect);
	if (rect.Width()>m_length || rect.Height()>m_length)  // presumably width is always smaller than length
	{
		// draw in some fill in artwork on the right hand side...
		// note that you can override this so it does nothing
		// make sure your dialog has no background showing through
/*		CDC memDC;
		memDC.CreateCompatibleDC(pDC);
		CBitmap* pOldBitmap;
		CBitmap art;
		if (m_bHorzAlign) art.LoadBitmap(IDB_TOOLBAR_HORZ);
		else art.LoadBitmap(IDB_TOOLBAR_VERT);
		BITMAP artworkinfo;
		art.GetBitmap(&artworkinfo);
		pOldBitmap = memDC.SelectObject(&art);
		if (m_bHorzAlign) pDC->BitBlt(m_length,0,rect.Width()-m_length,m_width,
				&memDC,artworkinfo.bmWidth-rect.Width()+m_length,0,SRCCOPY);
		else pDC->BitBlt(0,m_length,m_width,rect.Height()-m_length,
				&memDC,0,artworkinfo.bmHeight-rect.Height()+m_length,SRCCOPY);
		memDC.SelectObject(pOldBitmap);
		memDC.DeleteDC();*/
		// filesystem method
		FileNum artnum;
		if (m_bHorzAlign) 
			artnum=FIL_TOOL_HORIZONTAL;
		else
			artnum=FIL_TOOL_VERTICAL;
		BYTE* pData;
		if (artnum)
		{
			fileblock picture(artnum);
			pData=(BYTE*)getdata(picture);
			if (pData[0]=='B' && pData[1]=='M') // checks if its a bitmap file
			{
				// now render it...
				BITMAPFILEHEADER* pFile=(BITMAPFILEHEADER*)pData;
				BITMAPINFO* pInfo=(BITMAPINFO*)(pData+sizeof(BITMAPFILEHEADER));
				pData+=pFile->bfOffBits;
				int yoffset=0;
				int xoffset=0;
							//MIN art on child  <== parentMAX - childMAX - artworkSIZE
				if (m_bHorzAlign)
					xoffset=viewrect.right-rect.left-pInfo->bmiHeader.biWidth;
				else
					yoffset=viewrect.bottom-rect.top-pInfo->bmiHeader.biHeight;
				int xskip=0,yskip=0;

				switch (m_align)
				{	//do artwork shuffle down: Do it accross as well for vertical!
				case 0:	xoffset=0;				yskip=m_length;				break;
				case 1:	yoffset=-m_row*46;		xskip=m_length;				break;
				case 2:	xoffset=0;				yskip=m_length;				break;
				case 3:	yoffset=(m_row-2)*46;	xskip=m_length;				break;
				case 4:	xoffset=0;				yskip=m_length;				break;
				}

//int SetDIBitsToDevice(
//	HDC hdc,              
//	int XDest,		int YDest,            
//	DWORD dwWidth,	DWORD dwHeight,
//	int XSrc,		int YSrc,
//	UINT uStartScan,UINT cScanLines,
//	CONST VOID *lpvBits,	CONST BITMAPINFO *lpbmi,	UINT fuColorUse);

				if (yoffset)
					yoffset=yoffset;
//			pDC->FillSolidRect(0,0,rect.Width(),rect.Height(),COLORREF(int(this)&0x00ffffff));
				SetDIBitsToDevice(pDC->m_hDC,
						xskip,yskip+yoffset,
						pInfo->bmiHeader.biWidth-xskip,pInfo->bmiHeader.biHeight-yskip,
						xskip-xoffset,yskip,
						0,pInfo->bmiHeader.biHeight,
						pData,pInfo,DIB_RGB_COLORS);

			//wipe any bits that aren't covered by artwork!!!
			COLORREF	rgb=RGB(66,75,99);
			if (yoffset>yskip)
				pDC->FillSolidRect(yskip,xskip,rect.Width()-xskip,yoffset-yskip,rgb);
			if (pInfo->bmiHeader.biHeight+yoffset<rect.Height())
				if (pInfo->bmiHeader.biHeight+yoffset<<yskip)
					pDC->FillSolidRect(xskip,yskip,rect.Width()-xskip,rect.Height()-yskip,rgb);
				else
					pDC->FillSolidRect(xskip,pInfo->bmiHeader.biHeight+yoffset,rect.Width()-xskip,rect.Height()-yskip,rgb);
			if (xoffset>xskip)
				pDC->FillSolidRect(xskip,yskip,xoffset-xskip,rect.Height()-yskip,rgb);
			if (pInfo->bmiHeader.biWidth+xoffset<rect.Width())
				if (pInfo->bmiHeader.biWidth+xoffset<xskip)
					pDC->FillSolidRect(xskip,yskip,rect.Width()-xskip,rect.Height()-yskip,rgb);
				else
					pDC->FillSolidRect(pInfo->bmiHeader.biWidth+xoffset,yskip,rect.Width(),rect.Height()-yskip,RGB(78,100,78));
//			pDC->FillSolidRect(0,0,rect.Width(),rect.Height(),COLORREF(-int(this)&0x00ffffff));

			

			}
		}
	}
//	
	return TRUE;	
//	return CDialog::OnEraseBkgnd(pDC);
}


CRToolBar* CRToolBar::FindToolBar(CPoint point)
{ // recursively search the underlying windows for a docked toolbar
	// if it doesnt find one it will crash but this will never happen (tm)
	CRToolBar* pToolbar;
	pToolbar=(CRToolBar*)WindowFromPoint(point);
	if (pToolbar->IsKindOf(RUNTIME_CLASS(CRToolBar)) && pToolbar->m_index>-1) return pToolbar;
	// check for a failure as soon as possible
	if ((CWnd*)pToolbar==m_pFrame->m_wndSystemBox || 
		(CWnd*)pToolbar==m_pFrame ||
		(CWnd*)pToolbar==GetDesktopWindow()) 
		return NULL;
	pToolbar->ShowWindow(SW_HIDE);
	CRToolBar* pNewToolbar;
	pNewToolbar=FindToolBar(point);
	pToolbar->ShowWindow(SW_SHOW);
	return pNewToolbar;
}

int CRToolBar::OnGetString(int resourceID,char* workbuffer)
{
	return AfxLoadString(resourceID,workbuffer,(UByte)workbuffer[0]);
}



BYTE* CRToolBar::OnGetFile(int filenum)
{
	m_pfileblock=new fileblock((FileNum)filenum);
	return (BYTE*)getdata(m_pfileblock);
}

void CRToolBar::OnPlaySound(int filenum)
{
	_Miles.UIPlaySample((FileNum)filenum);						//RJS 12Mar99
//DeadCode RJS 12Mar99 	_Miles.ProcessInterfaceSpot();		//RJS 17Nov98

}

CHintBox* CRToolBar::OnGetHintBox()
{
	if (!RDialog::m_pHintBox)
		RDialog::m_pHintBox=new CHintBox;
	if (!RDialog::m_pHintBox->m_hWnd)
		RDialog::m_pHintBox->Create(CHintBox::IDD,NULL);
	return RDialog::m_pHintBox;
}

void CRToolBar::OnReleaseLastFile()
{
	delete m_pfileblock;
}

void CRToolBar::CalcWindowRect(LPRECT lpClientRect, UINT nAdjustType) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CDialog::CalcWindowRect(lpClientRect, nAdjustType);
}



LRESULT CRToolBar::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CDialog::DefWindowProc(message, wParam, lParam);
}

BOOL CRToolBar::DestroyWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CDialog::DestroyWindow();
}

int CRToolBar::DoModal() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CDialog::DoModal();
}

CScrollBar* CRToolBar::GetScrollBarCtrl(int nBar) const
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CDialog::GetScrollBarCtrl(nBar);
}

BOOL CRToolBar::OnAmbientProperty(COleControlSite* pSite, DISPID dispid, VARIANT* pvar) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CDialog::OnAmbientProperty(pSite, dispid, pvar);
}

BOOL CRToolBar::OnChildNotify(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pLResult) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CDialog::OnChildNotify(message, wParam, lParam, pLResult);
}

BOOL CRToolBar::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CDialog::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}

BOOL CRToolBar::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CDialog::OnCommand(wParam, lParam);
}

void CRToolBar::OnFinalRelease() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CDialog::OnFinalRelease();
}

BOOL CRToolBar::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CDialog::OnNotify(wParam, lParam, pResult);
}

void CRToolBar::OnSetFont(CFont* pFont) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CDialog::OnSetFont(pFont);
}

void CRToolBar::PostNcDestroy() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CDialog::PostNcDestroy();
}

BOOL CRToolBar::PreCreateWindow(CREATESTRUCT& cs) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CDialog::PreCreateWindow(cs);
}

void CRToolBar::PreSubclassWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CDialog::PreSubclassWindow();
}

BOOL CRToolBar::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CDialog::PreTranslateMessage(pMsg);
}

void CRToolBar::Serialize(CArchive& ar) 
{
	if (ar.IsStoring())
	{	// storing code
	}
	else
	{	// loading code
	}
}

LRESULT CRToolBar::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CDialog::WindowProc(message, wParam, lParam);
}

void CRToolBar::WinHelp(DWORD dwData, UINT nCmd) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CDialog::WinHelp(dwData, nCmd);
}

void CRToolBar::OnCancelMode() 
{
	CDialog::OnCancelMode();
	
	// TODO: Add your message handler code here
	
}

void CRToolBar::OnCaptureChanged(CWnd *pWnd) 
{
	// TODO: Add your message handler code here
	
	CDialog::OnCaptureChanged(pWnd);
}

void CRToolBar::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	
	CDialog::OnChar(nChar, nRepCnt, nFlags);
}

void CRToolBar::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	
	CDialog::OnClose();
}

int CRToolBar::OnCharToItem(UINT nChar, CListBox* pListBox, UINT nIndex) 
{
	// TODO: Add your message handler code here and/or call default
	
	return CDialog::OnCharToItem(nChar, pListBox, nIndex);
}

void CRToolBar::Float()
{
	if (m_index>-1) // float it if its docked
	{
		ModifyStyle(WS_CHILD,WS_POPUP); // Converts it to a popup since floating
		POSITION position;
		position=m_pList->FindIndex(m_index-1);
		m_pList->RemoveAt(position);
		m_index=-1;
		m_pFrame->RecalcLayout();
	}
}

void CRToolBar::Replace(CRToolBar* newtoolbar)
{
	newtoolbar->Float(); // assumed to be floating
	newtoolbar->m_pList=m_pList;
	newtoolbar->m_align=m_align;
	newtoolbar->m_index=m_index;
	newtoolbar->SetHorzAlign(m_bHorzAlign);
	if (m_index>-1) // if were docked replace the order
	{
		POSITION position;
		position=m_pList->FindIndex(m_index-1);
		m_pList->SetAt(position,newtoolbar);
		ModifyStyle(WS_CHILD,WS_POPUP); // Converts it to a popup since floating
		m_index=-1;
		ShowWindow(SW_HIDE);
		m_pFrame->RecalcLayout();
	}
	else
	{
		CRect parentrect;
		GetParent()->GetWindowRect(parentrect);
		GetParent()->ScreenToClient(parentrect);
		CRect rect;
		GetWindowRect(rect);
		rect-=parentrect.TopLeft();
		if (newtoolbar->m_bHorzAlign)
		{
			rect.right=rect.left+newtoolbar->m_length;
			rect.bottom=rect.top+newtoolbar->m_width;
		}
		else
		{
			rect.right=rect.left+newtoolbar->m_width;
			rect.bottom=rect.top+newtoolbar->m_length;
		}
		newtoolbar->MoveWindow(rect);
		ShowWindow(SW_HIDE);
	}
	MoveWindow(0,0,0,0);
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		OnInitDialog
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
extern	int	ScaleTranslate(int input,bool isy);
extern	UWord	scalinglookup[512][2][2];
BOOL CRToolBar::OnInitDialog()
{
	CDialog::OnInitDialog();
	if (!scalinglookup[1][0][1])
		for (int x=0;x<512;x++)
		{
			RECT baseunits={0,0,x,x};
			MapDialogRect(&baseunits);
			scalinglookup[x][0][1]=baseunits.right;
			scalinglookup[x][1][1]=baseunits.bottom;
		}
	// xfactor seems to be slightly smaller than yfactor
	// for some reason
//DEADCODE JIM 18/08/99 	float yfactor=96.0f/RDialog::fontdpi;
//DEADCODE JIM 18/08/99 	float xfactor=yfactor;
//DEADCODE JIM 18/08/99 	if (xfactor!=1.0f)
//DEADCODE JIM 18/08/99 		xfactor*=0.94f; // fiddle factor
	CRect rect;
	CRect parentrect;
	CWnd* pControl;
	pControl=GetTopWindow();
	GetClientRect(parentrect);
	ClientToScreen(parentrect);
	while (pControl)
	{
		// find coords relative to parent window...
		// why they dont have a ClientToParent function I dont know
		pControl->GetWindowRect(rect);
		rect-=parentrect.TopLeft();
		rect.right=ScaleTranslate(rect.right,false);
		rect.bottom=ScaleTranslate(rect.bottom,true);
		rect.left=ScaleTranslate(rect.left,false);
		rect.top=ScaleTranslate(rect.top,true);
		pControl->MoveWindow(rect);
		pControl=pControl->GetNextWindow();
	}
	// size the actual dialog
	GetWindowRect(rect);
	GetParent()->GetClientRect(parentrect);
	GetParent()->ClientToScreen(parentrect);
	rect-=parentrect.TopLeft();
	Invalidate();
	MoveWindow(rect.left,rect.top,ScaleTranslate(rect.Width(),false),ScaleTranslate(rect.Height(),true));
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
////////////////////////////////////////////////////////////////////////
//
// Function:    OnCommandHelp
// Date:        24/02/99
// Author:      RDH
//
// Description: 
//
////////////////////////////////////////////////////////////////////////
LRESULT CRToolBar::OnCommandHelp(WPARAM w, LPARAM lParam)
{
	return CDialog::OnCommandHelp(w,lParam);

}

BOOL CRToolBar::Create(UINT nIDTemplate, CWnd* pParentWnd)
{
	m_nIDHelp=nIDTemplate;
	return	CDialog::Create(nIDTemplate,pParentWnd);
}

//BOOL CRToolBar::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext) 
//{
//	// TODO: Add your specialized code here and/or call the base class
//	//m_nIDHelp=
//	return CDialog::Create(IDD, pParentWnd);
//}

void CRToolBar::OnEnable(BOOL bEnable) 
{
	CDialog::OnEnable(bEnable);
	
	// TODO: Add your message handler code here
	
}
