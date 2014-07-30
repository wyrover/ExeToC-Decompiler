// Copyright(C) 1999-2005 LiuTaoTao，bookaa@rorsoft.com


//	exe2c project

#include "stdafx.h"
#include "00000.h"
#include "FileLoad.h"
#include "CApiManage.h"

void	Disassembler_Init_offset(PBYTE code_buf, ea_t code_offset);
PBYTE	ea2ptr(ea_t pos);
ea_t ptr2ea(void* p);
BYTE	Peek_B(ea_t pos);
WORD	Peek_W(ea_t pos);
DWORD	Peek_D(ea_t pos);

//#include "Deasm_Init.h"

BOOL	PELoad_isMFC = FALSE;

int RelocationPE(PEHEADER* peh);
int	RelocImportTable(PEHEADER* peh);

void FileLoader::LoadPE(DWORD peoffs)
{
	PBYTE pestart = &fbuff[peoffs];
	PEHEADER* peh = (PEHEADER *)pestart;

	if (peh->flags & 0x2000)
	{
		g_EXEType = enum_PE_dll;
	}
	switch (peh->subsystem)
	{
	case 1:		//	native device driver
		g_EXEType = enum_PE_sys;
		break;
	case 2:		//	WINDOWS GUI
	case 3:		//	WINDOWS CUI console
		g_EXEType = enum_PE_exe;
		break;
	default:
		alert_prtf("subsystem = %x",peh->subsystem);
		assert(0);
	}
	//???? hpp_init();

	PEObjData *pdata = (PEObjData *)(pestart+sizeof(PEHEADER)+(peh->numintitems-0x0a)*8);

	DWORD imagelen = peh->imagesize;
	
	PBYTE p0 = (PBYTE)VirtualAlloc(0,imagelen,MEM_COMMIT,PAGE_READWRITE);
	if (p0 == NULL)
	{
		//error("VirtualAlloc get NULL\n");
	}
	//PBYTE p0 = new BYTE[imagelen];
	memcpy(p0, pestart, peh->headersize);

	for ( int i=0;i<peh->objects;i++ )
	{
		memcpy(p0 + pdata[i].rva,
			   fbuff + pdata[i].phys_offset,
			   pdata[i].phys_size);
	}
	
	this->image_buf = p0;
	this->image_len = imagelen;
	this->entry_buf = p0 + peh->entrypoint_rva;
	this->entry_offset = peh->entrypoint_rva+peh->image_base;
	
	// 因为文件的调入地址与虚拟地址不同，所以要记住这个差值
    // 以后主程序只以offset来访问，不管实际buffer
	
	//	在这里是因为后面的RelocImportTable要用到它
    Disassembler_Init_offset(this->entry_buf, this->entry_offset);

	//RelocationPE((PEHEADER*)p0);
	RelocImportTable((PEHEADER*)p0);

//	proc2(p0 + peh->entrypoint_rva,
//		  peh->entrypoint_rva+peh->image_base);

//	VirtualFree(p0,imagelen,0);
	//delete p0;

}
/*
	problems left:
	1.	if the module need a private DLL, then maybe we should change
			GetModuleHandle
		with
			LoadLibrary
		and do "FreeLibrary" somewhere
	2.	Only do import with name, should add import with ORD
*/
typedef struct
{
	DWORD	tbl1_rva;	//00
	DWORD	dummy1;		//04
	DWORD	dummy2;		//08
	DWORD	dllname_rva;	//0c
	DWORD	tbl2_rva;	//10
	//size of = 0x14
}IMP_0;

#include "DLL32DEF.h"

int	RelocImportTable(PEHEADER* peh)
{
	PBYTE pestart = (PBYTE)peh;
	PBYTE	pimp = pestart + peh->importtable_rva;

//	DWORD	impsize = peh->import_datasize;
	
    for (IMP_0*	pimp0 = (IMP_0*)pimp; pimp0->tbl1_rva != 0; pimp0++)
	{
		PSTR	pDLLname = (PSTR)pestart+pimp0->dllname_rva;
		log_prtl("pDLLname is %s ",pDLLname);
		//HMODULE hModule = GetModuleHandle(pDLLname);	//should I use Load ?
		PDWORD	p2 = PDWORD(pestart+pimp0->tbl2_rva);
		DWORD d;
		while ((d = *p2) != 0)
		{
			PSTR apiname;
			//DWORD apiaddr = (DWORD)GetProcAddress(hModule,apiname);
			static DWORD ggdd = 0xACBC0000;
			DWORD apiaddr = ggdd++;

			char buf[80];
			if ((d & 0xffff0000) == 0x80000000)
			{	//	按ord输入
				apiname = DLLDEF_Get_ApiName_from_ord(pDLLname,(WORD)d);
				if (apiname == NULL)
				{
					sprintf(buf,"ord_%x_%s",(WORD)d,pDLLname);
					PSTR pp11 = strchr(buf,'.');
					if (pp11)
						*pp11 = '_';
					apiname = buf;
				}
				assert(strlen(apiname) < 80);
			}
			else
			{
				PBYTE pimpitem = pestart+d;
				apiname = (PSTR)pimpitem+2;
				assert(strlen(apiname) < 80);
			}
			log_prtl("impapi is %s , %x",apiname,apiaddr);	// + 2byte
			
			*p2 = apiaddr;	//fill imp table with api address
			g_ApiManage->New_ImportAPI(apiname, ptr2ea((PBYTE)p2));
			p2++;
		}
	}
	

	return 0;
}

