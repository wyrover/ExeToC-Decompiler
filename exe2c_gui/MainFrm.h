// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM__H)
#define AFX_MAINFRM__H

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
#include "buttonbar.h"
#include "sampledoc.h"
#include "CoolTabCtrl.h"
#include"viewfundlg.h"
#include "Log.h"
#include "commanddlg.h"

class CMainFrame : public CMDIFrameWnd, public I_E2COUT
{
	DECLARE_DYNAMIC(CMainFrame)
public:
	CMainFrame();
	CCoolTabCtrl	m_TabCtrl;
	CTreeCtrl		m_wndTree;
	CEdit			m_wndEdit;
	CCoolBar		m_wndMyBar1;
	CCoolBar		m_wndMyBar2;
	CCoolBar		m_wndLogBar3;
	CViewFunDlg     dlg;
	CCommandDlg     m_commandDlg;
	CCommandDlg		m_log;
	

	CListCtrl       m_listFun;	
	//CLog *pCLog;
// Attributes
public:
// Operations
public:
//	CChildFormA m_wndChildOGLView1;
//	CChildFormA m_wndChildOGLView2;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
    virtual void __stdcall prt_log(PCSTR str);
	void ClearFun();
	 void ShowFun();
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;
	//CButtonBar  m_buttonbar;

	CString			m_strInfo;
//	CCoolBar m_wndMyBar1;///我们将它作为左边的窗口
//	CCoolBar m_wndMyBar2;///停靠在下方的窗口
// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnOptim() ;
	afx_msg void OnViewForm1();
	afx_msg void OnViewForm2();
	afx_msg void OnShowleftbar();
	afx_msg void OnUpdateShowleftbar(CCmdUI* pCmdUI);
	afx_msg void OnViewFun();
	afx_msg void OnUpdateViewFun(CCmdUI* pCmdUI);
	afx_msg void OnViewCommand();
	afx_msg void OnUpdateViewCommand(CCmdUI* pCmdUI);
	afx_msg void OnUpdateLog2(CCmdUI* pCmdUI);
	afx_msg void OnCommandLog2();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnTest();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM__H)
