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

// REditCtl.cpp : Implementation of the CREditCtrl ActiveX Control class.

#include "stdafx.h"
#include "REdit.h"
#include "REditCtl.h"
#include "REditPpg.h"
#include "messages.h"
#include "fileman.h"
#include "axcolors.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BOOL CREditCtrl::m_bDrawing = FALSE;

IMPLEMENT_DYNCREATE(CREditCtrl, COleControl)

extern int GetShadow1XOffset(int fontheight);
extern int GetShadow1YOffset(int fontheight);
extern int GetShadow2XOffset(int fontheight);
extern int GetShadow2YOffset(int fontheight);

/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CREditCtrl, COleControl)
	//{{AFX_MSG_MAP(CREditCtrl)
	ON_WM_LBUTTONDOWN()
	ON_WM_TIMER()
	ON_WM_KILLFOCUS()
	ON_WM_SETFOCUS()
	ON_WM_CHAR()
	ON_WM_KEYDOWN()
	ON_WM_GETDLGCODE()
	ON_WM_SETCURSOR()
	ON_WM_CREATE()
	ON_WM_KEYUP()
	//}}AFX_MSG_MAP
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Dispatch map

BEGIN_DISPATCH_MAP(CREditCtrl, COleControl)
	//{{AFX_DISPATCH_MAP(CREditCtrl)
	DISP_PROPERTY_EX(CREditCtrl, "FontNum", GetFontNum, SetFontNum, VT_I4)
	DISP_STOCKPROP_FORECOLOR()
	DISP_STOCKPROP_CAPTION()
	DISP_STOCKPROP_ENABLED()
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()


/////////////////////////////////////////////////////////////////////////////
// Event map

BEGIN_EVENT_MAP(CREditCtrl, COleControl)
	//{{AFX_EVENT_MAP(CREditCtrl)
	EVENT_CUSTOM("ReturnPressed", FireReturnPressed, VTS_BSTR)
	EVENT_CUSTOM("TextChanged", FireTextChanged, VTS_BSTR)
	//}}AFX_EVENT_MAP
END_EVENT_MAP()


/////////////////////////////////////////////////////////////////////////////
// Property pages

// TODO: Add more property pages as needed.  Remember to increase the count!
BEGIN_PROPPAGEIDS(CREditCtrl, 2)
	PROPPAGEID(CREditPropPage::guid)
    PROPPAGEID(CLSID_CColorPropPage)
END_PROPPAGEIDS(CREditCtrl)


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CREditCtrl, "REDIT.REditCtrl.1",
	0x499e2be6, 0xac32, 0x11d1, 0xa1, 0xf0, 0x44, 0x45, 0x53, 0x54, 0, 0)


/////////////////////////////////////////////////////////////////////////////
// Type library ID and version

IMPLEMENT_OLETYPELIB(CREditCtrl, _tlid, _wVerMajor, _wVerMinor)


/////////////////////////////////////////////////////////////////////////////
// Interface IDs

const IID BASED_CODE IID_DREdit =
		{ 0x499e2be4, 0xac32, 0x11d1, { 0xa1, 0xf0, 0x44, 0x45, 0x53, 0x54, 0, 0 } };
const IID BASED_CODE IID_DREditEvents =
		{ 0x499e2be5, 0xac32, 0x11d1, { 0xa1, 0xf0, 0x44, 0x45, 0x53, 0x54, 0, 0 } };


/////////////////////////////////////////////////////////////////////////////
// Control type information

static const DWORD BASED_CODE _dwREditOleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CREditCtrl, IDS_REDIT, _dwREditOleMisc)


/////////////////////////////////////////////////////////////////////////////
// CREditCtrl::CREditCtrlFactory::UpdateRegistry -
// Adds or removes system registry entries for CREditCtrl

BOOL CREditCtrl::CREditCtrlFactory::UpdateRegistry(BOOL bRegister)
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
			IDS_REDIT,
			IDB_REDIT,
			afxRegApartmentThreading,
			_dwREditOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}


/////////////////////////////////////////////////////////////////////////////
// Licensing strings

static const TCHAR BASED_CODE _szLicFileName[] = _T("REdit.lic");

