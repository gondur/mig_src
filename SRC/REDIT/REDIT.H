#if !defined(AFX_REDIT_H__499E2BEC_AC32_11D1_A1F0_444553540000__INCLUDED_)
#define AFX_REDIT_H__499E2BEC_AC32_11D1_A1F0_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// REdit.h : main header file for REDIT.DLL

#if !defined( __AFXCTL_H__ )
	#error include 'afxctl.h' before including this file
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CREditApp : See REdit.cpp for implementation.

class CREditApp : public COleControlModule
{
public:
	BOOL InitInstance();
	int ExitInstance();
};

extern const GUID CDECL _tlid;
extern const WORD _wVerMajor;
extern const WORD _wVerMinor;

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REDIT_H__499E2BEC_AC32_11D1_A1F0_444553540000__INCLUDED)
