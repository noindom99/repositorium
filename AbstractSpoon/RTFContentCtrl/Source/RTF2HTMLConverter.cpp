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
// - restyled using ProFactor StyleManager v1.17:
//      * removed unnecessary spaces and empty lines
//      * wrapped extremely long lines
//      * reformatted all the ctors to be more readable
//      * eliminated dead commented code
//*****************************************************************************

// RTF2HTMLConverter.cpp: implementation of the CRTF_HTMLConverter class.
//
//////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "RTF2HTMLTree.h"
#include "RTF2HTMLConverter.h"
#include "Util.h"

#include "../../Common/HtmlCharMap.h"
#include "../../../CodeProject/Source/Misc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

#pragma warning(disable: 4189)

const LPCTSTR MULTIBYTETAG = _T("\\'");
const CString DELIM = _T("\x20{}\\\r");

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CRTF_HTMLConverter::CRTF_HTMLConverter(TMode enMode)
{
	ASSERT(enMode == c_modRTF2HTML); //vice versa unsupported at the moment
	m_enMode = enMode;
	m_RTFTree = new CRTFTree;
	m_strTitle = _T("RTF2HTML Generated Document");
	ResetMetaData();
}

CRTF_HTMLConverter::~CRTF_HTMLConverter()
{
	delete m_RTFTree;
	ResetMetaData();
}

void CRTF_HTMLConverter::SetTitle(const CString& strTitle)
{
	m_strTitle = strTitle;
}

void CRTF_HTMLConverter::ResetMetaData()
{
	m_strCharset = _T("1252");
	m_strActFontColor = _T("#000000");
	m_strActFontName = _T("Arial");
	m_strActFontSize = _T("10");
	m_mapFontNames.RemoveAll();
	m_arrColors.RemoveAll();
	//   m_bTextSinceLastPara = FALSE;

	for (int i = 0; i < m_arrHTMLElements.GetSize(); i++)
	{
		delete m_arrHTMLElements[i];
	}

	m_arrHTMLElements.RemoveAll();
}

bool CRTF_HTMLConverter::ConvertRTF2HTML(BOOL bWantHeaderFooter)
{
	//Initializing
	m_strHTML = _T("");

	//Check_Valid_RTF
	m_strRTF.TrimRight(_T("\n"));
	m_strRTF.TrimRight(_T("\r"));
	CString strEndChar = m_strRTF.Right(1);
	strEndChar;
	if (!((m_strRTF.GetLength() >= 7) && (m_strRTF.Left(6) == _T("{\\rtf1"))))
	{
		//Invalid RTF file. Must start with "{RTF1" and end with "}"
		ASSERT(FALSE);
		return false;
	}

	// make sure it ends in a '}'
	int nLen = m_strRTF.GetLength();

	while (m_strRTF[nLen - 1] != _T('}'))
	{
		nLen--;
	}

	if (nLen < m_strRTF.GetLength())
	{
		m_strRTF = m_strRTF.Left(nLen);
	}

	ASSERT(m_strRTF[nLen - 1] == _T('}'));

	// remove pictures (for now)
	int nPicStart = m_strRTF.Find(_T("{\\pict"));

	while (nPicStart != -1)
	{
		// look for closing tag and remove
		int nLen = m_strRTF.GetLength();
		int nPicEnd = nPicStart + 6;

		while (nPicEnd < nLen)
		{
			if (m_strRTF[nPicEnd] == _T('}'))
			{
				break;
			}

			nPicEnd++;
		}

		if (nPicEnd > nLen)
		{
			return false;   // no end to picture
		}

		// remove picture
		if (nPicEnd == nLen)
		{
			m_strRTF = m_strRTF.Left(nPicStart);
		}
		else
		{
			m_strRTF = m_strRTF.Left(nPicStart) + m_strRTF.Mid(nPicEnd + 1);
		}

		// next picture
		nPicStart = m_strRTF.Find(_T("{\\pict"));
	}

	//Clear internal members
	ResetMetaData();

	//Build up RTF Tree. Each tree in a node coresponds to a {} section in the RTF file (code)
	//and has a designator (name), like \RTF or \FONTTBL. We start with the whole RTF file
	//(Section \RTF1)
	delete m_RTFTree;
	m_RTFTree = new CRTFTree;
	CRTFNode NodeRoot = R2H_BuildTree(m_strRTF);
	CString strRTFCode = (NodeRoot)->m_strThisCode;

	//Fill internal meta data members
	R2H_SetMetaData(NodeRoot);

	//Create html main body
	R2H_CreateHTMLElements(strRTFCode);

	//HTML Header
	R2H_GetHTMLElements(m_strHTML);

	if (bWantHeaderFooter)
	{
		R2H_GetHTMLElements(m_strHTML);
		m_strHTML = R2H_GetHTMLHeader() + m_strHTML + _T("\r\n") + R2H_GetHTMLFooter();
	}

	return true;
}

