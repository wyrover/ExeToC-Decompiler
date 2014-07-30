// Change.cpp : implementation file
//

#include "stdafx.h"
#include "exe2c_gui.h"
#include "Change.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChange dialog


CChange::CChange(CWnd* pParent /*=NULL*/)
	: CDialog(CChange::IDD, pParent)
{
	//{{AFX_DATA_INIT(CChange)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CChange::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CChange)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CChange, CDialog)
	//{{AFX_MSG_MAP(CChange)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChange message handlers

void CChange::OnOK() 
{
	// TODO: Add extra validation here
	CEdit* pEidt = (CEdit*)GetDlgItem(IDC_EDIT1);
	pEidt->GetWindowText(this->name);
	CDialog::OnOK();
}

void CChange::OnCancel() 
{
	// TODO: Add extra cleanup here	
	CDialog::OnCancel();
}
