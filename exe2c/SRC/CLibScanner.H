///////////////////////////////////////////////////////////////
//
// CLibScanner.h
// Copyright(C) 1999-2005 LiuTaoTao，bookaa@rorsoft.com
//
///////////////////////////////////////////////////////////////

#ifndef	_CLIBSCANNER_H_
#define	_CLIBSCANNER_H_

#include "..\LibScanner.H"
#include "vector"
typedef struct
{
	CHAR		ObjName[_MAX_PATH];	//名字
	size_t		StartOff;				//起始地址
	DWORD		Len;					//终止地址
	LPBYTE		lpBuffer;				//OBJ数据
}COFFOBJECT,*PCOFFOBJECT;

typedef struct
{
	SHORT SYMB_INX;
	SHORT SECT_NUM;
	BYTE  STOR_CLS;
	DWORD VALUE;
	WORD  TYPE;
	CHAR  Name[_MAX_PATH];
}COFFSYMBOL,*PCOFFSYMBOL;

#define MAKEDWORDREVERS(x)  ((((x)&0xFF)<<24) | (((x)&0xFF00) << 8) | (((x)&0xFF0000) >>8) | (((x)&0xFF000000)>>24))
class CLibScanner : public I_LIBSCANNER
{
	typedef std::vector<COFFOBJECT>	COFFOBJECT_LIST;
	typedef std::vector<COFFSYMBOL>	COFFSYMBOL_LIST;
	typedef std::vector<PFUNCTION_SYMBOL> FUNCTION_LIST;	
public:
	CLibScanner(){};
	~CLibScanner();

public:
///////////// DO NOT EDIT THIS //////////////
	virtual bool	__stdcall BaseInit();	//override the origin function, it's a class creator!
///////////// DO NOT EDIT THIS //////////////

	//Add interface here
	virtual bool	__stdcall test();		//Test interface
	//Add interface here
	virtual BOOL __stdcall ScanLib(LPCSTR szLib);
	virtual PFUNCTION_SYMBOL __stdcall GetFunctionInfo(LPCSTR szFun);
    virtual PCSTR __stdcall CheckIfLibFunc(PCBYTE phead);

private:
	//Add member here
	//Add member here
	FUNCTION_LIST m_funs;
	void ClearFunction();
	void ClearCOFFObject(COFFOBJECT_LIST &objs);
    LPCSTR	COFFGetName(const IMAGE_SYMBOL* coff_sym, const char* coff_strtab);
	BOOL ScanCOFFObject(COFFOBJECT_LIST &objs,LPBYTE lpBuffer,DWORD Len);
    PIMAGE_SECTION_HEADER FindSection(PCOFFOBJECT pObj,SHORT SectNumber);
    PCOFFSYMBOL FindSymbol(COFFSYMBOL_LIST &syms,int symIndx);
	void ScanFunction(FUNCTION_LIST & funs,PCOFFOBJECT pObj);
    bool CheckThisFunc(PFUNCTION_SYMBOL pFun, PCBYTE phead);
    bool CheckSubFunc(PFUNCTION_SYMBOL pFun, PCBYTE phead);
};

#endif	// _CLIBSCANNER_H_
