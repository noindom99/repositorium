////////////////////////////////////////////////////////////////////////////////
// This source file is part of the ZipArchive library source distribution and
// is Copyrighted 2000 - 2007 by Artpol Software - Tadeusz Dracz
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

#include "stdafx.h"
#include "_platform.h"
#include "ZipPlatform.h"
#include "ZipFileHeader.h"
#include "ZipException.h"
#include "ZipAutoBuffer.h"
#include <sys/stat.h>

#ifdef ZIP_ARCHIVE_WIN

#define ZIP_USES_SAFE_WINDOWS_API

#ifndef __BORLANDC__
        #include <sys/utime.h>
#else
	#ifndef _UTIMBUF_DEFINED
		#define _utimbuf utimbuf
		#define _UTIMBUF_DEFINED
	#endif
        #include <utime.h>
#endif

#ifndef INVALID_FILE_ATTRIBUTES
	#define INVALID_FILE_ATTRIBUTES ((DWORD)-1)
#endif

#include <direct.h>
#include <io.h>
#include <time.h> 
#include "ZipPathComponent.h"
#include "ZipCompatibility.h"

const TCHAR CZipPathComponent::m_cSeparator = _T('\\');

ULONGLONG ZipPlatform::GetDeviceFreeSpace(LPCTSTR lpszPath)
{
	ULONGLONG uFreeBytesToCaller = 0, uTotalBytes = 0, uFreeBytes = 0;

	CZipPathComponent zpc (lpszPath);
	CZipString szDrive = zpc.GetFileDrive();

	if (!GetDiskFreeSpaceEx(
		szDrive,
		(PULARGE_INTEGER)&uFreeBytesToCaller,
		(PULARGE_INTEGER)&uTotalBytes,
        (PULARGE_INTEGER)&uFreeBytes))

	{
		CZipPathComponent::AppendSeparator(szDrive); // in spite of what is written in MSDN it is sometimes needed (on fixed disks)
		if (!GetDiskFreeSpaceEx(
			szDrive,
			(PULARGE_INTEGER)&uFreeBytesToCaller,
			(PULARGE_INTEGER)&uTotalBytes,
			(PULARGE_INTEGER)&uFreeBytes))	
				return 0;
	}
	return uFreeBytes;
}

CZipString ZipPlatform::GetTmpFileName(LPCTSTR lpszPath, ZIP_SIZE_TYPE uSizeNeeded)
{
		TCHAR empty[] = _T("");
		CZipString tempPath;
		bool bCheckTemp = true;
		if (lpszPath)
		{
			tempPath = lpszPath;
			bCheckTemp = GetDeviceFreeSpace(tempPath) < uSizeNeeded;

		}
		if (bCheckTemp)
		{
			DWORD size = GetTempPath(0, empty);
			if (size == 0)
				return (CZipString)empty;
		
			GetTempPath(size, tempPath.GetBuffer(size));
			tempPath.ReleaseBuffer();
			if (GetDeviceFreeSpace(tempPath) < uSizeNeeded)
			{
				if (!GetCurrentDirectory(tempPath) || GetDeviceFreeSpace(tempPath) < uSizeNeeded)
					return (CZipString)empty;
			}
		}
		CZipString tempName;
		if (!GetTempFileName(tempPath, _T("ZAR"), 0, tempName.GetBuffer(_MAX_PATH)))
			return (CZipString)empty;
		tempName.ReleaseBuffer();
		return tempName;
}


bool ZipPlatform::GetCurrentDirectory(CZipString& sz)
{
	DWORD i = ::GetCurrentDirectory(0, NULL);
	if (!i)
		return false;
	TCHAR* pBuf = new TCHAR[i];
	bool b = true;
	if (!::GetCurrentDirectory(i, pBuf))
		b = false;
	else
		sz = pBuf;
	delete[] pBuf;
	return b;
}

bool ZipPlatform::SetFileAttr(LPCTSTR lpFileName, DWORD uAttr)
{
	return ::SetFileAttributes(lpFileName, uAttr) != 0;
}

bool ZipPlatform::GetFileAttr(LPCTSTR lpFileName, DWORD& uAttr)
{
	// not using MFC due to MFC bug (attr is one byte there)
	DWORD temp = ::GetFileAttributes(lpFileName);
	if (temp == INVALID_FILE_ATTRIBUTES)
		return false;
	uAttr = temp;
	return true;
	
}

bool ZipPlatform::GetFileModTime(LPCTSTR lpFileName, time_t & ttime)
{
#ifndef __BORLANDC__
    struct _stat st;
    if (_tstat(lpFileName, &st) != 0)
#else
    struct stat st;
    if (stat(lpFileName, &st) != 0)
#endif
	return false;
	ttime = st.st_mtime;
	if (ttime == (time_t)-1)
	{
		ttime = time(NULL);
		return false;
	}
	else
		return true;
}

