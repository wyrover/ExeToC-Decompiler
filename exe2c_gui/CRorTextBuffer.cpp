
#include "stdafx.h"
#include <malloc.h>
#include "editcmd.h"
#include "CRorTextBuffer.h"
#include "CRorTextView.h"


#ifndef __AFXPRIV_H__
#pragma message("Include <afxpriv.h> in your stdafx.h to avoid this message")
#include <afxpriv.h>
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//	Line allocation granularity
#define		CHAR_ALIGN					16
#define		ALIGN_BUF_SIZE(size)		((size) / CHAR_ALIGN) * CHAR_ALIGN + CHAR_ALIGN;

#define		UNDO_BUF_SIZE				1024

const TCHAR crlf[] = _T("\r\n");

#ifdef _DEBUG
#define _ADVANCED_BUGCHECK	1
#endif


/////////////////////////////////////////////////////////////////////////////
// CRorTextBuffer

IMPLEMENT_DYNCREATE(CRorTextBuffer, CCmdTarget)


CRorTextBuffer::CRorTextBuffer()
{
}


CRorTextBuffer::~CRorTextBuffer()
{
}


BEGIN_MESSAGE_MAP(CRorTextBuffer, CCmdTarget)
	//{{AFX_MSG_MAP(CRorTextBuffer)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CRorTextBuffer message handlers


void CRorTextBuffer::FreeAll()
{
}

BOOL CRorTextBuffer::InitNew()
{
    UpdateViews();
	return TRUE;
}

static const char *crlfs[] =
{
	"\x0d\x0a",			//	DOS/Windows style
	"\x0a\x0d",			//	UNIX style
	"\x0a"				//	Macintosh style
};

BOOL CRorTextBuffer::LoadFromFile(LPCTSTR pszFileName)
{
	UpdateViews();
	return true;
}

BOOL CRorTextBuffer::SaveToFile(LPCTSTR pszFileName)
{
	return true;
}

int CRorTextBuffer::GetLineCount()
{
    int n = this->m_xml.GetLineCount();
    if (n == 0)
        return 1;
    return n;
}

int CRorTextBuffer::GetLineLength(int nLine)
{
    return this->m_xml.GetLineLength(nLine);
}

LPTSTR CRorTextBuffer::GetLineChars(int nLine)
{
    return NULL;
}


static int FlagToIndex(DWORD dwFlag)
{
	int nIndex = 0;
	while ((dwFlag & 1) == 0)
	{
		dwFlag = dwFlag >> 1;
		nIndex ++;
		if (nIndex == 32)
			return -1;
	}
	dwFlag = dwFlag & 0xFFFFFFFE;
	if (dwFlag != 0)
		return -1;
	return nIndex;
}

CString CRorTextBuffer::GetText(int nStartLine, int nStartChar, int nEndLine, int nEndChar)
{
    CString text = this->m_xml.GetText(nStartLine, nStartChar, nEndLine, nEndChar);
    return text;
}

void CRorTextBuffer::AddView(CRorTextView *pView)
{
	m_lpViews.AddTail(pView);
}

void CRorTextBuffer::RemoveView(CRorTextView *pView)
{
	POSITION pos = m_lpViews.GetHeadPosition();
	while (pos != NULL)
	{
		POSITION thispos = pos;
		CRorTextView *pvw = m_lpViews.GetNext(pos);
		if (pvw == pView)
		{
			m_lpViews.RemoveAt(thispos);
			return;
		}
	}
	ASSERT(FALSE);
}

void CRorTextBuffer::UpdateViews()
{
    //CRorTextView *pSource, CUpdateContext *pContext, DWORD dwUpdateFlags, int nLineIndex /*= -1*/
    CRorTextView *pSource = NULL;
    CUpdateContext *pContext = NULL;
    DWORD dwUpdateFlags = UPDATE_RESET;
    int nLineIndex = -1;    /*= -1*/
    //NULL, NULL, UPDATE_RESET
	POSITION pos = m_lpViews.GetHeadPosition();
	while (pos != NULL)
	{
		CRorTextView *pView = m_lpViews.GetNext(pos);
		pView->UpdateView();    //pSource, pContext, dwUpdateFlags, nLineIndex);
	}
}

#include "Change.h"

int StrToInt(PCSTR str)
{
    int d = 0;
    sscanf(str, "%d", &d);
    return d;
}

    
bool CRorTextBuffer::SetCurWord(int x, int y)
{//return true 表明换单词了
	return this->m_xml.SetCurWord(x,y);
}
bool CRorTextBuffer::OnChar(int x, int y, UINT nChar)
{
    if (nChar == 'd' || nChar == 'D')
    {
        return true;
    }
    else if (nChar == 'p' || nChar == 'P')
    {
        int n = 0;
        return true;
    }
    else if (nChar == 'n' || nChar == 'N')
    {
        CChange* dlg = new CChange;
		dlg->DoModal();
        CString newname = dlg->name;

        XMLTYPE xmltype = XT_invalid;
        PVOID p = NULL;
        this->m_xml.GetItem(x,y, xmltype, p);
        if (xmltype != XT_invalid)
        {
            return ::g_EXE2C->Rename(xmltype,p,newname);
            //this->Rename(x, y, newname);
        }
        return false;
    }
    else if (nChar == 't' || nChar == 'T')
    {
        CChange* dlg = new CChange;
		dlg->DoModal();
        CString newtype = dlg->name;

        //this->ReType(x, y, newtype);
        return true;
    }
    else if (nChar == 'a' || nChar == 'A')
    {
        CChange* dlg = new CChange;
		dlg->DoModal();
        CString s = dlg->name;

        //this->Change_Array(x, y, StrToInt(s));
        return true;
    }
    return false;
}

void CRorTextBuffer::Parse(int nLineIndex, TEXTBLOCK *pBuf, int &nActualItems)
{
    return;
}


void MyRefreshFuncList();
extern CSampleView *g_VIEW;

void MyRefreshView()
{
	g_VIEW->ResetView();
	g_VIEW->DeleteAll();
    g_VIEW->LocateTextBuffer()->m_xml.Clear();
	g_EXE2C->prtout_cpp(&g_VIEW->LocateTextBuffer()->m_xml);
	g_VIEW->Invalidate();

    MyRefreshFuncList();
}


