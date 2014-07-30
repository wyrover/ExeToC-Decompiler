// Copyright(C) 1999-2005 LiuTaoTao，bookaa@rorsoft.com

//	analysis.cpp
#include "stdafx.h"

#include "cisc.h"
#include "CStrategy.h"

extern bool g_f_Step_by_Step;
extern bool g_any1_return_TRUE;
bool Step_by_Step();

bool	CFunc::analysis_step_by_step()
{
	//	让我们显示点信息
	static CFunc* lastfunc = 0;
	static int n = 0;
	if (this != lastfunc)
	{
		lastfunc = this;
		n = 0;
	}

	g_f_Step_by_Step = true;
	g_any1_return_TRUE = false;
	bool f = analysis_once();
	g_f_Step_by_Step = false;
	f = f || g_any1_return_TRUE;

	if (f)
	{
		log_prtl("step %d",n++);
	}
	return f;
}

typedef bool (CFuncOptim::*OPTIMFUNC)();
typedef bool (CFunc::*PROGFUNC)();

PROGFUNC tbl_Progress[] =
{
    CFunc::Step_1,
    CFunc::Step2_GetRetPurge,
    CFunc::AddRemoveSomeInstr,
    CFunc::Step3_FillStackInfo,
    CFunc::Step_Label_Analysis,
    CFunc::Step4_1,
    CFunc::Var_analysis,
    0
};

OPTIMFUNC tbl_Ana[] =
{
	CFuncOptim::Address_to_Add,					//0 看看i_Address能不能变成i_Add
	CFuncOptim::Simplify_Instr,					//1 看看简单指令能不能变成i_Assign
	CFuncOptim::Var_Split,					    //2 变量拆分
    CFuncOptim::ClassSubFuncProcess,            //  如果是一个class的子函数
	CFuncOptim::VarDataType_analysis_mydefine,	//3
	CFuncOptim::VarDataType_analysis,	        //4
	CFuncOptim::DataType_Flow,	                //5 数据类型流分析
	CFuncOptim::optim_once_new,	                //6
	CFuncOptim::pcode_1,	                    //7 如果cmp和jxx紧靠，把cmp和jxx合并
	CFuncOptim::ana_Flow,	                    //8
	0
};

bool	CFunc::analysis_once_1()
{
    m_prepareTrue_analysisFalse = false;
    if (this->m_nStep < STEP_100)
    {
        PROGFUNC fn = tbl_Progress[m_nStep];
        if (fn != NULL)
        {
            if ((this->*fn)())
            {
                m_nStep++;
                return true;
            }
            return false;
        }
        this->m_nStep = STEP_100;   //说明过关了！
    }
    
    assert(this->m_nStep == STEP_100);

    CFuncOptim the(this);
    for (int i=0; ;i++)
    {
        OPTIMFUNC pfunc = tbl_Ana[i];
        if (pfunc == 0)
            break;
		if ((the.*pfunc)())
            return true;
    }


	return false;
}
bool	CFunc::analysis_once()
{
    bool f = analysis_once_1();
    if (f)
    {
        if (g_CStrategy.IfAny())
        {
            g_CStrategy.PrintIt(this->m_instr_list, this);
            g_CStrategy.DoIt(this->m_instr_list, this->m_exprs);
        }
        DeleteUnusedVar();
    }
    return f;
}
void CFunc::analysis()
{
    for (;;)
    {
        g_f_Step_by_Step = true;
        g_any1_return_TRUE = false;
        if (!this->analysis_once())
            break;
    }
}


void	CFunc::ana_RetType()
{	//	检查函数的返回值
    VAR v;
    v.type = v_Reg;
    v.reg = enum_EAX;   //	enum_EAX = 0 = enum_AL = enum_AX 
    v.opsize = BIT32_is_4;

    if (this->m_functype != NULL)
    {
        int n = GG_VarType_ID2Size(this->m_functype->m_retdatatype_id);
        if (n == 0)
            return;
        if (n == 2 || n == 4)
            v.opsize = n;
    }


    POSITION pos = m_instr_list->GetHeadPosition();
	while (pos)
	{
		POSITION savpos = pos;
		PINSTR p = m_instr_list->GetNext(pos);
		if (p->type == i_Return)
		{
			PINSTR pnew = new INSTR;    //new_INSTR
			pnew->type = i_RetPar;	//	暂时认为每一个func都是ret DWORD
			pnew->var_r1 = v;
			m_instr_list->InsertBefore(savpos,pnew);
		}
	}
}

void CFunc::PrepareFunc()
{//prepare 是可以增加新函数的，但不会调用新函数的prepare
    m_prepareTrue_analysisFalse = true;
    while (this->m_nStep < 3)
    {
        PROGFUNC fn = tbl_Progress[m_nStep];
        if (fn != NULL)
        {
            if ((this->*fn)())
            {
                m_nStep++;
                continue;
            }
            break;
        }
        else
            this->m_nStep = STEP_100;
    }
}
