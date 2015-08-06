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

// Thumbnail.cpp : implementation file
//

#include "stdafx.h"
#include "MIG.h"
#include "Thumnail.h"
#include "MIGView.h"
#include "winuser.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#ifndef	THIS_FILE_DEFINED
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif
 static const CPoint offsetfix(2,8);
/////////////////////////////////////////////////////////////////////////////
// CThumbnail dialog


CThumbnail::CThumbnail(CWnd* pParent /*=NULL*/)
	: RowanDialog(CThumbnail::IDD, pParent)
{
	//{{AFX_DATA_INIT(CThumbnail)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_LButtonDown=FALSE;
}


void CThumbnail::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CThumbnail)
	DDX_Control(pDX, IDJ_TITLE, m_IDJ_TITLE);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CThumbnail, CDialog)
	//{{AFX_MSG_MAP(CThumbnail)
	ON_WM_CLOSE()
	ON_WM_SIZE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CThumbnail message handlers

void CThumbnail::OnClose() 
{
	CDialog::OnClose();
}

void CThumbnail::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	Invalidate();
}


void CThumbnail::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CRButton* button;
	button=GETDLGITEM(IDJ_TITLE);
	CRect buttonrect;
	button->GetClientRect(buttonrect);
	if (point.y<=buttonrect.bottom)
		CDialog::OnLButtonDown(nFlags, point);
	else
	{
		m_LButtonDown=TRUE;
		SetCapture();
		m_point=point;
//		m_point.y+=buttonrect.bottom;
		InvalidateMapOnly();
	}
}

void CThumbnail::OnLButtonUp(UINT nFlags, CPoint point) 
{
	ReleaseCapture(); 
	if (m_LButtonDown) 
	{
		m_point=m_point-offsetfix;			//quick thumbnail fix
		UpdateView();	
	}
	m_LButtonDown=FALSE;
	CDialog::OnLButtonUp(nFlags, point);

}

void CThumbnail::OnMouseMove(UINT nFlags, CPoint point) 
{
	if (m_LButtonDown)
	{
//TEMPCODE DAW 02/06/99 		CRButton* button;
//TEMPCODE DAW 02/06/99 		button=GETDLGITEM(IDJ_TITLE);
//TEMPCODE DAW 02/06/99 		CRect buttonrect;
//TEMPCODE DAW 02/06/99 		button->GetClientRect(buttonrect);
//		m_point.y+=buttonrect.bottom; 
		m_point=point;
		InvalidateMapOnly();
//		UpdateView();
	}
	else
		CDialog::OnMouseMove(nFlags, point);
}

BOOL CThumbnail::OnEraseBkgnd(CDC* pDC) 
{
	return TRUE;
}

void CThumbnail::DrawScaledBitmap(CDC * pDC, FileNum filenum, int left,int top,int width,int height)
{
	fileblock picture(filenum);
	BYTE* pData=(BYTE*)getdata(picture);
	if (pData[0]=='B' && pData[1]=='M') // checks if its a bitmap file
	{
		// now render it...
		BITMAPFILEHEADER* pFile=(BITMAPFILEHEADER*)pData;
		BITMAPINFO* pInfo=(BITMAPINFO*)(pData+sizeof(BITMAPFILEHEADER));
		pData+=pFile->bfOffBits;
		// scale it
		StretchDIBits(pDC->m_hDC,
			left,top,width,height,
			0,0,pInfo->bmiHeader.biWidth, pInfo->bmiHeader.biHeight,
			pData,pInfo,DIB_RGB_COLORS,SRCCOPY);
	}	

}

