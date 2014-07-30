// exe2c.h : main header file for the EXE2C DLL
//

#if !defined(AFX_EXE2C_H__3C47A373_6FEE_4FC4_BD6E_93C40AAD22B1__INCLUDED_)
#define AFX_EXE2C_H__3C47A373_6FEE_4FC4_BD6E_93C40AAD22B1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

//#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// Cexe2cApp
// See exe2c.cpp for the implementation of this class
//

class Cexe2cApp : public CWinApp
{
public:
	Cexe2cApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Cexe2cApp)
	//}}AFX_VIRTUAL

	//{{AFX_MSG(Cexe2cApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EXE2C_H__3C47A373_6FEE_4FC4_BD6E_93C40AAD22B1__INCLUDED_)
