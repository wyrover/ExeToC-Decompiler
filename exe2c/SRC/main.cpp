// Copyright(C) 1999-2005 LiuTaoTao，bookaa@rorsoft.com

#include "stdafx.h"
#include "cexe2c.h"
#include "CISC.H"

CFunc* g_Cur_Func = NULL;

//EXPR_LIST	*g_expr_list = NULL;	// 全局变量表


void __stdcall outstring_in_log(PCSTR str)
{
    g_Cexe2c->prt_log(str);
}

HANDLE Cexe2c::GetFirstFuncHandle()
{
    if (m_func_list == NULL)
        return 0;
    POSITION pos = m_func_list->GetHeadPosition();
    return (HANDLE)pos;
}

HANDLE Cexe2c::GetCurFuncHandle()
{
    if (m_func_list == NULL)
        return 0;
    POSITION pos = m_func_list->GetHeadPosition();
    while (pos)
    {
        POSITION sav_pos = pos;
        CFunc* p = m_func_list->GetNext(pos);
        if (p == g_Cur_Func)
        {
            return sav_pos;
        }
    }
    return 0;
}

void Cexe2c::SetCurFunc_by_Name(PCSTR funcname)
{
	CFunc *p = this->FindFuncByName((PSTR)funcname);
    if (p == NULL)
    	return;
    g_Cur_Func = p;
}
void   Cexe2c::GetFuncInfo(HANDLE h, OUT st_FuncInfo* info)
{
    if (m_func_list == NULL)
        return;
    if (h == 0)
        return;
    
    POSITION pos = (POSITION)h;
    CFunc* p = m_func_list->GetNext(pos);

    strcpy(info->name, p->m_funcname);
    info->nStep = p->m_nStep;
    info->headoff = p->m_head_off;
    info->endoff = p->m_end_off;
    info->stack_purge = p->m_stack_purge;
    info->m_EBP_base = p->m_EBP_base;
    info->m_args = p->m_args;
}
HANDLE Cexe2c::GetNextFuncHandle(HANDLE h)
{
    if (m_func_list == NULL)
        return NULL;
    if (h == 0)
        return 0;
    
    POSITION pos = (POSITION)h;
    m_func_list->GetNext(pos);
    return (HANDLE)pos;
}

bool Cexe2c::RenameCurFuncName(PCSTR name)
{
	CFunc *p = g_Cur_Func;
    if (p == NULL)
    	return false;
	if (!IfValideFuncName(name))
    	return false;	// name not valid
    if (this->FindFuncByName(name) != NULL )
    	return false;	// name already use
    strcpy(p->m_funcname, name);
    return true;
}
