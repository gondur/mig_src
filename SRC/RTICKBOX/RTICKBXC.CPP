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

// RTickBxC.cpp : Implementation of the CRTickBoxCtrl ActiveX Control class.

#include "stdafx.h"
#include "RTickBox.h"
#include "RTickBxC.h"
#include "RTickBxP.h"
#include "messages.h"
#include "fileman.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CRTickBoxCtrl, COleControl)
BOOL CRTickBoxCtrl::m_bDrawing = FALSE;

/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CRTickBoxCtrl, COleControl)
	//{{AFX_MSG_MAP(CRTickBoxCtrl)
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Dispatch map

BEGIN_DISPATCH_MAP(CRTickBoxCtrl, COleControl)
	//{{AFX_DISPATCH_MAP(CRTickBoxCtrl)
	DISP_PROPERTY_EX(CRTickBoxCtrl, "State", GetState, SetState, VT_BOOL)
	DISP_PROPERTY_EX(CRTickBoxCtrl, "FontNum", GetFontNum, SetFontNum, VT_I4)
	DISP_STOCKPROP_FORECOLOR()
	DISP_STOCKPROP_CAPTION()
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()


/////////////////////////////////////////////////////////////////////////////
// Event map

BEGIN_EVENT_MAP(CRTickBoxCtrl, COleControl)
	//{{AFX_EVENT_MAP(CRTickBoxCtrl)
	// NOTE - ClassWizard will add and remove event map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_EVENT_MAP
END_EVENT_MAP()


/////////////////////////////////////////////////////////////////////////////
// Property pages

// TODO: Add more property pages as needed.  Remember to increase the count!
BEGIN_PROPPAGEIDS(CRTickBoxCtrl, 2)
	PROPPAGEID(CRTickBoxPropPage::guid)
    PROPPAGEID(CLSID_CColorPropPage)
END_PROPPAGEIDS(CRTickBoxCtrl)


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CRTickBoxCtrl, "RTICKBOX.RTickBoxCtrl.1",
	0x840ed4a7, 0xcf9b, 0x11d1, 0xa1, 0xf0, 0, 0x80, 0xc8, 0x58, 0x2d, 0xe4)


/////////////////////////////////////////////////////////////////////////////
// Type library ID and version

IMPLEMENT_OLETYPELIB(CRTickBoxCtrl, _tlid, _wVerMajor, _wVerMinor)


/////////////////////////////////////////////////////////////////////////////
// Interface IDs

const IID BASED_CODE IID_DRTickBox =
		{ 0x840ed4a5, 0xcf9b, 0x11d1, { 0xa1, 0xf0, 0, 0x80, 0xc8, 0x58, 0x2d, 0xe4 } };
const IID BASED_CODE IID_DRTickBoxEvents =
		{ 0x840ed4a6, 0xcf9b, 0x11d1, { 0xa1, 0xf0, 0, 0x80, 0xc8, 0x58, 0x2d, 0xe4 } };


/////////////////////////////////////////////////////////////////////////////
// Control type information

static const DWORD BASED_CODE _dwRTickBoxOleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CRTickBoxCtrl, IDS_RTICKBOX, _dwRTickBoxOleMisc)


/////////////////////////////////////////////////////////////////////////////
// CRTickBoxCtrl::CRTickBoxCtrlFactory::UpdateRegistry -
// Adds or removes system registry entries for CRTickBoxCtrl

BOOL CRTickBoxCtrl::CRTickBoxCtrlFactory::UpdateRegistry(BOOL bRegister)
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
			IDS_RTICKBOX,
			IDB_RTICKBOX,
			afxRegApartmentThreading,
			_dwRTickBoxOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}


/////////////////////////////////////////////////////////////////////////////
// Licensing strings

static const TCHAR BASED_CODE _szLicFileName[] = _T("RTickBox.lic");

static const WCHAR BASED_CODE _szLicString[] =
	L"Copyright (c) 1998 Rowan Software";


/////////////////////////////////////////////////////////////////////////////
// CRTickBoxCtrl::CRTickBoxCtrlFactory::VerifyUserLicense -
// Checks for existence of a user license

BOOL CRTickBoxCtrl::CRTickBoxCtrlFactory::VerifyUserLicense()
{
	return AfxVerifyLicFile(AfxGetInstanceHandle(), _szLicFileName,
		_szLicString);
}


/////////////////////////////////////////////////////////////////////////////
// CRTickBoxCtrl::CRTickBoxCtrlFactory::GetLicenseKey -
// Returns a runtime licensing key

BOOL CRTickBoxCtrl::CRTickBoxCtrlFactory::GetLicenseKey(DWORD dwReserved,
	BSTR FAR* pbstrKey)
{
	if (pbstrKey == NULL)
		return FALSE;

	*pbstrKey = SysAllocString(_szLicString);
	return (*pbstrKey != NULL);
}


