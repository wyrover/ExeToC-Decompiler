///////////////////////////////////////////////////////////////
//
// Cexe2c.cpp
// Copyright(C) 1999-2005 LiuTaoTao，bookaa@rorsoft.com
// Created at 2005.2.1
// Description:	The main cpp file of the component
// History:		
//
///////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Cexe2c.h"
#include "CFuncStep1.h"
#include "DataType.h"
#include "ParseHead.h"
#include "..\LibScanner.H"


KS_DECLARE_COMPONENT(exe2c, EXE2C)


Cexe2c* g_Cexe2c = NULL;

I_LIBSCANNER* g_LIBSCANNER = NULL;

BOOL hpp_init();
void lib_init();
void lib_exit();
void CExprManage_cpp_Init();

bool __stdcall exe2c_Init()
{
	CExprManage_cpp_Init();
    hpp_init();
	return true;
}


void __stdcall exe2c_Exit()
{
    lib_exit();
}

class CSelfInit
{
public:
    CSelfInit()
    {
        exe2c_Init();
    }
    ~CSelfInit()
    {
        exe2c_Exit();
    }
};
CSelfInit self;


bool __stdcall Cexe2c::BaseInit()
{
	//KICK_MFC();
    m_E2COut = NULL;
    g_Cexe2c = this;

    this->m_api_name_manager = new CNameMng;    //new_CNameMng

	// 作一些全局初始化
	if (m_func_list == NULL)
		m_func_list = new FUNC_LIST;    //new_FUNC_LIST

    m_FileLoader = NULL;


	return true;
}


Cexe2c::~Cexe2c()
{
	//KICK_MFC();
    g_Cexe2c = NULL;
    delete this->m_api_name_manager;
    this->m_api_name_manager = NULL;

    delete m_func_list;
    m_func_list = NULL;

    delete m_FileLoader;
    m_FileLoader = NULL;
}


bool __stdcall Cexe2c::test()
{
	//KICK_MFC();
	return true;
}


void	Cexe2c::Recurse_Analysis()
{
	POSITION pos = m_func_list->GetHeadPosition();
    while (pos != NULL)
    {
        CFunc* p = m_func_list->GetNext(pos);
		
		log_prtl("Recurse_analysis %x",p->m_head_off);

		if (p->m_nStep != STEP_100)
			continue;

		p->analysis();
    }
}

void	Cexe2c::Recurse_Optim()
{
	POSITION pos = m_func_list->GetHeadPosition();
    while (pos != NULL)
    {
        CFunc* p = m_func_list->GetNext(pos);
		
		log_prtl("Recurse_Optim %x",p->m_head_off);

		if (p->m_nStep < STEP_6)
			continue;
    }
}
void __stdcall Cexe2c::exe2c_main(PCSTR fname)
{
    lib_init();
	//MessageBox(0,fname,"file open",0);

    //	文件调入
    if (m_FileLoader != NULL)
    	delete m_FileLoader;
	m_FileLoader = new FileLoader;  //new_FileLoader
	bool f = m_FileLoader->load(fname);
    if (!f)
    {
    	alert_prtf("File %s load error",fname);
        return;
    }


    PBYTE entry_buf;
    ea_t entry_offset;
    m_FileLoader->GetEntrance(entry_buf, entry_offset);

	// 因为文件的调入地址与虚拟地址不同，所以要记住这个差值
    // 以后主程序只以offset来访问，不管实际buffer
    Disassembler_Init_offset(entry_buf, entry_offset);

	//	开始分析
    this->do_exe2c(entry_offset);
}


CFunc*	Cexe2c::FindFuncByName(PCSTR pname)
{
	if (m_func_list == NULL)
    	return NULL;
	POSITION pos = m_func_list->GetHeadPosition();
    while (pos != NULL)
    {
        CFunc* p = m_func_list->GetNext(pos);
        if (stricmp(p->m_funcname,pname) == 0)
            return p;
    }
    return NULL;
}

	//	开始分析
void	Cexe2c::do_exe2c(ea_t start)
{
    ea_t pmain = Find_Main(start);

	// 第一步，根据 start，创建一个空的 CFunc
	CFunc* pfunc = this->func_new(pmain);

	if (pmain == start)
		strcpy(pfunc->m_funcname,"start");
	else
		strcpy(pfunc->m_funcname,"main");

	g_Cur_Func = pfunc;	//	设置当前的CFunc

    g_Cur_Func->PrepareFunc();
}

