// Copyright by Richard Butler.

//*****************************************************************************
// Modified by Elijah Zarezky aka SchweinDeBurg (elijah.zarezky@gmail.com):
// - improved compatibility with the Unicode-based builds
// - added AbstractSpoon Software copyright notice and license information
// - adjusted #include's paths
//*****************************************************************************

// StdAfx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__CBB777D4_541B_4A75_BE5D_0E67D4C9E96A__INCLUDED_)
#define AFX_STDAFX_H__CBB777D4_541B_4A75_BE5D_0E67D4C9E96A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//////////////////////////////////////////////////////////////////////////////////////////////
// unwanted warnings

// unreferenced local function has been removed
#pragma warning(disable: 4505)
// unreferenced inline function has been removed
#pragma warning(disable: 4514)
// function not inlined
#pragma warning(disable: 4710)
// identifier was truncated in the debug information
#pragma warning(disable: 4786)

// C4996: function or variable may be unsafe
#define _CRT_SECURE_NO_WARNINGS

//////////////////////////////////////////////////////////////////////////////////////////////
// use WinXP/IE6 features

#define WINVER 0x0501
#define _WIN32_WINDOWS 0x0500
#define _WIN32_IE 0x0600
#define _WIN32_WINNT 0x0501

//////////////////////////////////////////////////////////////////////////////////////////////
// prevent automatic CRT/STL/MFC/ATL manifest dependencies generation

// see http://www.codeproject.com/KB/cpp/PrivateAssemblyProjects.aspx and
// http://blog.m-ri.de/index.php/2008/05/06/hotfix-fuer-usemsprivateassembliesh-und-vc-2008/
// by by Martin Richter for more information

#define _CRT_NOFORCE_MANIFEST
#define _STL_NOFORCE_MANIFEST
#define _AFX_NOFORCE_MANIFEST
#define _ATL_NOFORCE_MANIFEST

#ifdef __cplusplus
extern "C"
{
#endif

__declspec(selectany) int _forceCRTManifest;
__declspec(selectany) int _forceMFCManifest;
__declspec(selectany) int _forceAtlDllManifest;

// the next symbols are used by the several versions of VC++ 2008 (9.0)
__declspec(selectany) int _forceCRTManifestRTM;
__declspec(selectany) int _forceMFCManifestRTM;
__declspec(selectany) int _forceMFCManifestCUR;

#ifdef __cplusplus
}   // extern "C"
#endif

//////////////////////////////////////////////////////////////////////////////////////////////
// PSDK headers

#define WIN32_LEAN_AND_MEAN   // exclude rarely-used stuff from Windows headers

#include <windows.h>

//////////////////////////////////////////////////////////////////////////////////////////////
// CRT headers

#include <crtdbg.h>

//////////////////////////////////////////////////////////////////////////////////////////////
// some tricks

#if !defined(_countof)
#define _countof(array) (sizeof(array) / sizeof(array[0]))
#endif   // _countof

// force ISO/IEC 14882 conformance in for loop scope
#if (_MSC_VER < 1300)
#define for if (false); else for
#else
#pragma conform(forScope, on)
#endif   // _MSC_VER

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__CBB777D4_541B_4A75_BE5D_0E67D4C9E96A__INCLUDED_)
