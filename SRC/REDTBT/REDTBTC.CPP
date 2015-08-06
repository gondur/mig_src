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

// REdtBtCtl.cpp : Implementation of the CREdtBtCtrl ActiveX Control class.
//DEADCODE RDH 28/02/99 #define F_SOUNDS
#define F_BATTLE
#define F_COMMON

#include "stdafx.h"
#include "REdtBt.h"
#include "REdtBtC.h"
#include "REdtBtP.h"
#include "messages.h"
#include "fileman.h"
#include "axcolors.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BOOL CREdtBtCtrl::m_bDrawing = FALSE;
Bool CREdtBtCtrl::m_bDrawOffscreen = FALSE;
IMPLEMENT_DYNCREATE(CREdtBtCtrl, COleControl)

extern int GetShadow1XOffset(int fontheight);
extern int GetShadow1YOffset(int fontheight);
extern int GetShadow2XOffset(int fontheight);
extern int GetShadow2YOffset(int fontheight);

/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CREdtBtCtrl, COleControl)
	//{{AFX_MSG_MAP(CREdtBtCtrl)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_MESSAGE( WM_CANACCEPTDROP, OnCanAcceptDrop)
	ON_MESSAGE( WM_DROPPEDON, OnDroppedOn)
	//}}AFX_MSG_MAP
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Dispatch map

BEGIN_DISPATCH_MAP(CREdtBtCtrl, COleControl)
	//{{AFX_DISPATCH_MAP(CREdtBtCtrl)
	DISP_PROPERTY_EX(CREdtBtCtrl, "FontNum", GetFontNum, SetFontNum, VT_I4)
	DISP_PROPERTY_EX(CREdtBtCtrl, "DragAndDropID", GetDragAndDropID, SetDragAndDropID, VT_I4)
	DISP_FUNCTION(CREdtBtCtrl, "SetPictureFileNum", SetPictureFileNum, VT_EMPTY, VTS_I4)
	DISP_STOCKPROP_FORECOLOR()
	DISP_STOCKPROP_CAPTION()
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()


/////////////////////////////////////////////////////////////////////////////
// Event map

BEGIN_EVENT_MAP(CREdtBtCtrl, COleControl)
	//{{AFX_EVENT_MAP(CREdtBtCtrl)
	EVENT_CUSTOM("Clicked", FireClicked, VTS_NONE)
	EVENT_CUSTOM("CanAcceptDrop", FireCanAcceptDrop, VTS_I4  VTS_PBOOL)
	EVENT_CUSTOM("DroppedOn", FireDroppedOn, VTS_I4)
	//}}AFX_EVENT_MAP
END_EVENT_MAP()


/////////////////////////////////////////////////////////////////////////////
// Property pages

// TODO: Add more property pages as needed.  Remember to increase the count!
BEGIN_PROPPAGEIDS(CREdtBtCtrl, 2)
	PROPPAGEID(CREdtBtPropPage::guid)
    PROPPAGEID(CLSID_CColorPropPage)
END_PROPPAGEIDS(CREdtBtCtrl)


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CREdtBtCtrl, "REDTBT.REdtBtCtrl.1",
	0x461a1fe3, 0xb81b, 0x11d1, 0xa1, 0xf0, 0x44, 0x45, 0x53, 0x54, 0, 0)


/////////////////////////////////////////////////////////////////////////////
// Type library ID and version

IMPLEMENT_OLETYPELIB(CREdtBtCtrl, _tlid, _wVerMajor, _wVerMinor)


/////////////////////////////////////////////////////////////////////////////
// Interface IDs

const IID BASED_CODE IID_DREdtBt =
		{ 0x461a1fe1, 0xb81b, 0x11d1, { 0xa1, 0xf0, 0x44, 0x45, 0x53, 0x54, 0, 0 } };
const IID BASED_CODE IID_DREdtBtEvents =
		{ 0x461a1fe2, 0xb81b, 0x11d1, { 0xa1, 0xf0, 0x44, 0x45, 0x53, 0x54, 0, 0 } };


/////////////////////////////////////////////////////////////////////////////
// Control type information

static const DWORD BASED_CODE _dwREdtBtOleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CREdtBtCtrl, IDS_REDTBT, _dwREdtBtOleMisc)


