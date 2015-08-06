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

// RTreeCtl.cpp : Implementation of the CRTreeCtrl ActiveX Control class.

#include "stdafx.h"
#include "RTree.h"
#include "RTreeCtl.h"
#include "RTreePpg.h"
#include <math.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CRTreeCtrl, COleControl)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CRTreeCtrl, COleControl)
	//{{AFX_MSG_MAP(CRTreeCtrl)
	// NOTE - ClassWizard will add and remove message map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Dispatch map

BEGIN_DISPATCH_MAP(CRTreeCtrl, COleControl)
	//{{AFX_DISPATCH_MAP(CRTreeCtrl)
	DISP_PROPERTY_EX(CRTreeCtrl, "ControlPicture", GetControlPicture, SetControlPicture, VT_PICTURE)
	DISP_PROPERTY_EX(CRTreeCtrl, "Depth", GetDepth, SetDepth, VT_I4)
	DISP_PROPERTY_EX(CRTreeCtrl, "BoxWidth", GetBoxWidth, SetBoxWidth, VT_I4)
	DISP_PROPERTY_EX(CRTreeCtrl, "BoxHeight", GetBoxHeight, SetBoxHeight, VT_I4)
	DISP_PROPERTY_EX(CRTreeCtrl, "GapWidth", GetGapWidth, SetGapWidth, VT_I4)
	DISP_FUNCTION(CRTreeCtrl, "GetText", GetText, VT_I4, VTS_I2)
	DISP_FUNCTION(CRTreeCtrl, "Clear", Clear, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION(CRTreeCtrl, "SetText", SetText, VT_EMPTY, VTS_BSTR VTS_I2)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()


/////////////////////////////////////////////////////////////////////////////
// Event map

BEGIN_EVENT_MAP(CRTreeCtrl, COleControl)
	//{{AFX_EVENT_MAP(CRTreeCtrl)
	// NOTE - ClassWizard will add and remove event map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_EVENT_MAP
END_EVENT_MAP()


/////////////////////////////////////////////////////////////////////////////
// Property pages

// TODO: Add more property pages as needed.  Remember to increase the count!
BEGIN_PROPPAGEIDS(CRTreeCtrl, 2)
	PROPPAGEID(CRTreePropPage::guid)
	PROPPAGEID(CLSID_CPicturePropPage)
END_PROPPAGEIDS(CRTreeCtrl)


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CRTreeCtrl, "RTREE.RTreeCtrl.1",
	0xe8cbaeae, 0x85c1, 0x11d1, 0xa1, 0xf0, 0x44, 0x45, 0x53, 0x54, 0, 0)


/////////////////////////////////////////////////////////////////////////////
// Type library ID and version

IMPLEMENT_OLETYPELIB(CRTreeCtrl, _tlid, _wVerMajor, _wVerMinor)


/////////////////////////////////////////////////////////////////////////////
// Interface IDs

const IID BASED_CODE IID_DRTree =
		{ 0xe8cbaeac, 0x85c1, 0x11d1, { 0xa1, 0xf0, 0x44, 0x45, 0x53, 0x54, 0, 0 } };
const IID BASED_CODE IID_DRTreeEvents =
		{ 0xe8cbaead, 0x85c1, 0x11d1, { 0xa1, 0xf0, 0x44, 0x45, 0x53, 0x54, 0, 0 } };


/////////////////////////////////////////////////////////////////////////////
// Control type information

static const DWORD BASED_CODE _dwRTreeOleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CRTreeCtrl, IDS_RTREE, _dwRTreeOleMisc)


/////////////////////////////////////////////////////////////////////////////
// CRTreeCtrl::CRTreeCtrlFactory::UpdateRegistry -
// Adds or removes system registry entries for CRTreeCtrl

BOOL CRTreeCtrl::CRTreeCtrlFactory::UpdateRegistry(BOOL bRegister)
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
			IDS_RTREE,
			IDB_RTREE,
			afxRegApartmentThreading,
			_dwRTreeOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}


