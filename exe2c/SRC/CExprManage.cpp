// Copyright(C) 1999-2005 LiuTaoTao，bookaa@rorsoft.com

#include "stdafx.h"
#include	"CISC.H"

	
CExprManage::CExprManage()
{
    vList = new MLIST;
}

CExprManage::~CExprManage()
{
    delete vList;
}


void CExprManage::DeleteUnuse_VarList(MLIST* vlist)
{
    POSITION pos = vlist->GetHeadPosition();
    while (pos)
    {
        POSITION savpos = pos;
        M_t* p = vlist->GetNext(pos);
        if (p->tem_useno == 0)
        {
            vlist->RemoveAt(savpos);
        }
    }
}


DWORD	regindex_2_regoff(DWORD regindex)
{
	//	把reg也批定一个offset，用struct的概念来处理al,ax的问题

	switch (regindex)
	{
	case _EAX_:	return enum_EAX;
	case _ECX_:	return enum_ECX;
	case _EDX_:	return enum_EDX;
	case _EBX_:	return enum_EBX;
	case _ESP_:	return enum_ESP;
	case _EBP_:	return enum_EBP;
	case _ESI_:	return enum_ESI;
	case _EDI_:	return enum_EDI;
	}

	switch (regindex)
	{
	case _AX_:	return enum_AX;
	case _CX_:	return enum_CX;
	case _DX_:	return enum_DX;
	case _BX_:	return enum_BX;
	case _SP_:	return enum_SP;
	case _BP_:	return enum_BP;
	case _SI_:	return enum_SI;
	case _DI_:	return enum_DI;
	}

	switch (regindex)
	{
	case _AH_:	return enum_AH;
	case _CH_:	return enum_CH;
	case _DH_:	return enum_DH;
	case _BH_:	return enum_BH;
	
	case _AL_:	return enum_AL;
	case _CL_:	return enum_CL;
	case _DL_:	return enum_DL;
	case _BL_:	return enum_BL;
	}

	return regindex;
}

PCSTR RegName(DWORD off, BYTE opsize)
{
	static char s[20];
	switch (opsize)
	{
	case 4:
		switch (off)
		{
		case enum_EAX:	return("EAX");	
		case enum_ECX:	return("ECX");	
		case enum_EBX:	return("EBX");	
		case enum_EDX:	return("EDX");	
		case enum_EBP:	return("EBP");	
		case enum_ESP:	return("ESP");	
		case enum_ESI:	return("ESI");	
		case enum_EDI:	return("EDI");	
		}
		break;
	case 2:
		switch (off)
		{
		case enum_AX:	return("AX");	
		case enum_CX:	return("CX");	
		case enum_BX:	return("BX");	
		case enum_DX:	return("DX");	
		case enum_BP:	return("BP");	
		case enum_SP:	return("SP");	
		case enum_SI:	return("SI");	
		case enum_DI:	return("DI");	
		}
		break;
	case 1:
		switch (off)
		{
		case enum_AH:	return("AH");	
		case enum_CH:	return("CH");	
		case enum_BH:	return("BH");	
		case enum_DH:	return("DH");	
		
		case enum_AL:	return("AL");	
		case enum_CL:	return("CL");	
		case enum_BL:	return("BL");	
		case enum_DL:	return("DL");	
		}
		break;
	}
	sprintf(s,"r_%x_%x", opsize, off);
	return s;
}
bool M_t::AnyOverlay(M_t* p)
{
    DWORD d = p->s_off;
    {
        if (d >= this->s_off && d < this->end_off())
            return true;
    }
    d = p->end_off();
    {
        if (d > this->s_off && d < this->end_off())
            return true;
    }
    return false;
}
void M_t::Expand(M_t* p)
{
    if (this->s_off > p->s_off)
    {
        this->size += this->s_off - p->s_off;
        this->s_off = p->s_off;
    }
    if (this->end_off() < p->end_off())
    {
        this->size += p->end_off() - this->end_off();
    }
    this->m_DataTypeID = g_VarTypeManage->NewSimpleVarType(this->size);
}


PCSTR CExprManage::BareVarName(VAR* v)
{
    if (v->type == v_Tem)
    {//就是说，不替换
        PCSTR retn = v->thevar->GetName();
        IsBadReadPtr(retn,1);
        return retn;
    }
    PCSTR retn = VarName(v);
    IsBadReadPtr(retn,1);
    return retn;
}

