// ButtonBar.cpp : implementation file
//

#include "stdafx.h"
#include "exe2c_gui.h"
#include "ButtonBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CButtonBar dialog


CButtonBar::CButtonBar()
{
	//{{AFX_DATA_INIT(CButtonBar)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CButtonBar::DoDataExchange(CDataExchange* pDX)
{
	CDialogBar::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CButtonBar)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CButtonBar, CDialogBar)
	//{{AFX_MSG_MAP(CButtonBar)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CButtonBar message handlers
LONG  CButtonBar::OnInitDialog  (UINT  wParam,  LONG  lParam)
 {
	 if  ( !HandleInitDialog(wParam,  lParam)  ||  !UpdateData(FALSE))
		{
			TRACE0("Warning:  UpdateData  failed  during  dialog  init.\n");
			return  FALSE;
		}


	
	return TRUE;
}