// Copyright(C) 1999-2005 LiuTaoTao，bookaa@rorsoft.com

#ifndef	CFuncType_H
#define CFuncType_H

enum enum_CallC
{	//	0 for invalid or unknown
	enum_unknown=	0,
	enum_cdecl	=	1,
	enum_stdcall,
	enum_pascal,
	enum_fastcall,
};	//	calling convention

enum_CallC if_CallC(PSTR p);

class CFuncType
{
public:
	enum_CallC	m_callc;
	VarTypeID	m_retdatatype_id;	//	返回值的数据类型
	BOOL		m_extern_c;
	BOOL		m_varpar;			//	为TRUE表明它参数可变
	int			m_args;				//	参数个数。如果m_varpar==TRUE，则这是最少个数
									//	not include last "..."
	VarTypeID*	m_partypes;			//	指向一个m_args大小的数组，是各个参数的数据类型
									//	VarTypeID[m_args] *
	PSTR*		m_parnames;			//	指向一个m_args大小的数组，是各个参数的name,比如argc,argv
									//	PSTR[m_args] *
	PSTR		m_pname;
	PSTR		m_internal_name;	//can be "_printf", "printf$CRS"
	class Class_st*	m_class;			//	if not null, means this func is a subfunc of this class

	CFuncType();
	~CFuncType();

	void create_internal_funcname();
	CFuncType* ft_clone();

	BYTE get_stack_purge();
    UINT para_total_size();
    VarTypeID SearchPara(UINT off);
};
    

typedef CList<CFuncType*,CFuncType*> FuncTypeList;


void func_1(CFuncType* pfunc,PSTR p);
void func_define_2(CFuncType* pfunc,PCSTR &p);


//	--------------------------------------------------------

CFuncType* Get_FuncDefine_from_internal_name(PCSTR pmyinternalname);
CFuncType* Get_FuncDefine_from_name(PCSTR pmyinternalname);
//	对库函数，是用internal_name，对api，则是用func_name


#endif	//	CFuncType_H
