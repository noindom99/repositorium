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

#if defined(_MSC_VER) && _MSC_VER < 1300
	// STL warnings
	#pragma warning(push, 3)
#endif

#include "FileFilter.h"

namespace ZipArchiveLib
{

bool CGroupFileFilter::Accept(LPCTSTR lpszParentDir, LPCTSTR lpszName, const CFileInfo& info)
{
	bool conditionToBreak;
	bool valueToReturn;

	// handle the evaluation as quickly as possible
	if (m_iType == CGroupFileFilter::And)
	{
		conditionToBreak = false;
		valueToReturn = m_bInverted;
	}
	else
	{
		conditionToBreak = true;
		valueToReturn = !m_bInverted;
	}

	for (ZIP_ARRAY_SIZE_TYPE i = 0; i < m_filters.GetSize(); i++)
	{
		CFileFilter* pFilter = m_filters[i];
		if (pFilter->HandlesFile(info) && pFilter->Evaluate(lpszParentDir, lpszName, info) == conditionToBreak)
		{
			return valueToReturn;
		}
	}

	return !valueToReturn;

}

} // namespace


#if defined(_MSC_VER) && _MSC_VER < 1300
	// STL warnings
	#pragma warning(pop)
#endif
