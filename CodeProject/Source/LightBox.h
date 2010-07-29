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
// - taken out from the original ToDoList package for better sharing
//*****************************************************************************

// LightBox.h: interface for the CLightBox class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LIGHTBOX_H__B86BA77E_2353_44E0_9F47_1EB2F02009A1__INCLUDED_)
#define AFX_LIGHTBOX_H__B86BA77E_2353_44E0_9F47_1EB2F02009A1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Subclass.h"
#include "RuntimeDlg.h"
#include "HookMgr.h"

class CLightBox;

class CLightBoxMgr : public CHookMgr<CLightBoxMgr>
{
	friend class CHookMgr<CLightBoxMgr>;
	
public:
	CLightBoxMgr();
	static BOOL Initialize(CWnd* pMainWnd, COLORREF crBkgnd = GetSysColor(COLOR_3DLIGHT), 
		int nOpaquePercent = 50);
	static void Disable() { Instance().Release(); }
		~CLightBoxMgr();
	
protected:
	CMap<HWND, HWND, CLightBox*, CLightBox*&> m_mapCtrls;
	COLORREF m_crBkgnd;
	int m_nOpaquePercent;
	
protected:
	static CLightBoxMgr& Instance() { return CHookMgr<CLightBoxMgr>::GetInstance(); }
	BOOL AttachLightBox(CWnd* pWnd);
	
	virtual BOOL OnCallWndProc(const MSG& msg);
};

class CLightBox : public CRuntimeDlg, public CSubclassWnd  
{
	DECLARE_DYNAMIC(CLightBox)
		
public:
	CLightBox();
	virtual ~CLightBox();
	
	BOOL Initialize(CWnd* pWnd, COLORREF crBkgnd = GetSysColor(COLOR_3DHILIGHT), int nOpaquePercent = 50);
	
protected:
	COLORREF m_crBkgnd;
	int m_nOpaquePercent;
	
	typedef DWORD (WINAPI *PSLWA)(HWND, DWORD, BYTE, DWORD);
	PSLWA m_pSetLayeredWindowAttributes;
	
	// Generated message map functions
protected:
	//{{AFX_MSG(CLightBox)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
		
protected:
	virtual LRESULT WindowProc(HWND hRealWnd, UINT msg, WPARAM wp, LPARAM lp);
	
	BOOL ShowTransparentWnd(BOOL bShow = TRUE);
};

#endif // !defined(AFX_LIGHTBOX_H__B86BA77E_2353_44E0_9F47_1EB2F02009A1__INCLUDED_)