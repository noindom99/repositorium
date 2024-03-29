// Copyright (C) 2003-2011 AbstractSpoon Software.
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
// - merged with ToDoList version 6.1.2 sources
//*****************************************************************************

#if !defined(AFX_TODOCTRLREMINDERS_H__E0CF538D_61A2_418B_8702_85A1BFFE05BF__INCLUDED_)
#define AFX_TODOCTRLREMINDERS_H__E0CF538D_61A2_418B_8702_85A1BFFE05BF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// ToDoCtrlReminders.h : header file
//

#include <afxtempl.h>
#include "TDCStruct.h"

const UINT WM_TD_REMINDER = ::RegisterWindowMessage(_T("WM_TD_REMINDER"));

/////////////////////////////////////////////////////////////////////////////
// CToDoCtrlReminders window

class CToDoCtrlReminders : protected CWnd
{
// Construction
public:
	CToDoCtrlReminders();
	BOOL Initialize(CWnd* pNotify);
	void AddToDoCtrl(const CFilteredToDoCtrl& tdc);
	void CloseToDoCtrl(const CFilteredToDoCtrl& tdc);
	void SetReminder(const TDCREMINDER& rem);
	void RemoveReminder(const TDCREMINDER& rem);
	void RemoveReminder(DWORD dwTaskID, const CFilteredToDoCtrl* pTDC);
	BOOL GetReminder(int nRem, TDCREMINDER& rem) const;
	int FindReminder(const TDCREMINDER& rem) const;
	int FindReminder(DWORD dwTaskID, const CFilteredToDoCtrl* pTDC) const;

// Attributes
protected:
	CWnd* m_pWndNotify;
	CArray<TDCREMINDER, TDCREMINDER&> m_aReminders;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CToDoCtrlReminders)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CToDoCtrlReminders();

	// Generated message map functions
protected:
	//{{AFX_MSG(CToDoCtrlReminders)
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:
	void SaveAndRemoveReminders(const CFilteredToDoCtrl& tdc);
	void LoadReminders(const CFilteredToDoCtrl& tdc);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TODOCTRLREMINDERS_H__E0CF538D_61A2_418B_8702_85A1BFFE05BF__INCLUDED_)
