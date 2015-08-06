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

// RStaticC.cpp : Implementation of the CRStaticCtrl ActiveX Control class.

#include "stdafx.h"
#include "RStatic.h"
#include "RStaticC.h"
#include "RStaticP.h"
#include "messages.h"
#include "Fileman.h"
#include "..\mfc\resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BOOL CRStaticCtrl::m_bDrawing = FALSE;
extern int GetShadow1XOffset(int fontheight);
extern int GetShadow1YOffset(int fontheight);
extern int GetShadow2XOffset(int fontheight);
extern int GetShadow2YOffset(int fontheight);

IMPLEMENT_DYNCREATE(CRStaticCtrl, COleControl)
extern int GetResourceNumberFromID(const char* text);
extern BOOL ConvertResourceID(const char* text, char* output);

/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CRStaticCtrl, COleControl)
	//{{AFX_MSG_MAP(CRStaticCtrl)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	//}}AFX_MSG_MAP
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Dispatch map

BEGIN_DISPATCH_MAP(CRStaticCtrl, COleControl)
	//{{AFX_DISPATCH_MAP(CRStaticCtrl)
	DISP_PROPERTY_NOTIFY(CRStaticCtrl, "UpdateCaption", m_updateCaption, OnUpdateCaptionChanged, VT_BOOL)
	DISP_PROPERTY_EX(CRStaticCtrl, "FontNum", GetFontNum, SetFontNum, VT_I4)
	DISP_PROPERTY_EX(CRStaticCtrl, "String", GetString, SetString, VT_BSTR)
	DISP_PROPERTY_EX(CRStaticCtrl, "ResourceNumber", GetResourceNumber, SetResourceNumber, VT_I4)
	DISP_PROPERTY_EX(CRStaticCtrl, "PictureFileNum", GetPictureFileNum, SetPictureFileNum, VT_I4)
	DISP_PROPERTY_EX(CRStaticCtrl, "Central", GetCentral, SetCentral, VT_BOOL)
	DISP_PROPERTY_EX(CRStaticCtrl, "ShadowColor", GetShadowColor, SetShadowColor, VT_COLOR)
	DISP_STOCKPROP_CAPTION()
	DISP_STOCKPROP_FORECOLOR()
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()


/////////////////////////////////////////////////////////////////////////////
// Event map

BEGIN_EVENT_MAP(CRStaticCtrl, COleControl)
	//{{AFX_EVENT_MAP(CRStaticCtrl)
	// NOTE - ClassWizard will add and remove event map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_EVENT_MAP
END_EVENT_MAP()


/////////////////////////////////////////////////////////////////////////////
// Property pages

// TODO: Add more property pages as needed.  Remember to increase the count!
BEGIN_PROPPAGEIDS(CRStaticCtrl, 2)
	PROPPAGEID(CRStaticPropPage::guid)
    PROPPAGEID(CLSID_CColorPropPage)
END_PROPPAGEIDS(CRStaticCtrl)


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CRStaticCtrl, "RSTATIC.RStaticCtrl.1",
	0xc42bac3d, 0xca3c, 0x11d1, 0xa1, 0xf0, 0x44, 0x45, 0x53, 0x54, 0, 0)


/////////////////////////////////////////////////////////////////////////////
// Type library ID and version

IMPLEMENT_OLETYPELIB(CRStaticCtrl, _tlid, _wVerMajor, _wVerMinor)


/////////////////////////////////////////////////////////////////////////////
// Interface IDs

const IID BASED_CODE IID_DRStatic =
		{ 0xc42bac3b, 0xca3c, 0x11d1, { 0xa1, 0xf0, 0x44, 0x45, 0x53, 0x54, 0, 0 } };
const IID BASED_CODE IID_DRStaticEvents =
		{ 0xc42bac3c, 0xca3c, 0x11d1, { 0xa1, 0xf0, 0x44, 0x45, 0x53, 0x54, 0, 0 } };


/////////////////////////////////////////////////////////////////////////////
// Control type information

static const DWORD BASED_CODE _dwRStaticOleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CRStaticCtrl, IDS_RSTATIC, _dwRStaticOleMisc)


/////////////////////////////////////////////////////////////////////////////
// CRStaticCtrl::CRStaticCtrlFactory::UpdateRegistry -
// Adds or removes system registry entries for CRStaticCtrl

