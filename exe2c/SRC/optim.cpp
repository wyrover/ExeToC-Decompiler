// Copyright(C) 1999-2005 LiuTaoTao£¬bookaa@rorsoft.com

#include "stdafx.h"
//	optim.cpp

#include "cisc.h"


bool CFunc::expr_only_use_in_this(VAR* pvar, PINSTR phead)
{
	assert( phead->type == i_Begin || phead->type == i_CplxBegin);

	INSTR_LIST* list = this->m_instr_list;
	POSITION pos = list->GetHeadPosition();
	while (pos)
	{
		PINSTR p = list->GetNext(pos);
		if (p == phead)
		{
			p = p->begin.m_end;
			pos = list->Find(p);
			continue;
		}
		if (VAR::IsSame(pvar, &p->var_w))
			return false;
		if (VAR::IsSame(pvar, &p->var_r1))
			return false;
		if (VAR::IsSame(pvar, &p->var_r2))
			return false;
	}
	return true;
}

