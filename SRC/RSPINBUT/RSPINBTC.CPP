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

// RSpinButCtl.cpp : Implementation of the CRSpinButCtrl ActiveX Control class.

#define F_COMMON
//DeadCode RDH 28Feb99 #define F_SOUNDS
#define F_BATTLE
#include "stdafx.h"
#include "RSpinBut.h"
#include "RSpinBtC.h"
#include "RSpinBtP.h"
#include "fileman.h"
#include "messages.h"
#include "axcolors.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CRSpinButCtrl, COleControl)
extern int GetShadow1XOffset(int fontheight);
extern int GetShadow1YOffset(int fontheight);
extern int GetShadow2XOffset(int fontheight);
extern int GetShadow2YOffset(int fontheight);
BOOL CRSpinButCtrl::m_bDrawing = FALSE;

/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CRSpinButCtrl, COleControl)
	//{{AFX_MSG_MAP(CRSpinButCtrl)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_CREATE()
	ON_WM_LBUTTONUP()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Dispatch map

BEGIN_DISPATCH_MAP(CRSpinButCtrl, COleControl)
	//{{AFX_DISPATCH_MAP(CRSpinButCtrl)
	DISP_PROPERTY_EX(CRSpinButCtrl, "RepeatDelay", GetRepeatDelay, SetRepeatDelay, VT_I4)
	DISP_PROPERTY_EX(CRSpinButCtrl, "index", GetIndex, SetIndex, VT_I4)
	DISP_PROPERTY_EX(CRSpinButCtrl, "FontNum", GetFontNum, SetFontNum, VT_I4)
	DISP_PROPERTY_EX(CRSpinButCtrl, "CurrentValue", GetCurrentValue, SetCurrentValue, VT_I4)
	DISP_FUNCTION(CRSpinButCtrl, "AddString", AddString, VT_EMPTY, VTS_BSTR)
	DISP_FUNCTION(CRSpinButCtrl, "DeleteString", DeleteString, VT_EMPTY, VTS_I4)
	DISP_FUNCTION(CRSpinButCtrl, "Clear", Clear, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION(CRSpinButCtrl, "SetPriceOption", SetPriceOption, VT_BOOL, VTS_I4 VTS_I4 VTS_I4)
	DISP_FUNCTION(CRSpinButCtrl, "SetValueOption", SetValueOption, VT_BOOL, VTS_I4 VTS_I4 VTS_I4)
	DISP_FUNCTION(CRSpinButCtrl, "SetPassWord", SetPassWord, VT_EMPTY, VTS_BOOL)
	DISP_FUNCTION(CRSpinButCtrl, "SetSearchValueOption", SetSearchValueOption, VT_BOOL, VTS_I4 VTS_I4 VTS_I4)
	DISP_FUNCTION(CRSpinButCtrl, "SetPlayerNegPriceOption", SetPlayerNegPriceOption, VT_BOOL, VTS_I4 VTS_I4 VTS_I4)
	DISP_STOCKPROP_FORECOLOR()
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()


/////////////////////////////////////////////////////////////////////////////
// Event map

BEGIN_EVENT_MAP(CRSpinButCtrl, COleControl)
	//{{AFX_EVENT_MAP(CRSpinButCtrl)
	EVENT_CUSTOM("TextChanged", FireTextChanged, VTS_BSTR)
	//}}AFX_EVENT_MAP
END_EVENT_MAP()


/////////////////////////////////////////////////////////////////////////////
// Property pages

// TODO: Add more property pages as needed.  Remember to increase the count!
BEGIN_PROPPAGEIDS(CRSpinButCtrl, 2)
	PROPPAGEID(CRSpinButPropPage::guid)
    PROPPAGEID(CLSID_CColorPropPage)
END_PROPPAGEIDS(CRSpinButCtrl)


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CRSpinButCtrl, "RSPINBUT.RSpinButCtrl.1",
	0xc3270e66, 0x6d6b, 0x11d1, 0xa1, 0xf0, 0x44, 0x45, 0x53, 0x54, 0, 0)


/////////////////////////////////////////////////////////////////////////////
// Type library ID and version

IMPLEMENT_OLETYPELIB(CRSpinButCtrl, _tlid, _wVerMajor, _wVerMinor)


/////////////////////////////////////////////////////////////////////////////
// Interface IDs

