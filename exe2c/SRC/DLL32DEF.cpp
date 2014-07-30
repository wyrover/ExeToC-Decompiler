// Copyright(C) 1999-2005 LiuTaoTao£¬bookaa@rorsoft.com


//	exe2c project
#include "stdafx.h"
#include "00000.h"
#include "DLL32DEF.h"
#include "strparse.h"

struct ord_st
{
	WORD ord;
	PSTR name;
	ord_st(){name = NULL;}
	~ord_st(){delete name; name = NULL;}
};

typedef CList<ord_st,ord_st &> ORD_LIST;

struct deffile_st
{
	deffile_st* next;
	char fname[20];
	ORD_LIST* list;
};

ORD_LIST* DefName_2_list(PSTR fname);

deffile_st* g_FirstDef = NULL;


void onExit_DLL32DEF()
{
	while (g_FirstDef)
	{
		deffile_st* p = g_FirstDef;
		g_FirstDef = p->next;
		delete p->list;
		delete p;
	}
}
PCSTR GetMyExePath();
extern	char g_mypath[];
CCbuf* ReadDefFile(PSTR fname)
{
	char path[256];
	strcpy(path,GetMyExePath());	//g_mypath);
	strcat(path, "\\def\\");
	strcat(path, fname);
	strcat(path, ".DEF");

	FILE* f = fopen(path,"rb");
	if (f == NULL)
	{
		alert_prtf("Need def\\%s",fname);
		return NULL;
	}

	CCbuf *pInfo = new CCbuf;

	pInfo->LoadFile(f);
	
	fclose(f);

	return pInfo;
}
PSTR DLLDEF_Get_ApiName_from_ord(PSTR pDLLname, WORD ord)
{
	if (strcmp(pDLLname,"MFC42.DLL") == 0)
	{
		if (ord == 0x628)
			nop();
			//return "AfxWinMain";
		//return NULL;
	}
	char fname[80];
	{
		strcpy(fname,pDLLname);
		int len = strlen(fname);
		if (len < 5)
			return NULL;
		if (fname[len-4] == '.')
		{
			fname[len-4] = '\0';
		}
		else
			return NULL;
	}

	ORD_LIST* olist = DefName_2_list(fname);
	if (olist == NULL)
		return NULL;

	POSITION pos = olist->GetHeadPosition();
	while (pos)
	{
		ord_st& p = olist->GetNext(pos);
		if (p.ord == ord)
		{
			assert(strlen(p.name) < 130);
			return p.name;
		}
	}
	return NULL;
}
PSTR * ppit = NULL;
ORD_LIST* DefName_createlist(PSTR fname);
ORD_LIST* DefName_2_list(PSTR fname)
{
	deffile_st* pdef = g_FirstDef;
	while (pdef)
	{
		if (strcmp(pdef->fname,fname) == 0)
			return pdef->list;
		pdef = pdef->next;
	}
	//	not find, lets create one
	return DefName_createlist(fname);
}

void Def_BuildList(ORD_LIST * list, PSTR buf, SIZEOF len);
ORD_LIST* DefName_createlist(PSTR fname)
{
	CCbuf* info = ReadDefFile(fname);

	if (info == NULL)
		return NULL;

	deffile_st* newlist = new deffile_st;
	newlist->next = g_FirstDef;
	g_FirstDef = newlist;

	strcpy(newlist->fname,fname);
	newlist->list = new ORD_LIST;

	PSTR pbuf = info->m_p;
	SIZEOF len = info->m_len;
	delete info;

	Def_BuildList(newlist->list, pbuf, len);
	delete pbuf;
	return newlist->list;
}
void Def_BuildList(ORD_LIST * list, PSTR pbuf, SIZEOF len)
{
	PSTR p = pbuf;
	while (*p == ';')
		p += strlen(p)+1;
    if (memicmp(p,"LIBRARY",7) != 0)
		return;
    p += strlen(p)+1;
	if (memicmp(p,"EXPORTS",7) != 0)
		return;
    p += strlen(p)+1;
    //	now, really
	while (p < pbuf+len)
	{
		char name[256];
		name[255] = '\0';
		get_1part(name,p);
		assert(name[255] == '\0');
		if (*p != '@')
		{
			p += strlen(p)+1;
			continue;
		}
		p++;
		skip_space(p);
		DWORD d = 0;
		sscanf(p,"%d",&d);
		
		ord_st pnew;
		ZeroMemory(&pnew,sizeof(ord_st));
		pnew.ord = (WORD)d;
		if (d == 0x9d0)
			nop();
		pnew.name = new_str(name);
		int llen = strlen(pnew.name);
		assert(llen<130);
		list->AddHead(pnew);
		pnew.name = NULL;	//	
		p += strlen(p)+1;
	}
}