static const WCHAR BASED_CODE _szLicString[] =
	L"Copyright (c) 1998 Rowan Software";


/////////////////////////////////////////////////////////////////////////////
// CREditCtrl::CREditCtrlFactory::VerifyUserLicense -
// Checks for existence of a user license

BOOL CREditCtrl::CREditCtrlFactory::VerifyUserLicense()
{
	return AfxVerifyLicFile(AfxGetInstanceHandle(), _szLicFileName,
		_szLicString);
}


/////////////////////////////////////////////////////////////////////////////
// CREditCtrl::CREditCtrlFactory::GetLicenseKey -
// Returns a runtime licensing key

BOOL CREditCtrl::CREditCtrlFactory::GetLicenseKey(DWORD dwReserved,
	BSTR FAR* pbstrKey)
{
	if (pbstrKey == NULL)
		return FALSE;

	*pbstrKey = SysAllocString(_szLicString);
	return (*pbstrKey != NULL);
}


/////////////////////////////////////////////////////////////////////////////
// CREditCtrl::CREditCtrl - Constructor

CREditCtrl::CREditCtrl()
{
	InitializeIIDs(&IID_DREdit, &IID_DREditEvents);
	m_timerID=0;
	m_bShowCursor=FALSE;
	m_curPoint=0;
	m_scrollPoint=0;
	m_curPos=INT_MAX;
	m_FirstSweep = TRUE;
//	partwork=NULL;
//	artworkinfo.bmWidth=0;
}


/////////////////////////////////////////////////////////////////////////////
// CREditCtrl::~CREditCtrl - Destructor

CREditCtrl::~CREditCtrl()
{
//	KillTimer(m_timerID); // Just in case (actually it causes an assert)
}


/////////////////////////////////////////////////////////////////////////////
// CREditCtrl::OnDraw - Drawing function

void CREditCtrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
{
	m_bDisabled = !GetEnabled();
	CRect rc = rcBounds;
	CWnd* parent;
    CFont* pOldFont;
	if (m_hWnd) parent=GetParent();
	if (m_hWnd) pOldFont = pdc->SelectObject((CFont*)parent->SendMessage(WM_GETGLOBALFONT,abs(m_FontNum),NULL));
	else pOldFont = pdc->GetCurrentFont();
	if (m_curPos==INT_MAX)
	{
		m_curPos=InternalGetText().GetLength();
		m_curPoint=pdc->GetTextExtent(InternalGetText()).cx;
//		if (m_hWnd)
//		{
//			partwork = (CBitmap*)this->GetParent()->SendMessage(WM_GETARTWORK,NULL,NULL);
//			if(partwork)
//			{
//				partwork->GetBitmap(&artworkinfo);
//			}
//		}
	}
	if (m_curPoint-(rc.Width()/2)<m_scrollPoint) m_scrollPoint=max(m_curPoint-(rc.Width()/2),0);
	if (m_curPoint-rc.Width()+4>m_scrollPoint) m_scrollPoint=m_curPoint-rc.Width()+4;
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
    pdc->SetBkMode(TRANSPARENT);
    pdc->SetTextAlign(TA_LEFT | TA_TOP);

//	m_pic.Render(pdc,CRect(offsetx,offsety,hmWidth+offsetx,hmHeight+offsety),rcBounds);
//	if ( artworkinfo.bmWidth)
//	{
//		CDC memDC;
//		memDC.CreateCompatibleDC(pdc);
//		CBitmap* pOldBitmap;
//		pOldBitmap = memDC.SelectObject(partwork);
//		pdc->BitBlt(offsetx,offsety,artworkinfo.bmWidth,artworkinfo.bmHeight,&memDC,0,0,SRCCOPY);
//		memDC.SelectObject(pOldBitmap);
//		memDC.DeleteDC();
//	}
//	else
//	{
//		pdc->FillRect(rcBounds, CBrush::FromHandle((HBRUSH)GetStockObject(BLACK_BRUSH)));
//	}
	FileNum artnum=FIL_NULL;
	BOOL X2flag=FALSE;
	if (m_hWnd && m_FirstSweep != TRUE)
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
		X2flag=parent->SendMessage(WM_GETX2FLAG,NULL,NULL);
	}
	if (!artnum && m_FirstSweep != TRUE || !m_hWnd)
	{
		pdc->FillRect(rcBounds, CBrush::FromHandle((HBRUSH)GetStockObject(BLACK_BRUSH)));
	}
	m_FirstSweep = FALSE;
	if (m_FontNum<0)
	{
		TEXTMETRIC tm;
		pdc->GetTextMetrics(&tm);
		pdc->SetTextColor(RGB(0,0,0));
		int shadowx=GetShadow1XOffset(tm.tmHeight);
		int shadowy=GetShadow1YOffset(tm.tmHeight);
	    pdc->ExtTextOut(2-m_scrollPoint+shadowx, 2+shadowy,
			ETO_CLIPPED, rc, InternalGetText(), InternalGetText().GetLength(), NULL);
		shadowx=GetShadow2XOffset(tm.tmHeight);
		shadowy=GetShadow2YOffset(tm.tmHeight);
	    pdc->ExtTextOut(2-m_scrollPoint+shadowx, 2+shadowy,
			ETO_CLIPPED, rc, InternalGetText(), InternalGetText().GetLength(), NULL);
	}
	if(m_bDisabled == FALSE)
	{
		pdc->SetTextColor(TranslateColor(GetForeColor()));
	}
	else
	{
		pdc->SetTextColor(RGB(128,128,128));
	}
    pdc->ExtTextOut(2-m_scrollPoint, 2,
		ETO_CLIPPED, rc, InternalGetText(), InternalGetText().GetLength(), NULL);
	if (m_bShowCursor && m_bDisabled == FALSE)
	{
		SetFocus();
		CPen pen(PS_SOLID,2,TranslateColor(GetForeColor()));
		pdc->SelectObject(pen);
		pdc->MoveTo(m_curPoint-m_scrollPoint+2,3);
		pdc->LineTo(m_curPoint-m_scrollPoint+2,pdc->GetTextExtent("jA").cy+2);
	}
	CPen BlackPen,WhitePen,pen;
	if (!m_hWnd || IsWindowEnabled())
	{
		BlackPen.CreatePen(PS_SOLID,1,AXC_DARKEDGE);
		WhitePen.CreatePen(PS_SOLID,1,AXC_LITEDGE);
	}
	else
	{
		BlackPen.CreatePen(PS_SOLID,1,AXC_DISABLEDDARKEDGE);
		WhitePen.CreatePen(PS_SOLID,1,AXC_DISABLEDLITEDGE);
	}

	if(m_bDisabled == TRUE)
	{
		pen.CreatePen(PS_SOLID,2,RGB(128,128,128));
		CPen* oldpen;
		oldpen=pdc->SelectObject(&pen);
		pdc->MoveTo(rcBounds.right-1,rcBounds.top+1);
		pdc->LineTo(rcBounds.right-1,rcBounds.bottom-1);
		pdc->LineTo(rcBounds.left,rcBounds.bottom-1);
		pdc->LineTo(rcBounds.left,rcBounds.top);
		pdc->LineTo(rcBounds.right,rcBounds.top);
		pdc->SelectObject(oldpen);
		pdc->SelectObject(pOldFont);
	}
	else
	{
		CPen* oldpen;
		oldpen=pdc->SelectObject(&WhitePen);
		pdc->MoveTo(rcBounds.right-1,rcBounds.top+1);
		pdc->LineTo(rcBounds.right-1,rcBounds.bottom-1);
		pdc->LineTo(rcBounds.left,rcBounds.bottom-1);
		pdc->SelectObject(&BlackPen);	
		pdc->LineTo(rcBounds.left,rcBounds.top);
		pdc->LineTo(rcBounds.right,rcBounds.top);
		pdc->SelectObject(oldpen);
		pdc->SelectObject(pOldFont);
	}	
}


/////////////////////////////////////////////////////////////////////////////
// CREditCtrl::DoPropExchange - Persistence support

void CREditCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);
	PX_Long(pPX, _T("FontNum"), m_FontNum, 0);
}