#define KSPE_IMAGE_SIZEOF_BASE_RELOCATION          8    // Because exclude the first TypeOffset

typedef struct _KSPE_IMAGE_BASE_RELOCATION {
    DWORD   VirtualAddress;
    DWORD   SizeOfBlock;
    WORD    TypeOffset[1];
} KSPE_IMAGE_BASE_RELOCATION, *PKSPE_IMAGE_BASE_RELOCATION;

#define KSPE_IMAGE_REL_BASED_ABSOLUTE              0
#define KSPE_IMAGE_REL_BASED_HIGH                  1
#define KSPE_IMAGE_REL_BASED_LOW                   2
#define KSPE_IMAGE_REL_BASED_HIGHLOW               3
#define KSPE_IMAGE_REL_BASED_HIGHADJ               4
#define KSPE_IMAGE_REL_BASED_MIPS_JMPADDR          5


int RelocationPE(PEHEADER* peh)
{
	PBYTE pestart = (PBYTE)peh;
	DWORD nRelocSize = peh->fixup_datasize;

//    int Result = false;

    KSPE_IMAGE_BASE_RELOCATION *pCurrentReLocBlock = NULL;
    int nRelocCountOfBlock = 0;
    WORD *pRelocItem = NULL;

    int nOffsetReloc = pestart - (PBYTE)(peh->image_base);
    if (nOffsetReloc == 0)
        return true; // not need to do Reloc

    pCurrentReLocBlock = (KSPE_IMAGE_BASE_RELOCATION *)(
        pestart + (peh->fixuptable_rva)
    );

    while (nRelocSize > 0)
    {
        BYTE *pbyRelocBlockStartAddress =
            pestart + (pCurrentReLocBlock->VirtualAddress);

        nRelocCountOfBlock = (
            (pCurrentReLocBlock->SizeOfBlock) - KSPE_IMAGE_SIZEOF_BASE_RELOCATION
        ) / sizeof(WORD);

        pRelocItem = pCurrentReLocBlock->TypeOffset;

        while (nRelocCountOfBlock > 0)
        {
            DWORD RelocItem = *pRelocItem;
            switch (RelocItem >> 12)
            {
            case KSPE_IMAGE_REL_BASED_HIGHLOW:
                // if Intel CPU
                // *((DWORD *)((RelocItem & 0xfff) + RelocBlockStartAddress) ) += nOffsetReloc;
                *((BYTE **)(pbyRelocBlockStartAddress + (RelocItem & 0xfff))) += nOffsetReloc;
                break;

            //default: Skip
            }
            pRelocItem++;
            nRelocCountOfBlock--;
        }
        nRelocSize -= pCurrentReLocBlock->SizeOfBlock;
        // Get Next Reloc Block
        pCurrentReLocBlock = (KSPE_IMAGE_BASE_RELOCATION *)(
            ((BYTE *)pCurrentReLocBlock) + (pCurrentReLocBlock->SizeOfBlock)
        );
    } // while

    return true;
}

ea_t	Find_Main(ea_t start)
{
	ea_t p = start;
	if (Peek_W(p) == 0x8B55
		&& Peek_W(p+3) == 0xFF6A
		&& Peek_W(p+0x1d) == 0xEC83
		&& Peek_B(p+0xaf) == 0xE8		//	401780 - 4016d1 = af
		)
	{
		p += 0xaf;
    	DWORD d = Peek_D(p+1);
		//alert_prtf("p = %x, d = %x",p,d);
		//alert_prtf(" I get main = %x",p+5+d);
        return p+5+d;
    }
	if (Peek_W(p) == 0x8B55
		&& Peek_W(p+3) == 0xFF6A
		&& Peek_W(p+0x1d) == 0xEC83
		&& Peek_B(p+0xc9) == 0xE8		//	00401149 - 00401080 = c9
		)
	{
		p += 0xc9;
    	DWORD d = Peek_D(p+1);
		//alert_prtf("p = %x, d = %x",p,d);
		//alert_prtf(" I get main = %x",p+5+d);
        return p+5+d;
    }

    if (Peek_W(p) == 0xa164
        && Peek_W(p+0x16) == 0x8964
        && Peek_W(p+0x2f) == 0x15ff
        && Peek_B(p+0x152) == 0xE8		//	1A42 - 18f0=152
        )
    {
        p += 0x152;
        DWORD d = Peek_D(p+1);
        //alert_prtf("p = %x, d = %x",p,d);
        //alert_prtf(" I get main = %x",p+5+d);
        return p+5+d;   //这是 WinMain
    }
    return start;
}

