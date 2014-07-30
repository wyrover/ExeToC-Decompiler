// Copyright(C) 1999-2005 LiuTaoTao£¬bookaa@rorsoft.com

//	exe2c project
//	EnumMng.h
#ifndef	CEnumMng_H
#define CEnumMng_H

typedef DWORD	VarTypeID;

struct NumStr_st
{
	NumStr_st* next;
	DWORD	n;
	PSTR	name;
};

struct enum_st
{
	char	m_name[80];		//	enum Ãû
	NumStr_st*	m_pfirst;
	PSTR lookup_itemname(DWORD n);
};
typedef CList<enum_st*,enum_st*> Enum_List;

class Enum_mng
{
public:
	Enum_List *	m_list;
	Enum_mng(){	m_list = new Enum_List;}
	~Enum_mng();

	void Add_New_Enum(enum_st * pnew);
	VarTypeID if_EnumName(PCSTR &pstr);
};


extern Enum_mng* g_enum_mng;

#endif	//	CEnumMng_H
