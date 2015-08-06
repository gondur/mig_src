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

// RScrlBarCtl.cpp : Implementation of the CRScrlBarCtrl ActiveX Control class.

#define F_COMMON
#define F_SOUNDS
#define F_BATTLE
#include "stdafx.h"
#include "RScrlBar.h"
#include "RScrlBrC.h"
#include "RScrlBrP.h"
#include "messages.h"
#include "FileMan.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BOOL CRScrlBarCtrl::m_bDrawing = FALSE;

IMPLEMENT_DYNCREATE(CRScrlBarCtrl, COleControl)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CRScrlBarCtrl, COleControl)
	//{{AFX_MSG_MAP(CRScrlBarCtrl)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_SETCURSOR()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Dispatch map

BEGIN_DISPATCH_MAP(CRScrlBarCtrl, COleControl)
	//{{AFX_DISPATCH_MAP(CRScrlBarCtrl)
	DISP_PROPERTY_EX(CRScrlBarCtrl, "MinValue", GetMinValue, SetMinValue, VT_I4)
	DISP_PROPERTY_EX(CRScrlBarCtrl, "MaxValue", GetMaxValue, SetMaxValue, VT_I4)
	DISP_PROPERTY_EX(CRScrlBarCtrl, "StepSize", GetStepSize, SetStepSize, VT_I4)
	DISP_PROPERTY_EX(CRScrlBarCtrl, "HorzAlign", GetHorzAlign, SetHorzAlign, VT_BOOL)
	DISP_PROPERTY_EX(CRScrlBarCtrl, "parentPointer", GetParentPointer, SetParentPointer, VT_I4)
	DISP_PROPERTY_EX(CRScrlBarCtrl, "PageSize", GetPageSize, SetPageSize, VT_I4)
	DISP_PROPERTY_EX(CRScrlBarCtrl, "ScrollPos", GetScrollPos, SetScrollPos, VT_I4)
	DISP_PROPERTY_EX(CRScrlBarCtrl, "UseMessagesInsteadOfEvents", GetUseMessagesInsteadOfEvents, SetUseMessagesInsteadOfEvents, VT_BOOL)
	DISP_PROPERTY_EX(CRScrlBarCtrl, "FileNumOffset", GetFileNumOffset, SetFileNumOffset, VT_I4)
	DISP_FUNCTION(CRScrlBarCtrl, "Move", Move, VT_EMPTY, VTS_I4 VTS_I4 VTS_I4 VTS_I4)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()


/////////////////////////////////////////////////////////////////////////////
// Event map

BEGIN_EVENT_MAP(CRScrlBarCtrl, COleControl)
	//{{AFX_EVENT_MAP(CRScrlBarCtrl)
	EVENT_CUSTOM("Scroll", FireScroll, VTS_I4)
	//}}AFX_EVENT_MAP
END_EVENT_MAP()


/////////////////////////////////////////////////////////////////////////////
// Property pages

// TODO: Add more property pages as needed.  Remember to increase the count!
BEGIN_PROPPAGEIDS(CRScrlBarCtrl, 1)
	PROPPAGEID(CRScrlBarPropPage::guid)
END_PROPPAGEIDS(CRScrlBarCtrl)


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CRScrlBarCtrl, "RSCRLBAR.RScrlBarCtrl.1",
	0x505aee46, 0x6a66, 0x11d1, 0xa1, 0xf0, 0x44, 0x45, 0x53, 0x54, 0, 0)


/////////////////////////////////////////////////////////////////////////////
// Type library ID and version

IMPLEMENT_OLETYPELIB(CRScrlBarCtrl, _tlid, _wVerMajor, _wVerMinor)


/////////////////////////////////////////////////////////////////////////////
// Interface IDs

const IID BASED_CODE IID_DRScrlBar =
		{ 0x505aee44, 0x6a66, 0x11d1, { 0xa1, 0xf0, 0x44, 0x45, 0x53, 0x54, 0, 0 } };
