// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__B1B69ECB_9FCE_11D2_8CA4_0080ADB8683C__INCLUDED_)
#define AFX_STDAFX_H__B1B69ECB_9FCE_11D2_8CA4_0080ADB8683C__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxcmn.h>			// MFC support for Windows Common Controls

#include <afxtempl.h>//
#include <afxpriv.h> 
#include <afxole.h> 
#define	_KSAPP_FRAME_CODE_
#define	_PLUG_INS_DIRECTORY_	"\\"

#include "..\exe2c\exe2c.h"
extern I_EXE2C* g_EXE2C;

#define	_SCB_REPLACE_MINIFRAME  ///浮动时候替换原来TOOL WINDOWS的框架
#include "sizecbar.h"
#include "scbarg.h"
//#include "sizecbar.h" 
//#include "scbarg.h" 

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__B1B69ECB_9FCE_11D2_8CA4_0080ADB8683C__INCLUDED_)
