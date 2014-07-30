
#include "stdafx.h"
#include <malloc.h>
#include "editcmd.h"
#include "CRorTextView.h"
#include "CRorTextBuffer.h"
#include "Change.h"
#include <assert.h>

#ifndef __AFXPRIV_H__
#pragma message("Include <afxpriv.h> in your stdafx.h to avoid this message")
#include <afxpriv.h>
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define TAB_CHARACTER				_T('\xBB')
#define SPACE_CHARACTER				_T('\x95')
#define DEFAULT_PRINT_MARGIN		1000				//	10 millimeters

#define SMOOTH_SCROLL_FACTOR		6


////////////////////////////////////////////////////////////////////////////
// CRorTextView

IMPLEMENT_DYNCREATE(CRorTextView, CView)

HINSTANCE CRorTextView::s_hResourceInst = NULL;

BEGIN_MESSAGE_MAP(CRorTextView, CView)
	//{{AFX_MSG_MAP(CRorTextView)
	ON_WM_DESTROY()
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
	ON_WM_VSCROLL()
	ON_WM_SETCURSOR()
	ON_WM_LBUTTONDOWN()
	ON_WM_SETFOCUS()
	ON_WM_HSCROLL()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_TIMER()
	ON_WM_KILLFOCUS()
	ON_WM_LBUTTONDBLCLK()
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
    ON_COMMAND(ID_EDIT_SELECT_ALL, OnEditSelectAll)
    ON_WM_RBUTTONDOWN()
	ON_WM_SYSCOLORCHANGE()
	ON_WM_CREATE()
    //}}AFX_MSG_MAP
	ON_COMMAND(ID_EDIT_CHAR_LEFT, OnCharLeft)
	ON_COMMAND(ID_EDIT_EXT_CHAR_LEFT, OnExtCharLeft)
	ON_COMMAND(ID_EDIT_CHAR_RIGHT, OnCharRight)
	ON_COMMAND(ID_EDIT_EXT_CHAR_RIGHT, OnExtCharRight)
	ON_COMMAND(ID_EDIT_WORD_LEFT, OnWordLeft)
	ON_COMMAND(ID_EDIT_EXT_WORD_LEFT, OnExtWordLeft)
	ON_COMMAND(ID_EDIT_WORD_RIGHT, OnWordRight)
	ON_COMMAND(ID_EDIT_EXT_WORD_RIGHT, OnExtWordRight)
	ON_COMMAND(ID_EDIT_LINE_UP, OnLineUp)
	ON_COMMAND(ID_EDIT_EXT_LINE_UP, OnExtLineUp)
	ON_COMMAND(ID_EDIT_LINE_DOWN, OnLineDown)
	ON_COMMAND(ID_EDIT_EXT_LINE_DOWN, OnExtLineDown)
	ON_COMMAND(ID_EDIT_SCROLL_UP, ScrollUp)
	ON_COMMAND(ID_EDIT_SCROLL_DOWN, ScrollDown)
	ON_COMMAND(ID_EDIT_PAGE_UP, OnPageUp)
	ON_COMMAND(ID_EDIT_EXT_PAGE_UP, OnExtPageUp)
	ON_COMMAND(ID_EDIT_PAGE_DOWN, OnPageDown)
	ON_COMMAND(ID_EDIT_EXT_PAGE_DOWN, OnExtPageDown)
	ON_COMMAND(ID_EDIT_LINE_END, OnLineEnd)
	ON_COMMAND(ID_EDIT_EXT_LINE_END, OnExtLineEnd)
	ON_COMMAND(ID_EDIT_HOME, OnHome)
	ON_COMMAND(ID_EDIT_EXT_HOME, OnExtHome)
	ON_COMMAND(ID_EDIT_TEXT_BEGIN, OnTextBegin)
	ON_COMMAND(ID_EDIT_EXT_TEXT_BEGIN, OnExtTextBegin)
	ON_COMMAND(ID_EDIT_TEXT_END, OnTextEnd)
	ON_COMMAND(ID_EDIT_EXT_TEXT_END, OnExtTextEnd)
	//	Standard printing commands
    ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
	//	Status
    
    
END_MESSAGE_MAP()

#define EXPAND_PRIMITIVE(impl, func)	\
	void CRorTextView::On##func() { impl(FALSE); }	\
	void CRorTextView::OnExt##func() { impl(TRUE); }
	EXPAND_PRIMITIVE(MoveLeft, CharLeft)
	EXPAND_PRIMITIVE(MoveRight, CharRight)
	EXPAND_PRIMITIVE(MoveWordLeft, WordLeft)
	EXPAND_PRIMITIVE(MoveWordRight, WordRight)
	EXPAND_PRIMITIVE(MoveUp, LineUp)
	EXPAND_PRIMITIVE(MoveDown, LineDown)
	EXPAND_PRIMITIVE(MovePgUp, PageUp)
	EXPAND_PRIMITIVE(MovePgDn, PageDown)
	EXPAND_PRIMITIVE(MoveHome, Home)
	EXPAND_PRIMITIVE(MoveEnd, LineEnd)
	EXPAND_PRIMITIVE(MoveCtrlHome, TextBegin)
	EXPAND_PRIMITIVE(MoveCtrlEnd, TextEnd)
#undef EXPAND_PRIMITIVE


/////////////////////////////////////////////////////////////////////////////
// CRorTextView construction/destruction

CRorTextView::CRorTextView()
{
	AFX_ZERO_INIT_OBJECT(CScrollView);
	ResetView();
}

CRorTextView::~CRorTextView()
{
	ASSERT(m_hAccel == NULL);
	ASSERT(m_pCacheBitmap == NULL);
	ASSERT(m_pTextBuffer == NULL);		//	Must be correctly detached
}

BOOL CRorTextView::PreCreateWindow(CREATESTRUCT& cs)
{
	CWnd *pParentWnd = CWnd::FromHandlePermanent(cs.hwndParent);
	if (pParentWnd == NULL || ! pParentWnd->IsKindOf(RUNTIME_CLASS(CSplitterWnd)))
	{
		//	View must always create its own scrollbars,
		//	if only it's not used within splitter
		cs.style |= (WS_HSCROLL | WS_VSCROLL);
	}
	cs.lpszClass = AfxRegisterWndClass(CS_DBLCLKS);
	return CScrollView::PreCreateWindow(cs);
}


/////////////////////////////////////////////////////////////////////////////
// CRorTextView drawing

void CRorTextView::GetSelection(CPoint &ptStart, CPoint &ptEnd)
{
	PrepareSelBounds();
	ptStart = m_ptDrawSelStart;
	ptEnd = m_ptDrawSelEnd;
}

CRorTextBuffer *CRorTextView::LocateTextBuffer()
{
	return NULL;
}

