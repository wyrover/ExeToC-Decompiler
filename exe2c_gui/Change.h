#if !defined(AFX_CHANGE__H)
#define AFX_CHANGE__H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Change.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CChange dialog


#include "stdafx.h"
#include "editcmd.h"
#include "exe2c_gui.h"

#include "MainFrm.h"
#include "ChildFrm.h"
#include "SampleDoc.h"
#include "SampleView.h"


class CChange : public CDialog
{
// Construction
public:
	CChange(CWnd* pParent = NULL);   // standard constructor
	CString name;

// Dialog Data
	//{{AFX_DATA(CChange)
	enum { IDD = IDD_DIALOG1 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChange)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CChange)
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHANGE__H)