const IID BASED_CODE IID_DRScrlBarEvents =
		{ 0x505aee45, 0x6a66, 0x11d1, { 0xa1, 0xf0, 0x44, 0x45, 0x53, 0x54, 0, 0 } };


/////////////////////////////////////////////////////////////////////////////
// Control type information

static const DWORD BASED_CODE _dwRScrlBarOleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CRScrlBarCtrl, IDS_RSCRLBAR, _dwRScrlBarOleMisc)


/////////////////////////////////////////////////////////////////////////////
// CRScrlBarCtrl::CRScrlBarCtrlFactory::UpdateRegistry -
// Adds or removes system registry entries for CRScrlBarCtrl

BOOL CRScrlBarCtrl::CRScrlBarCtrlFactory::UpdateRegistry(BOOL bRegister)
{
	// TODO: Verify that your control follows apartment-model threading rules.
	// Refer to MFC TechNote 64 for more information.
	// If your control does not conform to the apartment-model rules, then
	// you must modify the code below, changing the 6th parameter from
	// afxRegApartmentThreading to 0.

	if (bRegister)
		return AfxOleRegisterControlClass(
			AfxGetInstanceHandle(),
			m_clsid,
			m_lpszProgID,
			IDS_RSCRLBAR,
			IDB_RSCRLBAR,
			afxRegApartmentThreading,
			_dwRScrlBarOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}


/////////////////////////////////////////////////////////////////////////////
// Licensing strings

static const TCHAR BASED_CODE _szLicFileName[] = _T("RScrlBar.lic");

static const WCHAR BASED_CODE _szLicString[] =
	L"Copyright (c) 1997 RowanSoftware";


/////////////////////////////////////////////////////////////////////////////
// CRScrlBarCtrl::CRScrlBarCtrlFactory::VerifyUserLicense -
// Checks for existence of a user license

BOOL CRScrlBarCtrl::CRScrlBarCtrlFactory::VerifyUserLicense()
{
	return TRUE;
/*		AfxVerifyLicFile(AfxGetInstanceHandle(), _szLicFileName,
		_szLicString);
*/
}


/////////////////////////////////////////////////////////////////////////////
// CRScrlBarCtrl::CRScrlBarCtrlFactory::GetLicenseKey -
// Returns a runtime licensing key

BOOL CRScrlBarCtrl::CRScrlBarCtrlFactory::GetLicenseKey(DWORD dwReserved,
	BSTR FAR* pbstrKey)
{
	if (pbstrKey == NULL)
		return FALSE;

	*pbstrKey = SysAllocString(_szLicString);
	return (*pbstrKey != NULL);
}


/////////////////////////////////////////////////////////////////////////////
// CRScrlBarCtrl::CRScrlBarCtrl - Constructor

CRScrlBarCtrl::CRScrlBarCtrl()
{
	InitializeIIDs(&IID_DRScrlBar, &IID_DRScrlBarEvents);
	m_lStepSize=15;
	m_lMaxValue=100;
	m_lMinValue=0;
	m_bHorzAlign=FALSE;
	m_iScrollPos=0;
	m_parent=NULL;
	m_pagesize=0;
	m_offset=-1;
	m_timerID=0;
	m_button=0;
	m_FileNumOffset=0;
	m_bUseMessagesInsteadOfEvents=FALSE;
}


/////////////////////////////////////////////////////////////////////////////
// CRScrlBarCtrl::~CRScrlBarCtrl - Destructor

CRScrlBarCtrl::~CRScrlBarCtrl()
{
	// TODO: Cleanup your control's instance data here.
}


/////////////////////////////////////////////////////////////////////////////
// CRScrlBarCtrl::OnDraw - Drawing function

#define SBWIDTH 16
#define PUCKEND 12
#define PUCKWIDTH 10
#define PUCKGAP 3

void CRScrlBarCtrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
{
	CWnd* parent;
	if (m_bDrawing || !m_hWnd) return;
	m_bDrawing=TRUE;
	// all the graphics come from the file system and if this is not
	// available then we cant draw anything
//	long offsets;
	if (m_parent) // this contains the closest rdialog if the below case is not true
	{
		parent=m_parent;
	}
	else
	{
		// assumes we are on a listbox with an rdialog underneath it
		// it will probably break if its placed somewhere on its own...
		// I tried to set m_parent to be the listboxes parent but
		// I kept getting stupid errors
		parent=GetParent()->GetParent();
	}
	CDC* pOffScreenDC=(CDC*)parent->SendMessage(WM_GETOFFSCREENDC,NULL,NULL);
	ASSERT(pOffScreenDC); // this will fail if parent is not an RDialog
//	offsets=parent->SendMessage(WM_GETXYOFFSET,NULL,NULL);
	// this is quite a complex drawing procedure so we are going
	// to use an offscreen DC to prevent flicker...
	CBitmap bitmap;
	bitmap.CreateCompatibleBitmap(pdc,rcBounds.right,rcBounds.bottom);
	CBitmap* pOldBitmap;
	pOldBitmap=pOffScreenDC->SelectObject(&bitmap);
//	ASSERT(pOffScreenDC->GetDeviceCaps(CAPS1)&C1_TRANSPARENT);
/*
	offscreenDC2.CreateCompatibleDC(pdc);
	CBitmap bitmap2;
	bitmap2.CreateCompatibleBitmap(pdc,rcBounds.right,rcBounds.bottom);
	CBitmap* pOldBitmap2;
	pOldBitmap2=offscreenDC2.SelectObject(&bitmap2);
	// first draw the background artwork
	CRect rect;
	GetWindowRect(rect);
	CRect parentrect;
	parent->GetWindowRect(parentrect);
	int offsetx;
	int offsety;
	offsetx=short(offsets & 0x0000FFFF)+parentrect.left-rect.left;
	offsety=short((offsets & 0xFFFF0000)>>16)+parentrect.top-rect.top;
	FileNum artwork;
	artwork=(FileNum)parent->SendMessage(WM_GETARTWORK,NULL,NULL);
	DrawBitmap(artwork,pOffScreenDC2,offsetx,offsety);
*/	// now overlay the semi-transparent scrollbar body
//	if (m_bHorzAlign)
//		MergeBitmap(FileNum(FIL_HORZSCROLLBAR,pOffScreenDC,0,0);
//	else
//		MergeBitmap(FileNum(FIL_VERTSCROLLBAR,pOffScreenDC,0,0);
	if (m_bHorzAlign)
	{
		DrawTiledBitmap(FileNum(FIL_HORZ_SCROLLBAR+m_FileNumOffset),pOffScreenDC,SBWIDTH,0,rcBounds.right-rcBounds.left-SBWIDTH-SBWIDTH);
	}
	else
	{
		DrawTiledBitmap(FileNum(FIL_VERT_SCROLLBAR+m_FileNumOffset),pOffScreenDC,0,SBWIDTH,rcBounds.bottom-rcBounds.top-SBWIDTH-SBWIDTH);
	}
/*	int x;
	if (m_bHorzAlign)
	{
		for (x=32;x<rcBounds.right-rcBounds.left-32;x+=128)
			DrawBitmap(FileNum(FIL_HORZ_SCROLLBAR,pOffScreenDC,x,0);
	}
	else
	{
		for (x=32;x<rcBounds.bottom-rcBounds.top-32;x+=128)
			DrawBitmap(FileNum(FIL_VERT_SCROLLBAR,pOffScreenDC,0,x);
	}*/
//	MergeDCs(pOffScreenDC2,pOffScreenDC);
/*
	// supported in Windoze 98 only
	// MergeDCs does the same thing however
	GetClientRect(rect);
	BLENDFUNCTION blendfunction;
	blendfunction.blendOp=AC_SRC_OVER;
	blendfunction.blendFlags=NULL;
	blendfunction.SourceConstantAlpha=127;
	blendfunction.AlphaFormat=NULL;
	AlphaBlend(pOffScreenDC->m_hDC,0,0,rect.right,rect.bottom,
				pdc->m_hDC,0,0,rect.right,rect.bottom,blendfunction);
*/
	// now draw the puck
	if (m_bHorzAlign)
	{
		int divisor=m_pagesize+m_lMaxValue-m_lMinValue;
		int puckwidth=0;
		if (divisor>0)
			puckwidth=(m_pagesize*(rcBounds.right-rcBounds.left-SBWIDTH-SBWIDTH-PUCKEND-PUCKEND))/divisor;
		int puckpos=(m_iScrollPos*(rcBounds.right-rcBounds.left-SBWIDTH-SBWIDTH-PUCKEND-PUCKEND-puckwidth))/(m_lMaxValue-m_lMinValue);
		DrawTransparentBitmap(FileNum(FIL_PUCK_LEFT+m_FileNumOffset),pOffScreenDC,SBWIDTH+puckpos,PUCKGAP);
		DrawTransparentBitmap(FileNum(FIL_PUCK_RIGHT+m_FileNumOffset),pOffScreenDC,SBWIDTH+PUCKEND+puckpos+puckwidth,PUCKGAP);
//		for (int x=32+12+puckpos;x<32+12+puckpos+puckwidth;x++)
//		{
//			DrawBitmap(FileNum(FIL_PUCK_MIDDLE_HORZ,pOffScreenDC,x,PUCKGAP);
//		}
		DrawTiledBitmap(FileNum(FIL_PUCK_MIDDLE_HORZ+m_FileNumOffset),pOffScreenDC,SBWIDTH+PUCKEND+puckpos,PUCKGAP,puckwidth);
	}
	else
	{
		int divisor=m_pagesize+m_lMaxValue-m_lMinValue;
		int puckwidth=0;
		if (divisor>0)
			puckwidth=(m_pagesize*(rcBounds.bottom-rcBounds.top-SBWIDTH-SBWIDTH-PUCKEND-PUCKEND))/divisor;
		int puckpos=(m_iScrollPos*(rcBounds.bottom-rcBounds.top-SBWIDTH-SBWIDTH-PUCKEND-PUCKEND-puckwidth))/(m_lMaxValue-m_lMinValue);
		DrawTransparentBitmap(FileNum(FIL_PUCK_TOP+m_FileNumOffset),pOffScreenDC,PUCKGAP,SBWIDTH+puckpos);
		DrawTransparentBitmap(FileNum(FIL_PUCK_BOTTOM+m_FileNumOffset),pOffScreenDC,PUCKGAP,SBWIDTH+PUCKEND+puckpos+puckwidth);
//		for (int x=32+PUCKEND+puckpos;x<32+PUCKEND+puckpos+puckwidth;x++)
//		{
//			DrawBitmap(FileNum(FIL_PUCK_MIDDLE_VERT,pOffScreenDC,PUCKGAP,x);
//		}
		DrawTiledBitmap(FileNum(FIL_PUCK_MIDDLE_VERT+m_FileNumOffset),pOffScreenDC,PUCKGAP,SBWIDTH+PUCKEND+puckpos,puckwidth);
	}

	// now draw the buttons at the ends
	FileNum filenum;
	if (m_button==1)
		filenum=FileNum(FIL_SCROLLBAR_BUTTON_DOWN+m_FileNumOffset);
	else
		filenum=FileNum(FIL_SCROLLBAR_BUTTON_UP+m_FileNumOffset);
	DrawBitmap(filenum,pOffScreenDC,0,0);
	if (m_button==2)
		filenum=FileNum(FIL_SCROLLBAR_BUTTON_DOWN+m_FileNumOffset);
	else
		filenum=FileNum(FIL_SCROLLBAR_BUTTON_UP+m_FileNumOffset);
	if (m_bHorzAlign)
		DrawBitmap(filenum,pOffScreenDC,rcBounds.right-SBWIDTH,0);
	else
		DrawBitmap(filenum,pOffScreenDC,0,rcBounds.bottom-SBWIDTH);
	pdc->BitBlt(0,0,rcBounds.right-rcBounds.left,rcBounds.bottom-rcBounds.top,pOffScreenDC,
					0,0,SRCCOPY); // flips offscreen dc to real dc
    pOffScreenDC->SelectObject(pOldBitmap);
	// then delete the dc
//  offscreenDC2.SelectObject(pOldBitmap2);
//	offscreenDC2.DeleteDC();
	m_bDrawing=FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// CRScrlBarCtrl::DoPropExchange - Persistence support

void CRScrlBarCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);
}


