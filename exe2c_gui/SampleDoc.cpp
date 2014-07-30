// SampleDoc.cpp : implementation of the CSampleDoc class
//

#include "stdafx.h"
#include "exe2c_gui.h"
#include "mainfrm.h"
#include "SampleDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSampleDoc

IMPLEMENT_DYNCREATE(CSampleDoc, CDocument)

BEGIN_MESSAGE_MAP(CSampleDoc, CDocument)
	//{{AFX_MSG_MAP(CSampleDoc)
	//ON_COMMAND(ID_READ_ONLY, OnReadOnly)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSampleDoc construction/destruction

#pragma warning(disable:4355)

CSampleDoc::CSampleDoc() : m_xTextBuffer(this)
{
    // TODO: add one-time construction code here
}

CSampleDoc::~CSampleDoc()
{
}

BOOL CSampleDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	m_xTextBuffer.InitNew();
	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CSampleDoc serialization

void CSampleDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CSampleDoc diagnostics

#ifdef _DEBUG
void CSampleDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSampleDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSampleDoc commands

void CSampleDoc::DeleteContents() 
{
	CDocument::DeleteContents();

	m_xTextBuffer.FreeAll();
}
CMainFrame *g_Mfm = NULL;
void MyRefreshView();
BOOL CSampleDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;
    g_EXE2C->exe2c_main(lpszPathName);
	BOOL m_bSucc = m_xTextBuffer.LoadFromFile(lpszPathName);
	g_Mfm->ShowFun();

    MyRefreshView();
	return m_bSucc;
}

BOOL CSampleDoc::OnSaveDocument(LPCTSTR lpszPathName) 
{
	m_xTextBuffer.SaveToFile(lpszPathName);
	return TRUE;	//	Note - we didn't call inherited member!
}

void CSampleDoc::OnCloseDocument() 
{
	// TODO: Add your specialized code here and/or call the base class
	g_Mfm->ClearFun();
	CDocument::OnCloseDocument();
}
