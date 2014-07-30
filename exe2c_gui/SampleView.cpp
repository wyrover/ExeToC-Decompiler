// SampleView.cpp : implementation of the CSampleView class
//

#include "stdafx.h"
#include "exe2c_gui.h"

#include "SampleDoc.h"
#include "SampleView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSampleView

IMPLEMENT_DYNCREATE(CSampleView, CRorEditView)

BEGIN_MESSAGE_MAP(CSampleView, CRorEditView)
	//{{AFX_MSG_MAP(CSampleView)
	ON_WM_CONTEXTMENU()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CRorEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CRorEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CRorEditView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSampleView construction/destruction
extern CSampleView *g_VIEW;
CSampleView::CSampleView()
{
	g_VIEW = this;
}

CSampleView::~CSampleView()
{
}

BOOL CSampleView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CRorEditView::PreCreateWindow(cs);
}


/////////////////////////////////////////////////////////////////////////////
// CSampleView diagnostics

#ifdef _DEBUG
void CSampleView::AssertValid() const
{
	CRorEditView::AssertValid();
}

void CSampleView::Dump(CDumpContext& dc) const
{
	CRorEditView::Dump(dc);
}

CSampleDoc* CSampleView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSampleDoc)));
	return (CSampleDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSampleView message handlers
//CString g_string = "hello world\ngood day\n122222";
CRorTextBuffer *CSampleView::LocateTextBuffer()
{
//	GetDocument()->m_xTextBuffer.InsertLine(g_string);
	return &GetDocument()->m_xTextBuffer;
}

void CSampleView::OnInitialUpdate() 
{
	CRorEditView::OnInitialUpdate();
	
    SetFont();
}

void CSampleView::OnContextMenu(CWnd* pWnd, CPoint point) 
{
	AfxMessageBox("Build your own context menu!");
}