bool CRTF_HTMLConverter::Convert(const CString& sRtf, CString& sHtml, BOOL bWantHeaderFooter)
{
	CRTF_HTMLConverter r2h(c_modRTF2HTML);

	r2h.m_strRTF = sRtf;

	if (r2h.ConvertRTF2HTML(bWantHeaderFooter))
	{
		sHtml = r2h.m_strHTML;
		return true;
	}

	return false;
}

CString CRTF_HTMLConverter::R2H_GetHTMLHeader()
{
	CString strHTMLHeader;
	strHTMLHeader += _T("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01 Transitional//DE\" \"http://www.w3.org/TR/html4/loose.dtd\">\r\n");
	strHTMLHeader += _T("<html>\r\n");
	strHTMLHeader += _T("  <head>\r\n");
	strHTMLHeader += _T("     <meta http-equiv=\"Content-Type\" content=\"text/html; charset=windows-") + m_strCharset + _T("\">\r\n");
	strHTMLHeader += _T("     <title>") + m_strTitle + _T("</title>\r\n");
	strHTMLHeader += _T("  </head>\r\n");
	strHTMLHeader += _T("  <body>\r\n");
	return strHTMLHeader;
}

CString CRTF_HTMLConverter::R2H_GetHTMLFooter()
{
	CString strHTMLFooter;
	strHTMLFooter += _T("  </body>\r\n");
	strHTMLFooter += _T("</html>\r\n");
	return strHTMLFooter;
}

CString CRTF_HTMLConverter::R2H_GetRTFTag(const CString& strRTFSource, long lPos)
{
	//Initializing
	CString strTag;
	ASSERT(lPos < strRTFSource.GetLength()); //lPos is POS(\) within strRTFSource
	ASSERT(strRTFSource.GetAt(lPos) == _T('\\'));
	int nCnt = 0;
	TCHAR cFirstChar = 0;

	//Starting from lPos, we say everything is an rtf element until \ or blank or { occurs
	for (int iStrPos = lPos + 1; iStrPos < strRTFSource.GetLength(); iStrPos++)
	{
		TCHAR ChTest = strRTFSource[iStrPos];

		if (DELIM.Find(ChTest) != -1)
		{
			break;   //designator terminated
		}

		if (nCnt >= 3 && cFirstChar == _T('\''))
		{
			break;
		}

		if (!cFirstChar)
		{
			cFirstChar = ChTest;
		}

		//strTag+=ChTest;
		nCnt++;
	}

	strTag = strRTFSource.Mid(lPos + 1, nCnt);

	return strTag;
}

