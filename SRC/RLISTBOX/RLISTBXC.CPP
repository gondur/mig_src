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

// RListBoxCtl.cpp : Implementation of the CRListBoxCtrl ActiveX Control class.

#define F_BATTLE
#define F_COMMON
#define F_GRAFIX
#include "stdafx.h"
#include "RListBox.h"
#include "RListBxC.h"
#include "RListBxP.h"
#include "messages.h"
#include "FileMan.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern int GetShadow1XOffset(int fontheight);
extern int GetShadow1YOffset(int fontheight);
extern int GetShadow2XOffset(int fontheight);
extern int GetShadow2YOffset(int fontheight);

IMPLEMENT_DYNCREATE(CRListBoxCtrl, COleControl)
BOOL CRListBoxCtrl::m_bDrawing = FALSE;

/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CRListBoxCtrl, COleControl)
	//{{AFX_MSG_MAP(CRListBoxCtrl)
	ON_WM_LBUTTONDOWN()
	ON_WM_CREATE()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_SETCURSOR()
	ON_WM_MOVE()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Dispatch map

BEGIN_DISPATCH_MAP(CRListBoxCtrl, COleControl)
	//{{AFX_DISPATCH_MAP(CRListBoxCtrl)
	DISP_PROPERTY_EX(CRListBoxCtrl, "IsStripey", GetIsStripey, SetIsStripey, VT_BOOL)
	DISP_PROPERTY_EX(CRListBoxCtrl, "StripeColor", GetStripeColor, SetStripeColor, VT_COLOR)
	DISP_PROPERTY_EX(CRListBoxCtrl, "SelectColor", GetSelectColor, SetSelectColor, VT_COLOR)
	DISP_PROPERTY_EX(CRListBoxCtrl, "Lines", GetLines, SetLines, VT_BOOL)
	DISP_PROPERTY_EX(CRListBoxCtrl, "LineColor", GetLineColor, SetLineColor, VT_COLOR)
	DISP_PROPERTY_EX(CRListBoxCtrl, "DarkStripeColor", GetDarkStripeColor, SetDarkStripeColor, VT_COLOR)
	DISP_PROPERTY_EX(CRListBoxCtrl, "DarkBackColor", GetDarkBackColor, SetDarkBackColor, VT_COLOR)
	DISP_PROPERTY_EX(CRListBoxCtrl, "LockLeftColumn", GetLockLeftColumn, SetLockLeftColumn, VT_BOOL)
	DISP_PROPERTY_EX(CRListBoxCtrl, "LockTopRow", GetLockTopRow, SetLockTopRow, VT_BOOL)
	DISP_PROPERTY_EX(CRListBoxCtrl, "LockColor", GetLockColor, SetLockColor, VT_COLOR)
	DISP_PROPERTY_EX(CRListBoxCtrl, "DragAndDrop", GetDragAndDrop, SetDragAndDrop, VT_BOOL)
	DISP_PROPERTY_EX(CRListBoxCtrl, "FontNum", GetFontNum, SetFontNum, VT_I4)
	DISP_PROPERTY_EX(CRListBoxCtrl, "Blackboard", GetBlackboard, SetBlackboard, VT_BOOL)
	DISP_PROPERTY_EX(CRListBoxCtrl, "FontNum2", GetFontNum2, SetFontNum2, VT_I4)
	DISP_PROPERTY_EX(CRListBoxCtrl, "Lines2", GetLines2, SetLines2, VT_BOOL)
	DISP_PROPERTY_EX(CRListBoxCtrl, "HeaderColor", GetHeaderColor, SetHeaderColor, VT_COLOR)
	DISP_PROPERTY_EX(CRListBoxCtrl, "SelectWholeRows", GetSelectWholeRows, SetSelectWholeRows, VT_BOOL)
	DISP_PROPERTY_EX(CRListBoxCtrl, "FontPtr", GetFontPtr, SetFontPtr, VT_I4)
	DISP_PROPERTY_EX(CRListBoxCtrl, "ParentPointer", GetParentPointer, SetParentPointer, VT_I4)
	DISP_PROPERTY_EX(CRListBoxCtrl, "HilightRow", GetHilightRow, SetHilightRow, VT_I4)
	DISP_PROPERTY_EX(CRListBoxCtrl, "HilightCol", GetHilightCol, SetHilightCol, VT_I4)
	DISP_PROPERTY_EX(CRListBoxCtrl, "Border", GetBorder, SetBorder, VT_BOOL)
	DISP_PROPERTY_EX(CRListBoxCtrl, "Centred", GetCentred, SetCentred, VT_BOOL)
	DISP_PROPERTY_EX(CRListBoxCtrl, "HorzSeperation", GetHorzSeperation, SetHorzSeperation, VT_I4)
	DISP_PROPERTY_EX(CRListBoxCtrl, "VertSeperation", GetVertSeperation, SetVertSeperation, VT_I4)
	DISP_PROPERTY_EX(CRListBoxCtrl, "ToggleResizableColumns", GetToggleResizableColumns, SetToggleResizableColumns, VT_BOOL)
	DISP_PROPERTY_EX(CRListBoxCtrl, "ScrlBarOffset", GetScrlBarOffset, SetScrlBarOffset, VT_I2)
	DISP_PROPERTY_EX(CRListBoxCtrl, "ShadowSelectColour", GetShadowSelectColour, SetShadowSelectColour, VT_COLOR)
	DISP_PROPERTY_EX(CRListBoxCtrl, "ShadowLineColor", GetShadowLineColor, SetShadowLineColor, VT_COLOR)
	DISP_PROPERTY_EX(CRListBoxCtrl, "DrawBackgGound", GetDrawBackgGound, SetDrawBackgGound, VT_BOOL)
	DISP_FUNCTION(CRListBoxCtrl, "GetCount", GetCount, VT_I2, VTS_NONE)
	DISP_FUNCTION(CRListBoxCtrl, "AddString", AddString, VT_EMPTY, VTS_BSTR VTS_I2)
	DISP_FUNCTION(CRListBoxCtrl, "DeleteString", DeleteString, VT_EMPTY, VTS_I2 VTS_I2)
	DISP_FUNCTION(CRListBoxCtrl, "Clear", Clear, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION(CRListBoxCtrl, "AddColumn", AddColumn, VT_EMPTY, VTS_I4)
	DISP_FUNCTION(CRListBoxCtrl, "SetColumnWidth", SetColumnWidth, VT_EMPTY, VTS_I2 VTS_I4)
	DISP_FUNCTION(CRListBoxCtrl, "AddPlayerNum", AddPlayerNum, VT_EMPTY, VTS_I4)
	DISP_FUNCTION(CRListBoxCtrl, "DeletePlayerNum", DeletePlayerNum, VT_I4, VTS_I2)
	DISP_FUNCTION(CRListBoxCtrl, "ReplacePlayerNum", ReplacePlayerNum, VT_I4, VTS_I4 VTS_I2)
	DISP_FUNCTION(CRListBoxCtrl, "ReplaceString", ReplaceString, VT_EMPTY, VTS_BSTR VTS_I2 VTS_I2)
	DISP_FUNCTION(CRListBoxCtrl, "GetString", GetString, VT_I4, VTS_I2 VTS_I2)
	DISP_FUNCTION(CRListBoxCtrl, "GetPlayerNum", GetPlayerNum, VT_I4, VTS_I2)
	DISP_FUNCTION(CRListBoxCtrl, "GetRowFromY", GetRowFromY, VT_I2, VTS_I4)
	DISP_FUNCTION(CRListBoxCtrl, "UpdateScrollBar", UpdateScrollBar, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION(CRListBoxCtrl, "GetListHeight", GetListHeight, VT_I4, VTS_NONE)
	DISP_FUNCTION(CRListBoxCtrl, "ResizeToFit", ResizeToFit, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION(CRListBoxCtrl, "Shrink", Shrink, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION(CRListBoxCtrl, "GetColumnWidth", GetColumnWidth, VT_I4, VTS_I4)
	DISP_FUNCTION(CRListBoxCtrl, "SetNumberOfRows", SetNumberOfRows, VT_EMPTY, VTS_I4)
	DISP_FUNCTION(CRListBoxCtrl, "InsertRow", InsertRow, VT_EMPTY, VTS_I4)
	DISP_FUNCTION(CRListBoxCtrl, "DeleteRow", DeleteRow, VT_EMPTY, VTS_I4)
	DISP_FUNCTION(CRListBoxCtrl, "SelectRecentlyFired", SelectRecentlyFired, VT_BOOL, VTS_NONE)
	DISP_FUNCTION(CRListBoxCtrl, "AddIconColumn", AddIconColumn, VT_EMPTY, VTS_I4)
	DISP_FUNCTION(CRListBoxCtrl, "AddIcon", AddIcon, VT_EMPTY, VTS_I4 VTS_I2)
	DISP_FUNCTION(CRListBoxCtrl, "SetHorizontalOption", SetHorizontalOption, VT_EMPTY, VTS_I2)
	DISP_FUNCTION(CRListBoxCtrl, "GetColFromX", GetColFromX, VT_I2, VTS_I4)
	DISP_FUNCTION(CRListBoxCtrl, "GetRowColPlayerNum", GetRowColPlayerNum, VT_I4, VTS_I4 VTS_I4)
	DISP_FUNCTION(CRListBoxCtrl, "SetColumnRightAligned", SetColumnRightAligned, VT_EMPTY, VTS_I4 VTS_BOOL)
	DISP_FUNCTION(CRListBoxCtrl, "SetRowColour", SetRowColour, VT_EMPTY, VTS_I4 VTS_I4)
	DISP_FUNCTION(CRListBoxCtrl, "SetIcon", SetIcon, VT_EMPTY, VTS_I4 VTS_I2 VTS_I2)
	DISP_STOCKPROP_FORECOLOR()
	DISP_STOCKPROP_BACKCOLOR()
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()


/////////////////////////////////////////////////////////////////////////////
// Event map

BEGIN_EVENT_MAP(CRListBoxCtrl, COleControl)
	//{{AFX_EVENT_MAP(CRListBoxCtrl)
	EVENT_CUSTOM("Select", FireSelect, VTS_I4 VTS_I4)
	EVENT_CUSTOM("DoubleSelect", FireDoubleSelect, VTS_I4  VTS_I4)
	//}}AFX_EVENT_MAP
END_EVENT_MAP()


/////////////////////////////////////////////////////////////////////////////
// Property pages

// TODO: Add more property pages as needed.  Remember to increase the count!
BEGIN_PROPPAGEIDS(CRListBoxCtrl, 2)
	PROPPAGEID(CRListBoxPropPage::guid)
    PROPPAGEID(CLSID_CColorPropPage)
END_PROPPAGEIDS(CRListBoxCtrl)


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CRListBoxCtrl, "RLISTBOX.RListBoxCtrl.1",
	0x48814009, 0x65ae, 0x11d1, 0xa1, 0xf0, 0x44, 0x45, 0x53, 0x54, 0, 0)


/////////////////////////////////////////////////////////////////////////////
// Type library ID and version

IMPLEMENT_OLETYPELIB(CRListBoxCtrl, _tlid, _wVerMajor, _wVerMinor)


/////////////////////////////////////////////////////////////////////////////
// Interface IDs

const IID BASED_CODE IID_DRListBox =
		{ 0x90b5eda6, 0x666f, 0x11d1, { 0xa1, 0xf0, 0x44, 0x45, 0x53, 0x54, 0, 0 } };
const IID BASED_CODE IID_DRListBoxEvents =
		{ 0x90b5eda7, 0x666f, 0x11d1, { 0xa1, 0xf0, 0x44, 0x45, 0x53, 0x54, 0, 0 } };


/////////////////////////////////////////////////////////////////////////////
// Control type information

static const DWORD BASED_CODE _dwRListBoxOleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CRListBoxCtrl, IDS_RLISTBOX, _dwRListBoxOleMisc)


/////////////////////////////////////////////////////////////////////////////
// CRListBoxCtrl::CRListBoxCtrlFactory::UpdateRegistry -
// Adds or removes system registry entries for CRListBoxCtrl

BOOL CRListBoxCtrl::CRListBoxCtrlFactory::UpdateRegistry(BOOL bRegister)
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
			IDS_RLISTBOX,
			IDB_RLISTBOX,
			afxRegApartmentThreading,
			_dwRListBoxOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}


/////////////////////////////////////////////////////////////////////////////
// Licensing strings

static const TCHAR BASED_CODE _szLicFileName[] = _T("RListBox.lic");

static const WCHAR BASED_CODE _szLicString[] =
	L"Copyright (c) 1997 RowanSoftware";


/////////////////////////////////////////////////////////////////////////////
// CRListBoxCtrl::CRListBoxCtrlFactory::VerifyUserLicense -
// Checks for existence of a user license

BOOL CRListBoxCtrl::CRListBoxCtrlFactory::VerifyUserLicense()
{
	return AfxVerifyLicFile(AfxGetInstanceHandle(), _szLicFileName,
		_szLicString);
}


/////////////////////////////////////////////////////////////////////////////
// CRListBoxCtrl::CRListBoxCtrlFactory::GetLicenseKey -
// Returns a runtime licensing key

BOOL CRListBoxCtrl::CRListBoxCtrlFactory::GetLicenseKey(DWORD dwReserved,
	BSTR FAR* pbstrKey)
{
	if (pbstrKey == NULL)
		return FALSE;

	*pbstrKey = SysAllocString(_szLicString);
	return (*pbstrKey != NULL);
}


/////////////////////////////////////////////////////////////////////////////
// CRListBoxCtrl::CRListBoxCtrl - Constructor

CRListBoxCtrl::CRListBoxCtrl()
{
	InitializeIIDs(&IID_DRListBox, &IID_DRListBoxEvents);
	m_bInit=FALSE;
	m_lHorzScrollPos=0;
	m_lVertScrollPos=0;
	m_iColSel=-1;
	m_iRowSel=-1;
	m_lines=FALSE;
	AddColumn(50);
	m_LButtonDown=FALSE;
//	m_bBothScrollBars=FALSE;
	m_iSeperator=-1;
	CF_PLAYER = RegisterClipboardFormat("Rowan Football Player");
	m_pFontPtr=NULL;
	m_bSelectRecentlyFired=FALSE;
	m_pParent=NULL;
	m_HorizontalOption = FALSE ;
	textheight = 16 ;
	m_pHorzScrollBar=NULL;
	m_pVertScrollBar=NULL;
	m_toggleresizeablecolumns=FALSE;
	m_ScrlBarOffset = 0 ;
	m_FirstSweep = TRUE;
	m_isIcon = FALSE;
	m_maxscrl = FALSE;											//AMM 10Jul99
	OldArt = FIL_NULL;
//	m_ShadowselectColor = RGB(0,0,0);
//	m_ShadowlineColor = RGB(0,0,0);
}


/////////////////////////////////////////////////////////////////////////////
// CRListBoxCtrl::~CRListBoxCtrl - Destructor

CRListBoxCtrl::~CRListBoxCtrl()
{
	Clear();
	if (m_pHorzScrollBar)
	{
		m_pHorzScrollBar->DestroyWindow();
		delete m_pHorzScrollBar;
	}
	if (m_pVertScrollBar)
	{
		m_pVertScrollBar->DestroyWindow();
		delete m_pVertScrollBar;
	}
}


/////////////////////////////////////////////////////////////////////////////
// CRListBoxCtrl::OnDraw - Drawing function

void CRListBoxCtrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
{
	if (m_bDrawing) return;
	m_bDrawing=TRUE;
	CRect rc=rcBounds;
	CWnd* parent;
	long offsets;
	FileNum artnum=FIL_NULL;
	CDC* pOffScreenDC;
	CBitmap* pOldBitmap;
	CBitmap bitmap;
	if (m_hWnd) 
	{
		if (m_pParent)
			parent=m_pParent;
		else
			parent=GetParent();
		offsets=parent->SendMessage(WM_GETXYOFFSET,NULL,NULL);

		if(m_FirstSweep != TRUE || m_isIcon == TRUE)
			artnum = (FileNum)parent->SendMessage(WM_GETARTWORK,NULL,NULL);
		if(!m_isIcon && OldArt!=FIL_NULL && OldArt != artnum)
		{
			m_FirstSweep = TRUE;
			OldArt = artnum;
			artnum=FIL_NULL;
		}
		else													//JIM 19May99
			OldArt = artnum;
	}
	if (artnum)
	{
		if ((pOffScreenDC=(CDC*)parent->SendMessage(WM_GETOFFSCREENDC,NULL,NULL)) == NULL)		
		{
			m_bDrawing = FALSE ;
			return ;	
		}
		bitmap.CreateCompatibleBitmap(pdc,rcBounds.right,rcBounds.bottom);
		pOldBitmap=pOffScreenDC->SelectObject(&bitmap);
	}
	else
	{
		pOffScreenDC=pdc;
	}

//	m_pVertScrollBar->SetParentPointer((long)parent);
//	m_pHorzScrollBar->SetParentPointer((long)parent);
	BOOL X2flag=FALSE;
	if (m_bBlackboard)
	{
		long offsetx;
		long offsety;

		if (m_hWnd)
		{
//			long offsets;
//			offsets=parent->SendMessage(WM_GETXYOFFSET,NULL,NULL);
			CRect rect;
			GetWindowRect(rect);
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
		if (m_hWnd)
		{
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
				parent->SendMessage(WM_RELEASELASTFILE,NULL,NULL);
			}
			X2flag=parent->SendMessage(WM_GETX2FLAG,NULL,NULL);
		}
		if (!artnum && m_FirstSweep != TRUE || !m_hWnd)
		{
			pOffScreenDC->FillRect(rcBounds, CBrush::FromHandle((HBRUSH)GetStockObject(BLACK_BRUSH)));
		}
	}
	m_FirstSweep = FALSE;
	// Now draw the text...

    pOffScreenDC->SetBkMode(TRANSPARENT);
	POSITION position1;// = m_list.GetHeadPosition();
	POSITION position2;
	POSITION position3;// = m_sizeList.GetHeadPosition();
	CList<char*,char*>* list;
	long offset=0;
	long offset2;
	long bottomline,leftedge;
	CPen pen;
	CPen* pOldPen;
	if (X2flag)
	{
		pen.CreatePen(PS_SOLID,2,TranslateColor(GetLineColor()));
	}
	else
	{
		pen.CreatePen(PS_SOLID,1,TranslateColor(GetLineColor()));
	}
	pOldPen=pOffScreenDC->SelectObject(&pen);

 	// Draw captions first (if any exist)
    CFont* pOldFont;
 	if (m_pFontPtr) 
		pOldFont = pOffScreenDC->SelectObject(m_pFontPtr);
 	else if (m_hWnd)
 	{
 		CFont*	temp ;
 		temp = (CFont*)GetParent()->SendMessage(WM_GETGLOBALFONT,abs(m_FontNum2),NULL) ;
 		pOldFont = pOffScreenDC->SelectObject(temp);
 	}
 	else 
		pOldFont = pOffScreenDC->GetCurrentFont();
 	int toprowheight=0;
 	int leftcolumnwidth=0;
    TEXTMETRIC tm;
    pOffScreenDC->GetTextMetrics(&tm);
 	tm.tmHeight+=GetShadow2YOffset(tm.tmHeight);
 	tm.tmHeight+=m_vertSeperation;
 	int startx=1;
 	if (m_border)
 		if (X2flag)
 			startx=4;
 		else
 			startx=3;

	POSITION position7;
	COLORREF rowcolour;
	if (m_bLockLeftColumn)
	{
		position3 = m_sizeList.GetHeadPosition();
		leftcolumnwidth=m_sizeList.GetNext(position3)*tm.tmHeight/16;
		position1 = m_list.GetHeadPosition();
		list=m_list.GetNext(position1);
		if (list->GetCount()>0)
		{
			position2=list->GetHeadPosition();
			position7=m_rowColourList.GetHeadPosition();
			for (int y=0;y<list->GetCount();y++)
			{
				char* text=list->GetNext(position2);
				rowcolour=m_rowColourList.GetNext(position7);
				if (leftcolumnwidth>5)
				{
					if (m_bLockTopRow)
					{
						CRect clipbox(startx,max(tm.tmHeight,y*tm.tmHeight-m_lVertScrollPos),leftcolumnwidth,(y+1)*tm.tmHeight-m_lVertScrollPos);
						if (m_FontNum2<0)
						{
							if(y==m_iRowSel && m_bSelectWholeRows)
							{
								pOffScreenDC->SetTextColor(m_ShadowselectColor);
							}
							else
							{
								pOffScreenDC->SetTextColor(m_ShadowlineColor);
							}
							int shadowx=GetShadow1XOffset(tm.tmHeight-m_vertSeperation);
							int shadowy=GetShadow1YOffset(tm.tmHeight-m_vertSeperation);
 							pOffScreenDC->ExtTextOut(m_horzSeperation+startx+shadowx,y*tm.tmHeight-m_lVertScrollPos+shadowy,ETO_CLIPPED,
 								clipbox,text,strlen(text),NULL);
 							shadowx=GetShadow2XOffset(tm.tmHeight-m_vertSeperation);
 							shadowy=GetShadow2YOffset(tm.tmHeight-m_vertSeperation);
							pOffScreenDC->ExtTextOut(m_horzSeperation+startx+shadowx,y*tm.tmHeight-m_lVertScrollPos+shadowy,ETO_CLIPPED,
								clipbox,text,strlen(text),NULL);
						}
						if (y==m_iRowSel && m_bSelectWholeRows)
						{
							pOffScreenDC->SetTextColor(TranslateColor(GetSelectColor()));
						}
						else
						{
							pOffScreenDC->SetTextColor(rowcolour);
						}
 						pOffScreenDC->ExtTextOut(m_horzSeperation+startx,y*tm.tmHeight-m_lVertScrollPos,ETO_CLIPPED,
 							clipbox,text,strlen(text),NULL);
					}
					else
					{
 						CRect clipbox(startx,y*tm.tmHeight-m_lVertScrollPos,leftcolumnwidth,(y+1)*tm.tmHeight-m_lVertScrollPos);
						if (m_FontNum2<0)
						{
							if(y==m_iRowSel && m_bSelectWholeRows)
							{
								pOffScreenDC->SetTextColor(m_ShadowselectColor);
							}
							else
							{
								pOffScreenDC->SetTextColor(m_ShadowlineColor);
							}
// 							pOffScreenDC->SetTextColor(RGB(0,0,0));
 							int shadowx=GetShadow1XOffset(tm.tmHeight-m_vertSeperation);
 							int shadowy=GetShadow1YOffset(tm.tmHeight-m_vertSeperation);
  							pOffScreenDC->ExtTextOut(m_horzSeperation+startx+shadowx,y*tm.tmHeight-m_lVertScrollPos+shadowy,ETO_CLIPPED,
  								clipbox,text,strlen(text),NULL);
 							shadowx=GetShadow2XOffset(tm.tmHeight-m_vertSeperation);
 							shadowy=GetShadow2YOffset(tm.tmHeight-m_vertSeperation);
// 							pOffScreenDC->ExtTextOut(1+shadowx,y*tm.tmHeight-m_lVertScrollPos+shadowy,ETO_CLIPPED,CRect(0,y*tm.tmHeight-m_lVertScrollPos,leftcolumnwidth,(y+1)*tm.tmHeight-m_lVertScrollPos),text,strlen(text),NULL);
  							pOffScreenDC->ExtTextOut(m_horzSeperation+startx+shadowx,y*tm.tmHeight-m_lVertScrollPos+shadowy,ETO_CLIPPED,
  								clipbox,text,strlen(text),NULL);
 						}
 						if (y==m_iRowSel && m_bSelectWholeRows)
 						{
 							pOffScreenDC->SetTextColor(TranslateColor(GetSelectColor()));
 						}
 						else
 						{
							pOffScreenDC->SetTextColor(rowcolour);
// 							pOffScreenDC->SetTextColor(TranslateColor(GetHeaderColor()));
 						}
  						pOffScreenDC->ExtTextOut(startx+m_horzSeperation,y*tm.tmHeight-m_lVertScrollPos,ETO_CLIPPED,
  								clipbox,text,strlen(text),NULL);

					}
				}
			}
		}
		if (m_lines)
		{
			pOffScreenDC->MoveTo(leftcolumnwidth-2,0);
			pOffScreenDC->LineTo(leftcolumnwidth-2,rc.bottom-rc.top);
			pOffScreenDC->MoveTo(leftcolumnwidth-1,0);
			pOffScreenDC->LineTo(leftcolumnwidth-1,rc.bottom-rc.top);
		}
	}	
	BOOL isPicture; //NewCode JW 04Nov98
	long AlignOffset;
	POSITION position4;
	POSITION position5;
	if (m_bLockTopRow)
	{
		toprowheight=tm.tmHeight;
		position1 = m_list.GetHeadPosition();
		position3 = m_sizeList.GetHeadPosition();
		position4 = m_isPictureList.GetHeadPosition();
		position5 = m_isRightAlignedList.GetHeadPosition();
		for (int x=0;x<m_list.GetCount();x++)
		{
			offset2=m_sizeList.GetNext(position3)*tm.tmHeight/16;
			isPicture=m_isPictureList.GetNext(position4);
			if (m_isRightAlignedList.GetNext(position5))
			{
				AlignOffset=offset2;
				pOffScreenDC->SetTextAlign(TA_RIGHT | TA_TOP);
			}
			else
			{
				AlignOffset=0;
				pOffScreenDC->SetTextAlign(TA_LEFT | TA_TOP);
			}
			if (offset+offset2-m_lHorzScrollPos>rc.right-rc.left) offset2=rc.right-rc.left-offset+m_lHorzScrollPos;
			if (offset2==0) break;
			if (x==m_list.GetCount()-1) offset2=rc.right-rc.left-offset+m_lHorzScrollPos;
			list=m_list.GetNext(position1);
			if (list->GetCount()>0)
			{
				position2=list->GetHeadPosition();
				char* text=list->GetNext(position2);			//1 on mark's
				if (offset2>5)
				{

					if (isPicture && !m_bLockTopRow)//TempCode JW 04Nov98
						DrawClippedBitmap(pOffScreenDC,(FileNum)(long)text,offset-m_lHorzScrollPos,0,CRect(leftcolumnwidth,0,max(leftcolumnwidth,offset-m_lHorzScrollPos+offset2),tm.tmHeight));
					else
					{
						CRect clipbox(max(offset-m_lHorzScrollPos,leftcolumnwidth),0,max(leftcolumnwidth,offset-m_lHorzScrollPos+offset2),tm.tmHeight);

						if (m_FontNum2<0)
						{
							pOffScreenDC->SetTextColor(RGB(0,0,0));
							int shadowx=GetShadow1XOffset(tm.tmHeight-m_vertSeperation);
							int shadowy=GetShadow1YOffset(tm.tmHeight-m_vertSeperation);
							pOffScreenDC->ExtTextOut(m_horzSeperation+offset+AlignOffset-m_lHorzScrollPos+shadowx,shadowy,ETO_CLIPPED,
								clipbox,text,strlen(text),NULL);
							shadowx=GetShadow2XOffset(tm.tmHeight-m_vertSeperation);
							shadowy=GetShadow2YOffset(tm.tmHeight-m_vertSeperation);
							pOffScreenDC->ExtTextOut(m_horzSeperation+offset+AlignOffset-m_lHorzScrollPos+shadowx,shadowy,ETO_CLIPPED,
								clipbox,text,strlen(text),NULL);
						}
						pOffScreenDC->SetTextColor(TranslateColor(GetHeaderColor()));
//						pOffScreenDC->ExtTextOut(offset-m_lHorzScrollPos,0,ETO_CLIPPED,CRect(leftcolumnwidth,0,max(leftcolumnwidth,offset-m_lHorzScrollPos+offset2),tm.tmHeight),text,strlen(text),NULL);
						pOffScreenDC->ExtTextOut(m_horzSeperation+offset+AlignOffset-m_lHorzScrollPos,0,ETO_CLIPPED,
								clipbox,text,strlen(text),NULL);
					}
				}
			}
			offset+=offset2;

			if (m_bLines2)// && m_bLockTopRow)
			{
				pOffScreenDC->MoveTo(0,tm.tmHeight+1);
				pOffScreenDC->LineTo(rc.right-rc.left,tm.tmHeight+1);
				pOffScreenDC->MoveTo(0,tm.tmHeight);
				pOffScreenDC->LineTo(rc.right-rc.left,tm.tmHeight);
			}
		}
	}

	// Now draw internal text
	offset=0;
	position1 = m_list.GetHeadPosition();
	position3 = m_sizeList.GetHeadPosition();
	position4 = m_isPictureList.GetHeadPosition();
	position5 = m_isRightAlignedList.GetHeadPosition();
	if (m_pFontPtr) pOffScreenDC->SelectObject(m_pFontPtr);
	else if (m_hWnd) pOffScreenDC->SelectObject((CFont*)GetParent()->SendMessage(WM_GETGLOBALFONT,abs(m_FontNum),NULL));

	for (int x=0;x<m_list.GetCount();x++)
	{
		offset2=m_sizeList.GetNext(position3)*tm.tmHeight/16;
		if (m_isRightAlignedList.GetNext(position5))
		{
			AlignOffset=offset2;
			pOffScreenDC->SetTextAlign(TA_RIGHT | TA_TOP);
		}
		else
		{
			AlignOffset=0;
			pOffScreenDC->SetTextAlign(TA_LEFT | TA_TOP);
		}
		isPicture=m_isPictureList.GetNext(position4);
		if (offset+offset2-m_lHorzScrollPos>rc.right-rc.left) offset2=rc.right-rc.left-offset+m_lHorzScrollPos;
		if (offset2==0) break;
		if (x==m_list.GetCount()-1) offset2=rc.right-rc.left-offset+m_lHorzScrollPos;
		list=m_list.GetNext(position1);
		if (list->GetCount()>0)
		{
			position2=list->GetHeadPosition();
			position7=m_rowColourList.GetHeadPosition();
			for (int y=0;y<list->GetCount();y++)
			{
				rowcolour=m_rowColourList.GetNext(position7);
				char* string=list->GetNext(position2);
				bottomline=(y+1)*tm.tmHeight-m_lVertScrollPos;
				if (m_bCentred) leftedge=((rcBounds.right-rcBounds.left-pOffScreenDC->GetTextExtent(string,strlen(string)).cx)/2);
				else leftedge=offset-m_lHorzScrollPos+1;
				int clipleftedge;
				if (leftedge<leftcolumnwidth)
					clipleftedge=leftcolumnwidth;
				else
					clipleftedge=leftedge;
				if (m_FontNum<0 && !isPicture)
				{
					if(y==m_iRowSel && (x==m_iColSel || m_bSelectWholeRows))
					{
						pOffScreenDC->SetTextColor(m_ShadowselectColor);
					}
					else
					{
						pOffScreenDC->SetTextColor(m_ShadowlineColor);
					}
//					pOffScreenDC->SetTextColor(RGB(0,0,0));
					int shadowx=GetShadow1XOffset(tm.tmHeight-m_vertSeperation);
					int shadowy=GetShadow1YOffset(tm.tmHeight-m_vertSeperation);
					pOffScreenDC->ExtTextOut(leftedge+AlignOffset+shadowx,bottomline-tm.tmHeight+shadowy,
						ETO_CLIPPED,CRect(clipleftedge,toprowheight,offset+offset2-m_lHorzScrollPos,10000),
						string,strlen(string),NULL);
					shadowx=GetShadow2XOffset(tm.tmHeight-m_vertSeperation);
					shadowy=GetShadow2YOffset(tm.tmHeight-m_vertSeperation);
					pOffScreenDC->ExtTextOut(leftedge+AlignOffset+shadowx,bottomline-tm.tmHeight+shadowy,
						ETO_CLIPPED,CRect(clipleftedge,toprowheight,offset+offset2-m_lHorzScrollPos,10000),
						string,strlen(string),NULL);
				}
				if (y==m_iRowSel && (x==m_iColSel || m_bSelectWholeRows))
				{
					pOffScreenDC->SetTextColor(TranslateColor(GetSelectColor()));
				}
				else
				{
					pOffScreenDC->SetTextColor(rowcolour);
//					pOffScreenDC->SetTextColor(TranslateColor(GetForeColor()));
				}
//				char* string=list->GetNext(position2);
//				pOffScreenDC->TextOut(offset-m_lHorzScrollPos,y*tm.tmHeight-m_lVertScrollPos,list->GetNext(position2));
//				bottomline=(y+1)*tm.tmHeight-m_lVertScrollPos;
				if (offset2>6)
				{
					if (isPicture)
						DrawClippedBitmap(pOffScreenDC,(FileNum)(long)string,
							offset-m_lHorzScrollPos+1,bottomline-tm.tmHeight,
							CRect(leftcolumnwidth,toprowheight,max(leftcolumnwidth,offset+offset2-m_lHorzScrollPos),10000));
					else
						pOffScreenDC->ExtTextOut(leftedge+AlignOffset,bottomline-tm.tmHeight,
							ETO_CLIPPED,CRect(clipleftedge,toprowheight,max(leftcolumnwidth,offset+offset2-m_lHorzScrollPos),10000),
							string,strlen(string),NULL);
				}
				if (m_bLines2 && bottomline>toprowheight)
				{
					pOffScreenDC->MoveTo(0,bottomline);
					pOffScreenDC->LineTo(rc.right-rc.left,bottomline);
				}
			}
		}
		offset+=offset2;

		if (m_lines && offset-1-m_lHorzScrollPos>leftcolumnwidth)
		{
			pOffScreenDC->MoveTo(offset-1-m_lHorzScrollPos,0);
			pOffScreenDC->LineTo(offset-1-m_lHorzScrollPos,rc.bottom-rc.top);
		}
	}

	if (m_vert && m_horz)
	{
		pOffScreenDC->FillSolidRect(CRect(rcBounds.right-m_horz,rcBounds.bottom-m_vert,rcBounds.right,rcBounds.bottom),RGB(0,0,0));
	}

// now draw a nice border

	if (m_border)
	{
		rc.right-=m_vert;
		rc.bottom-=m_horz;
		if (X2flag)
		{
			pOffScreenDC->MoveTo(1,1);
			pOffScreenDC->LineTo(rc.right-1,1);
			pOffScreenDC->LineTo(rc.right-1,rc.bottom-1);
			pOffScreenDC->LineTo(1,rc.bottom-1);
			pOffScreenDC->LineTo(1,1);
		}
		else
		{
			pOffScreenDC->MoveTo(0,0);
			pOffScreenDC->LineTo(rc.right-1,0);
			pOffScreenDC->LineTo(rc.right-1,rc.bottom-1);
			pOffScreenDC->LineTo(0,rc.bottom-1);
			pOffScreenDC->LineTo(0,0);
		}
	}

/*
	CBrush stripe;
	CBrush back;
	CBrush darkstripe;
	CBrush darkback;
	CBrush lockcolor;
	CBrush lock;
	back.CreateSolidBrush(TranslateColor(GetBackColor()));
	stripe.CreateSolidBrush(TranslateColor(GetStripeColor()));
	darkback.CreateSolidBrush(TranslateColor(GetDarkBackColor()));
	darkstripe.CreateSolidBrush(TranslateColor(GetDarkStripeColor()));
	lock.CreateSolidBrush(TranslateColor(GetLockColor()));

    pOffScreenDC->SetTextAlign(TA_LEFT | TA_TOP);
    pOffScreenDC->SetBkMode(TRANSPARENT);
	POSITION position1 = m_list.GetHeadPosition();
	POSITION position2;
	POSITION position3 = m_sizeList.GetHeadPosition();
	if (m_lines)
	{
		CPen pen;
		pen.CreatePen(PS_SOLID,1,TranslateColor(GetLineColor()));
		pOffScreenDC->SelectObject(&pen);
	}
	CList<char*,char*>* list;
	long offset=0;
	long offset2;
	for (int x=0;x<m_list.GetCount();x++)
	{
		offset2=m_sizeList.GetNext(position3);
		if (offset+offset2-m_lHorzScrollPos>rc.right-rc.left) offset2=rc.right-rc.left-offset+m_lHorzScrollPos;
		if (offset2==0) break;
		if (x==m_list.GetCount()-1) offset2=rc.right-rc.left-offset+m_lHorzScrollPos;
		if (x%2==0)
		{
			pOffScreenDC->FillRect(CRect(rc.left+offset-m_lHorzScrollPos,rc.top,rc.left+offset+offset2-m_lHorzScrollPos,rc.bottom),&back);
			if (m_bIsStripey==TRUE)
			{
				int bottom;
				int top;
				for (int x=rc.top-m_lVertScrollPos%(tm.tmHeight*2);x<rc.bottom;x+=(tm.tmHeight*2))
				{
					// clipping
					top=x;
					if (top<rc.top) top=rc.top;
					bottom=x+tm.tmHeight;
					if (bottom>rc.bottom) bottom=rc.bottom;
					// draw the clipped stripe
					pOffScreenDC->FillRect(CRect(rc.left+offset-m_lHorzScrollPos,top,rc.left+offset+offset2-m_lHorzScrollPos,bottom),&
						stripe);
				}
			}
		}
		if (m_pic.GetType()==PICTYPE_NONE && x%2!=0)
		{
			pOffScreenDC->FillRect(CRect(rc.left+offset-m_lHorzScrollPos,rc.top,rc.left+offset+offset2-m_lHorzScrollPos,rc.bottom),&darkback);
			if (m_bIsStripey==TRUE)
			{
				int bottom;
				int top;
				for (int x=rc.top-m_lVertScrollPos%(tm.tmHeight*2);x<rc.bottom;x+=(tm.tmHeight*2))
				{
					// clipping
					top=x;
					if (top<rc.top) top=rc.top;
					bottom=x+tm.tmHeight;
					if (bottom>rc.bottom) bottom=rc.bottom;
					// draw the clipped stripe
					pOffScreenDC->FillRect(CRect(rc.left+offset-m_lHorzScrollPos,top,rc.left+offset+offset2-m_lHorzScrollPos,bottom),&
						darkstripe);
				}
			}
		}
		list=m_list.GetNext(position1);
		if (list->GetCount()>0)
		{
			position2=list->GetHeadPosition();
			for (int y=0;y<list->GetCount();y++)
			{
				if (x==m_iColSel && y==m_iRowSel)
				{
					pOffScreenDC->SetTextColor(TranslateColor(GetSelectColor()));
				}
				else
				{
					pOffScreenDC->SetTextColor(TranslateColor(GetForeColor()));
				}
				pOffScreenDC->TextOut(offset-m_lHorzScrollPos,y*tm.tmHeight-m_lVertScrollPos,list->GetNext(position2));
			}
		}
		offset+=offset2;

		if (m_lines)
		{
			pOffScreenDC->MoveTo(offset-1-m_lHorzScrollPos,0);
			pOffScreenDC->LineTo(offset-1-m_lHorzScrollPos,rc.bottom-rc.top);
		}
	}
	pOffScreenDC->SetTextColor(TranslateColor(GetForeColor()));
	if (m_bLockTopRow==TRUE)
	{
		if (m_pic.GetType()==PICTYPE_NONE)
		{
			pOffScreenDC->FillRect(CRect(rc.left,rc.top,rc.right,rc.top+tm.tmHeight),&lock);
		}
		offset=0;
		position1 = m_list.GetHeadPosition();
		position3 = m_sizeList.GetHeadPosition();
		for (int x=0;x<m_list.GetCount();x++)
		{
			offset2=m_sizeList.GetNext(position3);
			if (offset+offset2-m_lHorzScrollPos>rc.right-rc.left) offset2=rc.right-rc.left-offset+m_lHorzScrollPos;
			if (offset2==0) break;
			if (x==m_list.GetCount()-1) offset2=rc.right-rc.left-offset+m_lHorzScrollPos;
			list=m_list.GetNext(position1);
			if (list->GetCount()>0)
			{
				position2=list->GetHeadPosition();
				char* text=list->GetNext(position2);
				pOffScreenDC->ExtTextOut(offset-m_lHorzScrollPos,0,ETO_CLIPPED,CRect(offset-m_lHorzScrollPos,0,offset-m_lHorzScrollPos+offset2,tm.tmHeight),text,strlen(text),NULL);
			}
			offset+=offset2;
		}
//		rc.top+=tm.tmHeight; // prevent drawing on top row
	}
	int width;
	if (m_bLockLeftColumn==TRUE)
	{
		position3 = m_sizeList.GetHeadPosition();
		width=m_sizeList.GetNext(position3);
		pOffScreenDC->FillRect(CRect(rc.left,rc.top,rc.left+width,rc.bottom),&lock);
		position1 = m_list.GetHeadPosition();
		list=m_list.GetNext(position1);
		if (list->GetCount()>0)
		{
			position2=list->GetHeadPosition();
			for (int y=0;y<list->GetCount();y++)
			{
				char* text=list->GetNext(position2);
				pOffScreenDC->ExtTextOut(0,y*tm.tmHeight-m_lVertScrollPos,ETO_CLIPPED,CRect(0,y*tm.tmHeight-m_lVertScrollPos,width,(y+1)*tm.tmHeight-m_lVertScrollPos),text,strlen(text),NULL);
			}
		}
	}
	if (m_bLockLeftColumn && m_bLockTopRow)
	{
		pOffScreenDC->FillRect(CRect(rcBounds.left,rcBounds.top,rcBounds.left+width,rcBounds.top+tm.tmHeight),&lock);
	}
	if (m_bBothScrollBars)
	{
		pOffScreenDC->FillRect(CRect(rc.right-16,rc.bottom-16,rc.right,rc.bottom),&lock);
	}
*/
	if (artnum)
	{
		pdc->BitBlt(0,0,rcBounds.right-rcBounds.left,rcBounds.bottom-rcBounds.top,pOffScreenDC,
						0,0,SRCCOPY)!=NULL; // flips offscreen dc to real dc
		pOffScreenDC->SelectObject(pOldBitmap);
	}
	pOffScreenDC->SelectObject(pOldPen);
	pOffScreenDC->SelectObject(pOldFont);
	m_bDrawing=FALSE;
}


/////////////////////////////////////////////////////////////////////////////
// CRListBoxCtrl::DoPropExchange - Persistence support

void CRListBoxCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);
	PX_Bool(pPX, _T("IsStripey"), m_bIsStripey, FALSE);
	PX_Bool(pPX, _T("Lines"), m_lines, FALSE);
	PX_Bool(pPX, _T("Lines2"), m_bLines2, FALSE);
	PX_Bool(pPX, _T("LockLeftColumn"), m_bLockLeftColumn, FALSE);
	PX_Bool(pPX, _T("LockTopRow"), m_bLockTopRow, FALSE);
	PX_Bool(pPX, _T("DragAndDrop"), m_bDragAndDrop, FALSE);
    PX_Color(pPX, _T("StripeColor"), m_stripeColor, FALSE);
    PX_Color(pPX, _T("SelectColor"), m_selectColor, FALSE);
    PX_Color(pPX, _T("LineColor"), m_lineColor, FALSE);
    PX_Color(pPX, _T("DarkStripeColor"), m_darkStripeColor, FALSE);
    PX_Color(pPX, _T("DarkBackColor"), m_darkBackColor, FALSE);
    PX_Color(pPX, _T("LockColor"), m_lockColor, FALSE);
    PX_Color(pPX, _T("HeaderColor"), m_headerColor, FALSE);
	PX_Long(pPX, _T("FontNum"), m_FontNum, 0);
	PX_Long(pPX, _T("FontNum2"), m_FontNum2, 0);
	PX_Bool(pPX, _T("Blackboard"), m_bBlackboard, FALSE);
	PX_Bool(pPX, _T("SelectWholeRows"), m_bSelectWholeRows, FALSE);
	//	PX_Color(pPX, _T("ShadowlineColor"), m_ShadowlineColor, FALSE);
