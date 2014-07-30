// ViewFunDlg.cpp : implementation file
//

#include "stdafx.h"
#include "exe2c_gui.h"
#include "ViewFunDlg.h"
#include "sampleview.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CViewFunDlg dialog
IMPLEMENT_DYNCREATE(CViewFunDlg, CDialog)


CViewFunDlg::CViewFunDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CViewFunDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CViewFunDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CViewFunDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CViewFunDlg)
	DDX_Control(pDX, IDC_LIST1, m_list);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CViewFunDlg, CDialog)
	//{{AFX_MSG_MAP(CViewFunDlg)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, OnDblclkList1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CViewFunDlg message handlers

BOOL CViewFunDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_list.SetExtendedStyle(m_list.GetExtendedStyle() | LVS_EX_GRIDLINES |LVS_EX_FULLROWSELECT |LVS_EX_FULLROWSELECT);
	m_list.InsertColumn(0,"Name",40,70,10);
	m_list.InsertColumn(1,"nStep",40,45,10);
	m_list.InsertColumn(2,"headoff",40,50,10);
	m_list.InsertColumn(3,"endoff",40,50,10);
	m_list.InsertColumn(4,"stack",40,50,10);

	//	  li->Caption = info.name;
//            li->SubItems->Add( IntToStr(info.nStep) );
//            li->SubItems->Add( IntToHex((int)info.headoff,8) );
//            li->SubItems->Add( IntToHex((int)info.endoff,8) );
//            li->SubItems->Add( IntToStr(info.stack_purge) );

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
void MyRefreshView();
void CViewFunDlg::OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	UINT i,uSelectedCount=m_list.GetSelectedCount();
	int nItemSel=-1;
	
	CString strID;
	if(uSelectedCount>0)
	{
		for(i=0;i<uSelectedCount;i++)
			nItemSel=m_list.GetNextItem(nItemSel,LVNI_SELECTED);
		
		strID=m_list.GetItemText(nItemSel,0);
	}
//	MessageBox(strID);
	g_EXE2C->SetCurFunc_by_Name(strID);
    MyRefreshView();
	*pResult = 0;
}
