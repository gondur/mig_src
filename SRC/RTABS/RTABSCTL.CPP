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

	// RTabsCtl.cpp : Implementation of the CRTabsCtrl ActiveX Control class.

#define F_BATTLE

#include "stdafx.h"
#include "RTabs.h"
#include "RTabsCtl.h"
#include "RTabsPpg.h"
#include "messages.h"
#include "FileMan.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CRTabsCtrl, COleControl)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CRTabsCtrl, COleControl)
	//{{AFX_MSG_MAP(CRTabsCtrl)
	ON_WM_LBUTTONDOWN()
	ON_WM_SIZE()
	ON_WM_SHOWWINDOW()
	//}}AFX_MSG_MAP
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Dispatch map

BEGIN_DISPATCH_MAP(CRTabsCtrl, COleControl)
	//{{AFX_DISPATCH_MAP(CRTabsCtrl)
	DISP_PROPERTY_EX(CRTabsCtrl, "FirstTab", GetFirstTab, SetFirstTab, VT_I4)
	DISP_PROPERTY_EX(CRTabsCtrl, "HorzAlign", GetHorzAlign, SetHorzAlign, VT_BOOL)
	DISP_PROPERTY_EX(CRTabsCtrl, "FontNum", GetFontNum, SetFontNum, VT_I4)
	DISP_FUNCTION(CRTabsCtrl, "AddTab", AddTab, VT_EMPTY, VTS_BSTR VTS_I4)
	DISP_FUNCTION(CRTabsCtrl, "Clear", Clear, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION(CRTabsCtrl, "CalculateHeight", CalculateHeight, VT_I4, VTS_I4)
	DISP_FUNCTION(CRTabsCtrl, "CalcWidestWord", CalcWidestWord, VT_I4, VTS_NONE)
	DISP_FUNCTION(CRTabsCtrl, "SelectTab", SelectTab, VT_I4, VTS_I4)
	DISP_STOCKPROP_FORECOLOR()
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()


/////////////////////////////////////////////////////////////////////////////
// Event map

BEGIN_EVENT_MAP(CRTabsCtrl, COleControl)
	//{{AFX_EVENT_MAP(CRTabsCtrl)
	EVENT_CUSTOM("SelectTab", FireSelectTab, VTS_I4)
	//}}AFX_EVENT_MAP
END_EVENT_MAP()


/////////////////////////////////////////////////////////////////////////////
// Property pages

// TODO: Add more property pages as needed.  Remember to increase the count!
BEGIN_PROPPAGEIDS(CRTabsCtrl, 1)
	PROPPAGEID(CRTabsPropPage::guid)
END_PROPPAGEIDS(CRTabsCtrl)


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CRTabsCtrl, "RTABS.RTabsCtrl.1",
	0x4a1e1986, 0x8b31, 0x11d1, 0xa1, 0xf0, 0x44, 0x45, 0x53, 0x54, 0, 0)


/////////////////////////////////////////////////////////////////////////////
// Type library ID and version

IMPLEMENT_OLETYPELIB(CRTabsCtrl, _tlid, _wVerMajor, _wVerMinor)


/////////////////////////////////////////////////////////////////////////////
// Interface IDs

const IID BASED_CODE IID_DRTabs =
		{ 0x4a1e1984, 0x8b31, 0x11d1, { 0xa1, 0xf0, 0x44, 0x45, 0x53, 0x54, 0, 0 } };
const IID BASED_CODE IID_DRTabsEvents =
		{ 0x4a1e1985, 0x8b31, 0x11d1, { 0xa1, 0xf0, 0x44, 0x45, 0x53, 0x54, 0, 0 } };


/////////////////////////////////////////////////////////////////////////////
// Control type information

static const DWORD BASED_CODE _dwRTabsOleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CRTabsCtrl, IDS_RTABS, _dwRTabsOleMisc)


/////////////////////////////////////////////////////////////////////////////
// CRTabsCtrl::CRTabsCtrlFactory::UpdateRegistry -
// Adds or removes system registry entries for CRTabsCtrl

BOOL CRTabsCtrl::CRTabsCtrlFactory::UpdateRegistry(BOOL bRegister)
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
			IDS_RTABS,
			IDB_RTABS,
			afxRegApartmentThreading,
			_dwRTabsOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}