//	PX_Color(pPX, _T("ShadowselectColor"), m_ShadowselectColor, FALSE);
	if (pPX->GetVersion()&0x1)
	{
		PX_Bool(pPX, _T("Border"), m_border, FALSE);
		PX_Long(pPX, _T("HorzSeperation"), m_horzSeperation, 2);
		PX_Long(pPX, _T("VertSeperation"), m_vertSeperation, 2);
		PX_Bool(pPX, _T("Centred"), m_bCentred, FALSE);
	}
	else
	{
		m_border=FALSE;
		m_bCentred=FALSE;
		m_vertSeperation=0;
		m_horzSeperation=0;
	}
	if (pPX->GetVersion()&0x2)
	{
		PX_Color(pPX, _T("ShadowlineColor"), m_ShadowlineColor, FALSE);
		PX_Color(pPX, _T("ShadowselectColor"), m_ShadowselectColor, FALSE);
	}
	else 
	{
		m_ShadowlineColor = RGB(0,0,0);
		m_ShadowselectColor = RGB(0,0,0);
	}
}


/////////////////////////////////////////////////////////////////////////////
// CRListBoxCtrl::OnResetState - Reset control to default state

void CRListBoxCtrl::OnResetState()
{
	COleControl::OnResetState();  // Resets defaults found in DoPropExchange
	m_bIsStripey=FALSE;
	SetStripeColor(RGB(0,250,0));
	SetBackColor(RGB(0,200,0));
	SetDarkStripeColor(RGB(0,150,0));
	SetDarkBackColor(RGB(0,100,0));
	SetSelectColor(RGB(255,0,0));
	SetLockColor(RGB(200,200,200));
	SetHeaderColor(RGB(0,255,0));
	SetForeColor(RGB(255,255,255));
}


