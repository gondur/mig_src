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

// RRadioC.cpp : Implementation of the CRRadioCtrl ActiveX Control class.

#define F_COMMON
#define F_BATTLE
#include "stdafx.h"
#include "RRadio.h"
#include "RRadioC.h"
#include "RRadioP.h"
#include "messages.h"
#include "FileMan.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BOOL CRRadioCtrl::m_bDrawing = FALSE;

IMPLEMENT_DYNCREATE(CRRadioCtrl, COleControl)

extern int GetShadow1XOffset(int fontheight);
extern int GetShadow1YOffset(int fontheight);
extern int GetShadow2XOffset(int fontheight);
extern int GetShadow2YOffset(int fontheight);

/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CRRadioCtrl, COleControl)
	//{{AFX_MSG_MAP(CRRadioCtrl)
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Dispatch map

BEGIN_DISPATCH_MAP(CRRadioCtrl, COleControl)
	//{{AFX_DISPATCH_MAP(CRRadioCtrl)
	DISP_PROPERTY_EX(CRRadioCtrl, "FontNum", GetFontNum, SetFontNum, VT_I4)
	DISP_PROPERTY_EX(CRRadioCtrl, "Cols", GetCols, SetCols, VT_I4)
	DISP_PROPERTY_EX(CRRadioCtrl, "CurrentSelection", GetCurrentSelection, SetCurrentSelection, VT_I4)
	DISP_PROPERTY_EX(CRRadioCtrl, "ColumnWidth", GetColumnWidth, SetColumnWidth, VT_I4)
	DISP_FUNCTION(CRRadioCtrl, "AddButton", AddButton, VT_EMPTY, VTS_BSTR)
	DISP_FUNCTION(CRRadioCtrl, "Clear", Clear, VT_EMPTY, VTS_NONE)
	DISP_STOCKPROP_FORECOLOR()
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()


/////////////////////////////////////////////////////////////////////////////
// Event map

BEGIN_EVENT_MAP(CRRadioCtrl, COleControl)
	//{{AFX_EVENT_MAP(CRRadioCtrl)
	EVENT_CUSTOM("Selected", FireSelected, VTS_I4)
	//}}AFX_EVENT_MAP
END_EVENT_MAP()


/////////////////////////////////////////////////////////////////////////////
// Property pages

// TODO: Add more property pages as needed.  Remember to increase the count!
BEGIN_PROPPAGEIDS(CRRadioCtrl, 2)
	PROPPAGEID(CRRadioPropPage::guid)
    PROPPAGEID(CLSID_CColorPropPage)
END_PROPPAGEIDS(CRRadioCtrl)


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CRRadioCtrl, "RRADIO.RRadioCtrl.1",
	0x5363ba22, 0xd90a, 0x11d1, 0xa1, 0xf0, 0, 0x80, 0xc8, 0x58, 0x2d, 0xe4)


/////////////////////////////////////////////////////////////////////////////
// Type library ID and version

IMPLEMENT_OLETYPELIB(CRRadioCtrl, _tlid, _wVerMajor, _wVerMinor)


/////////////////////////////////////////////////////////////////////////////
// Interface IDs

const IID BASED_CODE IID_DRRadio =
		{ 0x7ebc74e3, 0xf3c, 0x11d2, { 0xa1, 0xf0, 0, 0x80, 0xc8, 0x58, 0x2d, 0xe4 } };
const IID BASED_CODE IID_DRRadioEvents =
		{ 0x7ebc74e4, 0xf3c, 0x11d2, { 0xa1, 0xf0, 0, 0x80, 0xc8, 0x58, 0x2d, 0xe4 } };


/////////////////////////////////////////////////////////////////////////////
// Control type information

static const DWORD BASED_CODE _dwRRadioOleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CRRadioCtrl, IDS_RRADIO, _dwRRadioOleMisc)


/////////////////////////////////////////////////////////////////////////////
// CRRadioCtrl::CRRadioCtrlFactory::UpdateRegistry -
// Adds or removes system registry entries for CRRadioCtrl

BOOL CRRadioCtrl::CRRadioCtrlFactory::UpdateRegistry(BOOL bRegister)
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
			IDS_RRADIO,
			IDB_RRADIO,
			afxRegApartmentThreading,
			_dwRRadioOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}


