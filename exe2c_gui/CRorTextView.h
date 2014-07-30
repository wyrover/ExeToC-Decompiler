#if !defined(AFX_CRorTEXTVIEW__H)
#define AFX_CRorTEXTVIEW__H

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "../exe2c/src/cxmllist.h"

////////////////////////////////////////////////////////////////////////////
// Forward class declarations

class CRorTextBuffer;
class CUpdateContext;


////////////////////////////////////////////////////////////////////////////
// CRorTextView class declaration


//	CRorTextView::UpdateView() flags
enum
{
	UPDATE_HORZRANGE	= 0x0001,		//	update horz scrollbar
	UPDATE_VERTRANGE	= 0x0002,		//	update vert scrollbar
	UPDATE_SINGLELINE	= 0x0100,		//	single line has changed
	UPDATE_FLAGSONLY	= 0x0200,		//	only line-flags were changed

	UPDATE_RESET		= 0x1000		//	document was reloaded, update all!
};

//	Syntax coloring overrides
struct TEXTBLOCK
{
    int	m_nCharPos;
    int m_nColorIndex;  //COLORINDEX_COMMENT µ»
    void* handle;
};


class CRorTextView : public CScrollView, public I_COLOROUT
{
	DECLARE_DYNCREATE(CRorTextView)

private:
	//	Painting caching bitmap
	CBitmap *m_pCacheBitmap;

	//	Line/character dimensions
	int m_nLineHeight, m_nCharWidth;
	void CalcLineCharDim();

	//	Amount of lines/characters that completely fits the client area
	int m_nScreenLines, m_nScreenChars;

	int m_nMaxLineLength;	

	BOOL m_bFocused;
	CPoint m_ptAnchor;
	CFont *m_apFont;

	//	Parsing stuff
    int m_nParseArraySize;
	void GetParseCookie(int nLineIndex);

	CPoint WordToRight(CPoint pt);
	CPoint WordToLeft(CPoint pt);

	CPoint m_ptDrawSelStart, m_ptDrawSelEnd;
	CPoint m_ptCursorPos;
	CPoint m_ptSelStart, m_ptSelEnd;
	void PrepareSelBounds();

	int ApproxActualOffset(int nLineIndex, int nOffset);
	void AdjustTextPoint(CPoint &point);
	void DrawLineHelperImpl(CDC *pdc, CPoint &ptOrigin, 
							LPCTSTR pszChars, int nCount);
	void DrawLineHelperImpl_1(CDC *pdc, CPoint &ptOrigin, 
							LPCTSTR pszChars, int nCount);
	BOOL IsInsideSelBlock(CPoint ptTextPos);


protected:
	CImageList *m_pIcons;
	CRorTextBuffer *m_pTextBuffer;
	HACCEL m_hAccel;
	virtual void ResetView();
	void UpdateCaret();

	CPoint ClientToText(const CPoint &point);
	CPoint TextToClient(const CPoint &point);
	void InvalidateLines(int nLine1, int nLine2, BOOL bInvalidateMargin = FALSE);
    
    
	//	Keyboard handlers
	void MoveLeft(BOOL bSelect);
	void MoveRight(BOOL bSelect);
	void MoveWordLeft(BOOL bSelect);
	void MoveWordRight(BOOL bSelect);
	void MoveUp(BOOL bSelect);
	void MoveDown(BOOL bSelect);
	void MoveHome(BOOL bSelect);
	void MoveEnd(BOOL bSelect);
	void MovePgUp(BOOL bSelect);
	void MovePgDn(BOOL bSelect);
	void MoveCtrlHome(BOOL bSelect);
	void MoveCtrlEnd(BOOL bSelect);

	void SelectAll();
	void Copy();

	BOOL IsSelection();
	BOOL IsInsideSelection(const CPoint &ptTextPos);
	void GetSelection(CPoint &ptStart, CPoint &ptEnd);
	void SetSelection(const CPoint &ptStart, const CPoint &ptEnd);

	int m_nTopLine, m_nOffsetChar;
	

    void PointTrans_ImageToChar(IN CPoint& pt1, OUT CPoint& pt2);
    void PointTrans_CharToImage(IN CPoint& pt1, OUT CPoint& pt2);
	int GetLineHeight();
	int GetCharWidth();
	int GetMaxLineLength();
	int GetScreenLines();
	int GetScreenChars();
	CFont *GetFont_1();

	void RecalcVertScrollBar(BOOL bPositionOnly = FALSE);
	void RecalcHorzScrollBar(BOOL bPositionOnly = FALSE);

	//	Scrolling helpers
	void ScrollToChar(int nNewOffsetChar);
	void ScrollToLine(int nNewTopLine, BOOL bNoSmoothScroll = FALSE, BOOL bTrackScrollBar = TRUE);

	//	Splitter support
	virtual void UpdateSiblingScrollPos(BOOL bHorz);
	virtual void OnUpdateSibling(CRorTextView *pUpdateSource, BOOL bHorz);
	CRorTextView *GetSiblingView(int nRow, int nCol);