bool ZipPlatform::SetFileModTime(LPCTSTR lpFileName, time_t ttime)
{
	struct _utimbuf ub;
	ub.actime = time(NULL);
	ub.modtime = ttime == -1 ? time(NULL) : ttime; // if wrong file time, set it to the current
	return _tutime(lpFileName, &ub) == 0;
}

bool ZipPlatform::ChangeDirectory(LPCTSTR lpDirectory)
{
	return _tchdir(lpDirectory) == 0; // returns 0 if ok
}

int ZipPlatform::FileExists(LPCTSTR lpszName)
{
#ifndef __BORLANDC__
	#if _MSC_VER >= 1400
	if (_taccess_s(lpszName, 0) == 0)
	#else
	if (_taccess(lpszName, 0) == 0)
	#endif
#else
	#ifdef _UNICODE
	if (_waccess(lpszName, 0) == 0)
	#else
	if (access(lpszName, 0) == 0)
	#endif
#endif
	{
		if (DirectoryExists(lpszName))
			return -1;
		return 1;
	}
	else
		return 0;

}

ZIPINLINE  bool ZipPlatform::IsDriveRemovable(LPCTSTR lpszFilePath)
{
	CZipPathComponent zpc(lpszFilePath);
	return ::GetDriveType(zpc.GetFileDrive()) == DRIVE_REMOVABLE;
}

ZIPINLINE  bool ZipPlatform::SetVolLabel(LPCTSTR lpszPath, LPCTSTR lpszLabel)
{
	CZipPathComponent zpc(lpszPath);
	CZipString szDrive = zpc.GetFileDrive();
	CZipPathComponent::AppendSeparator(szDrive);
	return ::SetVolumeLabel(szDrive, lpszLabel) != 0;
}

ZIPINLINE void ZipPlatform::AnsiOem(CZipAutoBuffer& buffer, bool bAnsiToOem)
{
#ifdef ZIP_USES_SAFE_WINDOWS_API
	UINT cpIn, cpOut;
	if (bAnsiToOem)
	{
		cpIn = CP_ACP;
		cpOut = CP_OEMCP;
	}
	else
	{
		cpIn = CP_OEMCP;
		cpOut = CP_ACP;
	}

	CZipAutoBuffer interBuffer;

	int size = buffer.GetSize();
	// iLen doesn't include terminating character
	int iLen = MultiByteToWideChar(cpIn, MB_PRECOMPOSED, buffer, size, NULL, 0);
	if (iLen <= 0)
		return;
	interBuffer.Allocate(iLen * sizeof(wchar_t));
	LPWSTR lpszWide = (LPWSTR)(char*)interBuffer;
	iLen = MultiByteToWideChar(cpIn, MB_PRECOMPOSED, buffer, size, lpszWide, iLen);
	ASSERT(iLen != 0);

	// iLen does not include terminating character
	size = WideCharToMultiByte(cpOut, 0, lpszWide, iLen, NULL, 0, NULL, NULL);
	if (size <= 0)
		return;
	buffer.Allocate(size);
	size = WideCharToMultiByte(cpOut, 0, lpszWide, iLen, buffer, size, NULL, NULL);
	ASSERT(size != 0);
#else
	if (bAnsiToOem)
		CharToOemBuffA(buffer, buffer, buffer.GetSize());
	else
		OemToCharBuffA(buffer, buffer, buffer.GetSize());
#endif
}

ZIPINLINE  bool ZipPlatform::RemoveFile(LPCTSTR lpszFileName, bool bThrow)
{
	if (!::DeleteFile((LPTSTR)lpszFileName))
		if (bThrow)
			CZipException::Throw(CZipException::notRemoved, lpszFileName);
		else 
			return false;
	return true;

}
ZIPINLINE  bool ZipPlatform::RenameFile( LPCTSTR lpszOldName, LPCTSTR lpszNewName, bool bThrow)
{
	if (!::MoveFile((LPTSTR)lpszOldName, (LPTSTR)lpszNewName))
		if (bThrow)
			CZipException::Throw(CZipException::notRenamed, lpszOldName);
		else 
			return false;
	return true;

}

ZIPINLINE  bool ZipPlatform::IsDirectory(DWORD uAttr)
{
	return (uAttr & FILE_ATTRIBUTE_DIRECTORY) != 0;
}

ZIPINLINE  bool ZipPlatform::CreateDirectory(LPCTSTR lpDirectory)
{
	return ::CreateDirectory(lpDirectory, NULL) != 0;
}

ZIPINLINE  DWORD ZipPlatform::GetDefaultAttributes()
{
	return FILE_ATTRIBUTE_ARCHIVE;
}