/////////////////////////////////////////////////////////////////////////////
// Licensing strings

static const TCHAR BASED_CODE _szLicFileName[] = _T("RRadio.lic");

static const WCHAR BASED_CODE _szLicString[] =
	L"Copyright (c) 1998 Rowan Software";


/////////////////////////////////////////////////////////////////////////////
// CRRadioCtrl::CRRadioCtrlFactory::VerifyUserLicense -
// Checks for existence of a user license

BOOL CRRadioCtrl::CRRadioCtrlFactory::VerifyUserLicense()
{
	return AfxVerifyLicFile(AfxGetInstanceHandle(), _szLicFileName,
		_szLicString);
}


/////////////////////////////////////////////////////////////////////////////
// CRRadioCtrl::CRRadioCtrlFactory::GetLicenseKey -
// Returns a runtime licensing key

BOOL CRRadioCtrl::CRRadioCtrlFactory::GetLicenseKey(DWORD dwReserved,
	BSTR FAR* pbstrKey)
{
	if (pbstrKey == NULL)
		return FALSE;

	*pbstrKey = SysAllocString(_szLicString);
	return (*pbstrKey != NULL);
}


/////////////////////////////////////////////////////////////////////////////
// CRRadioCtrl::CRRadioCtrl - Constructor

CRRadioCtrl::CRRadioCtrl()
{
	InitializeIIDs(&IID_DRRadio, &IID_DRRadioEvents);
	m_hButtonDown=(HICON)LoadImage(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDI_BUTTONDOWN),IMAGE_ICON,32,32,LR_DEFAULTCOLOR);
	m_hButtonUp=(HICON)LoadImage(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDI_BUTTONUP),IMAGE_ICON,32,32,LR_DEFAULTCOLOR);
	m_CurSel=0;
	m_bitmapheight = 0 ; //woody 10/12/98 
	m_FirstSweep = TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CRRadioCtrl::~CRRadioCtrl - Destructor

CRRadioCtrl::~CRRadioCtrl()
{
	Clear();
}


/////////////////////////////////////////////////////////////////////////////
// CRRadioCtrl::OnDraw - Drawing function

void CRRadioCtrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
{
	if (m_bDrawing) return;
	m_bDrawing=TRUE;
	// need to use an offscreenDC soley because we are
	// using my crappy transparent blit function
	// which leaves pink flashes if not rendered offscreen
	CRect rc = rcBounds;
	CWnd* parent;
	if (m_hWnd) parent=GetParent();
	long offsetx;
	long offsety;
	CDC* pOffScreenDC;
	CBitmap* pOldBitmap;
	CBitmap bitmap;
	if (m_hWnd)
	{
		long offsets;
		offsets=parent->SendMessage(WM_GETXYOFFSET,NULL,NULL);
		CRect rect;
		this->GetWindowRect(rect);
		CRect parentrect;
		parent->GetWindowRect(parentrect);
		offsetx=short(offsets & 0x0000FFFF)+parentrect.left-rect.left;
		offsety=short((offsets & 0xFFFF0000)>>16)+parentrect.top-rect.top;
		if(m_FirstSweep != TRUE)
		{
			pOffScreenDC=(CDC*)parent->SendMessage(WM_GETOFFSCREENDC,NULL,NULL);
			bitmap.CreateCompatibleBitmap(pdc,rcBounds.right,rcBounds.bottom);
			pOldBitmap=pOffScreenDC->SelectObject(&bitmap);
		}
		else
		{
			pOffScreenDC=pdc;
		}
	}
	else
	{
		pOffScreenDC=pdc;
		offsetx=0;
		offsety=0;
	}
    CFont* pOldFont;
	if (m_hWnd) pOldFont = pOffScreenDC->SelectObject((CFont*)this->GetParent()->SendMessage(WM_GETGLOBALFONT,abs(m_FontNum),NULL));
	else pOldFont = pOffScreenDC->GetCurrentFont();
    pOffScreenDC->SetBkMode(TRANSPARENT);
    pOffScreenDC->SetTextAlign(TA_LEFT | TA_TOP);
    TEXTMETRIC tm;
    pOffScreenDC->GetTextMetrics(&tm);
	FileNum artnum=FIL_NULL;
	if (m_hWnd)
	{
		if(m_FirstSweep != TRUE)
		{
			artnum = (FileNum)parent->SendMessage(WM_GETARTWORK,NULL,NULL);
		}
		BYTE* pData;
		if (artnum)
		{
			pData = (BYTE*)parent->SendMessage(WM_GETFILE,artnum,NULL);
			if (pData[0]=='B' && pData[1]=='M') // checks if its a bitmap file
			{
				// now render it...
				BITMAPFILEHEADER* pFile=(BITMAPFILEHEADER*)pData;
				BITMAPINFO* pInfo=(BITMAPINFO*)(pData+sizeof(BITMAPFILEHEADER));
				pData+=pFile->bfOffBits;
				VERIFY(SetDIBitsToDevice(pOffScreenDC->m_hDC,offsetx,offsety,pInfo->bmiHeader.biWidth, pInfo->bmiHeader.biHeight,
					0,0,0,pInfo->bmiHeader.biHeight,pData,pInfo,DIB_RGB_COLORS));
			}
			parent->SendMessage(WM_RELEASELASTFILE,NULL,NULL);
		}
	}
	if (!artnum && m_FirstSweep != TRUE || !m_hWnd)
	{
		pOffScreenDC->FillRect(rcBounds, CBrush::FromHandle((HBRUSH)GetStockObject(BLACK_BRUSH)));
	}
	POSITION position = m_list.GetHeadPosition();
	int x=0;
	int y=0;
   	int bestyinc = 0 ;		// Woody 14/12/98
	int yoffset=(tm.tmHeight-32)/2;
	for (int z=0;z<m_list.GetCount();z++)
	{
		// first draw the button
		if (m_CurSel==z)
		{
			if (!m_hWnd || IsWindowEnabled())
				DrawTransparentBitmap(FIL_RADIO_BUTTON_DOWN,pOffScreenDC,x,y+yoffset);
			else
				DrawTransparentBitmap(FIL_RADIO_BUTTON_DOWN_DISABLED,pOffScreenDC,x,y+yoffset);
		}
		else
		{
			if (!m_hWnd || IsWindowEnabled())
				DrawTransparentBitmap(FIL_RADIO_BUTTON_UP,pOffScreenDC,x,y+yoffset);
			else
				DrawTransparentBitmap(FIL_RADIO_BUTTON_UP_DISABLED,pOffScreenDC,x,y+yoffset);
		}
		char* string=m_list.GetNext(position);
		if (m_FontNum<0)
		{
			TEXTMETRIC tm;
			pOffScreenDC->GetTextMetrics(&tm);
			pOffScreenDC->SetTextColor(RGB(0,0,0));
			int shadowx=GetShadow1XOffset(tm.tmHeight);
			int shadowy=GetShadow1YOffset(tm.tmHeight);
		    pOffScreenDC->TextOut(x+32+shadowx, y+shadowy, string);
			shadowx=GetShadow2XOffset(tm.tmHeight);
			shadowy=GetShadow2YOffset(tm.tmHeight);
		    pOffScreenDC->TextOut(x+32+shadowx, y+shadowy, string);
		}
	    pOffScreenDC->SetTextColor(TranslateColor(GetForeColor()));
	    pOffScreenDC->TextOut(x+32, y, string);
		x+=m_ColumnWidth*tm.tmAveCharWidth;
		if (x/(m_ColumnWidth*tm.tmAveCharWidth)>=m_Cols)
		{
			x=0;
			if (!bestyinc)							// Woody 14/12/98
			{
				if (m_bitmapheight > tm.tmHeight + 2 )	// Woody 14/12/98
					bestyinc = m_bitmapheight + 2 ;
				else
					bestyinc = tm.tmHeight + 2 ;	// Woody 14/12/98
			}
			y+=tm.tmHeight+2;
		}
	}
	if(m_hWnd && m_FirstSweep != TRUE)
	{
		pdc->BitBlt(0,0,rcBounds.right-rcBounds.left,rcBounds.bottom-rcBounds.top,pOffScreenDC,
						0,0,SRCCOPY)!=NULL; // flips offscreen dc to real dc
		pOffScreenDC->SelectObject(pOldBitmap);
	}
	m_FirstSweep = FALSE;
	pOffScreenDC->SelectObject(pOldFont);
	m_bDrawing=FALSE;
}