/////////////////////////////////////////////////////////////////////////////
// Licensing strings

static const TCHAR BASED_CODE _szLicFileName[] = _T("RTabs.lic");

static const WCHAR BASED_CODE _szLicString[] =
	L"Copyright (c) 1998 RowanSoftware";


/////////////////////////////////////////////////////////////////////////////
// CRTabsCtrl::CRTabsCtrlFactory::VerifyUserLicense -
// Checks for existence of a user license

BOOL CRTabsCtrl::CRTabsCtrlFactory::VerifyUserLicense()
{
	return AfxVerifyLicFile(AfxGetInstanceHandle(), _szLicFileName,
		_szLicString);
}


/////////////////////////////////////////////////////////////////////////////
// CRTabsCtrl::CRTabsCtrlFactory::GetLicenseKey -
// Returns a runtime licensing key

BOOL CRTabsCtrl::CRTabsCtrlFactory::GetLicenseKey(DWORD dwReserved,
	BSTR FAR* pbstrKey)
{
	if (pbstrKey == NULL)
		return FALSE;

	*pbstrKey = SysAllocString(_szLicString);
	return (*pbstrKey != NULL);
}


/////////////////////////////////////////////////////////////////////////////
// CRTabsCtrl::CRTabsCtrl - Constructor

CRTabsCtrl::CRTabsCtrl()
{
	InitializeIIDs(&IID_DRTabs, &IID_DRTabsEvents);
	m_iCurrentSelection=0;
	m_firstTab=NULL;
//	m_hLowTabIcon=(HICON)LoadImage(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDI_TAB),IMAGE_ICON,400,32,LR_DEFAULTCOLOR);
//	m_hHighTabIcon=(HICON)LoadImage(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDI_TAB),IMAGE_ICON,400,30,LR_DEFAULTCOLOR);
//	m_hLowContinueIcon=(HICON)LoadImage(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDI_TAB),IMAGE_ICON,400,33,LR_DEFAULTCOLOR);
//	m_hHighContinueIcon=(HICON)LoadImage(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDI_TAB),IMAGE_ICON,400,31,LR_DEFAULTCOLOR);
//	m_TabUp.LoadBitmap(IDB_TABUP);
//	m_TabDown.LoadBitmap(IDB_TABDOWN);
	ASSERT(m_hLowTabIcon!=NULL && m_hHighTabIcon!=NULL);
	m_bHorzAlign=FALSE;
	m_bInit=TRUE;
	m_FontNum=0;
}


/////////////////////////////////////////////////////////////////////////////
// CRTabsCtrl::~CRTabsCtrl - Destructor

CRTabsCtrl::~CRTabsCtrl()
{
	Clear();
}


/////////////////////////////////////////////////////////////////////////////
// CRTabsCtrl::OnDraw - Drawing function

//CDC* gdc=NULL;
//CBitmap* gbm=NULL;

void CRTabsCtrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
{
	if (m_bInit)
	{
		m_TabUpDC.CreateCompatibleDC(pdc);
		m_TabDownDC.CreateCompatibleDC(pdc);
		m_TabUp.LoadBitmap(IDB_TABUP);
		m_TabDown.LoadBitmap(IDB_TABDOWN);	
		m_TabUpDC.SelectObject(m_TabUp);
		m_TabDownDC.SelectObject(m_TabDown);
		BITMAP bitmap;
		m_TabUp.GetBitmap(&bitmap);
		m_TabUpWidth=bitmap.bmWidth;
		m_TabUpHeight=bitmap.bmHeight;
		m_TabDown.GetBitmap(&bitmap);
		m_TabDownWidth=bitmap.bmWidth;
		m_TabDownHeight=bitmap.bmHeight;
		m_bInit=FALSE;		   
	}
	int count=m_textList.GetCount();
	if (count==0) return;
//	*(char*)0=0;
	// TODO: Replace the following code with your own drawing code.
	CDC offscreenDC;
	VERIFY(offscreenDC.CreateCompatibleDC(pdc));
	CBitmap bitmap;
	CBitmap* pOldBitmap;
	VERIFY(bitmap.CreateCompatibleBitmap(pdc,rcBounds.Width(),rcBounds.Height()));
	pOldBitmap=offscreenDC.SelectObject(&bitmap);
//	offscreenDC.FillRect(rcBounds, CBrush::FromHandle((HBRUSH)GetStockObject(BLACK_BRUSH)));
	// pre calculate the tab positions
	POSITION position = m_textList.GetHeadPosition();
	CRect rect;
	this->GetParent()->GetClientRect(rect);
	m_rectList.RemoveAll();
	m_tabList.RemoveAll();
	char* text;
    offscreenDC.SetTextAlign(TA_LEFT | TA_TOP);
    offscreenDC.SetBkMode(TRANSPARENT);
    offscreenDC.SetTextColor(TranslateColor(GetForeColor()));
    CFont* pOldFont;
	if (m_hWnd) pOldFont = offscreenDC.SelectObject((CFont*)this->GetParent()->SendMessage(WM_GETGLOBALFONT,m_FontNum,NULL));
	else pOldFont = offscreenDC.GetCurrentFont();
	int width;
	int start=0;
	if (m_bHorzAlign)
	{
		int finish;
		float seperation;
		int total=0;
		int laststart;
		int lastfinish;
		float lastseperation;
		BOOL lastrow=FALSE;
		BOOL notreallylastrow=FALSE;
		int row=0;
		for (int x=0;x<count;x++)
		{
			if (x==m_iCurrentSelection) lastrow=TRUE;
			text=m_textList.GetNext(position);
			width=offscreenDC.GetTextExtent(text).cx+15; // 15 is minimum seperation between text
			total+=width;
			if (total>rect.Width() || x==count-1)
			{
				// decide whether to put this tab on the next row...
				// doesnt happen if it is the only tab on the row
				if (x>start && total>rect.Width()) //|| (x-start)<3))
				{
//					finish=x-1;
//					total-=width;
					if (x==m_iCurrentSelection) notreallylastrow=TRUE;
					x--;
					if (position==NULL) position=m_textList.GetTailPosition();
					else m_textList.GetPrev(position);
					total-=width;
				}
//				else finish=x;
				finish=x;
				seperation=(float)(rect.Width()-total+(15*(finish-start+1)))/(float)(finish-start+1);
				if (lastrow==FALSE || notreallylastrow==TRUE)
					{
					DrawRow(seperation,start,finish,&offscreenDC,row,rect.Width(),FALSE);
					notreallylastrow=FALSE;
					}
				else
				{
					laststart=start;
					lastfinish=finish;
					lastseperation=seperation;
					lastrow=FALSE;
					row--;
				}
				total=0;
				start=x+1;
				row++;
			}
		}
		DrawRow(lastseperation,laststart,lastfinish,&offscreenDC,row,rect.Width(),TRUE);
	}
	else
	{
		// Draw vertical tabs.
		long widest;
		widest=CalcWidestWord();
		CRect rect2;
		this->GetClientRect(rect2);
//		widest=rect2.Width();
//		TRACE1("Measured Width: %d\n",widest);
		int y=0;
		char word[30];
		int startpos;
		BOOL NewTab;
		int oldy;
		int starty;
		for (int z=0;z<count;z++)
		{
			NewTab=TRUE;
			text=m_textList.GetNext(position);
			// split into component words
			start=0;
			startpos=2;
			starty=y;
			for (int x=0;x<(int)strlen(text)+1;x++) // includes terminating null character
			{
				if (text[x]==' ' || text[x]==NULL)
				{
					strncpy(word,text+start,min(x-start+1,30));
					word[min(x-start+1,30)]=NULL;
					start=x+1;
					width=offscreenDC.GetTextExtent(word).cx;
					if (NewTab)
					{
						if (z==m_iCurrentSelection)
						{
							DrawIconEx(offscreenDC.m_hDC,widest-400,y+2,m_hHighTabIcon,400,30,NULL,NULL,DI_NORMAL);
							offscreenDC.MoveTo(0,y);
							offscreenDC.LineTo(widest-15,y);
							offscreenDC.MoveTo(0,y+1);
							offscreenDC.LineTo(widest-10,y+1);
						}
						else DrawIconEx(offscreenDC.m_hDC,widest-402,y+2,m_hLowTabIcon,400,30,NULL,NULL,DI_NORMAL);
					}
					else
					{
						if (width+startpos>widest-15)
						{
							// Draw it at start of next line
							y+=30;
							startpos=2;
						}
						if (y!=oldy)
						{
							if (z==m_iCurrentSelection) DrawIconEx(offscreenDC.m_hDC,widest-400,y+2,m_hHighContinueIcon,400,30,NULL,NULL,DI_NORMAL);
							else DrawIconEx(offscreenDC.m_hDC,widest-402,y+2,m_hLowContinueIcon,400,30,NULL,NULL,DI_NORMAL);
						}
					}
					oldy=y; // oldy indicates that the background tab icon has been drawn for this line
					if (z==m_iCurrentSelection)
					{
						offscreenDC.ExtTextOut(startpos+2,y,ETO_CLIPPED,CRect(0,y,widest-15,y+30),word,NULL);
						if (width+startpos+2>widest-15) offscreenDC.TextOut(widest-12,y,"...");
					}
					else
					{
						offscreenDC.ExtTextOut(startpos,y+2,ETO_CLIPPED,CRect(0,y+2,widest-15,y+22),word,NULL);
						if (width+startpos>widest-15) offscreenDC.TextOut(widest-14,y+2,"...");
						offscreenDC.MoveTo(0,y+2);
						offscreenDC.LineTo(0,y+22);
						offscreenDC.MoveTo(1,y+2);
						offscreenDC.LineTo(1,y+22);
					}
					NewTab=FALSE;
					startpos+=width;
				}
			}
			y+=30;
			if (z<count-1) m_rectList.AddTail(CRect(0,starty,widest,y));
			else m_rectList.AddTail(CRect(0,starty,widest,INT_MAX));
			m_tabList.AddTail(z);
			if (z==count-1) // if at end fill remaining area with blank tab
			{
				while (y<rect2.Height())
				{
					if (z==m_iCurrentSelection) DrawIconEx(offscreenDC.m_hDC,widest-400,y+2,m_hHighContinueIcon,400,30,NULL,NULL,DI_NORMAL);
					else DrawIconEx(offscreenDC.m_hDC,widest-402,y+2,m_hLowContinueIcon,400,30,NULL,NULL,DI_NORMAL);
					y+=30;
				}
			}
		}
	}
	VERIFY(pdc->BitBlt(0,0,rcBounds.right-rcBounds.left,rcBounds.bottom-rcBounds.top,&offscreenDC,
					0,0,SRCCOPY)); // flips offscreen dc to real dc
	// select out any objects that were selected in
	offscreenDC.SelectObject(pOldFont);
    offscreenDC.SelectObject(pOldBitmap);
	// then delete the dc
	offscreenDC.DeleteDC();
}


