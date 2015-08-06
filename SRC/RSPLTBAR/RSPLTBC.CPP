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

// RSpltBarCtl.cpp : Implementation of the CRSpltBarCtrl ActiveX Control class.

#include "stdafx.h"
#include "RSpltBar.h"
#include "RSpltBC.h"
#include "RSpltBP.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CRSpltBarCtrl, COleControl)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CRSpltBarCtrl, COleControl)
	//{{AFX_MSG_MAP(CRSpltBarCtrl)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Dispatch map

BEGIN_DISPATCH_MAP(CRSpltBarCtrl, COleControl)
	//{{AFX_DISPATCH_MAP(CRSpltBarCtrl)
	DISP_PROPERTY_EX(CRSpltBarCtrl, "TopLeftWindow", GetTopLeftWindow, SetTopLeftWindow, VT_I4)
	DISP_PROPERTY_EX(CRSpltBarCtrl, "BottomRightWindow", GetBottomRightWindow, SetBottomRightWindow, VT_I4)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()


/////////////////////////////////////////////////////////////////////////////
// Event map

BEGIN_EVENT_MAP(CRSpltBarCtrl, COleControl)
	//{{AFX_EVENT_MAP(CRSpltBarCtrl)
	// NOTE - ClassWizard will add and remove event map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_EVENT_MAP
END_EVENT_MAP()


/////////////////////////////////////////////////////////////////////////////
// Property pages

// TODO: Add more property pages as needed.  Remember to increase the count!
BEGIN_PROPPAGEIDS(CRSpltBarCtrl, 1)
	PROPPAGEID(CRSpltBarPropPage::guid)
END_PROPPAGEIDS(CRSpltBarCtrl)


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CRSpltBarCtrl, "RSPLTBAR.RSpltBarCtrl.1",
	0x542bf46, 0x88df, 0x11d1, 0xa1, 0xf0, 0x44, 0x45, 0x53, 0x54, 0, 0)


/////////////////////////////////////////////////////////////////////////////
// Type library ID and version

IMPLEMENT_OLETYPELIB(CRSpltBarCtrl, _tlid, _wVerMajor, _wVerMinor)


/////////////////////////////////////////////////////////////////////////////
// Interface IDs

const IID BASED_CODE IID_DRSpltBar =
		{ 0x542bf44, 0x88df, 0x11d1, { 0xa1, 0xf0, 0x44, 0x45, 0x53, 0x54, 0, 0 } };
const IID BASED_CODE IID_DRSpltBarEvents =
		{ 0x542bf45, 0x88df, 0x11d1, { 0xa1, 0xf0, 0x44, 0x45, 0x53, 0x54, 0, 0 } };


/////////////////////////////////////////////////////////////////////////////
// Control type information

static const DWORD BASED_CODE _dwRSpltBarOleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CRSpltBarCtrl, IDS_RSPLTBAR, _dwRSpltBarOleMisc)


/////////////////////////////////////////////////////////////////////////////
// CRSpltBarCtrl::CRSpltBarCtrlFactory::UpdateRegistry -
// Adds or removes system registry entries for CRSpltBarCtrl

BOOL CRSpltBarCtrl::CRSpltBarCtrlFactory::UpdateRegistry(BOOL bRegister)
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
			IDS_RSPLTBAR,
			IDB_RSPLTBAR,
			afxRegApartmentThreading,
			_dwRSpltBarOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}


/////////////////////////////////////////////////////////////////////////////
// Licensing strings

static const TCHAR BASED_CODE _szLicFileName[] = _T("RSpltBar.lic");

static const WCHAR BASED_CODE _szLicString[] =
	L"Copyright (c) 1998 RowanSoftware";


/////////////////////////////////////////////////////////////////////////////
// CRSpltBarCtrl::CRSpltBarCtrlFactory::VerifyUserLicense -
// Checks for existence of a user license

BOOL CRSpltBarCtrl::CRSpltBarCtrlFactory::VerifyUserLicense()
{
	return AfxVerifyLicFile(AfxGetInstanceHandle(), _szLicFileName,
		_szLicString);
}


/////////////////////////////////////////////////////////////////////////////
// CRSpltBarCtrl::CRSpltBarCtrlFactory::GetLicenseKey -
// Returns a runtime licensing key

BOOL CRSpltBarCtrl::CRSpltBarCtrlFactory::GetLicenseKey(DWORD dwReserved,
	BSTR FAR* pbstrKey)
{
	if (pbstrKey == NULL)
		return FALSE;

	*pbstrKey = SysAllocString(_szLicString);
	return (*pbstrKey != NULL);
}


/////////////////////////////////////////////////////////////////////////////
// CRSpltBarCtrl::CRSpltBarCtrl - Constructor

CRSpltBarCtrl::CRSpltBarCtrl()
{
	InitializeIIDs(&IID_DRSpltBar, &IID_DRSpltBarEvents);
	m_pTopLeftWindow=NULL;
	m_pBottomRightWindow=NULL;
	m_LButtonDown=FALSE;
}


/////////////////////////////////////////////////////////////////////////////
// CRSpltBarCtrl::~CRSpltBarCtrl - Destructor

CRSpltBarCtrl::~CRSpltBarCtrl()
{
	// TODO: Cleanup your control's instance data here.
}


/////////////////////////////////////////////////////////////////////////////
// CRSpltBarCtrl::OnDraw - Drawing function

void CRSpltBarCtrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
{
	CRect rc=rcBounds;
//	rc.left++;
//	rc.right--;
//	rc.bottom--;
//	rc.top++;
	if (m_LButtonDown)
	{
		pdc->FillRect(rcInvalid, CBrush::FromHandle((HBRUSH)GetStockObject(GRAY_BRUSH)));
		pdc->DrawEdge(&rc,EDGE_SUNKEN,BF_RECT);
	}
	else
	{
		pdc->FillRect(rcInvalid, CBrush::FromHandle((HBRUSH)GetStockObject(LTGRAY_BRUSH)));
		pdc->DrawEdge(&rc,EDGE_RAISED,BF_RECT);
	}
}


/////////////////////////////////////////////////////////////////////////////
// CRSpltBarCtrl::DoPropExchange - Persistence support

void CRSpltBarCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);

	// TODO: Call PX_ functions for each persistent custom property.

}


/////////////////////////////////////////////////////////////////////////////
// CRSpltBarCtrl::OnResetState - Reset control to default state

void CRSpltBarCtrl::OnResetState()
{
	COleControl::OnResetState();  // Resets defaults found in DoPropExchange

	// TODO: Reset any other control state here.
}


/////////////////////////////////////////////////////////////////////////////
// CRSpltBarCtrl message handlers

// the windows the splitter bar is linked to can only be set once
// if these need to change later on add a changewindow function

long CRSpltBarCtrl::GetTopLeftWindow() 
{
	TRACE1("returning TOPLEFT: %d\n",(long)m_pTopLeftWindow);
	return (long)m_pTopLeftWindow;
}

void CRSpltBarCtrl::SetTopLeftWindow(long nNewValue) 
{
	m_pTopLeftWindow = (CWnd*)nNewValue;
	TRACE1("TOPLEFT=%d\n",nNewValue);
	SetModifiedFlag();
}

long CRSpltBarCtrl::GetBottomRightWindow() 
{
	TRACE1("returning BOTTOMRIGHT: %d\n",(long)m_pBottomRightWindow);
	return (long)m_pBottomRightWindow;
}

void CRSpltBarCtrl::SetBottomRightWindow(long nNewValue) 
{
	m_pBottomRightWindow = (CWnd*)nNewValue;
	TRACE1("BOTTOMRIGHT=%d\n",nNewValue);
	SetModifiedFlag();
}

void CRSpltBarCtrl::OnLButtonDown(UINT nFlags, CPoint point) 
{
	m_LButtonDown=TRUE;
	this->SetCapture();
	m_point=point;
	this->RedrawWindow();

	COleControl::OnLButtonDown(nFlags, point);
}

void CRSpltBarCtrl::OnLButtonUp(UINT nFlags, CPoint point) 
{
	m_LButtonDown=FALSE;
	ReleaseCapture();
	this->RedrawWindow();
	COleControl::OnLButtonUp(nFlags, point);
}

void CRSpltBarCtrl::OnMouseMove(UINT nFlags, CPoint point) 
{
	if (m_LButtonDown)
	{
		// might need to alter these rects so they are relative to their parents client area
		// luckily the client rect of all these windows fills the window rect
		CRect rectParent;
		this->GetParent()->GetWindowRect(rectParent);
		CRect rect;
		CRect rect2;
		CRect rect3;
		this->GetWindowRect(rect);
		int dx=0;
		int dy=0;
		if (rect.Width()<rect.Height())
			dx=point.x-m_point.x;
		else dy=point.y-m_point.y;
		// check if splitter bar isnt going to reduce a window below its
		// minimum size (currently 0,0) or if it doesnt exist check its not 
		// going to move outside parent window
		
		if (m_pTopLeftWindow)
		{
			m_pTopLeftWindow->GetWindowRect(rect2);
			rect2-=rectParent.TopLeft();
			if (rect2.Width()+dx<0) dx=-rect2.Width();
			if (rect2.Height()+dy<0) dy=-rect2.Height();
		}
		else
		{
			if (rectParent.left>rect.left+dx) dx=rectParent.left-rect.left;
			if (rectParent.top>rect.top+dy) dy=rectParent.top-rect.top;
		}

		if (m_pBottomRightWindow)
		{
			m_pBottomRightWindow->GetWindowRect(rect3);
			rect3-=rectParent.TopLeft();
			if (rect3.Width()-dx<0) dx=rect3.Width();
			if (rect3.Height()-dy<0) dy=rect3.Height();
		}
		else
		{
			if (rectParent.right<rect.right+dx) dx=rect.right-rectParent.right;
			if (rectParent.bottom<rect.bottom+dy) dy=rect.bottom-rectParent.bottom;
		}

		if (m_pBottomRightWindow)
		{
			m_pBottomRightWindow->MoveWindow(rect3.left+dx,rect3.top+dy,rect3.Width()-dx,rect3.Height()-dy);
		}

		rect-=rectParent.TopLeft();
		this->MoveWindow(rect.left+dx,rect.top+dy,rect.Width(),rect.Height());
		this->RedrawWindow();

		if (m_pTopLeftWindow)
		{
			m_pTopLeftWindow->MoveWindow(rect2.left,rect2.top,rect2.Width()+dx,rect2.Height()+dy);
		}
	}
	COleControl::OnMouseMove(nFlags, point);
}
