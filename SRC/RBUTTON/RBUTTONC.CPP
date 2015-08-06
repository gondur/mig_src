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

// RButtonCtl.cpp : Implementation of the CRButtonCtrl ActiveX Control class.

#define F_BATTLE

#include "DosDefs.h"
#include "stdafx.h"
#include "RButton.h"
#include "RButtonC.h"
#include "RButtonP.h"
#include "messages.h"
#include "..\mfc\resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
#ifndef THIS_FILE_DEFINED
static char THIS_FILE[] = __FILE__;
#endif
#endif

BOOL CRButtonCtrl::m_bDrawing = FALSE;
#define ICONWIDTH  22

IMPLEMENT_DYNCREATE(CRButtonCtrl, COleControl)
extern int GetResourceNumberFromID(const char* text);
extern BOOL ConvertResourceID(const char* text, char* output);
extern int GetFileNum(const char* text);
extern int GetShadow1XOffset(int fontheight);
extern int GetShadow1YOffset(int fontheight);
extern int GetShadow2XOffset(int fontheight);
extern int GetShadow2YOffset(int fontheight);
/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CRButtonCtrl, COleControl)
	//{{AFX_MSG_MAP(CRButtonCtrl)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_SETCURSOR()
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Dispatch map

BEGIN_DISPATCH_MAP(CRButtonCtrl, COleControl)
	//{{AFX_DISPATCH_MAP(CRButtonCtrl)
	DISP_PROPERTY_NOTIFY(CRButtonCtrl, "UpdateCaption", m_updateCaption, OnUpdateCaptionChanged, VT_BOOL)
	DISP_PROPERTY_EX(CRButtonCtrl, "MovesParent", GetMovesParent, SetMovesParent, VT_BOOL)
	DISP_PROPERTY_EX(CRButtonCtrl, "FontNum", GetFontNum, SetFontNum, VT_I4)
	DISP_PROPERTY_EX(CRButtonCtrl, "CloseButton", GetCloseButton, SetCloseButton, VT_BOOL)
	DISP_PROPERTY_EX(CRButtonCtrl, "TickButton", GetTickButton, SetTickButton, VT_BOOL)
	DISP_PROPERTY_EX(CRButtonCtrl, "ShowShadow", GetShowShadow, SetShowShadow, VT_BOOL)
	DISP_PROPERTY_EX(CRButtonCtrl, "ShadowColor", GetShadowColor, SetShadowColor, VT_COLOR)
	DISP_PROPERTY_EX(CRButtonCtrl, "String", GetString, SetString, VT_BSTR)
	DISP_PROPERTY_EX(CRButtonCtrl, "ResourceNumber", GetResourceNumber, SetResourceNumber, VT_I4)
	DISP_PROPERTY_EX(CRButtonCtrl, "NormalFileNum", GetNormalFileNum, SetNormalFileNum, VT_I4)
	DISP_PROPERTY_EX(CRButtonCtrl, "PressedFileNum", GetPressedFileNum, SetPressedFileNum, VT_I4)
	DISP_PROPERTY_EX(CRButtonCtrl, "NormalFileNumString", GetNormalFileNumString, SetNormalFileNumString, VT_BSTR)
	DISP_PROPERTY_EX(CRButtonCtrl, "PressedFileNumString", GetPressedFileNumString, SetPressedFileNumString, VT_BSTR)
	DISP_PROPERTY_EX(CRButtonCtrl, "Pressed", GetPressed, SetPressed, VT_BOOL)
	DISP_PROPERTY_EX(CRButtonCtrl, "Disabled", GetDisabled, SetDisabled, VT_BOOL)
	DISP_PROPERTY_EX(CRButtonCtrl, "HintStringID", GetHintStringID, SetHintStringID, VT_BSTR)
	DISP_PROPERTY_EX(CRButtonCtrl, "HintResourceNumber", GetHintResourceNumber, SetHintResourceNumber, VT_I4)
	DISP_PROPERTY_EX(CRButtonCtrl, "Transparency", GetTransparency, SetTransparency, VT_BOOL)
	DISP_PROPERTY_EX(CRButtonCtrl, "TransparentFileNum", GetTransparentBitMap, SetTransparentBitMap, VT_I4)
	DISP_PROPERTY_EX(CRButtonCtrl, "HelpButton", GetHelpButton, SetHelpButton, VT_BOOL)
	DISP_PROPERTY_EX(CRButtonCtrl, "HintString", GetHintString, SetHintString, VT_BSTR)
	DISP_STOCKPROP_FORECOLOR()
	DISP_STOCKPROP_CAPTION()
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()


/////////////////////////////////////////////////////////////////////////////
// Event map

BEGIN_EVENT_MAP(CRButtonCtrl, COleControl)
	//{{AFX_EVENT_MAP(CRButtonCtrl)
	EVENT_CUSTOM("Clicked", FireClicked, VTS_NONE)
	EVENT_CUSTOM("Cancel", FireCancel, VTS_NONE)
	EVENT_CUSTOM("OK", FireOK, VTS_NONE)
	//}}AFX_EVENT_MAP
END_EVENT_MAP()


/////////////////////////////////////////////////////////////////////////////
// Property pages

// TODO: Add more property pages as needed.  Remember to increase the count!
BEGIN_PROPPAGEIDS(CRButtonCtrl, 2)
	PROPPAGEID(CRButtonPropPage::guid)
//	PROPPAGEID(CLSID_CPicturePropPage)
    PROPPAGEID(CLSID_CColorPropPage)
END_PROPPAGEIDS(CRButtonCtrl)


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CRButtonCtrl, "RBUTTON.RButtonCtrl.1",
	0x78918646, 0xa917, 0x11d1, 0xa1, 0xf0, 0x44, 0x45, 0x53, 0x54, 0, 0)