void CRRadioCtrl::DrawTransparentBitmap(FileNum filenum,CDC * pDC, int x, int y)
{
	// note that palette entry 254 is the transparent colour
	BYTE* pData;
	CWnd* parent=GetParent();
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
		if (!m_bitmapheight) // Woody 14/12/98
			m_bitmapheight = Height ;
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

/////////////////////////////////////////////////////////////////////////////
// CRRadioCtrl::DoPropExchange - Persistence support

void CRRadioCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);
	PX_Long(pPX, _T("FontNum"), m_FontNum, 0);
	PX_Long(pPX, _T("Cols"), m_Cols, 1);
	PX_Long(pPX, _T("ColumnWidth"), m_ColumnWidth, 30);
}


/////////////////////////////////////////////////////////////////////////////
// CRRadioCtrl::OnResetState - Reset control to default state

void CRRadioCtrl::OnResetState()
{
	COleControl::OnResetState();  // Resets defaults found in DoPropExchange
	SetFontNum(0);
	SetCols(1);
	SetColumnWidth(20);
	SetForeColor(RGB(255,255,255));
}


/////////////////////////////////////////////////////////////////////////////
// CRRadioCtrl message handlers

long CRRadioCtrl::GetFontNum() 
{
	return m_FontNum;
}

void CRRadioCtrl::SetFontNum(long nNewValue) 
{
	m_FontNum=nNewValue;
	InvalidateControl();
	SetModifiedFlag();
}

long CRRadioCtrl::GetCols() 
{
	return m_Cols;
}

void CRRadioCtrl::SetCols(long nNewValue) 
{
	m_Cols=nNewValue;
	InvalidateControl();
	SetModifiedFlag();
}

void CRRadioCtrl::AddButton(LPCTSTR text) 
{
	char* buffer=new char[strlen(text)+1]; // include terminating null character
	strcpy(buffer,text);
	m_list.AddTail(buffer);
	InvalidateControl();
}

void CRRadioCtrl::Clear() 
{
	POSITION position = m_list.GetHeadPosition();
	for (int y=0;y<m_list.GetCount();y++)
	{
		delete [] m_list.GetNext(position);
	}
	m_list.RemoveAll();
}

long CRRadioCtrl::GetCurrentSelection() 
{
	return m_CurSel;
}

void CRRadioCtrl::SetCurrentSelection(long nNewValue) 
{
	m_CurSel=nNewValue;
	InvalidateControl();
	SetModifiedFlag();
}

long CRRadioCtrl::GetColumnWidth() 
{
	return m_ColumnWidth;
}

void CRRadioCtrl::SetColumnWidth(long nNewValue) 
{
	m_ColumnWidth=nNewValue;
	InvalidateControl();
	SetModifiedFlag();
}

void CRRadioCtrl::OnLButtonDown(UINT nFlags, CPoint point) 
{
	int x=point.x;
	int y=point.y;
	CDC* pdc=GetDC();
    CFont* pOldFont;
	if (m_hWnd) pOldFont = pdc->SelectObject((CFont*)GetParent()->SendMessage(WM_GETGLOBALFONT,abs(m_FontNum),NULL));
	else pOldFont = pdc->GetCurrentFont();
    TEXTMETRIC tm;
    pdc->GetTextMetrics(&tm);
	x/=m_ColumnWidth*tm.tmAveCharWidth;
	if (x>=m_Cols) x=m_Cols-1;
	y/=tm.tmHeight+2;
	if (y>m_list.GetCount()/m_Cols) y=(m_list.GetCount()/m_Cols);
	int CurSel=x+(y*m_Cols);
	if (CurSel>=m_list.GetCount()) CurSel-=m_Cols;

	pdc->SelectObject(pOldFont);
	ReleaseDC(pdc);
	COleControl::OnLButtonDown(nFlags, point);

	if (CurSel!=m_CurSel)
	{
		m_CurSel=CurSel;
		InvalidateControl();
		GetParent()->SendMessage(WM_PLAYSOUND,FIL_SFX_OFFICE_TICK,NULL);//DAW 06Apr99
		FireSelected(m_CurSel);
	}
//moved up	pdc->SelectObject(pOldFont);
//	COleControl::OnLButtonDown(nFlags, point);
}