void CRTF_HTMLConverter::R2H_SetMetaData(CRTFNode& NodeRoot)
{
	//Initializing
	CString strRTFSource = (NodeRoot)->m_strThisCode;

	//Go thru RTF main string's global data
	for (int iStrPos = 0; iStrPos < strRTFSource.GetLength(); iStrPos++)
	{
		TCHAR ChTest = strRTFSource[iStrPos];

		if (ChTest == _T('\\'))
		{
			CString strTag = R2H_GetRTFTag(strRTFSource, iStrPos);
			CString strTestTag;

			strTestTag = _T("ansicpg");

			if ((strTag.GetLength() >= strTestTag.GetLength()) && (strTag.Left(strTestTag.GetLength()) == strTestTag))
			{
				m_strCharset = strTag;
				m_strCharset.Delete(0, strTestTag.GetLength());
			}

			iStrPos += strTag.GetLength();

			if (((iStrPos + 1) < strRTFSource.GetLength()) && (strRTFSource[iStrPos + 1] == _T(' ')))
			{
				iStrPos++;   //Ignore Blank after Tag
			}
		}
		else
		{
			//Normal character
		}
	} //loop thru string

	//Go thru 1st-level-nodes
	for (int iRTFNodes = 0; iRTFNodes < NodeRoot.Count; iRTFNodes++)
	{
		//Color table
		if (NodeRoot.Nodes[iRTFNodes]->m_strName == _T("colortbl"))
		{
			CString strColorTbl = NodeRoot.Nodes[iRTFNodes]->m_strThisCode;
			strColorTbl.Delete(0, NodeRoot.Nodes[iRTFNodes]->m_strName.GetLength() + 1); //+1=leading \ (backslash)
			//Palette entries are separated with semicolon ;
			CStringArray arrStrColors;
			StringToArray(strColorTbl, arrStrColors);

			for (int iColor = 0; iColor < arrStrColors.GetSize(); iColor++)
			{
				//RGB values within palette entry are \redXXX\greenXXX\blueXXX
				DWORD r = 0, g = 0, b = 0;
				CString strColorEntry = arrStrColors[iColor];
				strColorEntry.TrimLeft();
				strColorEntry.TrimRight();
				if (strColorEntry.GetLength() > 0)
				{
					//Loop thru base colors (r,g,b) and set them
					CStringArray arrStrRGBs;
					R2H_GetRTFTags(strColorEntry, arrStrRGBs);
					ASSERT(arrStrRGBs.GetSize() == 3); //RTF must contain exactly 3 entries for red/green/blue
					for (int iBaseColor = 0; iBaseColor < arrStrRGBs.GetSize(); iBaseColor++)
					{
						CString strBaseColor = arrStrRGBs[iBaseColor];
						CString strTestBaseColor;
						strTestBaseColor = _T("red");
						if ((strBaseColor.GetLength() >= strTestBaseColor.GetLength()) && (strBaseColor.Left(strTestBaseColor.GetLength()) == strTestBaseColor))
						{
							strBaseColor.Delete(0, strTestBaseColor.GetLength());
							r = StringToLong(strBaseColor);
						}
						strTestBaseColor = _T("green");
						if ((strBaseColor.GetLength() >= strTestBaseColor.GetLength()) && (strBaseColor.Left(strTestBaseColor.GetLength()) == strTestBaseColor))
						{
							strBaseColor.Delete(0, strTestBaseColor.GetLength());
							g = StringToLong(strBaseColor);
						}
						strTestBaseColor = _T("blue");
						if ((strBaseColor.GetLength() >= strTestBaseColor.GetLength()) && (strBaseColor.Left(strTestBaseColor.GetLength()) == strTestBaseColor))
						{
							strBaseColor.Delete(0, strTestBaseColor.GetLength());
							b = StringToLong(strBaseColor);
						}
					}
				}
				COLORREF ref = RGB(r, g, b);
				m_arrColors.Add(ref);
			}
			continue;
		}
		//Font Table
		if (NodeRoot.Nodes[iRTFNodes]->m_strName == _T("fonttbl"))
		{
			for (int iFontNodes = 0; iFontNodes < NodeRoot.Nodes[iRTFNodes].Count; iFontNodes++)
			{
				CString strFontName = NodeRoot.Nodes[iRTFNodes].Nodes[iFontNodes]->m_strName;
				CString strFont = NodeRoot.Nodes[iRTFNodes].Nodes[iFontNodes]->m_strPlain;
				ASSERT((strFontName.GetLength() >= 2) && (strFontName.Left(1) == _T("f"))); //No valid RTF
				ASSERT(strFont.GetLength() > 0);
				strFont.TrimLeft();
				strFont.TrimRight();
				strFont.Remove(_T(';'));
				m_mapFontNames.SetAt(strFontName, strFont);
			} //for-each-font
			continue;
		} //if font-table
	} //for each 1st-level-node
}