const IID BASED_CODE IID_DRSpinBut =
		{ 0xc3270e64, 0x6d6b, 0x11d1, { 0xa1, 0xf0, 0x44, 0x45, 0x53, 0x54, 0, 0 } };
const IID BASED_CODE IID_DRSpinButEvents =
		{ 0xc3270e65, 0x6d6b, 0x11d1, { 0xa1, 0xf0, 0x44, 0x45, 0x53, 0x54, 0, 0 } };


/////////////////////////////////////////////////////////////////////////////
// Control type information

static const DWORD BASED_CODE _dwRSpinButOleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CRSpinButCtrl, IDS_RSPINBUT, _dwRSpinButOleMisc)


/////////////////////////////////////////////////////////////////////////////
// CRSpinButCtrl::CRSpinButCtrlFactory::UpdateRegistry -
// Adds or removes system registry entries for CRSpinButCtrl

BOOL CRSpinButCtrl::CRSpinButCtrlFactory::UpdateRegistry(BOOL bRegister)
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
			IDS_RSPINBUT,
			IDB_RSPINBUT,
			afxRegApartmentThreading,
			_dwRSpinButOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}


/////////////////////////////////////////////////////////////////////////////
// Licensing strings

static const TCHAR BASED_CODE _szLicFileName[] = _T("RSpinBut.lic");

static const WCHAR BASED_CODE _szLicString[] =
	L"Copyright (c) 1997 RowanSoftware";


/////////////////////////////////////////////////////////////////////////////
// CRSpinButCtrl::CRSpinButCtrlFactory::VerifyUserLicense -
// Checks for existence of a user license

BOOL CRSpinButCtrl::CRSpinButCtrlFactory::VerifyUserLicense()
{
	return AfxVerifyLicFile(AfxGetInstanceHandle(), _szLicFileName,
		_szLicString);
}


/////////////////////////////////////////////////////////////////////////////
// CRSpinButCtrl::CRSpinButCtrlFactory::GetLicenseKey -
// Returns a runtime licensing key

BOOL CRSpinButCtrl::CRSpinButCtrlFactory::GetLicenseKey(DWORD dwReserved,
	BSTR FAR* pbstrKey)
{
	if (pbstrKey == NULL)
		return FALSE;

	*pbstrKey = SysAllocString(_szLicString);
	return (*pbstrKey != NULL);
}


/////////////////////////////////////////////////////////////////////////////
// CRSpinButCtrl::CRSpinButCtrl - Constructor

CRSpinButCtrl::CRSpinButCtrl()
{
	InitializeIIDs(&IID_DRSpinBut, &IID_DRSpinButEvents);
	m_bLButtonDown=FALSE;
	m_bDrawing=FALSE;
	m_index=0;
 	m_SpinState = STATE_NORMAL; // JW 01Dec98					//MS 01Apr99
 	m_Min = 0;													//MS 01Apr99
	m_Max = 10000000 ;											//MS 01Apr99
	m_CurrentValue = 0 ;										//MS 01Apr99
	m_Delta = 1 ;												//MS 01Apr99
	m_password = FALSE;											//MS 01Apr99
	m_visible  = TRUE;											//MS 01Apr99
}


/////////////////////////////////////////////////////////////////////////////
// CRSpinButCtrl::~CRSpinButCtrl - Destructor

CRSpinButCtrl::~CRSpinButCtrl()
{
	Clear();
}


/////////////////////////////////////////////////////////////////////////////
// CRSpinButCtrl::OnDraw - Drawing function

char*	CRSpinButCtrl::GetCurrentText(char* currtext)
{
	if (m_SpinState == STATE_NORMAL)							//MS 01Apr99
	{
		ASSERT(m_list.GetCount()); // have at least one entry!
		char	tempst[255] ;
		strcpy(tempst, m_list.GetAt(m_list.FindIndex(m_index))) ;
		StringToPassWord(tempst, currtext);
	}	
	else if (m_SpinState == STATE_PRICE ||						//MS 01Apr99
			m_SpinState == STATE_PLAYERNEG)	//JW 01Dec98
	{	
		char	tempst[255] ;
		ValueToMoneyString(m_CurrentValue, tempst) ;
		StringToPassWord(tempst, currtext);
	}
	else if(m_SpinState == STATE_SEARCHVALUE)					//MS 01Apr99
	{
		char	tempst[255] ;
		if(m_CurrentValue > 10000000)//10,000,000
		{
			strcpy(tempst,"Any Value");
			StringToPassWord(tempst, currtext);
		}
		else
		{
			ValueToMoneyString(m_CurrentValue, tempst) ;
			StringToPassWord(tempst, currtext);
		}
	}
	else //STATE_VALUE											//MS 01Apr99
	{
		char	tempst[255] ;
		_itoa(m_CurrentValue, tempst, 10) ;
		StringToPassWord(tempst, currtext);
	}
	return (currtext) ;
}

void CRSpinButCtrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
{
	if (m_bDrawing || !m_hWnd) return;
	m_bDrawing=TRUE;
	CRect rc = rcBounds;
	CWnd* parent;
	long offsetx;
	long offsety;
	long offsets;
    CFont* pOldFont;
	FileNum artnum=FIL_NULL;
	parent=GetParent();
	offsets=parent->SendMessage(WM_GETXYOFFSET,NULL,NULL);
	CRect rect;
	GetWindowRect(rect);
	CRect parentrect;
	parent->GetWindowRect(parentrect);
	offsetx=short(offsets & 0x0000FFFF)+parentrect.left-rect.left;
	offsety=short((offsets & 0xFFFF0000)>>16)+parentrect.top-rect.top;
	artnum = (FileNum)parent->SendMessage(WM_GETARTWORK,NULL,NULL);
	if (artnum)
		DrawBitmap(artnum,pdc,offsetx,offsety);
	else
		pdc->FillRect(rcBounds, CBrush::FromHandle((HBRUSH)GetStockObject(BLACK_BRUSH)));
	// draw the text
    pdc->SetBkMode(TRANSPARENT);
    pdc->SetTextAlign(TA_LEFT | TA_TOP);

	if (m_hWnd) 
		pOldFont = pdc->SelectObject((CFont*)this->GetParent()->SendMessage(WM_GETGLOBALFONT,abs(m_FontNum),NULL));
	else 
		pOldFont = pdc->GetCurrentFont();

	char text[255] ;
	GetCurrentText(text) ;

	TEXTMETRIC tm;
	pdc->GetTextMetrics(&tm);
	if (m_FontNum<0)
	{
		pdc->SetTextColor(RGB(0,0,0));
		int shadowx=GetShadow1XOffset(tm.tmHeight);
		int shadowy=GetShadow1YOffset(tm.tmHeight);
	    pdc->ExtTextOut(3+shadowx, 2+shadowy,
			ETO_CLIPPED, CRect(rc.left,rc.top,rc.right-17,rc.bottom), text, strlen(text), NULL);
		shadowx=GetShadow2XOffset(tm.tmHeight);
		shadowy=GetShadow2YOffset(tm.tmHeight);
	    pdc->ExtTextOut(3+shadowx, 2+shadowy,
			ETO_CLIPPED, CRect(rc.left,rc.top,rc.right-17,rc.bottom), text, strlen(text), NULL);
	}
    pdc->SetTextColor(TranslateColor(GetForeColor()));
    pdc->ExtTextOut(3, 2,
		ETO_CLIPPED, CRect(rc.left,rc.top,rc.right-17,rc.bottom), text, strlen(text), NULL);
	// draw the arrows
	if (m_hWnd)
	{
		DrawTransparentBitmap(FIL_SPIN_UP,pdc,rcBounds.right-16,(rcBounds.Height()/2)-11);
		DrawTransparentBitmap(FIL_SPIN_DOWN,pdc,rcBounds.right-16,(rcBounds.Height()/2));
	}
	CPen BlackPen,WhitePen;
	if (IsWindowEnabled())
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
	oldpen=pdc->SelectObject(&WhitePen);
	pdc->MoveTo(rcBounds.right-1,rcBounds.top);
	pdc->LineTo(rcBounds.right-1,rcBounds.bottom-1);
	pdc->LineTo(rcBounds.left,rcBounds.bottom-1);
	pdc->SelectObject(&BlackPen);
	pdc->LineTo(rcBounds.left,rcBounds.top);
	pdc->LineTo(rcBounds.right-1,rcBounds.top);
	pdc->SelectObject(oldpen);
    pdc->SelectObject(pOldFont);
}

