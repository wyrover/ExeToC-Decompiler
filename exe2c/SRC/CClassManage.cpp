// Copyright(C) 1999-2005 LiuTaoTao，bookaa@rorsoft.com


#include "stdafx.h"
#include "00000.h"
#include "CClassManage.h"

#include	"hpp.h"
#include	"SVarType.h"
//#include	"../src/CFunc.h"
#include "strparse.h"

Class_st::Class_st()
{
	ZeroMemory(this, sizeof(Class_st));
}

#define SAFE_DELETE(p)\
	if (p != NULL)\
	{\
		delete p;\
		p = NULL;\
	}

Class_st::~Class_st()
{
	SAFE_DELETE(this->m_DataItems);
	for (int i=0;i < m_nSubFuncs;i++)
	{
		SAFE_DELETE(m_SubFuncs[i]);
	}
	SAFE_DELETE(m_SubFuncs);
}

void Class_st::set_subfuncs()
{
	for (int i=0; i<m_nSubFuncs; i++)
	{
		CFuncType *p = m_SubFuncs[i];
		p->m_class = this;
	}
}

BOOL Class_st::IfThisName(PCSTR name)
{
	if (strcmp(this->m_name, name) == 0)
		return TRUE;
	return FALSE;
}
//	----------------------------------

CClassManage* g_ClassManage = NULL;

CClassManage::CClassManage()
{
	this->m_classlist = new CLASS_LIST;
}
CClassManage::~CClassManage()
{
	POSITION pos = this->m_classlist->GetHeadPosition();
	while (pos)
	{
		Class_st* p = m_classlist->GetNext(pos);
		delete p;
	}
	delete this->m_classlist;
	m_classlist = NULL;
}
void CClassManage::add_class(Class_st* pnew)
{
	this->m_classlist->AddTail(pnew);
}

Class_st* CClassManage::LoopUp_class_by_name(PCSTR name)
{
	POSITION pos = this->m_classlist->GetHeadPosition();
	while (pos)
	{
		Class_st* p = this->m_classlist->GetNext(pos);
		if (p->IfThisName(name))
		{
			return p;
		}
	}
	return NULL;
}
CFuncType* CClassManage::Get_SubFuncDefine_from_name(
	PCSTR classname, PCSTR funcname)
{
	Class_st* pclass = this->LoopUp_class_by_name(classname);
	if (pclass == NULL)
		return NULL;

	return pclass->LookUp_SubFunc(funcname);
}


CFuncType* Class_st::LookUp_SubFunc(PCSTR name)
{
	for (int i=0; i<this->m_nSubFuncs; i++)
	{
		CFuncType* p = this->m_SubFuncs[i];
		if (strcmp(p->m_pname,name) == 0)
		{
			return p;
		}
	}
	return NULL;
}
BOOL	Class_st::is_GouZ(CFuncType* pft)
{//是构造
	if (strcmp(pft->m_pname,this->m_name))
		return FALSE;
	return TRUE;
}
BOOL	Class_st::is_GouX(CFuncType* pft)
{//是构析
	if (pft->m_pname[0] == '~')
		return TRUE;
	return FALSE;
}
BOOL	Class_st::is_GouZX(CFuncType* pft)
{//是构造或构析
	return is_GouZ(pft) || is_GouX(pft);
}

/*
void CFunc::ClassSubFuncProcess()
{
	if (m_ftype == NULL)
		return;
	if (m_ftype->m_class == NULL)
		return;

	VarTypeID id = g_VarTypeManage->Class2VarID(m_ftype->m_class);
	id = g_VarTypeManage->GetAddressOfID(id);

	this->m_instrs->Fill_this_ECX(id);
}*/

