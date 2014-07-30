
#include "stdafx.h"
#include "editcmd.h"
#include "CRorTextView.h"
#include "CRorTextBuffer.h"
#include <malloc.h>

#ifndef __AFXPRIV_H__
#pragma message("Include <afxpriv.h> in your stdafx.h to avoid this message")
#include <afxpriv.h>
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define	Ror_TIMER_DRAGSEL	1001


/////////////////////////////////////////////////////////////////////////////
// CRorTextView

void CRorTextView::MoveLeft(BOOL bSelect)
{
	PrepareSelBounds();
	if (m_ptDrawSelStart != m_ptDrawSelEnd && ! bSelect)
	{
		m_ptCursorPos = m_ptDrawSelStart;
	}
	else
	{
		if (m_ptCursorPos.x == 0)
		{
			if (m_ptCursorPos.y > 0)
			{
				m_ptCursorPos.y --;
				m_ptCursorPos.x = GetLineLength(m_ptCursorPos.y);
			}
		}
		else
			m_ptCursorPos.x --;
	}
	
	EnsureVisible(m_ptCursorPos);
	UpdateCaret();
	if (! bSelect)
		m_ptAnchor = m_ptCursorPos;
	SetSelection(m_ptAnchor, m_ptCursorPos);

    if (this->m_pTextBuffer->SetCurWord(this->m_ptCursorPos.x, this->m_ptCursorPos.y))
    {
        Invalidate();
    }
}

void CRorTextView::MoveRight(BOOL bSelect)
{
	PrepareSelBounds();
	if (m_ptDrawSelStart != m_ptDrawSelEnd && ! bSelect)
	{
		m_ptCursorPos = m_ptDrawSelEnd;
	}
	else
	{
		if (m_ptCursorPos.x == GetLineLength(m_ptCursorPos.y))
		{
			if (m_ptCursorPos.y < GetLineCount() - 1)
			{
				m_ptCursorPos.y ++;
				m_ptCursorPos.x = 0;
			}
		}
		else
			m_ptCursorPos.x ++;
	}
	
	EnsureVisible(m_ptCursorPos);
	UpdateCaret();
	if (! bSelect)
		m_ptAnchor = m_ptCursorPos;
	SetSelection(m_ptAnchor, m_ptCursorPos);

    if (this->m_pTextBuffer->SetCurWord(this->m_ptCursorPos.x, this->m_ptCursorPos.y))
    {
        Invalidate();
    }
}

void CRorTextView::MoveWordLeft(BOOL bSelect)
{
	PrepareSelBounds();
	if (m_ptDrawSelStart != m_ptDrawSelEnd && ! bSelect)
	{
		MoveLeft(bSelect);
		return;
	}

	if (m_ptCursorPos.x == 0)
	{
		if (m_ptCursorPos.y == 0)
			return;
		m_ptCursorPos.y --;
		m_ptCursorPos.x = GetLineLength(m_ptCursorPos.y);
	}

	m_ptCursorPos.x = this->LocateTextBuffer()->m_xml.MoveLeftWord(m_ptCursorPos.x, m_ptCursorPos.y);
	EnsureVisible(m_ptCursorPos);
	UpdateCaret();
	if (! bSelect)
		m_ptAnchor = m_ptCursorPos;
	SetSelection(m_ptAnchor, m_ptCursorPos);
}

void CRorTextView::MoveWordRight(BOOL bSelect)
{
	PrepareSelBounds();
	if (m_ptDrawSelStart != m_ptDrawSelEnd && ! bSelect)
	{
		MoveRight(bSelect);
		return;
	}

	if (m_ptCursorPos.x == GetLineLength(m_ptCursorPos.y))
	{
		if (m_ptCursorPos.y == GetLineCount() - 1)
			return;
		m_ptCursorPos.y ++;
		m_ptCursorPos.x = 0;
	}

	int nLength = GetLineLength(m_ptCursorPos.y);
	if (m_ptCursorPos.x == nLength)
	{
		MoveRight(bSelect);
		return;
	}

	m_ptCursorPos.x = this->LocateTextBuffer()->m_xml.MoveRightWord(m_ptCursorPos.x, m_ptCursorPos.y);
	
	EnsureVisible(m_ptCursorPos);
	UpdateCaret();
	if (! bSelect)
		m_ptAnchor = m_ptCursorPos;
	SetSelection(m_ptAnchor, m_ptCursorPos);
}

