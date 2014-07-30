
#include "stdafx.h"
#include "editcmd.h"
#include "CRorEditView.h"
#include "CRorTextBuffer.h"


#ifndef __AFXPRIV_H__
#pragma message("Include <afxpriv.h> in your stdafx.h to avoid this message")
#include <afxpriv.h>
#endif
#ifndef __AFXOLE_H__
#pragma message("Include <afxole.h> in your stdafx.h to avoid this message")
#include <afxole.h>
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define DRAG_BORDER_X		5
#define DRAG_BORDER_Y		5


/////////////////////////////////////////////////////////////////////////////
// CRorEditView

IMPLEMENT_DYNCREATE(CRorEditView, CRorTextView)

CRorEditView::CRorEditView()
{
	AFX_ZERO_INIT_OBJECT(CRorTextView);
}

CRorEditView::~CRorEditView()
{
}


BEGIN_MESSAGE_MAP(CRorEditView, CRorTextView)
	//{{AFX_MSG_MAP(CRorEditView)
    ON_WM_CHAR()
    ON_WM_CREATE()
	ON_WM_DESTROY()
    ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
    
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CRorEditView message handlers

void CRorEditView::ResetView()
{
	CRorTextView::ResetView();
}

BOOL CRorEditView::QueryEditable()
{
    return FALSE;
}

void CRorEditView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	CRorTextView::OnChar(nChar, nRepCnt, nFlags);

    if (nChar == 'i' || nChar == 'I')
    {
        static bool f = false;
        f=!f;
        if (f)
        {
            this->ResetView();
            this->DeleteAll();
            this->LocateTextBuffer()->m_xml.Clear();

            g_EXE2C->prtout_itn(&this->m_pTextBuffer->m_xml);
            this->Invalidate();
        }
        else
        {
            this->ResetView();
            this->DeleteAll();
            this->LocateTextBuffer()->m_xml.Clear();

            g_EXE2C->prtout_cpp(&this->m_pTextBuffer->m_xml);
            this->Invalidate();
        }
        return;
    }


	if ((::GetAsyncKeyState(VK_LBUTTON) & 0x8000) != 0 ||
			(::GetAsyncKeyState(VK_RBUTTON) & 0x8000) != 0)
		return;

	BOOL bTranslated = FALSE;
	if (nChar == VK_RETURN)
	{
		return;
	}

	if (nChar > 31)
	{
	}
}


int CRorEditView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CRorTextView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	return 0;
}

void CRorEditView::OnDestroy() 
{
	CRorTextView::OnDestroy();
}

/*void CRorEditView::OnDropSource(DROPEFFECT de)
{
	if (! IsDraggingText())
		return;

	ASSERT_VALIDTEXTPOS(m_ptDraggedTextBegin);
	ASSERT_VALIDTEXTPOS(m_ptDraggedTextEnd);

	if (de == DROPEFFECT_MOVE)
	{
		m_pTextBuffer->DeleteText(this, m_ptDraggedTextBegin.y, m_ptDraggedTextBegin.x, m_ptDraggedTextEnd.y, 
			m_ptDraggedTextEnd.x, CE_ACTION_DRAGDROP); // [JRT]
	}
} */

void CRorEditView::UpdateView()
{
    //CRorTextView *pSource, CUpdateContext *pContext, DWORD dwFlags, int nLineIndex /*= -1*/
    CRorTextView *pSource = NULL;
    CUpdateContext *pContext = NULL;
    DWORD dwFlags = UPDATE_RESET;
    int nLineIndex = -1;    /*= -1*/
	CRorTextView::UpdateView(); //pSource, pContext, dwFlags, nLineIndex);

}

void CRorEditView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
//	LPCTSTR pszLineChars = GetLineChars(point.y);
	CRorTextView::OnLButtonDown(nFlags, point);
}

void CRorEditView::DeleteAll()
{
    //add by bookaa

	if (m_pTextBuffer)
	{
	m_pTextBuffer->FreeAll();
	m_pTextBuffer->InitNew();
	}
}