/////////////////////////////////////////////////////////////////////////////
// CRListBoxCtrl message handlers

BOOL CRListBoxCtrl::GetIsStripey() 
{
	return m_bIsStripey;
}

void CRListBoxCtrl::SetIsStripey(BOOL bNewValue) 
{
	m_bIsStripey=bNewValue;
    SetModifiedFlag();
	InvalidateControl();
    BoundPropertyChanged(dispidIsStripey);
}

OLE_COLOR CRListBoxCtrl::GetStripeColor() 
{
	return m_stripeColor;
}

void CRListBoxCtrl::SetStripeColor(OLE_COLOR nNewValue) 
{
	m_stripeColor=nNewValue;
	InvalidateControl();
	SetModifiedFlag();
}

OLE_COLOR CRListBoxCtrl::GetSelectColor()
{
	return m_selectColor;
}

void CRListBoxCtrl::SetSelectColor(OLE_COLOR nNewValue) 
{
	m_selectColor=nNewValue;
	InvalidateControl();
	SetModifiedFlag();
}

short CRListBoxCtrl::GetCount() 
{
	// returns the size of the biggest column
	int biggest=0;
	int count;
	POSITION position = m_list.GetHeadPosition();
	for (int x=0;x<m_list.GetCount();x++)
	{
		 count = m_list.GetNext(position)->GetCount();
		 if (count>biggest) biggest=count;
	}
	return biggest;
}