ea_t	Find_WinMain(ea_t start)
{
	ea_t p = start;
	if (Peek_W(p) == 0x8B55
		&& Peek_W(p+3) == 0xFF6A
		&& Peek_W(p+0x1d) == 0xEC83
		&& Peek_B(p+0xc9) == 0xE8
		)
	{
		p += 0xc9;
    	DWORD d = Peek_D(p+1);
		//alert_prtf("p = %x, d = %x",p,d);
		//alert_prtf(" I get WinMain = %x",p+5+d);
		log_prtl(" I get WinMain = %x",p+5+d);
        return p+5+d;
    }
	if (Peek_W(p) == 0x8B55
		&& Peek_W(p+3) == 0xFF6A
		&& Peek_W(p+0x1d) == 0xEC83
		&& Peek_B(p+0x12f) == 0xE8
		)	//	这好象是用MFC的时候
	{
		p += 0x12f;
    	DWORD d = Peek_D(p+1);
		//alert_prtf("p = %x, d = %x",p,d);
		//alert_prtf(" I get main = %x",p+5+d);
		log_prtl(" I get MFC WinMain = %x",p+5+d);
		PELoad_isMFC = TRUE;
        return p+5+d;
    }
	//alert_prtf("not find WinMain");
	log_prtl("not find WinMain");
    return start;
}
BOOL	Valid_ea(ea_t ea)
{
	if (ea >= 0x400000 && ea < 0x80000000)
		return TRUE;
	return FALSE;
}
void OneItem_Init(ea_t ea);
void	SomeOther_about_MFC_load()
{
	if (! PELoad_isMFC)
		return;
	ea_t start = g_FileLoader->entry_offset;

	PBYTE p = ea2ptr(start);
	
	p += 0xbb;
	if (p[0] != 0x68 || p[5] != 0x68 || p[10] != 0xe8)
		return;		//	这里是两个push immed

	ea_t s_init = *(DWORD *)(p+6);
	ea_t e_init = *(DWORD *)(p+1);

	p = ea2ptr(s_init);
	
	ea_t ea = *(DWORD *)(p+4);
	if ( ! Valid_ea(ea))
		return;

	ea = *(DWORD *)(p+8);
	if ( ! Valid_ea(ea))
		return;

	OneItem_Init(ea);

	//alert_prtf("here init start = %x, end = %x, useful = %x",s_init, e_init, ea);
}

void	WinApp_vftbl(ea_t vftbl);

void OneItem_Init(ea_t ea)
{
	PBYTE p = ea2ptr(ea);
	if (*p != 0xe8)
		return;

	p += *(DWORD *)(p+1);
	p += 5;

	if (p[0] != 0xb9 || p[5] != 0xe9)
		return;

	ea_t theapp = *(DWORD *)(p+1);

	//alert_prtf("theapp = %x",theapp);

	p += *(DWORD *)(p+6);
	p += 10;

	if (p[5] != 0xe8)
		return;
    if (*(WORD*)(p+10) != 0x06c7)
		return;

	ea_t vftbl = *(DWORD *)(p+12);

	//alert_prtf("vftbl = %x",vftbl);

	WinApp_vftbl(vftbl);
}
/*
00401070                   Init2           proc near
00401070 E8 0B 00 00 00                    call    onInit
00401075 E9 16 00 00 00                    jmp     loc_401090
00401075                   Init2           endp

00401080                   onInit          proc near               ; CODE XREF: Init2p
00401080 B9 28 30 40 00                    mov     ecx, offset theApp
00401085 E9 96 FF FF FF                    jmp     sub_401020
00401085                   onInit          endp

00401020                   sub_401020      proc near               ; CODE XREF: onInit+5j
00401020 56                                push    esi
00401021 8B F1                             mov     esi, ecx
00401023 6A 00                             push    0
00401025 E8 4E 05 00 00                    call    ??0CWinApp@@QAE@PBD@Z ; CWinApp::CWinApp(char const *)
0040102A C7 06 18 22 40 00                 mov     dword ptr [esi], offset off_402218
00401030 8B C6                             mov     eax, esi
00401032 5E                                pop     esi
00401033 C3                                retn
00401033                   sub_401020      endp ; sp = -4
*/

#define	WinApp_InitInstance	0x16

void	WinApp_vftbl(ea_t vftbl)
{
	alert_prtf("vftbl = %x",vftbl);
	DWORD* p = (DWORD*)ea2ptr(vftbl);

	ea_t ea_InitInstance = p[WinApp_InitInstance];
	alert_prtf("ea_InitInstance = %x",ea_InitInstance);
}