/////////////////////////////////////////////////////////////////////////////
// CREditCtrl::OnResetState - Reset control to default state

void CREditCtrl::OnResetState()
{
	COleControl::OnResetState();  // Resets defaults found in DoPropExchange
	SetForeColor(RGB(255,255,255));
}


/////////////////////////////////////////////////////////////////////////////
// CREditCtrl message handlers

void CREditCtrl::OnLButtonDown(UINT nFlags, CPoint point) 
{
	m_bDisabled = !GetEnabled();
	if (m_bDisabled) return;
	CDC* pdc;
	pdc=GetDC();
    CFont* pOldFont;
	if (m_hWnd) pOldFont = pdc->SelectObject((CFont*)this->GetParent()->SendMessage(WM_GETGLOBALFONT,abs(m_FontNum),NULL));
	else pOldFont = pdc->GetCurrentFont();
	// figure out where the user clicked the cursor
	m_curPoint=pdc->GetTextExtent(InternalGetText()).cx;
	m_curPos=InternalGetText().GetLength();
	for (int i=1;i<=m_curPos;i++)
	{
		if (point.x-2+m_scrollPoint<pdc->GetTextExtent(InternalGetText().Left(i)).cx)
		{
			m_curPoint=pdc->GetTextExtent(InternalGetText().Left(i-1)).cx;
			m_curPos=i-1;
			break;
		}
	}
//	pdc->SelectObject(pOldFont);
	this->ReleaseDC(pdc);
	SetFocus();
	if (m_timerID)
	{
		m_bShowCursor=TRUE;
		InvalidateControl();
	}
    pdc->SelectObject(pOldFont);
	ReleaseDC(pdc);
	COleControl::OnLButtonDown(nFlags, point);
}

void CREditCtrl::OnTimer(UINT nIDEvent) 
{
	if (nIDEvent==m_timerID)
	{
		m_bShowCursor=!m_bShowCursor;
		InvalidateControl();
	}
	COleControl::OnTimer(nIDEvent);
}

void CREditCtrl::OnKillFocus(CWnd* pNewWnd) 
{
	COleControl::OnKillFocus(pNewWnd);
	if (m_curPos!=INT_MAX)
	{
		KillTimer(m_timerID);
		m_timerID=0;
		m_bShowCursor=FALSE;
		InvalidateControl();
	}
}

void CREditCtrl::OnSetFocus(CWnd* pOldWnd) 
{
	COleControl::OnSetFocus(pOldWnd);
	if (!m_timerID)
	{
		m_timerID=SetTimer(3474,500,NULL);
	}
}

