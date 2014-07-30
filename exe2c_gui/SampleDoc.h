// SampleDoc.h : interface of the CSampleDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SAMPLEDOC__H)
#define AFX_SAMPLEDOC__H

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "CRorTextBuffer.h"
#include"viewfundlg.h"
class CSampleDoc : public CDocument
{
protected: // create from serialization only
	CSampleDoc();
	DECLARE_DYNCREATE(CSampleDoc)

// Attributes
public:
	class CSampleTextBuffer : public CRorTextBuffer
	{
	private:
		CSampleDoc *m_pOwnerDoc;
	public:
		CSampleTextBuffer(CSampleDoc *pDoc) { m_pOwnerDoc = pDoc; };
		virtual void SetModified(BOOL bModified = TRUE)
			{ m_pOwnerDoc->SetModifiedFlag(bModified); };
	};

	CSampleTextBuffer m_xTextBuffer;
	CViewFunDlg     dlg;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSampleDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual void DeleteContents();
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	virtual void OnCloseDocument();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSampleDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CSampleDoc)
	//afx_msg void OnReadOnly();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SAMPLEDOC__H)
