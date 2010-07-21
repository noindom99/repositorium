// Copyright (C) 2003-2005 AbstractSpoon Software.
//
// This license applies to everything in the ToDoList package, except where
// otherwise noted.
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the
// use of this software. 
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented; you must not
// claim that you wrote the original software. If you use this software in a
// product, an acknowledgment in the product documentation would be appreciated
// but is not required.
//
// 2. Altered source versions must be plainly marked as such, and must not be
// misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.

//*****************************************************************************
// Modified by Elijah Zarezky aka SchweinDeBurg (elijah.zarezky@gmail.com):
// - improved compatibility with the Unicode-based builds
// - added AbstractSpoon Software copyright notice and licenese information
// - adjusted #include's paths
//*****************************************************************************

// StdAfx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__BEB85A7E_10B8_410B_BC4B_56649653A624__INCLUDED_)
#define AFX_STDAFX_H__BEB85A7E_10B8_410B_BC4B_56649653A624__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//////////////////////////////////////////////////////////////////////////////////////////////
// unwanted warnings

// nonstandard extension used : conversion from 'type' to 'type'
#pragma warning(disable: 4239)
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
// remove automatic CRT/MFC dependencies generation

// see http://www.codeproject.com/KB/cpp/PrivateAssemblyProjects.aspx and
// http://blog.m-ri.de/index.php/2008/05/06/hotfix-fuer-usemsprivateassembliesh-und-vc-2008/
// by by Martin Richter for more information

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

//////////////////////////////////////////////////////////////////////////////////////////////
// MFC headers

#if (_MSC_VER >= 1300)
#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS
#endif	// _MSC_VER

#include <afxwin.h>        // MFC core and standard components
#include <afxcmn.h>        // MFC common control classes
#include <afxtempl.h>      // MFC collection template classes
#include <afxdtctl.h>      // MFC date/time control classes
#include <afxext.h>        // MFC extensions and customizable classes
#include <afxpriv.h>       // MFC private classes
#include <afxinet.h>       // MFC support for WinInet
#include <afxole.h>        // MFC OLE support
#include <afxdisp.h>       // MFC IDispatch & ClassFactory support
#include <afxadv.h>        // MFC Advanced Classes

//////////////////////////////////////////////////////////////////////////////////////////////
// PSDK headers

#include <shlwapi.h>       // light-weight utility APIs
#include <multimon.h>      // stub module that fakes multiple monitor APIs
#include <mmsystem.h>      // multimedia APIs
#include <lmcons.h>        // LAN manager APIs

//////////////////////////////////////////////////////////////////////////////////////////////
// CRT headers

#include <math.h>          // math library
#include <locale.h>        // localization routines
#include <float.h>         // constants for floating point values
#include <direct.h>        // directory handling/creation

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

#endif // !defined(AFX_STDAFX_H__BEB85A7E_10B8_410B_BC4B_56649653A624__INCLUDED_)