void CRorTextView::MoveUp(BOOL bSelect)
{
	PrepareSelBounds();
	if (m_ptDrawSelStart != m_ptDrawSelEnd && ! bSelect)
		m_ptCursorPos = m_ptDrawSelStart;

	if (m_ptCursorPos.y > 0)
	{
		m_ptCursorPos.y --;
		m_ptCursorPos.x = ApproxActualOffset(m_ptCursorPos.y, m_ptCursorPos.x);
		if (m_ptCursorPos.x > GetLineLength(m_ptCursorPos.y))
			m_ptCursorPos.x = GetLineLength(m_ptCursorPos.y);
	}
	EnsureVisible(m_ptCursorPos);
	UpdateCaret();
	if (! bSelect)
		m_ptAnchor = m_ptCursorPos;
	SetSelection(m_ptAnchor, m_ptCursorPos);
}

void CRorTextView::MoveDown(BOOL bSelect)
{
	PrepareSelBounds();
	if (m_ptDrawSelStart != m_ptDrawSelEnd && ! bSelect)
		m_ptCursorPos = m_ptDrawSelEnd;

	if (m_ptCursorPos.y < GetLineCount() - 1)
	{
		m_ptCursorPos.y ++;
		m_ptCursorPos.x = ApproxActualOffset(m_ptCursorPos.y, m_ptCursorPos.x);
		if (m_ptCursorPos.x > GetLineLength(m_ptCursorPos.y))
			m_ptCursorPos.x = GetLineLength(m_ptCursorPos.y);
	}
	EnsureVisible(m_ptCursorPos);
	UpdateCaret();
	if (! bSelect)
		m_ptAnchor = m_ptCursorPos;
	SetSelection(m_ptAnchor, m_ptCursorPos);


    //InvalidateLines(m_ptCursorPos.y, -1, TRUE);
    //UpdateView();
}

void CRorTextView::MoveHome(BOOL bSelect)
{	
	m_ptCursorPos.x = this->LocateTextBuffer()->m_xml.MoveHome(m_ptCursorPos.y);

	EnsureVisible(m_ptCursorPos);
	UpdateCaret();
	if (! bSelect)
		m_ptAnchor = m_ptCursorPos;
	SetSelection(m_ptAnchor, m_ptCursorPos);
}

void CRorTextView::MoveEnd(BOOL bSelect)
{
	m_ptCursorPos.x = GetLineLength(m_ptCursorPos.y);
	
	EnsureVisible(m_ptCursorPos);
	UpdateCaret();
	if (! bSelect)
		m_ptAnchor = m_ptCursorPos;
	SetSelection(m_ptAnchor, m_ptCursorPos);
}

void CRorTextView::MovePgUp(BOOL bSelect)
{
	int nNewTopLine = m_nTopLine - GetScreenLines() + 1;
	if (nNewTopLine < 0)
		nNewTopLine = 0;
	if (m_nTopLine != nNewTopLine)
	{
		ScrollToLine(nNewTopLine);
		UpdateSiblingScrollPos(TRUE);
	}

	m_ptCursorPos.y -= GetScreenLines() - 1;
	if (m_ptCursorPos.y < 0)
		m_ptCursorPos.y = 0;
	if (m_ptCursorPos.x > GetLineLength(m_ptCursorPos.y))
		m_ptCursorPos.x = GetLineLength(m_ptCursorPos.y);
	
	EnsureVisible(m_ptCursorPos);	//todo: no vertical scroll
	UpdateCaret();
	if (! bSelect)
		m_ptAnchor = m_ptCursorPos;
	SetSelection(m_ptAnchor, m_ptCursorPos);
}

void CRorTextView::MovePgDn(BOOL bSelect)
{
	int nNewTopLine = m_nTopLine + GetScreenLines() - 1;
	if (nNewTopLine >= GetLineCount())
		nNewTopLine = GetLineCount() - 1;
	if (m_nTopLine != nNewTopLine)
	{
		ScrollToLine(nNewTopLine);
		UpdateSiblingScrollPos(TRUE);
	}

	m_ptCursorPos.y += GetScreenLines() - 1;
	if (m_ptCursorPos.y >= GetLineCount())
		m_ptCursorPos.y = GetLineCount() - 1;
	if (m_ptCursorPos.x > GetLineLength(m_ptCursorPos.y))
		m_ptCursorPos.x = GetLineLength(m_ptCursorPos.y);
	
	EnsureVisible(m_ptCursorPos);	//todo: no vertical scroll
	UpdateCaret();
	if (! bSelect)
		m_ptAnchor = m_ptCursorPos;
	SetSelection(m_ptAnchor, m_ptCursorPos);
}