/////////////////////////////////////////////////////////////////////////////
// CRScrlBarCtrl::OnResetState - Reset control to default state

void CRScrlBarCtrl::OnResetState()
{
	COleControl::OnResetState();  // Resets defaults found in DoPropExchange
}


/////////////////////////////////////////////////////////////////////////////
// CRScrlBarCtrl message handlers

void CRScrlBarCtrl::DrawBitmap(FileNum filenum,CDC* pdc,int x,int y)
{
	if (m_hWnd)
	{
		CWnd* parent;
		if (m_parent)
			parent=m_parent;
		else
			parent=GetParent()->GetParent();
		BYTE* pData;
		pData = (BYTE*)parent->SendMessage(WM_GETFILE,filenum,NULL);
		if (pData && pData[0]=='B' && pData[1]=='M') // checks if its a bitmap file
		{
			// now render it...
			BITMAPFILEHEADER* pFile=(BITMAPFILEHEADER*)pData;
			BITMAPINFO* pInfo=(BITMAPINFO*)(pData+sizeof(BITMAPFILEHEADER));
			pData+=pFile->bfOffBits;
			SetDIBitsToDevice(pdc->m_hDC,x,y,pInfo->bmiHeader.biWidth, pInfo->bmiHeader.biHeight,
				0,0,0,pInfo->bmiHeader.biHeight,pData,pInfo,DIB_RGB_COLORS);
		}
		parent->SendMessage(WM_RELEASELASTFILE,NULL,NULL);
	}
}

