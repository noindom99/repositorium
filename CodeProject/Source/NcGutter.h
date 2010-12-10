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
// - reformatted with using Artistic Style 2.01 and the following options:
//      --indent=tab=3
//      --indent=force-tab=3
//      --indent-switches
//      --max-instatement-indent=2
//      --brackets=break
//      --add-brackets
//      --pad-oper
//      --unpad-paren
//      --pad-header
//      --align-pointer=type
//      --lineend=windows
//      --suffix=none
// - merged with ToDoList version 6.1.2 sources
//*****************************************************************************

// NcGutter.h: interface for the CNcGutter class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_NCGUTTER_H__A356B1B6_1B4D_4013_8F39_8D9D2442E149__INCLUDED_)
#define AFX_NCGUTTER_H__A356B1B6_1B4D_4013_8F39_8D9D2442E149__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Subclass.h"
#include "HotTracker.h"
#include <afxtempl.h>

// wParam == ctrl id
const UINT WM_NCG_GETFIRSTVISIBLETOPLEVELITEM = ::RegisterWindowMessage(_T("WM_NCG_GETFIRSTVISIBLETOPLEVELITEM"));
const UINT WM_NCG_GETNEXTITEM = ::RegisterWindowMessage(_T("WM_NCG_GETNEXTITEM"));
const UINT WM_NCG_POSTDRAWITEM = ::RegisterWindowMessage(_T("WM_NCG_POSTDRAWITEM"));
const UINT WM_NCG_PREDRAWITEM = ::RegisterWindowMessage(_T("WM_NCG_PREDRAWITEM"));
const UINT WM_NCG_DRAWITEM = ::RegisterWindowMessage(_T("WM_NCG_DRAWITEM"));
const UINT WM_NCG_RECALCCOLWIDTH = ::RegisterWindowMessage(_T("WM_NCG_RECALCCOLWIDTH"));
const UINT WM_NCG_WIDTHCHANGE = ::RegisterWindowMessage(_T("WM_NCG_WIDTHCHANGE"));
const UINT WM_NCG_POSTNCDRAW = ::RegisterWindowMessage(_T("WM_NCG_POSTNCDRAW"));
const UINT WM_NCG_GETITEMRECT = ::RegisterWindowMessage(_T("WM_NCG_GETITEMRECT"));
const UINT WM_NCG_GETFIRSTCHILDITEM = ::RegisterWindowMessage(_T("WM_NCG_GETFIRSTCHILDITEM"));
const UINT WM_NCG_GETPARENTITEM = ::RegisterWindowMessage(_T("WM_NCG_GETPARENTITEM"));
const UINT WM_NCG_HITTEST = ::RegisterWindowMessage(_T("WM_NCG_HITTEST"));
const UINT WM_NCG_NOTIFYITEMCLICK = ::RegisterWindowMessage(_T("WM_NCG_NOTIFYITEMCLICK"));
const UINT WM_NCG_NOTIFYHEADERCLICK = ::RegisterWindowMessage(_T("WM_NCG_NOTIFYHEADERCLICK"));
const UINT WM_NCG_GETCURSOR = ::RegisterWindowMessage(_T("WM_NCG_GETCURSOR"));
const UINT WM_NCG_WANTREDRAW = ::RegisterWindowMessage(_T("WM_NCG_WANTREDRAW"));
const UINT WM_NCG_WANTRECALC = ::RegisterWindowMessage(_T("WM_NCG_WANTRECALC"));
const UINT WM_NCG_GETITEMCOLORS = ::RegisterWindowMessage(_T("WM_NCG_GETITEMCOLORS"));
const UINT WM_NCG_NOTIFYSCROLL = ::RegisterWindowMessage(_T("WM_NCG_NOTIFYSCROLL"));

const int NCG_COLPADDING = 3;

enum
{
	NCGS_RIGHTCOLUMNS       = 0x01,
	NCGS_DOUBLEBUFFERCLIENT = 0x02,
	NCGS_SHOWHEADER         = 0x04,
	NCGS_GRADIENTSELECTION  = 0x08,
};

struct NCGDRAWITEM
{
	NCGDRAWITEM()
	{
		pDC = NULL;
		dwItem = dwParentItem = 0;
		nColID = 0;
		rItem = NULL;
		nLevel = 0;
		nItemPos = 0;
		rWindow = NULL; /*bSelected = FALSE;*/
		nTextAlign = DT_LEFT;
	}

	CDC* pDC;
	DWORD dwItem;
	DWORD dwParentItem; // always zero unless control responds to WM_NCG_GETFIRSTCHILDITEM
	int nColID;
	const CRect* rItem;
	int nLevel; // always zero unless control responds to WM_NCG_GETFIRSTCHILDITEM
	int nItemPos;
	const CRect* rWindow;
	UINT nTextAlign;
};