void CThumbnail::OnPaint() 
{
	PAINTSTRUCT paintstruct;
	CDC* pDC;
	pDC=BeginPaint(&paintstruct);
	paintstruct.fErase=TRUE;
	CRect rect;
	GetClientRect(rect);
	// first draw scaled version of thumbnail underneath title bar
	CRButton* button;
	button=GETDLGITEM(IDJ_TITLE);
	CRect buttonrect;
	button->GetClientRect(buttonrect);
	rect.top+=buttonrect.bottom;
	// +1 prevents gaps
	int halfheight=rect.Height()/2+1;
	int offset=rect.Height()/8+1;
	int offset2=rect.Height()/16+1;
	DrawScaledBitmap(pDC,FIL_THUMBTOP,rect.left,rect.top-offset,rect.Width(),halfheight+offset2);
	DrawScaledBitmap(pDC,FIL_THUMBBOT,rect.left,rect.top+halfheight-offset2,rect.Width(),halfheight+offset2);
	// now draw the box in the appropriate position
	CRect rect2;
	m_pView->GetClientRect(rect2);
	m_boxSize=CSize((rect.right*rect2.right)/m_pView->m_size.cx,
					(rect.Height()*rect2.bottom)/m_pView->m_size.cy);
	if(m_LButtonDown==FALSE)
	{
		m_point=CPoint(((m_pView->m_scrollpoint.x*rect.right)/m_pView->m_size.cx)+(m_boxSize.cx/2),
					   ((m_pView->m_scrollpoint.y*rect.Height())/m_pView->m_size.cy)+(m_boxSize.cy/2)+rect.top);
		m_point=m_point+offsetfix;			//quick thumbnail fix
	}
	m_point.x=max(m_boxSize.cx/2,m_point.x);
	m_point.y=max((m_boxSize.cy/2)+rect.top,m_point.y);
	m_point.x=min(rect.right-(m_boxSize.cx/2),m_point.x);
	m_point.y=min(rect.bottom-(m_boxSize.cy/2),m_point.y);
	CPen pen;
	pen.CreatePen(PS_SOLID,2,RGB(255,0,0)); // red pen
	pDC->SelectObject(&pen);

	if (m_boxSize.cx<20) 
	{
		pDC->MoveTo(m_point.x-10,m_point.y);
		pDC->LineTo(m_point.x-m_boxSize.cx/2,m_point.y);
		pDC->MoveTo(m_point.x+10,m_point.y);
		pDC->LineTo(m_point.x+m_boxSize.cx/2,m_point.y);
	}
	if (m_boxSize.cy<20)
	{
		pDC->MoveTo(m_point.x,m_point.y-10);
		pDC->LineTo(m_point.x,m_point.y-m_boxSize.cy/2);
		pDC->MoveTo(m_point.x,m_point.y+10);
		pDC->LineTo(m_point.x,m_point.y+m_boxSize.cy/2);
	}
	pDC->MoveTo(m_point.x-(m_boxSize.cx/2),m_point.y-(m_boxSize.cy/2));
	pDC->LineTo(m_point.x+(m_boxSize.cx/2),m_point.y-(m_boxSize.cy/2));
	pDC->LineTo(m_point.x+(m_boxSize.cx/2),m_point.y+(m_boxSize.cy/2));
	pDC->LineTo(m_point.x-(m_boxSize.cx/2),m_point.y+(m_boxSize.cy/2));
	pDC->LineTo(m_point.x-(m_boxSize.cx/2),m_point.y-(m_boxSize.cy/2));
	EndPaint(&paintstruct);
}

void CThumbnail::InvalidateMapOnly()
{
	CRect rect;
	GetClientRect(rect);
	CRButton* button;
	button=GETDLGITEM(IDJ_TITLE);
	CRect buttonrect;
	button->GetClientRect(buttonrect);
	rect.top=buttonrect.bottom;
	InvalidateRect(rect);
}

void CThumbnail::UpdateView()
{
//	if (m_pView->m_drawing) return;
	CRect rect;
	GetClientRect(rect);
	CRButton* button;
	button=GETDLGITEM(IDJ_TITLE);
	CRect buttonrect;
	button->GetClientRect(buttonrect);
	rect.top=buttonrect.bottom;
//	CPoint oldscrollpoint=m_pView->m_scrollpoint;
	m_pView->m_scrollpoint=CPoint((((m_point.x-(m_boxSize.cx/2))*m_pView->m_size.cx)/rect.right)+1,
								  (((m_point.y-(m_boxSize.cy/2)-rect.top)*m_pView->m_size.cy)/(rect.Height()))+1);
	if (m_pView->m_scrollpoint.x<0) m_pView->m_scrollpoint.x=0;
	if (m_pView->m_scrollpoint.y<0) m_pView->m_scrollpoint.y=0;
//	if (m_pView->m_scrollpoint!=oldscrollpoint)
//	{
//		m_pView->m_drawing=TRUE;
//		m_pView->UpdateScrollbars();
//		m_pView->m_mapdlg.ScrollWindow(oldscrollpoint.x-m_pView->m_scrollpoint.x,oldscrollpoint.y-m_pView->m_scrollpoint.y);
//	}
	m_pView->m_mapdlg.Invalidate();
	m_pView->UpdateScrollbars();
}