void CRListBoxCtrl::AddString(LPCTSTR text,short index) 
{
	char* buffer=new char[strlen(text)+1]; // include terminating null character
	strcpy(buffer,text);
	if (m_HorizontalOption)  //TempCode JW 04Nov98 	
	{
		int lines, linesize, height ;
		CRect rc ;
		GetWindowRect(rc);
		lines = m_list.GetAt(m_list.FindIndex(index))->GetCount() ;
		linesize = (lines + 1) * textheight ;
		height = rc.Height();
		if (m_HorizontalOption && 
			linesize > height * (m_NoRepeats + 1)) // allow for second and third+ rows on grid style system
		{
			AddSetOfColumns();
			m_Lines = lines;
			m_NoRepeats++;	
		}
		CList<char*,char*>* list=m_list.GetAt(m_list.FindIndex(index + (m_NoRepeats*m_NoColumnsToRepeat)));
		list->AddTail(buffer);
		while (list->GetCount()>m_rowColourList.GetCount())
		{
			m_rowColourList.AddTail(TranslateColor(GetForeColor()));
		}
	}	
	else
	{
		CList<char*,char*>* list=m_list.GetAt(m_list.FindIndex(index));
		list->AddTail(buffer);
		while (list->GetCount()>m_rowColourList.GetCount())
		{
			m_rowColourList.AddTail(TranslateColor(GetForeColor()));
		}
	}
	// remember to delete it
	UpdateScrollBar();
}

int CRListBoxCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (COleControl::OnCreate(lpCreateStruct) == -1)
		return -1;
	return 0;
}

void CRListBoxCtrl::DeleteString(short row,short column) 
{
	POSITION position1;
	position1=m_list.FindIndex(column);
	CList<char*,char*>* list=m_list.GetAt(position1);
	POSITION position2;
	position2=list->FindIndex(row);
	delete [] list->GetAt(position2);
	list->RemoveAt(position2);
	delete list;
	m_list.RemoveAt(position1);
//	delete [] m_list.GetAt(position);
//	m_list.RemoveAt(position);
	UpdateScrollBar();
}

void CRListBoxCtrl::Clear() 
{
	POSITION position1 = m_list.GetHeadPosition();
	POSITION position2;
	POSITION position3 = m_isPictureList.GetHeadPosition();
	CList<char*,char*>* list;
	int countx=m_list.GetCount();
	int county;
	BOOL isPicture;
	for (int x=0;x<countx;x++)
	{
		list=m_list.GetNext(position1);
		isPicture=m_isPictureList.GetNext(position3);
		if (!isPicture)
		{
			position2=list->GetHeadPosition();
			county=list->GetCount();
			for (int y=0;y<county;y++)
			{
				delete [] list->GetNext(position2);
			}
		}	
		list->RemoveAll();
		delete list;
	}
	m_list.RemoveAll();
	m_sizeList.RemoveAll();
	m_playerList.RemoveAll();
	m_isPictureList.RemoveAll();
	m_rowColourList.RemoveAll();
//	UpdateScrollBar();
	m_lVertScrollPos=0;
	m_lHorzScrollPos=0;
	m_iColSel=-1;
	m_iRowSel=-1;
	InvalidateControl();
}

BEGIN_EVENTSINK_MAP(CRListBoxCtrl, COleControl)
    //{{AFX_EVENTSINK_MAP(CRListBoxCtrl)
	ON_EVENT(CRListBoxCtrl, 1000, 1 /* Scroll */, OnScrollVert, VTS_I4)
	ON_EVENT(CRListBoxCtrl, 1001, 1 /* Scroll */, OnScrollHorz, VTS_I4)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CRListBoxCtrl::OnScrollVert(long nPos) 
{
	m_lVertScrollPos=nPos;
	InvalidateControl();
}

void CRListBoxCtrl::OnScrollHorz(long nPos) 
{
	m_lHorzScrollPos=nPos;
	InvalidateControl();
}

void CRListBoxCtrl::UpdateScrollBar()
{
	CWnd* parent=GetParent();
	m_vert=0;
	m_horz=0;
	CDC* pdc;
	pdc=GetDC();
    CFont* pOldFont;
	if (m_pFontPtr) pOldFont = pdc->SelectObject(m_pFontPtr);
	else if (m_hWnd) pOldFont = pdc->SelectObject((CFont*)GetParent()->SendMessage(WM_GETGLOBALFONT,abs(m_FontNum2),NULL));
	else pOldFont = pdc->GetCurrentFont();
    TEXTMETRIC tm;
    pdc->GetTextMetrics(&tm);
	tm.tmHeight+=GetShadow2YOffset(tm.tmHeight);
 	tm.tmHeight+=m_vertSeperation;

	CRect rcBounds;
	GetClientRect(rcBounds);
	if (m_border)
	{
		rcBounds.top++;
		rcBounds.bottom-=2;	//seems to be a height???
		rcBounds.left++;
		rcBounds.right--;
	}
	int height=GetCount()*tm.tmHeight;
	if (height>rcBounds.bottom-rcBounds.top)
	{
		m_vert=16;
	}
	int width=0;
	POSITION position=m_sizeList.GetHeadPosition();
	for (int x=0;x<m_sizeList.GetCount();x++)
	{
		width+=m_sizeList.GetNext(position)*tm.tmHeight/16;
	}
	if (width>(rcBounds.right-rcBounds.left)-m_vert)
	{
		m_horz=16;
		if (!m_pHorzScrollBar)
		{
			m_pHorzScrollBar=new CRScrlBar;
			m_pHorzScrollBar->Create(NULL, WS_VISIBLE, CRect(-1,-1,-1,-1), this, 1001);
			if (m_ScrlBarOffset != 0)
				m_pHorzScrollBar->SetFileNumOffset(m_ScrlBarOffset) ;
		}
		m_pHorzScrollBar->ShowWindow(SW_SHOW);
	}
	else
	{
		if (m_pHorzScrollBar)
		{
//			m_pHorzScrollBar->Move(-1,-1,-1,-1);
			m_pHorzScrollBar->ShowWindow(SW_HIDE);
		}
	}
//	TRACE3("%d,%d,%d\n",height,rcBounds.bottom-rcBounds.top,m_horz);
	if (height>(rcBounds.bottom-rcBounds.top)-m_horz)
	{
		m_vert=16;
		if (!m_pVertScrollBar)
		{
			m_pVertScrollBar=new CRScrlBar;
			m_pVertScrollBar->Create(NULL, WS_VISIBLE, CRect(-1,-1,-1,-1), this, 1000);
			if (m_ScrlBarOffset != 0)
				m_pVertScrollBar->SetFileNumOffset(m_ScrlBarOffset) ;
		}
		m_pVertScrollBar->ShowWindow(SW_SHOW);
	}
	else
	{
		if (m_pVertScrollBar)
		{
//			m_pVertScrollBar->Move(-1,-1,-1,-1);
			m_pVertScrollBar->ShowWindow(SW_HIDE);
		}
	}
	int maxvalue;
	if (m_horz>0)
	{
		m_pHorzScrollBar->Move(rcBounds.left,rcBounds.bottom-16,rcBounds.right-m_vert,rcBounds.bottom);
		m_pHorzScrollBar->SetMinValue(0);
		maxvalue=width-(rcBounds.right-rcBounds.left)+m_vert;
		m_pHorzScrollBar->SetMaxValue(maxvalue);
		m_pHorzScrollBar->SetHorzAlign(TRUE);
		m_pHorzScrollBar->SetPageSize(rcBounds.right-rcBounds.left);
		if (m_lHorzScrollPos>maxvalue)
		{
			m_lHorzScrollPos=maxvalue;
		}
		m_pHorzScrollBar->SetScrollPos(m_lHorzScrollPos);			
	}
	else m_lHorzScrollPos=0;
	if (m_vert>0)
	{
		m_pVertScrollBar->Move(rcBounds.right-16,rcBounds.top,rcBounds.right,rcBounds.bottom-m_horz);
		m_pVertScrollBar->SetMinValue(0);
		maxvalue=GetCount()*tm.tmHeight-(rcBounds.bottom-rcBounds.top)+m_horz;
		m_pVertScrollBar->SetMaxValue(maxvalue);
		m_pVertScrollBar->SetStepSize(tm.tmHeight);
		m_pVertScrollBar->SetPageSize(rcBounds.bottom-rcBounds.top);
		if (m_lVertScrollPos>maxvalue || m_maxscrl == TRUE)		//AMM 10Jul99
//DeadCode AMM 10Jul99 		if (m_lVertScrollPos>maxvalue)
		{
			m_lVertScrollPos=maxvalue;
			m_maxscrl = FALSE;									//AMM 10Jul99
		}
		m_pVertScrollBar->SetScrollPos(m_lVertScrollPos);
//		if (m_horz>0) m_bBothScrollBars=TRUE;
//		else m_bBothScrollBars=FALSE;
	}
	else m_lVertScrollPos=0;
    pdc->SelectObject(pOldFont);
	ReleaseDC(pdc);
	InvalidateControl();
}

void CRListBoxCtrl::AddColumn(long width) 
{
	CList<char*,char*>* list=new CList<char*,char*>;
	m_list.AddTail(list);
	m_sizeList.AddTail(width);
	m_isPictureList.AddTail(FALSE);
	m_isRightAlignedList.AddTail(FALSE);
//	UpdateScrollBar();
}

void CRListBoxCtrl::SetColumnWidth(short index, long width) 
{
	m_sizeList.SetAt(m_sizeList.FindIndex(index),width);
}

BOOL CRListBoxCtrl::GetLines() 
{
	return m_lines;
}

void CRListBoxCtrl::SetLines(BOOL bNewValue) 
{
	m_lines=bNewValue;
	InvalidateControl();
	SetModifiedFlag();
}

OLE_COLOR CRListBoxCtrl::GetLineColor() 
{
	return m_lineColor;
}

void CRListBoxCtrl::SetLineColor(OLE_COLOR nNewValue) 
{
	m_lineColor=nNewValue;
	InvalidateControl();
	SetModifiedFlag();
}

void CRListBoxCtrl::OnLButtonDown(UINT nFlags, CPoint point) 
{
	if (m_vert && m_horz)
	{
		CRect rect;
		GetClientRect(rect);
		if (point.x>rect.right-m_horz || point.y>rect.bottom-m_vert) 
			return;
	}
	m_LButtonDown=TRUE;
	m_OldPoint=point;
	SetCapture();
	if (m_iSeperator==-1)
	{
		CDC* pdc;
		pdc=GetDC();
	    CFont* pOldFont;
		if (m_pFontPtr) pOldFont = pdc->SelectObject(m_pFontPtr);
		else if (m_hWnd) pOldFont = pdc->SelectObject((CFont*)GetParent()->SendMessage(WM_GETGLOBALFONT,abs(m_FontNum2),NULL));
		else pOldFont = pdc->GetCurrentFont();
		TEXTMETRIC tm;
		pdc->GetTextMetrics(&tm);
 		tm.tmHeight+=GetShadow2YOffset(tm.tmHeight);
 		tm.tmHeight+=m_vertSeperation;
		int offset=0;
		POSITION position;
		position=m_sizeList.GetHeadPosition();
		m_iSeperator = -1;
		for (int x=0;x<m_sizeList.GetCount();x++)
		{
			m_iOldSize=m_sizeList.GetNext(position)*tm.tmHeight/16;
			offset+=m_iOldSize;
			if (point.x+m_lHorzScrollPos<offset) break;
		}
		m_iColSel=x;
		int count=m_list.GetCount()-1;
		if (m_iColSel>count) m_iColSel=count;
		if (m_iColSel<0) m_iColSel=0;
		m_iRowSel=(point.y+m_lVertScrollPos)/tm.tmHeight;
		count=m_list.GetAt(m_list.FindIndex(m_iColSel))->GetCount()-1;
		if (m_iRowSel>count) m_iRowSel=count;
		if (m_iRowSel<0) m_iRowSel=0;
		if (m_iOldColSel!=m_iColSel || m_iOldRowSel!=m_iRowSel) InvalidateControl();
		pdc->SelectObject(pOldFont);
		ReleaseDC(pdc);
		RedrawWindow();
	}
	COleControl::OnLButtonDown(nFlags, point);
}

