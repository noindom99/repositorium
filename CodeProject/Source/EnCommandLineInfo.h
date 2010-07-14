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

// EnCommandLineInfo.h: interface for the CEnCommandLineInfo class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ENCOMMANDLINEINFO_H__71F4DB4E_3B2B_4F6A_B80F_0BB288E68335__INCLUDED_)
#define AFX_ENCOMMANDLINEINFO_H__71F4DB4E_3B2B_4F6A_B80F_0BB288E68335__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CEnCommandLineInfo : public CCommandLineInfo  
{
public:
	CEnCommandLineInfo();
	virtual ~CEnCommandLineInfo();

	BOOL HasOption(LPCTSTR szFlag) const; 
	BOOL GetOption(LPCTSTR szFlag, CStringArray& aParams) const; 
	BOOL GetOption(LPCTSTR szFlag, CString& sParam) const; 
	CString GetOption(LPCTSTR szFlag) const; 

	void DeleteOption(LPCTSTR szFlag);

	BOOL SetOption(LPCTSTR szFlag, LPCTSTR szParam); 
	BOOL SetOption(LPCTSTR szFlag, DWORD dwParam); 

	static CString ResolveShortcut(LPCTSTR szShortcut);

protected:
	CMapStringToString m_mapCommandLine;
	CString m_sLastOption;
	int m_nLastParameter;

protected:
	virtual void ParseParam(LPCTSTR lpszParam, BOOL bFlag, BOOL bLast);


};

#endif // !defined(AFX_ENCOMMANDLINEINFO_H__71F4DB4E_3B2B_4F6A_B80F_0BB288E68335__INCLUDED_)