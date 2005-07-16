// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently

#if !defined(AFX_STDAFX_H__483FB9A9_908F_4150_90A7_4EEAF73AD80C__INCLUDED_)
#define AFX_STDAFX_H__483FB9A9_908F_4150_90A7_4EEAF73AD80C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// unreferenced inline/local function has been removed
#pragma warning(disable: 4514)
// function not inlined
#pragma warning(disable: 4710)
// identifier was truncated in the debug information
#pragma warning(disable: 4786)

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

// MFC headers
#include <afxwin.h>		// MFC core and standard components
#include <afxtempl.h>
#include <afxsock.h>
#include <afxpriv.h>

// PSDK headers
#include <wininet.h>
#include <windns.h>		// DNS definitions and DNS API
#include <wincrypt.h>	// cryptographic API prototypes and definitions

// STL headers
#pragma warning(push, 3)
#include <string>
#include <algorithm>
#pragma warning(pop)

#if !defined(_STRING_)
#define _STRING_			// for compatibility with Dinkumware STL
#endif

#if !defined(min)
using std::min;
#endif	// min

#if !defined(max)
using std::max;
#endif	// max

// CRT headers
#include <locale.h>

#pragma hdrstop

// force ISO/IEC 14882 conformance in for loop scope
#if (_MSC_VER < 1300)
#define for if (false); else for
#else
#pragma conform(forScope, on)
#endif	// _MSC_VER

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__483FB9A9_908F_4150_90A7_4EEAF73AD80C__INCLUDED_)