BOOL CRStaticCtrl::CRStaticCtrlFactory::UpdateRegistry(BOOL bRegister)
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
			IDS_RSTATIC,
			IDB_RSTATIC,
			afxRegApartmentThreading,
			_dwRStaticOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}


/////////////////////////////////////////////////////////////////////////////
// Licensing strings

static const TCHAR BASED_CODE _szLicFileName[] = _T("RStatic.lic");

static const WCHAR BASED_CODE _szLicString[] =
	L"Copyright (c) 1998 Rowan Software";


/////////////////////////////////////////////////////////////////////////////
// CRStaticCtrl::CRStaticCtrlFactory::VerifyUserLicense -
// Checks for existence of a user license

BOOL CRStaticCtrl::CRStaticCtrlFactory::VerifyUserLicense()
{
	return AfxVerifyLicFile(AfxGetInstanceHandle(), _szLicFileName,
		_szLicString);
}


/////////////////////////////////////////////////////////////////////////////
// CRStaticCtrl::CRStaticCtrlFactory::GetLicenseKey -
// Returns a runtime licensing key

BOOL CRStaticCtrl::CRStaticCtrlFactory::GetLicenseKey(DWORD dwReserved,
	BSTR FAR* pbstrKey)
{
	if (pbstrKey == NULL)
		return FALSE;

	*pbstrKey = SysAllocString(_szLicString);
	return (*pbstrKey != NULL);
}


/////////////////////////////////////////////////////////////////////////////
// CRStaticCtrl::CRStaticCtrl - Constructor

CRStaticCtrl::CRStaticCtrl()
{
	InitializeIIDs(&IID_DRStatic, &IID_DRStaticEvents);
	m_bCentral=FALSE;
	m_PictureFileNum=FIL_NULL;
	m_FirstSweep = TRUE;
	//	m_ShadowColor = RGB(0,0,0);
	gotparentwnd=false;
}