void CRorTextView::ScrollToChar(int nNewOffsetChar)
{
    //	For now, ignoring bNoSmoothScroll and m_bSmoothScroll
	if (m_nOffsetChar != nNewOffsetChar)
	{
		int nScrollChars = m_nOffsetChar - nNewOffsetChar;
		m_nOffsetChar = nNewOffsetChar;
		CRect rcScroll;
		GetClientRect(&rcScroll);
		ScrollWindow(nScrollChars * GetCharWidth(), 0, &rcScroll, &rcScroll);
		UpdateWindow();
		RecalcHorzScrollBar(TRUE);
	}
    
}

void CRorTextView::ScrollToLine(int nNewTopLine, BOOL bNoSmoothScroll /*= FALSE*/, BOOL bTrackScrollBar /*= TRUE*/)
{
	if (m_nTopLine != nNewTopLine)
	{
			int nScrollLines = m_nTopLine - nNewTopLine;
			m_nTopLine = nNewTopLine;
			ScrollWindow(0, nScrollLines * GetLineHeight());
			UpdateWindow();
			if (bTrackScrollBar)
				RecalcVertScrollBar(TRUE);
	}
}

void CRorTextView::PointTrans_ImageToChar(IN CPoint& pt1, OUT CPoint& pt2)
{
    pt2.x = pt1.x / GetCharWidth();
    pt2.y = pt1.y / GetLineHeight();
}
void CRorTextView::PointTrans_CharToImage(IN CPoint& pt1, OUT CPoint& pt2)
{
    pt2.x = pt1.x * GetCharWidth();
    pt2.y = pt1.y * GetLineHeight();
}
void CRorTextView::DrawLineHelperImpl(CDC *pdc, CPoint &ptOrigin, 
									 LPCTSTR pszChars, int nCount)
{
    //this->DrawLineHelperImpl_1(pdc,ptOrigin,pszChars,nCount);
    //return;
    
    CPoint ptchar;
    PointTrans_ImageToChar(ptOrigin, ptchar);
    //ptchar = ptOrigin;
    
    this->DrawLineHelperImpl_1(pdc,ptchar,pszChars,nCount);

    PointTrans_CharToImage(ptchar, ptOrigin);
}
void CRorTextView::DrawLineHelperImpl_1(CDC *pdc, CPoint &ptOrigin, 
                                            LPCTSTR pszChars, int nCount)
{
	ASSERT(nCount >= 0);
	if (nCount > 0)
	{
        VERIFY(pdc->ExtTextOut(ptOrigin.x * GetCharWidth(), 
                               ptOrigin.y * GetLineHeight(), 
                               ETO_CLIPPED, NULL, pszChars, 
                               nCount,
                               NULL));
		ptOrigin.x += nCount;
	}
}

void CRorTextView::DrawLineHelper(CDC *pdc, CPoint &ptOrigin, 
									 LPCTSTR pszChars, int nCount, CPoint ptTextPos)
{
	if (nCount <= 0)
        return;

    //PointTrans_CharToImage(ptTextPos, ptOrigin);
    //DrawLineHelperImpl(pdc, ptOrigin, pszChars, nCount);

    //DrawLineHelperImpl(pdc, ptTextPos, pszChars, nCount);
    //PointTrans_CharToImage(ptTextPos, ptOrigin);
    //return;
	
    //PointTrans_ImageToChar(ptOrigin, ptTextPos);
    if (m_bFocused)
    {
        int nSelBegin = 0, nSelEnd = 0;
        if (m_ptDrawSelStart.y > ptTextPos.y)
        {
            nSelBegin = nCount;
        }
        else
        if (m_ptDrawSelStart.y == ptTextPos.y)
        {
            nSelBegin = m_ptDrawSelStart.x - ptTextPos.x;
            if (nSelBegin < 0)
                nSelBegin = 0;
            if (nSelBegin > nCount)
                nSelBegin = nCount;
        }
        if (m_ptDrawSelEnd.y > ptTextPos.y)
        {
            nSelEnd = nCount;
        }
        else
        if (m_ptDrawSelEnd.y == ptTextPos.y)
        {
            nSelEnd = m_ptDrawSelEnd.x - ptTextPos.x;
            if (nSelEnd < 0)
                nSelEnd = 0;
            if (nSelEnd > nCount)
                nSelEnd = nCount;
        }

        ASSERT(nSelBegin >= 0 && nSelBegin <= nCount);
        ASSERT(nSelEnd >= 0 && nSelEnd <= nCount);
        ASSERT(nSelBegin <= nSelEnd);

        //	Draw part of the text before selection
        if (nSelBegin > 0)
        {
            DrawLineHelperImpl(pdc, ptOrigin, pszChars, nSelBegin);
        }
        if (nSelBegin < nSelEnd)
        {
            COLORREF crOldBk = pdc->SetBkColor(GetColor(COLORINDEX_SELBKGND));
            COLORREF crOldText = pdc->SetTextColor(GetColor(COLORINDEX_SELTEXT));
            DrawLineHelperImpl(pdc, ptOrigin, pszChars + nSelBegin, nSelEnd - nSelBegin);
            pdc->SetBkColor(crOldBk);
            pdc->SetTextColor(crOldText);
        }
        if (nSelEnd < nCount)
        {
            if (nSelEnd == 0)
            {
                //int yellow_begin = 0, yellow_end = 0;
                //this->LocateTextBuffer()->
                DrawLineHelperImpl(pdc, ptOrigin, pszChars, nCount);
            }
            else
                DrawLineHelperImpl(pdc, ptOrigin, pszChars + nSelEnd, nCount - nSelEnd);
        }
    }
    else
    {
        DrawLineHelperImpl(pdc, ptOrigin, pszChars, nCount);
    }
}

void CRorTextView::func1(CDC *pdc, TEXTBLOCK *pBuf, int I, int nLength,
                             CPoint& origin,
                             LPCTSTR pszChars, int nLineIndex)
{
    ASSERT(pBuf[I].m_nCharPos >= 0 && pBuf[I].m_nCharPos <= nLength);
    pdc->SetTextColor(GetColor(pBuf[I].m_nColorIndex));
    //pdc->SelectObject(GetFont_1());
    DrawLineHelper(pdc, origin, 
                   pszChars + pBuf[I].m_nCharPos, 
                   pBuf[I + 1].m_nCharPos - pBuf[I].m_nCharPos,
                   CPoint(pBuf[I].m_nCharPos, nLineIndex));
}

