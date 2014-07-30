///////////////////////////////////////////////////////////////
//
// CLibScanner.cpp
// Copyright(C) 1999-2005 LiuTaoTao，bookaa@rorsoft.com
//
///////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CLibScanner.h"
#include <io.h>


KS_DECLARE_COMPONENT(LibScanner, LIBSCANNER)


bool __stdcall LibScanner_Init()
{
	return true;
}


void __stdcall LibScanner_Exit()
{
}


bool __stdcall CLibScanner::BaseInit()
{
	//KICK_MFC();
	return true;
}


CLibScanner::~CLibScanner()
{
	ClearFunction();
    //KICK_MFC();
}


bool __stdcall CLibScanner::test()
{
	//KICK_MFC();
	return true;
}


void CLibScanner::ClearFunction()
{
	for(FUNCTION_LIST::iterator it = m_funs.begin();it!=m_funs.end();++it)
	{
		PFUNCTION_SYMBOL pFun= *it;
		delete []pFun->FunRawData;
		delete  []((BYTE*)pFun);
	}
	m_funs.clear();
}

void CLibScanner::ClearCOFFObject(COFFOBJECT_LIST &objs)
{
	for(COFFOBJECT_LIST::iterator it = objs.begin();it!=objs.end();++it)
	{
		COFFOBJECT obj;
		obj= *it;
		delete  []obj.lpBuffer;
	}
	objs.clear();
}
LPCSTR CLibScanner::COFFGetName(const IMAGE_SYMBOL* coff_sym, const char* coff_strtab)
{
	static	char	namebuff[9];
	const char*		nampnt;

	if (coff_sym->N.Name.Short)
	{
		memcpy(namebuff, coff_sym->N.ShortName, 8);
		namebuff[8] = '\0';
		nampnt = &namebuff[0];
	}
	else
	{
		nampnt = coff_strtab + coff_sym->N.Name.Long;
	}

	return nampnt;
}

PIMAGE_SECTION_HEADER CLibScanner::FindSection(PCOFFOBJECT pObj,SHORT SectNumber)
{
	PIMAGE_FILE_HEADER pIFH = (PIMAGE_FILE_HEADER)pObj->lpBuffer;
	PIMAGE_SECTION_HEADER pISH = (PIMAGE_SECTION_HEADER)(pObj->lpBuffer + IMAGE_SIZEOF_FILE_HEADER);
	for(int j=0;j<pIFH->NumberOfSections;j++)
	{
		if(j+1==SectNumber)
			return &pISH[j];
	}	
	return NULL;
}

void CLibScanner::ScanFunction(FUNCTION_LIST & funs,PCOFFOBJECT pObj)
{
	PIMAGE_FILE_HEADER pIFH = (PIMAGE_FILE_HEADER)pObj->lpBuffer;
	PIMAGE_SYMBOL pIS = (PIMAGE_SYMBOL)(pObj->lpBuffer + pIFH->PointerToSymbolTable);
    LPCSTR lpStrTab= (const char*)(pIS + pIFH->NumberOfSymbols);

	COFFSYMBOL_LIST syms;
	for(int k =0;k<pIFH->NumberOfSymbols;k++)
	{
		PIMAGE_SYMBOL pcurIS = pIS+k;

		COFFSYMBOL sym;
		ZeroMemory(&sym,sizeof(COFFSYMBOL));
		strcpy(sym.Name,COFFGetName(pcurIS,lpStrTab));
		sym.SYMB_INX = k;
		sym.SECT_NUM = pcurIS->SectionNumber;
		sym.STOR_CLS = pcurIS->StorageClass;
		sym.TYPE     = pcurIS->Type;
		sym.VALUE    = pcurIS->Value;
		syms.push_back(sym);
	
		k+=pcurIS->NumberOfAuxSymbols;
	}


	for(int i =0;i<pIFH->NumberOfSymbols;i++)
	{
		PIMAGE_SYMBOL pSymb = pIS+i;
		LPCSTR lpName = COFFGetName(pSymb,lpStrTab);
		if(ISFCN(pSymb->Type) &&pSymb->SectionNumber>0)
		{
			
			PIMAGE_SECTION_HEADER pISH = FindSection(pObj,pSymb->SectionNumber);

			if(pISH)
			{
				PFUNCTION_SYMBOL pFun = (PFUNCTION_SYMBOL) new BYTE[sizeof(FUNCTION_SYMBOL)+pISH->NumberOfRelocations*sizeof(REFSYMBOL)];

				strcpy(pFun->FunctionName , COFFGetName(pSymb,lpStrTab));
				
				if(pISH->SizeOfRawData > pSymb->Value )
				{
					pFun->dwFuncLen  = pISH->SizeOfRawData - pSymb->Value;
					pFun->FunRawData = new BYTE[pFun->dwFuncLen];

					memcpy(pFun->FunRawData,(PBYTE)(pObj->lpBuffer + pISH->PointerToRawData) + pSymb->Value,pFun->dwFuncLen);		
					
					PIMAGE_RELOCATION pIR = (PIMAGE_RELOCATION)(pObj->lpBuffer + pISH->PointerToRelocations);
					
					pFun->RefCount = pISH->NumberOfRelocations;

					for(int i =0;i<pFun->RefCount;i++)
					{
						PCOFFSYMBOL symb = FindSymbol(syms,pIR[i].SymbolTableIndex);
						strcpy(pFun->RefInfo[i].RefSymbol,symb->Name);
						pFun->RefInfo[i].RefOffset = pIR[i].VirtualAddress;
						pFun->RefInfo[i].RefType   = pIR[i].Type;
					
					}
					strcpy(pFun->ObjName,pObj->ObjName);

					funs.push_back(pFun);
				}
                else
                {
                    TRACE("Error!\r\n");
                }
			}
		}
		i+=pSymb->NumberOfAuxSymbols;
	}
}

