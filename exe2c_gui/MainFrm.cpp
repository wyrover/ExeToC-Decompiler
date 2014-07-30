// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "exe2c_gui.h"
#include "sampleview.h"
#include "MainFrm.h"
#include "editcmd.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_COMMAND(ID_VIEW_FORM1, OnViewForm1)
	ON_COMMAND(ID_VIEW_FORM2, OnViewForm2)
	ON_COMMAND(ID_SHOWLEFTBAR, OnShowleftbar)
	ON_UPDATE_COMMAND_UI(ID_SHOWLEFTBAR, OnUpdateShowleftbar)
	ON_COMMAND(ID_OPTIM, OnOptim)
	ON_COMMAND(IDD_VIEW_FUN, OnViewFun)
	ON_UPDATE_COMMAND_UI(IDD_VIEW_FUN, OnUpdateViewFun)
	ON_COMMAND(IDD_VIEW_COMMAND, OnViewCommand)
	ON_UPDATE_COMMAND_UI(IDD_VIEW_COMMAND, OnUpdateViewCommand)
	ON_UPDATE_COMMAND_UI(ID_LOG2, OnUpdateLog2)
	ON_COMMAND(ID_LOG2, OnCommandLog2)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_SIZING()
	ON_WM_SIZE()
	ON_WM_SHOWWINDOW()
	ON_COMMAND(ID_TEST, OnTest)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

I_EXE2C* g_EXE2C = NULL;

