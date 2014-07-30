// Copyright(C) 1999-2005 LiuTaoTao，bookaa@rorsoft.com

#ifndef proto___H
#define proto___H

#include "../exe2c.h"
#include "enum.h"

typedef	CList<ea_t,ea_t>	EALIST;
//---------------------------------------------
//	unit1.cpp
void	Set_Cur_CFunc(CFunc* pfunc);
void	Redraw_CurFunc();
void	Redraw();
//---------------------------------------------
// assert warn 系列定义

void _stdcall _warn(char * __cond, char * __file, int __line);


#ifdef NDEBUG
#define assert(p)   ((void)0)
#define assert_msg(p,msg)   ((void)0)
#define warn(p)   ((void)0)
#define warn_msg(p,msg)   ((void)0)
#else
//  assert的错误会中止程序，而warn不会
//#define assert(p)   ((p) ? (void)0 : _assert(#p, __FILE__, __LINE__))
#define assert_msg(p,msg)   ((p) ? (void)0 : _assert(msg##" -- "#p, __FILE__, __LINE__))
#define warn(p)   ((p) ? (void)0 : _warn(#p, __FILE__, __LINE__))
#define warn_msg(p,msg)   ((p) ? (void)0 : _warn(msg##" -- "#p, __FILE__, __LINE__))
#endif

//	--------------------------
//	main.cpp


extern	CFunc	*g_Cur_Func;		// 全局保存当前 CFunc

//extern	EXPR_LIST	*g_expr_list;	// 全局变量表


//---------------------------------------------
// pub.cpp
PCSTR	prt_DWORD(DWORD d);
ea_t	Find_Main(ea_t start);

PSTR	new_str(PCSTR p);

int log_prtf(PCSTR fmt,...);
int log_prtl(PCSTR fmt,...);
int		alert_prtf(PCSTR fmt, ...);
void	error(PSTR msg);
void	alert(PSTR msg);


//---------------------------------------------
// Deasm_Init.cpp
void	Disassembler_Init_offset(PBYTE code_buf, ea_t code_offset);
PBYTE	ea2ptr(ea_t pos);
ea_t ptr2ea(void* p);
BYTE	Peek_B(ea_t pos);
WORD	Peek_W(ea_t pos);
DWORD	Peek_D(ea_t pos);


//---------------------------------------------
// CFunc.cpp

void	fill_func_info( ea_t pos,CFunc* pfnc);
bool	IfValideFuncName(PCSTR pname);


PCSTR	hlcode_name(HLType t);
//---------------------------------------------
DWORD	regindex_2_regoff(DWORD regindex);

//---------------------------------------------
//	CFunc_CreateInstrList.cpp
PINSTR	instr_next(INSTR_LIST* list,PINSTR p);
PINSTR	instr_prev(INSTR_LIST* list,PINSTR p);

//---------------------------------------------
//	FileLoad.cpp
bool	IfInWorkSpace(ea_t off);	//	check if off lye in our work space



#endif // proto___H