PCOFFSYMBOL CLibScanner::FindSymbol(COFFSYMBOL_LIST &syms,int symIndx)
{
	for(COFFSYMBOL_LIST::iterator it = syms.begin();it!=syms.end();++it)
	{
		if((*it).SYMB_INX == symIndx)
			return &(*it);
	}
	return NULL;
}


BOOL CLibScanner::ScanCOFFObject(COFFOBJECT_LIST &objs,LPBYTE lpBuffer,DWORD Len)
{
	if(memcmp(lpBuffer,IMAGE_ARCHIVE_START,IMAGE_ARCHIVE_START_SIZE)!=0)
		return FALSE;

	PIMAGE_ARCHIVE_MEMBER_HEADER pSect = (PIMAGE_ARCHIVE_MEMBER_HEADER)(lpBuffer+IMAGE_ARCHIVE_START_SIZE);
	BOOL bFirst = FALSE;

	LPBYTE lpNewPtr = (LPBYTE)pSect;
	LPSTR lpLongTable = NULL;
	while(lpNewPtr <lpBuffer + Len)
	{
		if(memcmp(pSect->Name,IMAGE_ARCHIVE_LINKER_MEMBER,16)==0)
		{
			//Nothing
		}
		else if(memcmp(pSect->Name,IMAGE_ARCHIVE_LONGNAMES_MEMBER,16)==0)//LONG Name
		{
			DWORD theSecSize = atol((LPSTR)pSect->Size);
			lpLongTable  = ((LPSTR)pSect) + sizeof(IMAGE_ARCHIVE_MEMBER_HEADER);
		}	
		else //Obj Section
		{
			size_t ObjOff = ((LPBYTE)pSect) - lpBuffer;
			LPSTR lpEnd = (LPSTR)&pSect->Name[15];
			
			while(*lpEnd!='/')
			{
				lpEnd--;
			}
			
			LPSTR lpObjName = NULL;
			if(lpEnd == (LPSTR)pSect->Name )
			{//Long Name
				int longNameOff = atol((LPSTR)&pSect->Name[1]);
				lpObjName = lpLongTable+longNameOff;
			}
			else
			{
				lpEnd++;
				*lpEnd = 0;
				lpObjName = (LPSTR)pSect->Name;
			}

			COFFOBJECT Obj;
			strcpy(Obj.ObjName,lpObjName);
			Obj.Len		 = atol((LPSTR)pSect->Size);
			Obj.lpBuffer = new BYTE[Obj.Len];
			Obj.StartOff = ObjOff;

			LPBYTE lpData = ((LPBYTE)pSect) + sizeof(IMAGE_ARCHIVE_MEMBER_HEADER);
			memcpy(Obj.lpBuffer,lpData,Obj.Len);
			objs.push_back(Obj);
		}
		lpNewPtr = (LPBYTE)pSect;
		lpNewPtr += atol((LPSTR)pSect->Size) + sizeof(IMAGE_ARCHIVE_MEMBER_HEADER);
		if(*lpNewPtr=='\n')
			lpNewPtr++;
		pSect = (PIMAGE_ARCHIVE_MEMBER_HEADER) lpNewPtr;
	}	
	return TRUE;
}


