#if !defined(AFX_RANIBUT_H__8E9ADEEC_6C9B_11D1_A1F0_444553540000__INCLUDED_)
#define AFX_RANIBUT_H__8E9ADEEC_6C9B_11D1_A1F0_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// RAniBut.h : main header file for RANIBUT.DLL

#if !defined( __AFXCTL_H__ )
	#error include 'afxctl.h' before including this file
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CRAniButApp : See RAniBut.cpp for implementation.

class CRAniButApp : public COleControlModule
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

#endif // !defined(AFX_RANIBUT_H__8E9ADEEC_6C9B_11D1_A1F0_444553540000__INCLUDED)