/////////////////////////////////////////////////////////////////////////////
// CRTabsCtrl::DoPropExchange - Persistence support

void CRTabsCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);
	PX_Long(pPX, _T("FontNum"), m_FontNum, 0);
}


/////////////////////////////////////////////////////////////////////////////
// CRTabsCtrl::OnResetState - Reset control to default state

void CRTabsCtrl::OnResetState()
{                                                                                                                                                                                                                               
	COleControl::OnResetState();  // Resets defaults found in DoPropExchange
}


/////////////////////////////////////////////////////////////////////////////
// CRTabsCtrl message handlers

void CRTabsCtrl::AddTab(LPCTSTR text, long pWnd) 
{
	char* buffer=new char[strlen(text)+1]; // include terminating null character
	strcpy(buffer,text);
	m_textList.AddTail(buffer);
	m_windowList.AddTail((CWnd*)pWnd);
	TRACE1("Total tabs: %d",m_textList.GetCount());
	InvalidateControl();
}

void CRTabsCtrl::Clear() 
{
	m_windowList.RemoveAll();
	POSITION position=m_textList.GetHeadPosition();
	for (int x=0;x<m_textList.GetCount();x++)
	{
		delete m_textList.GetNext(position);
	}
	m_textList.RemoveAll();
	InvalidateControl();
}

void CRTabsCtrl::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// find which tab was clicked on, show that window and hide the rest
// the old way of finding tab...
	// lets assume for now that each tab is 80 pixels wide;
