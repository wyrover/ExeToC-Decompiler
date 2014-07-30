// Copyright(C) 1999-2005 LiuTaoTao，bookaa@rorsoft.com

#include "stdafx.h"
#include	"CISC.H"

INSTR::INSTR()
{
    this->va_r1.pv = &this->var_r1;
    this->va_r2.pv = &this->var_r2;
}

INSTR::~INSTR()
{
}


bool st_InstrAddOn::IsSame(st_InstrAddOn* p1, st_InstrAddOn* p2)
{//static function
    if (p1 == NULL)
    {
        return (p2 == NULL);
    }
    if (p2 == NULL)
        return false;
    //现在，两个都不是NULL了
    if (p1->type != p2->type)
        return false;
    if (p1->type == IA_AddImmed || p1->type == IA_MulImmed)
    {
        if (p1->addimmed.iAddon != p2->addimmed.iAddon)
            return false;
    }
    return IsSame(p1->pChild, p2->pChild);
}