/////////////////////////////////////////////////////////////////////////////
// CREdtBtCtrl::CREdtBtCtrlFactory::UpdateRegistry -
// Adds or removes system registry entries for CREdtBtCtrl

BOOL CREdtBtCtrl::CREdtBtCtrlFactory::UpdateRegistry(BOOL bRegister)
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
			IDS_REDTBT,
			IDB_REDTBT,
			afxRegApartmentThreading,
			_dwREdtBtOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}


/////////////////////////////////////////////////////////////////////////////
// Licensing strings

static const TCHAR BASED_CODE _szLicFileName[] = _T("REdtBt.lic");

static const WCHAR BASED_CODE _szLicString[] =
	L"Copyright (c) 1998 Rowan Software";


/////////////////////////////////////////////////////////////////////////////
// CREdtBtCtrl::CREdtBtCtrlFactory::VerifyUserLicense -
// Checks for existence of a user license

BOOL CREdtBtCtrl::CREdtBtCtrlFactory::VerifyUserLicense()
{
	return AfxVerifyLicFile(AfxGetInstanceHandle(), _szLicFileName,
		_szLicString);
}


/////////////////////////////////////////////////////////////////////////////
// CREdtBtCtrl::CREdtBtCtrlFactory::GetLicenseKey -
// Returns a runtime licensing key

BOOL CREdtBtCtrl::CREdtBtCtrlFactory::GetLicenseKey(DWORD dwReserved,
	BSTR FAR* pbstrKey)
{
	if (pbstrKey == NULL)
		return FALSE;

	*pbstrKey = SysAllocString(_szLicString);
	return (*pbstrKey != NULL);
}


/////////////////////////////////////////////////////////////////////////////
// CREdtBtCtrl::CREdtBtCtrl - Constructor

CREdtBtCtrl::CREdtBtCtrl()
{
	InitializeIIDs(&IID_DREdtBt, &IID_DREdtBtEvents);
	m_Init=TRUE;
	captiontext="";
	m_DragAndDropID=0;
	m_bCanAcceptDrop=FALSE;
	m_LButtonDown=FALSE;
	m_bDragging=FALSE;
	m_TransparentPicture = (FileNum)NULL ;									//RDH 23Dec98
	m_FirstSweep = TRUE;
//	partwork=NULL;
//	artworkinfo.bmWidth=0;
}


/////////////////////////////////////////////////////////////////////////////
// CREdtBtCtrl::~CREdtBtCtrl - Destructor

CREdtBtCtrl::~CREdtBtCtrl()
{
	// TODO: Cleanup your control's instance data here.
}


/////////////////////////////////////////////////////////////////////////////
// CREdtBtCtrl::OnDraw - Drawing function

void CREdtBtCtrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
{
	if (m_bDrawing) return;
	// using a transparent bitmap so use an offscreenDC
	m_bDrawing=TRUE;
	if(m_bDrawOffscreen == TRUE)//global telling to draw offscreen to put in
		m_FirstSweep = FALSE;
	CRect rc = rcBounds;
	CWnd* parent;
	if (m_hWnd) parent=GetParent();
	long offsetx;
	long offsety;
	CDC* pOffScreenDC;
	CBitmap bitmap;
	CBitmap* pOldBitmap;
    CFont* pOldFont;
	if (m_hWnd)
	{
		if(m_FirstSweep != TRUE)
		{
			pOffScreenDC=(CDC*)parent->SendMessage(WM_GETOFFSCREENDC,NULL,NULL);
			bitmap.CreateCompatibleBitmap(pdc,rcBounds.right,rcBounds.bottom);
			pOldBitmap=pOffScreenDC->SelectObject(&bitmap);
		}
		else
		{
			pOffScreenDC = pdc;
		}
		long offsets;
		offsets=parent->SendMessage(WM_GETXYOFFSET,NULL,NULL);
		CRect rect;
		GetWindowRect(rect);
		CRect parentrect;
		parent->GetWindowRect(parentrect);
		offsetx=short(offsets & 0x0000FFFF)+parentrect.left-rect.left;
		offsety=short((offsets & 0xFFFF0000)>>16)+parentrect.top-rect.top;
		pOldFont = pOffScreenDC->SelectObject((CFont*)this->GetParent()->SendMessage(WM_GETGLOBALFONT,abs(m_FontNum),NULL));
	}
	else
	{
		offsetx=0;
		offsety=0;
		pOffScreenDC=pdc;
		pOldFont = pOffScreenDC->GetCurrentFont();
	}
    pOffScreenDC->SetBkMode(TRANSPARENT);
    pOffScreenDC->SetTextAlign(TA_LEFT | TA_TOP);

	FileNum artnum=FIL_NULL;
	BOOL X2flag=FALSE;
	if(m_FirstSweep != TRUE && m_hWnd)
		artnum = (FileNum)parent->SendMessage(WM_GETARTWORK,NULL,NULL);

	BYTE* pData;
	if (artnum)
	{
		pData = (BYTE*)parent->SendMessage(WM_GETFILE,artnum,NULL);
		if (pData && pData[0]=='B' && pData[1]=='M') // checks if its a bitmap file
		{
			// now render it...
			BITMAPFILEHEADER* pFile=(BITMAPFILEHEADER*)pData;
			BITMAPINFO* pInfo=(BITMAPINFO*)(pData+sizeof(BITMAPFILEHEADER));
			pData+=pFile->bfOffBits;
			VERIFY(SetDIBitsToDevice(pOffScreenDC->m_hDC,offsetx,offsety,pInfo->bmiHeader.biWidth, pInfo->bmiHeader.biHeight,
				0,0,0,pInfo->bmiHeader.biHeight,pData,pInfo,DIB_RGB_COLORS));
		}
		if(m_TransparentPicture)// Woody 21/12/98
		{
			DrawTransparentBitmap(m_TransparentPicture,pOffScreenDC,0,0);//JW 15Dec98
		}
		parent->SendMessage(WM_RELEASELASTFILE,NULL,NULL);
	}else															  //JIM 21/05/99
	{
		if(m_TransparentPicture)// Woody 21/12/98					  //JIM 21/05/99
		{
			DrawTransparentBitmap(m_TransparentPicture,pOffScreenDC,0,0);//JW 15Dec98
		}
	}																  //JIM 21/05/99
	if(m_hWnd)
		X2flag=parent->SendMessage(WM_GETX2FLAG,NULL,NULL);
	if (!artnum && m_FirstSweep != TRUE || !m_hWnd)
	{
		pOffScreenDC->FillRect(rcBounds, CBrush::FromHandle((HBRUSH)GetStockObject(BLACK_BRUSH)));
	}

	int rightside=rc.right;
	if (m_bDrawBitmap)
		rightside=rc.right-17;

	if (m_FontNum<0)
	{
	    TEXTMETRIC tm;
	    pOffScreenDC->GetTextMetrics(&tm);
		pOffScreenDC->SetTextColor(RGB(0,0,0));
		int shadowx=GetShadow1XOffset(tm.tmHeight);
		int shadowy=GetShadow1YOffset(tm.tmHeight);
	    pOffScreenDC->ExtTextOut(2+shadowx, 2+shadowy,
			ETO_CLIPPED, CRect(rc.left,rc.top,rightside,rc.bottom), captiontext, captiontext.GetLength(), NULL);
		shadowx=GetShadow2XOffset(tm.tmHeight);
		shadowy=GetShadow2YOffset(tm.tmHeight);
	    pOffScreenDC->ExtTextOut(2+shadowx, 2+shadowy,
			ETO_CLIPPED, CRect(rc.left,rc.top,rightside,rc.bottom), captiontext, captiontext.GetLength(), NULL);
	}
    pOffScreenDC->SetTextColor(TranslateColor(GetForeColor()));
    pOffScreenDC->ExtTextOut(2, 2,
		ETO_CLIPPED, CRect(rc.left,rc.top,rightside,rc.bottom), captiontext, captiontext.GetLength(), NULL);

	// draw icon and rectangle
	if (!m_TransparentPicture)									//RDH 23Dec98
	{
		CPen BlackPen,WhitePen;
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
		CPen* oldpen;
		oldpen=pOffScreenDC->SelectObject(&WhitePen);
		pOffScreenDC->MoveTo(rcBounds.right-1,rcBounds.top);
		pOffScreenDC->LineTo(rcBounds.right-1,rcBounds.bottom-1);
		pOffScreenDC->LineTo(rcBounds.left,rcBounds.bottom-1);
		pOffScreenDC->SelectObject(&BlackPen);
		pOffScreenDC->LineTo(rcBounds.left,rcBounds.top);
		pOffScreenDC->LineTo(rcBounds.right-1,rcBounds.top);
		if (m_bDrawBitmap)
			DrawTransparentBitmap(FIL_EDIT_BUTTON,pOffScreenDC,rc.right-14,(rc.Height()/2)-12);
		pOffScreenDC->SelectObject(oldpen);
	}
	pOffScreenDC->SelectObject(pOldFont);
	if (m_hWnd && m_FirstSweep != TRUE)
	{
		pdc->BitBlt(0,0,rcBounds.right-rcBounds.left,rcBounds.bottom-rcBounds.top,pOffScreenDC,
						0,0,SRCCOPY); // flips offscreen dc to real dc
		pOffScreenDC->SelectObject(pOldBitmap);
	}
	m_FirstSweep = FALSE;
	m_bDrawing=FALSE;
}