void CRorTextView::DrawSingleLine(CDC *pdc, int nLineIndex)
{
	return;	//not use anymore
	ASSERT(nLineIndex >= 0 && nLineIndex < GetLineCount());

	//	Acquire the background color for the current line
	int nLength = GetLineLength(nLineIndex);
	if (nLength == 0)
	{
		//	Draw the empty line
		if ((m_bFocused) && IsInsideSelBlock(CPoint(0, nLineIndex)))
		{
			pdc->FillSolidRect(0, 0, GetCharWidth(), 99, 
                               GetColor(COLORINDEX_SELBKGND));
		}
		return;
	}

	//	Parse the line
	LPCTSTR pszChars = GetLineChars(nLineIndex);
    TEXTBLOCK *pBuf = (TEXTBLOCK *) _alloca(sizeof(TEXTBLOCK) * nLength * 3);
        //不需要 free ?
	int nBlocks = 0;
    
    this->m_pTextBuffer->Parse(nLineIndex, pBuf, nBlocks);
    
	//	Draw the line text
	CPoint origin(0 - m_nOffsetChar * GetCharWidth(), 0);

	if (nBlocks > 0)
	{
		ASSERT(pBuf[0].m_nCharPos >= 0 && pBuf[0].m_nCharPos <= nLength);
		pdc->SetTextColor(GetColor(COLORINDEX_NORMALTEXT));
		//pdc->SelectObject(GetFont_1());
		DrawLineHelper(pdc, origin, pszChars, pBuf[0].m_nCharPos, CPoint(0, nLineIndex));
		for (int I = 0; I < nBlocks - 1; I ++)
		{
			func1(pdc, pBuf, I, nLength, origin, pszChars, nLineIndex);
		}
		ASSERT(pBuf[nBlocks - 1].m_nCharPos >= 0 && pBuf[nBlocks - 1].m_nCharPos <= nLength);
		pdc->SetTextColor(GetColor(pBuf[nBlocks - 1].m_nColorIndex));
		//pdc->SelectObject(GetFont_1());
		DrawLineHelper(pdc, origin, 
                       pszChars + pBuf[nBlocks - 1].m_nCharPos, 
                       nLength - pBuf[nBlocks - 1].m_nCharPos,
                       CPoint(pBuf[nBlocks - 1].m_nCharPos, nLineIndex));
	}
	else
	{
		pdc->SetTextColor(GetColor(COLORINDEX_NORMALTEXT));
		//pdc->SelectObject(GetFont_1());
		DrawLineHelper(pdc, origin, pszChars, nLength, CPoint(0, nLineIndex));
	}
}

COLORREF CRorTextView::GetColor(int nColorIndex)
{
	switch (nColorIndex)
	{
    case COLORINDEX_0: return RGB(25, 125, 125);
    case COLORINDEX_func: return RGB(255, 25, 2);
    case COLOR_Var:
    case COLOR_VarH: return RGB(155, 205, 2);
    case COLOR_Immed: return RGB(5, 125, 62);
    case COLOR_ea: return RGB(95, 225, 2);
    case COLOR_type: return RGB(195, 65, 82);
    case COLOR_label:   return RGB(82, 195, 25);


	case COLORINDEX_WHITESPACE:
	case COLORINDEX_BKGND:
		return RGB(0, 0, 0);//::GetSysColor(COLOR_WINDOW);
	case COLORINDEX_NORMALTEXT:
		return RGB(250,250,250);    //::GetSysColor(COLOR_WINDOWTEXT);
	case COLORINDEX_SELMARGIN:
		return ::GetSysColor(COLOR_SCROLLBAR);
	case COLORINDEX_PREPROCESSOR:
		return RGB(0, 128, 192);
	case COLORINDEX_COMMENT:
		return RGB(128, 128, 128);
	//	[JRT]: Enabled Support For Numbers...
	case COLORINDEX_NUMBER:
		return RGB(0x80, 0x00, 0x00);
	//	[JRT]: Support For C/C++ Operators
	case COLORINDEX_OPERATOR:
		return RGB(0x00, 0x00, 0x00);
	case COLORINDEX_KEYWORD:
		return RGB(0, 0, 255);
	case COLORINDEX_SELBKGND:
		return RGB(0, 0, 125);
	case COLORINDEX_SELTEXT:
		return RGB(255, 255, 255);
	}
	return RGB(255, 0, 0);
}

BOOL CRorTextView::IsInsideSelBlock(CPoint ptTextPos)
{
    CPoint pt3 = ptTextPos;
    CPoint pt1 = m_ptDrawSelStart; 
    CPoint pt2 = m_ptDrawSelEnd;
	ASSERT_VALIDTEXTPOS(pt3);
	if (pt3.y < pt1.y)
		return FALSE;
	if (pt3.y > pt2.y)
		return FALSE;
	if (pt3.y < pt2.y && pt3.y > pt1.y)
		return TRUE;
	if (pt1.y < pt2.y)
	{
		if (pt3.y == pt2.y)
			return pt3.x < pt2.x;
		ASSERT(pt3.y == pt1.y);
		return pt3.x >= pt1.x;
	}
	ASSERT(pt1.y == pt2.y);
	return pt3.x >= pt1.x && pt3.x < pt2.x;
}

BOOL CRorTextView::IsInsideSelection(const CPoint &ptTextPos)
{
	PrepareSelBounds();
	return IsInsideSelBlock(ptTextPos);
}

void CRorTextView::PrepareSelBounds()
{
	if (m_ptSelStart.y < m_ptSelEnd.y ||
			(m_ptSelStart.y == m_ptSelEnd.y && m_ptSelStart.x < m_ptSelEnd.x))
	{
		m_ptDrawSelStart = m_ptSelStart;
		m_ptDrawSelEnd = m_ptSelEnd;
	}
	else
	{
		m_ptDrawSelStart = m_ptSelEnd;
		m_ptDrawSelEnd = m_ptSelStart;
	}
}


void CRorTextView::ResetView()
{
	m_nTopLine = 0;
	m_nOffsetChar = 0;
	m_nLineHeight = -1;
	m_nCharWidth = -1;
    m_nMaxLineLength = -1;
	m_nScreenLines = -1;
	m_nScreenChars = -1;
    m_ptAnchor.x = 0;
	m_ptAnchor.y = 0;
	if (m_pIcons != NULL)
	{
		delete m_pIcons;
		m_pIcons = NULL;
	}
	{
		if (m_apFont != NULL)
		{
			m_apFont->DeleteObject();
			delete m_apFont;
			m_apFont = NULL;
		}
	}
	m_nParseArraySize = 0;
	m_ptCursorPos.x = 0;
	m_ptCursorPos.y = 0;
	m_ptSelStart = m_ptSelEnd = m_ptCursorPos;
    if (::IsWindow(m_hWnd))
		UpdateCaret();
}

void CRorTextView::UpdateCaret()
{
	ASSERT_VALIDTEXTPOS(m_ptCursorPos);
	if (m_bFocused && m_ptCursorPos.x >= m_nOffsetChar)
	{
		CreateSolidCaret(2, GetLineHeight());
		SetCaretPos(TextToClient(m_ptCursorPos));
		ShowCaret();
	}
	else
	{
		HideCaret();
	}
}


