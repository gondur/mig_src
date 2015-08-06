#if !defined(AFX_RJOYCFG_H__1B499F71_C31E_11D1_A1F0_444553540000__INCLUDED_)
#define AFX_RJOYCFG_H__1B499F71_C31E_11D1_A1F0_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// RJoyCfg.h : main header file for RJOYCFG.DLL

#if !defined( __AFXCTL_H__ )
	#error include 'afxctl.h' before including this file
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CRJoyCfgApp : See RJoyCfg.cpp for implementation.

class CRJoyCfgApp : public COleControlModule
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

#endif // !defined(AFX_RJOYCFG_H__1B499F71_C31E_11D1_A1F0_444553540000__INCLUDED)