void CRTF_HTMLConverter::R2H_InterpretTag(const CString& strRTFTag)
{
	CString strTestTag;
	CHTMLElement* pElement = NULL;

	//Char attributes
	if (strRTFTag == _T("b"))
	{
		pElement = new CHTMLElement(CHTMLElement::c_nodHTMLBegin, _T("b"));
	}
	else if (strRTFTag == _T("b0"))
	{
		pElement = new CHTMLElement(CHTMLElement::c_nodHTMLEnd, _T("b"));
	}
	else if (strRTFTag == _T("i"))
	{
		pElement = new CHTMLElement(CHTMLElement::c_nodHTMLBegin, _T("i"));
	}
	else if (strRTFTag == _T("i0"))
	{
		pElement = new CHTMLElement(CHTMLElement::c_nodHTMLEnd, _T("i"));
	}
	else if (strRTFTag == _T("ul"))
	{
		pElement = new CHTMLElement(CHTMLElement::c_nodHTMLBegin, _T("u"));
	}
	else if (strRTFTag == _T("ulnone"))
	{
		pElement = new CHTMLElement(CHTMLElement::c_nodHTMLEnd, _T("u"));
	}
	else
	{
		pElement = new CHTMLElement();
	}

	//Special character (umlaut)
	strTestTag = _T("\'");
	if ((pElement->m_enNodeType == CHTMLElement::c_nodInvalid) && (strRTFTag.GetLength() >= strTestTag.GetLength()) &&
		(strRTFTag.Left(strTestTag.GetLength()) == strTestTag))
	{
		CString strSpecialChar = strRTFTag;
		strSpecialChar.Delete(0, strTestTag.GetLength());
		ASSERT(strSpecialChar.GetLength() == 2); //Invalid RTF (must be 2-digit hex code)
		strSpecialChar = strSpecialChar.Left(2);
		pElement->m_enNodeType = CHTMLElement::c_nodText;
		pElement->m_strNodeText = _T("&#x") + strSpecialChar + _T(";");
	}

	//Paragraph Tag
	if ((pElement->m_enNodeType == CHTMLElement::c_nodInvalid) && (strRTFTag == _T("par")))
	{
		long lLastUnclosedPStart = -1;
		//Look if we first must close paragraph
		for (int iLastElements = m_arrHTMLElements.GetSize() - 1; iLastElements >= 0; iLastElements--)
		{
			/*
			CHTMLElement* pElementTest = m_arrHTMLElements[iLastElements];
			if ((pElementTest->m_enNodeType==CHTMLElement::c_nodHTMLEnd)&&(pElementTest->m_strNodeText=="p")) break; //everything is OK
			if ((pElementTest->m_enNodeType==CHTMLElement::c_nodHTMLBegin)&&(pElementTest->m_strNodeText=="p"))
			{
			lLastUnclosedPStart=iLastElements;
			break; //everything is OK
			}
			*/
		}
		if (lLastUnclosedPStart >= 0)
		{
			//Look if there is no text between last <p> and this <p-end> (e.g. <p></p>)
			//HTML does then not display a linefeed, therefore make it to <p>&nbsp;</p>
			BOOL bLastParaEmpty = TRUE;
			for (int iLastPara = lLastUnclosedPStart; iLastPara < m_arrHTMLElements.GetSize(); iLastPara++)
			{
				CHTMLElement* pElementTest = m_arrHTMLElements[iLastPara];
				if (pElementTest->m_enNodeType == CHTMLElement::c_nodText)
				{
					if ((pElementTest->m_strNodeText != _T("")) &&
						(pElementTest->m_strNodeText != _T("\r")) &&
						(pElementTest->m_strNodeText != _T("\n")) &&
						(pElementTest->m_strNodeText != _T("\r\n")) &&
						(pElementTest->m_strNodeText != _T("b")))
					{
						bLastParaEmpty = FALSE;
					}
				}
			}
		}
		//Add paragraph tag (<p>
		pElement->m_enNodeType = CHTMLElement::c_nodHTMLBegin;
		pElement->m_strNodeText = _T("br");
		//      pElement->m_strNodeText = "p";
	}
	// else Unknown RTF tag, just ignore

	//Paragraph Alignment
	strTestTag = _T("q");
	if ((pElement->m_enNodeType == CHTMLElement::c_nodInvalid) && (strRTFTag.GetLength() >= strTestTag.GetLength()) &&
		(strRTFTag.Left(strTestTag.GetLength()) == strTestTag))
	{
		//Get RTF alignment
		CString strAlignRTF, strAlignHTML;
		pElement->m_enNodeType = CHTMLElement::c_nodHTMLBegin;
		pElement->m_strNodeText = _T("font");
		strAlignRTF = strRTFTag;
		strAlignRTF.Delete(0, strTestTag.GetLength());
		ASSERT(strAlignRTF.GetLength() == 1); //Invalid RTF

		//Convert RTF options to HTML options
		if (strAlignRTF == _T("l"))
		{
			strAlignHTML = _T("left");
		}
		else if (strAlignRTF == _T("r"))
		{
			strAlignHTML = _T("right");
		}
		else if (strAlignRTF == _T("c"))
		{
			strAlignHTML = _T("center");
		}
		else
		{
			; //unsupported
		}
		//Find last paragraph
		long lLastParaStart = -1;
		for (int iLastElements = m_arrHTMLElements.GetSize() - 1; iLastElements >= 0; iLastElements--)
		{
			CHTMLElement* pElementTest = m_arrHTMLElements[iLastElements];
			if ((pElementTest->m_enNodeType == CHTMLElement::c_nodHTMLBegin) && (pElementTest->m_strNodeText == _T("p")))
			{
				lLastParaStart = iLastElements;
				break; //everything is OK
			}
		}
		if ((lLastParaStart >= 0) && (strAlignHTML != _T("")))
		{
			CHTMLElement* pElementPara = m_arrHTMLElements[lLastParaStart];
			pElementPara->m_mapParams.SetAt(_T("align"), _T("\"") + strAlignHTML + _T("\""));
		}

	}

	//font color
	strTestTag = _T("cf");
	if ((pElement->m_enNodeType == CHTMLElement::c_nodInvalid) && (strRTFTag.GetLength() >= strTestTag.GetLength()) &&
		(strRTFTag.Left(strTestTag.GetLength()) == strTestTag))
	{
		CString strActColor;
		pElement->m_enNodeType = CHTMLElement::c_nodHTMLBegin;
		pElement->m_strNodeText = _T("font");
		strActColor = strRTFTag;
		strActColor.Delete(0, strTestTag.GetLength());
		ASSERT(strActColor.GetLength() > 0); //Invalid RTF
		long lActColor = StringToLong(strActColor);
		ASSERT(lActColor < m_arrColors.GetSize()); //Color not in Colortable !
		if (lActColor < m_arrColors.GetSize())
		{
			DWORD r = 0, g = 0, b = 0;
			COLORREF ref = m_arrColors[lActColor];
			r = GetRValue(ref);
			g = GetGValue(ref);
			b = GetBValue(ref);
			CString strHTMLColor;
			strHTMLColor.Format(_T("#%02x%02x%02x"), r, g, b);
			m_strActFontColor = strHTMLColor;
		}
	}
	//font size
	strTestTag = _T("fs");
	if ((pElement->m_enNodeType == CHTMLElement::c_nodInvalid) && (strRTFTag.GetLength() >= strTestTag.GetLength()) &&
		(strRTFTag.Left(strTestTag.GetLength()) == strTestTag))
	{
		pElement->m_enNodeType = CHTMLElement::c_nodHTMLBegin;
		pElement->m_strNodeText = _T("font");
		m_strActFontSize = strRTFTag;
		m_strActFontSize.Delete(0, strTestTag.GetLength());
		ASSERT(m_strActFontSize.GetLength() > 0); //Invalid RTF
		m_strActFontSize = LongToString(StringToLong(m_strActFontSize) / 2); //RTF stores the doubled font size
	}
	//font name
	strTestTag = _T("f"); //f+number
	if ((pElement->m_enNodeType == CHTMLElement::c_nodInvalid) && (strRTFTag.GetLength() >= strTestTag.GetLength()) &&
		(strRTFTag.Left(strTestTag.GetLength()) == strTestTag) &&
		(strRTFTag.Mid(1).SpanIncluding(_T("01234567890")) == strRTFTag.Mid(1)))
	{
		CString strActFontDsgn = strRTFTag;
		pElement->m_enNodeType = CHTMLElement::c_nodHTMLBegin;
		pElement->m_strNodeText = _T("font");
		ASSERT(strActFontDsgn.GetLength() > 0); //Invalid RTF
		CString strActFontName;
		BOOL bFound = m_mapFontNames.Lookup(strActFontDsgn, strActFontName);
		ASSERT(bFound); //Font not found in font table, don't change font
		if (bFound)
		{
			m_strActFontName = strActFontName;
		}
	}

	//New font tag ?
	if ((pElement->m_enNodeType == CHTMLElement::c_nodHTMLBegin) && (pElement->m_strNodeText == _T("font")))
	{
		BOOL bMustClose = FALSE;
		//Look if we first must close paragraph
		for (int iLastElements = m_arrHTMLElements.GetSize() - 1; iLastElements >= 0; iLastElements--)
		{
			CHTMLElement* pElementTest = m_arrHTMLElements[iLastElements];
			if ((pElementTest->m_enNodeType == CHTMLElement::c_nodHTMLEnd) && (pElementTest->m_strNodeText == _T("font")))
			{
				break;   //everything is OK
			}
			if ((pElementTest->m_enNodeType == CHTMLElement::c_nodHTMLBegin) &&
				(pElementTest->m_strNodeText == _T("font")))
			{
				bMustClose = TRUE;
				break; //everything is OK
			}
		}
		if (bMustClose)
		{
			//Insert Closing </p>
			CHTMLElement* pElementClose = new CHTMLElement();
			pElementClose->m_enNodeType = CHTMLElement::c_nodHTMLEnd;
			pElementClose->m_strNodeText = _T("font");
			m_arrHTMLElements.Add(pElementClose);
		}
		//Set font tag options
		pElement->m_mapParams.SetAt(_T("color"), _T("\"") + m_strActFontColor + _T("\""));
		pElement->m_mapParams.SetAt(_T("style"), _T("\"font-size: ") + m_strActFontSize + _T("pt; font-family:") +
			m_strActFontName + _T(";\""));
	}
	if (pElement->m_enNodeType != CHTMLElement::c_nodInvalid)
	{
		m_arrHTMLElements.Add(pElement);
	}
	else
	{
		delete pElement;
	}
}

