////////////////////////////////////////////////////////////////////////////////
// This source file is part of the ZipArchive library source distribution and
// is Copyrighted 2000 - 2012 by Artpol Software - Tadeusz Dracz
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// For the licensing details refer to the License.txt file.
//
// Web Site: http://www.artpol-software.com
////////////////////////////////////////////////////////////////////////////////
// Modified by Elijah Zarezky aka SchweinDeBurg (elijah.zarezky@gmail.com):
// - reformatted using Artistic Style 2.02 with the following options:
//      --indent=tab=3
//      --indent=force-tab=3
//      --indent-cases
//      --min-conditional-indent=0
//      --max-instatement-indent=2
//      --style=allman
//      --add-brackets
//      --pad-oper
//      --unpad-paren
//      --pad-header
//      --align-pointer=type
//      --lineend=windows
//      --suffix=none
// - implemented support for the Windows Mobile/CE tragets
// - added possibility to seamless usage in the ATL-based projects
////////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZipMemFile.h"
#include "Private/ZipException.h"

#if defined(__INTEL_COMPILER)
// warning #186: pointless comparison of unsigned integer with zero
#pragma warning(disable: 186)
#endif	// __INTEL_COMPILER

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

#if defined _ZIP_IMPL_MFC && (_MSC_VER >= 1300 || _ZIP_FILE_IMPLEMENTATION != ZIP_ZFI_WIN)
IMPLEMENT_DYNAMIC(CZipMemFile, CFile)
#endif

void CZipMemFile::Grow(size_t nGrowTo)
{
	if (m_nBufSize < (UINT)nGrowTo)
	{
		if (m_nGrowBy == 0)
		{
			CZipException::Throw(CZipException::memError);
		}
		size_t nNewSize = m_nBufSize;
		while (nNewSize < nGrowTo)
		{
			nNewSize += m_nGrowBy;
		}
		BYTE* lpNew;
		if (m_lpBuf)
		{
			lpNew = (BYTE*)realloc((void*) m_lpBuf, nNewSize);
		}
		else
		{
			lpNew = (BYTE*)malloc(nNewSize);
		}

		if (!lpNew)
		{
			CZipException::Throw(CZipException::memError);
		}
		m_nBufSize = nNewSize;
		m_lpBuf = lpNew;
	}
}

void CZipMemFile::SetLength(ZIP_FILE_USIZE nNewLen)
{
	if (m_nBufSize < (size_t)nNewLen)
	{
		Grow((size_t)nNewLen);
	}
	else
	{
		m_nPos = (size_t)nNewLen;
	}
	m_nDataSize = (size_t)nNewLen;
}

UINT CZipMemFile::Read(void* lpBuf, UINT nCount)
{
	if (m_nPos >= m_nDataSize)
	{
		return 0;
	}
	UINT nToRead = (m_nPos + nCount > m_nDataSize) ? (UINT)(m_nDataSize - m_nPos) : nCount;
	memcpy(lpBuf, m_lpBuf + m_nPos, nToRead);
	m_nPos += nToRead;
	return nToRead;

}

void CZipMemFile::Write(const void* lpBuf, UINT nCount)
{
	if (!nCount)
	{
		return;
	}

	if (m_nPos + nCount > m_nBufSize)
	{
		Grow(m_nPos + nCount);
	}
	memcpy(m_lpBuf + m_nPos, lpBuf, nCount);
	m_nPos += nCount;
	if (m_nPos > m_nDataSize)
	{
		m_nDataSize = m_nPos;
	}
}
ZIP_FILE_USIZE CZipMemFile::Seek(ZIP_FILE_SIZE lOff, int nFrom)
{
	ZIP_FILE_USIZE lNew = m_nPos;

	if (nFrom == CZipAbstractFile::begin)
	{
		if (lOff < 0)
		{
			CZipException::Throw(CZipException::memError);
		}
		lNew = lOff;
	}
	else if (nFrom == CZipAbstractFile::current)
	{
		if (lOff < 0 && (ZIP_FILE_USIZE)(-lOff) > lNew)
		{
			CZipException::Throw(CZipException::memError);
		}
		lNew += lOff;
	}
	else if (nFrom == CZipAbstractFile::end)
	{
		if (lOff < 0 && ZIP_FILE_USIZE(-lOff) > m_nDataSize)
		{
			CZipException::Throw(CZipException::memError);
		}
		lNew = m_nDataSize + lOff;
	}
	else
	{
		return lNew;
	}

	// assumption that size_t is always signed
	if (lNew > (size_t)(-1)) // max of size_t
	{
		CZipException::Throw(CZipException::memError);
	}
	if (lNew > m_nDataSize)
	{
		Grow((size_t)lNew);
	}

	m_nPos = (size_t)lNew;
	return lNew;
}