void CREdtBtCtrl::DrawTransparentBitmap(FileNum filenum,CDC * pDC, int x, int y)
{
	// this is a new way optimised for when a bitmap
	// is mostly transparent (as is the case with the edit
	// button
	if (m_hWnd)
	{
		BYTE* pData;
		CWnd* parent;
		parent=GetParent();
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
			if(m_FirstSweep == FALSE)//global variable tells to draw offscreen
			{//dont do test
				for (y2=Height-1;y2>=0;y2--)
				{
					for (x2=0;x2<Width;x2++)
					{
						code=*pData2++;
						if (code!=254)
						{
							color=pInfo->bmiColors[code];
							pDC->SetPixel(x+x2,y+y2,RGB(color.rgbRed,color.rgbGreen,color.rgbBlue));
						}
					}
				}
			}
			else
			{//do test
				Bool tested = FALSE;
				for (y2=Height-1;y2>=0;y2--)
				{						
					for (x2=0;x2<Width;x2++)
					{
						code=*pData2++;
						if (code!=254 && x2<pInfo->bmiHeader.biWidth)
						{
							color=pInfo->bmiColors[code];		
							COLORREF setval = pDC->GetNearestColor(RGB(color.rgbRed,color.rgbGreen,color.rgbBlue));
							pDC->SetPixel(x+x2,y+y2,setval);
							COLORREF returnval = pDC->GetPixel(x+x2,y+y2);
							tested = TRUE;
							if(setval != returnval)
							{
								//set global variable to draw all editbtc controls offscreen
								//cause control to redraw offscreen
								m_bDrawOffscreen=TRUE;
								m_bDrawing=FALSE;
								InvalidateControl();
							}
							x2++;
							break;
						}
					}
					if(tested == TRUE)
					{
						break;
					}
				}
				if(m_bDrawing==TRUE)
				{
					for (y2;y2>=0;y2--)
					{
						for (x2;x2<Width;x2++)
						{
							code=*pData2++;
							if (code!=254)
							{
								color=pInfo->bmiColors[code];
								pDC->SetPixel(x+x2,y+y2,RGB(color.rgbRed,color.rgbGreen,color.rgbBlue));
							}
						}
						x2 = 0;
					}
				}
			}
		}
		parent->SendMessage(WM_RELEASELASTFILE,NULL,NULL);
	}
}

/////////////////////////////////////////////////////////////////////////////
// CREdtBtCtrl::DoPropExchange - Persistence support

void CREdtBtCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);
	PX_Long(pPX, _T("FontNum"), m_FontNum, 0);
	if (pPX->IsLoading())
	{
		captiontext=InternalGetText();
		if(!captiontext.IsEmpty() && captiontext[0]=='~')
			m_bDrawBitmap=FALSE;
		else
			m_bDrawBitmap=TRUE;
	}
}


/////////////////////////////////////////////////////////////////////////////
// CREdtBtCtrl::OnResetState - Reset control to default state

