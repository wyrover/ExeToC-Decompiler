///////////////////////////////////////////////////////////////
//
// Cexe2c.h
// Copyright(C) 1999-2005 LiuTaoTao，bookaa@rorsoft.com
// Created at 2005.2.1
// Description:	The standard header file of the component implement
// History:		
//
///////////////////////////////////////////////////////////////

#ifndef	_CEXE2C_H_
#define	_CEXE2C_H_

#include "..\exe2c.H"
#include "cisc.h"
#include "proto.h"
#include "CFuncStep1.h"

class Cexe2c : public I_EXE2C
{
public:
	Cexe2c(){}
	~Cexe2c();

public:
///////////// DO NOT EDIT THIS //////////////
	virtual bool	__stdcall BaseInit();	//override the origin function, it's a class creator!
///////////// DO NOT EDIT THIS //////////////

	//Add interface here
	virtual bool	__stdcall test();		//Test interface
    void __stdcall exe2c_main(PCSTR fname);
    void __stdcall prtout_asm(I_XmlOut* iOut)
    {
        if (g_Cur_Func->m_nStep == 0)
            return;

        CXmlOutPro out(iOut);
        CFuncLL the(g_Cur_Func->ll.m_asmlist);
        the.prtout_asm(g_Cur_Func, &g_Cur_Func->m_varll, &out);
    }
    void __stdcall prtout_itn(I_XmlOut* iOut) 
    { 	
        CXmlOutPro out(iOut);
        g_Cur_Func->prtout_internal(&out);
    }
    void __stdcall prtout_cpp(I_XmlOut* iOut)
    {
		if (g_Cur_Func != NULL)
		{
			CXmlOutPro out(iOut);
			CFunc_Prt prt(g_Cur_Func);
			prt.prtout_cpp(&out);
		}
    }
    void __stdcall Init(I_E2COUT* i_E2COut)
    {
        m_E2COut = i_E2COut;
    }
    void prt_log(PCSTR str)
    {
        if (m_E2COut != NULL)
        {
            m_E2COut->prt_log(str);
        }
    }


    HANDLE __stdcall GetFirstFuncHandle();
    void   __stdcall GetFuncInfo(HANDLE h, OUT st_FuncInfo* info);
    HANDLE __stdcall GetNextFuncHandle(HANDLE h);
    HANDLE __stdcall GetCurFuncHandle();

    void __stdcall SetCurFunc_by_Name(PCSTR funcname);

    bool __stdcall analysis_Once() 
	{
		if (g_Cur_Func != NULL)
			return (g_Cur_Func->analysis_step_by_step());
		return false;
    }
    void __stdcall analysis_All() {
        g_Cur_Func->analysis();
    }
    bool __stdcall RenameCurFuncName(PCSTR name);
    virtual void __stdcall DoCommandLine(PCSTR cmd);
    virtual bool __stdcall Rename(enum XMLTYPE xmltype, void* handle, PCSTR newname);
    virtual void __stdcall ReType(int colorindex, void* handle, PCSTR newtype);
    virtual void __stdcall Change_Array(int colorindex, void* handle, int newarray);
    virtual void __stdcall HotKey(int colorindex, void* handle, char key);
    virtual void __stdcall LineHotKey(void* hline, char nChar);
	//Add interface here

    void Recurse_Analysis();
    void Recurse_Optim();
    CFunc* func_new(ea_t start);
    CFunc* GetFunc(ea_t start);

    
private:
	//Add member here
    I_E2COUT* m_E2COut;
    CNameMng* m_api_name_manager;   //用于保存API的函数名列表
    FileLoader* m_FileLoader;
    FUNC_LIST* m_func_list;	// 全局函数列表
	//Add member here

    CFunc*	FindFuncByName(PCSTR pname);
    void	do_exe2c(ea_t entry);
};

extern Cexe2c* g_Cexe2c;
#endif	// _CEXE2C_H_
