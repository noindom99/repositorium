// atlmfc71 library.
// Copyright (c) 2005 by Elijah Zarezky,
// All rights reserved.

// stdafx.h - include file for standard system include files

// initially generated by AfxScratch v1.0.2461 on 21.01.2005 at 09:57:58
// visit http://zarezky.spb.ru/projects/afx_scratch.html for more info

#if !defined(__stdafx_h)
#define __stdafx_h

#if defined(_MSC_VER) && (_MSC_VER > 1000)
#pragma once
#endif	// _MSC_VER

// unreferenced inline/local function has been removed
#pragma warning(disable: 4514)
// function not inlined
#pragma warning(disable: 4710)
// identifier was truncated in the debug information
#pragma warning(disable: 4786)

// use Win2000 features
#define _WIN32_WINNT 0x0500

// MFC headers
#include <afxwin.h>			// MFC core and standard components
#include <afxdlgs.h>			// MFC standard dialogs
#include <afxpriv.h>			// MFC private classes

// RSDK headers
#include <shlwapi.h>			// light-weight utility APIs
#include <dlgs.h>				// standard control IDs for commdlg

// force ISO/IEC 14882 conformance in for loop scope
#if (_MSC_VER < 1300)
#define for if (false); else for
#else
#pragma conform(forScope, on)
#endif	// _MSC_VER

#endif	// __stdafx_h

// end of file