void CRListBoxCtrl::OnLButtonUp(UINT nFlags, CPoint point) 
{
	m_LButtonDown=FALSE;
	ReleaseCapture();
	if (m_iSeperator==-1)
	{
		CDC* pdc;
		pdc=GetDC();
	    CFont* pOldFont;
		if (m_pFontPtr) pOldFont = pdc->SelectObject(m_pFontPtr);
		else if (m_hWnd) pOldFont = pdc->SelectObject((CFont*)GetParent()->SendMessage(WM_GETGLOBALFONT,abs(m_FontNum2),NULL));
		else pOldFont = pdc->GetCurrentFont();
		TEXTMETRIC tm;
		pdc->GetTextMetrics(&tm);
		tm.tmHeight+=GetShadow2YOffset(tm.tmHeight);
	 	tm.tmHeight+=m_vertSeperation;
		int offset=0;
		POSITION position;
		position=m_sizeList.GetHeadPosition();
		for (int x=0;x<m_sizeList.GetCount();x++)
		{
			offset+=m_sizeList.GetNext(position)*tm.tmHeight/16;
			if (point.x+m_lHorzScrollPos<offset) break;
		}
		m_iColSel=x;
		int count=m_list.GetCount()-1;
		if (m_iColSel>count) m_iColSel=count;
		if (m_iColSel<0) m_iColSel=0;
		m_iRowSel=(point.y+m_lVertScrollPos)/tm.tmHeight;
		count=m_list.GetAt(m_list.FindIndex(m_iColSel))->GetCount()-1;
		if (m_iRowSel>count) m_iRowSel=count;
		if (m_iRowSel<0) m_iRowSel=0;
		if (m_iOldColSel!=m_iColSel || m_iOldRowSel!=m_iRowSel) InvalidateControl();
		pdc->SelectObject(pOldFont);
		ReleaseDC(pdc);
		m_bSelectRecentlyFired=TRUE;
		InvalidateControl();
		CWnd* parent;
//DEADCODE DAW 13/04/99 		if (m_pParent)
//DEADCODE DAW 13/04/99 			parent=m_pParent;
//DEADCODE DAW 13/04/99 		else
			parent=GetParent();
		// do a sound dependent on the current font

		if (m_FontNum==-10)
		{
			parent->SendMessage(WM_PLAYSOUND,FIL_SFX_OFFICE_DRAWER1,NULL);
		}
		else
		{
			parent->SendMessage(WM_PLAYSOUND,FIL_SFX_OFFICE_KEYPRESS2,NULL);
		}
		InvalidateControl();
		FireSelect(m_iRowSel,m_iColSel);
		return;
	}
	else UpdateScrollBar();
	COleControl::OnLButtonUp(nFlags, point);
}

void CRListBoxCtrl::OnMouseMove(UINT nFlags, CPoint point) 
{
	CDC* pdc;
	pdc=GetDC();
    CFont* pOldFont;
	if (m_pFontPtr) pOldFont = pdc->SelectObject(m_pFontPtr);
	else if (m_hWnd) pOldFont = pdc->SelectObject((CFont*)GetParent()->SendMessage(WM_GETGLOBALFONT,abs(m_FontNum2),NULL));
	else pOldFont = pdc->GetCurrentFont();
	TEXTMETRIC tm;
	pdc->GetTextMetrics(&tm);
	tm.tmHeight+=GetShadow2YOffset(tm.tmHeight);
 	tm.tmHeight+=m_vertSeperation;
    pdc->SelectObject(pOldFont);
	ReleaseDC(pdc);
	if (m_LButtonDown==FALSE)
	{
		if (m_vert && m_horz)
		{
			CRect rect;
			GetClientRect(rect);
			if (point.x>rect.right-m_horz || point.y>rect.bottom-m_vert) 
				return;
		}
		// check if we just moved over one of the dividing lines
		int offset=0;
		m_iSeperator = -1;
		if (m_lines && !m_toggleresizeablecolumns || !m_lines && m_toggleresizeablecolumns)
		{
			POSITION position;
			position=m_sizeList.GetHeadPosition();
			for (int x=0;x<m_sizeList.GetCount();x++)
			{
				m_iOldSize=m_sizeList.GetNext(position)*tm.tmHeight/16;
				offset+=m_iOldSize;
				if (x==0 && m_bLockLeftColumn && point.x>offset-3 && point.x<offset+3)
				{
					m_iSeperator=0;
					break;
				}
				// see if we clicked within 2 pixels either side of the seperator
				if (point.x+m_lHorzScrollPos>offset-3 && point.x+m_lHorzScrollPos<offset+3)
				{ // if its the right most seperator ignore it
					if (x<m_sizeList.GetCount()-1)
					{
						m_iSeperator=x;
						break;
					}
				}
			}
		}
	}
	if (m_LButtonDown==TRUE && m_iSeperator==-1)
	{// check here if we have moved enough to warrant drag & drop...
		CRect ptrect = CRect(m_OldPoint.x-5,m_OldPoint.y-5,m_OldPoint.x+5,m_OldPoint.y+5);
		if (ptrect.PtInRect(point) || m_bDragAndDrop==FALSE) // havent moved enough to warrant drag drop
		{
			m_iOldColSel=m_iColSel;
			m_iOldRowSel=m_iRowSel;
			CDC* pdc;
			pdc=GetDC();
		    CFont* pOldFont;
			if (m_pFontPtr) pOldFont = pdc->SelectObject(m_pFontPtr);
			else if (m_hWnd) pOldFont = pdc->SelectObject((CFont*)GetParent()->SendMessage(WM_GETGLOBALFONT,abs(m_FontNum2),NULL));
			else pOldFont = pdc->GetCurrentFont();
			TEXTMETRIC tm;
			pdc->GetTextMetrics(&tm);
			tm.tmHeight+=GetShadow2YOffset(tm.tmHeight);
		 	tm.tmHeight+=m_vertSeperation;
			int offset=0;
			POSITION position;
			position=m_sizeList.GetHeadPosition();
			for (int x=0;x<m_sizeList.GetCount();x++)
			{
				offset+=m_sizeList.GetNext(position)*tm.tmHeight/16;
				if (point.x+m_lHorzScrollPos<offset) break;
			}
			m_iColSel=x;
			int count=m_list.GetCount()-1;
			if (m_iColSel>count) m_iColSel=count;
			if (m_iColSel<0) m_iColSel=0;
			m_iRowSel=(point.y+m_lVertScrollPos)/tm.tmHeight;
			count=m_list.GetAt(m_list.FindIndex(m_iColSel))->GetCount()-1;
			if (m_iRowSel>count) m_iRowSel=count;
			if (m_iRowSel<0) m_iRowSel=0;
			if (m_iOldColSel!=m_iColSel || m_iOldRowSel!=m_iRowSel) InvalidateControl();
			pdc->SelectObject(pOldFont);
			ReleaseDC(pdc);
		}
		else
		{
			long playerNum=GetRowColPlayerNum(m_iRowSel, m_iColSel);
			if (playerNum != NULL)
			{
				long shirtNum=atol((char*)GetString(m_iRowSel,1));
				TRACE1("Dragging %d\n",playerNum);
				HGLOBAL hglobal;
				hglobal=GlobalAlloc(GHND,12);
				if (hglobal==NULL) return;
				long* pglobal = (long*)GlobalLock(hglobal);
				*pglobal=playerNum;
				*(pglobal+1)=shirtNum;
				*(pglobal+2)=(long)m_hWnd;
				GlobalUnlock(hglobal);
				COleDataSource oledatasource;
				oledatasource.CacheGlobalData(CF_PLAYER,hglobal);
				CRect rect;
				GetClientRect(rect);
				DROPEFFECT result=oledatasource.DoDragDrop(); //DROPEFFECT_COPY,rect,NULL);	
				TRACE1("Drag & Drop result %d\n",result);
			}
/*			if (result=DROPEFFECT_MOVE)
			{
				// delete the contents of that row
				// check if its the correct row since if the drag drop
				// ended up adding something above us then the row
				// will need to be increased by 1;
				if (GetPlayerNum(m_iRowSel)!=playerNum) m_iRowSel++;
				DeletePlayerNum(m_iRowSel);
				for (int x=0;x<m_list.GetCount();x++)
					DeleteString(m_iRowSel,x);
			}*/ // disabled for now
			m_LButtonDown=FALSE;
		}
	}
	else if (m_LButtonDown==TRUE)
	{
		int newSeperation=point.x-m_OldPoint.x+m_iOldSize;
		if (newSeperation<5) newSeperation=5;
		m_sizeList.SetAt(m_sizeList.FindIndex(m_iSeperator),newSeperation*16/tm.tmHeight);
		InvalidateControl();
	}
	COleControl::OnMouseMove(nFlags, point);
}

OLE_COLOR CRListBoxCtrl::GetDarkStripeColor() 
{
	return m_darkStripeColor;
}

void CRListBoxCtrl::SetDarkStripeColor(OLE_COLOR nNewValue) 
{
	m_darkStripeColor=nNewValue;
	InvalidateControl();
	SetModifiedFlag();
}

OLE_COLOR CRListBoxCtrl::GetDarkBackColor() 
{
	return m_darkBackColor;
}

void CRListBoxCtrl::SetDarkBackColor(OLE_COLOR nNewValue) 
{
	m_darkBackColor=nNewValue;
	InvalidateControl();
	SetModifiedFlag();
}

BOOL CRListBoxCtrl::GetLockLeftColumn() 
{
	return m_bLockLeftColumn;
}

void CRListBoxCtrl::SetLockLeftColumn(BOOL bNewValue) 
{
	m_bLockLeftColumn=bNewValue;
	InvalidateControl();
	SetModifiedFlag();
}

BOOL CRListBoxCtrl::GetLockTopRow() 
{
	return m_bLockTopRow;
}

void CRListBoxCtrl::SetLockTopRow(BOOL bNewValue) 
{
	m_bLockTopRow=bNewValue;
	InvalidateControl();
	SetModifiedFlag();
}

OLE_COLOR CRListBoxCtrl::GetLockColor() 
{
	return m_lockColor;
}

void CRListBoxCtrl::SetLockColor(OLE_COLOR nNewValue) 
{
	m_lockColor=nNewValue;
	InvalidateControl();
	SetModifiedFlag();
}

BOOL CRListBoxCtrl::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	if (m_iSeperator>-1)
	    ::SetCursor(AfxGetApp()->LoadStandardCursor(IDC_SIZEWE));
	else
		::SetCursor(AfxGetApp()->LoadStandardCursor(IDC_ARROW));
	return TRUE;
}

BOOL CRListBoxCtrl::GetDragAndDrop() 
{
	return m_bDragAndDrop;
}

void CRListBoxCtrl::SetDragAndDrop(BOOL bNewValue) 
{
	m_bDragAndDrop=bNewValue;
	SetModifiedFlag();
}

void CRListBoxCtrl::ReplaceString(LPCTSTR text, short row, short col) 
{
	CList<char*,char*>* list=m_list.GetAt(m_list.FindIndex(col));
	POSITION position = list->FindIndex(row);
	ASSERT(position != NULL); // the cell does not exist
	delete list->GetAt(position);
	char* buffer=new char[strlen(text)+1]; // include terminating null character
	strcpy(buffer,text);
	list->SetAt(position,buffer);
	InvalidateControl();
}

