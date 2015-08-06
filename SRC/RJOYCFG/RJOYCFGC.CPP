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

// RJoyCfgC.cpp : Implementation of the CRJoyCfgCtrl ActiveX Control class.

#include "stdafx.h"
#include "RJoyCfg.h"
#include "RJoyCfgC.h"
#include "RJoyCfgP.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CRJoyCfgCtrl, COleControl)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CRJoyCfgCtrl, COleControl)
	//{{AFX_MSG_MAP(CRJoyCfgCtrl)
	// NOTE - ClassWizard will add and remove message map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Dispatch map

BEGIN_DISPATCH_MAP(CRJoyCfgCtrl, COleControl)
	//{{AFX_DISPATCH_MAP(CRJoyCfgCtrl)
	DISP_PROPERTY_EX(CRJoyCfgCtrl, "ControlPicture", GetControlPicture, SetControlPicture, VT_PICTURE)
	DISP_PROPERTY_EX(CRJoyCfgCtrl, "X", GetX, SetX, VT_I4)
	DISP_PROPERTY_EX(CRJoyCfgCtrl, "Y", GetY, SetY, VT_I4)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()


/////////////////////////////////////////////////////////////////////////////
// Event map

BEGIN_EVENT_MAP(CRJoyCfgCtrl, COleControl)
	//{{AFX_EVENT_MAP(CRJoyCfgCtrl)
	// NOTE - ClassWizard will add and remove event map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_EVENT_MAP
END_EVENT_MAP()


/////////////////////////////////////////////////////////////////////////////
// Property pages

// TODO: Add more property pages as needed.  Remember to increase the count!
BEGIN_PROPPAGEIDS(CRJoyCfgCtrl, 1)
//	PROPPAGEID(CRJoyCfgPropPage::guid)
	PROPPAGEID(CLSID_CPicturePropPage)
END_PROPPAGEIDS(CRJoyCfgCtrl)


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CRJoyCfgCtrl, "RJOYCFG.RJoyCfgCtrl.1",
	0x1b499f6b, 0xc31e, 0x11d1, 0xa1, 0xf0, 0x44, 0x45, 0x53, 0x54, 0, 0)


/////////////////////////////////////////////////////////////////////////////
// Type library ID and version

IMPLEMENT_OLETYPELIB(CRJoyCfgCtrl, _tlid, _wVerMajor, _wVerMinor)


/////////////////////////////////////////////////////////////////////////////
// Interface IDs

const IID BASED_CODE IID_DRJoyCfg =
		{ 0x1b499f69, 0xc31e, 0x11d1, { 0xa1, 0xf0, 0x44, 0x45, 0x53, 0x54, 0, 0 } };
const IID BASED_CODE IID_DRJoyCfgEvents =
		{ 0x1b499f6a, 0xc31e, 0x11d1, { 0xa1, 0xf0, 0x44, 0x45, 0x53, 0x54, 0, 0 } };


/////////////////////////////////////////////////////////////////////////////
// Control type information

static const DWORD BASED_CODE _dwRJoyCfgOleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CRJoyCfgCtrl, IDS_RJOYCFG, _dwRJoyCfgOleMisc)


/////////////////////////////////////////////////////////////////////////////
// CRJoyCfgCtrl::CRJoyCfgCtrlFactory::UpdateRegistry -
// Adds or removes system registry entries for CRJoyCfgCtrl

BOOL CRJoyCfgCtrl::CRJoyCfgCtrlFactory::UpdateRegistry(BOOL bRegister)
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
			IDS_RJOYCFG,
			IDB_RJOYCFG,
			afxRegApartmentThreading,
			_dwRJoyCfgOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}


/////////////////////////////////////////////////////////////////////////////
// Licensing strings

static const TCHAR BASED_CODE _szLicFileName[] = _T("RJoyCfg.lic");

static const WCHAR BASED_CODE _szLicString[] =
	L"Copyright (c) 1998 Rowan Software";