static UINT indicators[] =
{
	ID_SEPARATOR,               // status line indicator 
	ID_EDIT_INDICATOR_POSITION,	 
	ID_EDIT_INDICATOR_COL,
	ID_EDIT_INDICATOR_CRLF,
	ID_INDICATOR_OVR,	
	ID_EDIT_INDICATOR_READ,
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CSampleView *g_VIEW = NULL;

extern CMainFrame* g_Mfm;
CMainFrame::CMainFrame()
{
	g_Mfm = this;

    g_EXE2C = NEW_EXE2C();
	g_EXE2C->Init(this);
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
//	
//	if (!m_wndToolBar.Create(this) ||
//		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
//	{
//		TRACE0("Failed to create toolbar\n");
//		return -1;      // fail to create
//	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}
	
	//pCLog = NULL;

	// TODO: Remove this if you don't want tool tips or a resizeable toolbar
//	m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() |
//		CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);
//	if (!m_buttonbar.Create(this,IDD_DIALOGBAR1,  CBRS_TOP, IDD_DIALOGBAR1))
//	{
//		return -1;
//	}

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
// 	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
//	EnableDocking(CBRS_ALIGN_ANY);
//	DockControlBar(&m_wndToolBar);
	if (!m_wndMyBar1.Create(_T("控制条"), this, CSize(280,100),TRUE,123))
	{
		TRACE0("Failed to create mybar\n");
			return -1;
	}
	if (!m_wndMyBar2.Create(_T("我的控制条2"), this,CSize(200,30),TRUE,124))
	{
		TRACE0("Failed to create mybar\n");
			return -1;
	}
	
	if (!m_wndLogBar3.Create(_T("输出窗口"), this,CSize(100,250),TRUE,124))
	{
		TRACE0("Failed to create mybar\n");
			return -1;
	}

	

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.SetButtonText(0," Optim ");
	m_wndToolBar.SetButtonText(1," Exit ");
	/////////////调整工具条/////////////////
	CRect rc(0, 0, 0, 0);
	CSize sizeMax(0, 0);
	CToolBarCtrl& bar = m_wndToolBar.GetToolBarCtrl();
	for (int nIndex = bar.GetButtonCount() - 1; nIndex >= 0; nIndex--)
	{
		bar.GetItemRect(nIndex, rc);

		rc.NormalizeRect();
		sizeMax.cx = __max(rc.Size().cx, sizeMax.cx);
		sizeMax.cy = __max(rc.Size().cy, sizeMax.cy);
	}
	//sizeMax.cx += 10;
	m_wndToolBar.SetSizes(sizeMax, CSize(16,15));

	
		////////////创建TAB Control，并把它加入到ControlBar中
	/// 需要注意的是:同一个ControlBar只能加入一个"一级子窗口"
//	m_TabCtrl.Create(TCS_DOWN|WS_CHILD|WS_VISIBLE,CRect(0,0,100,100),&m_wndMyBar1,125);
	/////////////这一段代码创建树型控件////////////
//	if (!m_wndTree.Create(WS_CHILD|WS_VISIBLE|
//		TVS_HASLINES|TVS_HASBUTTONS|TVS_LINESATROOT,
//		CRect(0, 0, 0, 0), &m_TabCtrl, IDC_MYTREECTRL))
//	{
//		TRACE0("Failed to create instant bar child\n");
//		return -1;
//	}
//	m_wndTree.ModifyStyleEx(0, WS_EX_CLIENTEDGE);
	///往树型控件添加内容
//	HTREEITEM hti = m_wndTree.InsertItem(_T("函数名"));
//	m_wndTree.InsertItem(_T("2"));
//	m_wndTree.InsertItem(_T("main()"), hti);
//	m_wndTree.InsertItem(_T("aaa"), hti);
	///将树型控件加入到TabCtrl中
//	m_TabCtrl.AddPage(&m_wndTree,"函数",IDI_ICON1);
//	m_TabCtrl.AddPage(RUNTIME_CLASS(CViewFunDlg),IDD_DIALOGBAR2,"第1页",IDI_ICON1);
//	m_TabCtrl.AddPage(RUNTIME_CLASS(CViewDlg),IDD_DIALOG2,"第三页",IDI_ICON1);
//	m_TabCtrl.UpdateWindow();
	////////对话框///////////
	if(!dlg.Create(IDD_DIALOGBAR2,&m_wndMyBar1))
		return -1;
	dlg.ShowWindow(SW_SHOW);
	if(!m_commandDlg.Create(IDD_COMMAND,&m_wndMyBar2))
		return -1;
	m_commandDlg.ShowWindow(SW_SHOW);

	if(!m_log.Create(IDD_DIALOGBAR3,&m_wndLogBar3))
		return -1;	
	m_log.ShowWindow(SW_SHOW);
	

//	m_listFun.Create(
//   WS_CHILD|WS_VISIBLE|WS_BORDER|LVS_REPORT,
//   CRect(10,10,400,200), pParentWnd, 1);

	////////编辑控件///////////
//	if(!m_wndEdit.Create(WS_VSCROLL|WS_CHILD|WS_VISIBLE|ES_AUTOVSCROLL|ES_MULTILINE|ES_WANTRETURN,CRect(0,0,0,0),&m_wndMyBar2,101))
//		return -1;
//	m_wndEdit.ModifyStyleEx(0,WS_EX_CLIENTEDGE);
	///////////////停靠控制///////////////////
	m_wndMyBar1.SetBarStyle(m_wndMyBar1.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);

	m_wndMyBar2.SetBarStyle(m_wndMyBar2.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);

	m_wndLogBar3.SetBarStyle(m_wndLogBar3.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);

	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	m_wndMyBar1.EnableDocking(CBRS_ALIGN_ANY);
	m_wndMyBar2.EnableDocking(CBRS_ALIGN_ANY);
	m_wndLogBar3.EnableDocking(CBRS_ALIGN_ANY);

	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);
    

	DockControlBar(&m_wndMyBar1, AFX_IDW_DOCKBAR_RIGHT);
	RecalcLayout();

	CRect rect;
	m_wndMyBar1.GetWindowRect(rect);
	rect.OffsetRect(0,1);//偏移一个位置
	DockControlBar(&m_wndLogBar3, AFX_IDW_DOCKBAR_RIGHT,rect);///也停靠在底部


	DockControlBar(&m_wndMyBar2, AFX_IDW_DOCKBAR_BOTTOM);
		

	/////////使浮动与停靠显示相同的头部////
	#ifdef _SCB_REPLACE_MINIFRAME
    m_pFloatingFrameClass = RUNTIME_CLASS(CSCBMiniDockFrameWnd);
	#endif //_SCB_REPLACE_MINIFRAME
//	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
//	EnableDocking(CBRS_ALIGN_ANY);
//	DockControlBar(&m_wndToolBar);


	//::SendMessage(m_log.GetSafeHwnd(),WM_LBUTTONDOWN,0x1,0x31FFF8);
	//::SendMessage(m_log.GetSafeHwnd(),WM_MOUSEMOVE,0x1,0xD6003F);
	//::SendMessage(m_log.GetSafeHwnd(),WM_LBUTTONUP,0x0,0xD6003F);
	

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{

//	cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
//	cs.lpszClass = AfxRegisterWndClass(0);
	return CMDIFrameWnd::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CMDIFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CMDIFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers



void CMainFrame::OnViewForm1() 
{

}

void CMainFrame::OnViewForm2() 
{
}

void CMainFrame::OnShowleftbar() 
{
	ShowControlBar(&m_wndMyBar1, !m_wndMyBar1.IsVisible(), FALSE);
	
}

void CMainFrame::OnUpdateShowleftbar(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable();
	pCmdUI->SetCheck(m_wndMyBar1.IsVisible());
	/*
	if (pCLog == NULL)
	{
		pCLog = new CLog;	
		pCLog->Create(IDD_DIALOG4);
		CRect Rect1;
		CRect Rect2;		
		
		pCLog->GetWindowRect(&Rect1);
		this->GetWindowRect(&Rect2);
		pCLog->SetWindowPos(NULL,
							Rect2.Width()-Rect1.Width()+210,
							Rect2.Height()-Rect1.Height()+180,
							Rect1.Width(),
							Rect1.Height(),
							0);
		
		pCLog->ShowWindow(SW_SHOW);
	}//*/
}





void CMainFrame::ShowFun()
{
	HANDLE h = g_EXE2C->GetFirstFuncHandle();
	int i=0;
    while (h)
    {
		st_FuncInfo info;
		ZeroMemory(&info, sizeof(info));
		g_EXE2C->GetFuncInfo(h, &info);
		if (info.name[0] != 0)
		{
			dlg.m_list.InsertItem(i,"Function name");
			dlg.m_list.SetItemText(i,0,info.name);
			char strStep[20];
			itoa(info.nStep,strStep,10);
			dlg.m_list.SetItemText(i,1,strStep);
			char strHeadoff[20];
			itoa(info.headoff,strHeadoff,16);
			dlg.m_list.SetItemText(i,2,_strupr(strHeadoff));
			char strEndoff[20];
			itoa(info.endoff,strEndoff,16);
			dlg.m_list.SetItemText(i,3,_strupr(strEndoff));
			char strStack_purge[20];
			itoa(info.stack_purge,strStack_purge,10);
			dlg.m_list.SetItemText(i,4,strStack_purge);
		}
        h = g_EXE2C->GetNextFuncHandle(h);
		i+=1;
    }
}

void CMainFrame::ClearFun()
{
    int nCount=dlg.m_list.GetItemCount();
	for(int i = 0;i<nCount;i++)
	{
            dlg.m_list.DeleteItem(0);
    }
}
void MyRefreshView();
void CMainFrame::OnOptim() 
{
	g_EXE2C->analysis_Once();
	MyRefreshView();	
}


void __stdcall CMainFrame::prt_log(PCSTR str)
{
    this->m_log.AddLine(str);
}
void CMainFrame::OnViewFun() 
{
	ShowControlBar(&m_wndMyBar1, !m_wndMyBar1.IsVisible(), FALSE);
	
}

void CMainFrame::OnUpdateViewFun(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable();
	pCmdUI->SetCheck(m_wndMyBar1.IsVisible());	
}

void CMainFrame::OnViewCommand() 
{
	ShowControlBar(&m_wndMyBar2, !m_wndMyBar2.IsVisible(), FALSE);	
}

void CMainFrame::OnUpdateViewCommand(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable();
	pCmdUI->SetCheck(m_wndMyBar2.IsVisible());	
}

void CMainFrame::OnUpdateLog2(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable();
	pCmdUI->SetCheck(m_wndLogBar3.IsVisible());	
	
}

void CMainFrame::OnCommandLog2() 
{
	// TODO: Add your command handler code here
	ShowControlBar(&m_wndLogBar3, !m_wndLogBar3.IsVisible(), FALSE);
}

void CMainFrame::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	//MessageBox("OnLButtonDown","asdf",MB_OK);
	CMDIFrameWnd::OnLButtonDown(nFlags, point);
}

void CMainFrame::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default		
	CMDIFrameWnd::OnMouseMove(nFlags, point);
}

void CMainFrame::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	//MessageBox("OnLButtonUp","asdf",MB_OK);
	CMDIFrameWnd::OnLButtonUp(nFlags, point);
}

void CMainFrame::OnTest() 
{
	// TODO: Add your command handler code here
	SetCursorPos(5,100);
	::SendMessage(m_log.GetSafeHwnd(),WM_LBUTTONDOWN,NULL,NULL);
	Sleep(100);
	::SendMessage(m_log.GetSafeHwnd(),WM_MOUSEMOVE,0x1,0x23A0320);
	Sleep(100);
	::SendMessage(m_log.GetSafeHwnd(),WM_LBUTTONUP,0x0,0x23902FF);
}
void MyRefreshFuncList()
{
    g_Mfm->ClearFun();
    g_Mfm->ShowFun();
}

