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

//DEAD// migmfc.cpp : Defines the class behaviors for the application.
//DEAD//
//DEAD
//DEAD#include "stdafx.h"
//DEAD#include "migmfc.h"
//DEAD#include	"WaveTabs.h"
//DEAD#include	"dosdefs.h"
//DEAD#include "MainFrm.h"
//DEAD#include "ChildFrm.h"
//DEAD#include "migmfcD.h"
//DEAD#include "migmfcV.h"
//DEAD//#include	"rsplitter.h"
//DEAD#include	"sub1.h"
//DEAD#include	"d4.h"
//DEAD#include	"Wave.h"
//DEAD#include	"Targets.h"
//DEAD#include "topplate.h"
//DEAD#include	"stub3d.h"
//DEAD#ifdef _DEBUG
//DEAD#define new DEBUG_NEW
//DEAD#undef THIS_FILE
//DEADstatic char THIS_FILE[] = __FILE__;
//DEAD#endif
//DEAD
//DEAD/////////////////////////////////////////////////////////////////////////////
//DEAD// CMigmfcApp
//DEAD
//DEADBEGIN_MESSAGE_MAP(CMigmfcApp, CWinApp)
//DEAD	//{{AFX_MSG_MAP(CMigmfcApp)
//DEAD	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
//DEAD		// NOTE - the ClassWizard will add and remove mapping macros here.
//DEAD		//    DO NOT EDIT what you see in these blocks of generated code!
//DEAD	//}}AFX_MSG_MAP
//DEAD	// Standard file based document commands
//DEAD	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
//DEAD	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
//DEAD	// Standard print setup command
//DEAD	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
//DEADEND_MESSAGE_MAP()
//DEAD
//DEAD/////////////////////////////////////////////////////////////////////////////
//DEAD// CMigmfcApp construction
//DEAD
//DEADCMigmfcApp::CMigmfcApp()	 //RegisterClass
//DEAD{
//DEAD	// TODO: add construction code here,
//DEAD	// Place all significant initialization in InitInstance
//DEAD//	  RegisterClassEx(NULL);
//DEAD}
//DEAD/////////////////////////////////////////////////////////////////////////////
//DEAD// The one and only CMigmfcApp object
//DEAD
//DEADCMigmfcApp theApp;
//DEAD
//DEAD/////////////////////////////////////////////////////////////////////////////
//DEAD// CMigmfcApp initialization
//DEAD
//DEADBOOL CMigmfcApp::InitInstance()
//DEAD{
//DEAD	AfxEnableControlContainer();
//DEAD
//DEAD	// Standard initialization
//DEAD	// If you are not using these features and wish to reduce the size
//DEAD	//  of your final executable, you should remove from the following
//DEAD	//  the specific initialization routines you do not need.
//DEAD
//DEAD#ifdef _AFXDLL
//DEAD	Enable3dControls();			// Call this when using MFC in a shared DLL
//DEAD#else
//DEAD	Enable3dControlsStatic();	// Call this when linking to MFC statically
//DEAD#endif
//DEAD
//DEAD	// Change the registry key under which our settings are stored.
//DEAD	// You should modify this string to be something appropriate
//DEAD	// such as the name of your company or organization.
//DEAD	SetRegistryKey(_T("Rowan Software"));
//DEAD
//DEAD	LoadStdProfileSettings(3);  // Load standard INI file options (including MRU)
//DEAD
//DEAD	// Register the application's document templates.  Document templates
//DEAD	//  serve as the connection between documents, frame windows and views.
//DEAD
//DEAD	
//DEAD	CMultiDocTemplate*pDocTemplate = new CMultiDocTemplate(
//DEAD		IDR_MIGMFCTYPE,
//DEAD		RUNTIME_CLASS(CMigmfcDoc),
//DEAD		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
//DEAD		RUNTIME_CLASS(CMigmfcView));
//DEAD//	CMultiDocTemplate*	pDocTemplate;
//DEAD//	AddDocTemplate(
//DEAD//		pDocTemplate=
//DEAD//			new CMultiDocTemplate(IDR_MIGMFCTYPE,
//DEAD//			RUNTIME_CLASS(CMigmfcDoc),RUNTIME_CLASS(RSplitter),NULL
//DEAD//				)				);
//DEAD
//DEAD	// create main MDI Frame window
//DEAD	CMainFrame* pMainFrame = new CMainFrame;
//DEAD	if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
//DEAD		return FALSE;
//DEAD	m_pMainWnd = pMainFrame;
//DEAD
//DEAD	// Enable drag/drop open
//DEAD	m_pMainWnd->DragAcceptFiles();
//DEAD
//DEAD	// Enable DDE Execute open
//DEAD	EnableShellOpen();
//DEAD//	RegisterShellFileTypes(TRUE);
//DEAD
//DEAD	// Parse command line for standard shell commands, DDE, file open
//DEAD	CCommandLineInfo cmdInfo;
//DEAD	ParseCommandLine(cmdInfo);
//DEAD
//DEAD	// Dispatch commands specified on the command line
//DEAD//	if (!ProcessShellCommand(cmdInfo))
//DEAD//		return FALSE;
//DEAD
//DEAD	// The main window has been initialized, so show and update it.
//DEAD//	m_nCmdShow=SW_SHOWMAXIMIZED;
//DEAD	pMainFrame->ShowWindow(m_nCmdShow);
//DEAD	pMainFrame->UpdateWindow();
//DEAD	typedef	HideEdgeControl	EDGE; 
//DEAD/*
//DEAD	RDialog::MakeTopDialog(CRect(0,0,640,480),
//DEAD							DialList(DialBox(IDB_ARTWORK,new d4),
//DEAD								DialBox(IDB_ARTWORK2,new sub1,Edges(EDGE::ALIGN_MIN + EDGE::ACTIONS_SPLITTER,EDGE::ALIGN_MIN,EDGE::ALIGN_MIN + EDGE::OCCLUDE_INSIDE,EDGE::ALIGN_MIN + EDGE::OCCLUDE_INSIDE)),
//DEAD								DialBox(IDB_ARTWORK3,new sub1,Edges(EDGE::ALIGN_MIN,EDGE::ALIGN_MIN,EDGE::ALIGN_MIN + EDGE::ACTIONS_SPLITTER,EDGE::ALIGN_MIN)),
//DEAD//								DialBox(IDB_ARTWORK2,new sub1,Edges(EDGE::ALIGN_MIN,EDGE::ALIGN_MIN+EDGE::ACTIONS_TABBED,EDGE::ALIGN_MIN,EDGE::ALIGN_MIN)),
//DEAD//								DialBox(IDB_ARTWORK3,new sub1,Edges(EDGE::ALIGN_MIN,EDGE::ALIGN_MIN+EDGE::ACTIONS_TABBED,EDGE::ALIGN_MIN,EDGE::ALIGN_MIN))
//DEAD
//DEAD								VTabBox(NULL,IdList(IDS_TAB1,"A rather long tab",NULL,"Tab 4"),Edges(EDGE::ALIGN_MIN,EDGE::ALIGN_MIN,EDGE::ALIGN_MAX,EDGE::ALIGN_MAX), 
//DEAD									DialBox(IDB_ARTWORK,new sub1),
//DEAD									DialBox(IDB_ARTWORK2,new sub1),
//DEAD									DialBox(IDB_ARTWORK3,new sub1),
//DEAD									DialBox(IDB_ARTWORK4,new sub1)
//DEAD								),
//DEAD								HTabBox(NULL,IdList(IDS_TAB1,"A quite long tab",NULL,"Tab 4"),Edges(EDGE::ALIGN_MIN,EDGE::ALIGN_MIN,EDGE::ALIGN_MAX,EDGE::ALIGN_MAX), 
//DEAD									DialBox(IDB_ARTWORK,new sub1),
//DEAD									DialBox(IDB_ARTWORK2,new sub1),
//DEAD									DialBox(IDB_ARTWORK3,new sub1),
//DEAD									DialBox(IDB_ARTWORK4,new sub1)
//DEAD								)
//DEAD							)
//DEAD						  );
//DEAD*/
//DEAD	CTargets* ptargets;
//DEAD	ptargets=new CTargets;
//DEAD	RDialog::MakeTopDialog(CRect(0,0,320,420),
//DEAD							DialList(DialBox(IDB_ESCORT,new CWaveTabs),
//DEAD								HTabBox(NULL,IdList("BarCAP","Strike F80 (2)","AAA F80 (2)","Escort F80 (2)"),Edges(EDGE::ALIGN_MIN,EDGE::ALIGN_MIN,EDGE::ALIGN_MAX,EDGE::ALIGN_MAX), 
//DEAD									DialBox(IDB_ARTWORK2,new sub1),
//DEAD									DialList(DialBox(IDB_ESCORT,new CWave),
//DEAD										DialBox(IDB_ESCORT,ptargets,Edges(EDGE::ALIGN_MIN,EDGE::ALIGN_MIN,EDGE::ALIGN_MIN,EDGE::ALIGN_MIN))),
//DEAD									DialBox(IDB_ARTWORK3,new sub1),
//DEAD									DialBox(IDB_ARTWORK4,new sub1)
//DEAD								)
//DEAD							)
//DEAD						  );
//DEAD	// should change this into a function and make these private again.
//DEAD//	ptargets->homesize.bottom=ptargets->homesize.bottom/2;
//DEAD	// update the change by calling the size function without actually changing the size
//DEAD//	ptargets->OnSize(0,ptargets->viewsize.Width(),ptargets->viewsize.Height());
//DEAD	return TRUE;
//DEAD}
//DEAD
//DEAD/////////////////////////////////////////////////////////////////////////////
//DEAD// CAboutDlg dialog used for App About
//DEAD
//DEADclass CAboutDlg : public CDialog
//DEAD{
//DEAD	sub1	sub;
//DEADpublic:
//DEAD	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
//DEAD	CAboutDlg();
//DEAD	BOOL	Create(CWnd* w=NULL)	{return CDialog::Create(IDD,w);}
//DEAD// Dialog Data
//DEAD	//{{AFX_DATA(CAboutDlg)
//DEAD	enum { IDD = IDD_ABOUTBOX };
//DEAD	//}}AFX_DATA
//DEAD
//DEAD	// ClassWizard generated virtual function overrides
//DEAD	//{{AFX_VIRTUAL(CAboutDlg)
//DEAD	protected:
//DEAD	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
//DEAD	//}}AFX_VIRTUAL
//DEAD
//DEAD// Implementation
//DEADprotected:
//DEAD	//{{AFX_MSG(CAboutDlg)
//DEAD//	afx_msg void OnSize(UINT nType, int cx, int cy);
//DEAD//	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
//DEAD	//}}AFX_MSG
//DEAD	DECLARE_MESSAGE_MAP()
//DEAD};
//DEAD
//DEADCAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD),sub(this)
//DEAD{
//DEAD	//{{AFX_DATA_INIT(CAboutDlg)
//DEAD	//}}AFX_DATA_INIT
//DEAD
//DEAD}
//DEAD
//DEADvoid CAboutDlg::DoDataExchange(CDataExchange* pDX)
//DEAD{
//DEAD	CDialog::DoDataExchange(pDX);
//DEAD	//{{AFX_DATA_MAP(CAboutDlg)
//DEAD	//}}AFX_DATA_MAP
//DEAD}
//DEAD
//DEADBEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
//DEAD	//{{AFX_MSG_MAP(CAboutDlg)
//DEAD	ON_WM_SIZE()
//DEAD	ON_WM_CREATE()
//DEAD	//}}AFX_MSG_MAP
//DEADEND_MESSAGE_MAP()
//DEAD
//DEAD// App command to run the dialog
//DEADvoid CMigmfcApp::OnAppAbout()
//DEAD{	
//DEAD	typedef	HideEdgeControl	EDGE; 
//DEAD	RDialog::MakeTopDialog(CRect(0,0,640,480),
//DEAD							DialList(DialBox(IDB_ARTWORK,new d4),
//DEAD								DialBox(IDB_ARTWORK2,new sub1,Edges(EDGE::ALIGN_MIN + EDGE::ACTIONS_SPLITTER,EDGE::ALIGN_MIN,EDGE::ALIGN_MIN + EDGE::OCCLUDE_INSIDE,EDGE::ALIGN_MIN + EDGE::OCCLUDE_INSIDE)),
//DEAD								DialBox(IDB_ARTWORK3,new sub1,Edges(EDGE::ALIGN_MIN,EDGE::ALIGN_MIN,EDGE::ALIGN_MIN + EDGE::ACTIONS_SPLITTER,EDGE::ALIGN_MIN)),
//DEAD//								DialBox(IDB_ARTWORK2,new sub1,Edges(EDGE::ALIGN_MIN,EDGE::ALIGN_MIN+EDGE::ACTIONS_TABBED,EDGE::ALIGN_MIN,EDGE::ALIGN_MIN)),
//DEAD//								DialBox(IDB_ARTWORK3,new sub1,Edges(EDGE::ALIGN_MIN,EDGE::ALIGN_MIN+EDGE::ACTIONS_TABBED,EDGE::ALIGN_MIN,EDGE::ALIGN_MIN))
//DEAD
//DEAD								VTabBox(NULL,IdList(IDS_TAB1,"A rather long tab",NULL,"Tab 4"),Edges(EDGE::ALIGN_MIN,EDGE::ALIGN_MIN,EDGE::ALIGN_MAX,EDGE::ALIGN_MAX), 
//DEAD									DialBox(IDB_ARTWORK,new sub1),
//DEAD									DialBox(IDB_ARTWORK2,new sub1),
//DEAD									DialBox(IDB_ARTWORK3,new sub1),
//DEAD									DialBox(IDB_ARTWORK4,new sub1)
//DEAD								),
//DEAD								HTabBox(NULL,IdList(IDS_TAB1,"A quite long tab",NULL,"Tab 4"),Edges(EDGE::ALIGN_MIN,EDGE::ALIGN_MIN,EDGE::ALIGN_MAX,EDGE::ALIGN_MAX), 
//DEAD									DialBox(IDB_ARTWORK,new sub1),
//DEAD									DialBox(IDB_ARTWORK2,new sub1),
//DEAD									DialBox(IDB_ARTWORK3,new sub1),
//DEAD									DialBox(IDB_ARTWORK4,new sub1)
//DEAD								)
//DEAD							)
//DEAD						  );
//DEAD
//DEAD//	CAboutDlg* aboutDlg=new CAboutDlg;
//DEAD//	m_pMainWnd->ModifyStyle(0,WS_CLIPCHILDREN);
//DEAD//	aboutDlg->Create(); //m_pMainWnd);
//DEAD//	//delete CAboutDlg;
//DEAD}
//DEAD
//DEAD/////////////////////////////////////////////////////////////////////////////
//DEAD// CMigmfcApp commands
//DEAD
//DEAD//void CAboutDlg::OnSize(UINT nType, int cx, int cy) 
//DEAD//{
//DEAD	//CDialog::OnSize(nType, cx, cy);
//DEAD//	
//DEAD	// TODO: Add your message handler code here
//DEAD//	ModifyStyle(0,WS_HSCROLL+WS_VSCROLL);	
//DEAD//}
//DEAD
//DEAD//int CAboutDlg::OnCreate(LPCREATESTRUCT lpCreateStruct) 
//DEAD//{
//DEAD//	if (CDialog::OnCreate(lpCreateStruct) == -1)
//DEAD//		return -1;
//DEAD//	
//DEAD//	// TODO: Add your specialized creation code here
//DEAD////	sub.Create(IDD_sub1,this);
//DEAD//
//DEAD//	
//DEAD//	return 0;
//DEAD//} 
//DEAD
//DEAD
//DEAD
//DEADint CMigmfcApp::Run() 
//DEAD{
//DEAD	Master_3d.Init(m_hInstance,m_pMainWnd->m_hWnd);
//DEAD	for (int i=0;i<Master_3d.NUM_EVENTS;i++)
//DEAD		Master_3d.htable[i]=CreateEvent(0,0,0,0);
//DEAD
//DEAD	// Culled from CWinApp::Run() and CWinTread::Run()
//DEAD	// The following bit is called once in CWinApp::Run()
//DEAD	if (m_pMainWnd == NULL && AfxOleGetUserCtrl())
//DEAD	{
//DEAD		// Not launched /Embedding or /Automation, but has no main window!
//DEAD		TRACE0("Warning: m_pMainWnd is NULL in CWinApp::Run - quitting application.\n");
//DEAD		AfxPostQuitMessage(0);
//DEAD	}
//DEAD
//DEAD
//DEAD	// Add your specialized code here and/or call the base class
//DEAD	//
//DEAD	// The following is adapted from CWinThread::Run()
//DEAD	// OnIdle()			is called when there are no more messages
//DEAD	// PumpMessage()	is called when there is a windows message
//DEAD	//						-returns FALSE after WM_QUIT message.
//DEAD	//
//DEAD	// I need to add new code for the message pump when in the 3d.
//DEAD	// At present, I will just cheat.
//DEAD	//
//DEAD
//DEAD 	ASSERT_VALID(this);
//DEAD	// for tracking the idle time state
//DEAD	BOOL bIdle = TRUE;
//DEAD	LONG lIdleCount = 0;
//DEAD
//DEAD
//DEAD
//DEAD
//DEAD	// acquire and dispatch messages until a WM_QUIT message is received.
//DEAD	for (;;)
//DEAD	{
//DEAD
//DEAD		int result;
//DEAD		if (Inst3d::InThe3D()||!bIdle)
//DEAD			result=MsgWaitForMultipleObjects(2,Master_3d.htable,FALSE,INFINITE,QS_ALLINPUT);//don't wait - ever!
//DEAD		else
//DEAD			result=MsgWaitForMultipleObjects(2,Master_3d.htable,FALSE,0,QS_ALLINPUT);//don't wait - ever!
//DEAD		switch (result)
//DEAD		{
//DEAD		case WAIT_OBJECT_0+Mast3d::EVENT_KEYS:
//DEAD			Inst3d::OnKeyInput();
//DEAD
//DEAD			break;
//DEAD		case WAIT_OBJECT_0+Mast3d::EVENT_MOUSE:
//DEAD			break;
//DEAD		case WAIT_OBJECT_0+Mast3d::NUM_EVENTS:
//DEAD			if (Inst3d::InThe3D())
//DEAD				while (::PeekMessage(&m_msgCur, NULL, WM_KEYFIRST, WM_KEYLAST,PM_REMOVE))
//DEAD				{}
//DEAD			while (::PeekMessage(&m_msgCur, NULL, NULL, NULL, PM_NOREMOVE))
//DEAD			{
//DEAD		
//DEAD				if (!PumpMessage())
//DEAD					return ExitInstance();
//DEAD			}
//DEAD			if (IsIdleMessage(&m_msgCur))
//DEAD			{
//DEAD				bIdle = TRUE;
//DEAD				lIdleCount = 0;
//DEAD			}
//DEAD			break;
//DEAD		default:
//DEAD			*(char*)0xb0A00+=1;
//DEAD			if (!OnIdle(lIdleCount++))
//DEAD				bIdle = FALSE; // assume "no idle" state
//DEAD		}
//DEAD	}
//DEAD
//DEAD	ASSERT(FALSE);  // not reachable
//DEAD
//DEAD}
//DEAD
