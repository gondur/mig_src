#if !defined(AFX_RSPLTBAR_H__0542BF4C_88DF_11D1_A1F0_444553540000__INCLUDED_)
#define AFX_RSPLTBAR_H__0542BF4C_88DF_11D1_A1F0_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// RSpltBar.h : main header file for RSPLTBAR.DLL

#if !defined( __AFXCTL_H__ )
	#error include 'afxctl.h' before including this file
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CRSpltBarApp : See RSpltBar.cpp for implementation.

class CRSpltBarApp : public COleControlModule
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

#endif // !defined(AFX_RSPLTBAR_H__0542BF4C_88DF_11D1_A1F0_444553540000__INCLUDED)