//	int tab=point.x/80;
// the new way!
	GetParent()->SendMessage(WM_PLAYSOUND,FIL_SFX_OFFICE_PAPER1,NULL);//DAW 06Apr99

	POSITION rectpos=m_rectList.GetHeadPosition();
	POSITION tabpos=m_tabList.GetHeadPosition();
	int x;
	CRect rect;
	int tab;
	for (x=0;x<m_rectList.GetCount();x++)
	{
		rect = m_rectList.GetNext(rectpos);
		tab = m_tabList.GetNext(tabpos);
		if (rect.PtInRect(point)) break;
	}
	SelectTab(tab);
	COleControl::OnLButtonDown(nFlags, point);
}

long CRTabsCtrl::GetFirstTab() 
{
	return (long)m_firstTab;
}

void CRTabsCtrl::SetFirstTab(long nNewValue) 
{
	m_firstTab=(CWnd*)nNewValue;
	SetModifiedFlag();
}

void CRTabsCtrl::DrawRow(float seperation, int start, int finish, CDC * pdc, int row, int rowWidth,BOOL lastrow)
{
	POSITION position = m_textList.FindIndex(finish);
	char* text;
	float total=(float)rowWidth;
	float width;
	CRect rect;
	this->GetParent()->GetClientRect(rect);
	for (int x=finish;x>=start;x--)
	{
		text=m_textList.GetPrev(position);
		width=pdc->GetTextExtent(text).cx+seperation;
		// draw the text in some sort of tab thingie here;
//		pdc->GetBoundsRect(temp,DCB_RESET);
//		pdc->SetBoundsRect(CRect(total-width,0,total,rect.bottom),DCB_DISABLE);
		m_rectList.AddTail(CRect(int(total-width),row*30,(int)total,(row*30)+29));
		m_tabList.AddTail(x);
		if (x==m_iCurrentSelection)
		{
//			DrawIconEx(pdc->m_hDC,(int)(total-400)+2,(row*30)+2,m_hHighTabIcon,400,30,NULL,NULL,DI_NORMAL);
			pdc->BitBlt(total-width-1,(row*30),width+3,30,&m_TabUpDC,
					m_TabUpWidth-width-3,0,SRCCOPY);
			pdc->ExtTextOut((int)(total-width)+8,(row*30)+4,ETO_CLIPPED,CRect((int)(total-width)+2,(row*30)+2,int(total),(row*30)+22),text,NULL);
			if (seperation<15) 	pdc->TextOut(int(total-14),(row*30)+2,"...");
//			pdc->MoveTo(int(total-width-15),(row*30));
//			pdc->LineTo(int(total-15),(row*30));
//			pdc->MoveTo(int(total-width-15),(row*30)+1);
//			pdc->LineTo(int(total-10),(row*30)+1);
		}
		else
		{
//			DrawIconEx(pdc->m_hDC,int(total-400),(row*30)+2,m_hLowTabIcon,400,32,NULL,NULL,DI_NORMAL);
			pdc->BitBlt(total-width-1,(row*30),width+1,30,&m_TabDownDC,
					m_TabDownWidth-width-1,0,SRCCOPY);
			pdc->ExtTextOut(int(total-width)+6,(row*30)+6,ETO_CLIPPED,CRect(int(total-width),(row*30)+4,int(total),(row*30)+22),text,NULL);
			if (seperation<15) pdc->TextOut(int(total-12),(row*30)+4,"...");
			if (lastrow)
			{
//				pdc->MoveTo(int(total-width),(row*30)+29);
//				pdc->LineTo(int(total),(row*30)+29);
//				pdc->MoveTo(int(total-width),(row*30)+18);
//				pdc->LineTo(int(total),(row*30)+18);
			}

		}
		total-=width;
	}
}

void CRTabsCtrl::OnSize(UINT nType, int cx, int cy) 
{
	COleControl::OnSize(nType, cx, cy);
	this->RedrawWindow();	
}