void CRSpinButCtrl::DrawBitmap(FileNum filenum,CDC* pdc,int x,int y)
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
		SetDIBitsToDevice(pdc->m_hDC,x,y,pInfo->bmiHeader.biWidth, pInfo->bmiHeader.biHeight,
			0,0,0,pInfo->bmiHeader.biHeight,pData,pInfo,DIB_RGB_COLORS);
	}
	parent->SendMessage(WM_RELEASELASTFILE,NULL,NULL);
	m_bDrawing=FALSE;
}

void CRSpinButCtrl::DrawTransparentBitmap(FileNum filenum,CDC * pDC, int x, int y)
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

/////////////////////////////////////////////////////////////////////////////
// CRSpinButCtrl::DoPropExchange - Persistence support

void CRSpinButCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);
	PX_Long(pPX, "RepeatDelay",m_RepeatDelay);
	PX_Long(pPX, "FontNum",m_FontNum);
}


/////////////////////////////////////////////////////////////////////////////
// CRSpinButCtrl::OnResetState - Reset control to default state

void CRSpinButCtrl::OnResetState()
{
	COleControl::OnResetState();  // Resets defaults found in DoPropExchange
	m_RepeatDelay=100;
}


/////////////////////////////////////////////////////////////////////////////
// CRSpinButCtrl message handlers

void CRSpinButCtrl::OnLButtonDown(UINT nFlags, CPoint point) 
{
	COleControl::OnLButtonDown(nFlags, point);
	CRect rect;
	this->GetClientRect(rect);
	if (point.x<rect.right-15) return;
	m_bLButtonDown=TRUE;
	this->SetCapture();
	m_visible = TRUE;
	m_timerid=SetTimer(8374,m_RepeatDelay,NULL);
	if (point.y<rect.bottom/2)
	{
		m_bGoingDown=FALSE;
	}
	else
	{
		m_bGoingDown=TRUE;
	}
	OnTimer(m_timerid);
}

void CRSpinButCtrl::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	// disable double clicking
	OnLButtonDown(nFlags,point);
}

int CRSpinButCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (COleControl::OnCreate(lpCreateStruct) == -1)
		return -1;
	return 0;
}

void CRSpinButCtrl::OnLButtonUp(UINT nFlags, CPoint point) 
{
	if (m_bLButtonDown==TRUE)
	{
		m_bLButtonDown=FALSE;
		this->KillTimer(m_timerid);
		if(m_password == TRUE)
		{
			for(int i=0;i<=10000;i++)
			{
				for(int a=0;a<=1000;a++)
				{
				//delay
				}
			}
			m_visible = FALSE;
			this->ReleaseCapture();
			InvalidateControl();
		
		}
		else
		{
			this->ReleaseCapture();
		}
	}
	COleControl::OnLButtonUp(nFlags, point);
}

long CRSpinButCtrl::GetRepeatDelay() 
{
	return m_RepeatDelay;
}

void CRSpinButCtrl::SetRepeatDelay(long nNewValue) 
{
	m_RepeatDelay=nNewValue;
	SetModifiedFlag();
}

