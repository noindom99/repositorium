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
//*****************************************************************************

// TDLSendTasksDlg.cpp : implementation file
//

#include "StdAfx.h"
#include "ToDoListApp.h"
#include "TDLSendTasksDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTDLSendTasksDlg dialog

CTDLSendTasksDlg::CTDLSendTasksDlg(TD_SENDWHAT nWhat, TD_SENDAS nSendAs, CWnd* pParent /*=NULL*/):
CDialog(CTDLSendTasksDlg::IDD, pParent), m_nSendWhat(nWhat), m_nSendTasksAsOption(nSendAs)
{
	//{{AFX_DATA_INIT(CTDLSendTasksDlg)
	//}}AFX_DATA_INIT
}

void CTDLSendTasksDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTDLSendTasksDlg)
	DDX_Radio(pDX, IDC_SENDACTIVETASKLIST, m_nSendWhat);
	DDX_CBIndex(pDX, IDC_SELTASKSSENDAS, m_nSendTasksAsOption);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTDLSendTasksDlg, CDialog)
	//{{AFX_MSG_MAP(CTDLSendTasksDlg)
	ON_BN_CLICKED(IDC_SENDACTIVETASKLIST, OnChangeSendWhat)
	ON_BN_CLICKED(IDC_SENDSELECTEDTASKS, OnChangeSendWhat)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTDLSendTasksDlg message handlers

BOOL CTDLSendTasksDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	GetDlgItem(IDC_SELTASKSSENDAS)->EnableWindow(m_nSendWhat == TDSW_SELECTEDTASKS);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CTDLSendTasksDlg::OnChangeSendWhat()
{
	UpdateData();

	GetDlgItem(IDC_SELTASKSSENDAS)->EnableWindow(m_nSendWhat == TDSW_SELECTEDTASKS);
}