/////////////////////////////////////////////////////////////////////////////
// Type library ID and version

IMPLEMENT_OLETYPELIB(CRButtonCtrl, _tlid, _wVerMajor, _wVerMinor)


/////////////////////////////////////////////////////////////////////////////
// Interface IDs

const IID BASED_CODE IID_DRButton =
		{ 0x78918644, 0xa917, 0x11d1, { 0xa1, 0xf0, 0x44, 0x45, 0x53, 0x54, 0, 0 } };
const IID BASED_CODE IID_DRButtonEvents =
		{ 0x78918645, 0xa917, 0x11d1, { 0xa1, 0xf0, 0x44, 0x45, 0x53, 0x54, 0, 0 } };


/////////////////////////////////////////////////////////////////////////////
// Control type information

static const DWORD BASED_CODE _dwRButtonOleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CRButtonCtrl, IDS_RBUTTON, _dwRButtonOleMisc)


/////////////////////////////////////////////////////////////////////////////
// CRButtonCtrl::CRButtonCtrlFactory::UpdateRegistry -
// Adds or removes system registry entries for CRButtonCtrl

BOOL CRButtonCtrl::CRButtonCtrlFactory::UpdateRegistry(BOOL bRegister)
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
			IDS_RBUTTON,
			IDB_RBUTTON,
			afxRegApartmentThreading,
			_dwRButtonOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}


/////////////////////////////////////////////////////////////////////////////
// Licensing strings

static const TCHAR BASED_CODE _szLicFileName[] = _T("RButton.lic");

static const WCHAR BASED_CODE _szLicString[] =
	L"Copyright (c) 1998 Rowan Software";


/////////////////////////////////////////////////////////////////////////////
// CRButtonCtrl::CRButtonCtrlFactory::VerifyUserLicense -
// Checks for existence of a user license

BOOL CRButtonCtrl::CRButtonCtrlFactory::VerifyUserLicense()
{
	return AfxVerifyLicFile(AfxGetInstanceHandle(), _szLicFileName,
		_szLicString);
}


/////////////////////////////////////////////////////////////////////////////
// CRButtonCtrl::CRButtonCtrlFactory::GetLicenseKey -
// Returns a runtime licensing key

BOOL CRButtonCtrl::CRButtonCtrlFactory::GetLicenseKey(DWORD dwReserved,
	BSTR FAR* pbstrKey)
{
	if (pbstrKey == NULL)
		return FALSE;

	*pbstrKey = SysAllocString(_szLicString);
	return (*pbstrKey != NULL);
}


/////////////////////////////////////////////////////////////////////////////
// CRButtonCtrl::CRButtonCtrl - Constructor

CRButtonCtrl::CRButtonCtrl()
{
	InitializeIIDs(&IID_DRButton, &IID_DRButtonEvents);
	m_LButtonDown=FALSE;
	m_bInit=TRUE;
//	if (!m_hWnd) FILEMAN.InitFileSystem(); // ONLY DO THIS IF AT DESIGN TIME!!!!!!!!
	// disabled for now since design time is so hard to detect...
//	m_bDrawing=FALSE;
	m_bDisabled=FALSE;
	m_bPressed=FALSE;
	m_bClosePressed=FALSE;
	m_bHelpPressed=FALSE;
	m_bTickPressed=FALSE;
	m_TransparentInnerFileNum=NULL;
	m_BitMapWithTransparencies = FALSE; // Woody Added
	m_FirstSweep = TRUE;
	m_bHelpButton = TRUE;
	gotparentwnd=false;	//not yet tried to get parent wnd
}

//////////////////////////////////////////////////////////////////////
//
// Function:    GetParentWndInfo
// Date:		21/05/99
// Author:		JIM
//
//Description:	Get all the info from the parent that Dallas couldn't be bothered with...
//				This procedure is called at the top of any routine that might try to access
//				one of:
//					caption						m_ResourceNumber==>m_string
//					hint						m_hintResourceNumber==>m_hintString
//					background artwork number???
//					font number???
//
//////////////////////////////////////////////////////////////////////
void	CRButtonCtrl::GetParentWndInfo()
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
				workspace[0]=99;
				if (!m_hintStringID.IsEmpty() && m_hintStringID [0]>' ' && m_hintResourceNumber && m_hintResourceNumber!=IDS_NONE)
				{
					int strsize=parent->SendMessage(WM_GETSTRING,m_hintResourceNumber,(int)workspace);
					m_hintString=workspace;
				}
				else
					m_hintString="";
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////
// CRButtonCtrl::~CRButtonCtrl - Destructor

CRButtonCtrl::~CRButtonCtrl()
{
	// TODO: Cleanup your control's instance data here.
}


/////////////////////////////////////////////////////////////////////////////
// CRButtonCtrl::OnDraw - Drawing function

void CRButtonCtrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
{
	// note that palette entry 254 is the transparent colour//JW 15Dec98
	// TODO: Replace the following code with your own drawing code.
	if (m_bDrawing) 
		return;
	GetParentWndInfo();
	// need to use an offscreenDC soley because we are			//JW 15Dec98
	// using dallas's crappy transparent blit function
	// which leaves pink flashes if not rendered offscreen
	CDC* pOffScreenDC;											//JW 15Dec98
	CWnd* parent ;												//JW 15Dec98
	CBitmap* pOldBitmap;										//JW 15Dec98
	CBitmap bitmap;												//JW 15Dec98
	m_bDrawing=TRUE;

	if (m_hWnd)					//JW 15Dec98
		parent = GetParent();	//JW 15Dec98
	else						//JW 15Dec98
		parent = NULL ;			//JW 15Dec98

	if (m_bInit)
	{
		m_bInit=FALSE;
//		if (m_bCloseButton || m_bTickButton)
//			m_bHelpButton=TRUE; // remove this if it becomes a persistent property
//		else
//			m_bHelpButton=FALSE;
//DEADCODE JIM 01/06/99 		if(!m_bCloseButton && !m_bTickButton)
//DEADCODE JIM 01/06/99 			m_bHelpButton=FALSE;
		if (m_bCloseButton) 
		{
			m_closeUpIcon=LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDI_BYEUP));
			m_closeDownIcon=LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDI_BYEDOWN));
		}
		if (m_bTickButton) 
		{
			m_tickUpIcon=LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDI_TICKUP));
			m_tickDownIcon=LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDI_TICKDOWN));
		}
		if (m_bHelpButton) 
		{
			m_helpUpIcon=LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDI_HELPUP));
			m_helpDownIcon=LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDI_HELPDOWN));
		}
	}
	long filenum=m_NormalFileNum;
	if (m_PressedFileNum<6 && m_PressedFileNum>0)
	{
		if (m_bDisabled && m_PressedFileNum>=4 && !m_bPressed)
			filenum=m_NormalFileNum+3;
		else if (m_bDisabled && m_PressedFileNum>=5 && m_bPressed)
			filenum=m_NormalFileNum+4;
		else if (m_bDisabled && m_PressedFileNum==4)				  //JIM 14/04/99
			filenum=m_NormalFileNum+3;								  //JIM 14/04/99
		else if (m_LButtonDown && m_PressedFileNum>=2)
			filenum=m_NormalFileNum+1;
		else if (m_bPressed && m_PressedFileNum>=3)
			filenum=m_NormalFileNum+2;
	}
	else if (m_PressedFileNum && m_LButtonDown)
		filenum=m_PressedFileNum;
	if (m_hWnd && (m_BitMapWithTransparencies || m_TransparentInnerFileNum)) //JW 15/2/98
	{
		if(m_FirstSweep != TRUE)
		{
			pOffScreenDC = (CDC*)parent->SendMessage(WM_GETOFFSCREENDC,NULL,NULL);
			bitmap.CreateCompatibleBitmap(pdc,rcBounds.right,rcBounds.bottom);
			pOldBitmap=pOffScreenDC->SelectObject(&bitmap);
		}
		else
		{
			pOffScreenDC = pdc;
		}

		FileNum artnum=FIL_NULL; // only need to draw background if we are in transparent mode JW 15Dec98
		if (m_hWnd)
		{
			long offsetx, offsety ;
			long offsets;
			CRect parentrect;
			CRect rect ;
			
			offsets=parent->SendMessage(WM_GETXYOFFSET,NULL,NULL);
			if(m_FirstSweep != TRUE)
				artnum = (FileNum)parent->SendMessage(WM_GETARTWORK,NULL,NULL);

			GetWindowRect(rect);
			parent->GetWindowRect(parentrect);
			offsetx=short(offsets & 0x0000FFFF)+parentrect.left-rect.left;
			offsety=short((offsets & 0xFFFF0000)>>16)+parentrect.top-rect.top;
			BYTE* pData;
			if (artnum)
			{
				pData = (BYTE*)parent->SendMessage(WM_GETFILE,artnum,NULL);
				if (pData[0]=='B' && pData[1]=='M') // checks if its a bitmap file//JW 15Dec98
				{
					// now render it...
					BITMAPFILEHEADER* pFile=(BITMAPFILEHEADER*)pData;
					BITMAPINFO* pInfo=(BITMAPINFO*)(pData+sizeof(BITMAPFILEHEADER));
					pData+=pFile->bfOffBits;
					VERIFY(SetDIBitsToDevice(pOffScreenDC->m_hDC,offsetx,offsety,pInfo->bmiHeader.biWidth, pInfo->bmiHeader.biHeight,
						0,0,0,pInfo->bmiHeader.biHeight,pData,pInfo,DIB_RGB_COLORS));
				}
				parent->SendMessage(WM_RELEASELASTFILE,NULL,NULL);//JW 15Dec98
			}
		}
//		DrawBitmapWTrans((FileNum)filenum,pOffScreenDC);
		DrawBitmapWithTransparencies((FileNum)filenum,pOffScreenDC);//JW 15Dec98
	}
	else
	{
		pOffScreenDC = pdc ;									//JW 15Dec98
		DrawBitmap((FileNum)filenum,pOffScreenDC);
	}
    CRect rc = rcBounds;
    CFont* pOldFont;
    TEXTMETRIC tm;
    const CString& strCaption = m_string;

    // Set the ForeColor property color and transparent background mode into the device context
    pOffScreenDC->SetBkMode(TRANSPARENT);

    // Draw the caption using the stock Font and ForeColor properties
	if (m_hWnd)
		pOldFont = pOffScreenDC->SelectObject((CFont*)parent->SendMessage(WM_GETGLOBALFONT,m_FontNum,NULL));
	else
		pOldFont = pOffScreenDC->GetCurrentFont();
    pOffScreenDC->GetTextMetrics(&tm);
    pOffScreenDC->SetTextAlign(TA_LEFT | TA_TOP);
	int offset=0;
	if (m_bCloseButton)
	{
		if (m_bClosePressed) 
			pOffScreenDC->DrawIcon(rc.right-ICONWIDTH,rc.top+(rc.Height()/2)-16,m_closeDownIcon);
		else
			pOffScreenDC->DrawIcon(rc.right-ICONWIDTH,rc.top+(rc.Height()/2)-16,m_closeUpIcon);
		offset=ICONWIDTH;
	}
	if (m_bTickButton)
	{
		if (m_bTickPressed)
			pOffScreenDC->DrawIcon(rc.right-ICONWIDTH-offset,rc.top+(rc.Height()/2)-16,m_tickDownIcon);
		else
			pOffScreenDC->DrawIcon(rc.right-ICONWIDTH-offset,rc.top+(rc.Height()/2)-16,m_tickUpIcon);
		offset+=ICONWIDTH;
	}
	if (m_bHelpButton)
	{
		if (m_bHelpPressed)
			pOffScreenDC->DrawIcon(rc.right-ICONWIDTH-offset,rc.top+(rc.Height()/2)-16,m_helpDownIcon);
		else
			pOffScreenDC->DrawIcon(rc.right-ICONWIDTH-offset,rc.top+(rc.Height()/2)-16,m_helpUpIcon);
		offset+=ICONWIDTH;
	}
	int newheight=tm.tmHeight;

	if (m_bMovesParent)
	{
		newheight+=4;
	}

	CRect clipbox=rc;
	BOOL bClipped=FALSE;
	int width=pOffScreenDC->GetTextExtent(strCaption).cx;
	int xoffset=(rc.Width()/2)-(width/2);
	int yoffset=rc.top + (rc.bottom/2)-(newheight/2);
	int fullstopswidth=pOffScreenDC->GetTextExtent("...").cx;
	if (m_bCloseButton || m_bTickButton) // signifies button is a title strip
	{
		if (width>rc.Width()-offset-32)
		{
			bClipped=TRUE;
			clipbox=CRect(rc.left,rc.top,rc.right-offset-fullstopswidth,rc.bottom);
		}
		if (xoffset<32 || xoffset+width>rc.Width()-offset-32) 
			xoffset=32;
	}

	if (m_bShowShadow)
	{
	    pOffScreenDC->SetTextColor(TranslateColor(GetShadowColor()));
		int shadowx=GetShadow2XOffset(tm.tmHeight);
		int shadowy=GetShadow2YOffset(tm.tmHeight);
		newheight+=shadowy;
	    pOffScreenDC->ExtTextOut(xoffset+shadowx, yoffset+shadowy,
			ETO_CLIPPED, clipbox, strCaption, strCaption.GetLength(), NULL);
		if (bClipped) 
			pOffScreenDC->TextOut(rc.right-offset-fullstopswidth+shadowx,yoffset+shadowy,"...");
		shadowx=GetShadow1XOffset(tm.tmHeight);
		shadowy=GetShadow1YOffset(tm.tmHeight);
	    pOffScreenDC->ExtTextOut(xoffset+shadowx,yoffset+shadowy,
			ETO_CLIPPED, clipbox, strCaption, strCaption.GetLength(), NULL);
		if (bClipped) 
			pOffScreenDC->TextOut(rc.right-offset-fullstopswidth+shadowx,yoffset+shadowy,"...");
	}
    pOffScreenDC->SetTextColor(TranslateColor(GetForeColor()));
    pOffScreenDC->ExtTextOut(xoffset, yoffset,
		ETO_CLIPPED, clipbox, strCaption, strCaption.GetLength(), NULL);
	if (bClipped) 
		pOffScreenDC->TextOut(rc.right-offset-fullstopswidth,yoffset,"...");
	pOffScreenDC->SelectObject(pOldFont);
	if (m_hWnd && (m_BitMapWithTransparencies || m_TransparentInnerFileNum)
		&& m_FirstSweep != TRUE) //JW 15/2/98
	{
		//if (m_TransparentInnerFileNum)									//JW 15Dec98 draw transparent fella inside button
		//{
		//	DrawTransparentBitmap(pOffScreenDC,(FileNum)(m_TransparentInnerFileNum)); // just one bitmap now -Woody
		//}
		pdc->BitBlt(0,0,rcBounds.right-rcBounds.left,rcBounds.bottom-rcBounds.top,pOffScreenDC,
						0,0,SRCCOPY)!=NULL; // flips offscreen dc to real dc
		pOffScreenDC->SelectObject(pOldBitmap);
	}    
	m_FirstSweep = FALSE;    
	m_bDrawing=FALSE;
}


