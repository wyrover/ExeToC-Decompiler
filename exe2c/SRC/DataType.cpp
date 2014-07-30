// Copyright(C) 1999-2005 LiuTaoTao£¬bookaa@rorsoft.com

// DataType.cpp: implementation of the CDataTypeMng class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DataType.h"
#include "ParseHead.h"
//#include	"CISC.H"



static bool __stdcall exe2c_Init()
{
    if (true)//GetFileAttributes("e2c_define.h") != -1)
    {
        //CParseHead ph;
        //ph.ParseHeadFile("e2c_define.h");
        
//        g_FuncDefineMng.prtall();
    }
    else
    {
        MessageBox(NULL,"not find e2c_define.h", "error", 0);
    }
	return true;
}


static void __stdcall exe2c_Exit()
{
}

class CDataType_cpp
{
public:
    CDataType_cpp()
    {
        exe2c_Init();
    }
    ~CDataType_cpp()
    {
        exe2c_Exit();
    }
};

CDataType_cpp g_CDataType_cpp;


int log_prtl(PCSTR fmt,...);


    
PCSTR my_itoa(int i)
{
    static char buf[80];
    sprintf(buf, "%d", i);
    return buf;
}

PCSTR CallConvToName(enum_CallC ec)
{
    switch (ec)
    {
    case enum_stdcall: return "__stdcall";
    case enum_cdecl:   return "__cdecl";
    case enum_pascal:  return "PASCAL";
    case enum_fastcall:return "__fastcall";
    default:
        return "__unknown";
    }
}

    


    