void CRSpinButCtrl::OnTimer(UINT nIDEvent) 
{
	if (nIDEvent==m_timerid)
	{

		if (m_SpinState == STATE_NORMAL)
		{
			CWnd* parent;
			parent=GetParent();

//DeadCode RDH 28Feb99 		if (m_bGoingDown)
//DeadCode RDH 28Feb99 		{
//DeadCode RDH 28Feb99 			m_index--;
//DeadCode RDH 28Feb99 			if (m_index<0)
//DeadCode RDH 28Feb99 				m_index=0;
//DeadCode RDH 28Feb99 		}
//DeadCode RDH 28Feb99 		else
//DeadCode RDH 28Feb99 		{
//DeadCode RDH 28Feb99 			m_index++;
//DeadCode RDH 28Feb99 			if (m_index>=m_list.GetCount())
//DeadCode RDH 28Feb99 				m_index=m_list.GetCount()-1;
//DeadCode RDH 28Feb99 		}
			if (m_bGoingDown)
			{
				if (m_index >= 1)
				{
					m_index--;
					parent->SendMessage(WM_PLAYSOUND,FIL_SFX_OFFICE_KEYPRESS1,NULL);//RDH 12Apr99
				}else
					parent->SendMessage(WM_PLAYSOUND,FIL_SFX_OFFICE_BOOKCLOSE1,NULL);//RDH 12Apr99
			}
			else
			{
				if (m_index<=(m_list.GetCount()-2))
				{
					m_index++;
					parent->SendMessage(WM_PLAYSOUND,FIL_SFX_OFFICE_KEYPRESS1,NULL);//RDH 12Apr99
				}else
					parent->SendMessage(WM_PLAYSOUND,FIL_SFX_OFFICE_BOOKCLOSE1,NULL);//RDH 12Apr99
			
			}
		}
		else if(	m_SpinState == STATE_PRICE 
				||
				 	m_SpinState == STATE_VALUE 
				||
				 	m_SpinState == STATE_PLAYERNEG)
		{
//Old_Code MS 01Apr99 			if(		m_SpinState == STATE_PRICE 
//Old_Code MS 01Apr99 				||
//Old_Code MS 01Apr99 					m_SpinState == STATE_PLAYERNEG)
//Old_Code MS 01Apr99 				ResetStepSize() ;
			if (m_bGoingDown)
			{
				m_CurrentValue -= m_Delta ;
				if (m_CurrentValue < m_Min)
					m_CurrentValue = m_Min;
			}
			else
			{
				m_CurrentValue += m_Delta ;
				if (m_CurrentValue > m_Max)
					m_CurrentValue = m_Max ;
			}//NewCode JW 01Dec98
			if(		m_SpinState == STATE_PRICE 
				||
					m_SpinState == STATE_PLAYERNEG)
				ResetStepSize() ;
		}
		else if(m_SpinState == STATE_SEARCHVALUE)
		{
			FindSearchValue();
		}
		InvalidateControl();
		char st[255] ;
		FireTextChanged(GetCurrentText(st));
	}
	else
		COleControl::OnTimer(nIDEvent);
}

long CRSpinButCtrl::GetIndex() 
{
	return m_index;
}

void CRSpinButCtrl::SetIndex(long nNewValue) 
{
	m_index=nNewValue;
	ASSERT(m_index<m_list.GetCount()); // index is out of bounds
	InvalidateControl();
	SetModifiedFlag();
}

void CRSpinButCtrl::AddString(LPCTSTR text) 
{
	char* buffer=new char[strlen(text)+1]; // include terminating null character
	strcpy(buffer,text);
	m_list.AddTail(buffer);
}

void CRSpinButCtrl::DeleteString(long index) 
{
	POSITION position;
	position=m_list.FindIndex(index);
	delete [] m_list.GetAt(position);
	m_list.RemoveAt(position);
	if (m_index>index) m_index--;
	InvalidateControl();
}

void CRSpinButCtrl::Clear() 
{
	int count=m_list.GetCount();
	POSITION position=m_list.GetHeadPosition();
	for (int i=0;i<count;i++)
	{
		 delete [] m_list.GetNext(position);
	}
	m_list.RemoveAll();
	m_index=0;
}

long CRSpinButCtrl::GetFontNum() 
{
	return m_FontNum;
}

void CRSpinButCtrl::SetFontNum(long nNewValue) 
{
	m_FontNum=nNewValue;
	InvalidateControl();
	SetModifiedFlag();
}

BOOL CRSpinButCtrl::SetPriceOption(long min, long max, long current) //NewCode JW 01Dec98 	
{	
	m_SpinState = STATE_PRICE ;
	m_Min = min ;
	m_Max = max ;
	m_CurrentValue = current ;
	ResetStepSize() ;
	InvalidateControl();
	SetModifiedFlag();
	return TRUE;
}

BOOL CRSpinButCtrl::SetValueOption(long min, long max, long current) //NewCode JW 01Dec98 	
{
	m_SpinState = STATE_VALUE ;
	m_Min = min ;
	m_Max = max ;
	m_CurrentValue = current ;
	m_Delta = 1 ;
	ResetStepSize() ;
	InvalidateControl();
	SetModifiedFlag();
	return TRUE;
}

BOOL CRSpinButCtrl::SetSearchValueOption(long min, long max, long current) //NewCode JW 01Dec98 	
{
	m_SpinState = STATE_SEARCHVALUE ;
	m_Min = min ;
	m_Max = max ;
	m_CurrentValue = current ;
	InvalidateControl();
	SetModifiedFlag();
	return TRUE;
}