struct NCGRECALCCOLUMN
{
	int nColID;
	CDC* pDC;
	UINT nWidth; // fill in on return
};

struct NCGITEMRECT
{
	NCGITEMRECT()
	{
		dwItem = 0;
		::SetRectEmpty(&rItem);
	}

	DWORD dwItem;
	RECT rItem; // return client coords
};

struct NCGITEMCLICK
{
	DWORD dwItem;
	DWORD dwPrevItem; // set if this is a BUTTONUP msg
	int nColID; // NCG_CLIENTCOLUMNID if client click
	UINT nMsgID; // WM_...
	POINT ptClick;
};

struct NCGHDRCLICK
{
	int nColID;
	UINT nMsgID; // WM_...
	BOOL bPressed; // notifyee can modify to indicate what the final state should be
};

struct NCGGETCURSOR
{
	int nColID;
	DWORD dwItem;
};

struct NCGITEMSELECTION
{
	DWORD dwItem;
	BOOL bSelected;
};

struct NCGITEMCOLORS
{
	DWORD dwItem; // in
	COLORREF crBack; // out
	COLORREF crText; // out
	BOOL bBackSet; // out
	BOOL bTextSet; // out
};

const UINT NCG_CLIENTCOLUMNID = 0xffff;

enum NCGSORT
{
	NCGSORT_UP = -1,
	NCGSORT_NONE = 0, // default
	NCGSORT_DOWN = 1,
};

class CThemed;

class CNcGutter : protected CSubclassWnd
{
public:
	CNcGutter(DWORD dwStyles);
	virtual ~CNcGutter();

	BOOL Initialize(HWND hwnd);
	BOOL IsInitialized() const
	{
		return IsHooked();
	}

	// add WM_ messages that should cause a recalc
	// use nNotification for
	void AddRecalcMessage(UINT nMessage, UINT nNotification = 0);
	void AddRedrawMessage(UINT nMessage, UINT nNotification = 0); // add WM_ messages that should cause a redraw

	void Redraw();
	void RedrawItem(DWORD dwItem);

	void RecalcGutter(BOOL bForceRedraw = TRUE);
	BOOL RecalcColumn(UINT nColID); // TRUE if the gutter changed width
	int GetGutterWidth() const;

	void EnableStyle(DWORD dwStyle, BOOL bEnable = TRUE);
	BOOL HasStyle(DWORD dwStyle) const
	{
		return ((m_dwStyles & dwStyle) == dwStyle);
	}

	int AddColumn(UINT nColID, LPCTSTR szTitle = NULL, UINT nWidth = 0, UINT nTextAlign = DT_LEFT); // returns the index of the added column
	void PressHeader(UINT nColID, BOOL bPress = TRUE);
	void SetHeaderTitle(UINT nColID, LPCTSTR szTitle, LPCTSTR szFont = NULL, BOOL bSymbolFont = TRUE);
	void EnableHeaderClicking(UINT nColID, BOOL bEnable = TRUE);
	void SetColumnSort(UINT nColID, NCGSORT nSortDir, BOOL bExclusive = TRUE);
	int GetColumnCount() const
	{
		return m_aColumns.GetSize() - 1;   // don't count the client column
	}
	int GetColumnWidth(UINT nColID) const;
	void SetColumnTextAlignment(UINT nColID, UINT nTextAlign, BOOL bRedraw = TRUE);
	UINT GetColumnTextAlignment(UINT nColID) const;

	BOOL PtInHeader(CPoint ptScreen) const;
	void GetWindowClientRect(CRect& rClient, BOOL bScreen) const;

protected:
	CMap<DWORD, DWORD, char, char> m_mapRecalcMessages;
	CMap<DWORD, DWORD, char, char> m_mapRedrawMessages;
	BOOL m_bSetRedraw;
	CBitmap m_bmClient, m_bmNonClient;
	BOOL m_bFirstRecalc;
	CHotTracker m_hotTrack;
	int m_nHeaderColDown;
	DWORD m_dwButtonDownItem;
	DWORD m_dwStyles;
	float m_fAveCharWidth;

	struct COLUMNDESC
	{
		COLUMNDESC(UINT nID = 0) : nColID(nID), nWidth(0), bCalcWidth(TRUE), bPressed(FALSE),
			nTextAlign(DT_LEFT), bClickable(TRUE), nSortDir(NCGSORT_NONE),
			hFont(NULL), bSymbolFont(FALSE) {}
		~COLUMNDESC()
		{
			::DeleteObject(hFont);
		}

