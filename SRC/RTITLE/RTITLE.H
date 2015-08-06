#if !defined(AFX_RTITLE_H__008F23EF_9243_11D1_A1F0_444553540000__INCLUDED_)
#define AFX_RTITLE_H__008F23EF_9243_11D1_A1F0_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// RTitle.h : main header file for RTITLE.DLL

#if !defined( __AFXCTL_H__ )
	#error include 'afxctl.h' before including this file
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CRTitleApp : See RTitle.cpp for implementation.

class CRTitleApp : public COleControlModule
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

#endif // !defined(AFX_RTITLE_H__008F23EF_9243_11D1_A1F0_444553540000__INCLUDED)