/*
void	Class_st::prtout(CXmlPrt* prt)
{
	prt->XMLbegin(XT_Keyword, 0);
	if (this->m_Fstruc_Tunion)
		prt->prtt("union");
	else
		prt->prtt("struct");
	prt->XMLend(XT_Keyword);

	prt->XMLbegin(XT_Class, this);
	prt->prtt(this->m_name);
	prt->XMLend(XT_Class);

	prt->prtt("\n");

	prt->XMLbegin(XT_K1, 0);
	prt->prtt("{");
	prt->XMLend(XT_K1);

	prt->prtt("    ");
	
	prt->XMLbegin(XT_Comment, this);
	prt->prtf("//sizeof = 0x%x",this->m_size);
	prt->XMLend(XT_Comment);
	
	prt->prtt("\n");
	
	prt->ident_add1();
	for (int i=0;i<this->m_nDataItem;i++)
	{
		st_Var_Declare* pv = &this->m_DataItems[i];
		if (pv->m_access == nm_sub_end)
			prt->ident_sub1();
		prt->ident();

		if (pv->m_access == nm_substruc)
		{
			prt->XMLbegin(XT_Keyword, 0);
			prt->prtt("struct");
			prt->XMLend(XT_Keyword);

			prt->XMLbegin(XT_K1, 0);
			prt->prtt("{");
			prt->XMLend(XT_K1);
			
			prt->prtt("\n");

			prt->ident_add1();
			continue;
		}
		if (pv->m_access == nm_subunion)
		{
			prt->XMLbegin(XT_Keyword, 0);
			prt->prtt("union");
			prt->XMLend(XT_Keyword);

			prt->XMLbegin(XT_K1, 0);
			prt->prtt("{");
			prt->XMLend(XT_K1);
			
			prt->prtt("\n");

			prt->ident_add1();
			continue;
		}
		if (pv->m_access == nm_sub_end)
		{
			prt->XMLbegin(XT_K1, 0);
			prt->prtt("}");
			prt->XMLend(XT_K1);
			if (pv->m_name[0])
			{
				//any XmlType ?
				prt->prtt(pv->m_name);
			}
			prt->prtt(";\n");
            continue;
		}

		prt->XMLbegin(XT_DataType, 0);
		prt->prtt(GG_VarType_ID2Name(pv->m_vartypeid));
		prt->XMLend(XT_DataType);

		prt->prtt("\t");

		prt->prtt(pv->m_name);
		
		SVarType* pvt = GG_id2_VarType(pv->m_vartypeid);
		if (pvt && pvt->type == vtt_array)
		{
			prt->XMLbegin(XT_K1, 0);
			prt->prtt("[");
			prt->XMLend(XT_K1);

			prt->XMLbegin(XT_Number, 0);
			prt->prtf("%d", pvt->m_array.arraynum);
			prt->XMLend(XT_Number);
			
			prt->XMLbegin(XT_K1, 0);
			prt->prtt("]");
			prt->XMLend(XT_K1);
		}
		prt->prtt(";\t");
		
		prt->XMLbegin(XT_Comment, this);
		prt->prtf("//+%02x",pv->m_offset_in_struc);
		prt->XMLend(XT_Comment);
		
		prt->prtt("\n");

	}
	prt->XMLbegin(XT_K1, 0);
	prt->prtt("}");
	prt->XMLend(XT_K1);
	
	prt->prtt("\n");
	
}*/
void	CClassManage::new_struc(Class_st* pnew)
{
	this->m_classlist->AddHead(pnew);
}



PCSTR	Class_st::getclassitemname(DWORD off)
{
	st_Var_Declare* p = this->GetClassItem(off);
	if (p == NULL)
		return "??a??";
    SVarType* psvt = GG_id2_VarType(p->m_vartypeid);
    if (psvt->type == vtt_array)
    {
        SIZEOF sz = GG_VarType_ID2Size(psvt->m_array.id_arrayitem);
        int n = (off - p->m_offset_in_struc) / sz;
        static char buf[128];
        sprintf(buf,"%s[%d]",p->m_name,n);
        return buf;
    }
	return p->m_name;
}
st_Var_Declare* Class_st::GetClassItem(DWORD off)
{
	assert(this->m_nDataItem < 0x1000);
	for (int i=0; i<this->m_nDataItem; i++)
	{
		st_Var_Declare* p = this->m_DataItems + i;
		if (p->m_offset_in_struc == off)
		{
			return p;
		}
		if (p->m_offset_in_struc <= off
			&& (p->m_offset_in_struc + p->m_size) > off)
		{
			return p;
		}
	}
	return NULL;
}
VarTypeID CClassManage::if_StrucName(PCSTR &pstr)
{
	POSITION pos = this->m_classlist->GetHeadPosition();
	while (pos)
	{
		Class_st* p = this->m_classlist->GetNext(pos);
		int n = strlen(p->getname());
		if (memcmp(p->getname(),pstr,n))
			continue;
		if (if_split_char(pstr[n]))
		{
			pstr += n;
			return g_VarTypeManage->Class2VarID(p);
		}
	}
	return 0;
}

PCSTR	Class_st::getname()
{
	return this->m_name;
}