void CRScrlBarCtrl::DrawTiledBitmap(FileNum filenum,CDC* pdc,int x,int y,int length)
{
	if (m_hWnd)
	{
		CWnd* parent;
		if (m_parent)
			parent=m_parent;
		else
			parent=GetParent()->GetParent();
		BYTE* pData;
		pData = (BYTE*)parent->SendMessage(WM_GETFILE,filenum,NULL);
		if (pData && pData[0]=='B' && pData[1]=='M') // checks if its a bitmap file
		{
			// now render it...
			BITMAPFILEHEADER* pFile=(BITMAPFILEHEADER*)pData;
			BITMAPINFO* pInfo=(BITMAPINFO*)(pData+sizeof(BITMAPFILEHEADER));
			pData+=pFile->bfOffBits;
			// tiling...
			int z,width;
			if (m_bHorzAlign)
			{
				for (z=x;z<x+length;z+=pInfo->bmiHeader.biWidth)
				{
					width=min(x+length-z,pInfo->bmiHeader.biWidth);
					SetDIBitsToDevice(pdc->m_hDC,z,y,width, pInfo->bmiHeader.biHeight,
						0,0,0,pInfo->bmiHeader.biHeight,pData,pInfo,DIB_RGB_COLORS);
				}
			}
			else
			{
				for (z=y;z<y+length;z+=pInfo->bmiHeader.biHeight)
				{
					width=min(y+length-z,pInfo->bmiHeader.biHeight);
					SetDIBitsToDevice(pdc->m_hDC,x,z, pInfo->bmiHeader.biWidth, width,
						0,0,0,pInfo->bmiHeader.biHeight,pData,pInfo,DIB_RGB_COLORS);
				}
			}
		}
		parent->SendMessage(WM_RELEASELASTFILE,NULL,NULL);
	}
}

