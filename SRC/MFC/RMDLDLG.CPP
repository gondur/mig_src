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

// RMdlDlg.cpp : implementation file
//
// a greatly reduced rdialog used for message boxes
// does not support dialog nesting or resizing
// does not necessarily have to be modal though

#include "stdafx.h"
#include "mig.h"
#include "RMdlDlg.h"
#include "messages.h"
#include "fileman.h"
#include "MIGView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#ifndef THIS_FILE_DEFINED
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif
extern CFont* (g_AllFonts[][4]);
extern CDC g_OffScreenDC;

/////////////////////////////////////////////////////////////////////////////
// RMdlDlg dialog


RMdlDlg::RMdlDlg(CWnd* pParent /*=NULL*/)
	: CDialog(RMdlDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(RMdlDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_pfileblock=NULL;
	m_lbuttondown=FALSE;
}


void RMdlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(RMdlDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	DDX_Control(pDX,IDC_OK,m_IDC_OK);
	DDX_Control(pDX,IDC_CANCEL,m_IDC_CANCEL);
	DDX_Control(pDX,IDJ_TITLE,m_IDJ_TITLE);

	DDX_Control(pDX,IDC_RETRY,m_IDC_RETRY);
	DDX_Control(pDX,IDC_MESSAGE_TEXT,m_IDC_MESSAGE_TEXT);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(RMdlDlg, CDialog)
	//{{AFX_MSG_MAP(RMdlDlg)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_MESSAGE( WM_GETARTWORK, OnGetArt)
	ON_MESSAGE( WM_GETXYOFFSET, OnGetXYOffset)
	ON_MESSAGE( WM_GETGLOBALFONT, OnGetGlobalFont)
	ON_MESSAGE( WM_GETFILE, OnGetFile)
	ON_MESSAGE( WM_RELEASELASTFILE, OnReleaseLastFile)
	ON_MESSAGE( WM_GETOFFSCREENDC, OnGetOffScreenDC)
	ON_MESSAGE( WM_GETHINTBOX, OnGetHintBox)
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// RMdlDlg message handlers
FileNum RMdlDlg::OnGetArt()
{
	return m_artnum;
}

long RMdlDlg::OnGetXYOffset()
{
	return 0;
}

CFont* RMdlDlg::OnGetGlobalFont(int fontnum)
{
    if (fontnum<0||fontnum>MAXFONTS)
		fontnum=0;
	return g_AllFonts[fontnum][0];
}

BYTE* RMdlDlg::OnGetFile(int filenum)
{
	if (m_pfileblock)
	{
		delete m_pfileblock;
		m_pfileblock=NULL;
	}
	if (!(filenum>0x6800 && filenum<0x7100))  //only directories 104..113
		return NULL;
	m_pfileblock=new fileblock((FileNum)filenum);
	return (BYTE*)getdata(m_pfileblock);
}

void RMdlDlg::OnReleaseLastFile()
{
	delete m_pfileblock;
	m_pfileblock=NULL;
}

CDC* RMdlDlg::OnGetOffScreenDC()
{
	return &g_OffScreenDC;
}

CHintBox* RMdlDlg::OnGetHintBox()
{
	if (!RDialog::m_pHintBox)
		RDialog::m_pHintBox=new CHintBox;
	if (!RDialog::m_pHintBox->m_hWnd)
		RDialog::m_pHintBox->Create(CHintBox::IDD,this);
	return RDialog::m_pHintBox;
}

BEGIN_EVENTSINK_MAP(RMdlDlg, CDialog)
    //{{AFX_EVENTSINK_MAP(RMdlDlg)
	ON_EVENT(RMdlDlg, IDC_OK, 1 /* Clicked */, OnClickedOk, VTS_NONE)
	ON_EVENT(RMdlDlg, IDC_RETRY, 1 /* Clicked */, OnClickedRetry, VTS_NONE)
	ON_EVENT(RMdlDlg, IDC_CANCEL, 1 /* Clicked */, OnClickedCancel, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void RMdlDlg::OnClickedOk() 
{
	EndDialog(0);
}

void RMdlDlg::OnClickedRetry() 
{
	EndDialog(2);
}

void RMdlDlg::OnClickedCancel() 
{
	EndDialog(1);
}
int	ScaleTranslate(int input,bool isy);

BOOL RMdlDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	// scale due to font size change
	// xfactor seems to be slightly smaller than yfactor
	// for some reason
//DEADCODE JIM 18/08/99 	float yfactor=96.0f/RDialog::fontdpi;
//DEADCODE JIM 18/08/99 	float xfactor=yfactor;
//DEADCODE JIM 18/08/99 	if (xfactor!=1.0f)
//DEADCODE JIM 18/08/99 		xfactor*=0.94f; // fiddle factor
	CRect rect;
	CRect parentrect;
	CWnd* pControl;
	pControl=GetTopWindow();
	GetClientRect(parentrect);
	ClientToScreen(parentrect);
	while (pControl)
	{
		// find coords relative to parent window...
		// why they dont have a ClientToParent function I dont know
		pControl->GetWindowRect(rect);
		rect-=parentrect.TopLeft();
		rect.right=ScaleTranslate(rect.right,false);
		rect.bottom=ScaleTranslate(rect.bottom,true);
		rect.left=ScaleTranslate(rect.left,false);
		rect.top=ScaleTranslate(rect.top,true);;
		pControl->MoveWindow(rect);
		pControl=pControl->GetNextWindow();
	}
	// size the actual dialog
	CRect rect2;
	GetClientRect(rect2);
	rect2.right=ScaleTranslate(rect2.right,false);
	rect2.bottom=ScaleTranslate(rect2.bottom,true);

	CRButton* rbutton;
	CRStatic* rstatic;
	CString string;
	rbutton=GETDLGITEM(IDJ_TITLE);
	string.LoadString(m_TitleID);
	rbutton->SetString(string);
	rstatic=GETDLGITEM(IDC_MESSAGE_TEXT);
	string.LoadString(m_MessageID);
	rstatic->SetString(string);
	rbutton=GETDLGITEM(IDC_OK);
	if (m_Button0ID)
	{
		string.LoadString(m_Button0ID);
		rbutton->SetString(string);
	}
	else
		rbutton->ShowWindow(SW_HIDE);
	rbutton=GETDLGITEM(IDC_CANCEL);
	if (m_Button1ID)
	{
		string.LoadString(m_Button1ID);
		rbutton->SetString(string);
	}
	else
		rbutton->ShowWindow(SW_HIDE);
	rbutton=GETDLGITEM(IDC_RETRY);
	if (m_Button2ID)
	{
		string.LoadString(m_Button2ID);
		rbutton->SetString(string);
	}
	else
		rbutton->ShowWindow(SW_HIDE);
	// centre the dialog on the screen
	GetDesktopWindow()->GetWindowRect(rect);
	MoveWindow((rect.Width()-rect2.Width())/2,(rect.Height()-rect2.Height())/2,rect2.Width(),rect2.Height());
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void RMdlDlg::OnPaint() 
{
	PAINTSTRUCT paintstruct;
	CDC* pDC;
	pDC=this->BeginPaint(&paintstruct);
	paintstruct.fErase=TRUE;
	BYTE* pData;
	if (m_artnum)
	{
		fileblock picture(m_artnum);
		pData=(BYTE*)getdata(picture);
		if (pData[0]=='B' && pData[1]=='M') // checks if its a bitmap file
		{
			// now render it...
			BITMAPFILEHEADER* pFile=(BITMAPFILEHEADER*)pData;
			BITMAPINFO* pInfo=(BITMAPINFO*)(pData+sizeof(BITMAPFILEHEADER));
			pData+=pFile->bfOffBits;
			// check if any of the parents have the same artwork then calculate an offset
			long offsets=OnGetXYOffset();
			SetDIBitsToDevice(pDC->m_hDC,short(offsets & 0x0000FFFF),short((offsets & 0xFFFF0000)>>16),pInfo->bmiHeader.biWidth, pInfo->bmiHeader.biHeight,
				0,0,0,pInfo->bmiHeader.biHeight,pData,pInfo,DIB_RGB_COLORS);
		}
	}
	this->EndPaint(&paintstruct);
}

void RMdlDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	m_point=point;	
	m_lbuttondown=TRUE;
	SetCapture();
	CDialog::OnLButtonDown(nFlags, point);
}

void RMdlDlg::OnMouseMove(UINT nFlags, CPoint point) 
{
	if (m_lbuttondown)
	{
		CRect rect;
		GetWindowRect(rect);
		rect+=point-m_point;
		MoveWindow(rect);
	}
	CDialog::OnMouseMove(nFlags, point);
}

void RMdlDlg::OnLButtonUp(UINT nFlags, CPoint point) 
{
	m_lbuttondown=FALSE;
	ReleaseCapture();
	CDialog::OnLButtonUp(nFlags, point);
}

BOOL RMdlDlg::OnEraseBkgnd(CDC* pDC) 
{
	return TRUE;
}
