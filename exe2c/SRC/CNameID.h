// Copyright(C) 1999-2005 LiuTaoTao£¬bookaa@rorsoft.com

#ifndef NameID__H
#define NameID__H

struct st_NameID
{
	H_NAMEID id;
	PSTR name;
};

typedef CList<st_NameID*,st_NameID*> CNameList;

class CNameMng
{
private:
	CNameList* list;
public:
	CNameMng();
	~CNameMng();
	PCSTR id2name(H_NAMEID id);
	H_NAMEID savname(PCSTR name);
	H_NAMEID LookupName(PCSTR name);
    void Rename(H_NAMEID h, PCSTR newname);
};

#endif // NameID__H