void CRScrlBarCtrl::MergeDCs(CDC* sourceDC, CDC* destDC)
{
	// does an alphamerge but is very slow
/*
	CRect rect;
	GetClientRect(rect);
	COLORREF sourcecolour;
	COLORREF destcolour;
	COLORREF averagecolour;
//	TRACE0("colour dump:\n");
	for (int y=0;y<rect.bottom;y++)
	{
		for (int x=0;x<rect.right;x++)
		{
			sourcecolour=sourceDC->GetPixel(x,y);
			destcolour=destDC->GetPixel(x,y);
			averagecolour=((destcolour&0xff)+(sourcecolour&0xff))>>1;
			averagecolour+=(((destcolour&0xff00)+(sourcecolour&0xff00))>>9)<<8;
			averagecolour+=(((destcolour&0xff0000)+(sourcecolour&0xff0000))>>17)<<16;
//			TRACE3("R: %d G: %d B: %d\n",averagecolour&0xff,(averagecolour&0xff00)>>8,(averagecolour&0xff0000)>>16);
//			ASSERT(FALSE);
			destDC->SetPixel(x,y,averagecolour);
		}
	}
*/
}


void CRScrlBarCtrl::DrawTransparentBitmap(FileNum filenum,CDC * pDC, int x, int y)
{
	// note that palette entry 254 is the transparent colour
	BYTE* pData;
	CWnd* parent;
	if (m_parent)
		parent=m_parent;
	else
		parent=GetParent()->GetParent();
	pData = (BYTE*)parent->SendMessage(WM_GETFILE,filenum,NULL);
	if (pData[0]=='B' && pData[1]=='M') // checks if its a bitmap file
	{
		// now render it...
		BITMAPFILEHEADER* pFile=(BITMAPFILEHEADER*)pData;
		BITMAPINFO* pInfo=(BITMAPINFO*)(pData+sizeof(BITMAPFILEHEADER));
		pData+=pFile->bfOffBits;
		BYTE* pData2=pData;
		BYTE code;
		int Width=pInfo->bmiHeader.biWidth;
		if (Width%4) Width+=4-Width%4; // DWord alignment
		int Height=pInfo->bmiHeader.biHeight;
		int x2,y2;
		RGBQUAD color;
		for (y2=Height-1;y2>=0;y2--)
		{
			for (x2=0;x2<Width;x2++)
			{
				code=*pData2++;
				if (code!=254 && x2<pInfo->bmiHeader.biWidth)
				{
					color=pInfo->bmiColors[code];
					pDC->SetPixel(x+x2,y+y2,RGB(color.rgbRed,color.rgbGreen,color.rgbBlue));
				}
			}
		}
	}
	parent->SendMessage(WM_RELEASELASTFILE,NULL,NULL);
}