long CRTabsCtrl::CalculateHeight(long totalWidth) 
{
	int count=m_textList.GetCount();
	char* text;
	POSITION position = m_textList.GetHeadPosition();
	CDC* pdc=GetDC();
    CFont* pOldFont;
	if (m_hWnd) pOldFont = pdc->SelectObject((CFont*)this->GetParent()->SendMessage(WM_GETGLOBALFONT,m_FontNum,NULL));
	else pOldFont = pdc->GetCurrentFont();
	int start=0;
	int total=0;
	int width;
	long row=0;
	for (int x=0;x<count;x++)
	{
		text=m_textList.GetNext(position);
		width=pdc->GetTextExtent(text).cx+15; // 15 is minimum seperation between text
		total+=width;
		if (total>totalWidth || x==count-1)
		{
			if (x>start && total>totalWidth)
			{
				x--;
				if (position==NULL) position=m_textList.GetTailPosition();
				m_textList.GetPrev(position);
			}
			total=0;
			start=x+1;
			row++;
		}
	}
    pdc->SelectObject(pOldFont);
	ReleaseDC(pdc);
	return row*30;
}

BOOL CRTabsCtrl::GetHorzAlign() 
{
	return m_bHorzAlign;
}

void CRTabsCtrl::SetHorzAlign(BOOL bNewValue) 
{
	m_bHorzAlign=bNewValue;
	SetModifiedFlag();
	InvalidateControl();
}

long CRTabsCtrl::CalcWidestWord() 
{
	// Find the length of the longest word and put in widest
	int y;
	char word[30];
	long widest=0;
	int start;
	char* text;
	int width;
	CDC* pdc;
	pdc=GetDC();
    CFont* pOldFont;
	if (m_hWnd) pOldFont = pdc->SelectObject((CFont*)this->GetParent()->SendMessage(WM_GETGLOBALFONT,m_FontNum,NULL));
	else pOldFont = pdc->GetCurrentFont();
	POSITION position = m_textList.GetHeadPosition();
	for (int x=0;x<m_textList.GetCount();x++)
	{
		text=m_textList.GetNext(position);
		// split into component words
		start=0;
		for (y=0;y<(int)strlen(text)+1;y++) // includes terminating null character
		{
			if (text[y]==' ' || text[y]==NULL)
			{
				strncpy(word,text+start,min(y-start+1,30));
				word[min(y-start+1,30)]=NULL;
				start=y+1;
				width=pdc->GetTextExtent(word).cx+15;
				if (width>widest) widest=width;
			}
		}
	}
	pdc->SelectObject(pOldFont);
	ReleaseDC(pdc);
	widest+=15; // width of end bit of tab
	CRect rect;
	this->GetParent()->GetClientRect(rect);
	if (widest>rect.Width()/2) widest=rect.Width()/2;
	return widest;
}

void CRTabsCtrl::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	COleControl::OnShowWindow(bShow, nStatus);
}

long CRTabsCtrl::GetFontNum() 
{
	return m_FontNum;
}

void CRTabsCtrl::SetFontNum(long nNewValue) 
{
	m_FontNum=nNewValue;
	InvalidateControl();
	SetModifiedFlag();
}

CWnd* CRTabsCtrl::SelectTabBody(long tab) 
{
	int total=m_windowList.GetCount();
	CWnd* currentWindow;
	CWnd* pWnd;
	POSITION position=m_windowList.GetHeadPosition();
	for (int x=0;x<total;x++)
	{
		// why a loop? I suspect the GetIndex method uses
		// the same loop and using that function twice would end
		// up doing 2 loops which is slower.
		pWnd = m_windowList.GetNext(position);
		if (x==tab) 
		{
			pWnd->ShowWindow(SW_SHOW);
			currentWindow=pWnd;
		}
		else if (x==m_iCurrentSelection) pWnd->ShowWindow(SW_HIDE);
	}
//DEADCODE RDH 28/02/99 	GetParent()->SendMessage(WM_PLAYSOUND,FIL_SFX_OFFICE_DRAWER_SLIDE,NULL);
	return currentWindow;
}

long CRTabsCtrl::SelectTabInternal(long tab) 
{
	CWnd* currentWindow=SelectTabBody(tab);
	if (tab!=m_iCurrentSelection) FireSelectTab((long)currentWindow);
	m_iCurrentSelection=tab;
	InvalidateControl();
	return (long)currentWindow;
}
long CRTabsCtrl::SelectTab(long tab) 
{
	CWnd* currentWindow=SelectTabBody(tab);
	FireSelectTab((long)currentWindow);
	m_iCurrentSelection=tab;
	InvalidateControl();
	return (long)currentWindow;
}
