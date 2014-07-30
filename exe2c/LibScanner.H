///////////////////////////////////////////////////////////////
//
// LibScanner.h
// Copyright(C) 1999-2005 LiuTaoTao，bookaa@rorsoft.com
//
///////////////////////////////////////////////////////////////
//#include "..\..\LibScanner\LibScanner.H"

#ifndef	_LIBSCANNER_H_
#define	_LIBSCANNER_H_

#include "..\I_KSUNKNOWN\KsFrame.h"

#define	IID_LIBSCANNER				0x00003a91
#define	LIBSCANNER_INITORDER		0x80000000
#define	LIBSCANNER_PARENT_IID		NULL
#define	LIBSCANNER_PRIORITY			0x80000000
#pragma warning(disable:4200)

typedef struct REFSYMBOL
{
	CHAR    RefSymbol[_MAX_PATH];	//引用符号
	WORD	RefType;    //such as IMAGE_REL_I386_REL32
	DWORD	RefOffset;				//引用在函数中的偏移
} *PREFSYMBOL;

typedef struct tagFUNCTION_SYMBOL
{
	DWORD       dwFuncLen;
	BYTE*		FunRawData;
	CHAR		ObjName[_MAX_PATH];
	CHAR		FunctionName[_MAX_PATH];
	DWORD		RefCount;			//引用的符号次数
	REFSYMBOL	RefInfo[];			//引用信息
}FUNCTION_SYMBOL,* PFUNCTION_SYMBOL;
#pragma warning(default:4200)

typedef const BYTE* PCBYTE;

class I_LIBSCANNER : public I_KSUNKNOWN
{
public:
	//Add interface here
	virtual bool	__stdcall test() = 0;	//Test interface
	//Add interface here
    
	virtual BOOL __stdcall ScanLib(LPCSTR szLib)=0;
	virtual PFUNCTION_SYMBOL __stdcall GetFunctionInfo(LPCSTR szFun)=0;
    virtual PCSTR __stdcall CheckIfLibFunc(PCBYTE phead) = 0;
};

KS_DECLARE_INTERFACE(LibScanner, LIBSCANNER)

#endif	// _LIBSCANNER_H_

/*	这里放接口函数的详细解释
	
*/	