void CREditCtrl::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{	
	m_bDisabled = !GetEnabled();
	if (m_bDisabled) return;
	TRACE1("virtual: %c\n",nChar);
	CDC* pdc;
	pdc=GetDC();
    CFont* pOldFont;
	if (m_hWnd) pOldFont = pdc->SelectObject((CFont*)GetParent()->SendMessage(WM_GETGLOBALFONT,abs(m_FontNum),NULL));
	else pOldFont = pdc->GetCurrentFont();
	switch (nChar)
	{
		case VK_BACK:
			if(m_curPos>0)
			{
				m_curPos--;
				CString buffer=InternalGetText().Left(m_curPos);
				SetWindowText(buffer+InternalGetText().Right(InternalGetText().GetLength()-m_curPos-1));
				InvalidateControl();
			}
			break;
		case VK_DELETE:
			if(m_curPos<InternalGetText().GetLength())
			{
				CString buffer=InternalGetText().Left(m_curPos);
				SetWindowText(buffer+InternalGetText().Right(InternalGetText().GetLength()-m_curPos-1));
				InvalidateControl();
			}
			break;
		case VK_LEFT:
			if(m_curPos>0)
			{
				m_curPos--;
				InvalidateControl();
			}
			break;
		case VK_RIGHT:
			if(m_curPos<InternalGetText().GetLength())
			{
				m_curPos++;
				InvalidateControl();
			}
			break;
		case VK_HOME:
			m_curPos=0;
			break;
		case VK_END:
			m_curPos=InternalGetText().GetLength();
			break;
		case VK_RETURN:
			FireReturnPressed(InternalGetText());
			if (m_curPos > InternalGetText().GetLength())			  //AMM 06/07/99
			{														  //AMM 06/07/99
				m_curPos=InternalGetText().GetLength();				  //AMM 06/07/99
			}														  //AMM 06/07/99
			TRACE0("User pressed Enter\n");
			break;
	}
	m_curPoint=pdc->GetTextExtent(InternalGetText().Left(m_curPos)).cx;
	SetWindowText(InternalGetText());
//DeadCode DAW 09Mar99 	FireTextChanged(InternalGetText());
	pdc->SelectObject(pOldFont);
	ReleaseDC(pdc);
//	FireTextChanged(InternalGetText());
	COleControl::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CREditCtrl::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	m_bDisabled = !GetEnabled();
	if (m_bDisabled) return;
	TRACE1("char: %d\n",nChar);
	if (nChar>31 && nChar!=':' && nChar!='/' && nChar!='\\' && nChar!='$')
	{
		// insert the character in the right place...
		CDC* pdc;
		pdc=GetDC();
	    CFont* pOldFont;
		if (m_hWnd) pOldFont = pdc->SelectObject((CFont*)this->GetParent()->SendMessage(WM_GETGLOBALFONT,abs(m_FontNum),NULL));
		else pOldFont = pdc->GetCurrentFont();
		CString buffer=InternalGetText().Left(m_curPos);
		buffer+=(char)nChar;
		buffer+=InternalGetText().Right(InternalGetText().GetLength()-m_curPos);
		SetWindowText(buffer);
		m_curPos++;
		m_curPoint+=pdc->GetTextExtent((char)nChar).cx;
		SetWindowText(InternalGetText());
	    pdc->SelectObject(pOldFont);
		ReleaseDC(pdc);
		InvalidateControl();
//DeadCode DAW 09Mar99 		FireTextChanged(InternalGetText());
	}
	COleControl::OnChar(nChar, nRepCnt, nFlags);
}

UINT CREditCtrl::OnGetDlgCode() 
{
	return DLGC_WANTARROWS|DLGC_WANTALLKEYS|DLGC_WANTCHARS;
}

BOOL CREditCtrl::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	::SetCursor(AfxGetApp()->LoadStandardCursor(IDC_IBEAM));
	return TRUE;
//	return COleControl::OnSetCursor(pWnd, nHitTest, message);
}

int CREditCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (COleControl::OnCreate(lpCreateStruct) == -1)
		return -1;
	return 0;
}

long CREditCtrl::GetFontNum() 
{
	return m_FontNum;
}

void CREditCtrl::SetFontNum(long nNewValue) 
{
	m_FontNum=nNewValue;
	InvalidateControl();
	SetModifiedFlag();
}

void CREditCtrl::OnTextChanged() 
{
	InvalidateControl();
	SetModifiedFlag();	
	COleControl::OnTextChanged();
}

void CREditCtrl::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
//	COleControl::OnKeyUp(nChar, nRepCnt, nFlags);
	CDC* pdc;
	pdc=GetDC();
    CFont* pOldFont;
	if (m_hWnd) pOldFont = pdc->SelectObject((CFont*)GetParent()->SendMessage(WM_GETGLOBALFONT,abs(m_FontNum),NULL));
	else pOldFont = pdc->GetCurrentFont();

	{	//Jim's new code in firetextchanged...
		char*	backup=new char[InternalGetText().GetLength()+10];
		char*	buffer=new char[InternalGetText().GetLength()+10];
		strcpy	(backup,InternalGetText());
		strcpy	(buffer,InternalGetText());
		FireTextChanged(buffer);
		if (strcmp(backup,buffer))
		{
			if (strlen(buffer)>strlen(backup)+10)
				INT3;
			if (m_curPos>strlen(buffer))
				m_curPos=strlen(buffer);
			m_curPoint=pdc->GetTextExtent(InternalGetText().Left(m_curPos)).cx;
			SetText(buffer);
			SetWindowText(InternalGetText());

		}
		delete [] backup;
		delete [] buffer;
	}
    pdc->SelectObject(pOldFont);
	ReleaseDC(pdc);


}
