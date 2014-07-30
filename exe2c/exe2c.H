///////////////////////////////////////////////////////////////
//
// exe2c.h
// Copyright(C) 1999-2005 LiuTaoTao，bookaa@rorsoft.com
// Created at 2005.2.1
// Description:	The interface description of the component
// History:		
//
///////////////////////////////////////////////////////////////
//#include "..\..\exe2c\exe2c.H"

#ifndef	_EXE2C_H_
#define	_EXE2C_H_

#include "..\I_KSUNKNOWN\KsFrame.h"

#define	IID_EXE2C				0x00006efa
#define	EXE2C_INITORDER		0x80000000
#define	EXE2C_PARENT_IID		NULL
#define	EXE2C_PRIORITY			0x80000000

typedef unsigned int uint;
struct st_FuncInfo
{
    char name[256];
    int nStep;
    uint headoff;
    uint endoff;
    int stack_purge;
    int m_EBP_base;
    int m_args;
};

struct st_LINE_SYNTAX
{
    int pos;    //以0开始的在字串中的位置，不能大于串长
    int len;
    int colorindex; //用什么颜色显示
    void* handle;   //这是个什么东西，对于未知的东西，或无意义的东西，这是零
};

class I_E2COUT
{
public:
    virtual void __stdcall prt_log(PCSTR str) = 0;
};

class I_XmlOut
{
public:
	virtual void __stdcall prtt(PCSTR s) = 0;
	virtual void __stdcall XMLbegin(enum XMLTYPE xmltype, PVOID p) = 0;
	virtual void __stdcall XMLend(enum XMLTYPE xmltype) = 0;
};


class I_EXE2C : public I_KSUNKNOWN
{
public:
	//Add interface here
	virtual bool	__stdcall test() = 0;	//Test interface
	
    virtual void __stdcall exe2c_main(PCSTR fname) = 0;
    virtual void __stdcall prtout_asm(I_XmlOut* iOut) = 0;
    virtual void __stdcall prtout_itn(I_XmlOut* iOut) = 0;
    virtual void __stdcall prtout_cpp(I_XmlOut* iOut) = 0;
    virtual void __stdcall Init(I_E2COUT* i_E2COut) = 0;

    virtual HANDLE __stdcall GetFirstFuncHandle() = 0;
    virtual void   __stdcall GetFuncInfo(HANDLE h, OUT st_FuncInfo* info) = 0;
    virtual HANDLE __stdcall GetNextFuncHandle(HANDLE h) = 0;
    virtual HANDLE __stdcall GetCurFuncHandle() = 0;

    virtual void __stdcall SetCurFunc_by_Name(PCSTR funcname) = 0;

    virtual bool __stdcall analysis_Once()  = 0;
    virtual void __stdcall analysis_All()  = 0;
    virtual bool __stdcall RenameCurFuncName(PCSTR name) = 0;
    virtual void __stdcall DoCommandLine(PCSTR cmd) = 0;
    
    virtual bool __stdcall Rename(enum XMLTYPE xmltype, PVOID p, PCSTR newname) = 0;
    virtual void __stdcall ReType(int colorindex, void* handle, PCSTR newtype) = 0;
    virtual void __stdcall Change_Array(int colorindex, void* handle, int newarray) = 0;
    virtual void __stdcall HotKey(int colorindex, void* handle, char key) = 0;
    virtual void __stdcall LineHotKey(void* hline, char nChar) = 0;
    //Add interface here
};

KS_DECLARE_INTERFACE(exe2c, EXE2C)

#endif	// _EXE2C_H_

/*	这里放接口函数的详细解释
	
*/	