void	CRStaticCtrl::GetParentWndInfo()
{
	if (!gotparentwnd)
	{
		gotparentwnd=true;
		if (m_hWnd)
		{
			CWnd* parent = GetParent();	//JW 15Dec98
			if (parent)
			{
				char workspace[100];
				workspace[0]=99;
				if (m_ResourceNumber && m_ResourceNumber!=IDS_NONE)
				{
					int strsize=parent->SendMessage(WM_GETSTRING,m_ResourceNumber,(int)workspace);
					m_string=workspace;
				}
				else
					m_string="";
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////
// CRStaticCtrl::~CRStaticCtrl - Destructor

CRStaticCtrl::~CRStaticCtrl()
{
	// TODO: Cleanup your control's instance data here.
}


/////////////////////////////////////////////////////////////////////////////
// CRStaticCtrl::OnDraw - Drawing function

void CRStaticCtrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
{
	if (m_bDrawing) return;
	GetParentWndInfo();
	CDC* pdc2;
	CBitmap* pOldBitmap;
	CBitmap bitmap;
	// if we are drawing a transparent bitmap we need to use an offscreenDC
	// to prevent flicker.  But this slows down drawing so only do so if
	// we really have to
	CWnd* parent;
	if (m_hWnd) parent=GetParent();
	if (m_PictureFileNum && m_hWnd)
	{
		pdc2=pdc;
		pdc=(CDC*)parent->SendMessage(WM_GETOFFSCREENDC,NULL,NULL);
		bitmap.CreateCompatibleBitmap(pdc2,rcBounds.right,rcBounds.bottom);
		pOldBitmap=pdc->SelectObject(&bitmap);
	}
	m_bDrawing=TRUE;
	CRect rc = rcBounds;
	long offsetx;
	long offsety;
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
	}
	else
	{
		offsetx=0;
		offsety=0;
	}
    CFont* pOldFont;
	if (m_hWnd) pOldFont = pdc->SelectObject((CFont*)this->GetParent()->SendMessage(WM_GETGLOBALFONT,abs(m_FontNum),NULL));
	else pOldFont = pdc->GetCurrentFont();
    pdc->SetBkMode(TRANSPARENT);
	if (m_bCentral)
	    pdc->SetTextAlign(TA_CENTER | TA_TOP);
	else
    	pdc->SetTextAlign(TA_LEFT | TA_TOP);
	FileNum artnum=FIL_NULL;
	if (m_hWnd && m_FirstSweep != TRUE || m_PictureFileNum != FIL_NULL) 
	{
		artnum = (FileNum)parent->SendMessage(WM_GETARTWORK,NULL,NULL);
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
				VERIFY(SetDIBitsToDevice(pdc->m_hDC,offsetx,offsety,pInfo->bmiHeader.biWidth, pInfo->bmiHeader.biHeight,
					0,0,0,pInfo->bmiHeader.biHeight,pData,pInfo,DIB_RGB_COLORS));
			}
			parent->SendMessage(WM_RELEASELASTFILE,NULL,NULL);
		}
	}
	if (!artnum && m_FirstSweep != TRUE && m_PictureFileNum == FIL_NULL || !m_hWnd)
	{
		pdc->FillRect(rcBounds, CBrush::FromHandle((HBRUSH)GetStockObject(BLACK_BRUSH)));
	}
	m_FirstSweep = FALSE;
	// slice the string into seperate lines if necessary...
	int length=0;
	int width=rc.Width();
//	char c;
//	for (int i=0;i<m_string.GetLength();i++)
//	{
//		c=m_string[i];
//		length+=pdc->GetTextExtent(&c,1).cx;
//		if (length>width) // search backwards for the first space
//		{
//			while (m_string[i]!=' ')
//			{
//				i--;
//				if (i<0) break;
//			}
//			m_string.SetAt(i,'\n');
//			length=0;
//		}
//	}
	if (m_PictureFileNum && m_hWnd)
		DrawTransparentBitmap(m_PictureFileNum,pdc);

	if (m_FontNum<0)
	{
		pdc->SetTextColor(RGB(0,0,0));
	    TEXTMETRIC tm;
	    pdc->GetTextMetrics(&tm);
		pdc->SetTextColor(m_ShadowColor);
//		pdc->SetTextColor(RGB(0,0,0));
		int shadowx=GetShadow1XOffset(tm.tmHeight);
		int shadowy=GetShadow1YOffset(tm.tmHeight);
		CRect rc2=rc+CPoint(shadowx, shadowy);
		if (m_bCentral)											//MS 01Apr99
			pdc->TextOut(rc2.right/2,rc2.top, m_string);		//MS 01Apr99
		else
		    pdc->DrawText(m_string,rc2,DT_LEFT+DT_WORDBREAK);
		shadowx=GetShadow2XOffset(tm.tmHeight);
		shadowy=GetShadow2YOffset(tm.tmHeight);
		rc2=rc+CPoint(shadowx, shadowy);
		if (m_bCentral)											//MS 01Apr99
			pdc->TextOut(rc2.right/2,rc2.top, m_string);
		else
	    	pdc->DrawText(m_string,rc2,DT_LEFT+DT_WORDBREAK);
	}
    pdc->SetTextColor(TranslateColor(GetForeColor()));
	if (m_bCentral)
		pdc->TextOut(rc.right/2, 0, m_string);
	else
    	pdc->DrawText(m_string,rc,DT_LEFT+DT_WORDBREAK+DT_TABSTOP);
	if (m_PictureFileNum && m_hWnd)
	{
		pdc2->BitBlt(0,0,rcBounds.right-rcBounds.left,rcBounds.bottom-rcBounds.top,pdc,
						0,0,SRCCOPY)!=NULL; // flips offscreen dc to real dc
		pdc->SelectObject(pOldBitmap);
	}
	m_bDrawing=FALSE;

}	//USE int height=pdc->DrawText(m_string,rc,DT_LEFT+DT_WORDBREAK+DT_CALCRECT);


/////////////////////////////////////////////////////////////////////////////
// CRStaticCtrl::DoPropExchange - Persistence support

void CRStaticCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);
	PX_Long(pPX, _T("FontNum"), m_FontNum, 0);
	PX_String(pPX, _T("String"), m_string, _T(""));
	PX_Long(pPX, _T("ResourceNumber"), m_ResourceNumber, 0);
//	PX_Color(pPX, _T("ShadowColor"), m_ShadowColor, FALSE);
	if (pPX->GetVersion()&0x1)
	{
        PX_Color(pPX, _T("ShadowColor"), m_ShadowColor, FALSE);
	}
    else 
	{
		m_ShadowColor = RGB(0,0,0);
	}
}


