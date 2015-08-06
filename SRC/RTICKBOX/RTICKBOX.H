#if !defined(AFX_RTICKBOX_H__840ED4AD_CF9B_11D1_A1F0_0080C8582DE4__INCLUDED_)
#define AFX_RTICKBOX_H__840ED4AD_CF9B_11D1_A1F0_0080C8582DE4__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// RTickBox.h : main header file for RTICKBOX.DLL

#if !defined( __AFXCTL_H__ )
	#error include 'afxctl.h' before including this file
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CRTickBoxApp : See RTickBox.cpp for implementation.

class CRTickBoxApp : public COleControlModule
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

#endif // !defined(AFX_RTICKBOX_H__840ED4AD_CF9B_11D1_A1F0_0080C8582DE4__INCLUDED)