void CRTF_HTMLConverter::R2H_GetRTFTags(const CString& strRTFSource, CStringArray& arrTgt)
{
	//Go thru RTF main string
	for (int iStrPos = 0; iStrPos < strRTFSource.GetLength(); iStrPos++)
	{
		CString strChTest(strRTFSource[iStrPos]);
		if (strChTest == _T("\\"))
		{
			CString strTag = R2H_GetRTFTag(strRTFSource, iStrPos);
			arrTgt.Add(strTag);
			iStrPos += strTag.GetLength();
			if (((iStrPos + 1) < strRTFSource.GetLength()) && (strRTFSource[iStrPos + 1] == _T(' ')))
			{
				iStrPos++;   //Ignore Blank after Tag
			}
		}
	} //loop thru string
}


//! Gets the created HTML elements as HTML text
void CRTF_HTMLConverter::R2H_GetHTMLElements(CString& strHTML)
{
	strHTML = _T("");

	// remove invalid trailing elements
	int iElemCount = m_arrHTMLElements.GetSize();

	while (iElemCount--)
	{
		CHTMLElement* pElem = m_arrHTMLElements[iElemCount];

		if (pElem->m_enNodeType == CHTMLElement::c_nodHTMLEnd)
		{
			iElemCount++; // we want this element
			break;
		}
		else if (pElem->m_enNodeType == CHTMLElement::c_nodText)
		{
			CString sText = pElem->m_strNodeText;
			sText.TrimLeft();
			sText.TrimRight();

			if (!sText.IsEmpty() && sText != _T("br") && sText != _T("\n") && sText != _T("\r\n"))
			{
				iElemCount++; // we want this element
				break;
			}
		}
	}

	// Loop thru what's remaining of the HTML elements
	CMap<CString, LPCTSTR, int, int> mapOpenTags;

	for (int iElem = 0; iElem < iElemCount; iElem++)
	{
		CHTMLElement* pElem = m_arrHTMLElements[iElem];
		CString sElem;

		if (pElem->m_enNodeType == CHTMLElement::c_nodHTMLBegin)
		{
			// look ahead so that we can strip out empty tag pairs (typically 'font')
			bool bEmpty = false;

			if (iElem + 1 < m_arrHTMLElements.GetSize())
			{
				CHTMLElement* pElemNext = m_arrHTMLElements[iElem + 1];

				if (pElemNext->m_enNodeType == CHTMLElement::c_nodHTMLEnd &&
					pElemNext->m_strNodeText == pElem->m_strNodeText)
				{
					//TRACE ("CRTF_HTMLConverter::R2H_GetHTMLElements(removing '%s')\n", pElemNext->m_strNodeText);
					bEmpty = true;
				}
			}

			if (bEmpty)
			{
				iElem++;   // remove end tag too
			}
			else
			{
				// keep track of opentags
				int nCount = 0;

				mapOpenTags.Lookup(pElem->m_strNodeText, nCount);
				mapOpenTags[pElem->m_strNodeText] = ++nCount;

				// HTML element open tag
				sElem = _T("<");
				sElem += pElem->m_strNodeText;

				// HTML element parameters (<font param1="test" param2="hugo">
				POSITION pos = pElem->m_mapParams.GetStartPosition();

				while (pos)
				{
					CString strKey, strValue;
					pElem->m_mapParams.GetNextAssoc(pos, strKey, strValue);

					sElem += _T(" ") + strKey + _T(" = ") + strValue;
				}
				sElem += _T(">");
			}
		}
		else if (pElem->m_enNodeType == CHTMLElement::c_nodHTMLEnd)
		{
			sElem.Format(_T("</%s>"), pElem->m_strNodeText);

			// decrement open tag count
			int nCount = 0;

			mapOpenTags.Lookup(pElem->m_strNodeText, nCount);

			if (nCount > 0)
			{
				mapOpenTags[pElem->m_strNodeText] = --nCount;
			}
		}
		else if (pElem->m_enNodeType == CHTMLElement::c_nodText)
		{
			sElem = pElem->m_strNodeText;
		}
		else
		{
			ASSERT(FALSE); //internal error (wrong html tag)
		}

		if (!sElem.IsEmpty())
		{
			strHTML += sElem;
		}
	}

	// any open tags remaining?
	POSITION pos = mapOpenTags.GetStartPosition();

	while (pos)
	{
		CString sTag, sClose;
		int nCount = 0;
		mapOpenTags.GetNextAssoc(pos, sTag, nCount);

		if (nCount && sTag != _T("br"))
		{
			sClose.Format(_T("</%s>"), sTag);

			while (nCount--)
			{
				strHTML += sClose;
			}
		}
	}
}