/////////////////////////////////////////////////////////////////////////////
// CRStaticCtrl::OnResetState - Reset control to default state

void CRStaticCtrl::OnResetState()
{
	COleControl::OnResetState();  // Resets defaults found in DoPropExchange
	SetForeColor(RGB(255,255,255));
	SetShadowColor(RGB(0,0,0));
	m_FontNum=0;
}


/////////////////////////////////////////////////////////////////////////////
// CRStaticCtrl message handlers

long CRStaticCtrl::GetFontNum() 
{
	return m_FontNum;
}

void CRStaticCtrl::SetFontNum(long nNewValue) 
{
	m_FontNum=nNewValue;
	InvalidateControl();
	SetModifiedFlag();
}

void CRStaticCtrl::OnTextChanged() 
{
	COleControl::OnTextChanged();
}

BSTR CRStaticCtrl::GetString() 
{
	GetParentWndInfo();
	return m_string.AllocSysString();
}

void CRStaticCtrl::SetString(LPCTSTR lpszNewValue) 
{
	GetParentWndInfo();
	m_string=lpszNewValue;
	InvalidateControl();
	SetModifiedFlag();
}

long CRStaticCtrl::GetResourceNumber() 
{
	return m_ResourceNumber;
}

void CRStaticCtrl::SetResourceNumber(long nNewValue) 
{
	m_ResourceNumber=nNewValue;
	SetModifiedFlag();
}

void CRStaticCtrl::OnUpdateCaptionChanged() 
{
	GetParentWndInfo();
	m_ResourceNumber=GetResourceNumberFromID(InternalGetText());
	if (m_ResourceNumber==-1)
	{
//		this->MessageBox("That was not a valid resource ID","ERROR");
//		SetText(strcat("Invalid ID: ",InternalGetText()));
		SetString("Invalid ID!");
	}
	else
	{
		char output[100];
		if (!ConvertResourceID(InternalGetText(),output))
		{
//			this->MessageBox("That resource ID is not equivalent to anything","ERROR");
			SetString("Invalid ID!");
		}
		else SetString(output);
	}
	InvalidateControl();
	SetModifiedFlag();	
}

void CRStaticCtrl::OnLButtonDown(UINT nFlags, CPoint point) 
{
	GetParentWndInfo();
	CRect rect;
	GetWindowRect(rect);
	CRect parentrect;
	GetParent()->GetClientRect(parentrect);
	GetParent()->ClientToScreen(parentrect);
	point+=rect.TopLeft()-parentrect.TopLeft();
	LPARAM lparam;
	lparam = point.x+(point.y<<16);
	ReleaseCapture();
	GetParent()->SendMessage(WM_LBUTTONDOWN,nFlags,lparam);
	return;
}
void CRStaticCtrl::OnLButtonUp(UINT nFlags, CPoint point) 
{
	GetParentWndInfo();
	CRect rect;
	GetWindowRect(rect);
	CRect parentrect;
	GetParent()->GetClientRect(parentrect);
	GetParent()->ClientToScreen(parentrect);
	point+=rect.TopLeft()-parentrect.TopLeft();
	LPARAM lparam;
	lparam = point.x+(point.y<<16);
	ReleaseCapture();
	GetParent()->SendMessage(WM_LBUTTONUP,nFlags,lparam);
	return;
}

long CRStaticCtrl::GetPictureFileNum() 
{
	return (long)m_PictureFileNum;
}

void CRStaticCtrl::SetPictureFileNum(long nNewValue) 
{
	m_PictureFileNum=(FileNum)nNewValue;
	SetModifiedFlag();
	InvalidateControl();
}

BOOL CRStaticCtrl::GetCentral() 								//MS 01Apr99
{
	return m_bCentral;
}

void CRStaticCtrl::SetCentral(BOOL bNewValue) 					//MS 01Apr99
{
	m_bCentral=bNewValue;
	SetModifiedFlag();
}

void CRStaticCtrl::DrawTransparentBitmap(FileNum filenum,CDC * pDC, int x, int y)
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


OLE_COLOR CRStaticCtrl::GetShadowColor() 
{
	return m_ShadowColor;
//	return RGB(0,0,0);
}

void CRStaticCtrl::SetShadowColor(OLE_COLOR nNewValue) 
{
	m_ShadowColor = nNewValue;
	SetModifiedFlag();
}
