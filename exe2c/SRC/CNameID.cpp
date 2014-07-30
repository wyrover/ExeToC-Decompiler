// Copyright(C) 1999-2005 LiuTaoTao，bookaa@rorsoft.com

#include "stdafx.h"
#include	"CISC.H"


CNameMng::CNameMng()
{
	list = new CNameList;
}
CNameMng::~CNameMng()
{
	list->RemoveAll();
	delete list;
}
PCSTR CNameMng::id2name(H_NAMEID id)
{
	POSITION pos = list->GetHeadPosition();
	while (pos)
	{
		st_NameID* p = list->GetNext(pos);
		if (p->id == id)
			return p->name;
	}
	return NULL;
}
H_NAMEID CNameMng::savname(PCSTR name)
{
    H_NAMEID h = this->LookupName(name);
    if (h != 0)
        return h;   //不要重复存

	st_NameID* p = new st_NameID;
	p->name = new_str(name);
	p->id = (H_NAMEID)p->name;	//	不管怎样，这也是唯一的

	list->AddTail(p);

	return p->id;
}
H_NAMEID CNameMng::LookupName(PCSTR name)
{
	POSITION pos = list->GetHeadPosition();
	while (pos)
	{
		st_NameID* p = list->GetNext(pos);
		if (!strcmp(name, p->name))
		{
			return p->id;
		}
	}
	return 0;
}
void CNameMng::Rename(H_NAMEID h, PCSTR newname)
{
	POSITION pos = list->GetHeadPosition();
	while (pos)
	{
		st_NameID* p = list->GetNext(pos);
		if (p->id == h)
        {
            strcpy(p->name, newname);
            return;
        }
	}
}