int CRTF_HTMLConverter::GetCodePage(const CString& sRtf)
{
	const CString CPGTAG(_T("\\ansicpg"));

	int nFind = sRtf.Find(CPGTAG);

	if (nFind != -1)
	{
		return _ttoi((LPCTSTR)sRtf + (nFind + CPGTAG.GetLength()));
	}

	return -1;
}

BOOL CRTF_HTMLConverter::HasMultiByteChars(const CString& sRtf)
{
	int nFind = sRtf.Find(MULTIBYTETAG);

	while (nFind != -1)
	{
		// check for bullet chars (\'B7) which are okay
		if (sRtf.GetLength() < nFind + 4)
		{
			return TRUE;
		}

		if (sRtf[nFind + 2] != _T('B') || sRtf[nFind + 3] != _T('7'))
		{
			return TRUE;
		}

		nFind = sRtf.Find(MULTIBYTETAG, nFind + 1);
	}

	return FALSE;
}

void CRTF_HTMLConverter::R2H_CreateHTMLElements(const CString& strRTFSource)
{
	//Go thru RTF main string
	CString strCurrentText;
	for (int iStrPos = 0; iStrPos < strRTFSource.GetLength(); iStrPos++)
	{
		CString strChTest(strRTFSource[iStrPos]);
#ifdef _DEBUG
		const TCHAR* szPos = (LPCTSTR)strRTFSource + iStrPos;
#endif

		if (strChTest == _T("\\"))
		{
			//New tag
			if (strCurrentText != _T(""))
			{
				CHTMLElement* pElement = new CHTMLElement();
				pElement->m_enNodeType = CHTMLElement::c_nodText;
				pElement->m_strNodeText = strCurrentText;
				m_arrHTMLElements.Add(pElement);
				strCurrentText = _T("");
			}
			CString strTag = R2H_GetRTFTag(strRTFSource, iStrPos);
			R2H_InterpretTag(strTag);
			iStrPos += strTag.GetLength();
			if (((iStrPos + 1) < strRTFSource.GetLength()) && (strRTFSource[iStrPos + 1] == _T(' ')))
			{
				iStrPos++;   //Ignore Blank after Tag
			}
		}
		else if (strChTest == _T("\n") || strChTest == _T("\r"))
		{
			// line endings
			strCurrentText += strChTest;
		}
		else
		{
			//Normal character
			strCurrentText += CHtmlCharMap::ConvertToRep(strChTest);
		}
	} //loop thru string

	//Add last text
	if (strCurrentText != _T(""))
	{
		CHTMLElement* pElement = new CHTMLElement();
		pElement->m_enNodeType = CHTMLElement::c_nodText;
		pElement->m_strNodeText = strCurrentText;
		m_arrHTMLElements.Add(pElement);
		strCurrentText = _T("");
	}
}