/////////////////////////////////////////////////////////////////////////////
// CRTickBoxCtrl::CRTickBoxCtrl - Constructor

CRTickBoxCtrl::CRTickBoxCtrl()
{
	InitializeIIDs(&IID_DRTickBox, &IID_DRTickBoxEvents);
	m_curPos=INT_MAX;
//	partwork=NULL;
//	artworkinfo.bmWidth=0;
	m_state=FALSE;
}


/////////////////////////////////////////////////////////////////////////////
// CRTickBoxCtrl::~CRTickBoxCtrl - Destructor

CRTickBoxCtrl::~CRTickBoxCtrl()
{
	// TODO: Cleanup your control's instance data here.
}


/////////////////////////////////////////////////////////////////////////////
// CRTickBoxCtrl::OnDraw - Drawing function

void CRTickBoxCtrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
{
	if (m_bDrawing) return;
	m_bDrawing=TRUE;
	CRect rc = rcBounds;
	CWnd* parent;
	if (m_hWnd) parent=this->GetParent();
	if (m_curPos==INT_MAX)
	{
		m_yes.LoadBitmap(IDB_YES);
		m_no.LoadBitmap(IDB_NO);
		m_curPos=0;
//		if (m_hWnd)
//		{
//			partwork = (CBitmap*)this->GetParent()->SendMessage(WM_GETARTWORK,NULL,NULL);
//			if(partwork)
//			{
//				partwork->GetBitmap(&artworkinfo);
//			}
//		}
	}
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
	if (m_hWnd) pOldFont = pdc->SelectObject((CFont*)this->GetParent()->SendMessage(WM_GETGLOBALFONT,m_FontNum,NULL));
	else pOldFont = pdc->GetCurrentFont();
    pdc->SetBkMode(TRANSPARENT);
    pdc->SetTextColor(TranslateColor(GetForeColor()));
    pdc->SetTextAlign(TA_LEFT | TA_TOP);
//	m_pic.Render(pdc,CRect(offsetx,offsety,hmWidth+offsetx,hmHeight+offsety),rcBounds);
	CDC memDC;
	memDC.CreateCompatibleDC(pdc);
	CBitmap* pOldBitmap;
	pOldBitmap=memDC.GetCurrentBitmap();
//	if ( artworkinfo.bmWidth)
//	{
//		memDC.SelectObject(partwork);
//		pdc->BitBlt(offsetx,offsety,artworkinfo.bmWidth,artworkinfo.bmHeight,&memDC,0,0,SRCCOPY);
//	}
//	else
//	{
//		pdc->FillRect(rcBounds, CBrush::FromHandle((HBRUSH)GetStockObject(BLACK_BRUSH)));
//	}
	FileNum artnum=FIL_NULL;
	if (m_hWnd)
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
	if (!artnum)
	{
		pdc->FillRect(rcBounds, CBrush::FromHandle((HBRUSH)GetStockObject(BLACK_BRUSH)));
	}
	if (m_state)
	{
		memDC.SelectObject(&m_yes);
		pdc->BitBlt(0,0,16,16,&memDC,0,0,SRCCOPY);
	}
	else
	{
		memDC.SelectObject(&m_no);
		pdc->BitBlt(0,0,16,16,&memDC,0,0,SRCCOPY);
	}
	memDC.SelectObject(pOldBitmap);
	memDC.DeleteDC();
    pdc->TextOut(20, 0, InternalGetText());
	m_bDrawing=FALSE;
}


/////////////////////////////////////////////////////////////////////////////
// CRTickBoxCtrl::DoPropExchange - Persistence support

void CRTickBoxCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);
	PX_Long(pPX, _T("FontNum"), m_FontNum, 0);
}


/////////////////////////////////////////////////////////////////////////////
// CRTickBoxCtrl::OnResetState - Reset control to default state

void CRTickBoxCtrl::OnResetState()
{
	COleControl::OnResetState();  // Resets defaults found in DoPropExchange

	// TODO: Reset any other control state here.
}


/////////////////////////////////////////////////////////////////////////////
// CRTickBoxCtrl message handlers

BOOL CRTickBoxCtrl::GetState() 
{
	return m_state;
}

void CRTickBoxCtrl::SetState(BOOL bNewValue) 
{
	m_state=bNewValue;
	InvalidateControl();
	SetModifiedFlag();
}

void CRTickBoxCtrl::OnTextChanged() 
{
	InvalidateControl();
	SetModifiedFlag();
	COleControl::OnTextChanged();
}

void CRTickBoxCtrl::OnLButtonDown(UINT nFlags, CPoint point) 
{
	SetState(!GetState());
	COleControl::OnLButtonDown(nFlags, point);
}

long CRTickBoxCtrl::GetFontNum() 
{
	return m_FontNum;
}

void CRTickBoxCtrl::SetFontNum(long nNewValue) 
{
	m_FontNum=nNewValue;
	InvalidateControl();
	SetModifiedFlag();
}
