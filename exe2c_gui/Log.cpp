// Log.cpp : implementation file
//

#include "stdafx.h"
#include "exe2c_gui.h"
#include "Log.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLog dialog


CLog::CLog(CWnd* pParent /*=NULL*/)
	: CDialog(CLog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CLog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLog)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLog, CDialog)
	//{{AFX_MSG_MAP(CLog)
	ON_WM_SHOWWINDOW()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLog message handlers

/*void CLog::OnSize(UINT nType, int cx, int cy) 
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

void CLog::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	
	CEdit *p = (CEdit *)GetDlgItem(IDC_EDIT1);
	p->SetWindowText(this->buf);
	// TODO: Add your message handler code here
	
}*/

void CLog::OnSize(UINT nType, int cx, int cy) 
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

void CLog::AddLine(PCSTR str)
{
	//MessageBox("asdfasd", str,MB_OK);	

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
    
	//MessageBox("asdfasd","adsf",MB_OK);
}