BOOL CRSpinButCtrl::SetPlayerNegPriceOption(long min, long max, long current) 
{
	// TODO: Add your dispatch handler code here
	m_SpinState = STATE_PLAYERNEG ;
	m_Min = min ;
	m_Max = max ;
	m_CurrentValue = current ;
	m_Delta = 1 ;
	ResetStepSize() ;
	InvalidateControl();
	SetModifiedFlag();
	return TRUE;
}

long CRSpinButCtrl::GetCurrentValue() 
{
	//NewCode JW 01Dec98 	// TODO: Add your property handler here	
	return m_CurrentValue ;
}

void CRSpinButCtrl::SetCurrentValue(long nNewValue) 
{
	//NewCode JW 01Dec98 
	m_CurrentValue = nNewValue ;
	InvalidateControl();
	SetModifiedFlag();
}

void CRSpinButCtrl::ResetStepSize() //NewCode JW 01Dec98 	
{
	// delta wants to be steps a tenth of current value
	if(m_SpinState == STATE_PLAYERNEG)
	{
		if(m_bGoingDown)
		{
			if (m_CurrentValue <= 100)
				m_Delta =  10;
			else if (m_CurrentValue <= 1000) //1,000
				m_Delta = 100 ;
			else if (m_CurrentValue <= 10000) //10,000
				m_Delta = 1000 ;
			else if (m_CurrentValue <= 100000) //100,000
				m_Delta = 5000 ;
			else if (m_CurrentValue <= 250000) //250,000
				m_Delta = 10000 ;
			else if (m_CurrentValue <= 1000000) //1,000,000
				m_Delta = 25000 ;
			else if (m_CurrentValue <= 5000000) //5,000,000
				m_Delta = 100000 ;
			else if (m_CurrentValue <= 10000000) //10,000,000
				m_Delta = 250000 ;	
			else if (m_CurrentValue <= 20000000) //20,000,000
				m_Delta = 500000 ;
			else if (m_CurrentValue <= 50000000) //50,000,000
				m_Delta = 1000000 ;		
		}
		else
		{
			if (m_CurrentValue < 100)
				m_Delta =  10;
			else if (m_CurrentValue < 1000) //1,000
				m_Delta = 100 ;
			else if (m_CurrentValue < 10000) //10,000
				m_Delta = 1000 ;
			else if (m_CurrentValue < 100000) //100,000
				m_Delta = 5000 ;
			else if (m_CurrentValue < 250000) //250,000
				m_Delta = 10000 ;
			else if (m_CurrentValue < 1000000) //1,000,000
				m_Delta = 25000 ;
			else if (m_CurrentValue < 5000000) //5,000,000
				m_Delta = 100000 ;
			else if (m_CurrentValue < 10000000) //10,000,000
				m_Delta = 250000 ;	
			else if (m_CurrentValue < 20000000) //20,000,000
				m_Delta = 500000 ;
			else if (m_CurrentValue < 50000000) //50,000,000
				m_Delta = 1000000 ;		
		}
	}
	else
	{
		if(m_bGoingDown)
		{
			if (m_CurrentValue <= 100)
				m_Delta = 1 ;
			else if (m_CurrentValue <= 1000) //1,000
				m_Delta = 10 ;
			else if (m_CurrentValue <= 10000) //10,000
				m_Delta = 100 ;
			else if (m_CurrentValue <= 1000000) //1,000000
				m_Delta = 1000 ;
			else if (m_CurrentValue <= 10000000) // 10,000,000
				m_Delta = 10000 ;
			else if (m_CurrentValue <= 100000000)  // 100,000,000
				m_Delta = 100000 ; //(100,000)
			else 
				m_Delta = 1000000 ; //(1,000,000)
		}
		else
		{
			if (m_CurrentValue < 100)
				m_Delta = 1 ;
			else if (m_CurrentValue < 1000) //1,000
				m_Delta = 10 ;
			else if (m_CurrentValue < 10000) //10,000
				m_Delta = 100 ;
			else if (m_CurrentValue < 1000000) //1,000000
				m_Delta = 1000 ;
			else if (m_CurrentValue < 10000000) // 10,000,000
				m_Delta = 10000 ;
			else if (m_CurrentValue < 100000000)  // 100,000,000
				m_Delta = 100000 ; //(100,000)
			else 
				m_Delta = 1000000 ; //(1,000,000)
		}
	}
}