CRTF_HTMLConverter::CRTFNode CRTF_HTMLConverter::R2H_BuildTree(const CString& strSource, CRTFNode* pNodeParent)
{
	//Initializing
	CString strName;

	//Extract Node's Name
	if ((strSource.GetLength() > 2) && (strSource[0] == _T('{')) && (strSource[1] == _T('\\')))
	{
		int iStrCount = strSource.GetLength();
		int iStrPos = 2;

		while (DELIM.Find(strSource[iStrPos]) == -1)
		{
			iStrPos++;
		}

		strName = strSource.Mid(2, iStrPos - 2);
	}
	else
	{
		//Invalid RTF Node. RTF Nodes must start with a { and then contain a \NAME identifier
		ASSERT(FALSE);
		return CRTFNode();
	}

	//Extract pure text
	CString strNodeText = strSource.Mid(1, strSource.GetLength() - 2);

	//Add node into tree
	CRTFNodeA nodeA;
	nodeA.m_strCode = strSource;
	nodeA.m_strName = strName;
	CRTFNode nodeThis;
	if (pNodeParent)
	{
		nodeThis = pNodeParent->AddNode(nodeA);
	}
	else
	{
		nodeThis = m_RTFTree->AddNode(nodeA);
	}

	// preallocate strings to make string building more efficient
	TCHAR* szNodeNew = new TCHAR[strSource.GetLength() + 1];
	int nLenNode = 0;

	TCHAR* szThisCode = new TCHAR[strSource.GetLength() + 1];
	int nLenCode = 0;

	//Looking for children
	long lLevel = 0; //# Of opened '{'
	int iStrPos, iStrCount = strNodeText.GetLength();

	int nChildStart = strNodeText.Find(_T('{'));
	int nChildEnd = -1;

	for (iStrPos = 0; iStrPos < iStrCount; iStrPos++)
	{
		TCHAR cTest = strNodeText[iStrPos];
		if (cTest == _T('{'))
		{
			//New element
			if (lLevel == 0)
			{
				nLenNode = 0;
				//strNodeNew.Empty();
			}
			// else Nested Element, will be added during recurse

			lLevel++;
		}

		if (lLevel > 0)
		{
			szNodeNew[nLenNode] = cTest;
			nLenNode++;
			//strNodeNew+=cTest;
		}
		else
		{
			szThisCode[nLenCode] = cTest;
			nLenCode++;
			//strThisCode+=cTest;
		}

		if (cTest == _T('}'))
		{
			ASSERT(lLevel > 0); //Invalid RTF, more closing } than opening �{
			lLevel--;
			if (lLevel == 0)
			{
				szNodeNew[nLenNode] = 0; // null terminate string
				//Recurse (new Sub-Node (child) ready
				R2H_BuildTree(szNodeNew, &nodeThis);
			}
			// else Nested Element, will be added during recurse
		}
	} //loop thru string


	// Get the plain text (without \)
	// reuse szNodeNew for efficiency
	TCHAR* szPlain = szNodeNew;
	int nLenPlain = 0;
	iStrCount = strNodeText.GetLength();

	for (iStrPos = 0; iStrPos < iStrCount; iStrPos++)
	{
		TCHAR cTest = strNodeText[iStrPos];

		if (cTest == _T('\\'))
		{
			CString strTag = R2H_GetRTFTag(strNodeText, iStrPos);
			iStrPos += strTag.GetLength();

			if (((iStrPos + 1) < strNodeText.GetLength()) && (strNodeText[iStrPos + 1] == _T(' ')))
			{
				iStrPos++;   //Ignore Blank after Tag
			}
		}
		else
		{
			//strPlain+=cTest;
			szPlain[nLenPlain] = cTest;
			nLenPlain++;
		}
	} //loop thru string

	szPlain[nLenPlain] = 0; // null terminate string
	nodeThis->m_strPlain = szPlain;//strPlain;
	szThisCode[nLenCode] = 0; // null terminate string
	nodeThis->m_strThisCode = szThisCode;//strThisCode;
	//TRACE("R2H_BuildTree(Code = %s)\n", szThisCode);

	// cleanup
	delete [] szThisCode;
	delete [] szNodeNew;

	return nodeThis;
}

CString& operator<<(CString& os, CRTF_HTMLConverter& conv)
{
	//For streaming operations
	if (conv.m_enMode == CRTF_HTMLConverter::c_modRTF2HTML)
	{
		os = conv.m_strHTML;
	}
	else
	{
		os = conv.m_strHTML;
	}
	return os;
}

CString& operator>>(CString& is, CRTF_HTMLConverter& conv)
{
	//For streaming operations
	CString strTemp;
	strTemp = is;
	//RTF->HTML
	if (conv.m_enMode == CRTF_HTMLConverter::c_modRTF2HTML)
	{
		conv.m_strRTF = strTemp;
		conv.ConvertRTF2HTML(TRUE);
	}
	return is;
}

CRTF_HTMLConverter::CHTMLElement::CHTMLElement(THTMLNodeType type, LPCTSTR szText):
m_enNodeType(type),
m_strNodeText(szText)
{
}