int log_prtl(PCSTR fmt,...);
BOOL __stdcall CLibScanner::ScanLib(LPCSTR szLib)
{
    log_prtl("Loading %s", szLib);
	FILE * pFile = fopen(szLib,"rb");
	if(pFile==NULL)
	{
        log_prtl("Load error: file not find %s", szLib);
		return FALSE;
	}
	long fsize = _filelength(fileno(pFile));

	PBYTE fbuf = new BYTE[fsize];
	if (fbuf == NULL)
	{
		fclose(pFile);
		return FALSE;
	}
	fread(fbuf,fsize,1,pFile);

	fclose(pFile);
	COFFOBJECT_LIST objs;
	if(!ScanCOFFObject(objs,fbuf,fsize))
	{
		delete []fbuf;
		return FALSE;
	}
	delete []fbuf;
 
	for(COFFOBJECT_LIST::iterator it = objs.begin();it!=objs.end();++it)
	{
		ScanFunction(m_funs,&(*it));
	}
	ClearCOFFObject(objs);

    log_prtl("%d function loaded.", this->m_funs.size());
	return TRUE;
}
PFUNCTION_SYMBOL __stdcall CLibScanner::GetFunctionInfo(LPCSTR szFun)
{
	for(FUNCTION_LIST::iterator it = m_funs.begin();it!=m_funs.end();++it)
	{
		PFUNCTION_SYMBOL pFun= *it;

		if(strcmp(pFun->FunctionName,szFun)==0)
			return pFun;
	}
	return NULL;	
}
bool IfReAlloc(PFUNCTION_SYMBOL pFun, int offset)
{
    for (int i=0; i<pFun->RefCount; i++)
    {
        REFSYMBOL* p = &pFun->RefInfo[i];
        if (p->RefOffset == offset)
            return true;
    }
    return false;
}
void nop(int)
{
}
void nop(const void*)
{
}

//call    ??2@YAPAXI@Z    ; operator new(uint)
bool CLibScanner::CheckSubFunc(PFUNCTION_SYMBOL pFun, PCBYTE phead)
{
    for (int i=0; i<pFun->RefCount; i++)
    {
        REFSYMBOL* p = &pFun->RefInfo[i];
        nop(p->RefType);
		PCBYTE p1 = phead + p->RefOffset;
		nop(p1);
		if (p->RefType == IMAGE_REL_I386_REL32	//==0x14
            && *(p1-1) == 0xe8) //e8是个call
        {
            signed int off = *(signed int*)p1;
            PCBYTE new_phead = p1 + off + 4;
            if (!strcmp(p->RefSymbol, this->CheckIfLibFunc(new_phead)))
            {//有一个就足够了
                return true;
            }
			else
				return false;
        }
    }
    return true;
}
bool CLibScanner::CheckThisFunc(PFUNCTION_SYMBOL pFun, PCBYTE phead)
{
    PCBYTE phead1 = phead;

    PCBYTE psrc = pFun->FunRawData;
    int len = pFun->dwFuncLen;
    int offset = 0;
    while (len > 0)
    {
        if (IfReAlloc(pFun, offset))
        {
            offset += 4;
            len -= 4;
            psrc+=4;
            phead1+=4;
            continue;
        }
        if (*psrc != *phead1)
            return false;
        offset++;
        len--;
        psrc++;
        phead1++;
    }
    if (pFun->dwFuncLen < 0x200 && pFun->RefCount > 0)
    {//太短的函数，最好再检查一下它call的函数
        return CheckSubFunc(pFun, phead);
    }
    return true;
}
PCSTR __stdcall CLibScanner::CheckIfLibFunc(PCBYTE phead)
{
    for(FUNCTION_LIST::iterator it = m_funs.begin();it!=m_funs.end();++it)
    {
        PFUNCTION_SYMBOL pFun= *it;

        if (this->CheckThisFunc(pFun, phead))
        {
            return pFun->FunctionName;
        }
    }
    return NULL;
}
