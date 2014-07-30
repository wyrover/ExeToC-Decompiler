// CommandDlg.cpp : implementation file
//

#include "stdafx.h"
#include "exe2c_gui.h"
#include "CommandDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCommandDlg dialog


CCommandDlg::CCommandDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCommandDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCommandDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CCommandDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCommandDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCommandDlg, CDialog)
	//{{AFX_MSG_MAP(CCommandDlg)
		// NOTE: the ClassWizard will add message map macros here
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCommandDlg message handlers

#include "mainfrm.h"
extern class CMainFrame* g_Mfm;
BOOL CCommandDlg::PreTranslateMessage(MSG* pMsg) 
{

	if(pMsg->message==WM_KEYDOWN && pMsg->wParam==13)
	{
		CString m_strCommand;
		GetDlgItem(IDC_COMMAND)->GetWindowText(m_strCommand);
        ::g_EXE2C->DoCommandLine(m_strCommand);

    g_Mfm->ClearFun();
    g_Mfm->ShowFun();

		//MessageBox(m_strCommand);
		GetDlgItem(IDC_COMMAND)->SetWindowText("");
//		return false;
		
	}	
	return CDialog::PreTranslateMessage(pMsg);
}

void CCommandDlg::OnOK()
{


}

void CCommandDlg::AddLine(PCSTR str)
{
	CEdit *p = (CEdit *)GetDlgItem(IDC_EDIT1);	
	strcpy(this->buf,str);
	char *s = strchr(buf,'\n');
	if(s != NULL)
	{
		strcpy(s, "\r\n");
	}//*/
	if (p != NULL)
	{
		p->ReplaceSel(buf);		
	}	
}
void CCommandDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	if(nType ==SIZE_RESTORED)
	{
		CRect r;
		this->GetClientRect(&r);
		CEdit *p = (CEdit *)GetDlgItem(IDC_EDIT1);
		if(NULL != p->GetSafeHwnd())
		{
			p->MoveWindow(r);
			p->GetClientRect(&r);
		}
	}
}