CFont *CRorTextView::GetFont_1()
{
	if (m_apFont == NULL)
	{
        LOGFONT m_lfBaseFont;
        memset(&m_lfBaseFont, 0, sizeof(m_lfBaseFont));
        strcpy(m_lfBaseFont.lfFaceName, "Courier");
        m_lfBaseFont.lfHeight = 0;
        m_lfBaseFont.lfWeight = FW_NORMAL;
        m_lfBaseFont.lfItalic = FALSE;
        m_lfBaseFont.lfOutPrecision = OUT_DEFAULT_PRECIS;
        m_lfBaseFont.lfClipPrecision = CLIP_DEFAULT_PRECIS;
        m_lfBaseFont.lfQuality = DEFAULT_QUALITY;
        m_lfBaseFont.lfCharSet = ANSI_CHARSET;
        m_lfBaseFont.lfPitchAndFamily = DEFAULT_PITCH | FF_DONTCARE;

		m_apFont = new CFont;
		if (! m_apFont->CreateFontIndirect(&m_lfBaseFont))
		{
			delete m_apFont;
			m_apFont = NULL;
			return CView::GetFont();
		}

	}
	return m_apFont;
}

void CRorTextView::CalcLineCharDim()
{
	CDC *pdc = GetDC();
	CFont *pOldFont = pdc->SelectObject(GetFont_1());
	CSize szCharExt = pdc->GetTextExtent(_T("X"));
	m_nLineHeight = szCharExt.cy;
	if (m_nLineHeight < 1)
		m_nLineHeight = 1;
	m_nCharWidth = szCharExt.cx;
	pdc->SelectObject(pOldFont);
	ReleaseDC(pdc);
}

int CRorTextView::GetLineHeight()
{
	if (m_nLineHeight == -1)
		CalcLineCharDim();
	return m_nLineHeight;
}

int CRorTextView::GetCharWidth()
{
	if (m_nCharWidth == -1)
		CalcLineCharDim();
	return m_nCharWidth;
}

int CRorTextView::GetMaxLineLength()
{
	if (m_nMaxLineLength == -1)
	{
		m_nMaxLineLength = 0;
		int nLineCount = GetLineCount();
		for (int I = 0; I < nLineCount; I ++)
		{
			int nActualLength = GetLineLength(I);
			if (m_nMaxLineLength < nActualLength)
				m_nMaxLineLength = nActualLength;
		}
	}
	return m_nMaxLineLength;
}

CRorTextView *CRorTextView::GetSiblingView(int nRow, int nCol)
{
	CSplitterWnd *pSplitter = GetParentSplitter(this, FALSE);
	if (pSplitter == NULL)
		return NULL;
	CWnd *pWnd = CWnd::FromHandlePermanent(
		::GetDlgItem(pSplitter->m_hWnd, pSplitter->IdFromRowCol(nRow, nCol)));
	if (pWnd == NULL || ! pWnd->IsKindOf(RUNTIME_CLASS(CRorTextView)))
		return NULL;
	return (CRorTextView *) pWnd;
}

void CRorTextView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	AttachToBuffer(NULL);

	CSplitterWnd *pSplitter = GetParentSplitter(this, FALSE);
	if (pSplitter != NULL)
	{
		//	See CSplitterWnd::IdFromRowCol() implementation
		int nRow = (GetDlgCtrlID() - AFX_IDW_PANE_FIRST) / 16;
		int nCol = (GetDlgCtrlID() - AFX_IDW_PANE_FIRST) % 16;
		ASSERT(nRow >= 0 && nRow < pSplitter->GetRowCount());
		ASSERT(nCol >= 0 && nCol < pSplitter->GetColumnCount());

		if (nRow > 0)
		{
			CRorTextView *pSiblingView = GetSiblingView(0, nCol);
			if (pSiblingView != NULL && pSiblingView != this)
			{
				m_nOffsetChar = pSiblingView->m_nOffsetChar;
				ASSERT(m_nOffsetChar >= 0 && m_nOffsetChar <= GetMaxLineLength());
			}
		}

		if (nCol > 0)
		{
			CRorTextView *pSiblingView = GetSiblingView(nRow, 0);
			if (pSiblingView != NULL && pSiblingView != this)
			{
				m_nTopLine = pSiblingView->m_nTopLine;
				ASSERT(m_nTopLine >= 0 && m_nTopLine < GetLineCount());
			}
		}
	}
}


/////////////////////////////////////////////////////////////////////////////
// CRorTextView printing

void CRorTextView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo) 
{
	CView::OnPrepareDC(pDC, pInfo);
}

/////////////////////////////////////////////////////////////////////////////
// CRorTextView message handlers

int CRorTextView::GetLineCount()
{
	if (m_pTextBuffer == NULL)
		return 1;		//	Single empty line
	int nLineCount = m_pTextBuffer->GetLineCount();
	ASSERT(nLineCount > 0);
	return nLineCount;
}

int CRorTextView::GetLineLength(int nLineIndex)
{
	if (m_pTextBuffer == NULL)
		return 0;
	return m_pTextBuffer->GetLineLength(nLineIndex);
}

LPCTSTR CRorTextView::GetLineChars(int nLineIndex)
{
	if (m_pTextBuffer == NULL)
		return NULL;
	return m_pTextBuffer->GetLineChars(nLineIndex);
}

void CRorTextView::AttachToBuffer(CRorTextBuffer *pBuf /*= NULL*/)
{
	if (m_pTextBuffer != NULL)
		m_pTextBuffer->RemoveView(this);
	if (pBuf == NULL)
	{
		pBuf = LocateTextBuffer();
		//	...
	}
	m_pTextBuffer = pBuf;
	if (m_pTextBuffer != NULL)
		m_pTextBuffer->AddView(this);
	ResetView();

	//	Init scrollbars
	CScrollBar *pVertScrollBarCtrl = GetScrollBarCtrl(SB_VERT);
	if (pVertScrollBarCtrl != NULL)
		pVertScrollBarCtrl->EnableScrollBar(GetScreenLines() >= GetLineCount() ?
											ESB_DISABLE_BOTH : ESB_ENABLE_BOTH);
	CScrollBar *pHorzScrollBarCtrl = GetScrollBarCtrl(SB_HORZ);
	if (pHorzScrollBarCtrl != NULL)
		pHorzScrollBarCtrl->EnableScrollBar(GetScreenChars() >= GetMaxLineLength() ?
											ESB_DISABLE_BOTH : ESB_ENABLE_BOTH);

	//	Update scrollbars
	RecalcVertScrollBar();
	RecalcHorzScrollBar();
}

void CRorTextView::DetachFromBuffer()
{
	if (m_pTextBuffer != NULL)
	{
		m_pTextBuffer->RemoveView(this);
		m_pTextBuffer = NULL;
		ResetView();
	}
}