M_t* CExprManage::GetVarByName_1(MLIST* list, PCSTR varname)
//SuperC_func: 只在＜CExprManage::GetVarByName＞中使用
{
	POSITION pos = list->GetHeadPosition();
	while (pos)
	{
		M_t* p = list->GetNext(pos);

        if (strcmp(varname, p->namestr) == 0)
            return p;
	}
    return NULL;
}
M_t* CExprManage::GetVarByName(PCSTR varname)
//当前，仅支持par,var,reg三种类型
{
    return this->GetVarByName_1(this->vList, varname);
}
PCSTR GetBeautyImmedValue(DWORD n)
{
    static char s[80];
    if (n < 16)
        sprintf(s,"%d",n);
    else if (n < 100 && (n % 10) == 0)
        sprintf(s,"%d", n);
    else if (n >= 100 && (n % 100) == 0)
        sprintf(s,"%d", n);
    else
        sprintf(s,"0x%x", n);
    return s;
}


void Cstr_fmt(PSTR dst, PCSTR src)
{
	int n = 0;
	dst[n++] = '\"';

	char c;
	while ((c = *src++) != '\0')
	{
		switch (c)
		{
		case '\n':
			dst[n++] = '\\';
			dst[n++] = 'n';
			break;
		case '\t':
			dst[n++] = '\\';
			dst[n++] = 't';
			break;
		default:
			dst[n++] = c;
			break;
		}
		if (n > 240)
		{
			dst[n++] = '.';
			dst[n++] = '.';
			dst[n++] = '.';
			break;
		}
	}
	dst[n++] = '\"';
	dst[n] = '\0';
}

void 	CExprManage::prt_var_Immed(VAR* v, CXmlOutPro* out)
{
    if (v->thevar == NULL || g_VarTypeManage->is_simple(v->thevar->m_DataTypeID))
    {
        out->XMLbegin(XT_Number, NULL);
        out->prtt(GetBeautyImmedValue(v->d));
        out->XMLend(XT_Number);
        return;
    }
    VarTypeID id1 = v->thevar->m_DataTypeID;
    assert(id1 != 0);
    static char buf[180];

    VarTypeID id_p = g_VarTypeManage->GetPointTo(id1);
    if ( id_p != 0 && g_VarTypeManage->If_Based_on_idid(id_p,id_char))
    {
        static char strbuf[180];
        if ( ! if_valid_ea((ea_t)v->d))	//	奇怪
        {
            //sprintf(strbuf,"(WHY_PSTR)0x%x",v->d);
            //return strbuf;
            out->prtt("(");
            out->XMLbegin(XT_DataType, (PVOID)id1);
            out->prtt(GG_VarType_ID2Name(id1));
            out->XMLend(XT_DataType);
            out->nospace();
            out->prtt(")");
            out->XMLbegin(XT_Number, NULL);
            out->prtf("0x%x", v->d);
            out->XMLend(XT_Number);
            return;
        }
        PCSTR pstr = (PCSTR)ea2ptr((ea_t)v->d);
        Cstr_fmt(strbuf,pstr);
        //return strbuf;
        out->XMLbegin(XT_Number, NULL);
        out->prtt(strbuf);
        out->XMLend(XT_Number);
        return;
    }

    out->prtt("(");
    out->XMLbegin(XT_DataType, (PVOID)id1);
    out->prtt(GG_VarType_ID2Name(id1));
    out->XMLend(XT_DataType);
    out->nospace();
    out->prtt(")");

    out->XMLbegin(XT_Number, NULL);
    //sprintf(buf,"(%s)", GG_VarType_ID2Name(v->thevar->m_DataTypeID));
    if (v->thevar->immed.d == 0 && g_VarTypeManage->GetPointTo(v->thevar->m_DataTypeID) != 0)
    {
        out->prtt("NULL");
    }
    else
        out->prtt(GetBeautyImmedValue(v->d));
    
    out->XMLend(XT_Number);
}
PCSTR CExprManage::VarName_Immed(VAR* v)
{
    if (v->thevar == NULL || g_VarTypeManage->is_simple(v->thevar->m_DataTypeID))
        return GetBeautyImmedValue(v->d);
    VarTypeID id1 = v->thevar->m_DataTypeID;
    assert(id1 != 0);
    static char buf[180];

    VarTypeID id_p = g_VarTypeManage->GetPointTo(id1);
    if ( id_p != 0 && g_VarTypeManage->If_Based_on_idid(id_p,id_char))
    {
        static char strbuf[180];
        if ( ! if_valid_ea((ea_t)v->d))	//	奇怪
        {
            sprintf(strbuf,"(WHY_PSTR)0x%x",v->d);
            return strbuf;
        }
        PCSTR pstr = (PCSTR)ea2ptr((ea_t)v->d);
        Cstr_fmt(strbuf,pstr);
        return strbuf;
    }

    sprintf(buf,"(%s)", GG_VarType_ID2Name(v->thevar->m_DataTypeID));
    if (v->thevar->immed.d == 0 && g_VarTypeManage->GetPointTo(v->thevar->m_DataTypeID) != 0)
    {
        strcat(buf, "NULL");
    }
    else
        strcat(buf, GetBeautyImmedValue(v->d));
    return buf;
}
PCSTR CExprManage::VarName(VAR* v)
{
    assert(v->type != v_Tem);

	static char s[20];
	M_t* p;
	switch (v->type)
	{
	case v_Global:
	case v_Reg:
	case v_Var:
	case v_Par:
		//p = this->LookUpVar(v);
        p = v->thevar;
		if (p == NULL)
			return "WHAT";
		assert(p);
        if (p->size == v->opsize)
		{
			if (p->m_DataTypeID != 0)
			{
				UINT typesize = ::GG_VarType_ID2Size(p->m_DataTypeID);
				if (typesize == p->size)
					nop();
			}
            return p->namestr;
		}
        if (v->part_flag != 0 && g_VarTypeManage->is_class(p->m_DataTypeID) != NULL)
        {
            static char buf[180];
            sprintf(buf, "%s.%s", p->namestr, 
                    g_VarTypeManage->is_class(p->m_DataTypeID)->getclassitemname(v->part_flag - 1));
            return buf;
        }
        else
        {
            static char buf[180];
            sprintf(buf, "%s.part", p->namestr);
            return buf;
        }
    case v_Immed:
        return VarName_Immed(v);
    case v_Volatile:
        return "FS:[00]";
	default:
		sprintf(s,"?%d?",v->type);
		return s;
	}
}