	virtual int GetLineCount();
	virtual int GetLineLength(int nLineIndex);
	virtual LPCTSTR GetLineChars(int nLineIndex);
	CString GetText(const CPoint &ptStart, const CPoint &ptEnd);

	//	Clipboard overridable
    virtual BOOL PutToClipboard(LPCTSTR pszText);
    

	virtual COLORREF GetColor(int nColorIndex);
    
	void DrawLineHelper(CDC *pdc, CPoint &ptOrigin, 
						LPCTSTR pszChars, int nCount, CPoint ptTextPos);
	virtual void DrawSingleLine(CDC *pdc, int nLineIndex);
    void func1(CDC *pdc, TEXTBLOCK *pBuf, int I, int nLength, CPoint& origin,
               LPCTSTR pszChars, int nLineIndex);


    virtual HINSTANCE GetResourceHandle();

// Attributes
public:
    void SetFont();

    class CTempDraw* m_pdraw;   //¡Ÿ ±¡ø
    virtual void __stdcall SetBKColor(COLORREF textcolor);
    virtual void __stdcall ColorOut(PCSTR str, long len, COLORREF textcolor);
    

	//	Default handle to resources
	static HINSTANCE s_hResourceInst;

	enum
	{
		//	Base colors
		COLORINDEX_0 = 0,
		COLORINDEX_func,
        COLOR_Var,
        COLOR_VarH,
        COLOR_Immed,
        COLOR_ea,
        COLOR_type,
        COLOR_label,

		COLORINDEX_WHITESPACE,
		COLORINDEX_BKGND,
		COLORINDEX_NORMALTEXT,
		COLORINDEX_SELMARGIN,
		COLORINDEX_SELBKGND,
		COLORINDEX_SELTEXT,
		//	Syntax colors
		COLORINDEX_KEYWORD,
		COLORINDEX_COMMENT,
		COLORINDEX_NUMBER,
		COLORINDEX_OPERATOR,      // [JRT]:
		COLORINDEX_STRING,
		COLORINDEX_PREPROCESSOR,
		//	Compiler/debugger colors
		COLORINDEX_ERRORBKGND,
		COLORINDEX_ERRORTEXT,
		COLORINDEX_EXECUTIONBKGND,
		COLORINDEX_EXECUTIONTEXT,
		COLORINDEX_BREAKPOINTBKGND,
		COLORINDEX_BREAKPOINTTEXT
		//	...
		//	Expandable: custom elements are allowed.
	};

// Operations
public:
	void AttachToBuffer(CRorTextBuffer *pBuf = NULL);
	void DetachFromBuffer();

	//	Buffer-view interaction, multiple views
	virtual CRorTextBuffer *LocateTextBuffer();
	virtual void UpdateView();  //CRorTextView *pSource, CUpdateContext *pContext, DWORD dwFlags, int nLineIndex = -1);

	//	Operations
	void EnsureVisible(CPoint pt);


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRorTextView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
    
	//}}AFX_VIRTUAL

// Implementation
public:
	CRorTextView();
	~CRorTextView();

protected:

// Generated message map functions
protected:
#ifdef _DEBUG
	void AssertValidTextPos(const CPoint &pt);
#endif

	//{{AFX_MSG(CRorTextView)
    afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnDestroy();
    afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    //afx_msg void OnTimer(UINT nIDEvent);
    afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnEditCopy();
    afx_msg void OnEditSelectAll();
    afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    //}}AFX_MSG
    
	afx_msg void OnCharLeft();
	afx_msg void OnExtCharLeft();
	afx_msg void OnCharRight();
	afx_msg void OnExtCharRight();
	afx_msg void OnWordLeft();
	afx_msg void OnExtWordLeft();
	afx_msg void OnWordRight();
	afx_msg void OnExtWordRight();
	afx_msg void OnLineUp();
	afx_msg void OnExtLineUp();
	afx_msg void OnLineDown();
	afx_msg void OnExtLineDown();
	afx_msg void OnPageUp();
	afx_msg void OnExtPageUp();
	afx_msg void OnPageDown();
	afx_msg void OnExtPageDown();
	afx_msg void OnLineEnd();
	afx_msg void OnExtLineEnd();
	afx_msg void OnHome();
	afx_msg void OnExtHome();
	afx_msg void OnTextBegin();
	afx_msg void OnExtTextBegin();
	afx_msg void OnTextEnd();
	afx_msg void OnExtTextEnd();

    afx_msg void ScrollUp();
	afx_msg void ScrollDown();
	afx_msg void ScrollLeft();
	afx_msg void ScrollRight();
	DECLARE_MESSAGE_MAP()
};

#ifdef _DEBUG
#define ASSERT_VALIDTEXTPOS(pt)		AssertValidTextPos(pt);
#else
#define ASSERT_VALIDTEXTPOS(pt)
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CRorTEXTVIEW__H)