int CRorTextView::GetScreenLines()
{
	if (m_nScreenLines == -1)
	{
		CRect rect;
		GetClientRect(&rect);
		m_nScreenLines = rect.Height() / GetLineHeight();
	}
	return m_nScreenLines;
}

int CRorTextView::GetScreenChars()
{
	if (m_nScreenChars == -1)
	{
		CRect rect;
		GetClientRect(&rect);
		m_nScreenChars = rect.Width() / GetCharWidth();
	}
	return m_nScreenChars;
}

void MyRefreshView();
void CRorTextView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
    CScrollView::OnChar(nChar,nRepCnt,nFlags);
        
    if (this->m_pTextBuffer->OnChar(this->m_ptCursorPos.x, this->m_ptCursorPos.y, nChar))
    {
		//Invalidate();
        MyRefreshView();
    }
}
void CRorTextView::OnDestroy() 
{
	DetachFromBuffer();
	m_hAccel = NULL;

	CView::OnDestroy();

	{
		if (m_apFont != NULL)
		{
			m_apFont->DeleteObject();
			delete m_apFont;
			m_apFont = NULL;
		}
	}
	if (m_pCacheBitmap != NULL)
	{
		delete m_pCacheBitmap;
		m_pCacheBitmap = NULL;
	}
}


void CRorTextView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	if (m_pCacheBitmap != NULL)
	{
		m_pCacheBitmap->DeleteObject();
		delete m_pCacheBitmap;
		m_pCacheBitmap = NULL;
	}
	m_nScreenLines = -1;
	m_nScreenChars = -1;
	RecalcVertScrollBar();
	RecalcHorzScrollBar();
}

void CRorTextView::UpdateSiblingScrollPos(BOOL bHorz)
{
	CSplitterWnd *pSplitterWnd = GetParentSplitter(this, FALSE);
	if (pSplitterWnd != NULL)
	{
		//	See CSplitterWnd::IdFromRowCol() implementation for details
		int nCurrentRow = (GetDlgCtrlID() - AFX_IDW_PANE_FIRST) / 16;
		int nCurrentCol = (GetDlgCtrlID() - AFX_IDW_PANE_FIRST) % 16;
		ASSERT(nCurrentRow >= 0 && nCurrentRow < pSplitterWnd->GetRowCount());
		ASSERT(nCurrentCol >= 0 && nCurrentCol < pSplitterWnd->GetColumnCount());

		if (bHorz)
		{
			int nCols = pSplitterWnd->GetColumnCount();
			for (int nCol = 0; nCol < nCols; nCol ++)
			{
				if (nCol != nCurrentCol)	//	We don't need to update ourselves
				{
					CRorTextView *pSiblingView = GetSiblingView(nCurrentRow, nCol);
					if (pSiblingView != NULL)
						pSiblingView->OnUpdateSibling(this, TRUE);
				}
			}
		}
		else
		{
			int nRows = pSplitterWnd->GetRowCount();
			for (int nRow = 0; nRow < nRows; nRow ++)
			{
				if (nRow != nCurrentRow)	//	We don't need to update ourselves
				{
					CRorTextView *pSiblingView = GetSiblingView(nRow, nCurrentCol);
					if (pSiblingView != NULL)
						pSiblingView->OnUpdateSibling(this, FALSE);
				}
			}
		}
	}
}

void CRorTextView::OnUpdateSibling(CRorTextView *pUpdateSource, BOOL bHorz)
{
	if (pUpdateSource != this)
	{
		ASSERT(pUpdateSource != NULL);
		ASSERT_KINDOF(CRorTextView, pUpdateSource);
		if (bHorz)
		{
			ASSERT(pUpdateSource->m_nTopLine >= 0);
			ASSERT(pUpdateSource->m_nTopLine < GetLineCount());
			if (pUpdateSource->m_nTopLine != m_nTopLine)
			{
				ScrollToLine(pUpdateSource->m_nTopLine, TRUE, FALSE);
				UpdateCaret();
			}
		}
		else
		{
			ASSERT(pUpdateSource->m_nOffsetChar >= 0);
			ASSERT(pUpdateSource->m_nOffsetChar < GetMaxLineLength());
			if (pUpdateSource->m_nOffsetChar != m_nOffsetChar)
			{
				ScrollToChar(pUpdateSource->m_nOffsetChar);
				UpdateCaret();
			}
		}
	}
}

void CRorTextView::RecalcVertScrollBar(BOOL bPositionOnly /*= FALSE*/)
{
	SCROLLINFO si;
	si.cbSize = sizeof(si);
	if (bPositionOnly)
	{
		si.fMask = SIF_POS;
		si.nPos = m_nTopLine;
	}
	else
	{
		if (GetScreenLines() >= GetLineCount() && m_nTopLine > 0)
		{
			m_nTopLine = 0;
			Invalidate();
			UpdateCaret();
		}
		si.fMask = SIF_DISABLENOSCROLL | SIF_PAGE | SIF_POS | SIF_RANGE;
		si.nMin = 0;
		si.nMax = GetLineCount() - 1;
		si.nPage = GetScreenLines();
		si.nPos = m_nTopLine;
	}
	VERIFY(SetScrollInfo(SB_VERT, &si));
}

void CRorTextView::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	CView::OnVScroll(nSBCode, nPos, pScrollBar);

	//	Note we cannot use nPos because of its 16-bit nature
	SCROLLINFO si;
	si.cbSize = sizeof(si);
	si.fMask = SIF_ALL;
	VERIFY(GetScrollInfo(SB_VERT, &si));

	int nPageLines = GetScreenLines();
	int nLineCount = GetLineCount();

	int nNewTopLine;
	BOOL bDisableSmooth = TRUE;
	switch (nSBCode)
	{
	case SB_TOP:
		nNewTopLine = 0;
		bDisableSmooth = FALSE;
		break;
	case SB_BOTTOM:
		nNewTopLine = nLineCount - nPageLines + 1;
		bDisableSmooth = FALSE;
		break;
	case SB_LINEUP:
		nNewTopLine = m_nTopLine - 1;
		break;
	case SB_LINEDOWN:
		nNewTopLine = m_nTopLine + 1;
		break;
	case SB_PAGEUP:
		nNewTopLine = m_nTopLine - si.nPage + 1;
		bDisableSmooth = FALSE;
		break;
	case SB_PAGEDOWN:
		nNewTopLine = m_nTopLine + si.nPage - 1;
		bDisableSmooth = FALSE;
		break;
	case SB_THUMBPOSITION:
	case SB_THUMBTRACK:
		nNewTopLine = si.nTrackPos;
		break;
	default:
		return;
	}

	if (nNewTopLine < 0)
		nNewTopLine = 0;
	if (nNewTopLine >= nLineCount)
		nNewTopLine = nLineCount - 1;
	ScrollToLine(nNewTopLine, bDisableSmooth);
}