#include "cfunctype.h"
    
    
CFunc* Cexe2c::GetFunc(ea_t start)
{
	POSITION pos = m_func_list->GetHeadPosition();
    while (pos != NULL)
    {
        CFunc* p = m_func_list->GetNext(pos);
        if (p->m_head_off == start)						
            return p;
    }
    return NULL;
}

//#include "..\..\LibScanner\LibScanner.H"
#include "..\LibScanner.H"

PCSTR check_if_jmp_api(PCBYTE phead);
PCSTR GetMyExePath();
static CString CheckIf_libfunc(PCBYTE phead)
{
    PCSTR apiname = check_if_jmp_api(phead);
    if (apiname)
    {
        return apiname;
    }

    if (1)
    {
        CString fcname = g_LIBSCANNER->CheckIfLibFunc(phead);

        if (!fcname.IsEmpty())
        {
            return fcname;
        }
    }
    return "";
}
CFunc* Cexe2c::func_new(ea_t start)
//	根据 start，创建一个空的 CFunc
//	并加入 m_func_list
//	如果该地址的 CFunc 已经存在，则直接返回它
{
    {
        // 检查本func是否已经在func链中了
        CFunc* p = GetFunc(start);
        if (p != NULL)
            return p;
    }

    // not find
	log_prtl("New func %x",start);
    if (start == 0x128b1e1)
    {
        start = 0x128b1e1;
    }

	CFunc* p = new CFunc(start);    //new_CFunc

	//	填入 CFunc 的一些其它信息
	fill_func_info(start, p);

    CString pname = CheckIf_libfunc(ea2ptr(p->m_head_off));

    if (!pname.IsEmpty())
    {
        p->m_IfLibFunc = true;
        p->m_functype = Get_FuncDefine_from_internal_name(pname);
        if (p->m_functype)
            strcpy(p->m_funcname, p->m_functype->m_pname);
        else
            strcpy(p->m_funcname, pname);
    }

    m_func_list->AddTail(p);	//insert cur Func to m_func_list

    return p;
}

static DWORD str_to_dword(PCSTR cmd)
{
    char buf[80];
    strncpy(buf, cmd, 70);
    buf[70] = 0;
    strupr(buf);
    if (buf[0] == '0' && buf[1] == 'X')
    {
        DWORD d;
        sscanf(buf+2,"%X", &d);
        return d;
    }
    DWORD d;
    sscanf(buf,"%d", &d);
    return d;
}
#include "hpp.h"
PCSTR my_itoa(int i);
void __stdcall Cexe2c::DoCommandLine(PCSTR cmd)
{
    //MessageBox(NULL,"asdf","dddd",0);
    //if (g_Cur_Func == NULL)
        //return;
    if (memcmp(cmd, "var ", 4) == 0)
    {
        PCSTR varname = cmd + 4;
        CFuncOptim the(g_Cur_Func);
        the.Prt_Var_Flow(varname);
    }
    else if (memcmp(cmd, "funcinfo", 8) == 0)
    {
        g_Cur_Func->report_info();
    }
    else if (memcmp(cmd, "funcproto ", 10) == 0)
    {//当前函数的预定义
        cmd += 10;
        CCInfo * pnew = new CCInfo;
        CFuncType* pfunctype = pnew->do_func_proto(cmd);
        g_Cur_Func->m_functype = pfunctype;
        strcpy(g_Cur_Func->m_funcname, pfunctype->m_pname);
    }
    else if (memcmp(cmd, "classof ", 8) == 0)
    {
        cmd += 8;
        VarTypeID id = g_VarTypeManage->VarType_Name2ID(cmd);
        Class_st* pclass = g_VarTypeManage->id2_Class(id);
        CFuncType* pfunctype = g_Cur_Func->m_functype;
        if (pfunctype != NULL && pclass != NULL)
        {
            pfunctype->m_class = pclass;
        }
        //this->DoCommandLine("funcproto void __cdecl func1()");
        //this->DoCommandLine("classof CTest1");
    }
    else if (memcmp(cmd, "macro1", 6) == 0)
    {
        this->DoCommandLine("funcproto ATOM __cdecl MyRegisterClass(HINSTANCE hInstance)");
    }
    else if (memcmp(cmd, "macro2", 6) == 0)
    {
        this->DoCommandLine("funcproto BOOL __cdecl InitInstance(HINSTANCE hInstance, int nCmdShow)");
    }
    else if (memcmp(cmd, "macro3", 6) == 0)
    {
        this->DoCommandLine("funcproto int __stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)");
    }
    else if (memcmp(cmd, "macro_test", 10) == 0)
    {
        this->DoCommandLine("funcproto void __cdecl CTest1()");
    }
    else if (memcmp(cmd, "macro5", 6) == 0)
    {
        this->DoCommandLine("classof CTest1");
    }
#if 0
    //this->DoCommandLine("funcproto void __cdecl test_class()");
    //this->DoCommandLine("funcproto void __cdecl test_class()");
#endif
    else if (memcmp(cmd, "restart", 7) == 0)
    {
        g_Cur_Func->Restart();
    }
    else if (memcmp(cmd, "optim", 5) == 0)
    {
        this->analysis_All();
    }
    else if (memcmp(cmd, "funcnew ", 8) == 0)
    {
        cmd += 8;
        DWORD d = str_to_dword(cmd);
        this->func_new(d);
    }
}

