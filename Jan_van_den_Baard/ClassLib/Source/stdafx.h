// ClassLib library.
// Copyright (c) 2008 by Elijah Zarezky,
// All rights reserved.

// stdafx.h - include file for standard system include files

// initially generated by AfxScratch v1.0.3839 on 27.03.2008 at 08:21:03
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
#if (_MSC_VER > 1310)
#define _CRT_SECURE_NO_WARNINGS
#endif   // _MSC_VER

#define OEMRESOURCE

// remove automatic CRT/MFC dependencies generation

// see http://www.codeproject.com/KB/cpp/PrivateAssemblyProjects.aspx and
// http://blog.m-ri.de/index.php/2008/05/06/hotfix-fuer-usemsprivateassembliesh-und-vc-2008/
// by by Martin Richter for more information

#if defined(_MSC_VER) && (_MSC_VER >= 1400) && !defined(UNDER_CE)
// VC++ 8.0 or greater

#define _STL_NOFORCE_MANIFEST
#define _CRT_NOFORCE_MANIFEST
#define _AFX_NOFORCE_MANIFEST
#define _ATL_NOFORCE_MANIFEST

#ifdef __cplusplus
extern "C"
{
#endif

__declspec(selectany) int _forceCRTManifest;
__declspec(selectany) int _forceMFCManifest;
__declspec(selectany) int _forceAtlDllManifest;

// the next symbols are used by the several versions of VC++ 9.0
__declspec(selectany) int _forceCRTManifestRTM;
__declspec(selectany) int _forceMFCManifestRTM;
__declspec(selectany) int _forceMFCManifestCUR;

#ifdef __cplusplus
}   // extern "C"
#endif

#endif   // _MSC_VER && !UNDER_CE

// CRT headers

// _CRTDBG_MAP_ALLOC is not #define-d because we use our own implementation
// of the new and delete operators (see application.cpp file)

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdarg.h>
#include <tchar.h>
#include <malloc.h>
#include <crtdbg.h>
#include <new.h>

// PSDK headers

#include <windows.h>
#include <commctrl.h>
#include <shlwapi.h>

// force ISO/IEC 14882 conformance in for loop scope

#if (_MSC_VER < 1300)
#define for if (false); else for
#else
#pragma conform(forScope, on)
#endif	// _MSC_VER

#endif	// __stdafx_h

// end of file