void CREdtBtCtrl::OnResetState()
{
	COleControl::OnResetState();  // Resets defaults found in DoPropExchange
	SetForeColor(RGB(255,255,255));
}


/////////////////////////////////////////////////////////////////////////////
// CREdtBtCtrl message handlers

long CREdtBtCtrl::GetFontNum() 
{
	return m_FontNum;
}

void CREdtBtCtrl::SetFontNum(long nNewValue) 
{
	m_FontNum=nNewValue;
	InvalidateControl();
	SetModifiedFlag();
}

void CREdtBtCtrl::OnLButtonDown(UINT nFlags, CPoint point) 
{
//	FireClicked();

	m_point=point;
	m_LButtonDown=TRUE;
	m_bDragging=FALSE;
	SetCapture();
	COleControl::OnLButtonDown(nFlags, point);
}

void CREdtBtCtrl::OnMouseMove(UINT nFlags, CPoint point) 
{
	if (m_LButtonDown && m_DragAndDropID && !m_bDragging &&
		!CRect(m_point.x-3,m_point.y-3,m_point.x+3,m_point.y+3).PtInRect(point))
	{
		GetParent()->SendMessage(WM_PLAYSOUND,FIL_SFX_OFFICE_PAPER2,NULL);//DAW 06Apr99
		m_bDragging=TRUE;
	    ::SetCursor(AfxGetApp()->LoadStandardCursor(IDC_NO));
	}
	if (m_bDragging)
	{
		CRect rect;
		GetClientRect(rect);
		ClientToScreen(rect);
		point+=rect.TopLeft();
		CWnd* target=WindowFromPoint(point);
		if (target->SendMessage(WM_CANACCEPTDROP,m_DragAndDropID))
		{
			::SetCursor(AfxGetApp()->LoadStandardCursor(IDC_SIZENS));
			m_bCanAcceptDrop=TRUE;
		}
		else
		{
			::SetCursor(AfxGetApp()->LoadStandardCursor(IDC_NO));
			m_bCanAcceptDrop=FALSE;
		}
	}
	else
	{
		::SetCursor(AfxGetApp()->LoadStandardCursor(IDC_ARROW));
	}
	COleControl::OnMouseMove(nFlags, point);
}

void CREdtBtCtrl::OnLButtonUp(UINT nFlags, CPoint point) 
{
	if (!m_bDragging)
		GetParent()->SendMessage(WM_PLAYSOUND,FIL_SFX_OFFICE_BOOKCLOSE2,NULL);//DAW 06Apr99

	ReleaseCapture();
	m_LButtonDown=FALSE;
	COleControl::OnLButtonUp(nFlags, point);
	if (!m_bDragging) FireClicked();
	else 
	{
		m_bDragging=FALSE;
//		if (m_bCanAcceptDrop)
//		{
			CRect rect;
			GetClientRect(rect);
			ClientToScreen(rect);
			point+=rect.TopLeft();
			CWnd* target=WindowFromPoint(point);
			if (target)
			{
				if (target->SendMessage(WM_CANACCEPTDROP,m_DragAndDropID))
					target->SendMessage(WM_DROPPEDON,m_DragAndDropID);
			}
//		}
	}
}

void CREdtBtCtrl::OnTextChanged() 
{
	captiontext=InternalGetText();
	InvalidateControl();
	SetModifiedFlag();
	COleControl::OnTextChanged();
}

long CREdtBtCtrl::GetDragAndDropID() 
{
	return m_DragAndDropID;
}

void CREdtBtCtrl::SetDragAndDropID(long nNewValue) 
{
	m_DragAndDropID=nNewValue;
}

BOOL CREdtBtCtrl::OnCanAcceptDrop(long dropID)
{
	BOOL retval=FALSE;
	FireCanAcceptDrop(dropID,&retval);
	return retval;
}

void CREdtBtCtrl::OnDroppedOn(long dropID)
{
	FireDroppedOn(dropID);
}

void CREdtBtCtrl::SetPictureFileNum(long picture) 
{
	m_TransparentPicture = (FileNum)picture ;	//Woody 21/12/98
	m_bDrawBitmap=FALSE;
}
