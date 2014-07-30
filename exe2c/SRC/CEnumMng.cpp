// Copyright(C) 1999-2005 LiuTaoTao£¬bookaa@rorsoft.com

//	EnumMng.h

#include "stdafx.h"
//#include "cisc.h"
#include "00000.h"
#include "CEnumMng.H"

#include "strparse.h"
#include "SVarType.h"

Enum_mng * g_enum_mng = NULL;

Enum_mng::~Enum_mng()
{
	POSITION pos = m_list->GetHeadPosition();
	while (pos)
	{
		enum_st* p = m_list->GetNext(pos);
		NumStr_st* p1 = p->m_pfirst;
		while (p1)
		{
			NumStr_st* p2 = p1->next;
			delete p1->name;
			delete p1;
			p1 = p2;
		}
		delete p;
	}
	delete m_list;
}
void Enum_mng::Add_New_Enum(enum_st* pnew)
{
	m_list->AddHead(pnew);
}

PSTR enum_st::lookup_itemname(DWORD n)
{
	NumStr_st* p = this->m_pfirst;
	while (p)
	{
		if (p->n == n)
			return p->name;
        p = p->next;
	}
	return NULL;
}
VarTypeID Enum_mng::if_EnumName(PCSTR &pstr)
{
	POSITION pos = this->m_list->GetHeadPosition();
	while (pos)
	{
		enum_st* p = this->m_list->GetNext(pos);
		int n = strlen(p->m_name);
		if (memcmp(p->m_name,pstr,n))
			continue;
		if (if_split_char(pstr[n]))
		{
			pstr += n;
			return g_VarTypeManage->Enum2VarID(p);
		}
	}
	return 0;
}
