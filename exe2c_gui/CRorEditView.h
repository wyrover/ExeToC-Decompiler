
#if !defined(AFX_CRorEDITVIEW__H)
#define AFX_CRorEDITVIEW__H

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "CRorTextView.h"


/////////////////////////////////////////////////////////////////////////////
//	CRorEditView view

class CRorEditView : public CRorTextView
{
	DECLARE_DYNCREATE(CRorEditView)

// Attributes
public:
    virtual void ResetView();


// Operations
public:
	void DeleteAll();
	CRorEditView();
	~CRorEditView();

    virtual BOOL QueryEditable();
	virtual void UpdateView();  //CRorTextView *pSource, CUpdateContext *pContext, DWORD dwFlags, int nLineIndex = -1);

// Implementation
protected:

	// Generated message map functions
protected:
	//{{AFX_MSG(CRorEditView)
    afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
    afx_msg int  OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////


//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CRorEDITVIEW__H)