		UINT nColID;
		CString sTitle;
		BOOL bCalcWidth;
		UINT nWidth;
		UINT nTextWidth;
		BOOL bPressed;
		UINT nTextAlign;
		BOOL bClickable;
		NCGSORT nSortDir;
		HFONT hFont;
		BOOL bSymbolFont;
	};

	CArray<COLUMNDESC*, COLUMNDESC*> m_aColumns;

protected:
	virtual LRESULT WindowProc(HWND hRealWnd, UINT msg, WPARAM wp, LPARAM lp);

	// specific message handlers
	void OnPrint(HDC hdc, UINT& nFlags);
	void OnNcPaint();
	void OnPaint();
	void OnHotChange(int nPrevHot, int nHot);
	void OnNcButtonDown(UINT nMsg, CPoint point);
	void OnNcButtonUp(UINT nMsg, CPoint point);
	void OnButtonDown(UINT nMsg, CPoint point);
	void OnButtonUp(UINT nMsg, CPoint point);
	LRESULT OnNcHitTest(CPoint point);
	BOOL OnSetCursor(); // returns TRUE if the cursor was set
	LRESULT OnNcCalcSize(LPNCCALCSIZE_PARAMS lpncsp);

	// these test for messages added with AddRecalcMessage/AddRedrawMessage
	BOOL ProcessRecalcMsg(UINT nMsg, WPARAM wp, LPARAM lp, LRESULT& lr);
	BOOL ProcessRedrawMsg(UINT nMsg, WPARAM wp, LPARAM lp, LRESULT& lr);

	BOOL ParentWantRecalc();
	BOOL ParentWantRedraw();

	void NcDrawItem(CDC* pDC, DWORD dwItem, DWORD dwParentItem, int nLevel, int nPos,
		const CRect& rGutter, CRect& rItem, BOOL bDrawChildren);
	void PostNcDraw(CDC* pDC, const CRect& rWindow);
	void PostNcDrawItem(CDC* pDC, DWORD dwItem, const CRect& rItem, int nLevel, BOOL bParent);

	DWORD GetFirstVisibleTopLevelItem(int& nItem) const; // return 0 if no items
	DWORD GetNextItem(DWORD dwItem) const; // return 0 at end
	CRect GetWindowItemRect(DWORD dwItem) const;
	DWORD GetFirstChildItem(DWORD dwItem) const;
	DWORD GetParentItem(DWORD dwItem) const;
	void GetItemColors(DWORD dwItem, COLORREF& crText, COLORREF& crBack) const;

	enum NCG_HITTEST { NCGHT_HEADER, NCGHT_ITEM, NCGHT_NOWHERE }; // private

	NCG_HITTEST HitTest(CPoint ptScreen, DWORD& dwItem, int& nColumn) const;
	NCG_HITTEST HitTest(CPoint ptScreen) const;
	DWORD ItemHitTest(CPoint ptClient) const;
	int ColumnHitTest(CPoint ptScreen) const;

	enum HCHDRPART { NONCLIENT, CLIENT }; // private

	void NcDrawHeader(CDC* pDC, const CRect& rHeader, HCHDRPART nPart, const LPPOINT pCursor);
	void NcDrawHeaderColumn(CDC* pDC, int nColumn, CRect rColumn, CThemed* pTheme, const LPPOINT pCursor);
	void UpdateHeaderHotRects();
	void UnpressAllColumnHeaders(int nExcludeCol = -1);
	int RecalcGutterWidth();
	int GetColumnIndex(UINT nColID) const; // can return -1

	inline BOOL IsClientColumn(int nCol) const
	{
		return (nCol == m_aColumns.GetSize() - 1);
	}

	BOOL PrepareBitmap(CDC* pDC, CBitmap* pBitmap, const CRect& rect, BOOL bClient);
	CFont* PrepareFont(CDC* pDC, BOOL bHeader, HFONT hFont = NULL); // returns 'old' font

	enum GHR_WHAT { GHR_NONCLIENT, GHR_CLIENT, GHR_ALL }; // private

	void GetHeaderRect(CRect& rHeader, GHR_WHAT nWhat, BOOL bScreen) const;
	void GetWindowRectEx(CRect& rWindow, BOOL bScreen) const;
	void GetGutterRect(CRect& rGutter, BOOL bScreen) const;
	void GetCursorPos(CPoint& ptCursor, BOOL bScreen) const;
};

#endif // !defined(AFX_NCGUTTER_H__A356B1B6_1B4D_4013_8F39_8D9D2442E149__INCLUDED_)
