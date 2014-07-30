
#if !defined(AFX_CRorTEXTBUFFER__H)
#define AFX_CRorTEXTBUFFER__H

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "CRorTextView.h"

#include "..\exe2c\exe2c.H"
#include "..\exe2c\src\CXmlPrt.h"

#ifndef __AFXTEMPL_H__
#pragma message("Include <afxtempl.h> in your stdafx.h to avoid this message")
#include <afxtempl.h>
#endif

#define UNDO_DESCRIP_BUF        32

enum LINEFLAGS
{
	LF_BOOKMARK_FIRST			= 0x00000001L,
	LF_EXECUTION				= 0x00010000L,
	LF_BREAKPOINT				= 0x00020000L,
	LF_COMPILATION_ERROR		= 0x00040000L,
	LF_BOOKMARKS	        	= 0x00080000L,
	LF_INVALID_BREAKPOINT       = 0x00100000L
};

#define LF_BOOKMARK(id)		(LF_BOOKMARK_FIRST << id)

enum CRLFSTYLE
{
	CRLF_STYLE_AUTOMATIC	= -1,
	CRLF_STYLE_DOS			= 0,
	CRLF_STYLE_UNIX			= 1,
	CRLF_STYLE_MAC			= 2
};

enum
{
	CE_ACTION_UNKNOWN		= 0,
	CE_ACTION_PASTE			= 1,
	CE_ACTION_DELSEL		= 2,
	CE_ACTION_CUT			= 3,
	CE_ACTION_TYPING		= 4,
	CE_ACTION_BACKSPACE		= 5,
	CE_ACTION_INDENT		= 6,
	CE_ACTION_DRAGDROP		= 7,
	CE_ACTION_REPLACE		= 8,
	CE_ACTION_DELETE		= 9,
	CE_ACTION_AUTOINDENT	= 10
	//	...
	//	Expandable: user actions allowed
};


/////////////////////////////////////////////////////////////////////////////
// CUpdateContext class

class CUpdateContext
{
public:
	virtual void RecalcPoint(CPoint &ptPoint) = 0;
};


/////////////////////////////////////////////////////////////////////////////
// CRorTextBuffer command target



class CRorTextBuffer : public CCmdTarget
{
	DECLARE_DYNCREATE(CRorTextBuffer)

protected:
	//	Nested class declarations
	struct SLineInfo
	{
		TCHAR	*m_pcLine;
		int		m_nLength, m_nMax;

        void* m_hline;
        st_LINE_SYNTAX lineSyntax[240];

		SLineInfo() { ZeroMemory(this, sizeof(SLineInfo)); };
	};


	//	Lines of text
	CArray <SLineInfo, SLineInfo&> m_aLines;


	//	Connected views
	CList <CRorTextView *, CRorTextView *> m_lpViews;
public:
    CXmlPrt m_xml;

    void Parse(int nLineIndex, TEXTBLOCK *pBuf, int &nActualItems);

    bool OnChar(int x, int y, UINT nChar);
    bool SetCurWord(int x, int y);
	//	Construction/destruction code
	CRorTextBuffer();
	~CRorTextBuffer();

	//	Basic functions
	BOOL InitNew();
	BOOL LoadFromFile(LPCTSTR pszFileName);
	BOOL SaveToFile(LPCTSTR pszFileName);
	void FreeAll();

	//	Connect/disconnect views
	void AddView(CRorTextView *pView);
	void RemoveView(CRorTextView *pView);

	//	Text access functions
	int GetLineCount();
	int GetLineLength(int nLine);
	LPTSTR GetLineChars(int nLine);
	CString GetText(int nStartLine, int nStartChar, int nEndLine, int nEndChar);

    //	Notify all connected views about changes in text
	void UpdateViews();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRorTextBuffer)
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CRorTextBuffer)
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CRorTEXTBUFFER__H)
