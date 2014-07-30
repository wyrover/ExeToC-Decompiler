// Copyright(C) 1999-2005 LiuTaoTao，bookaa@rorsoft.com

#include "stdafx.h"
#include	"CISC.H"

DWORD	g_ea2ptr = 0;

void	Disassembler_Init_offset(PBYTE code_buf, ea_t code_offset)
// 因为文件的调入地址与虚拟地址不同，所以要记住这个差值
// 以后主程序只以offset来访问，不管实际buffer
{
	g_ea2ptr = (DWORD)code_buf - code_offset;
}

PBYTE	ea2ptr(ea_t pos)
{
	return PBYTE(g_ea2ptr+pos);
}
ea_t ptr2ea(void* p)
{
    PBYTE p1 = ea2ptr(0);
    return (PBYTE)p - p1;
}

BYTE	Peek_B(ea_t pos)
{
	PBYTE p = ea2ptr(pos);
    return *p;
}
WORD	Peek_W(ea_t pos)
{
	PBYTE p = ea2ptr(pos);
    return *(WORD *)p;
}
DWORD	Peek_D(ea_t pos)
{
	PBYTE p = ea2ptr(pos);
    return *(DWORD *)p;
}

bool	XCPUCODE::IsJxx()
{
	BYTE opcode = this->opcode;
	switch (opcode)
	{
	case	C_JO:
	case	C_JNO:
	case	C_JB:
	case	C_JNB:
	case	C_JZ:
	case	C_JNZ:
	case	C_JNA:
	case	C_JA:
	case	C_JS:
	case	C_JNS:
	case	C_JP:
	case	C_JNP:
	case	C_JL:
	case	C_JNL:
	case	C_JLE:
	case	C_JNLE:
	
	case	C_JCASE:
		return true;

	default:
		return false;
	}
}
bool	XCPUCODE::IsJmpNear()
{
	if (this->opcode == C_JMP && this->op[0].mode == OP_Near)
		return true;
	return false;
}

	//	作一次反汇编，pos自动递增，分析结果留xcpu
BYTE	 CDisasm::Disasm_OneCode(ea_t &pos)
{
    st_IDA_OUT idaout;
    DWORD n = this->Disassembler_X(ea2ptr(pos), pos, &idaout);

    pos += n;
	return (BYTE)n;
}
