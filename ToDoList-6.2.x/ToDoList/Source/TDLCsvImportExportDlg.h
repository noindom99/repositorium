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
// - added AbstractSpoon Software copyright notice and license information
// - adjusted #include's paths
// - reformatted using Artistic Style 2.02 with the following options:
//      --indent=tab=3
//      --indent=force-tab=3
//      --indent-cases
//      --max-instatement-indent=2
//      --style=allman
//      --add-brackets
//      --pad-oper
//      --unpad-paren
//      --pad-header
//      --align-pointer=type
//      --lineend=windows
//      --suffix=none
// - merged with ToDoList version 6.2.2 sources
//*****************************************************************************

#if !defined(AFX_TDLCSVIMPORTEXPORTDLG_H__3230FA12_9619_426A_9D8A_FC4D76A56596__INCLUDED_)
#define AFX_TDLCSVIMPORTEXPORTDLG_H__3230FA12_9619_426A_9D8A_FC4D76A56596__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TDLCsvImportExportDlg.h : header file
//

#include "TDLCsvAttributeSetupListCtrl.h"

#include "../../Common/FileEdit.h"

/////////////////////////////////////////////////////////////////////////////
// CTDLCsvImportExportDlg dialog

class CTDLCsvImportExportDlg : public CDialog
{
// Construction
public:
	CTDLCsvImportExportDlg(const CString& sFilePath, CWnd* pParent = NULL);   // import constructor
	CTDLCsvImportExportDlg(const CString& sFilePath, const CTDCAttributeArray& aExportAttributes, CWnd* pParent = NULL);   // export constructor

	int GetColumnMapping(CTDCCsvColumnMapping& aMapping) const;
	CString GetDelimiter() const
	{
		return m_sDelim;
	}

protected:
// Dialog Data
	//{{AFX_DATA(CTDLCsvImportExportDlg)
	CString	m_sDelim;
	CString	m_sFilePath;
	BOOL	m_bAlwaysExportTaskIDs;
	//}}AFX_DATA
	CFileEdit	m_eFilePath;
	CTDLCsvAttributeSetupListCtrl m_lcColumnSetup;
	BOOL m_bImporting;
	CTDCCsvColumnMapping m_aMasterColumnMapping;
	CTDCAttributeArray m_aExportAttributes;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTDLCsvImportExportDlg)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTDLCsvImportExportDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnChangeCsvdelimiter();
	afx_msg void OnExportTaskids();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	virtual void OnOK();

protected:
	int BuildImportColumnMapping(CTDCCsvColumnMapping& aImportMapping) const;
	int BuildExportColumnMapping(CTDCCsvColumnMapping& aExportMapping) const;

	void BuildDefaultMasterColumnMapping();
	void UpdateMasterColumnMappingFromList();

	int FindMasterColumn(TDC_ATTRIBUTE attrib) const;
	CString GetMasterColumnName(TDC_ATTRIBUTE attrib) const;
	void SetMasterColumnName(TDC_ATTRIBUTE attrib, LPCTSTR szColumn);

	int FindMasterColumn(LPCTSTR szColumn) const;
	TDC_ATTRIBUTE GetMasterColumnAttribute(LPCTSTR szColumn) const;
	void SetMasterColumnAttribute(LPCTSTR szColumn, TDC_ATTRIBUTE attrib);

	int LoadMasterColumnMapping();
	void SaveMasterColumnMapping() const;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TDLCSVIMPORTEXPORTDLG_H__3230FA12_9619_426A_9D8A_FC4D76A56596__INCLUDED_)