void __stdcall Cexe2c::Change_Array(int colorindex, void* handle, int newarray)
{
    if (handle == NULL)
        return;
    
    if (colorindex == COLOR_Var)
    {
        st_VarLL* p = (st_VarLL*)handle;
        if (p->array < newarray)
        {
        }
        p->array = newarray;
    }
    if (colorindex == COLOR_VarH)
    {
        M_t* p = (M_t*)handle;
        //g_Cur_Func->m_exprs->Change_Array(p, newarray);
    }
}
void __stdcall Cexe2c::LineHotKey(void* hline, char key)
{
    if (key == 'i' || key == 'I')
    {//i for internal
        static bool flag = false;
        flag = !flag;
        if (flag)
        {
            //prtout_itn();
        }
        else
        {
            //prtout_cpp();
        }
    }
    if (hline == NULL)
        return;
    
    if (key == 'd' || key == 'D')
    {
        g_Cur_Func->MakeDownInstr(hline);
    }
}
void __stdcall Cexe2c::HotKey(int colorindex, void* handle, char key)
{
    if (handle == NULL)
        return;
    if (key == 'p' || key == 'P')
    {
    }
    else
        return;

    if (colorindex == COLOR_VarH)
    {
        M_t* p = (M_t*)handle;
        //g_Cur_Func->m_exprs->namemanager->Rename(p->nameid,newname);
    }
}
    
void __stdcall Cexe2c::ReType(int colorindex, void* handle, PCSTR newtype)
{
    if (handle == NULL)
        return;
    else if (colorindex == COLOR_VarH || colorindex == COLOR_type)
    {
        M_t* p = (M_t*)handle;
        g_Cur_Func->ReType(p, newtype);
    }
}
bool __stdcall Cexe2c::Rename(enum XMLTYPE xmltype, void* handle, PCSTR newname)
{
    if (handle == NULL)
        return false;
    
    if (xmltype == XT_FuncName)
    {
        CFunc* p = (CFunc*)handle;
        strcpy(p->m_funcname, newname);
        return true;
    }
    else if (xmltype == XT_Symbol)
    {
        M_t* p = (M_t*)handle;
        strcpy(p->namestr, newname);
        return true;
    }
    /*
    else if (colorindex == COLOR_Var)
    {
        st_VarLL* p = (st_VarLL*)handle;
        strcpy(p->Name, newname);
    }
    else if (colorindex == COLOR_type)
    {
        M_t* p = (M_t*)handle;
        g_Cur_Func->ReType(p, newname);
    }
    */
    return false;
}
void lib_init()
{
    I_LIBSCANNER* pnew = NEW_LIBSCANNER();

    char buf[255];
    sprintf(buf,"%s\\LIB\\%s",
            GetMyExePath(),//g_mypath,
            "LIBC.LIB");

    pnew->ScanLib(buf);

    g_LIBSCANNER = pnew;
}

void lib_exit()
{
    if (g_LIBSCANNER != NULL)
    {
        g_LIBSCANNER->Release();
        g_LIBSCANNER = NULL;
    }
}
