// MIG.h : main header file for the MIG application
//

#if !defined(AFX_MIG_H__19CD38C5_A868_11D1_9B68_444553540000__INCLUDED_)
#define AFX_MIG_H__19CD38C5_A868_11D1_9B68_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CMIGApp:
// See MIG.cpp for the implementation of this class
//

class CMIGApp : public CWinApp
{
public:
	CMIGApp();
	~CMIGApp();

	HINSTANCE resourceInst;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMIGApp)
	public:
	virtual BOOL InitInstance();
	virtual int Run();
	virtual int ExitInstance();	
	//}}AFX_VIRTUAL

// Implementation
	char helpfilepath[80];
	const char* oldhelppath;
	UINT	wheelmessagenum;
	//{{AFX_MSG(CMIGApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MIG_H__19CD38C5_A868_11D1_9B68_444553540000__INCLUDED_)