/////////////////////////////////////////////////////////////////////////////
// CRButtonCtrl::DoPropExchange - Persistence support

void CRButtonCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);
	PX_Bool(pPX, _T("MovesParent"), m_bMovesParent, FALSE);
	PX_Long(pPX, _T("FontNum"), m_FontNum, 0);
	PX_Bool(pPX, _T("CloseButton"), m_bCloseButton, FALSE);
	PX_Bool(pPX, _T("TickButton"), m_bTickButton, FALSE);
	PX_Bool(pPX, _T("ShowShadow"), m_bShowShadow, FALSE);
	PX_Color(pPX, _T("ShadowColor"), m_ShadowColor, FALSE);
	PX_String(pPX, _T("String"), m_string, _T(""));
	PX_Long(pPX, _T("ResourceNumber"), m_ResourceNumber, 0);
	PX_Long(pPX, _T("NormalFileNum"), m_NormalFileNum, 0);
	PX_Long(pPX, _T("PressedFileNum"), m_PressedFileNum, 0);
	PX_String(pPX, _T("NormalFileNumString"), m_NormalFileNumString, _T(""));
	PX_String(pPX, _T("PressedFileNumString"), m_PressedFileNumString, _T(""));
	if (pPX->GetVersion()&0x1)
	{
		PX_String(pPX, _T("HintString"), m_hintString, _T(""));
		PX_String(pPX, _T("HintStringID"), m_hintStringID, _T(""));
		PX_Long(pPX, _T("HintResourceNumber"), m_hintResourceNumber, 0);
	}






	if (pPX->IsLoading())
	{
		if (m_bCloseButton || m_bTickButton)							  //JIM 21/05/99
			m_bHelpButton=TRUE; // remove this if it becomes a persistent property
		else
			m_bHelpButton=FALSE;
	}
}


/////////////////////////////////////////////////////////////////////////////
// CRButtonCtrl::OnResetState - Reset control to default state