/////////////////////////////////////////////////////////////////////////////
// Licensing strings

static const TCHAR BASED_CODE _szLicFileName[] = _T("RTree.lic");

static const WCHAR BASED_CODE _szLicString[] =
	L"Copyright (c) 1998 RowanSoftware";


/////////////////////////////////////////////////////////////////////////////
// CRTreeCtrl::CRTreeCtrlFactory::VerifyUserLicense -
// Checks for existence of a user license

BOOL CRTreeCtrl::CRTreeCtrlFactory::VerifyUserLicense()
{
	return AfxVerifyLicFile(AfxGetInstanceHandle(), _szLicFileName,
		_szLicString);
}


/////////////////////////////////////////////////////////////////////////////
// CRTreeCtrl::CRTreeCtrlFactory::GetLicenseKey -
// Returns a runtime licensing key

BOOL CRTreeCtrl::CRTreeCtrlFactory::GetLicenseKey(DWORD dwReserved,
	BSTR FAR* pbstrKey)
{
	if (pbstrKey == NULL)
		return FALSE;

	*pbstrKey = SysAllocString(_szLicString);
	return (*pbstrKey != NULL);
}


/////////////////////////////////////////////////////////////////////////////
// CRTreeCtrl::CRTreeCtrl - Constructor

CRTreeCtrl::CRTreeCtrl()
{
	InitializeIIDs(&IID_DRTree, &IID_DRTreeEvents);

	// TODO: Initialize your control's instance data here.
}


/////////////////////////////////////////////////////////////////////////////
// CRTreeCtrl::~CRTreeCtrl - Destructor

CRTreeCtrl::~CRTreeCtrl()
{
	Clear();
}


/////////////////////////////////////////////////////////////////////////////
// CRTreeCtrl::OnDraw - Drawing function

void CRTreeCtrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
{
	// draw the funky piccy
    m_pic.Render(pdc, rcBounds, rcBounds);

	// draw a box and fill it with text.
	// the zoom function will alter the font and box dimensions

    CFont* pOldFont;
    TEXTMETRIC tm;
    const CString& strCaption = InternalGetText();

    // Set the ForeColor property color and transparent background mode into the device context
    pdc->SetTextColor(TranslateColor(GetForeColor()));
    pdc->SetBkMode(TRANSPARENT);

    // Draw the caption using the stock Font and ForeColor properties
    pOldFont = SelectStockFont(pdc);
    pdc->GetTextMetrics(&tm);
    pdc->SetTextAlign(TA_LEFT | TA_TOP);
	int gapsize;
	int gapsize2;
	int ydistance;
	int xdistance=0;
	int index=0;
	char* buffer;
	CRect rect;
	for (int x=0;x<m_lDepth;x++)
	{
		gapsize=(int)(pow(2,x)-1)*m_lBoxHeight;
		ydistance=gapsize/2;
		gapsize2=(int)(pow(2,x-2)*m_lBoxHeight);
		for (int y=0;y<pow(2,m_lDepth-x-1);y++)
		{
			rect=CRect(xdistance,ydistance,xdistance+m_lBoxWidth,ydistance+m_lBoxHeight);
			buffer=(char*)GetText(index);
			if (buffer!=NULL)
			    pdc->ExtTextOut(rect.left+2, rect.top+2,
					ETO_CLIPPED, CRect(rect.left+2,rect.top+2,rect.right-2,rect.bottom-2), buffer, strlen(buffer), NULL);
			pdc->DrawEdge(rect,EDGE_ETCHED,BF_RECT);
			index++;
			if (x>0)
			{
				pdc->MoveTo(xdistance-m_lGapWidth,ydistance+(m_lBoxHeight/2)+gapsize2);
				pdc->LineTo(xdistance,ydistance+(m_lBoxHeight/2));
				pdc->MoveTo(xdistance-m_lGapWidth,ydistance+(m_lBoxHeight/2)-gapsize2);
				pdc->LineTo(xdistance,ydistance+(m_lBoxHeight/2));
			}
			ydistance+=gapsize+m_lBoxHeight;
		}
		xdistance+=m_lBoxWidth+m_lGapWidth;
	}
    pdc->SelectObject(pOldFont);
}