void	CRSpinButCtrl::ValueToMoneyString(long	value, char*	buffer) //NewCode JW 01Dec98 	
{
	char	st[50] ;
	if (value < 1000) // standard amount
	{
		strcpy(buffer, "£ ") ;
		_itoa(value, st, 10 );
		strcat(buffer,st) ;
	}
	else if (value < 1000000) //K
	{
		strcpy(buffer, "£ ") ;
		_itoa(value / 1000, st, 10 );
		strcat(buffer,st) ;
		if (value % 1000 > 0)
		{
			strcat(buffer,".") ;
			_itoa(value % 1000, st, 10 );
			strcat(buffer,st) ;
			StrTrimZeros(buffer) ;
		}
		strcat(buffer, "K");
	}
	else // M
	{
		strcpy(buffer, "£ ") ;
		_itoa(value / 1000000, st, 10 );
		strcat(buffer,st) ;
		if (value % 1000000 > 0)
		{
			strcat(buffer,".") ;
			_itoa(value % 1000000, st, 10 );
			strcat(buffer,st) ;
			StrTrimZeros(buffer) ;
		}
		strcat(buffer, "M");
	}
}

char*	CRSpinButCtrl::StrEnd (char*	st ) //NewCode JW 01Dec98 	
{
	while (*st != 0)
		st++ ;
	return(st) ;
}

char*	CRSpinButCtrl::StrTrimZeros(char* startbuffer) //NewCode JW 01Dec98 	
{
	char*	start = startbuffer ;
	char*	st ;

	st = StrEnd(start) ;
	if (st == start)
		return start ;
	st-- ;
	while(*st == '0')
	{
		*st = 0 ;
		st-- ;
	}
	return(start) ;
}

void CRSpinButCtrl::SetPassWord(BOOL ispassword) 
{
	// TODO: Add your dispatch handler code here
	m_password = static_cast<Bool>(ispassword);
	if(m_password == TRUE)
	{
		m_visible = FALSE;
	}
	else
	{
		m_visible = TRUE;
	}
}

void	CRSpinButCtrl::StringToPassWord(char* String, char*	buffer)
{
	if(m_visible == FALSE)
	{
		strcpy(buffer,"£££££");
	}
	else
	{
		strcpy(buffer,String);
	}
}

void	CRSpinButCtrl::FindSearchValue()
{
	if (m_bGoingDown)
	{
		if(m_CurrentValue > 50000000)
			m_CurrentValue = 50000000;
		else if(m_CurrentValue > 10000000)
			m_CurrentValue = 10000000;
		else if(m_CurrentValue > 5000000)
			m_CurrentValue = 5000000;
		else if(m_CurrentValue > 2000000)
			m_CurrentValue = 2000000;
		else if(m_CurrentValue > 1000000)
			m_CurrentValue = 1000000;
		else if(m_CurrentValue > 500000)
			m_CurrentValue = 500000;
		else if(m_CurrentValue > 250000)
			m_CurrentValue = 250000;
		else if(m_CurrentValue > 100000)
			m_CurrentValue = 100000;
		else if(m_CurrentValue > 50000)
			m_CurrentValue = 50000;
		else if(m_CurrentValue > 25000)
			m_CurrentValue = 25000;
		else if(m_CurrentValue > 0)
			m_CurrentValue = 0;
		
		if (m_CurrentValue < m_Min)
			m_CurrentValue = m_Min ;
	
	}
	else
	{
		if(m_CurrentValue < 25000)
			m_CurrentValue = 25000;
		else if(m_CurrentValue < 50000)
			m_CurrentValue = 50000;
		else if(m_CurrentValue < 100000)
			m_CurrentValue = 100000;
		else if(m_CurrentValue < 250000)
			m_CurrentValue = 250000;
		else if(m_CurrentValue < 500000)
			m_CurrentValue = 500000;
		else if(m_CurrentValue < 1000000)
			m_CurrentValue = 1000000;
		else if(m_CurrentValue < 2000000)
			m_CurrentValue = 2000000;
		else if(m_CurrentValue < 5000000)
			m_CurrentValue = 5000000;
		else if(m_CurrentValue < 10000000)
			m_CurrentValue = 10000000;
		else if(m_CurrentValue < 50000000)
			m_CurrentValue = 50000000;
		if (m_CurrentValue > m_Max)
			m_CurrentValue = m_Max ;	
	}
}
