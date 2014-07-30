// Copyright(C) 1999-2005 LiuTaoTao£¬bookaa@rorsoft.com

//	ComplexInstr.h
#ifndef ComplexInstr__H
#define ComplexInstr__H

struct OneCase
{
	int case_n;
	PINSTR thelabel;
};

typedef CList<OneCase*,OneCase*> CasePrt_List;



#endif // ComplexInstr__H