void CRorTextView::RecalcHorzScrollBar(BOOL bPositionOnly /*= FALSE*/)
{
	//	Again, we cannot use nPos because it's 16-bit
	SCROLLINFO si;
	si.cbSize = sizeof(si);
	if (bPositionOnly)
	{
		si.fMask = SIF_POS;
		si.nPos = m_nOffsetChar;
	}
	else
	{
		if (GetScreenChars() >= GetMaxLineLength() && m_nOffsetChar > 0)
		{
			m_nOffsetChar = 0;
			Invalidate();
			UpdateCaret();
		}
		si.fMask = SIF_DISABLENOSCROLL | SIF_PAGE | SIF_POS | SIF_RANGE;
		si.nMin = 0;
		si.nMax = GetMaxLineLength() - 1;
		si.nPage = GetScreenChars();
		si.nPos = m_nOffsetChar;
	}
	VERIFY(SetScrollInfo(SB_HORZ, &si));
}

void CRorTextView::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	CView::OnHScroll(nSBCode, nPos, pScrollBar);

	SCROLLINFO si;
	si.cbSize = sizeof(si);
	si.fMask = SIF_ALL;
	VERIFY(GetScrollInfo(SB_HORZ, &si));

	int nPageChars = GetScreenChars();
	int nMaxLineLength = GetMaxLineLength();

	int nNewOffset;
	switch (nSBCode)
	{
	case SB_LEFT:
		nNewOffset = 0;
		break;
	case SB_BOTTOM:
		nNewOffset = nMaxLineLength - nPageChars + 1;
		break;
	case SB_LINEUP:
		nNewOffset = m_nOffsetChar - 1;
		break;
	case SB_LINEDOWN:
		nNewOffset = m_nOffsetChar + 1;
		break;
	case SB_PAGEUP:
		nNewOffset = m_nOffsetChar - si.nPage + 1;
		break;
	case SB_PAGEDOWN:
		nNewOffset = m_nOffsetChar + si.nPage - 1;
		break;
	case SB_THUMBPOSITION:
	case SB_THUMBTRACK:
		nNewOffset = si.nTrackPos;
		break;
	default:
		return;
	}

	if (nNewOffset >= nMaxLineLength)
		nNewOffset = nMaxLineLength - 1;
	if (nNewOffset < 0)
		nNewOffset = 0;
	ScrollToChar(nNewOffset);
	UpdateCaret();
}

BOOL CRorTextView::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	if (nHitTest == HTCLIENT)
	{
		CPoint pt;
		::GetCursorPos(&pt);
		ScreenToClient(&pt);
		if (pt.x < 0)
		{
			::SetCursor(::LoadCursor(GetResourceHandle(), MAKEINTRESOURCE(IDR_MARGIN_CURSOR)));
		}
		else
		{
			CPoint ptText = ClientToText(pt);
			PrepareSelBounds();
		}
		return TRUE;
	}
	return CView::OnSetCursor(pWnd, nHitTest, message);
}

CPoint CRorTextView::ClientToText(const CPoint &point)
{
	int nLineCount = GetLineCount();

	CPoint pt;
	pt.y = m_nTopLine + point.y / GetLineHeight();
	if (pt.y >= nLineCount)
		pt.y = nLineCount - 1;
	if (pt.y < 0)
		pt.y = 0;

	int nLength = 0;
	if (pt.y >= 0 && pt.y < nLineCount)
	{
		nLength = GetLineLength(pt.y);
	}

	int nPos = m_nOffsetChar + (point.x) / GetCharWidth();
	if (nPos < 0)
		nPos = 0;

	int nIndex = 0, nCurPos = 0;
	while (nIndex < nLength)
	{
		nCurPos ++;

		if (nCurPos > nPos)
			break;

		nIndex ++;
	}

	ASSERT(nIndex >= 0 && nIndex <= nLength);
	pt.x = nIndex;
	return pt;
}

#ifdef _DEBUG
void CRorTextView::AssertValidTextPos(const CPoint &point)
{
	if (GetLineCount() > 0)
	{
		ASSERT(m_nTopLine >= 0 && m_nOffsetChar >= 0);
		ASSERT(point.y >= 0 && point.y < GetLineCount());
		ASSERT(point.x >= 0 && point.x <= GetLineLength(point.y));
	}
}
#endif

CPoint CRorTextView::TextToClient(const CPoint &point)
{
	ASSERT_VALIDTEXTPOS(point);

	CPoint pt;
	pt.y = (point.y - m_nTopLine) * GetLineHeight();
	pt.x = (point.x - m_nOffsetChar) * GetCharWidth();
	return pt;
}

void CRorTextView::InvalidateLines(int nLine1, int nLine2, BOOL bInvalidateMargin /*= FALSE*/)
{
	bInvalidateMargin = TRUE;
	if (nLine2 == -1)
	{
		CRect rcInvalid;
		GetClientRect(&rcInvalid);
		rcInvalid.top = (nLine1 - m_nTopLine) * GetLineHeight();
		InvalidateRect(&rcInvalid, FALSE);
	}
	else
	{
		if (nLine2 < nLine1)
		{
			int nTemp = nLine1;
			nLine1 = nLine2;
			nLine2 = nTemp;
		}
		CRect rcInvalid;
		GetClientRect(&rcInvalid);
		rcInvalid.top = (nLine1 - m_nTopLine) * GetLineHeight();
		rcInvalid.bottom = (nLine2 - m_nTopLine + 1) * GetLineHeight();
		InvalidateRect(&rcInvalid, FALSE);
	}
}

void CRorTextView::SetSelection(const CPoint &ptStart, const CPoint &ptEnd)
{
	ASSERT_VALIDTEXTPOS(ptStart);
	ASSERT_VALIDTEXTPOS(ptEnd);
	if (m_ptSelStart == ptStart)
	{
		if (m_ptSelEnd != ptEnd)
			InvalidateLines(ptEnd.y, m_ptSelEnd.y);
	}
	else
	{
		InvalidateLines(ptStart.y, ptEnd.y);
		InvalidateLines(m_ptSelStart.y, m_ptSelEnd.y);
	}
	m_ptSelStart = ptStart;
	m_ptSelEnd = ptEnd;
}

void CRorTextView::AdjustTextPoint(CPoint &point)
{
	point.x += GetCharWidth() / 2;	//todo
}

void CRorTextView::OnSetFocus(CWnd* pOldWnd) 
{
	CView::OnSetFocus(pOldWnd);

	m_bFocused = TRUE;
	if (m_ptSelStart != m_ptSelEnd)
		InvalidateLines(m_ptSelStart.y, m_ptSelEnd.y);
	UpdateCaret();
}


int CRorTextView::ApproxActualOffset(int nLineIndex, int nOffset)
{
	if (nOffset == 0)
		return 0;

    nOffset--;

	int nLength = GetLineLength(nLineIndex);
    	
	return min(nLength, nOffset);
}

