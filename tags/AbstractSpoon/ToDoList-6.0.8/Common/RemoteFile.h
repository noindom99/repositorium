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

// RemoteFile.h: interface for the CRemoteFile class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_REMOTEFILE_H__04648C98_565F_41B2_A1F7_E10E00800691__INCLUDED_)
#define AFX_REMOTEFILE_H__04648C98_565F_41B2_A1F7_E10E00800691__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "RemoteFileDialog.h"
#include <afxinet.h>

enum RMERR
{
	RMERR_SUCCESS,
	RMERR_UNKNOWN,
	RMERR_SERVERDETAILS,
	RMERR_REMOTEPATH,
	RMERR_LOCALPATH,
	RMERR_OPENINGREMOTEFILETOREAD,
	RMERR_OPENINGREMOTEFILETOWRITE,
	RMERR_OPENINGLOCALFILETOREAD,
	RMERR_OPENINGLOCALFILETOWRITE,
	RMERR_CONNECTING,
	RMERR_USERCANCELLED,
	RMERR_NOTCONNECTED,
	RMERR_READINGREMOTEFILE,
	RMERR_READINGLOCALFILE,
	RMERR_WRITINGREMOTEFILE,
	RMERR_WRITINGLOCALFILE,
	//	RMERR_,
};

enum // options
{
	RMO_ALLOWDIALOG			= 0x00000001,
	RMO_USETEMPFILE			= 0x00000002, // only valid for download
	RMO_KEEPEXTENSION		= 0x00000004, // only valid if RMO_USETEMPFILE is specified
	RMO_LOWERCASEPATHS		= 0x00000008,
	RMO_DELETEFAILURES		= 0x00000010,
	RMO_CREATEDOWNLOADDIR	= 0x00000020, // if not already there
	RMO_ANONYMOUSLOGIN		= 0x00000040,
	RMO_CONFIRMOVERWRITE	= 0x00000080,
	RMO_NONAVIGATE			= 0x00000100, // restricts browsing away from the initial folder
	RMO_NOANONYMOUSLOGIN	= 0x00000200, // prevents anonymous logins and hides the checkbox on the server dialog
	RMO_NOPROGRESS			= 0x00000400, // prevents appearance of progress dialog
	RMO_PRESERVESTRUCTURE	= 0x00000800,
	RMO_SUBDIRECTORIES		= 0x00001000, // parses sub dirs when using a wildcard for uploading
	RMO_NOCANCELPROGRESS	= 0x00002000,
	RMO_MULTISELECT			= 0x00004000,
	/*	RMO_ = 0x0001,
	RMO_ = 0x0001,
	*/


	RMO_DEFGETFILE			= RMO_ALLOWDIALOG | RMO_CREATEDOWNLOADDIR | RMO_CONFIRMOVERWRITE | RMO_MULTISELECT,
	RMO_DEFSETFILE			= RMO_ALLOWDIALOG | RMO_LOWERCASEPATHS | RMO_DELETEFAILURES | RMO_CONFIRMOVERWRITE,
};

// note: if you don't need the browse capabilities then you can #define NO_DIALOGS
// in which case you must pass in correct parameters to avoid failure

// note: file filter takes standard form: eg. "Zip Files (*.zip)|*.zip||"

class CProgressDlg;
struct FILERESULT;

class CRemoteFile : protected CInternetSession
{
public:
	CRemoteFile(LPCTSTR szAgent = NULL, LPCTSTR szServer = NULL, LPCTSTR szUsername = NULL, LPCTSTR szPassword = NULL, CWnd* pParent = NULL);
	virtual ~CRemoteFile();

	// sRemoteFile is always sans server eg 'abstractspoon\test.htm'

	// both sRemotePath and sLocalPath may reference folders in both GetFile() and SetFile()

	// if sRemotePath is a folder then it must have a trailing forward slash '/'
	// if sLocalPath is a folder that exists then it need not have a trailing backslash '\'
	// however if it might not exist and you want it created then append a trailing backslash

	RMERR GetFile(CString& sRemotePath, CString& sLocalPath, DWORD dwOptions = RMO_DEFGETFILE, LPCTSTR szFilter = NULL);
	RMERR SetFile(CString& sLocalPath, CString& sRemotePath, DWORD dwOptions = RMO_DEFSETFILE);

	CString GetServer() { return m_sServer; }
	CString GetUsername() { return m_sUsername; }
	CString GetPassword() { return m_sPassword; }
	CString GetLastError() { return m_sLastError; }

	static void SplitPath(LPCTSTR szFullRemotePath, CString& sServer, CString& sFile);

protected:
	CString m_sServer, m_sUsername, m_sPassword;
	CString m_sRemotePath, m_sLocalPath;
	CFtpConnection* m_pConnection;
	DWORD m_dwInternetErr;
	CWnd* m_pParent;
	CString m_sLastError;

protected:
	BOOL EstablishConnection(RMERR& nRes, DWORD dwOptions);
	BOOL DoServerDlg(DWORD dwOptions, BOOL& bAnonLogin); // returns TRUE for IDOK else FALSE (cancel)
	void CloseConnection();

	RMERR DownloadFile(const FILERESULT* pRemoteFile, LPCTSTR szToLocalPath, DWORD dwOptions, CProgressDlg* pDlg = NULL);
	RMERR UploadFile(LPCTSTR szFromLocalPath, const FILERESULT* pRemoteFile, DWORD dwOptions, CProgressDlg* pDlg = NULL);

	void ValidateOptions(DWORD& dwOptions, BOOL bDownload);
	RMERR SaveErrorMsg(RMERR nErr, LPCTSTR szRemotePath = NULL, LPCTSTR szLocalPath = NULL); // returns nErr to allow chaining
	DWORD GetRemoteFileSize(LPCTSTR szRemotePath);

	RMERR GetRemotePaths(CFRArray& aRemoteFiles, const CStringArray& aLocalFiles,
		DWORD dwOptions, LPCTSTR szRemoteDir = NULL, LPCTSTR szLocalRoot = NULL); // for upload
	RMERR GetRemotePaths(CFRArray& aRemoteFiles, DWORD dwOptions, LPCTSTR szFilter, LPCTSTR szRemoteDir = NULL); // for download

	RMERR GetLocalPaths(CStringArray& aLocalFiles, BOOL& bTemp, const CFRArray& aRemoteFiles,
		DWORD dwOptions, LPCTSTR szLocalDir = NULL); // for download
	RMERR GetLocalPaths(CStringArray& aLocalFiles, DWORD dwOptions, LPCTSTR szLocalDir = NULL); // for upload

	CString GetTempPath(const CString& sRemotePath, BOOL bKeepExt);
	BOOL RemoteFileExists(LPCTSTR szRemotePath);

	static BOOL ValidateLocalFolder(CString& sFolder, BOOL bAllowCreation);
	static BOOL RemotePathIsFolder(const CString& sFolder);
	static void DoProgress(CProgressDlg* pDlg, DWORD dwBytesRead, DWORD dwFileSize, BOOL bUpload);
	static CString MakeRemotePath(const CString& sLocalPath, const CString& sRemoteDir, const TCHAR* szLocalRoot);
};

#endif // !defined(AFX_REMOTEFILE_H__04648C98_565F_41B2_A1F7_E10E00800691__INCLUDED_)