void CRButtonCtrl::OnResetState()
{
	COleControl::OnResetState();  // Resets defaults found in DoPropExchange
//	m_picNormal.CreateEmpty();
//	m_picPressed.CreateEmpty();
}


/////////////////////////////////////////////////////////////////////////////
// CRButtonCtrl message handlers

void CRButtonCtrl::OnLButtonDown(UINT nFlags, CPoint point) 
{
	GetParentWndInfo();
	if (m_bDisabled) return;
	m_LButtonDown=TRUE;
	InvalidateControl();
	CRect clientrect;
	GetClientRect(clientrect);
	SetCapture();
	if (point.x>clientrect.right-ICONWIDTH) // was 32			//JW 09Mar99
	{
		if (m_bCloseButton) 
		{
			m_bClosePressed=TRUE;
			return;
		}
		else if (m_bTickButton) 
		{
			m_bTickPressed=TRUE;
			return;
		}
		else if (m_bHelpButton) 
		{
			m_bHelpPressed=TRUE;
			return;
		}
	}
	else if (point.x>clientrect.right-ICONWIDTH*2) 				//JW 09Mar99
	{
		if (m_bTickButton && m_bCloseButton)
		{
			m_bTickPressed=TRUE;
			return;
		}
		if (m_bHelpButton && (m_bCloseButton || m_bTickButton))
		{
			m_bHelpPressed=TRUE;
			return;
		}
	}
	else if (point.x>clientrect.right-ICONWIDTH*3) 
	{
		if (m_bHelpButton && m_bTickButton && m_bCloseButton)
		{
			m_bHelpPressed=TRUE;
			return;
		}
	}
	if (m_bMovesParent)
	{
		CRect rect;
		GetWindowRect(rect);
		CRect parentrect;
		GetParent()->GetClientRect(parentrect);
		GetParent()->ClientToScreen(parentrect);
		point+=rect.TopLeft()-parentrect.TopLeft();
		LPARAM lparam;
		lparam = point.x+(point.y<<16);
//		TRACE0("Sending LBUTTONDOWN\n");
		ReleaseCapture();
		GetParent()->SendMessage(WM_LBUTTONDOWN,nFlags,lparam);
		return;
	}
	COleControl::OnLButtonDown(nFlags, point);
}

void CRButtonCtrl::OnLButtonUp(UINT nFlags, CPoint point) 
{
//DEADCODE DAW 12/04/99 	if (m_bDisabled) return;
	m_LButtonDown=FALSE;
	m_bPressed=!m_bPressed;
	ReleaseCapture();
	InvalidateControl();
	CDialog* phintbox=(CDialog*)GetParent()->SendMessage(WM_GETHINTBOX,NULL,NULL);
	phintbox->ShowWindow(SW_HIDE);
	CRect clientrect;
	GetClientRect(clientrect);

	{
//Button inc:				rbuton\rbuttonc.cpp		XXXX
//	Tick/Help/cross				FIL_SFX_OFFICE_BOOKCLOSE? 1-3			1
//	Toolbar icon				FIL_SFX_OFFICE_BUTTON? 1-3
//	Tickbox						FIL_SFX_OFFICE_TICK						2
//	Dialogue buttons(disable)	FIL_SFX_OFFICE_BUTTON? 1-3			
//	Dialogue buttons(undisblable)
//	Big Dialogue buttons(undisablable)


		FileNum reqsfx=FIL_SFX_OFFICE_BUTTON1;
		if (m_bClosePressed)
			reqsfx=FIL_SFX_OFFICE_BOOKCLOSE1;
		else if (m_bTickPressed)
			reqsfx=FIL_SFX_OFFICE_DRAWER1;
		else if (m_bHelpPressed)
			reqsfx=FIL_SFX_OFFICE_BOOKCLOSE3;
		else if (m_bMovesParent)				   //anywhere else on title bar
			reqsfx=FIL_NULL;
		else if (m_NormalFileNum==FIL_ICON_TICKBOX1)     //tickbox
			reqsfx=FIL_SFX_OFFICE_TICK;
		else
			if (m_bDisabled)
			{
				if (clientrect.Width()<30)		
					reqsfx=FIL_SFX_OFFICE_BUTTON1;	//small square
				else if (clientrect.Height()>30)
					reqsfx=FIL_SFX_OFFICE_BUTTON3;	//big square
				else 
					reqsfx=FIL_SFX_OFFICE_BUTTON2;	//wide short
			}
			else
			{
				if (clientrect.Width()<30)		
					reqsfx=FIL_SFX_OFFICE_BUTTON1;	//small square
				else if (clientrect.Height()>30)
					reqsfx=FIL_SFX_OFFICE_BUTTON3;	//big square
				else 
					reqsfx=FIL_SFX_OFFICE_BUTTON2;	//wide short
			}

		if (reqsfx)
			GetParent()->SendMessage(WM_PLAYSOUND,reqsfx,NULL);//DAW 06Apr99
	}
	if (m_bDisabled) return;										  //DAW 12/04/99

	if (m_bClosePressed) 
	{
		FireCancel();
	}
	if (m_bTickPressed) 
	{
		FireOK();
	}
	if (m_bHelpPressed) 
	{
		CWnd* oldfocus;
		oldfocus=GetParent()->SetFocus(); // ensures help is for correct dialog
		GetParent()->SendMessage(WM_COMMAND,ID_HELP);
		oldfocus->SetFocus(); // restores the focus to the thing that
							// originally had it (such as an edit box)
	}
	m_bClosePressed=FALSE;
	m_bTickPressed=FALSE;
	m_bHelpPressed=FALSE;
	FireClicked();
}

BOOL CRButtonCtrl::GetMovesParent() 
{
	return m_bMovesParent;
}

void CRButtonCtrl::SetMovesParent(BOOL bNewValue) 
{
	m_bMovesParent=bNewValue;
	SetModifiedFlag();
}

