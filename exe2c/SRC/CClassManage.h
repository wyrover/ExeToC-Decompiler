// Copyright(C) 1999-2005 LiuTaoTao，bookaa@rorsoft.com


#ifndef CClassManage_H
#define CClassManage_H

typedef DWORD ea_t;

//#include "../CXmlPrt/CXmlPrt.h"
#include "CFuncType.h"

enum enumClassMemberAccess
{
	nm_unknown	=	0,
	nm_private,
	nm_protected,
	nm_public,
	
	nm_substruc,
	nm_subunion,
	nm_sub_end,
};

struct st_Var_Declare
{	//	是对一个量的定义，包括数据类型和变量名
	//	可用于struct_struct中的item定义，和functoin parameter的定义等等
	VarTypeID	m_vartypeid;
	SIZEOF		m_size;
	DWORD		m_offset_in_struc;
	char		m_name[80];
	enumClassMemberAccess	m_access;	//	为class预留
};

//	----------------------------------------------------
//	class

class Class_st
{
public:
	BOOL	m_TclassFstruc;	//	TRUE means class, FALSE means struct
	char	m_name[80];		//	class名
	SIZEOF	m_size;			//	class的size,数据部分
	int		m_nDataItem;	//	数据量的个数
	st_Var_Declare* m_DataItems;	//	sizeof = m_nDataItem 的一个buffer
	BOOL	m_Fstruc_Tunion;	//TRUE = union

	ea_t	m_Vftbl;		//	虚表的地址，如果有的话
	int		m_nSubFuncs;		//	子函数的个数
	CFuncType**		m_SubFuncs;	//	各个子函数

public:
	Class_st();
	~Class_st();

	CFuncType* LookUp_SubFunc(PCSTR name);
	BOOL	is_GouZ(CFuncType* pft);        //是构造
	BOOL	is_GouX(CFuncType* pft);        //是构析
	BOOL	is_GouZX(CFuncType* pft);       //是构造或构析
	PCSTR	getclassitemname(DWORD off);
	st_Var_Declare* GetClassItem(DWORD off);
//	void	prtout(CXmlPrt* prt);
	void	set_subfuncs();
	BOOL	IfThisName(PCSTR name);
	PCSTR	getname();
};

typedef	CList<Class_st *, Class_st *> CLASS_LIST;

class CClassManage
{
	CLASS_LIST*	m_classlist;
public:

	CClassManage();
	~CClassManage();

	CFuncType* Get_SubFuncDefine_from_name(PCSTR classname, PCSTR funcname);
	void add_class(Class_st* pnew);
	Class_st* LoopUp_class_by_name(PCSTR name);
	
	VarTypeID if_StrucName(PCSTR &p);
	void	new_struc(Class_st* pnew);
};


extern	CClassManage* g_ClassManage;

#endif	//	CClassManage_H