void CRScrlBarCtrl::OnLButtonDown(UINT nFlags, CPoint point) 
{
	m_button=0;
	SetCapture();
	m_point=point;
	CRect rect;
	GetClientRect(rect);
	m_offset=-1;
	if (m_timerID) 
	{
		KillTimer(m_timerID);
		m_timerID=0;
	}
	m_timerID=SetTimer(2374,100,NULL);
	if (m_bHorzAlign)
	{
	    if (point.x<SBWIDTH)
		{
			m_iScrollPos-=m_lStepSize;
			m_button=1;
		}
		else if (point.x>rect.right-SBWIDTH)
		{
			m_iScrollPos+=m_lStepSize;
			m_button=2;
		}
		else
		{
			// figure out if we have clicked on the puck
			int divisor=m_pagesize+m_lMaxValue-m_lMinValue;
			int puckwidth=0;
			if (divisor>0)
				puckwidth=(m_pagesize*(rect.right-SBWIDTH-SBWIDTH-PUCKEND-PUCKEND))/divisor;
			int puckpos=(m_iScrollPos*(rect.right-SBWIDTH-SBWIDTH-PUCKEND-PUCKEND-puckwidth))/(m_lMaxValue-m_lMinValue)+SBWIDTH;
			if (CRect(puckpos,0,puckpos+puckwidth+PUCKEND+PUCKEND,SBWIDTH).PtInRect(point))
			{
				m_offset=point.x-puckpos;
				if (m_timerID) 
				{
					KillTimer(m_timerID);
					m_timerID=0;
				}
			}
			else
			{
				// did we click to the left or the right of it
				if (point.x<puckpos)
				{
					m_iScrollPos-=m_pagesize;
				}
				else
				{
					m_iScrollPos+=m_pagesize;
				}
			}
		}
	}
	else
	{
	    if (point.y<SBWIDTH)
		{
			m_iScrollPos-=m_lStepSize;
			m_button=1;
		}
		else if (point.y>rect.bottom-SBWIDTH)
		{
			m_iScrollPos+=m_lStepSize;
			m_button=2;
		}
		else
		{
			// figure out if we have clicked on the puck
			int divisor=m_pagesize+m_lMaxValue-m_lMinValue;
			int puckwidth=0;
			if (divisor>0)
				puckwidth=(m_pagesize*(rect.bottom-SBWIDTH-SBWIDTH-PUCKEND-PUCKEND))/divisor;
			int puckpos=(m_iScrollPos*(rect.bottom-SBWIDTH-SBWIDTH-PUCKEND-PUCKEND-puckwidth))/(m_lMaxValue-m_lMinValue)+SBWIDTH;
			if (CRect(0,puckpos,SBWIDTH,puckpos+puckwidth+PUCKEND+PUCKEND).PtInRect(point))
			{
				m_offset=point.y-puckpos;
				if (m_timerID) 
				{
					KillTimer(m_timerID);
					m_timerID=0;
				}
			}
			else
			{
				// did we click to the left or the right of it
				if (point.y<puckpos)
				{
					m_iScrollPos-=m_pagesize;
				}
				else
				{
					m_iScrollPos+=m_pagesize;
				}
			}
		}
	}
	DoFireScroll();
	COleControl::OnLButtonDown(nFlags, point);
}

