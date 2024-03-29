// LayoutEngine application.
// Copyright (c) 2008 by Jan van den Baard,
// All rights reserved.

// stdafx.h - include file for standard system include files

// initially generated by AfxScratch v1.0.3839 on 11.04.2008 at 10:49:38
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

// C4996: function or variable may be unsafe
#define _CRT_SECURE_NO_WARNINGS

// PSDK headers
#include <windows.h>

// CRT headers
#include <tchar.h>

// force ISO/IEC 14882 conformance in for loop scope
#if (_MSC_VER < 1300)
#define for if (false); else for
#else
#pragma conform(forScope, on)
#endif	// _MSC_VER

#endif	// __stdafx_h

// end of file
