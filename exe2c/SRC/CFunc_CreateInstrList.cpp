// Copyright(C) 1999-2005 LiuTaoTao，bookaa@rorsoft.com

#include "stdafx.h"
//	CFunc_CreateInstrList.cpp

#include "cisc.h"


	
bool CFunc::Step4_1()
{
    this->Step4_CreateInstrList();  ////	and set STEP_4

    this->Step5_GetArgs();	//	and set STEP_5
    this->ana_RetType();
    this->Func_FillCallParas();	//	Fill Call paras, and Step = 6

    return true;
}
void CFunc::Step4_CreateInstrList()
// 读取代码序列
//	读取intel代码序列，转变为伪代码，构造CFunc的伪代码序列表instr_list
//  同时构造CFunc的内部变量表 expr_list，
//  如果需要的话，在全局变量表 g_expr_list 中添加条目
{
	// 初步完成构造伪代码序列表instr_list的工作
	// 但在 stack, expr, call 等方面尚需完善

	m_instr_list = new INSTR_LIST;  //new_INSTR_LIST 伪码表

    CCodeList the;
	the.CreateInstrList_raw(m_instr_list, this->ll.m_asmlist, this->m_EBP_base);

	// 完善一，对 label 的完善,因为在每条指令前加了label，要去掉没人引用的

	Create_Labels_backend();
	// 完善二，对 call 的完善
//	CreateInstrList_welldone_call();   	// find call, and fill its args

}
PINSTR findlabel(INSTR_LIST* list, ea_t off)
{
	assert(off);	//	一般情况下，这是不为零的
	POSITION pos = list->GetHeadPosition();
	while (pos)
	{
		PINSTR p = list->GetNext(pos);
		if (p->type == i_Label && p->label.label_off == off)
			return p;
	}
	assert_msg(0,"why here");
	return NULL;
}
void CFunc::Create_Labels_backend()	// 标号后端
{
	INSTR_LIST* list = this->m_instr_list;
	POSITION pos = list->GetHeadPosition();
	while (pos)
	{
		PINSTR p = list->GetNext(pos);
		if (p->type == i_Jump)
		{
			PINSTR thelabel = findlabel(list,p->jmp.jmpto_off);
			if (thelabel->label.ref_instr)
				p->jmp.next_ref_of_this_label = thelabel->label.ref_instr;	// save old ref list
			thelabel->label.ref_instr = p;	// tell the label it was referred
			p->jmp.the_label = thelabel;	// tell the Jxx the label it need
		}
	}
	
	pos = list->GetHeadPosition();
	while (pos)
	{	// remove all label not referred
		POSITION savpos = pos;
		PINSTR p = list->GetNext(pos);
		if (p->type == i_Label && p->label.ref_instr == 0)
		{
			list->RemoveAt(savpos);
		}
	}
}


