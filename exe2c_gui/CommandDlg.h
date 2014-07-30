#if !defined(AFX_COMMANDDLG__H)
#define AFX_COMMANDDLG__H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CommandDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCommandDlg dialog

class CCommandDlg : public CDialog
{
// Construction
public:
	void OnOK();
	CCommandDlg(CWnd* pParent = NULL);   // standard constructor
	char buf[1024];
    void AddLine(PCSTR str);
	

// Dialog Data
	//{{AFX_DATA(CCommandDlg)
	enum { IDD = IDD_COMMAND };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCommandDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCommandDlg)
		// NOTE: the ClassWizard will add member functions here
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG	
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COMMANDDLG__H)
