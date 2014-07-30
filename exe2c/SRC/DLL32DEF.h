// Copyright(C) 1999-2005 LiuTaoTao£¬bookaa@rorsoft.com

#ifndef	DLL32DEF_H
#define	DLL32DEF_H

#include	"CCbuf.h"

CCbuf* ReadDefFile(PSTR fname);
void onExit_DLL32DEF();
PSTR DLLDEF_Get_ApiName_from_ord(PSTR pDLLname, WORD ord);

#endif	//DLL32DEF_H