/////////////////////////////////////////////////////////////////////////////
// CRTreeCtrl::DoPropExchange - Persistence support

void CRTreeCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);
	PX_Picture(pPX, _T("ControlPicture"),m_pic);
    PX_Long(pPX, _T("BoxWidth"), m_lBoxWidth, TRUE);
    PX_Long(pPX, _T("BoxHeight"), m_lBoxHeight, TRUE);
    PX_Long(pPX, _T("Depth"), m_lDepth, TRUE);
    PX_Long(pPX, _T("GapWidth"), m_lGapWidth, TRUE);	
}


/////////////////////////////////////////////////////////////////////////////
// CRTreeCtrl::OnResetState - Reset control to default state

void CRTreeCtrl::OnResetState()
{
	COleControl::OnResetState();  // Resets defaults found in DoPropExchange
	m_pic.CreateEmpty();
	m_lBoxWidth=100;
	m_lBoxHeight=50;
	m_lGapWidth=50;
	m_lDepth=-1;
	m_list=NULL;
	SetDepth(4);
}


/////////////////////////////////////////////////////////////////////////////
// CRTreeCtrl message handlers

LPPICTUREDISP CRTreeCtrl::GetControlPicture() 
{
	return m_pic.GetPictureDispatch();
}

void CRTreeCtrl::SetControlPicture(LPPICTUREDISP newValue) 
{
	m_pic.SetPictureDispatch(newValue);
	InvalidateControl();
	SetModifiedFlag();
}

long CRTreeCtrl::GetDepth() 
{
	return m_lDepth;
}

void CRTreeCtrl::SetDepth(long nNewValue) 
{
	Clear();
	m_lDepth=nNewValue;
	int size=(int)pow(2,m_lDepth+1)-1;
	m_list=new char*[size];
	for (int x=0;x<size;x++)
	{
		m_list[x]=NULL;
	}
	InvalidateControl();
	SetModifiedFlag();
}

long CRTreeCtrl::GetBoxWidth() 
{
	return m_lBoxWidth;
}

void CRTreeCtrl::SetBoxWidth(long nNewValue) 
{
	m_lBoxWidth=nNewValue;
	InvalidateControl();
	SetModifiedFlag();
}

long CRTreeCtrl::GetBoxHeight() 
{
	return m_lBoxHeight;
}

void CRTreeCtrl::SetBoxHeight(long nNewValue) 
{
	m_lBoxHeight=nNewValue;
	InvalidateControl();
	SetModifiedFlag();
}

long CRTreeCtrl::GetGapWidth() 
{
	return m_lGapWidth;
}

void CRTreeCtrl::SetGapWidth(long nNewValue) 
{
	m_lGapWidth=nNewValue;
	InvalidateControl();
	SetModifiedFlag();
}

long CRTreeCtrl::GetText(short index) 
{
	return (long)m_list[index];
}

void CRTreeCtrl::Clear()
{
	for (int x=0;x<pow(2,m_lDepth+1)-1;x++)
	{
		if (m_list[x]!=NULL) delete [] m_list[x];
		m_list[x]=NULL;
	}
	if (m_list!=NULL) delete [] m_list;
}

void CRTreeCtrl::SetText(LPCTSTR text, short index) 
{
	if (m_list[index]!=NULL) delete m_list[index];
	m_list[index]=new char[strlen(text)+1]; // include terminating null character
	// remember to delete it
	strcpy(m_list[index],text);
	InvalidateControl();
}
