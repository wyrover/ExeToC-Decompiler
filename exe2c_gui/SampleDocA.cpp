// SampleDocA.cpp : implementation file
//

#include "stdafx.h"
#include "sample.h"
#include "SampleDocA.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSampleDocA

IMPLEMENT_DYNCREATE(CSampleDocA, CDocument)

CSampleDocA::CSampleDocA()
{
}

BOOL CSampleDocA::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	SetTitle("String");
	return TRUE;
}

CSampleDocA::~CSampleDocA()
{
}


BEGIN_MESSAGE_MAP(CSampleDocA, CDocument)
	//{{AFX_MSG_MAP(CSampleDocA)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSampleDocA diagnostics

#ifdef _DEBUG
void CSampleDocA::AssertValid() const
{
	CDocument::AssertValid();
}

void CSampleDocA::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSampleDocA serialization

void CSampleDocA::Serialize(CArchive& ar)
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
// CSampleDocA commands