void CRButtonCtrl::OnMouseMove(UINT nFlags, CPoint point) 
{
	GetParentWndInfo();

	if (m_LButtonDown&&m_bMovesParent) m_LButtonDown=FALSE;
	// display hint text if it exists
	if (m_hintString!="")
	{
		CRect rect;
		GetClientRect(rect);
		CDialog* phintbox=(CDialog*)GetParent()->SendMessage(WM_GETHINTBOX,NULL,NULL);
		if (rect.PtInRect(point))
		{
			SetCapture();
			if (!phintbox->IsWindowVisible())
			{
				CString realhint=" "+m_hintString+" ";
				phintbox->SetWindowText(realhint);
				CDC* pDC=phintbox->GetDC();
				// select in a font here if you want
				CSize textsize=pDC->GetTextExtent(realhint);
				GetWindowRect(rect);
				// a good way of getting the screen resolution
				CRect deskrect;
				GetDesktopWindow()->GetWindowRect(deskrect);
				CPoint hinttopleft=CPoint(rect.left,rect.bottom+5);
				if (hinttopleft.x+textsize.cx>deskrect.right) 
					hinttopleft.x=rect.right-textsize.cx-3;
				if (hinttopleft.y+textsize.cy>deskrect.bottom) 
					hinttopleft.y=rect.top-8-textsize.cy;
				phintbox->MoveWindow(hinttopleft.x,hinttopleft.y,textsize.cx+2,textsize.cy+2);
				phintbox->ShowWindow(SW_SHOW);
				phintbox->ReleaseDC(pDC);
			}
		}
		else
		{
			ReleaseCapture();
			phintbox->ShowWindow(SW_HIDE);
			if (m_LButtonDown)
			{
				m_LButtonDown=false;
				InvalidateControl();
			}
		}
	}
	COleControl::OnMouseMove(nFlags, point);
}

BOOL CRButtonCtrl::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	::SetCursor(AfxGetApp()->LoadStandardCursor(IDC_ARROW));
	return TRUE;
}

BOOL CRButtonCtrl::OnEraseBkgnd(CDC* pDC) 
{	
	return TRUE;
}

long CRButtonCtrl::GetFontNum() 
{
	return m_FontNum;
}

void CRButtonCtrl::SetFontNum(long nNewValue) 
{
	m_FontNum=nNewValue;
	InvalidateControl();
	SetModifiedFlag();
}

void CRButtonCtrl::OnTextChanged() 
{
	InvalidateControl();
	SetModifiedFlag();	
	COleControl::OnTextChanged();
}

BOOL CRButtonCtrl::GetCloseButton() 
{
	return m_bCloseButton;
}

void CRButtonCtrl::SetCloseButton(BOOL bNewValue) 
{
	m_bCloseButton=bNewValue;
	if (m_bCloseButton) 
	{
		m_closeUpIcon=LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDI_BYEUP));
		m_closeDownIcon=LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDI_BYEDOWN));
	}
	InvalidateControl();
	SetModifiedFlag();
}

BOOL CRButtonCtrl::GetTickButton() 
{
	return m_bTickButton;
}

void CRButtonCtrl::SetTickButton(BOOL bNewValue) 
{
	m_bTickButton=bNewValue;
	if (m_bTickButton) 
	{
		m_tickUpIcon=LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDI_TICKUP));
		m_tickDownIcon=LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDI_TICKDOWN));
	}
	InvalidateControl();
	SetModifiedFlag();
}

BOOL CRButtonCtrl::GetHelpButton() 
{
	return m_bHelpButton;
}

void CRButtonCtrl::SetHelpButton(BOOL bNewValue) 
{
	m_bHelpButton=bNewValue;
	if (m_bHelpButton) 
	{
		m_helpUpIcon=LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDI_HELPUP));
		m_helpDownIcon=LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDI_HELPDOWN));
	}
	InvalidateControl();
	SetModifiedFlag();
}

BOOL CRButtonCtrl::GetShowShadow() 
{
	return m_bShowShadow;
}

void CRButtonCtrl::SetShowShadow(BOOL bNewValue) 
{
	m_bShowShadow=bNewValue;
	InvalidateControl();
	SetModifiedFlag();
}

OLE_COLOR CRButtonCtrl::GetShadowColor() 
{
	return m_ShadowColor;
}

void CRButtonCtrl::SetShadowColor(OLE_COLOR nNewValue) 
{
	m_ShadowColor=nNewValue;
	InvalidateControl();
	SetModifiedFlag();
}

BSTR CRButtonCtrl::GetString() 
{
	GetParentWndInfo();
	return m_string.AllocSysString();
}

void CRButtonCtrl::SetString(LPCTSTR lpszNewValue) 
{
	GetParentWndInfo();
	m_string=lpszNewValue;
	InvalidateControl();
	SetModifiedFlag();
}


long CRButtonCtrl::GetResourceNumber() 
{
	return m_ResourceNumber;
}

void CRButtonCtrl::SetResourceNumber(long nNewValue) 
{
	m_ResourceNumber=nNewValue;
	SetModifiedFlag();
}

long CRButtonCtrl::GetNormalFileNum() 
{
	return m_NormalFileNum;
}

void CRButtonCtrl::SetNormalFileNum(long nNewValue) 
{
	m_NormalFileNum=nNewValue;
	InvalidateControl();
	SetModifiedFlag();
}

long CRButtonCtrl::GetPressedFileNum() 
{
	return m_PressedFileNum;
}

void CRButtonCtrl::SetPressedFileNum(long nNewValue) 
{
	m_PressedFileNum=nNewValue;
	InvalidateControl();
	SetModifiedFlag();
}

BSTR CRButtonCtrl::GetNormalFileNumString() 
{
	return m_NormalFileNumString.AllocSysString();
}

