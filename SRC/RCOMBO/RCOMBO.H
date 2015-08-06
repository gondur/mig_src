#if !defined(AFX_RCOMBO_H__737CB0CF_B42B_11D1_A1F0_444553540000__INCLUDED_)
#define AFX_RCOMBO_H__737CB0CF_B42B_11D1_A1F0_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// RCombo.h : main header file for RCOMBO.DLL

#if !defined( __AFXCTL_H__ )
	#error include 'afxctl.h' before including this file
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CRComboApp : See RCombo.cpp for implementation.

class CRComboApp : public COleControlModule
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

#endif // !defined(AFX_RCOMBO_H__737CB0CF_B42B_11D1_A1F0_444553540000__INCLUDED)