void CRorTextView::EnsureVisible(CPoint pt)
{
	//	Scroll vertically
	int nLineCount = GetLineCount();
	int nNewTopLine = m_nTopLine;
	if (pt.y >= nNewTopLine + GetScreenLines())
	{
		nNewTopLine = pt.y - GetScreenLines() + 1;
	}
	if (pt.y < nNewTopLine)
	{
		nNewTopLine = pt.y;
	}

	if (nNewTopLine < 0)
		nNewTopLine = 0;
	if (nNewTopLine >= nLineCount)
		nNewTopLine = nLineCount - 1;

	if (m_nTopLine != nNewTopLine)
	{
		ScrollToLine(nNewTopLine);
		UpdateSiblingScrollPos(TRUE);
	}

	//	Scroll horizontally
	int nActualPos = pt.x;
	int nNewOffset = m_nOffsetChar;
	if (nActualPos > nNewOffset + GetScreenChars())
	{
		nNewOffset = nActualPos - GetScreenChars();
	}
	if (nActualPos < nNewOffset)
	{
		nNewOffset = nActualPos;
	}

	if (nNewOffset >= GetMaxLineLength())
		nNewOffset = GetMaxLineLength() - 1;
	if (nNewOffset < 0)
		nNewOffset = 0;

	if (m_nOffsetChar != nNewOffset)
	{
		ScrollToChar(nNewOffset);
		UpdateCaret();
		UpdateSiblingScrollPos(FALSE);
	}
}

void CRorTextView::OnKillFocus(CWnd* pNewWnd) 
{
	CView::OnKillFocus(pNewWnd);

	m_bFocused = FALSE;
	UpdateCaret();
	if (m_ptSelStart != m_ptSelEnd)
		InvalidateLines(m_ptSelStart.y, m_ptSelEnd.y);
    //ReleaseCapture();
}

CString CRorTextView::GetText(const CPoint &ptStart, const CPoint &ptEnd)
{
	if (m_pTextBuffer != NULL)
		return m_pTextBuffer->GetText(ptStart.y, ptStart.x, ptEnd.y, ptEnd.x);
	return _T("");
}

void CRorTextView::UpdateView()
{
    //CRorTextView *pSource, CUpdateContext *pContext, DWORD dwFlags, int nLineIndex /*= -1*/
    CRorTextView *pSource = NULL;
    CUpdateContext *pContext = NULL;
    DWORD dwFlags = UPDATE_RESET;
    int nLineIndex = -1;    /*= -1*/
	if (dwFlags & UPDATE_RESET)
	{
		ResetView();
		RecalcVertScrollBar();
		RecalcHorzScrollBar();
		return;
	}

	int nLineCount = GetLineCount();
	ASSERT(nLineCount > 0);
	ASSERT(nLineIndex >= -1 && nLineIndex < nLineCount);
	if ((dwFlags & UPDATE_SINGLELINE) != 0)
	{
		ASSERT(nLineIndex != -1);
		//	Repaint the lines
		InvalidateLines(nLineIndex, -1, TRUE);
	}
	else
	{
		if (nLineIndex == -1)
			nLineIndex = 0;		//	Refresh all text
		//	Repaint the lines
		InvalidateLines(nLineIndex, -1, TRUE);
	}

	//	All those points must be recalculated and validated
	if (pContext != NULL)
	{
		pContext->RecalcPoint(m_ptCursorPos);
		pContext->RecalcPoint(m_ptSelStart);
		pContext->RecalcPoint(m_ptSelEnd);
		pContext->RecalcPoint(m_ptAnchor);
		ASSERT_VALIDTEXTPOS(m_ptCursorPos);
		ASSERT_VALIDTEXTPOS(m_ptSelStart);
		ASSERT_VALIDTEXTPOS(m_ptSelEnd);
		ASSERT_VALIDTEXTPOS(m_ptAnchor);
		CPoint ptTopLine(0, m_nTopLine);
		pContext->RecalcPoint(ptTopLine);
		ASSERT_VALIDTEXTPOS(ptTopLine);
		m_nTopLine = ptTopLine.y;
		UpdateCaret();
	}

	//	Recalculate vertical scrollbar, if needed
	if ((dwFlags & UPDATE_VERTRANGE) != 0)
	{
        RecalcVertScrollBar();
	}

	//	Recalculate horizontal scrollbar, if needed
	if ((dwFlags & UPDATE_HORZRANGE) != 0)
	{
		m_nMaxLineLength = -1;
        RecalcHorzScrollBar();
	}
}

HINSTANCE CRorTextView::GetResourceHandle()
{
#ifdef CRYSEDIT_RES_HANDLE
	return CRYSEDIT_RES_HANDLE;
#else
	if (s_hResourceInst != NULL)
		return s_hResourceInst;
	return AfxGetResourceHandle();
#endif
}

int CRorTextView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	ASSERT(m_hAccel == NULL);
	m_hAccel = ::LoadAccelerators(GetResourceHandle(), MAKEINTRESOURCE(IDR_DEFAULT_ACCEL));
	ASSERT(m_hAccel != NULL);
	return 0;
}

BOOL CRorTextView::PreTranslateMessage(MSG *pMsg) 
{
	if (pMsg->message >= WM_KEYFIRST && pMsg->message <= WM_KEYLAST)
	{
		if (m_hAccel != NULL)
		{
			if (::TranslateAccelerator(m_hWnd, m_hAccel, pMsg))
				return TRUE;
		}
	}

	return CView::PreTranslateMessage(pMsg);
}



void CRorTextView::SetFont()
{
	m_nScreenLines = -1;
	m_nScreenChars = -1;
	m_nCharWidth = -1;
	m_nLineHeight = -1;
	if (m_pCacheBitmap != NULL)
	{
		m_pCacheBitmap->DeleteObject();
		delete m_pCacheBitmap;
		m_pCacheBitmap = NULL;
	}
	{
		if (m_apFont != NULL)
		{
			m_apFont->DeleteObject();
			delete m_apFont;
			m_apFont = NULL;
		}
	}
	if (::IsWindow(m_hWnd))
	{
		RecalcVertScrollBar();
		RecalcHorzScrollBar();
		UpdateCaret();
		Invalidate();
	}
}

class CTempDraw
{
public:
    ~CTempDraw();
    CTempDraw(CDC* pdc);

    CDC* m_pdc;
    CDC* m_pcacheDC;
    int m_lineno;
    int m_xpos;
    CRect rcClient;
    int nLineHeight;
    
    CBitmap* pOldBitmap;
};
    
CTempDraw::CTempDraw(CDC* pdc)
{
    m_pdc = pdc;
    m_lineno = 0;
    m_xpos = 0;
}
CTempDraw::~CTempDraw()
{
	m_pcacheDC->SelectObject(pOldBitmap);
	m_pcacheDC->DeleteDC();
}

