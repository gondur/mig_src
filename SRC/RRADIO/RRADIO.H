#if !defined(AFX_RRADIO_H__7EBC74EA_0F3C_11D2_A1F0_0080C8582DE4__INCLUDED_)
#define AFX_RRADIO_H__7EBC74EA_0F3C_11D2_A1F0_0080C8582DE4__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// RRadio.h : main header file for RRADIO.DLL

#if !defined( __AFXCTL_H__ )
	#error include 'afxctl.h' before including this file
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CRRadioApp : See RRadio.cpp for implementation.

class CRRadioApp : public COleControlModule
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

#endif // !defined(AFX_RRADIO_H__7EBC74EA_0F3C_11D2_A1F0_0080C8582DE4__INCLUDED)
