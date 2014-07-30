#if !defined(AFX_VIEWFUNDLG__H)
#define AFX_VIEWFUNDLG__H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ViewFunDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CViewFunDlg dialog

class CViewFunDlg : public CDialog
{
// Construction
public:
	CViewFunDlg(CWnd* pParent = NULL);   // standard constructor
	DECLARE_DYNCREATE(CViewFunDlg)

// Dialog Data
	//{{AFX_DATA(CViewFunDlg)
	enum { IDD = IDD_DIALOGBAR2 };
	CListCtrl	m_list;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CViewFunDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CViewFunDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIEWFUNDLG__H)