void CRorTextView::MoveCtrlHome(BOOL bSelect)
{
	m_ptCursorPos.x = 0;
	m_ptCursorPos.y = 0;
	
	EnsureVisible(m_ptCursorPos);
	UpdateCaret();
	if (! bSelect)
		m_ptAnchor = m_ptCursorPos;
	SetSelection(m_ptAnchor, m_ptCursorPos);
}

void CRorTextView::MoveCtrlEnd(BOOL bSelect)
{
	m_ptCursorPos.y = GetLineCount() - 1;
	m_ptCursorPos.x = GetLineLength(m_ptCursorPos.y);
	
	EnsureVisible(m_ptCursorPos);
	UpdateCaret();
	if (! bSelect)
		m_ptAnchor = m_ptCursorPos;
	SetSelection(m_ptAnchor, m_ptCursorPos);
}

void CRorTextView::ScrollUp()
{
	if (m_nTopLine > 0)
	{
		ScrollToLine(m_nTopLine - 1);
		UpdateSiblingScrollPos(TRUE);
	}
}

void CRorTextView::ScrollDown()
{
	if (m_nTopLine < GetLineCount() - 1)
	{
		ScrollToLine(m_nTopLine + 1);
		UpdateSiblingScrollPos(TRUE);
	}
}

void CRorTextView::ScrollLeft()
{
	if (m_nOffsetChar > 0)
	{
		ScrollToChar(m_nOffsetChar - 1);
		UpdateCaret();
	}
}

void CRorTextView::ScrollRight()
{
	if (m_nOffsetChar < GetMaxLineLength() - 1)
	{
		ScrollToChar(m_nOffsetChar + 1);
		UpdateCaret();
	}
}

CPoint CRorTextView::WordToRight(CPoint pt)
{
	ASSERT_VALIDTEXTPOS(pt);
	pt.x = this->LocateTextBuffer()->m_xml.WordToRight(pt.x, pt.y);
	/*
	int nLength = GetLineLength(pt.y);
	LPCTSTR pszChars = GetLineChars(pt.y);
	while (pt.x < nLength)
	{
		if (! isalnum(pszChars[pt.x]) && pszChars[pt.x] != _T('_'))
			break;
		pt.x ++;
	}*/
	ASSERT_VALIDTEXTPOS(pt);
	return pt;
}

CPoint CRorTextView::WordToLeft(CPoint pt)
{
	ASSERT_VALIDTEXTPOS(pt);
	pt.x = this->LocateTextBuffer()->m_xml.WordToLeft(pt.x, pt.y);
	/*
	LPCTSTR pszChars = GetLineChars(pt.y);
	while (pt.x > 0)
	{
		if (! isalnum(pszChars[pt.x - 1]) && pszChars[pt.x - 1] != _T('_'))
			break;
		pt.x --;
	}*/
	ASSERT_VALIDTEXTPOS(pt);
	return pt;
}

void CRorTextView::SelectAll()
{
	int nLineCount = GetLineCount();
	m_ptCursorPos.x = GetLineLength(nLineCount - 1);
	m_ptCursorPos.y = nLineCount - 1;
	SetSelection(CPoint(0, 0), m_ptCursorPos);
	UpdateCaret();
}