/////////////////////////////////////////////////////////////////////////////
// CRJoyCfgCtrl::CRJoyCfgCtrlFactory::VerifyUserLicense -
// Checks for existence of a user license

BOOL CRJoyCfgCtrl::CRJoyCfgCtrlFactory::VerifyUserLicense()
{
	return AfxVerifyLicFile(AfxGetInstanceHandle(), _szLicFileName,
		_szLicString);
}


/////////////////////////////////////////////////////////////////////////////
// CRJoyCfgCtrl::CRJoyCfgCtrlFactory::GetLicenseKey -
// Returns a runtime licensing key

BOOL CRJoyCfgCtrl::CRJoyCfgCtrlFactory::GetLicenseKey(DWORD dwReserved,
	BSTR FAR* pbstrKey)
{
	if (pbstrKey == NULL)
		return FALSE;

	*pbstrKey = SysAllocString(_szLicString);
	return (*pbstrKey != NULL);
}


/////////////////////////////////////////////////////////////////////////////
// CRJoyCfgCtrl::CRJoyCfgCtrl - Constructor

CRJoyCfgCtrl::CRJoyCfgCtrl()
{
	InitializeIIDs(&IID_DRJoyCfg, &IID_DRJoyCfgEvents);
	m_hPlaneIcon=(HICON)LoadImage(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDI_PLANE),IMAGE_ICON,32,32,LR_DEFAULTCOLOR);
	m_x=m_y=0;
}


/////////////////////////////////////////////////////////////////////////////
// CRJoyCfgCtrl::~CRJoyCfgCtrl - Destructor

CRJoyCfgCtrl::~CRJoyCfgCtrl()
{
	// TODO: Cleanup your control's instance data here.
}


/////////////////////////////////////////////////////////////////////////////
// CRJoyCfgCtrl::OnDraw - Drawing function

void CRJoyCfgCtrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
{
	// TODO: Replace the following code with your own drawing code.

	long hmWidth;
	long hmHeight;
	m_pic.m_pPict->get_Width(&hmWidth);
	m_pic.m_pPict->get_Height(&hmHeight);
	hmWidth/=26; // this seems a bit dodge might get problems later
	hmHeight/=26;
	m_pic.Render(pdc,CRect(0,0,hmWidth,hmHeight),rcBounds);
	pdc->DrawIcon(m_x,m_y,m_hPlaneIcon);
}


/////////////////////////////////////////////////////////////////////////////
// CRJoyCfgCtrl::DoPropExchange - Persistence support

void CRJoyCfgCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);
	PX_Picture(pPX, "ControlPicture",m_pic);
}


/////////////////////////////////////////////////////////////////////////////
// CRJoyCfgCtrl::OnResetState - Reset control to default state

void CRJoyCfgCtrl::OnResetState()
{
	COleControl::OnResetState();  // Resets defaults found in DoPropExchange
	m_pic.CreateEmpty();
}


/////////////////////////////////////////////////////////////////////////////
// CRJoyCfgCtrl message handlers

LPPICTUREDISP CRJoyCfgCtrl::GetControlPicture() 
{
	return m_pic.GetPictureDispatch();
}

void CRJoyCfgCtrl::SetControlPicture(LPPICTUREDISP newValue) 
{
	m_pic.SetPictureDispatch(newValue);
	InvalidateControl();
	SetModifiedFlag();
}

long CRJoyCfgCtrl::GetX() 
{
	return m_x;
}

void CRJoyCfgCtrl::SetX(long nNewValue) 
{
	if (m_x!=nNewValue)
	{
		m_x=nNewValue;
		SetModifiedFlag();
		InvalidateControl();
	}
}

long CRJoyCfgCtrl::GetY() 
{
	return m_y;
}

void CRJoyCfgCtrl::SetY(long nNewValue) 
{
	if (m_y!=nNewValue)
	{
		m_y=nNewValue;
		SetModifiedFlag();
		InvalidateControl();
	}
}
