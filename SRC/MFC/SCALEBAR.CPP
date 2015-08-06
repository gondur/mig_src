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

// ScaleBar.cpp : implementation file
//

#include "stdafx.h"
#include "mig.h"
#include "ScaleBar.h"
#include "migview.h"
#include "mainfrm.h"
#include "savegame.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#ifndef THIS_FILE_DEFINED
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif

/////////////////////////////////////////////////////////////////////////////
// CScaleBar dialog


CScaleBar::CScaleBar(CWnd* pParent /*=NULL*/)
	: CRToolBar(pParent)
{
	//{{AFX_DATA_INIT(CScaleBar)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_RButtonDown=FALSE;
}


void CScaleBar::DoDataExchange(CDataExchange* pDX)
{
	CRToolBar::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CScaleBar)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CScaleBar, CRToolBar)
	//{{AFX_MSG_MAP(CScaleBar)
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_SIZE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CScaleBar message handlers

BOOL CScaleBar::OnEraseBkgnd(CDC* pDC) 
{
	return TRUE;
}

void CScaleBar::OnSize(UINT nType, int cx, int cy) 
{
	CRToolBar::OnSize(nType, cx, cy);
	Invalidate();
}

void CScaleBar::OnPaint() 
{
	if (m_init) return;
	PAINTSTRUCT paintstruct;
	CDC* pDC;
	pDC=this->BeginPaint(&paintstruct);
    pDC->SetBkMode(TRANSPARENT);
    pDC->SetTextColor(RGB(255,255,255));
	pDC->SelectStockObject(WHITE_PEN);
	CRect rect;
	this->GetClientRect(rect);
	if (m_bHorzAlign) rect.left+=25;
	else rect.top+=25;
//	m_pView->m_pDialogBar = this;
	int counter;
	char string[10];
	#define zoom m_pView->m_zoom
	// a nice black background
	pDC->FillRect(rect, CBrush::FromHandle((HBRUSH)GetStockObject(BLACK_BRUSH)));
	float grad_10 = zoom * Save_Data.dist.longcm * 10 /65536;
	float grad_1 = grad_10/10;
	float grad_tenth = grad_10/ 100;
	if (m_align==3)
	{
		pDC->SetTextAlign(TA_CENTER | TA_TOP | TA_NOUPDATECP);
		pDC->MoveTo(CPoint(30,2));
		pDC->LineTo(CPoint(rect.right-5,2)); // line at top of scale
		// first draw in 10 mile seperators these are always present
		counter=0;
		for (float x=30;x<rect.right-5;x+=grad_10)
		{
			pDC->MoveTo(CPoint(x,2));
			pDC->LineTo(CPoint(x,15));
			// and the corresponding number
			if (counter%5==0)
			{
				if (counter%20==0 || (counter%10==0 && zoom>0.5) || zoom>=1.5)
				{
//DEADCODE DAW 07/05/99 					if (counter==0)
//DEADCODE DAW 07/05/99 						sprintf(string,"0 %s",);
//DEADCODE DAW 07/05/99 					else
						sprintf(string,"%d",counter*10);
					pDC->TextOut(x,15,string);
					if (counter==0)
						pDC->TextOut(x,30,LoadResString(Save_Data.dist.longabbr));
				}
			}
			counter++;
		}
		// now 1 mile seperators
		if (zoom>=4)
		{
			counter=0;
			for (float x=30;x<rect.right-5;x+=grad_1)
			{
				if (counter%10>0)
				{
					pDC->MoveTo(CPoint(x,2));
					pDC->LineTo(CPoint(x,12));
				}
				if (counter%10==0 || (counter%5==0 && zoom>=8))
				{
					if (counter%50>0)
					{
						sprintf(string,"%d",counter);
						pDC->TextOut(x,15,string);
					}
				}
				counter++;
			}
		}
		// now 1/10 mile seperators
		if (m_pView->m_zoom>=32)
		{
			counter=0;
			for (float x=30;x<rect.right-5;x+=grad_tenth)
			{
				if (counter%10>0)
				{
					pDC->MoveTo(CPoint(x,2));
					pDC->LineTo(CPoint(x,10));
				}
				else if (counter%50>0)
				{
				sprintf(string,"%d",counter/10);
				pDC->TextOut(x,15,string);
				}
				counter++;
			}
		}
	}
	else if (m_align==1)
	{
		pDC->SetTextAlign(TA_CENTER | TA_TOP | TA_NOUPDATECP);
		pDC->MoveTo(CPoint(30,m_width-3));
		pDC->LineTo(CPoint(rect.right-5,m_width-3)); // line at bottom of scale
		// first draw in 10 mile seperators these are always present
		counter=0;
		for (float x=30;x<rect.right-5;x+=grad_10)
		{
			pDC->MoveTo(CPoint(x,m_width-2));
			pDC->LineTo(CPoint(x,m_width-15));
			// and the corresponding number
			if (counter%5==0)
			{
				if (counter%20==0 || (counter%10==0 && zoom>0.5) || zoom>=1.5)
				{
//DEADCODE DAW 07/05/99 					if (counter==0)
//DEADCODE DAW 07/05/99 						sprintf(string,"0\n%s",);
//DEADCODE DAW 07/05/99 					else
						sprintf(string,"%d",counter*10);
					pDC->TextOut(x,0,string);
					if (counter==0)
						pDC->TextOut(x,15,LoadResString(Save_Data.dist.longabbr));
				}
			}
			counter++;
		}
		// now 1 mile seperators
		if (zoom>=4)
		{
			counter=0;
			for (float x=30;x<rect.right-5;x+=grad_1)
			{
				if (counter%10>0)
				{
					pDC->MoveTo(CPoint(x,m_width-2));
					pDC->LineTo(CPoint(x,m_width-12));
				}
				if (counter%10==0 || (counter%5==0 && zoom>=8))
				{
					if (counter%50>0)
					{
						sprintf(string,"%d",counter);
						pDC->TextOut(x,0,string);
					}
				}
				counter++;
			}
		}
		// now 1/10 mile seperators
		if (m_pView->m_zoom>=32)
		{
			counter=0;
			for (float x=30;x<rect.right-5;x+=grad_tenth)
			{
				if (counter%10>0)
				{
					pDC->MoveTo(CPoint(x,m_width-2));
					pDC->LineTo(CPoint(x,m_width-10));
				}
				else if (counter%50>0)
				{
				sprintf(string,"%d",counter/10);
				pDC->TextOut(x,0,string);
				}
				counter++;
			}
		}
	}
	else if (m_align==2)
	{
		CFont* pfont;
		pfont = pDC->GetCurrentFont();
		LOGFONT logfont;
		pfont->GetLogFont(&logfont);
		int offset=logfont.lfHeight/2;
		pDC->SetTextAlign(TA_LEFT | TA_TOP | TA_NOUPDATECP);
		pDC->MoveTo(CPoint(2,offset+25));
		pDC->LineTo(CPoint(2,rect.bottom-offset)); // line at top of scale
		// first draw in 10 mile seperators these are always present
		counter=0;
		for (float x=offset+25;x<rect.bottom-offset;x+=grad_10)
		{
			pDC->MoveTo(CPoint(2,x));
			pDC->LineTo(CPoint(15,x));
			if (counter%5==0)
			{
				if (counter%20==0 || (counter%10==0 && zoom>0.5) || zoom>=1.5)
				{
					if (counter==0)
						sprintf(string,"0 %s",LoadResString(Save_Data.dist.longabbr));
					else
						sprintf(string,"%d",counter*10);
					pDC->TextOut(15,x-offset,string);
				}
			}
			counter++;
		}
		// now 1 mile seperators
		if (zoom>=4)
		{
			counter=0;
			for (float x=offset+25;x<rect.bottom-offset;x+=grad_1)
			{
				if (counter%10>0)
				{
					pDC->MoveTo(CPoint(2,x));
					pDC->LineTo(CPoint(12,x));
				}
				if (counter%10==0 || (counter%5==0 && zoom>=8))
				{
					if (counter%50>0)
					{
						sprintf(string,"%d",counter);
						pDC->TextOut(15,x-offset,string);
					}
				}
				counter++;
			}
		}

		// now 1/10 mile seperators
		if (m_pView->m_zoom>=32)
		{
			counter=0;
			for (float x=offset+25;x<rect.bottom-offset;x+=grad_tenth)
			{
				if (counter%10>0)
				{
					pDC->MoveTo(CPoint(2,x));
					pDC->LineTo(CPoint(10,x));
				}
				else if (counter%50>0)
				{
				sprintf(string,"%d",counter/10);
				pDC->TextOut(15,x-offset,string);
				}
				counter++;
			}
		}
	}
	else if (m_align==4)
	{
		CFont* pfont;
		pfont = pDC->GetCurrentFont();
		LOGFONT logfont;
		pfont->GetLogFont(&logfont);
		int offset=logfont.lfHeight/2;
		pDC->SetTextAlign(TA_RIGHT | TA_TOP | TA_NOUPDATECP);
		pDC->MoveTo(CPoint(m_width-2,offset+25));
		pDC->LineTo(CPoint(m_width-2,rect.bottom-offset)); // line at top of scale
		// first draw in 10 mile seperators these are always present
		counter=0;
		for (float x=offset+25;x<rect.bottom-offset;x+=grad_10)
		{
			pDC->MoveTo(CPoint(m_width-2,x));
			pDC->LineTo(CPoint(m_width-15,x));
			if (counter%5==0)
			{
				if (counter%20==0 || (counter%10==0 && zoom>0.5) || grad_10>10)
				{
					if (counter==0)
						sprintf(string,"0 %s",LoadResString(Save_Data.dist.longabbr));
					else
						sprintf(string,"%d",counter*10);
					pDC->TextOut(m_width-15,x-offset,string);
				}
			}
			counter++;
		}
		// now 1 mile seperators
		if (grad_10>=50)
		{
			counter=0;
			for (float x=offset+25;x<rect.bottom-offset;x+=grad_1)
			{
				if (counter%10>0)
				{
					pDC->MoveTo(CPoint(m_width-2,x));
					pDC->LineTo(CPoint(m_width-12,x));
				}
				if (counter%10==0 || (counter%5==0 && grad_10>=100))
				{
					if (counter%50>0)
					{
						sprintf(string,"%d",counter);
						pDC->TextOut(m_width-15,x-offset,string);
					}
				}
				counter++;
			}
		}

		// now 1/10 mile seperators
		if (grad_10>=500)
		{
			counter=0;
			for (float x=offset+25;x<rect.bottom-offset;x+=grad_tenth)
			{
				if (counter%10>0)
				{
					pDC->MoveTo(CPoint(m_width-2,x));
					pDC->LineTo(CPoint(m_width-10,x));
				}
				else if (counter%50>0)
				{
				sprintf(string,"%d",counter/10);
				pDC->TextOut(m_width-15,x-offset,string);
				}
				counter++;
			}
		}
	}
//	pDC->DrawEdge(&rect,EDGE_ETCHED,BF_RECT); // border
	this->EndPaint(&paintstruct);
}