void CRButtonCtrl::SetNormalFileNumString(LPCTSTR lpszNewValue) 
{
	m_NormalFileNumString=lpszNewValue;
	m_NormalFileNum=GetFileNum(m_NormalFileNumString);
	InvalidateControl();
	SetModifiedFlag();
}

BSTR CRButtonCtrl::GetPressedFileNumString() 
{
	return m_PressedFileNumString.AllocSysString();
}

void CRButtonCtrl::SetPressedFileNumString(LPCTSTR lpszNewValue) 
{
	m_PressedFileNumString=lpszNewValue;
	m_PressedFileNum=GetFileNum(m_PressedFileNumString);
	if (atoi(m_PressedFileNumString)<6) m_PressedFileNum=atoi(m_PressedFileNumString);
	InvalidateControl();
	SetModifiedFlag();
}

void CRButtonCtrl::OnUpdateCaptionChanged() 
{
	GetParentWndInfo();
	if (InternalGetText().IsEmpty())
	{
		SetString("");
	}
	else
	{
		m_ResourceNumber=GetResourceNumberFromID(InternalGetText());
		if (m_ResourceNumber==-1)
		{
//			this->MessageBox("That was not a valid resource ID","ERROR");
//			SetText(strcat("Invalid ID: ",InternalGetText()));
			SetString("Invalid ID!");
		}
		else
		{
			char output[100];
			if (!ConvertResourceID(InternalGetText(),output))
			{
//				this->MessageBox("That resource ID is not equivalent to anything","ERROR");
				SetString("Invalid ID!");
			}
			else SetString(output);
		}
	}
	if (m_hintStringID.IsEmpty())
	{
		SetHintString("");
	}
	else
	{
		m_hintResourceNumber=GetResourceNumberFromID(m_hintStringID);
		if (m_hintResourceNumber==-1)
		{
			SetHintString("Invalid ID!");
		}
		else
		{
			char output[100];
			if (!ConvertResourceID(m_hintStringID,output))
			{
				SetHintString("Invalid ID!");
			}
			else SetHintString(output);
		}
	}
	SetNormalFileNumString(m_NormalFileNumString);
	SetPressedFileNumString(m_PressedFileNumString);
	InvalidateControl();
	SetModifiedFlag();
}

BOOL CRButtonCtrl::GetPressed() 
{
	return m_bPressed;
}

void CRButtonCtrl::SetPressed(BOOL bNewValue) 
{
	m_bPressed=bNewValue;
	InvalidateControl();
	SetModifiedFlag();
}

BOOL CRButtonCtrl::GetDisabled() 
{
	return m_bDisabled;
}

void CRButtonCtrl::SetDisabled(BOOL bNewValue) 
{
	m_bDisabled=bNewValue;
	InvalidateControl();
	SetModifiedFlag();
}

void CRButtonCtrl::DrawBitmap(FileNum filenum,CDC* pdc)
{
	if (filenum)
		if (m_hWnd)
		{
			BYTE* pData;
			pData = (BYTE*)GetParent()->SendMessage(WM_GETFILE,filenum,NULL);
			if (pData && pData[0]=='B' && pData[1]=='M') // checks if its a bitmap file
			{
				// now render it...
				BITMAPFILEHEADER* pFile=(BITMAPFILEHEADER*)pData;
				BITMAPINFO* pInfo=(BITMAPINFO*)(pData+sizeof(BITMAPFILEHEADER));
				pData+=pFile->bfOffBits;
				SetDIBitsToDevice(pdc->m_hDC,0,0,pInfo->bmiHeader.biWidth, pInfo->bmiHeader.biHeight,
					0,0/*pInfo->bmiHeader.biHeight*/,0,pInfo->bmiHeader.biHeight,pData,pInfo,DIB_RGB_COLORS);
			}
			GetParent()->SendMessage(WM_RELEASELASTFILE,NULL,NULL);
		}
}

BSTR CRButtonCtrl::GetHintString() 
{
	GetParentWndInfo();
	return m_hintString.AllocSysString();
}

void CRButtonCtrl::SetHintString(LPCTSTR lpszNewValue) 
{
	GetParentWndInfo();
	m_hintString=lpszNewValue;
	SetModifiedFlag();
}

BSTR CRButtonCtrl::GetHintStringID() 
{
	GetParentWndInfo();
	return m_hintStringID.AllocSysString();
}

void CRButtonCtrl::SetHintStringID(LPCTSTR lpszNewValue) 
{
	GetParentWndInfo();
	m_hintStringID=lpszNewValue;
	SetModifiedFlag();
}

long CRButtonCtrl::GetHintResourceNumber() 
{
	GetParentWndInfo();
	return m_hintResourceNumber;
}

void CRButtonCtrl::SetHintResourceNumber(long nNewValue) 
{
	GetParentWndInfo();
	m_hintResourceNumber=nNewValue;
	SetModifiedFlag();
}