void CRorTextView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CView::OnLButtonDown(nFlags, point);

	BOOL bShift = GetKeyState(VK_SHIFT) & 0x8000;
	BOOL bControl = GetKeyState(VK_CONTROL) & 0x8000;

	if (point.x < 0)
	{
		AdjustTextPoint(point);
		if (bControl)
		{
			SelectAll();
		}
		else
		{
			m_ptCursorPos = ClientToText(point);
			m_ptCursorPos.x = 0;				//	Force beginning of the line
			if (! bShift)
				m_ptAnchor = m_ptCursorPos;

			CPoint ptStart, ptEnd;
			ptStart = m_ptAnchor;
			if (ptStart.y == GetLineCount() - 1)
				ptStart.x = GetLineLength(ptStart.y);
			else
			{
				ptStart.y ++;
				ptStart.x = 0;
			}

			ptEnd = m_ptCursorPos;
			ptEnd.x = 0;

			m_ptCursorPos = ptEnd;
			UpdateCaret();
			EnsureVisible(m_ptCursorPos);
			SetSelection(ptStart, ptEnd);

			SetCapture();
			SetTimer(Ror_TIMER_DRAGSEL, 100, NULL);
		}
	}
	else
	{
		CPoint ptText = ClientToText(point);
		PrepareSelBounds();
		{
			AdjustTextPoint(point);
			m_ptCursorPos = ClientToText(point);
			if (! bShift)
				m_ptAnchor = m_ptCursorPos;

			CPoint ptStart, ptEnd;
			if (bControl)
			{
				if (m_ptCursorPos.y < m_ptAnchor.y ||
					m_ptCursorPos.y == m_ptAnchor.y && m_ptCursorPos.x < m_ptAnchor.x)
				{
					ptStart = WordToLeft(m_ptCursorPos);
					ptEnd = WordToRight(m_ptAnchor);
				}
				else
				{
					ptStart = WordToLeft(m_ptAnchor);
					ptEnd = WordToRight(m_ptCursorPos);
				}
			}
			else
			{
				ptStart = m_ptAnchor;
				ptEnd = m_ptCursorPos;
			}

			m_ptCursorPos = ptEnd;
			UpdateCaret();
			EnsureVisible(m_ptCursorPos);
			SetSelection(ptStart, ptEnd);
			
//			CString m_sText;
//			GetText(ptStart,ptEnd,m_sText);
			SetCapture();
			SetTimer(Ror_TIMER_DRAGSEL, 100, NULL);
		}
	}


	ASSERT_VALIDTEXTPOS(m_ptCursorPos);
}

void CRorTextView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	CView::OnLButtonUp(nFlags, point);

    ReleaseCapture();

	ASSERT_VALIDTEXTPOS(m_ptCursorPos);
}

void CRorTextView::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	CView::OnLButtonDblClk(nFlags, point);

	if (1)//! m_bDragSelection)
	{
		AdjustTextPoint(point);

		m_ptCursorPos = ClientToText(point);
		m_ptAnchor = m_ptCursorPos;

		CPoint ptStart, ptEnd;
		if (m_ptCursorPos.y < m_ptAnchor.y ||
			m_ptCursorPos.y == m_ptAnchor.y && m_ptCursorPos.x < m_ptAnchor.x)
		{
			ptStart = WordToLeft(m_ptCursorPos);
			ptEnd = WordToRight(m_ptAnchor);
		}
		else
		{
			ptStart = WordToLeft(m_ptAnchor);
			ptEnd = WordToRight(m_ptCursorPos);
		}

		m_ptCursorPos = ptEnd;
		UpdateCaret();
		EnsureVisible(m_ptCursorPos);
		SetSelection(ptStart, ptEnd);

		SetCapture();
		SetTimer(Ror_TIMER_DRAGSEL, 100, NULL);
	}
}

void CRorTextView::OnEditCopy() 
{
	Copy();
}

void CRorTextView::OnEditSelectAll() 
{
	SelectAll();
}

void CRorTextView::OnRButtonDown(UINT nFlags, CPoint point) 
{
	CPoint pt = point;
	AdjustTextPoint(pt);
	pt = ClientToText(pt);
	if (! IsInsideSelBlock(pt))
	{
		m_ptAnchor = m_ptCursorPos = pt;
		SetSelection(m_ptCursorPos, m_ptCursorPos);
		EnsureVisible(m_ptCursorPos);
		UpdateCaret();
	}

	CView::OnRButtonDown(nFlags, point);
}

BOOL CRorTextView::IsSelection()
{
	return m_ptSelStart != m_ptSelEnd;
}

void CRorTextView::Copy()
{
	if (m_ptSelStart == m_ptSelEnd)
		return;

	PrepareSelBounds();
	CString text = GetText(m_ptDrawSelStart, m_ptDrawSelEnd);
	PutToClipboard(text);
}


BOOL CRorTextView::PutToClipboard(LPCTSTR pszText)
{
	if (pszText == NULL || lstrlen(pszText) == 0)
		return FALSE;

	CWaitCursor wc;
	BOOL bOK = FALSE;
	if (OpenClipboard())
	{
		EmptyClipboard();
		HGLOBAL hData = GlobalAlloc(GMEM_MOVEABLE | GMEM_DDESHARE, lstrlen(pszText) + 1);
		if (hData != NULL)
		{
			LPSTR pszData = (LPSTR) ::GlobalLock(hData);
			USES_CONVERSION;
			strcpy(pszData, T2A((LPTSTR) pszText));
			GlobalUnlock(hData);
			bOK = SetClipboardData(CF_TEXT, hData) != NULL;
		}
		CloseClipboard();
	}
	return bOK;
}