void CRListBoxCtrl::AddPlayerNum(long playerNum) 
{
	m_playerList.AddTail(playerNum);
}

long CRListBoxCtrl::DeletePlayerNum(short row) 
{
	POSITION position;
	long playerNum;
	position=m_playerList.FindIndex(row);
	playerNum = m_playerList.GetAt(position);
	m_playerList.RemoveAt(position);
	return playerNum;
}

long CRListBoxCtrl::ReplacePlayerNum(long playerNum, short row) 
{
	POSITION position;
	long playerNumOld;
	position=m_playerList.FindIndex(row);
	playerNumOld = m_playerList.GetAt(position);
	m_playerList.SetAt(position,playerNum);
	return playerNumOld;
}

long CRListBoxCtrl::GetString(short row, short col) 
{
	CList<char*,char*>* list=m_list.GetAt(m_list.FindIndex(col));
	return (long)list->GetAt(list->FindIndex(row));
}

long CRListBoxCtrl::GetPlayerNum(short row) 
{
	POSITION position;
	long playerNumOld;
	position=m_playerList.FindIndex(row);
	if (position == NULL)
		return(NULL) ;
	playerNumOld = m_playerList.GetAt(position);
	return playerNumOld;
}

short CRListBoxCtrl::GetRowFromY(long y) 
{
	CDC* pdc;
	pdc=GetDC();
    CFont* pOldFont;
	if (m_pFontPtr) pOldFont = pdc->SelectObject(m_pFontPtr);
	else if (m_hWnd) pOldFont = pdc->SelectObject((CFont*)GetParent()->SendMessage(WM_GETGLOBALFONT,abs(m_FontNum2),NULL));
	else pOldFont = pdc->GetCurrentFont();
    TEXTMETRIC tm;
    pdc->GetTextMetrics(&tm);
	tm.tmHeight+=GetShadow2YOffset(tm.tmHeight);
 	tm.tmHeight+=m_vertSeperation;
    pdc->SelectObject(pOldFont);
	ReleaseDC(pdc);
	short row=(short)((y+m_lVertScrollPos)/tm.tmHeight);
	if (row>m_playerList.GetCount()) row=-1; // selected beyond the end
	return row;
}

long CRListBoxCtrl::GetFontNum() 
{
	return m_FontNum;
}

void CRListBoxCtrl::SetFontNum(long nNewValue) 
{
	m_FontNum=nNewValue;
	SetModifiedFlag();
	InvalidateControl();
}

BOOL CRListBoxCtrl::GetBlackboard() 
{
	return m_bBlackboard;
}

void CRListBoxCtrl::SetBlackboard(BOOL bNewValue) 
{
	m_bBlackboard=bNewValue;
	InvalidateControl();
	SetModifiedFlag();
}

long CRListBoxCtrl::GetFontNum2() 
{
	return m_FontNum2;
}

void CRListBoxCtrl::SetFontNum2(long nNewValue) 
{
	m_FontNum2=nNewValue;
	InvalidateControl();
	SetModifiedFlag();
}

BOOL CRListBoxCtrl::GetLines2() 
{
	return m_bLines2;
}

void CRListBoxCtrl::SetLines2(BOOL bNewValue) 
{
	m_bLines2=bNewValue;
	InvalidateControl();
	SetModifiedFlag();
}

OLE_COLOR CRListBoxCtrl::GetHeaderColor() 
{
 	return m_headerColor;
}

void CRListBoxCtrl::SetHeaderColor(OLE_COLOR nNewValue) 
{
	m_headerColor=nNewValue;
	InvalidateControl();
	SetModifiedFlag();
}

BOOL CRListBoxCtrl::GetSelectWholeRows() 
{
	return m_bSelectWholeRows;
}

void CRListBoxCtrl::SetSelectWholeRows(BOOL bNewValue) 
{
	m_bSelectWholeRows=bNewValue;
	InvalidateControl();
	SetModifiedFlag();
}

long CRListBoxCtrl::GetFontPtr() 
{
	return (long)m_pFontPtr;
}

void CRListBoxCtrl::SetFontPtr(long nNewValue) 
{
	m_pFontPtr=(CFont*)nNewValue;
	InvalidateControl();
	SetModifiedFlag();
}

void CRListBoxCtrl::OnMove(int x, int y) 
{
	COleControl::OnMove(x, y);
	UpdateScrollBar();	
}

long CRListBoxCtrl::GetListHeight() 
{
	CDC* pdc;
	pdc=GetDC();
    CFont* pOldFont;
	if (m_pFontPtr) pOldFont = pdc->SelectObject(m_pFontPtr);
	else if (m_hWnd) pOldFont = pdc->SelectObject((CFont*)GetParent()->SendMessage(WM_GETGLOBALFONT,abs(m_FontNum2),NULL));
	else pOldFont = pdc->GetCurrentFont();
    TEXTMETRIC tm;
    pdc->GetTextMetrics(&tm);
	tm.tmHeight+=GetShadow2YOffset(tm.tmHeight);
 	tm.tmHeight+=m_vertSeperation;
    pdc->SelectObject(pOldFont);
	ReleaseDC(pdc);
	return (GetCount()*tm.tmHeight)+GetShadow2YOffset(tm.tmHeight);
}

void CRListBoxCtrl::ResizeToFit() 
{
	// calculate width and height of listbox
	// first find current position of listbox
	// why windows doesnt have a proper command for this I dont know
	CDC* pdc;
	pdc=GetDC();
	pdc->SetMapMode(MM_TEXT);
    CFont* pOldFont;
	if (m_pFontPtr) pOldFont = pdc->SelectObject(m_pFontPtr);
	else if (m_hWnd) pOldFont = pdc->SelectObject((CFont*)GetParent()->SendMessage(WM_GETGLOBALFONT,abs(m_FontNum2),NULL));
	else pOldFont = pdc->GetCurrentFont();
	TEXTMETRIC tm;
	pdc->GetTextMetrics(&tm);
	tm.tmHeight+=GetShadow2YOffset(tm.tmHeight);
 	tm.tmHeight+=m_vertSeperation;
    pdc->SelectObject(pOldFont);
	ReleaseDC(pdc);
	CRect rect;
	GetWindowRect(rect);
	CRect parentrect;
	GetParent()->GetClientRect(parentrect);
	GetParent()->ClientToScreen(parentrect);
	CPoint topleft;
	topleft=rect.TopLeft()-parentrect.TopLeft();
	int width=0;
	POSITION position=m_sizeList.GetHeadPosition();
	for (int x=0;x<m_sizeList.GetCount();x++)
	{
		width+=m_sizeList.GetNext(position)*tm.tmHeight/16;
	}
	MoveWindow(topleft.x,topleft.y,width,GetListHeight());
	UpdateScrollBar();
}

void CRListBoxCtrl::SetParentPointer(long nNewValue) 
{
	m_pParent=(CWnd*)nNewValue;
	if (m_pVertScrollBar)
		m_pVertScrollBar->SetParentPointer(nNewValue);
	if (m_pHorzScrollBar)
		m_pHorzScrollBar->SetParentPointer(nNewValue);
	SetModifiedFlag();
}

void CRListBoxCtrl::Shrink() // this sets all the columns to be the minimum possible size...
{
	CDC* pdc;
	pdc=GetDC();
    CFont* pOldFont;
	if (m_pFontPtr) pOldFont = pdc->SelectObject(m_pFontPtr);
	else if (m_hWnd) pOldFont = pdc->SelectObject((CFont*)GetParent()->SendMessage(WM_GETGLOBALFONT,abs(m_FontNum2),NULL));
	else pOldFont = pdc->GetCurrentFont();
	TEXTMETRIC tm;
	pdc->GetTextMetrics(&tm);
	int spacing=tm.tmHeight/6;
	POSITION position1;// = m_list.GetHeadPosition();
	POSITION position2;
	POSITION position3;
	int bestwidth;
	int newwidth;
	CList<char*,char*>* list;
	position1 = m_list.GetHeadPosition();
	position3 = m_sizeList.GetHeadPosition();
	for (int x=0;x<m_list.GetCount();x++)
	{
		list=m_list.GetNext(position1);
		bestwidth=0;
		if (list->GetCount()>0)
		{
			position2=list->GetHeadPosition();
			for (int y=0;y<list->GetCount();y++)
			{
				char* string=list->GetNext(position2);
				newwidth=pdc->GetTextExtent(string).cx;
				if (newwidth>bestwidth)
					bestwidth=newwidth;
			}
			m_sizeList.SetAt(position3,((bestwidth)*16/tm.tmHeight)+spacing);
			m_sizeList.GetNext(position3);
		}
	}
    pdc->SelectObject(pOldFont);
	ReleaseDC(pdc);
	Invalidate();
}

long CRListBoxCtrl::GetParentPointer() 
{
	return (long)m_pParent;
}



long CRListBoxCtrl::GetHilightRow() 
{
	return m_iRowSel;
}

void CRListBoxCtrl::SetHilightRow(long nNewValue) 
{
	if(nNewValue == -1)											//AMM 10Jul99
	{															//AMM 10Jul99
		m_maxscrl = TRUE;										//AMM 10Jul99
		UpdateScrollBar();										//AMM 10Jul99
	}															//AMM 10Jul99
	else														//AMM 10Jul99
	{															//AMM 10Jul99
		m_iRowSel=nNewValue;
		// find out if this is off the window
		CDC* pdc;
		pdc=GetDC();
		CFont* pOldFont;
		if (m_pFontPtr) pOldFont = pdc->SelectObject(m_pFontPtr);
		else if (m_hWnd) pOldFont = pdc->SelectObject((CFont*)GetParent()->SendMessage(WM_GETGLOBALFONT,m_FontNum2,NULL));
		else pOldFont = pdc->GetCurrentFont();
		TEXTMETRIC tm;
		pdc->GetTextMetrics(&tm);
		int ypos=(m_iRowSel*tm.tmHeight)-m_lVertScrollPos;
		CRect rect;
		GetClientRect(rect);
		if (ypos<0 || ypos>(rect.bottom-tm.tmHeight*(m_bLockTopRow+1)))
		{
			m_lVertScrollPos=(m_iRowSel-1)*tm.tmHeight;
			if (m_lVertScrollPos<0) m_lVertScrollPos=0;
			UpdateScrollBar();
		}
		pdc->SelectObject(pOldFont);
		ReleaseDC(pdc);
	}
	InvalidateControl();
}

long CRListBoxCtrl::GetHilightCol() 
{
	return m_iColSel;
}

void CRListBoxCtrl::SetHilightCol(long nNewValue) 
{
	m_iColSel=nNewValue;
	InvalidateControl();
}

long CRListBoxCtrl::GetColumnWidth(long col) 
{
	return m_sizeList.GetAt(m_sizeList.FindIndex(col));
}

void CRListBoxCtrl::SetNumberOfRows(long rows) 
{
//	INT3;
	POSITION position1 = m_list.GetHeadPosition();
	POSITION position2;
	CList<char*,char*>* list;
	int count;
	char* buffer;
	for (int x=0;x<m_list.GetCount();x++)
	{
		list=m_list.GetNext(position1);
		count=list->GetCount();
		if (count<=rows) // add extra rows
		{
			for (int y=count;y<rows;y++)
			{
				buffer=new char[1];
				buffer[0]=NULL;
				list->AddTail(buffer);
			}
		}
		else // delete extra rows
		{
			for (int y=rows;y<count;y++)
			{
				char* tail=list->GetTail();
				list->RemoveTail();
				delete []tail;
			}
		}
	}
	while (rows>m_rowColourList.GetCount())
	{
		m_rowColourList.AddTail(TranslateColor(GetForeColor()));
	}

	InvalidateControl();
}