void 	CExprManage::prt_var(VAR* v, CXmlOutPro* out)
{
    if (v->type == v_Immed)
    {
        prt_var_Immed(v, out);
        return;
    }
    out->XMLbegin(XT_Symbol, v->thevar);
    out->prtt(VarName(v));
    out->XMLend(XT_Symbol);
}
void CExprManage::prt_var_declares(CXmlOutPro* out)
{
	MLIST* list = this->vList;
	POSITION pos = list->GetHeadPosition();
	while (pos)
	{
		M_t* p = list->GetNext(pos);
        if (p->type != MTT_reg)
            continue;

        out->prtspace(4);
        
        out->XMLbegin(XT_DataType, p);
        out->prtt(GG_VarType_ID2Name(p->m_DataTypeID));
        out->XMLend(XT_DataType);
        
        out->XMLbegin(XT_Symbol, p);
        out->prtt(p->namestr);
        out->XMLend(XT_Symbol);
        
        if (GG_id2_VarType(p->m_DataTypeID)->type == vtt_array)
        {
            out->prtt("[");
            out->prtf("%d", GG_id2_VarType(p->m_DataTypeID)->m_array.arraynum);
            out->prtt("]");
        }
		out->prtt(";");
        out->endline();
	}
	
	pos = list->GetHeadPosition();
	while (pos)
	{
		M_t* p = list->GetNext(pos);
        if (p->type != MTT_var)
            continue;
        if (p->bTem)
            continue;

        out->prtspace(4);
        
        out->XMLbegin(XT_DataType, p);
        out->prtt(GG_VarType_ID2Name(p->m_DataTypeID));
        out->XMLend(XT_DataType);
		
        out->prtspace();
        out->XMLbegin(XT_Symbol, p);
        out->prtt(p->namestr);
        out->XMLend(XT_Symbol);
        if (GG_id2_VarType(p->m_DataTypeID)->type == vtt_array)
        {
            out->prtt("[");
            out->prtf("%d", GG_id2_VarType(p->m_DataTypeID)->m_array.arraynum);
            out->prtt("]");
        }
		out->prtt(";");
        out->endline();

	}
}
void CExprManage::prt_parameters(CXmlOutPro* out)
{
	bool first = true;
	
    assert(this);
	MLIST* list = this->vList;
    assert(list);
	POSITION pos = list->GetHeadPosition();
	while (pos)
	{
		M_t* p = list->GetNext(pos);
        if (p->type != MTT_par)
            continue;
        
		if (first)
			first = false;
		else
        {
            out->nospace();
			out->prtt(", ");
        }

        out->XMLbegin(XT_DataType, (PVOID)p->m_DataTypeID);
        out->prtt(GG_VarType_ID2Name(p->m_DataTypeID));
        out->XMLend(XT_DataType);

        out->XMLbegin(XT_Symbol, p);
        out->prtt(p->namestr);
        out->XMLend(XT_Symbol);
	}
}