ZIPINLINE  DWORD ZipPlatform::GetDefaultDirAttributes()
{
	return FILE_ATTRIBUTE_DIRECTORY;
}

ZIPINLINE  int ZipPlatform::GetSystemID()
{
	return ZipCompatibility::zcDosFat;
}

ZIPINLINE bool ZipPlatform::GetSystemCaseSensitivity()
{
	return false;
}

#ifdef _UNICODE	
int ZipPlatform::WideToMultiByte(LPCWSTR lpszIn, CZipAutoBuffer &szOut, UINT uCodePage)
{
	size_t wideLen = wcslen(lpszIn);
	if (wideLen == 0)
	{
		szOut.Release();
		return 0;
	}

	// iLen does not include terminating character
	int iLen = WideCharToMultiByte(uCodePage, 0, lpszIn, (int)wideLen, szOut, 
		0, NULL, NULL);
	if (iLen > 0)
	{
		szOut.Allocate(iLen, true);
		iLen = WideCharToMultiByte(uCodePage, 0, lpszIn , (int)wideLen, szOut, 
			iLen, NULL, NULL);
		ASSERT(iLen != 0);
	}
	else // here it means error
	{
		szOut.Release();
		iLen --;
	}
	return iLen;

}
int ZipPlatform::MultiByteToWide(const CZipAutoBuffer &szIn, CZipString& szOut, UINT uCodePage)
{
	int singleLen = szIn.GetSize();
	// iLen doesn't include terminating character
	DWORD dwFlags = uCodePage <= CP_OEMCP ? MB_PRECOMPOSED : 0;
	int iLen = MultiByteToWideChar(uCodePage, dwFlags, szIn.GetBuffer(), singleLen, NULL, 0);
	if (iLen > 0)
	{
		iLen = MultiByteToWideChar(uCodePage, dwFlags, szIn.GetBuffer(), singleLen, 
			szOut.GetBuffer(iLen) , iLen);
		szOut.ReleaseBuffer(iLen);
		ASSERT(iLen != 0);
	}
	else
	{
		szOut.Empty();
		iLen --; // return -1
	}
	return iLen;
}
#endif

#if defined ZIP_ARCHIVE_STL || defined ZIP_FILE_USES_STL

#if _MSC_VER > 1000
	#pragma warning( push )
	#pragma warning (disable : 4702) // unreachable code
#endif


#include <io.h>
#include <share.h>
bool ZipPlatform::TruncateFile(int iDes, ULONGLONG uSize)
{	
#if (_MSC_VER >= 1400)
	return _chsize_s(iDes, uSize) == 0;
#else
	if (uSize <= LONG_MAX)
		return chsize(iDes, (LONG)uSize) == 0;
	else if (uSize > _I64_MAX)
		CZipException::Throw(CZipException::tooBigSize);
	else
	{
		HANDLE handle = (HANDLE)GetFileSystemHandle(iDes);
		ULARGE_INTEGER li;
		li.QuadPart = uSize;
		li.LowPart = SetFilePointer(handle, li.LowPart, (LONG*)&li.HighPart, FILE_BEGIN);
		if (li.LowPart == UINT_MAX && GetLastError() != NO_ERROR)
			return false;
		return SetEndOfFile(handle) != 0;
	}
	return false; // for the compiler
#endif

}

#if _MSC_VER > 1000
	#pragma warning( pop )
#endif


int ZipPlatform::OpenFile(LPCTSTR lpszFileName, UINT iMode, int iShareMode)
{
	switch (iShareMode)
	{
	case (CZipFile::shareDenyWrite & CZipFile::shareDenyRead):
		iShareMode = SH_DENYRW;
		break;
	case (CZipFile::shareDenyRead):
		iShareMode = SH_DENYRD;
		break;
	case (CZipFile::shareDenyWrite):
		iShareMode = SH_DENYWR;
		break;
	default:
		iShareMode = SH_DENYNO;
	}
#if _MSC_VER >= 1400	
	int handle;
	if (_tsopen_s(&handle, lpszFileName, iMode, iShareMode, S_IREAD | S_IWRITE /*required only when O_CREAT mode*/) != 0)
		return -1;
	else
		return handle;
#else
	return  _tsopen(lpszFileName, iMode, iShareMode, S_IREAD | S_IWRITE /*required only when O_CREAT mode*/);
#endif
	
}

bool ZipPlatform::FlushFile(int iDes)
{
	return _commit(iDes) == 0;
}

intptr_t ZipPlatform::GetFileSystemHandle(int iDes)
{
	return _get_osfhandle(iDes);
}


#endif // ZIP_ARCHIVE_STL || ZIP_FILE_USES_STL

#endif // ZIP_ARCHIVE_WIN