void CRListBoxCtrl::InsertRow(long row) 
{
///why why why???	SetNumberOfRows(row-1);
	POSITION position1 = m_list.GetHeadPosition();
	POSITION position2;
	CList<char*,char*>* list;
	char* buffer;
	for (int x=0;x<m_list.GetCount();x++)
	{
		list=m_list.GetNext(position1);
		buffer=new char[1];
		buffer[0]=NULL;
		if (row==0)
			list->AddHead(buffer);
		else
		{
			position2 = list->FindIndex(row-1);
			list->InsertAfter(position2,buffer);
		}
		while (list->GetCount()>m_rowColourList.GetCount())
		{
			m_rowColourList.AddTail(TranslateColor(GetForeColor()));
		}
	}
	UpdateScrollBar();
}

void CRListBoxCtrl::DeleteRow(long row) 
{
	POSITION position1 = m_list.GetHeadPosition();
	POSITION position2;
	CList<char*,char*>* list;
	for (int x=0;x<m_list.GetCount();x++)
	{
		list=m_list.GetNext(position1);
		position2 = list->FindIndex(row);
		delete list->GetAt(position2);
		list->RemoveAt(position2);
	}
	UpdateScrollBar();
}

BOOL CRListBoxCtrl::SelectRecentlyFired() 
{
	BOOL temp=m_bSelectRecentlyFired;
	m_bSelectRecentlyFired=FALSE;
	return temp;
}

void CRListBoxCtrl::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	CRListBoxCtrl::OnLButtonDown(nFlags, point);
	FireDoubleSelect(m_iRowSel,m_iColSel);
}

void CRListBoxCtrl::OnSize(UINT nType, int cx, int cy) 
{
	COleControl::OnSize(nType, cx, cy);
	UpdateScrollBar();	
}

BOOL CRListBoxCtrl::GetBorder() 
{
	return m_border;
}

void CRListBoxCtrl::SetBorder(BOOL bNewValue) 
{
	m_border=bNewValue;
	SetModifiedFlag();
}

//Code JW 04Nov98 
void CRListBoxCtrl::DrawClippedBitmap(CDC * pDC, FileNum filenum, int x, int y, CRect cliprect)
{
	CWnd* parent;
	parent=GetParent();
	BYTE* pData;
	pData = (BYTE*)parent->SendMessage(WM_GETFILE,filenum,NULL);
	if (pData && pData[0]=='B' && pData[1]=='M') // checks if its a bitmap file
	{
		// now render it...
		BITMAPFILEHEADER* pFile=(BITMAPFILEHEADER*)pData;
		BITMAPINFO* pInfo=(BITMAPINFO*)(pData+sizeof(BITMAPFILEHEADER));
		pData+=pFile->bfOffBits;
		BYTE* pData2=pData;		//tim 2/2/99
		BYTE code;				//tim 2/2/99
		int width=pInfo->bmiHeader.biWidth;
		int height=pInfo->bmiHeader.biHeight;
		if (cliprect.left>x) 
		{
			width-=cliprect.left-x;
			x=cliprect.left;
		}
		if (cliprect.top>y) 
		{
			height-=cliprect.top-y;
			y=cliprect.top;
		}
		if (cliprect.right<x+width)
		{
			width=cliprect.right-x;
		}
		if (cliprect.bottom<y+height)
		{
			height=cliprect.bottom-y;
		}
		int x2,y2;				//tim 2/2/99
		RGBQUAD color;
		for (y2=height-1;y2>=0;y2--)
		{
			for ( x2=0 ; x2<width ; x2++)
			{
				code=*pData2++;
				if (code!=254 && x2<pInfo->bmiHeader.biWidth)
				{
					color=pInfo->bmiColors[code] ;
					pDC->SetPixel(x+x2,y+y2,RGB(color.rgbRed,color.rgbGreen,color.rgbBlue));
				}
			}
		}						//tim 2/2/99
//		SetDIBitsToDevice(pDC->m_hDC,x,y,width,height,						//tim 2/2/99
//			0,0,0,pInfo->bmiHeader.biHeight,pData,pInfo,DIB_RGB_COLORS);	//tim 2/2/99
	}
	parent->SendMessage(WM_RELEASELASTFILE,NULL,NULL);
}

void CRListBoxCtrl::AddSetOfColumns() 
{
	int						i ;
	POSITION				sizelist ;
	POSITION				picturelist	;
	POSITION				rightalignedlist ;
	long					columnsize, iscolumnpicture ;
	BOOL					isrightaligned;
	CList<char*,char*>*		list ;

	sizelist = m_sizeList.GetHeadPosition();
	picturelist = m_isPictureList.GetHeadPosition();
	rightalignedlist = m_isRightAlignedList.GetHeadPosition();
	for (i=0 ; i < m_NoColumnsToRepeat ; i++)
	{
		list = new CList<char*,char*>;
		columnsize = m_sizeList.GetNext(sizelist) ;
		iscolumnpicture = m_isPictureList.GetNext(picturelist) ;
		isrightaligned = m_isRightAlignedList.GetNext(rightalignedlist) ;
		m_list.AddTail( list ) ; // this list is 2d, others are 1d
		m_sizeList.AddTail(columnsize);
		m_isPictureList.AddTail(iscolumnpicture);
		m_isRightAlignedList.AddTail(isrightaligned);
	}
}

BOOL CRListBoxCtrl::GetCentred() 
{
	return m_bCentred;
}

void CRListBoxCtrl::SetCentred(BOOL bNewValue) 
{
	m_bCentred=bNewValue;
	InvalidateControl();
	SetModifiedFlag();
}

long CRListBoxCtrl::GetHorzSeperation() 
{
	return m_horzSeperation;
}

void CRListBoxCtrl::SetHorzSeperation(long nNewValue) 
{
	m_horzSeperation=nNewValue;
	InvalidateControl();
	SetModifiedFlag();
}

long CRListBoxCtrl::GetVertSeperation() 
{
	return m_vertSeperation;
}

void CRListBoxCtrl::SetVertSeperation(long nNewValue) 
{
	m_vertSeperation=nNewValue;
	InvalidateControl();
	SetModifiedFlag();
}

void CRListBoxCtrl::AddIconColumn(long width) 
{
	CList<char*,char*>* list=new CList<char*,char*>;
	m_list.AddTail(list);
	m_sizeList.AddTail(width);
	m_isPictureList.AddTail(TRUE);
	m_isRightAlignedList.AddTail(FALSE);
}

void CRListBoxCtrl::AddIcon(long filenum, short index) 
{
	int		lines, linesize, height ;
	CRect	rc ;
	if (m_HorizontalOption)
	{
		GetWindowRect(rc);
		lines = m_list.GetAt(m_list.FindIndex(index))->GetCount() ;
		linesize = (lines + 1) * textheight ;
		height = rc.Height() ;
		if (linesize > height * (m_NoRepeats + 1)) // allow for second and third+ rows on grid style system
		{
			AddSetOfColumns() ;
			m_Lines = lines ;
			m_NoRepeats++ ;	
		}
		m_list.GetAt(m_list.FindIndex(index + (m_NoRepeats*m_NoColumnsToRepeat)))->AddTail((char*)filenum);
	}
	else
		m_list.GetAt(m_list.FindIndex(index))->AddTail((char*)filenum);
	// remember to delete it
	UpdateScrollBar();
}

void CRListBoxCtrl::SetHorizontalOption(short columns) 
{
	//Code JW 04Nov98 	// New Woody code
	m_NoColumnsToRepeat = columns ;
	m_NoRepeats = 0 ; // default at start of columns
	m_HorizontalOption = TRUE ;
	SetModifiedFlag();
//	return m_HorizontalOption;
}

short CRListBoxCtrl::GetColFromX(long x) 
{
	//Code JW 04Nov98 	// Woody new code
	int		i ;
	CDC*	pdc;
	CFont*	pOldFont;
	long	currcolwidth ;

	pdc=GetDC();
	if (m_pFontPtr) 
		pOldFont = pdc->SelectObject(m_pFontPtr);
	else if (m_hWnd) 
		pOldFont = pdc->SelectObject((CFont*)GetParent()->SendMessage(WM_GETGLOBALFONT,m_FontNum2,NULL));
	else 
		pOldFont = pdc->GetCurrentFont();
	TEXTMETRIC tm;
	pdc->GetTextMetrics(&tm);
	POSITION position;
	position=m_sizeList.GetHeadPosition();
	currcolwidth = 0 ;
	for (i=0 ; i < m_sizeList.GetCount() ; i++)
	{
		currcolwidth += m_sizeList.GetNext(position) * tm.tmHeight / 16;
		if (x < currcolwidth) 
			break;
	}
	if (i < m_sizeList.GetCount())
		return i ; // column number
	else
		return 0 ;
}

long CRListBoxCtrl::GetRowColPlayerNum(long row, long col) 
{
	//Code JW 04Nov98 
	// Woods code
	if (!m_HorizontalOption)  
		return (GetPlayerNum(row)) ;
	else if (m_NoRepeats < 0)
		return (GetPlayerNum(row)) ;
	else // get player number from row column grid repeating system
	{
		POSITION	position;
		long		actualrow ;
		long		playerNumOld;
		actualrow = row + ((col / m_NoColumnsToRepeat) * m_Lines) ;
		position=m_playerList.FindIndex(actualrow);
		if (position == NULL)
			return(NULL) ;
		playerNumOld = m_playerList.GetAt(position);
		return playerNumOld;
	}
}

void CRListBoxCtrl::SetColumnRightAligned(long index, BOOL bNewVal) 
{
	m_isRightAlignedList.SetAt(m_isRightAlignedList.FindIndex(index),bNewVal);
}

void CRListBoxCtrl::SetRowColour(long row, long RGBcolour) 
{
	// TODO: Add your dispatch handler code here
	ASSERT (row<m_rowColourList.GetCount());
	m_rowColourList.SetAt(m_rowColourList.FindIndex(row),(COLORREF)RGBcolour);
}

BOOL CRListBoxCtrl::GetToggleResizableColumns() 
{
	return m_toggleresizeablecolumns;
}

void CRListBoxCtrl::SetToggleResizableColumns(BOOL bNewValue) 
{
	m_toggleresizeablecolumns=bNewValue;
	SetModifiedFlag();
}

short CRListBoxCtrl::GetScrlBarOffset() 
{
	return m_ScrlBarOffset;
}

void CRListBoxCtrl::SetScrlBarOffset(short nNewValue) 
{
	m_ScrlBarOffset = nNewValue ;
	SetModifiedFlag();
}

void CRListBoxCtrl::SetIcon(long filenum, short row, short column) 
{
	// TODO: Add your dispatch handler code here
	CList<char*,char*>* list=m_list.GetAt(m_list.FindIndex(column));
	POSITION position = list->FindIndex(row);
	ASSERT(position != NULL); // the cell does not exist
	list->SetAt(position,(char*)filenum);
	
	InvalidateControl();
}



OLE_COLOR CRListBoxCtrl::GetShadowSelectColour() 
{
	return m_ShadowselectColor;
//	return RGB(0,0,0);
}

void CRListBoxCtrl::SetShadowSelectColour(OLE_COLOR nNewValue) 
{
	m_ShadowselectColor = nNewValue;
	SetModifiedFlag();
}

OLE_COLOR CRListBoxCtrl::GetShadowLineColor() 
{
	return m_ShadowlineColor;
//	return RGB(0,0,0);
}

void CRListBoxCtrl::SetShadowLineColor(OLE_COLOR nNewValue) 
{
	m_ShadowlineColor = nNewValue;
	SetModifiedFlag();
}

BOOL CRListBoxCtrl::GetDrawBackgGound() 
{
	return m_isIcon;
}

void CRListBoxCtrl::SetDrawBackgGound(BOOL bNewValue) 
{
	if(bNewValue)
		m_isIcon = TRUE;
	else
		m_isIcon = FALSE;
	SetModifiedFlag();
}