M_t* CExprManage::AddRef_immed(DWORD d, DWORD size)
{
	M_t* pnew = new M_t;    //new_M_t
    pnew->type = MTT_immed;
    pnew->immed.d = d;
    pnew->size = size;
    pnew->m_DataTypeID = g_VarTypeManage->NewSimpleVarType(pnew->size);

    vList->AddTail(pnew);

    return pnew;
}
M_t* CExprManage::AddRef_tem(DWORD temno, DWORD size)
{
    POSITION pos = vList->GetHeadPosition();
    while (pos)
    {
        M_t* p = vList->GetNext(pos);
        if (p->type == MTT_tem && p->tem.temno == temno)
        {
            return p;
        }
    }
    //没找到，就new一个
	M_t* pnew = new M_t;    //new_M_t
    pnew->type = MTT_tem;
    pnew->tem.temno = temno;
    sprintf(pnew->namestr, "t_%x", temno);
    pnew->size = size;
    pnew->m_DataTypeID = g_VarTypeManage->NewSimpleVarType(pnew->size);

    vList->AddTail(pnew);

    return pnew;
}
void Replace_Var(INSTR_LIST* instr_list, M_t* pvar, M_t* thevar);
M_t* CExprManage::AddRef_with_name(en_MTTYPE type, DWORD off, DWORD size, PCSTR tj_name)
//SuperC_func: 只在＜CExprManage::AddRef＞中使用
{
    assert(type != MTT_tem);


    {//先找一找是不是已经有了
        POSITION pos = vList->GetHeadPosition();
        while (pos)
        {
            M_t* p = vList->GetNext(pos);
            if (p->type == type && p->s_off == off && p->size == size)
            {
                if (!p->iThrowned)
                    return p;
            }
        }
    }

	M_t* pnew = new M_t;    //new_M_t
    pnew->type = type;
	pnew->s_off = off;
    pnew->size = size;
    pnew->m_DataTypeID = g_VarTypeManage->NewSimpleVarType(pnew->size);

    vList->AddTail(pnew);

    this->Enlarge_Var(pnew, ::g_Cur_Func->m_instr_list);

    strcpy(pnew->namestr, tj_name);

    return pnew;
}

signed int varoff2stack(UINT off);
void CExprManage::EspReport(signed int esplevel)
{
    static int static_iThrown = 1;
    static_iThrown++;

    POSITION pos = vList->GetHeadPosition();
    while (pos)
    {
        M_t* p = vList->GetNext(pos);
        if (p->type != MTT_var)
            continue;
        
        if (esplevel > varoff2stack(p->s_off))
        {
            p->iThrowned = static_iThrown;    //扔掉
        }
    }
}

    
M_t* CExprManage::SearchMT(en_MTTYPE type, DWORD off)
{
	POSITION pos = vList->GetHeadPosition();
	while (pos)
	{
		M_t* p = vList->GetNext(pos);
        if (p->type == type && p->s_off == off)
            return p;
    }
    return NULL;
}

CExprManage g_GlobalExpr;