void CRorTextView::OnDraw(CDC *pdc)
{
#if 1
    this->m_pdraw = new CTempDraw(pdc);   

    CRect rcClient;
    GetClientRect(rcClient);
    int nLineCount = GetLineCount();
	int nLineHeight = GetLineHeight();
    this->m_pdraw->nLineHeight = nLineHeight;
    PrepareSelBounds();

    this->m_pdraw->rcClient = rcClient;

    CDC cacheDC;
    VERIFY(cacheDC.CreateCompatibleDC(pdc));
    if (m_pCacheBitmap == NULL)
    {
        m_pCacheBitmap = new CBitmap;
        VERIFY(m_pCacheBitmap->CreateCompatibleBitmap(pdc, rcClient.Width(), nLineHeight));
    }
    m_pdraw->pOldBitmap = cacheDC.SelectObject(m_pCacheBitmap);

    m_pdraw->m_pcacheDC = &cacheDC;

    //================
    this->LocateTextBuffer()->m_xml.Display(this);  //will call this->ColorOut
    //================

    for (int i=0; i<100; i++)
    {
        this->ColorOut("=\n",2,RGB(255,255,255));
    }

    delete this->m_pdraw;
    this->m_pdraw = NULL;
#else
	CRect rcClient;
	GetClientRect(rcClient);
	int nLineCount = GetLineCount();
	int nLineHeight = GetLineHeight();
	PrepareSelBounds();

	CDC cacheDC;
	VERIFY(cacheDC.CreateCompatibleDC(pdc));
	if (m_pCacheBitmap == NULL)
	{
		m_pCacheBitmap = new CBitmap;
		VERIFY(m_pCacheBitmap->CreateCompatibleBitmap(pdc, rcClient.Width(), nLineHeight));
	}
	CBitmap *pOldBitmap = cacheDC.SelectObject(m_pCacheBitmap);

	CRect rcLine;
	rcLine = rcClient;
	rcLine.bottom = rcLine.top + nLineHeight;

	int nCurrentLine = m_nTopLine;
	while (rcLine.top < rcClient.bottom)
	{
        cacheDC.FillSolidRect(CRect(0, 0, 9999, 99), GetColor(COLORINDEX_WHITESPACE));
		if (nCurrentLine < nLineCount)
		{
            cacheDC.SetBkColor(GetColor(COLORINDEX_BKGND));
            cacheDC.SelectObject(GetFont_1());
            DrawSingleLine(&cacheDC, nCurrentLine);
		}

		VERIFY(pdc->BitBlt(rcLine.left, rcLine.top, rcLine.Width(), rcLine.Height(), &cacheDC, 0, 0, SRCCOPY));

		nCurrentLine ++;
		rcLine.OffsetRect(0, nLineHeight);
	}

	cacheDC.SelectObject(pOldBitmap);
	cacheDC.DeleteDC();
#endif
}


void __stdcall CRorTextView::SetBKColor(COLORREF textcolor)
{
	m_pdraw->m_pcacheDC->SetBkColor(textcolor);
}

void __stdcall CRorTextView::ColorOut(PCSTR str, long len, COLORREF textcolor)
{
    if (!memcmp(str, "if", 2))
    {
        memcmp(str, "if", 2);
    }
	if (textcolor != RGB(255,255,255))
		textcolor = textcolor;

	if (len > 1)
		len = len;
    assert(this->m_pdraw != NULL);

    
    if (m_pdraw->m_xpos == 0)
    {//这是行首,清本行
        m_pdraw->m_pcacheDC->FillSolidRect(CRect(0, 0, 9999, 99), GetColor(COLORINDEX_WHITESPACE));
        m_pdraw->m_pcacheDC->SetBkColor(GetColor(COLORINDEX_BKGND));
        m_pdraw->m_pcacheDC->SelectObject(GetFont_1());
    }
	if (m_pdraw->m_lineno >= GetLineCount())
	{
		int lines = this->m_pdraw->m_lineno - m_nTopLine;
		CRect rcLine = m_pdraw->rcClient;
		rcLine.bottom = rcLine.top + m_pdraw->nLineHeight;
		rcLine.OffsetRect(0, m_pdraw->nLineHeight * lines);
		VERIFY(m_pdraw->m_pdc->BitBlt(
			rcLine.left, rcLine.top, rcLine.Width(), rcLine.Height(), 
			m_pdraw->m_pcacheDC, 0, 0, SRCCOPY));
		this->m_pdraw->m_lineno++;
		return;
	}
    //---------------------------------
    if (len == 0)
        return;
    
    for (int i=0; i<len; i++)
    {
        char c = str[i];
        if (c == '\r' || c == '\n')
        {
            ColorOut(str,i,textcolor);	//递归
            if (this->m_pdraw->m_lineno >= m_nTopLine)
            {
                int lines = this->m_pdraw->m_lineno - m_nTopLine;
                CRect rcLine = m_pdraw->rcClient;
                rcLine.bottom = rcLine.top + m_pdraw->nLineHeight;
                rcLine.OffsetRect(0, m_pdraw->nLineHeight * lines);
                VERIFY(m_pdraw->m_pdc->BitBlt(
                    rcLine.left, rcLine.top, rcLine.Width(), rcLine.Height(), 
                    m_pdraw->m_pcacheDC, 0, 0, SRCCOPY));
            }
            this->m_pdraw->m_lineno++;
			m_pdraw->m_xpos = 0;
            if (c == '\r' && str[i+1] == '\n')
                i++;
            i++;
            ColorOut(str+i,len-i,textcolor);
            return;
        }
    }
    //以上是处理换行问题
    //显示
	bool f = false;
	{
		//处理 select 的问题
		for (int i=0; i<len; i++)
		{
			CPoint pos(m_pdraw->m_xpos+i,m_pdraw->m_lineno);
			if (IsInsideSelBlock(pos))
			{
				if (i != 0)
				{
					ColorOut(str,i,textcolor);
					ColorOut(str+i,len-i,textcolor);
					return;
				}
				f=true;
			}
			else
			{
				if (f)
				{
					ColorOut(str,i,textcolor);
					ColorOut(str+i,len-i,textcolor);
					return;
				}
			}
		}
		if (f)
		{
			m_pdraw->m_pcacheDC->SetBkColor(RGB(33,33,73));
		}
	}
    m_pdraw->m_pcacheDC->SetTextColor(textcolor);
    VERIFY(m_pdraw->m_pcacheDC->ExtTextOut(
        this->m_pdraw->m_xpos * GetCharWidth(), 
        0,  //ptOrigin.y * GetLineHeight(), 
        ETO_CLIPPED, NULL, str, 
        len,
        NULL));

	if (f)
	{
		m_pdraw->m_pcacheDC->SetBkColor(RGB(0,0,0));
	}
    this->m_pdraw->m_xpos += len;
}




