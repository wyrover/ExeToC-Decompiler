#if !defined(AFX_BUTTONBAR__H)
#define AFX_BUTTONBAR__H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ButtonBar.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CButtonBar dialog

class CButtonBar : public CDialogBar
{
// Construction
public:
	CButtonBar();   // standard constructor

// Dialog Data
	//{{AFX_DATA(CButtonBar)
	enum { IDD = IDD_DIALOGBAR1 };
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CButtonBar)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CButtonBar)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	afx_msg  LONG  OnInitDialog(UINT, LONG); 

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BUTTONBAR__H)
