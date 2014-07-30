// Copyright(C) 1999-2005 LiuTaoTao，bookaa@rorsoft.com

// EXPR.h
#ifndef EXPR__H
#define EXPR__H
/*
class EXPR;
typedef	EXPR*	PEXPR;

class EXPR
{
public:
	BYTE    type;		// EXPR_???

	BYTE    len;		// var size in BYTE
	BYTE    no1;
	BYTE    f_G;		// 0: local 1: global

	BYTE	fUserDefineName;	//if it already has a user defined name, then we should not optim it
	BYTE	f_part;		// this expr is part of another, AL to EAX
	BYTE	no2;
	BYTE	no3;

	char	str_type[20];	//string of EXPR type, "unsigned long"


	union
	{
		DWORD d;
		struct
		{
			DWORD ESP_off;	//-04 for first push
		} v1;
		struct
		{
			BYTE REG_index;
		} v2;
		struct
		{
			DWORD MEM_off;
		} v3;
		struct
		{
			//BYTE    base_reg;
			//BYTE    index_reg;
			PEXPR   expr_base;
			PEXPR   expr_index;
			DWORD   off;
		} reg_ptr;
	};
	//VALUEE   value;
	char    name[20];

	EXPR();		// 必须用 CFunc::expr_new() 来创建一个 EXPR
	~EXPR();

	PSTR Get_TypeDefStr();	// 返回 EXPR 的定义，如 "unsigned long"
};

typedef	CList<PEXPR,PEXPR>   EXPR_LIST;
*/
enum VARType
{
	v_Invalid = 0,
	v_Immed,    //  立即数
	v_Reg,		//r_
	//v_Stack, 堆栈分正负，分别为参数或内部变量，不会混的，所以分开
	v_Par,		//v_ 参数
	v_Var,		//a_ 变量
	v_Global,	//g_ 全局变量
	v_Tem,		//t_ 临时变量
    v_Volatile, //现在只用于 fs:0
};

struct VAR
{
	VARType	type;	//can be v_Reg,v_Stack,v_Global,v_Immed

	UINT	opsize;	//0:void,1:BYTE,2:WORD,4:DWORD,...
    struct M_t* thevar;
    int part_flag;  //一般为0，如果不为0，表示本var是thevar的一部分
                    //part_flag-1就是本var在thevar中的offset

	union
	{
		DWORD	reg;	//for v_Reg, 0:eax,1:ah,4:ecx....
		DWORD	par_off;	//	for v_Par
		DWORD	var_off;	//  for v_Var
		ea_t	off;	//for v_Global
		BYTE	b;
		WORD	w;
		DWORD	d;		//for v_Immed
		DWORD	temno;	//for v_Tem
	};

    static bool IsSame(VAR* v1,VAR* v2);
    static int	VarCompare(VAR* v1,VAR* v2);
    	//	0:	no relationship
    	//	1:	same
    	//	2:	v1 include v2
    	//	3:	v2 include v1
    VAR()
    {
        thevar = NULL;
        part_flag = 0;
    }
};


DWORD	stack2varoff(signed long stackoff);

#endif // EXPR__H