void CRScrlBarCtrl::OnMouseMove(UINT nFlags, CPoint point) 
{
	m_point=point;
	if (m_bDrawing) return;
	if (m_offset>=0)
	{
		CRect rect;
		GetClientRect(rect);
		if (m_bHorzAlign)
		{
			int divisor=m_pagesize+m_lMaxValue-m_lMinValue;
			int puckwidth=0;
			if (divisor>0)
				puckwidth=(m_pagesize*(rect.right-SBWIDTH-SBWIDTH-PUCKEND-PUCKEND))/(divisor);
			m_iScrollPos=(point.x-m_offset-SBWIDTH)*(m_lMaxValue-m_lMinValue)/(rect.right-SBWIDTH-SBWIDTH-PUCKEND-PUCKEND-puckwidth);
			DoFireScroll();
		}
		else
		{
			int divisor=m_pagesize+m_lMaxValue-m_lMinValue;
			int puckwidth=0;
			if (divisor>0)
				puckwidth=(m_pagesize*(rect.bottom-SBWIDTH-SBWIDTH-PUCKEND-PUCKEND))/divisor;
			m_iScrollPos=(point.y-m_offset-SBWIDTH)*(m_lMaxValue-m_lMinValue)/(rect.bottom-SBWIDTH-SBWIDTH-PUCKEND-PUCKEND-puckwidth);
			DoFireScroll();
		}
	}
	COleControl::OnMouseMove(nFlags, point);
}

void CRScrlBarCtrl::OnLButtonUp(UINT nFlags, CPoint point) 
{
	m_offset=-1;
	if (m_timerID) 
	{
		KillTimer(m_timerID);
		m_timerID=0;
	}
	if (m_button)
	{
		m_button=0;
		InvalidateControl();
	}
	ReleaseCapture();
	COleControl::OnLButtonUp(nFlags, point);
}

