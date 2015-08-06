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

//DEADCODE DAW 08/05/99 // ResizableDlgBar.cpp : implementation file
//DEADCODE DAW 08/05/99 //
//DEADCODE DAW 08/05/99 
//DEADCODE DAW 08/05/99 #include "stdafx.h"
//DEADCODE DAW 08/05/99 #include "MIG.h"
//DEADCODE DAW 08/05/99 #include "RDlgBar.h"
//DEADCODE DAW 08/05/99 #include "MIGView.h"
//DEADCODE DAW 08/05/99 #include "MainFrm.h"
//DEADCODE DAW 08/05/99 #include <afxpriv.h>
//DEADCODE DAW 08/05/99 
//DEADCODE DAW 08/05/99 #ifdef _DEBUG
//DEADCODE DAW 08/05/99 #define new DEBUG_NEW
//DEADCODE DAW 08/05/99 #ifndef	THIS_FILE_DEFINED
//DEADCODE DAW 08/05/99 #undef THIS_FILE
//DEADCODE DAW 08/05/99 static char THIS_FILE[] = __FILE__;
//DEADCODE DAW 08/05/99 #endif
//DEADCODE DAW 08/05/99 #endif
//DEADCODE DAW 08/05/99 
//DEADCODE DAW 08/05/99 /////////////////////////////////////////////////////////////////////
//DEADCODE DAW 08/05/99 
//DEADCODE DAW 08/05/99 BOOL CResizableDlgBar::Create( CWnd* pParentWnd, UINT nIDTemplate, 
//DEADCODE DAW 08/05/99                                UINT nStyle, UINT nID)
//DEADCODE DAW 08/05/99 {
//DEADCODE DAW 08/05/99 	if(!CDialogBar::Create(pParentWnd,nIDTemplate,nStyle,nID))
//DEADCODE DAW 08/05/99           return FALSE;
//DEADCODE DAW 08/05/99 	m_pParent = (CMainFrame*)pParentWnd;
//DEADCODE DAW 08/05/99 	CDC* pDC;
//DEADCODE DAW 08/05/99 	pDC=m_pParent->GetDC();
//DEADCODE DAW 08/05/99 	// using parents DC since this DC doesnt exist yet and text font
//DEADCODE DAW 08/05/99 	// should be identical in both.
//DEADCODE DAW 08/05/99 	CSize textsize;
//DEADCODE DAW 08/05/99 	textsize=pDC->GetTextExtent("1000");
//DEADCODE DAW 08/05/99 	m_iFixedWidth=15+textsize.cx; // scale is 15 pixels wide
//DEADCODE DAW 08/05/99 	m_iFixedHeight=15+textsize.cy;
//DEADCODE DAW 08/05/99 	m_RButtonDown=FALSE;
//DEADCODE DAW 08/05/99 	m_iBarLength=200;
//DEADCODE DAW 08/05/99 	m_bHorzAlign=FALSE;
//DEADCODE DAW 08/05/99 	return TRUE;
//DEADCODE DAW 08/05/99 }
//DEADCODE DAW 08/05/99 
//DEADCODE DAW 08/05/99 BOOL CResizableDlgBar::Create( CWnd* pParentWnd, 
//DEADCODE DAW 08/05/99 
//DEADCODE DAW 08/05/99                                LPCTSTR lpszTemplateName, UINT nStyle,
//DEADCODE DAW 08/05/99                                UINT nID)
//DEADCODE DAW 08/05/99 {
//DEADCODE DAW 08/05/99     if (!CDialogBar::Create( pParentWnd, lpszTemplateName,
//DEADCODE DAW 08/05/99                                               nStyle, nID))
//DEADCODE DAW 08/05/99         return FALSE;
//DEADCODE DAW 08/05/99 	m_pParent = (CMainFrame*)pParentWnd; 
//DEADCODE DAW 08/05/99 	CDC* pDC;
//DEADCODE DAW 08/05/99 	pDC=m_pParent->GetDC();
//DEADCODE DAW 08/05/99 	CSize textsize;
//DEADCODE DAW 08/05/99 	textsize=pDC->GetTextExtent("1000");
//DEADCODE DAW 08/05/99 	m_iFixedWidth=15+textsize.cx; // scale is 15 pixels wide
//DEADCODE DAW 08/05/99 	m_iFixedHeight=15+textsize.cy;
//DEADCODE DAW 08/05/99 	m_RButtonDown=FALSE;
//DEADCODE DAW 08/05/99 	m_iBarLength=400;
//DEADCODE DAW 08/05/99     return TRUE;
//DEADCODE DAW 08/05/99 } 
//DEADCODE DAW 08/05/99 
//DEADCODE DAW 08/05/99 
//DEADCODE DAW 08/05/99 
//DEADCODE DAW 08/05/99 ////////////////////////////////////////////////////////////////////
//DEADCODE DAW 08/05/99 // Overloaded functions
//DEADCODE DAW 08/05/99 
//DEADCODE DAW 08/05/99 CSize CResizableDlgBar::CalcDynamicLayout(int nLength, DWORD dwMode)
//DEADCODE DAW 08/05/99 {
//DEADCODE DAW 08/05/99 	CFrameWnd* pDockFrame = m_pDockBar->GetParentFrame();
//DEADCODE DAW 08/05/99 	pDockFrame->ModifyStyle(WS_CAPTION,0); // Bye bye title bar
//DEADCODE DAW 08/05/99 	this->ModifyStyle(WS_CAPTION,0); // Bye bye title bar
//DEADCODE DAW 08/05/99 	m_pDockBar->ModifyStyle(WS_CAPTION,0); // Bye bye title bar
//DEADCODE DAW 08/05/99 
//DEADCODE DAW 08/05/99 //	pDockFrame->ModifyStyle(pDockFrame->GetStyle(),WS_CHILD | WS_VISIBLE | WS_THICKFRAME); // Bye bye title bar
//DEADCODE DAW 08/05/99 //	this->ModifyStyle(this->GetStyle(),WS_CHILD | WS_VISIBLE | WS_THICKFRAME); // Bye bye title bar
//DEADCODE DAW 08/05/99 //	m_pDockBar->ModifyStyle(m_pDockBar->GetStyle(),WS_CHILD | WS_VISIBLE | WS_THICKFRAME); // Bye bye title bar
//DEADCODE DAW 08/05/99 
//DEADCODE DAW 08/05/99 	CMIGView* pView = (CMIGView*)(m_pParent->GetActiveView());
//DEADCODE DAW 08/05/99 	CRect rect;
//DEADCODE DAW 08/05/99 	pView->GetWindowRect(rect);
//DEADCODE DAW 08/05/99 	CRect rect2;
//DEADCODE DAW 08/05/99 	this->GetWindowRect(rect2);
//DEADCODE DAW 08/05/99 	if (rect.left<=rect2.left || rect.top<=rect2.top)
//DEADCODE DAW 08/05/99 	{
//DEADCODE DAW 08/05/99 		if (rect.left>rect2.left)
//DEADCODE DAW 08/05/99 		{							//	1
//DEADCODE DAW 08/05/99 			m_bHorzAlign=FALSE;		// 4 2
//DEADCODE DAW 08/05/99 			m_iAlign=4;				//	3
//DEADCODE DAW 08/05/99 		}
//DEADCODE DAW 08/05/99 		if (rect.top>rect2.top)
//DEADCODE DAW 08/05/99 		{
//DEADCODE DAW 08/05/99 			m_bHorzAlign=TRUE;
//DEADCODE DAW 08/05/99 			m_iAlign=1;
//DEADCODE DAW 08/05/99 		}
//DEADCODE DAW 08/05/99 	}
//DEADCODE DAW 08/05/99 	if (rect.right>=rect2.left+m_iFixedWidth || rect.bottom>=rect2.top+m_iFixedHeight)
//DEADCODE DAW 08/05/99 	{
//DEADCODE DAW 08/05/99 		if (rect.right<rect2.left+m_iFixedWidth)
//DEADCODE DAW 08/05/99 		{							//	1
//DEADCODE DAW 08/05/99 			m_bHorzAlign=FALSE;		// 4 2
//DEADCODE DAW 08/05/99 			m_iAlign=2;				//	3
//DEADCODE DAW 08/05/99 		}
//DEADCODE DAW 08/05/99 		if (rect.bottom<rect2.top+m_iFixedHeight)
//DEADCODE DAW 08/05/99 		{
//DEADCODE DAW 08/05/99 			m_bHorzAlign=TRUE;
//DEADCODE DAW 08/05/99 			m_iAlign=3;
//DEADCODE DAW 08/05/99 		}
//DEADCODE DAW 08/05/99 	}
//DEADCODE DAW 08/05/99 
//DEADCODE DAW 08/05/99     if ((dwMode & LM_VERTDOCK) || (dwMode & LM_HORZDOCK)) // its asking for docked size
//DEADCODE DAW 08/05/99     {
//DEADCODE DAW 08/05/99 		if (dwMode & LM_HORZ)
//DEADCODE DAW 08/05/99 		{
//DEADCODE DAW 08/05/99             return CSize(m_iBarLength,m_iFixedHeight);
//DEADCODE DAW 08/05/99 		}
//DEADCODE DAW 08/05/99 		else
//DEADCODE DAW 08/05/99 		{
//DEADCODE DAW 08/05/99 			return CSize(m_iFixedWidth,m_iBarLength);
//DEADCODE DAW 08/05/99 		}
//DEADCODE DAW 08/05/99 	}
//DEADCODE DAW 08/05/99 	// first check if it merely wants to know what the previous size was
//DEADCODE DAW 08/05/99     if (dwMode & LM_MRUWIDTH)
//DEADCODE DAW 08/05/99 	{
//DEADCODE DAW 08/05/99 		if (m_bHorzAlign) return CSize(m_iBarLength,m_iFixedHeight);
//DEADCODE DAW 08/05/99 		else return CSize(m_iFixedWidth,m_iBarLength);
//DEADCODE DAW 08/05/99 	}
//DEADCODE DAW 08/05/99 	// ok attempting to resize and nLength holds the new size.
//DEADCODE DAW 08/05/99     if (dwMode & LM_LENGTHY) // attempting to resize in y direction
//DEADCODE DAW 08/05/99 	{
//DEADCODE DAW 08/05/99 		if (!m_bHorzAlign)
//DEADCODE DAW 08/05/99 		{
//DEADCODE DAW 08/05/99 			m_iBarLength=nLength;
//DEADCODE DAW 08/05/99 			return CSize(m_iFixedWidth,m_iBarLength);
//DEADCODE DAW 08/05/99 		}
//DEADCODE DAW 08/05/99 		return CSize(m_iBarLength,m_iFixedHeight);
//DEADCODE DAW 08/05/99 	}
//DEADCODE DAW 08/05/99 	else
//DEADCODE DAW 08/05/99 	{
//DEADCODE DAW 08/05/99 		if (m_bHorzAlign)
//DEADCODE DAW 08/05/99 		{
//DEADCODE DAW 08/05/99 			m_iBarLength=nLength;
//DEADCODE DAW 08/05/99 			return CSize(m_iBarLength,m_iFixedHeight);
//DEADCODE DAW 08/05/99 		}
//DEADCODE DAW 08/05/99 		return CSize(m_iFixedWidth,m_iBarLength);	
//DEADCODE DAW 08/05/99 	}
//DEADCODE DAW 08/05/99 }
//DEADCODE DAW 08/05/99 /*
//DEADCODE DAW 08/05/99 CSize CResizableDlgBar::CalcDynamicLayout(int nLength, DWORD dwMode) { 
//DEADCODE DAW 08/05/99 	// most of this code is stolen off an example in MSDN
//DEADCODE DAW 08/05/99     // Return default if it is being docked or floated
//DEADCODE DAW 08/05/99     if ((dwMode & LM_VERTDOCK) || (dwMode & LM_HORZDOCK))
//DEADCODE DAW 08/05/99     {
//DEADCODE DAW 08/05/99         if (dwMode & LM_STRETCH) // if not docked stretch to fit
//DEADCODE DAW 08/05/99             return CSize((dwMode & LM_HORZ) ? 32767 : m_sizeDocked.cx,
//DEADCODE DAW 08/05/99                          (dwMode & LM_HORZ) ? m_sizeDocked.cy : 32767);
//DEADCODE DAW 08/05/99         else
//DEADCODE DAW 08/05/99 		if (dwMode & LM_HORZ)
//DEADCODE DAW 08/05/99 		{
//DEADCODE DAW 08/05/99 			m_bHorzAlign=TRUE;
//DEADCODE DAW 08/05/99             return m_sizeDocked;
//DEADCODE DAW 08/05/99 		}
//DEADCODE DAW 08/05/99 		else
//DEADCODE DAW 08/05/99 		{
//DEADCODE DAW 08/05/99 			m_bHorzAlign=FALSE;
//DEADCODE DAW 08/05/99 			return CSize(m_sizeDocked.cy+10,m_sizeDocked.cx);
//DEADCODE DAW 08/05/99 		}
//DEADCODE DAW 08/05/99     }
//DEADCODE DAW 08/05/99 	m_bHorzAlign=TRUE;
//DEADCODE DAW 08/05/99     if (dwMode & LM_MRUWIDTH)
//DEADCODE DAW 08/05/99         return m_sizeFloating;
//DEADCODE DAW 08/05/99     // In all other cases, accept the dynamic length
//DEADCODE DAW 08/05/99     if (dwMode & LM_LENGTHY)
//DEADCODE DAW 08/05/99 //        return CSize(m_sizeFloating.cx, (m_bChangeDockedSize) ?
//DEADCODE DAW 08/05/99 //					m_sizeFloating.cy = m_sizeDocked.cy = nlength :
//DEADCODE DAW 08/05/99 //                     m_sizeFloating.cy = nLength);
//DEADCODE DAW 08/05/99 		return m_sizeFloating;
//DEADCODE DAW 08/05/99      else
//DEADCODE DAW 08/05/99         return CSize(m_sizeFloating.cx = m_sizeDocked.cx = nLength,
//DEADCODE DAW 08/05/99 					 m_sizeFloating.cy = m_sizeDocked.cy);
//DEADCODE DAW 08/05/99 }
//DEADCODE DAW 08/05/99 */
//DEADCODE DAW 08/05/99 
//DEADCODE DAW 08/05/99 BEGIN_MESSAGE_MAP(CResizableDlgBar, CDialogBar) 
//DEADCODE DAW 08/05/99 
//DEADCODE DAW 08/05/99     //{{AFX_MSG_MAP(CResizableDlgBar)
//DEADCODE DAW 08/05/99 	ON_WM_SIZE()
//DEADCODE DAW 08/05/99 	ON_WM_PAINT()
//DEADCODE DAW 08/05/99 	ON_WM_RBUTTONDOWN()
//DEADCODE DAW 08/05/99 	ON_WM_RBUTTONUP()
//DEADCODE DAW 08/05/99 	ON_WM_MOUSEMOVE()
//DEADCODE DAW 08/05/99 	//}}AFX_MSG_MAP
//DEADCODE DAW 08/05/99 
//DEADCODE DAW 08/05/99 
//DEADCODE DAW 08/05/99 
//DEADCODE DAW 08/05/99 END_MESSAGE_MAP() 
//DEADCODE DAW 08/05/99 
//DEADCODE DAW 08/05/99 
//DEADCODE DAW 08/05/99 
//DEADCODE DAW 08/05/99 /////////////////////////////////////////////////////////////////////
//DEADCODE DAW 08/05/99 // CResizableDlgBar message handlers
//DEADCODE DAW 08/05/99 /////////////////////////////////////////////////////////////////////
//DEADCODE DAW 08/05/99 
//DEADCODE DAW 08/05/99 void CResizableDlgBar::OnSize(UINT nType, int cx, int cy) 
//DEADCODE DAW 08/05/99 {
//DEADCODE DAW 08/05/99 	CDialogBar::OnSize(nType, cx, cy);
//DEADCODE DAW 08/05/99 	this->RedrawWindow();
//DEADCODE DAW 08/05/99 }
//DEADCODE DAW 08/05/99 
//DEADCODE DAW 08/05/99 void CResizableDlgBar::OnPaint() 
//DEADCODE DAW 08/05/99 {
//DEADCODE DAW 08/05/99 //	CDialogBar::OnPaint();	// Draws Box.
//DEADCODE DAW 08/05/99 	PAINTSTRUCT paintstruct;
//DEADCODE DAW 08/05/99 	CDC* pDC;
//DEADCODE DAW 08/05/99 	pDC=this->BeginPaint(&paintstruct);
//DEADCODE DAW 08/05/99 	pDC->SetBkColor(GetSysColor(COLOR_MENU)); // fixes white background on numbers bug
//DEADCODE DAW 08/05/99 	CRect rect;
//DEADCODE DAW 08/05/99 	this->GetClientRect(rect);
//DEADCODE DAW 08/05/99 	CMIGView* pView;
//DEADCODE DAW 08/05/99 	pView = (CMIGView*)(m_pParent->GetActiveView());
//DEADCODE DAW 08/05/99 //	pView->m_pDialogBar = this;
//DEADCODE DAW 08/05/99 	int counter;
//DEADCODE DAW 08/05/99 	char string[10];
//DEADCODE DAW 08/05/99 	float zoom = pView->m_zoom;
//DEADCODE DAW 08/05/99 	if (m_iAlign==3)
//DEADCODE DAW 08/05/99 	{
//DEADCODE DAW 08/05/99 		pDC->SetTextAlign(TA_CENTER | TA_TOP | TA_NOUPDATECP);
//DEADCODE DAW 08/05/99 		pDC->MoveTo(CPoint(5,2));
//DEADCODE DAW 08/05/99 		pDC->LineTo(CPoint(rect.right-5,2)); // line at top of scale
//DEADCODE DAW 08/05/99 		// first draw in 10 mile seperators these are always present
//DEADCODE DAW 08/05/99 		counter=0;
//DEADCODE DAW 08/05/99 		for (float x=5;x<rect.right-5;x+=zoom*10)
//DEADCODE DAW 08/05/99 		{
//DEADCODE DAW 08/05/99 			pDC->MoveTo(CPoint(x,2));
//DEADCODE DAW 08/05/99 			pDC->LineTo(CPoint(x,15));
//DEADCODE DAW 08/05/99 			// and the corresponding number
//DEADCODE DAW 08/05/99 			if (counter%5==0)
//DEADCODE DAW 08/05/99 			{
//DEADCODE DAW 08/05/99 				if (counter%20==0 || (counter%10==0 && zoom>0.5) || zoom>=1.5)
//DEADCODE DAW 08/05/99 				{
//DEADCODE DAW 08/05/99 					sprintf(string,"%d",counter*10);
//DEADCODE DAW 08/05/99 					pDC->TextOut(x,15,string);
//DEADCODE DAW 08/05/99 				}
//DEADCODE DAW 08/05/99 			}
//DEADCODE DAW 08/05/99 			counter++;
//DEADCODE DAW 08/05/99 		}
//DEADCODE DAW 08/05/99 		// now 1 mile seperators
//DEADCODE DAW 08/05/99 		if (zoom>=4)
//DEADCODE DAW 08/05/99 		{
//DEADCODE DAW 08/05/99 			counter=0;
//DEADCODE DAW 08/05/99 			for (float x=5;x<rect.right-5;x+=zoom)
//DEADCODE DAW 08/05/99 			{
//DEADCODE DAW 08/05/99 				if (counter%10>0)
//DEADCODE DAW 08/05/99 				{
//DEADCODE DAW 08/05/99 					pDC->MoveTo(CPoint(x,2));
//DEADCODE DAW 08/05/99 					pDC->LineTo(CPoint(x,12));
//DEADCODE DAW 08/05/99 				}
//DEADCODE DAW 08/05/99 				if (counter%10==0 || (counter%5==0 && zoom>=8))
//DEADCODE DAW 08/05/99 				{
//DEADCODE DAW 08/05/99 					if (counter%50>0)
//DEADCODE DAW 08/05/99 					{
//DEADCODE DAW 08/05/99 						sprintf(string,"%d",counter);
//DEADCODE DAW 08/05/99 						pDC->TextOut(x,15,string);
//DEADCODE DAW 08/05/99 					}
//DEADCODE DAW 08/05/99 				}
//DEADCODE DAW 08/05/99 				counter++;
//DEADCODE DAW 08/05/99 			}
//DEADCODE DAW 08/05/99 		}
//DEADCODE DAW 08/05/99 		// now 1/10 mile seperators
//DEADCODE DAW 08/05/99 		if (pView->m_zoom>=32)
//DEADCODE DAW 08/05/99 		{
//DEADCODE DAW 08/05/99 			counter=0;
//DEADCODE DAW 08/05/99 			for (float x=5;x<rect.right-5;x+=zoom/10)
//DEADCODE DAW 08/05/99 			{
//DEADCODE DAW 08/05/99 				if (counter%10>0)
//DEADCODE DAW 08/05/99 				{
//DEADCODE DAW 08/05/99 					pDC->MoveTo(CPoint(x,2));
//DEADCODE DAW 08/05/99 					pDC->LineTo(CPoint(x,10));
//DEADCODE DAW 08/05/99 				}
//DEADCODE DAW 08/05/99 				else if (counter%50>0)
//DEADCODE DAW 08/05/99 				{
//DEADCODE DAW 08/05/99 				sprintf(string,"%d",counter/10);
//DEADCODE DAW 08/05/99 				pDC->TextOut(x,15,string);
//DEADCODE DAW 08/05/99 				}
//DEADCODE DAW 08/05/99 				counter++;
//DEADCODE DAW 08/05/99 			}
//DEADCODE DAW 08/05/99 		}
//DEADCODE DAW 08/05/99 	}
//DEADCODE DAW 08/05/99 	else if (m_iAlign==1)
//DEADCODE DAW 08/05/99 	{
//DEADCODE DAW 08/05/99 		pDC->SetTextAlign(TA_CENTER | TA_TOP | TA_NOUPDATECP);
//DEADCODE DAW 08/05/99 		pDC->MoveTo(CPoint(5,m_iFixedHeight-3));
//DEADCODE DAW 08/05/99 		pDC->LineTo(CPoint(rect.right-5,m_iFixedHeight-3)); // line at bottom of scale
//DEADCODE DAW 08/05/99 		// first draw in 10 mile seperators these are always present
//DEADCODE DAW 08/05/99 		counter=0;
//DEADCODE DAW 08/05/99 		for (float x=5;x<rect.right-5;x+=zoom*10)
//DEADCODE DAW 08/05/99 		{
//DEADCODE DAW 08/05/99 			pDC->MoveTo(CPoint(x,m_iFixedHeight-2));
//DEADCODE DAW 08/05/99 			pDC->LineTo(CPoint(x,m_iFixedHeight-15));
//DEADCODE DAW 08/05/99 			// and the corresponding number
//DEADCODE DAW 08/05/99 			if (counter%5==0)
//DEADCODE DAW 08/05/99 			{
//DEADCODE DAW 08/05/99 				if (counter%20==0 || (counter%10==0 && zoom>0.5) || zoom>=1.5)
//DEADCODE DAW 08/05/99 				{
//DEADCODE DAW 08/05/99 					sprintf(string,"%d",counter*10);
//DEADCODE DAW 08/05/99 					pDC->TextOut(x,0,string);
//DEADCODE DAW 08/05/99 				}
//DEADCODE DAW 08/05/99 			}
//DEADCODE DAW 08/05/99 			counter++;
//DEADCODE DAW 08/05/99 		}
//DEADCODE DAW 08/05/99 		// now 1 mile seperators
//DEADCODE DAW 08/05/99 		if (zoom>=4)
//DEADCODE DAW 08/05/99 		{
//DEADCODE DAW 08/05/99 			counter=0;
//DEADCODE DAW 08/05/99 			for (float x=5;x<rect.right-5;x+=zoom)
//DEADCODE DAW 08/05/99 			{
//DEADCODE DAW 08/05/99 				if (counter%10>0)
//DEADCODE DAW 08/05/99 				{
//DEADCODE DAW 08/05/99 					pDC->MoveTo(CPoint(x,m_iFixedHeight-2));
//DEADCODE DAW 08/05/99 					pDC->LineTo(CPoint(x,m_iFixedHeight-12));
//DEADCODE DAW 08/05/99 				}
//DEADCODE DAW 08/05/99 				if (counter%10==0 || (counter%5==0 && zoom>=8))
//DEADCODE DAW 08/05/99 				{
//DEADCODE DAW 08/05/99 					if (counter%50>0)
//DEADCODE DAW 08/05/99 					{
//DEADCODE DAW 08/05/99 						sprintf(string,"%d",counter);
//DEADCODE DAW 08/05/99 						pDC->TextOut(x,0,string);
//DEADCODE DAW 08/05/99 					}
//DEADCODE DAW 08/05/99 				}
//DEADCODE DAW 08/05/99 				counter++;
//DEADCODE DAW 08/05/99 			}
//DEADCODE DAW 08/05/99 		}
//DEADCODE DAW 08/05/99 		// now 1/10 mile seperators
//DEADCODE DAW 08/05/99 		if (pView->m_zoom>=32)
//DEADCODE DAW 08/05/99 		{
//DEADCODE DAW 08/05/99 			counter=0;
//DEADCODE DAW 08/05/99 			for (float x=5;x<rect.right-5;x+=zoom/10)
//DEADCODE DAW 08/05/99 			{
//DEADCODE DAW 08/05/99 				if (counter%10>0)
//DEADCODE DAW 08/05/99 				{
//DEADCODE DAW 08/05/99 					pDC->MoveTo(CPoint(x,m_iFixedHeight-2));
//DEADCODE DAW 08/05/99 					pDC->LineTo(CPoint(x,m_iFixedHeight-10));
//DEADCODE DAW 08/05/99 				}
//DEADCODE DAW 08/05/99 				else if (counter%50>0)
//DEADCODE DAW 08/05/99 				{
//DEADCODE DAW 08/05/99 				sprintf(string,"%d",counter/10);
//DEADCODE DAW 08/05/99 				pDC->TextOut(x,0,string);
//DEADCODE DAW 08/05/99 				}
//DEADCODE DAW 08/05/99 				counter++;
//DEADCODE DAW 08/05/99 			}
//DEADCODE DAW 08/05/99 		}
//DEADCODE DAW 08/05/99 	}
//DEADCODE DAW 08/05/99 	else if (m_iAlign==2)
//DEADCODE DAW 08/05/99 	{
//DEADCODE DAW 08/05/99 		CFont* pfont;
//DEADCODE DAW 08/05/99 		pfont = pDC->GetCurrentFont();
//DEADCODE DAW 08/05/99 		LOGFONT logfont;
//DEADCODE DAW 08/05/99 		pfont->GetLogFont(&logfont);
//DEADCODE DAW 08/05/99 		int offset=logfont.lfHeight/2;
//DEADCODE DAW 08/05/99 		pDC->SetTextAlign(TA_LEFT | TA_TOP | TA_NOUPDATECP);
//DEADCODE DAW 08/05/99 		pDC->MoveTo(CPoint(2,offset));
//DEADCODE DAW 08/05/99 		pDC->LineTo(CPoint(2,rect.bottom-offset)); // line at top of scale
//DEADCODE DAW 08/05/99 		// first draw in 10 mile seperators these are always present
//DEADCODE DAW 08/05/99 		counter=0;
//DEADCODE DAW 08/05/99 		for (float x=offset;x<rect.bottom-offset;x+=zoom*10)
//DEADCODE DAW 08/05/99 		{
//DEADCODE DAW 08/05/99 			pDC->MoveTo(CPoint(2,x));
//DEADCODE DAW 08/05/99 			pDC->LineTo(CPoint(15,x));
//DEADCODE DAW 08/05/99 			if (counter%5==0)
//DEADCODE DAW 08/05/99 			{
//DEADCODE DAW 08/05/99 				if (counter%20==0 || (counter%10==0 && zoom>0.5) || zoom>=1.5)
//DEADCODE DAW 08/05/99 				{
//DEADCODE DAW 08/05/99 					sprintf(string,"%d",counter*10);
//DEADCODE DAW 08/05/99 					pDC->TextOut(15,x-offset,string);
//DEADCODE DAW 08/05/99 				}
//DEADCODE DAW 08/05/99 			}
//DEADCODE DAW 08/05/99 			counter++;
//DEADCODE DAW 08/05/99 		}
//DEADCODE DAW 08/05/99 		// now 1 mile seperators
//DEADCODE DAW 08/05/99 		if (zoom>=4)
//DEADCODE DAW 08/05/99 		{
//DEADCODE DAW 08/05/99 			counter=0;
//DEADCODE DAW 08/05/99 			for (float x=offset;x<rect.bottom-offset;x+=zoom)
//DEADCODE DAW 08/05/99 			{
//DEADCODE DAW 08/05/99 				if (counter%10>0)
//DEADCODE DAW 08/05/99 				{
//DEADCODE DAW 08/05/99 					pDC->MoveTo(CPoint(2,x));
//DEADCODE DAW 08/05/99 					pDC->LineTo(CPoint(12,x));
//DEADCODE DAW 08/05/99 				}
//DEADCODE DAW 08/05/99 				if (counter%10==0 || (counter%5==0 && zoom>=8))
//DEADCODE DAW 08/05/99 				{
//DEADCODE DAW 08/05/99 					if (counter%50>0)
//DEADCODE DAW 08/05/99 					{
//DEADCODE DAW 08/05/99 						sprintf(string,"%d",counter);
//DEADCODE DAW 08/05/99 						pDC->TextOut(15,x-offset,string);
//DEADCODE DAW 08/05/99 					}
//DEADCODE DAW 08/05/99 				}
//DEADCODE DAW 08/05/99 				counter++;
//DEADCODE DAW 08/05/99 			}
//DEADCODE DAW 08/05/99 		}
//DEADCODE DAW 08/05/99 
//DEADCODE DAW 08/05/99 		// now 1/10 mile seperators
//DEADCODE DAW 08/05/99 		if (pView->m_zoom>=32)
//DEADCODE DAW 08/05/99 		{
//DEADCODE DAW 08/05/99 			counter=0;
//DEADCODE DAW 08/05/99 			for (float x=offset;x<rect.bottom-offset;x+=zoom/10)
//DEADCODE DAW 08/05/99 			{
//DEADCODE DAW 08/05/99 				if (counter%10>0)
//DEADCODE DAW 08/05/99 				{
//DEADCODE DAW 08/05/99 					pDC->MoveTo(CPoint(2,x));
//DEADCODE DAW 08/05/99 					pDC->LineTo(CPoint(10,x));
//DEADCODE DAW 08/05/99 				}
//DEADCODE DAW 08/05/99 				else if (counter%50>0)
//DEADCODE DAW 08/05/99 				{
//DEADCODE DAW 08/05/99 				sprintf(string,"%d",counter/10);
//DEADCODE DAW 08/05/99 				pDC->TextOut(15,x-offset,string);
//DEADCODE DAW 08/05/99 				}
//DEADCODE DAW 08/05/99 				counter++;
//DEADCODE DAW 08/05/99 			}
//DEADCODE DAW 08/05/99 		}
//DEADCODE DAW 08/05/99 	}
//DEADCODE DAW 08/05/99 	else if (m_iAlign==4)
//DEADCODE DAW 08/05/99 	{
//DEADCODE DAW 08/05/99 		CFont* pfont;
//DEADCODE DAW 08/05/99 		pfont = pDC->GetCurrentFont();
//DEADCODE DAW 08/05/99 		LOGFONT logfont;
//DEADCODE DAW 08/05/99 		pfont->GetLogFont(&logfont);
//DEADCODE DAW 08/05/99 		int offset=logfont.lfHeight/2;
//DEADCODE DAW 08/05/99 		pDC->SetTextAlign(TA_RIGHT | TA_TOP | TA_NOUPDATECP);
//DEADCODE DAW 08/05/99 		pDC->MoveTo(CPoint(m_iFixedWidth-3,offset));
//DEADCODE DAW 08/05/99 		pDC->LineTo(CPoint(m_iFixedWidth-3,rect.bottom-offset)); // line at top of scale
//DEADCODE DAW 08/05/99 		// first draw in 10 mile seperators these are always present
//DEADCODE DAW 08/05/99 		counter=0;
//DEADCODE DAW 08/05/99 		for (float x=offset;x<rect.bottom-offset;x+=zoom*10)
//DEADCODE DAW 08/05/99 		{
//DEADCODE DAW 08/05/99 			pDC->MoveTo(CPoint(m_iFixedWidth-2,x));
//DEADCODE DAW 08/05/99 			pDC->LineTo(CPoint(m_iFixedWidth-15,x));
//DEADCODE DAW 08/05/99 			if (counter%5==0)
//DEADCODE DAW 08/05/99 			{
//DEADCODE DAW 08/05/99 				if (counter%20==0 || (counter%10==0 && zoom>0.5) || zoom>=1.5)
//DEADCODE DAW 08/05/99 				{
//DEADCODE DAW 08/05/99 					sprintf(string,"%d",counter*10);
//DEADCODE DAW 08/05/99 					pDC->TextOut(m_iFixedWidth-15,x-offset,string);
//DEADCODE DAW 08/05/99 				}
//DEADCODE DAW 08/05/99 			}
//DEADCODE DAW 08/05/99 			counter++;
//DEADCODE DAW 08/05/99 		}
//DEADCODE DAW 08/05/99 		// now 1 mile seperators
//DEADCODE DAW 08/05/99 		if (zoom>=4)
//DEADCODE DAW 08/05/99 		{
//DEADCODE DAW 08/05/99 			counter=0;
//DEADCODE DAW 08/05/99 			for (float x=offset;x<rect.bottom-offset;x+=zoom)
//DEADCODE DAW 08/05/99 			{
//DEADCODE DAW 08/05/99 				if (counter%10>0)
//DEADCODE DAW 08/05/99 				{
//DEADCODE DAW 08/05/99 					pDC->MoveTo(CPoint(m_iFixedWidth-2,x));
//DEADCODE DAW 08/05/99 					pDC->LineTo(CPoint(m_iFixedWidth-12,x));
//DEADCODE DAW 08/05/99 				}
//DEADCODE DAW 08/05/99 				if (counter%10==0 || (counter%5==0 && zoom>=8))
//DEADCODE DAW 08/05/99 				{
//DEADCODE DAW 08/05/99 					if (counter%50>0)
//DEADCODE DAW 08/05/99 					{
//DEADCODE DAW 08/05/99 						sprintf(string,"%d",counter);
//DEADCODE DAW 08/05/99 						pDC->TextOut(m_iFixedWidth-15,x-offset,string);
//DEADCODE DAW 08/05/99 					}
//DEADCODE DAW 08/05/99 				}
//DEADCODE DAW 08/05/99 				counter++;
//DEADCODE DAW 08/05/99 			}
//DEADCODE DAW 08/05/99 		}
//DEADCODE DAW 08/05/99 
//DEADCODE DAW 08/05/99 		// now 1/10 mile seperators
//DEADCODE DAW 08/05/99 		if (pView->m_zoom>=32)
//DEADCODE DAW 08/05/99 		{
//DEADCODE DAW 08/05/99 			counter=0;
//DEADCODE DAW 08/05/99 			for (float x=offset;x<rect.bottom-offset;x+=zoom/10)
//DEADCODE DAW 08/05/99 			{
//DEADCODE DAW 08/05/99 				if (counter%10>0)
//DEADCODE DAW 08/05/99 				{
//DEADCODE DAW 08/05/99 					pDC->MoveTo(CPoint(m_iFixedWidth-2,x));
//DEADCODE DAW 08/05/99 					pDC->LineTo(CPoint(m_iFixedWidth-10,x));
//DEADCODE DAW 08/05/99 				}
//DEADCODE DAW 08/05/99 				else if (counter%50>0)
//DEADCODE DAW 08/05/99 				{
//DEADCODE DAW 08/05/99 				sprintf(string,"%d",counter/10);
//DEADCODE DAW 08/05/99 				pDC->TextOut(m_iFixedWidth-15,x-offset,string);
//DEADCODE DAW 08/05/99 				}
//DEADCODE DAW 08/05/99 				counter++;
//DEADCODE DAW 08/05/99 			}
//DEADCODE DAW 08/05/99 		}
//DEADCODE DAW 08/05/99 	}
//DEADCODE DAW 08/05/99 	pDC->DrawEdge(&rect,EDGE_ETCHED,BF_RECT); // border
//DEADCODE DAW 08/05/99 	this->EndPaint(&paintstruct);
//DEADCODE DAW 08/05/99 	// Do not call CDialogBar::OnPaint() for painting messages
//DEADCODE DAW 08/05/99 }
//DEADCODE DAW 08/05/99 
//DEADCODE DAW 08/05/99 void CResizableDlgBar::OnRButtonDown(UINT nFlags, CPoint point) 
//DEADCODE DAW 08/05/99 {
//DEADCODE DAW 08/05/99 	m_RButtonDown=TRUE;
//DEADCODE DAW 08/05/99 	this->SetCapture();
//DEADCODE DAW 08/05/99 	m_oldPoint=point;
//DEADCODE DAW 08/05/99 	CDialogBar::OnRButtonDown(nFlags, point);
//DEADCODE DAW 08/05/99 }
//DEADCODE DAW 08/05/99 
//DEADCODE DAW 08/05/99 void CResizableDlgBar::OnRButtonUp(UINT nFlags, CPoint point) 
//DEADCODE DAW 08/05/99 {
//DEADCODE DAW 08/05/99 	m_RButtonDown=FALSE;
//DEADCODE DAW 08/05/99 	ReleaseCapture(); 	
//DEADCODE DAW 08/05/99 	CMIGView* pView;
//DEADCODE DAW 08/05/99 	pView = (CMIGView*)(m_pParent->GetActiveView());
//DEADCODE DAW 08/05/99 	CRect rect;
//DEADCODE DAW 08/05/99 	pView->GetClientRect(rect);
//DEADCODE DAW 08/05/99 	pView->Zoom(CPoint(rect.right/2,rect.bottom/2));
//DEADCODE DAW 08/05/99 	CDialogBar::OnRButtonUp(nFlags, point);
//DEADCODE DAW 08/05/99 }
//DEADCODE DAW 08/05/99 
//DEADCODE DAW 08/05/99 void CResizableDlgBar::OnMouseMove(UINT nFlags, CPoint point) 
//DEADCODE DAW 08/05/99 {
//DEADCODE DAW 08/05/99 	if (m_RButtonDown)
//DEADCODE DAW 08/05/99 	{
//DEADCODE DAW 08/05/99 		CMIGView* pView;
//DEADCODE DAW 08/05/99 		pView = (CMIGView*)(m_pParent->GetActiveView());
//DEADCODE DAW 08/05/99 		if (m_bHorzAlign)
//DEADCODE DAW 08/05/99 			pView->m_zoom=((point.x-5)*pView->m_zoom)/(m_oldPoint.x-5);
//DEADCODE DAW 08/05/99 		else
//DEADCODE DAW 08/05/99 			pView->m_zoom=((point.y-5)*pView->m_zoom)/(m_oldPoint.y-5);
//DEADCODE DAW 08/05/99 		if (pView->m_zoom<0.25) pView->m_zoom=0.25;
//DEADCODE DAW 08/05/99 		else if (pView->m_zoom>256) pView->m_zoom=256;
//DEADCODE DAW 08/05/99 		else m_oldPoint=point;
//DEADCODE DAW 08/05/99 		this->RedrawWindow();
//DEADCODE DAW 08/05/99 	}
//DEADCODE DAW 08/05/99 	CDialogBar::OnMouseMove(nFlags, point);
//DEADCODE DAW 08/05/99 }
