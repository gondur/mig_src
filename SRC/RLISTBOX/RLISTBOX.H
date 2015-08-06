#if !defined(AFX_RLISTBOX_H__90B5EDAD_666F_11D1_A1F0_444553540000__INCLUDED_)
#define AFX_RLISTBOX_H__90B5EDAD_666F_11D1_A1F0_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// RListBox.h : main header file for RLISTBOX.DLL

#if !defined( __AFXCTL_H__ )
	#error include 'afxctl.h' before including this file
#endif

#include "resource.h"       // main symbols
#include "rscrlbar.h"	// Added by ClassView

/////////////////////////////////////////////////////////////////////////////
// CRListBoxApp : See RListBox.cpp for implementation.

class CRListBoxApp : public COleControlModule
{
public:
	CRScrlBar m_rScrlBar;
	BOOL InitInstance();
	int ExitInstance();
};

extern const GUID CDECL _tlid;
extern const WORD _wVerMajor;
extern const WORD _wVerMinor;

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RLISTBOX_H__90B5EDAD_666F_11D1_A1F0_444553540000__INCLUDED)