void CRScrlBarCtrl::Move(long left, long top, long right, long bottom) 
{
	SetRectInContainer(CRect(left,top,right,bottom));
}

void CRScrlBarCtrl::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	// Disable double clicks
	this->OnLButtonDown(nFlags,point);
//	COleControl::OnLButtonDblClk(nFlags, point);
}

long CRScrlBarCtrl::GetMinValue() 
{
	return m_lMinValue;
}

void CRScrlBarCtrl::SetMinValue(long nNewValue) 
{
	m_lMinValue=nNewValue;
	SetModifiedFlag();
}

long CRScrlBarCtrl::GetMaxValue() 
{
	return m_lMaxValue;
}

void CRScrlBarCtrl::SetMaxValue(long nNewValue) 
{
	if (nNewValue<=0)
	{
		nNewValue=1;
		ASSERT(FALSE);
	}
	m_lMaxValue=nNewValue;
	SetModifiedFlag();
}

long CRScrlBarCtrl::GetStepSize() 
{
	return m_lStepSize;
}

void CRScrlBarCtrl::SetStepSize(long nNewValue) 
{
	m_lStepSize=nNewValue;
	SetModifiedFlag();
}

BOOL CRScrlBarCtrl::GetHorzAlign() 
{
	return m_bHorzAlign;
}

void CRScrlBarCtrl::SetHorzAlign(BOOL bNewValue) 
{
	m_bHorzAlign=bNewValue;
	InvalidateControl();
	SetModifiedFlag();
}

long CRScrlBarCtrl::GetParentPointer() 
{
	return (long)m_parent;
}

void CRScrlBarCtrl::SetParentPointer(long nNewValue) 
{
	m_parent=(CWnd*)nNewValue;
	SetModifiedFlag();
}

long CRScrlBarCtrl::GetPageSize() 
{
	return m_pagesize;
}

void CRScrlBarCtrl::SetPageSize(long nNewValue) 
{
	m_pagesize=nNewValue;
	InvalidateControl();
	SetModifiedFlag();
}

void CRScrlBarCtrl::DoFireScroll()
{
	if (m_iScrollPos>m_lMaxValue) m_iScrollPos=m_lMaxValue;
	if (m_iScrollPos<m_lMinValue) m_iScrollPos=m_lMinValue;
	if (m_bUseMessagesInsteadOfEvents && m_parent)
		m_parent->SendMessage(WM_ACTIVEXSCROLL,m_iScrollPos,m_bHorzAlign);
	else
		FireScroll(m_iScrollPos);
	RedrawWindow();
}

long CRScrlBarCtrl::GetScrollPos() 
{
	return m_iScrollPos;
}

void CRScrlBarCtrl::SetScrollPos(long nNewValue) 
{
	m_iScrollPos=nNewValue;
	InvalidateControl();
	SetModifiedFlag();
}

BOOL CRScrlBarCtrl::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	::SetCursor(AfxGetApp()->LoadStandardCursor(IDC_ARROW));
	return TRUE;
}

void CRScrlBarCtrl::OnTimer(UINT nIDEvent) 
{
	if (nIDEvent && nIDEvent==m_timerID)
	{
		OnLButtonDown(NULL,m_point);
	}
	COleControl::OnTimer(nIDEvent);
}

BOOL CRScrlBarCtrl::GetUseMessagesInsteadOfEvents() 
{
	return m_bUseMessagesInsteadOfEvents;
}

void CRScrlBarCtrl::SetUseMessagesInsteadOfEvents(BOOL bNewValue) 
{
	m_bUseMessagesInsteadOfEvents=bNewValue;
	SetModifiedFlag();
}

long CRScrlBarCtrl::GetFileNumOffset() 
{
	return m_FileNumOffset;
}

void CRScrlBarCtrl::SetFileNumOffset(long nNewValue) 
{
	m_FileNumOffset=nNewValue;
	SetModifiedFlag();
}
