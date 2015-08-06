// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//
#pragma optimize( "g", off )

#if !defined(AFX_STDAFX_H__19CD38C7_A868_11D1_9B68_444553540000__INCLUDED_)
#define AFX_STDAFX_H__19CD38C7_A868_11D1_9B68_444553540000__INCLUDED_


#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers
#include <afxctl.h>
#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxole.h>         // MFC OLE classes
#include <afxodlgs.h>       // MFC OLE dialog classes
#include <afxdisp.h>        // MFC OLE automation classes
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT
#include "dosdefs.h"

//#include	"resource.h"
//#include	"RDialog.h"
//#include	"RSheets.h"
#ifndef	NO_AFX_AUTO
//#include	"Sheetdef.h"
#include	"afxauto.h"	  //DONT COMMENT THIS OUT. IF YOU HAVE A PROBLEM ASK ME!!!!!
#endif

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__19CD38C7_A868_11D1_9B68_444553540000__INCLUDED_)