void CScaleBar::OnRButtonDown(UINT nFlags, CPoint point) 
{
	CRToolBar::OnRButtonDown(nFlags, point);
}

void CScaleBar::OnRButtonUp(UINT nFlags, CPoint point) 
{
	CRToolBar::OnRButtonUp(nFlags, point);
}

void CScaleBar::OnMouseMove(UINT nFlags, CPoint point) 
{
	if (m_RButtonDown)
	{
		if (m_bHorzAlign)
			m_pView->m_zoom=((point.x-25)*m_oldzoom)/(m_oldPoint.x-25);
		else
			m_pView->m_zoom=((point.y-25)*m_oldzoom)/(m_oldPoint.y-25);
		if (m_pView->m_zoom<ZOOMMIN) 
			m_pView->m_zoom=ZOOMMIN;
		else 
			if (m_pView->m_zoom>ZOOMMAX) 
				m_pView->m_zoom=ZOOMMAX;
			else
			{
//				m_oldPoint=point;
//				m_oldzoom=m_pView->m_zoom;
			}
//		TRACE1("Redrawing! %f!",m_pView->m_zoom);
		RedrawWindow();
//	CRect rect;														  //JIM 08/05/99
//	m_pView->GetClientRect(rect);
//	m_pView->Zoom(CPoint(rect.right/2,rect.bottom/2),false);
//		TRACE1("Finished! %f\n",m_pView->m_zoom);

	}
	CRToolBar::OnMouseMove(nFlags, point);
}

void CScaleBar::OnLButtonDown(UINT nFlags, CPoint point) 
{
	if ((m_bHorzAlign && point.x<25) ||
		(!m_bHorzAlign && point.y<25))
	{
		CRToolBar::OnLButtonDown(nFlags, point);
	}
	else
	{
		m_RButtonDown=TRUE;
		this->SetCapture();
		m_oldPoint=point;
		m_oldzoom=m_pView->m_zoom;
	}
}

void CScaleBar::OnLButtonUp(UINT nFlags, CPoint point) 
{
	m_RButtonDown=FALSE;
	ReleaseCapture(); 	
	CRect rect;
	m_pView->GetClientRect(rect);
	m_pView->Zoom(CPoint(rect.right/2,rect.bottom/2));

	CRToolBar::OnLButtonUp(nFlags, point);
}