void CExprManage::AddRef(VAR* pvar)
{	//	告诉一声CExprManage，这个var 有人用
    // 确保所有var都会产生一个thevar
	switch (pvar->type)
	{
	case v_Invalid: return;
    case v_Immed: 
        if (pvar->d == 4)
        {
            pvar->d = 4;
        }
        pvar->thevar = this->AddRef_immed(pvar->d, pvar->opsize);
        return;
    case v_Global:
        {
            char name[20];
    		sprintf(name,"g_%x",pvar->off);
            pvar->thevar = g_GlobalExpr.AddRef_with_name(MTT_global, pvar->off, pvar->opsize, name);
            return;
        }
    case v_Volatile:
    case v_Tem: 
        {
            pvar->thevar = this->AddRef_tem(pvar->temno, pvar->opsize);
            pvar->thevar->bTem = true;
            return;		
        }
    case v_Var:
        {
            this->m_VarRange_H;
            this->m_VarRange_L;
            char name[20];
            if (0x7ffff - (signed int)pvar->var_off + 1 > -this->m_VarRange_L)
            {
                sprintf(name,"tem_%x",0x7ffff - pvar->var_off + 1);	//0x7ffff - p->s_off + 1
                pvar->thevar = this->AddRef_with_name(MTT_var, pvar->var_off, pvar->opsize, name);
                //pvar->thevar = this->CreateNewTemVar(pvar->opsize);
                pvar->thevar->bTem = true;
            }
            else
            {
                sprintf(name,"v_%x",0x7ffff - pvar->var_off + 1);	//0x7ffff - p->s_off + 1
                pvar->thevar = this->AddRef_with_name(MTT_var, pvar->var_off, pvar->opsize, name);
            }
        }
        break;
    case v_Par:
        {
            char name[20];
    		sprintf(name,"a_%x",pvar->par_off);
            pvar->thevar = this->AddRef_with_name(MTT_par, pvar->par_off, pvar->opsize, name);
        }
        break;
    case v_Reg:
        {
            PCSTR pname = RegName(pvar->reg, pvar->opsize);
            pvar->thevar = this->AddRef_with_name(MTT_reg, pvar->reg, pvar->opsize, pname);
        }
        break;
    default:
        assert(0);
    }
}
DWORD	stack2varoff(signed long stackoff)
{
	assert(stackoff < 0);
	DWORD off = (DWORD)stackoff;		//	BYTE 转为 DWORD
	off &= 0x7ffff;				//	够了吧?
	return off;
}
signed int varoff2stack(UINT off)
{
    return -(0x7ffff - (signed int)off + 1);
}

    
int g_newtemno = 737;
    //每次使用都加2，这样就把偶数的值留出来了

M_t* CExprManage::CreateNewTemVar(UINT size)
{
    M_t* pnew = new M_t;
    pnew->type = MTT_tem;
    pnew->size = size;

    pnew->tem.temno = g_newtemno;
    g_newtemno += 2;
    sprintf(pnew->namestr, "tem_%x", pnew->tem.temno);
    pnew->m_DataTypeID = g_VarTypeManage->NewSimpleVarType(pnew->size);

    vList->AddTail(pnew);
    return pnew;
}

void Replace_Var_1(VAR* var, M_t* pvar, M_t* thevar)
{
    if (var->thevar != pvar)
        return;
        
    var->thevar = thevar;
    if (var->opsize != thevar->size)
    {
        switch (var->type)
        {
        case v_Var:
            var->part_flag = 1+var->var_off-thevar->s_off;
            break;
        default:
            var->part_flag = 1;
            break;
        }
    }
}
void Replace_Var(INSTR_LIST* instr_list, M_t* pvar, M_t* thevar)
{
	assert(instr_list != NULL);
    POSITION pos = instr_list->GetHeadPosition();
    while (pos)
    {
        PINSTR p = instr_list->GetNext(pos);
        Replace_Var_1(&p->var_w,pvar,thevar);
        Replace_Var_1(&p->var_r1,pvar,thevar);
        Replace_Var_1(&p->var_r2,pvar,thevar);
    }
}
void CExprManage::Enlarge_Var(M_t* thevar, INSTR_LIST* instr_list)
{
    //下面，要删被我占了的var

	assert(instr_list != NULL);
    MLIST*	list = vList;
    POSITION pos = list->GetHeadPosition();
    while (pos)
    {
        POSITION savpos = pos;
        M_t* p = list->GetNext(pos);
        if (p == thevar)
        {
            Replace_Var(instr_list, p, thevar); //replace myself
            continue;
        }
        if (p->type != thevar->type)
            continue;
        if (p->iThrowned != 0 && p->iThrowned != thevar->iThrowned)
            continue;
        
        if (thevar->IfInclude(p->s_off) 
            && thevar->IfInclude(p->s_off + p->size))
        {
            list->RemoveAt(savpos);
            //仅仅删掉是不行的，还要更新instrlist

            Replace_Var(instr_list, p, thevar);
        }
    }
}

void CExprManage::ClearUse()
{
    POSITION pos = vList->GetHeadPosition();
    while (pos)
    {
        M_t* p = vList->GetNext(pos);
        p->tem_useno = 0;
    }
}

