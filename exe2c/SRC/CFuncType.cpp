// Copyright(C) 1999-2005 LiuTaoTao，bookaa@rorsoft.com


#include "stdafx.h"
#include "00000.h"
#include "CFuncType.h"
#include "SVarType.h"

#define SAFE_DELETE(p)\
	if (p != NULL)\
	{\
		delete p;\
		p = NULL;\
	}

CFuncType::CFuncType()
{
    ZeroMemory(this, sizeof(CFuncType));
}
CFuncType::~CFuncType()
{
	SAFE_DELETE(this->m_pname);
	SAFE_DELETE(this->m_internal_name);
	SAFE_DELETE(this->m_partypes);
	
	if (this->m_parnames)
	{
		for (int i=0;i<this->m_args;i++)
		{
			SAFE_DELETE(m_parnames[i]);
		}
		SAFE_DELETE(this->m_parnames);
	}
}

CFuncType* CFuncType::ft_clone()
{	//	把当前信息复制一份
	CFuncType* pnew = new CFuncType;
	*pnew = *this;

	if ( m_pname )
		pnew->m_pname = new_str(m_pname);
	else
		pnew->m_pname = NULL;
	pnew->m_internal_name = new_str(this->m_internal_name);
	
	pnew->m_partypes = new VarTypeID[this->m_args];
	memcpy(pnew->m_partypes, this->m_partypes,
		   sizeof(VarTypeID) * this->m_args);
	
	if (this->m_args)
	{
		pnew->m_parnames = new PSTR[this->m_args];
		memcpy(pnew->m_parnames, this->m_parnames,
			   sizeof(PSTR) * this->m_args);
		for (int i=0;i<m_args;i++)
		{
			PSTR pstr = m_parnames[i];
			if (pstr)
				pnew->m_parnames[i] = new_str(pstr);
		}
	}
	
	return pnew;
}

void CFuncType::create_internal_funcname()
{
	if (this->m_internal_name)
		return;

	char buf[80];
	if (this->m_extern_c)
	{
		buf[0] = '_';
		buf[1] = '\0';
		strcat(buf,this->m_pname);
		this->m_internal_name = new_str(buf);
		return;
	}

	if (this->m_callc == enum_stdcall)
	{	//	stdcall 也简单
		sprintf(buf,"%s@%d",this->m_pname,this->m_args * 4);
		this->m_internal_name = new_str(buf);
		return;
	}
	else if (this->m_callc == enum_fastcall)
	{	//	不知道怎么变，随便吧
		sprintf(buf,"%s@@%d",this->m_pname,this->m_args * 4);
		this->m_internal_name = new_str(buf);
		return;
	}
	else if (this->m_callc == enum_cdecl)
	{
		sprintf(buf,"%s@%d",this->m_pname,this->m_args * 4);
		this->m_internal_name = new_str(buf);
		return;
	}

	assert(("I do not know how to convert it to internal funcname",0));
}

    
VarTypeID CFuncType::SearchPara(UINT off)
{
    UINT retn = 0;
    for (int i=0; i<m_args; i++)
    {
        if (retn == off)
            return m_partypes[i];
        
        retn += GG_VarType_ID2Size(m_partypes[i]);
    }
    return 0;
}
UINT CFuncType::para_total_size()
{
    UINT retn = 0;
    for (int i=0; i<m_args; i++)
    {
        retn += GG_VarType_ID2Size(m_partypes[i]);
    }
    return retn;
}

BYTE CFuncType::get_stack_purge()
{
	//	根据m_ftype，算出 m_stack_purge
	if (m_varpar)
	{
		assert(m_callc == enum_cdecl);	//	似乎只有__cdecl才会变参
        return 0;	//	变参数肯定是不改堆栈的
	}
	switch (m_callc)
	{
	case enum_cdecl:
		return 0;

	case enum_fastcall:
		if (m_args <= 2)
			return 0;
		return (m_args-2) * 4;

	case enum_stdcall:
		return m_args * 4;

	default:
		assert(0);
		return 0;
	}

}