void CRButtonCtrl::DrawBitmapWithTransparencies(FileNum filenum,CDC* pDC)
{
	if (m_hWnd)
	{
		BYTE* pData;
		CWnd* parent;
		parent=GetParent();
		pData = (BYTE*)parent->SendMessage(WM_GETFILE,filenum,NULL);
		if (pData[0]=='B' && pData[1]=='M') // checks if its a bitmap file
		{
			// now render it...
	//		_asm{int 3}
			BITMAPFILEHEADER* pFile=(BITMAPFILEHEADER*)pData;
			BITMAPINFO* pInfo=(BITMAPINFO*)(pData+sizeof(BITMAPFILEHEADER));
			pData+=pFile->bfOffBits;
			BYTE* pData2=pData;
			BYTE code;
			CRect rect;
			GetClientRect(rect);
		
			//int x=rect.right / 2-pInfo->bmiHeader.biWidth/2; - old code used to draw bitmap in middle - Woody
			int x=rect.left ; 
			int y=rect.top ; //(rect.bottom / 2-pInfo->bmiHeader.biHeight/2) + pressedoffsety ;
			int Width=pInfo->bmiHeader.biWidth;
			if (Width%4) Width+=4-Width%4; // DWord alignment
			int Height=pInfo->bmiHeader.biHeight;
			int x2,y2;
			RGBQUAD color;
			for (y2=Height-1;y2>=0;y2--)
			{
				for ( x2=0 ; x2<Width ; x2++)
				{
					code=*pData2++;
					if (code!=254 && x2<pInfo->bmiHeader.biWidth)
					{
						color=pInfo->bmiColors[code] ;
						pDC->SetPixel(x+x2,y+y2,RGB(color.rgbRed,color.rgbGreen,color.rgbBlue));
					}
				}
			}

//			COLORREF* buffer=new COLORREF[Width*Height];
//Old_Code JW 15Dec98 			for (y2=Height-1;y2>=0;y2--)
//Old_Code JW 15Dec98 			{
//Old_Code JW 15Dec98 				for ( x2=0 ; x2<Width ; x2++)
//Old_Code JW 15Dec98 				{
//Old_Code JW 15Dec98 					code=*pData2++;
//Old_Code JW 15Dec98 					if (code==254)
//Old_Code JW 15Dec98 					{
//Old_Code JW 15Dec98 						buffer[y2*Width+x2]=pDC->GetPixel(x+x2,y+y2);
//Old_Code JW 15Dec98 					}
//Old_Code JW 15Dec98 					else buffer[y2*Width+x2]=RGB(255,0,255);
//Old_Code JW 15Dec98 				}
//Old_Code JW 15Dec98 			}
//Old_Code JW 15Dec98 			VERIFY(SetDIBitsToDevice(pDC->m_hDC,x,y,pInfo->bmiHeader.biWidth, Height,
//Old_Code JW 15Dec98 				0,0,0,Height,pData,pInfo,DIB_RGB_COLORS));
//Old_Code JW 15Dec98 			COLORREF colour;
//Old_Code JW 15Dec98 			for (x2=0 ; x2<pInfo->bmiHeader.biWidth ; x2++)
//Old_Code JW 15Dec98 			{
//Old_Code JW 15Dec98 				for (y2=0;y2<Height;y2++)
//Old_Code JW 15Dec98 				{
//Old_Code JW 15Dec98 					colour=buffer[y2*Width+x2];
//Old_Code JW 15Dec98 					if (colour!=RGB(255,0,255))
//Old_Code JW 15Dec98 					{
//Old_Code JW 15Dec98 						pDC->SetPixel(x+x2,y+y2,colour);
//Old_Code JW 15Dec98 					}
//Old_Code JW 15Dec98 				}
//Old_Code JW 15Dec98 			}
//Old_Code JW 15Dec98 			delete [] buffer;
		}
		parent->SendMessage(WM_RELEASELASTFILE,NULL,NULL);
	}
}

void CRButtonCtrl::DrawTransparentBitmap(CDC * pDC, FileNum filenum)
{
	if (m_hWnd)
	{
		BYTE* pData;
		CWnd* parent;
		parent=GetParent();
		pData = (BYTE*)parent->SendMessage(WM_GETFILE,filenum,NULL);
		if (pData[0]=='B' && pData[1]=='M') // checks if its a bitmap file
		{
			// now render it...
	//		_asm{int 3}
			BITMAPFILEHEADER* pFile=(BITMAPFILEHEADER*)pData;
			BITMAPINFO* pInfo=(BITMAPINFO*)(pData+sizeof(BITMAPFILEHEADER));
			pData+=pFile->bfOffBits;
			BYTE* pData2=pData;
			BYTE code;
			CRect rect;
			GetClientRect(rect);
			int pressedoffsetx = 3 ;
			int pressedoffsety = 1 ;
			if (m_bPressed)
			{
				pressedoffsetx += 1 ;
				pressedoffsety += 1 ;
			}		
			//int x=rect.right / 2-pInfo->bmiHeader.biWidth/2; - old code used to draw bitmap in middle - Woody
			int x=rect.left + pressedoffsetx; 
			int y=(rect.bottom / 2-pInfo->bmiHeader.biHeight/2) + pressedoffsety ;
			int Width=pInfo->bmiHeader.biWidth;
			if (Width%4) Width+=4-Width%4; // DWord alignment
			int Height=pInfo->bmiHeader.biHeight;
			int x2,y2;
			RGBQUAD color;
			for (y2=Height-1;y2>=0;y2--)
			{
				for ( x2=0 ; x2<Width ; x2++)
				{
					code=*pData2++;
					if (code!=254 && x2<pInfo->bmiHeader.biWidth)
					{
						color=pInfo->bmiColors[code] ;
						pDC->SetPixel(x+x2,y+y2,RGB(color.rgbRed,color.rgbGreen,color.rgbBlue));
					}
				}
			}
		}
		parent->SendMessage(WM_RELEASELASTFILE,NULL,NULL);
	}
}

BOOL CRButtonCtrl::GetTransparency() 
{
	return m_BitMapWithTransparencies ;
}

void CRButtonCtrl::SetTransparency(BOOL bNewValue) 
{
	m_BitMapWithTransparencies = bNewValue ;
	SetModifiedFlag();
}

long CRButtonCtrl::GetTransparentBitMap() 
{
	return m_TransparentInnerFileNum;
}

void CRButtonCtrl::SetTransparentBitMap(long nNewValue) 
{
	// TODO: Add your property handler here
	m_TransparentInnerFileNum=nNewValue;
	InvalidateControl();
	SetModifiedFlag();
}
