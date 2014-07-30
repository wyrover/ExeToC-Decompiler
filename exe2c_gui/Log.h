#if !defined(AFX_LOG__H)
#define AFX_LOG__H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Log.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLog dialog

class CLog : public CDialog
{
// Construction
public:
	CLog(CWnd* pParent = NULL);   // standard constructor	
	char buf[1024];
    void AddLine(PCSTR str);
	
// Dialog Data
	//{{AFX_DATA(CLog)
	enum { IDD = IDD_DIALOG4 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CLog)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LOG__H)
