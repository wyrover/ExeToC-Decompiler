// Copyright(C) 1999-2005 LiuTaoTao，bookaa@rorsoft.com

//	CApiManage.cpp
#include "stdafx.h"
#include "cisc.h"
#include "cexe2c.h"

CApiManage* g_ApiManage = NULL;

class CApiManage_cpp
{
public:
	CApiManage_cpp();
	~CApiManage_cpp(){}
};

CApiManage_cpp self;

CApiManage_cpp::CApiManage_cpp()
{
	g_ApiManage = new CApiManage;   //new_CApiManage
}
//	--------------------------------------------------


bool CApiManage::new_api(ea_t address,int stacksub)
{
	CApi *p = new CApi;     //new_CApi
	p->address = address;
	p->m_stack_purge = stacksub;
	
	sprintf(p->name,"api_%x",address);
    
	this->apilist->AddHead(p);
	return true;
}
CApi*	CApiManage::get_api(ea_t address)
{
//    DWORD ptr = (DWORD)ea2ptr(address);
	POSITION pos = this->apilist->GetHeadPosition();
	while (pos)
	{
		CApi* p = this->apilist->GetNext(pos);
		if (p->address == address)
		{
			return p;
		}
	}
    assert(0);
	return NULL;
}

void CApiManage::New_ImportAPI(PCSTR pstr, DWORD apiaddr)
{
    //注意这时的apiaddr实际上是个ptr而不是ea_t
    //因为这时ea2ptr函数还不能正常工作
    if (!stricmp(pstr, "RegisterClassExA"))
        log_prtl("New_ImportAPI %s 0x%x", pstr, apiaddr);
    

    CFuncType* pf = Get_FuncDefine_from_name(pstr);
	if (pf == NULL)
		return;
	CApi *p = new CApi;     //new_CApi
	p->address = apiaddr;
    assert(pf);
    p->m_functype = pf;
	p->m_stack_purge = pf->get_stack_purge(); //g_FuncDefineMng.API_stack(pstr);
	
	strcpy(p->name, pstr);
    
	this->apilist->AddHead(p);
}
typedef const BYTE* PCBYTE;
PCSTR check_if_jmp_api(PCBYTE phead)
{
	if (*(WORD *)phead != 0x25ff)
		return NULL;
    phead += 2;

	DWORD d = *(DWORD *)phead;

	CApi* papi = g_ApiManage->get_api((ea_t)d);
	if (papi == NULL)
	{
		alert_prtf("error!!! %x", d);
		return NULL;
	}

	PSTR name = papi->name;
	//alert_prtf("I find jmp api %s",name);
	return name;
}

