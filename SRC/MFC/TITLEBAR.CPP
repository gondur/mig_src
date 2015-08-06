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

// TitleBar.cpp : implementation file
//

#include "stdafx.h"
#include "mig.h"
#include "TitleBar.h"
#include "migview.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#ifndef THIS_FILE_DEFINED
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif
/////////////////////////////////////////////////////////////////////////////
// TitleBar dialog

TitleBar::TitleBar(CWnd* pParent /*=NULL*/)
	: CRToolBar(pParent)
{
	//{{AFX_DATA_INIT(TitleBar)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}
void TitleBar::Redraw()
{
	CRButton*   b;
	b=GETDLGITEM(IDC_DATE);
	b->SetString(GetDateName(MMC.currdate, DATE_SHORT) + ": "+ RESLIST(MORNING,MMC.debrief.currperiod)
				+ ", " + RESLIST(PLANNING,MMC.indebrief));
	Invalidate();													  //RDH 11/06/99

}

void TitleBar::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	//{{AFX_DATA_MAP(TitleBar)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	DDX_Control(pDX,IDC_TITLE,m_IDC_TITLE);
	DDX_Control(pDX,IDC_DATE,m_IDC_DATE);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(TitleBar, CRToolBar)
	//{{AFX_MSG_MAP(TitleBar)
//	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
	ON_MESSAGE( WM_GETARTWORK, OnGetArt)
	ON_MESSAGE( WM_GETXYOFFSET, OnGetXYOffset)
	ON_MESSAGE( WM_GETGLOBALFONT, OnGetGlobalFont)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// TitleBar message handlers
FileNum TitleBar::OnGetArt()
{
	return FIL_TOOL_HORIZONTAL;
}
long TitleBar::OnGetXYOffset()
{
	short offsetx=0;
	short offsety=0;
	return offsetx+(offsety<<16);
}
CFont* TitleBar::OnGetGlobalFont(int fontnum)
{
    if (fontnum<0||fontnum>MAXFONTS)
		fontnum=0;
//	if (RDialog::m_scalingfactor>1.5) 
//		return RDialog::g_AllFonts[fontnum][3];
//	else 
		return g_AllFonts[fontnum][0];
}

void TitleBar::OnPaint() 
{
}

BOOL TitleBar::OnEraseBkgnd(CDC* pDC) 
{	//STOLEN FROM RTOOLBAR.CPP
	CRect rect;
	GetWindowRect(rect);
	CRect viewrect;
	m_pFrame->GetWindowRect(viewrect);
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
			if (m_index>-1) // offset the artwork if docked
			{
				if (m_bHorzAlign)
					xoffset=viewrect.right-rect.left-pInfo->bmiHeader.biWidth;
				else
					yoffset=viewrect.bottom-rect.top-pInfo->bmiHeader.biHeight;
				if (m_align==1)
				{
					yoffset=-m_row*46;
//					if (m_row==0)
//					{
//						CRect rect3;
//						m_pFrame->m_wndSystemBox->GetWindowRect(rect3);
//						xoffset+=rect3.Width();
//					}
				}
				if (m_align==3)
					yoffset=(m_row-2)*46;
				m_xoffset=xoffset;
				m_yoffset=yoffset;
			}
			else
			{
				xoffset=m_xoffset;
				yoffset=m_yoffset;
			}
			SetDIBitsToDevice(pDC->m_hDC,xoffset,yoffset,pInfo->bmiHeader.biWidth, pInfo->bmiHeader.biHeight,
				0,0,0,pInfo->bmiHeader.biHeight,pData,pInfo,DIB_RGB_COLORS);
			COLORREF	rgb=RGB(66,75,99);
			if (yoffset>0)
				pDC->FillSolidRect(0,0,rect.Width(),yoffset,rgb);
			if (pInfo->bmiHeader.biHeight+yoffset<rect.Height())
				if (pInfo->bmiHeader.biHeight+yoffset<<0)
					pDC->FillSolidRect(0,0,rect.Width(),rect.Height(),rgb);
				else
					pDC->FillSolidRect(0,pInfo->bmiHeader.biHeight+yoffset,rect.Width(),rect.Height(),rgb);
			if (xoffset>0)
				pDC->FillSolidRect(0,0,xoffset,rect.Height(),rgb);
			if (pInfo->bmiHeader.biWidth+xoffset<rect.Width())
				if (pInfo->bmiHeader.biWidth+xoffset<0)
					pDC->FillSolidRect(0,0,rect.Width(),rect.Height(),rgb);
				else
					pDC->FillSolidRect(pInfo->bmiHeader.biWidth+xoffset,0,rect.Width(),rect.Height(),RGB(78,100,78));
		}
	}

	return TRUE;
}
