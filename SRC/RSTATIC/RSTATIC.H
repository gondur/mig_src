#if !defined(AFX_RSTATIC_H__C42BAC43_CA3C_11D1_A1F0_444553540000__INCLUDED_)
#define AFX_RSTATIC_H__C42BAC43_CA3C_11D1_A1F0_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// RStatic.h : main header file for RSTATIC.DLL

#if !defined( __AFXCTL_H__ )
	#error include 'afxctl.h' before including this file
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CRStaticApp : See RStatic.cpp for implementation.

class CRStaticApp : public COleControlModule
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

#endif // !defined(AFX_RSTATIC_H__C42BAC43_CA3C_11D1_A1F0_444553540000__INCLUDED)
