// Crypto++DLL dynamic-link library.
// Copyright (c) 1995-2009 by Wei Dai,
// All rights reserved.

// pch.h - include file for standard system include files

// initially generated by AfxScratch v1.1.4778 on 06.06.2009 at 12:08:32
// visit http://zarezky.spb.ru/projects/afx_scratch.html for more info

#if !defined(__pch_h)
#define __pch_h

#if defined(_MSC_VER) && (_MSC_VER > 1000)
#pragma once
#endif   // _MSC_VER

//////////////////////////////////////////////////////////////////////////////////////////////
// unwanted warnings

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

//////////////////////////////////////////////////////////////////////////////////////////////
// use NT4/IE6 features

#define WINVER 0x0400
#define _WIN32_WINDOWS 0x0400
#define _WIN32_IE 0x0600
#define _WIN32_WINNT 0x0400

//////////////////////////////////////////////////////////////////////////////////////////////
// remove automatic CRT/MFC dependencies generation

#if defined(_LIB) || defined(CRYPTOPP_PRIVATE_CRT)

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

#endif   // _LIB || CRYPTOPP_PRIVATE_CRT

//////////////////////////////////////////////////////////////////////////////////////////////
// PSDK headers

// prevent inclusion of winsock.h in windows.h
#define _WINSOCKAPI_

#define NOMINMAX

#include <windows.h>
#include <wincrypt.h>
#include <winsock2.h>

//////////////////////////////////////////////////////////////////////////////////////////////
// CRT headers

#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_NON_CONFORMING_SWPRINTFS

#include <tchar.h>
#include <time.h>
#include <ctype.h>
#include <math.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

//////////////////////////////////////////////////////////////////////////////////////////////
// STL headers

#include <vector>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <memory>
#include <limits>
#include <functional>
#include <new>
#include <sstream>
#include <map>
#include <list>
#include <fstream>
#include <deque>
#include <iosfwd>
#include <string>
#include <exception>
#include <typeinfo>

//////////////////////////////////////////////////////////////////////////////////////////////
// ATL headers

#define _ATL_NO_COM_SUPPORT
#define _ATL_NO_HOSTING
#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS
#define _ATL_NO_AUTOMATIC_NAMESPACE

#define _SECURE_ATL 1

#include <atlbase.h>
#include <atlconv.h>

//////////////////////////////////////////////////////////////////////////////////////////////
// Crypto++ headers

#if defined(CRYPTOPP_GENERATE_X64_MASM)

#include "cpu.h"

#else
// !CRYPTOPP_GENERATE_X64_MASM

#include "config.h"

#if defined(USE_PRECOMPILED_HEADERS)
#include "simple.h"
#include "secblock.h"
#include "misc.h"
#include "smartptr.h"
#endif   // USE_PRECOMPILED_HEADERS

#endif   // CRYPTOPP_GENERATE_X64_MASM

//////////////////////////////////////////////////////////////////////////////////////////////
// some tricks

// force ISO/IEC 14882 conformance in for loop scope
#if (_MSC_VER < 1300)
#define for if (false); else for
#else
#pragma conform(forScope, on)
#endif   // _MSC_VER

#endif   // __pch_h

// end of file
