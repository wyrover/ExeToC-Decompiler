// Copyright(C) 1999-2005 LiuTaoTao，bookaa@rorsoft.com

#ifndef DASM__H
#define DASM__H

#define BIT16	0
#define	BIT32	1

#define	_EAX_	0
#define	_ECX_	1
#define	_EDX_	2
#define	_EBX_	3
#define	_ESP_	4
#define	_EBP_	5
#define	_ESI_	6
#define	_EDI_	7
#define	_AX_	0
#define	_CX_	1
#define	_DX_	2
#define	_BX_	3
#define	_SP_	4
#define	_BP_	5
#define	_SI_	6
#define	_DI_	7
#define	_AL_	0
#define	_CL_	1
#define	_DL_	2
#define	_BL_	3
#define	_AH_	4
#define	_CH_	5
#define	_DH_	6
#define	_BH_	7
#define	_NOREG_	100

#define	_ES_	0
#define	_CS_	1
#define	_SS_	2
#define	_DS_	3
#define	_FS_	4
#define	_GS_	5
#define	_NOSEG_	100

#define	ERR_NOERROR			0
#define	ERR_INVALIDCODE		1

#define	NOPREFIX			0
#define	REPZ_PREFIX			1
#define	REPNZ_PREFIX		2


#define	OPER_UNKNOWN	0
#define OPER_READ		1
#define	OPER_WRITE		2
#define	OPER_ACCESS		3

enum OP_TYPE
{
	OP_Invalid	=	0,
	OP_Address	=	1,
	OP_Register	=	2,
	OP_Segment	=	3,
	OP_Immed	=	4,
	OP_Near		=	5,
	OP_Far		=	6,
	
};

typedef	DWORD	ea_t;

typedef struct OPERITEM
{
	OP_TYPE mode;		//OP_Register, ...
	BYTE    rwflag;		//0:Unknown	1:Read 2:Write 3:Access
	BYTE    opersize;	//1:BYTE, 2:WORD, 4:DWORD, 8:double DWORD
	union
	{
		struct
		{
			BYTE    seg_index;	//SegReg Index!!!
			//BYTE    reg_size;	//2:WORD 4:DWORD
			BYTE    base_reg_index;
			BYTE    off_reg_index;
			BYTE    off_reg_scale;
			DWORD   off_value;
		}   addr;		//for OP_Address
		struct
		{
			DWORD   reg_index;  //_ESP_
		}   reg;		//for OP_Register
		struct
		{
			DWORD   sreg_index;
		}   sreg;		//for OP_Segment
		struct
		{
			DWORD   immed_value;
		}   immed;		//for OP_Immed
		struct
		{
			ea_t   offset;
		}   nearptr;	//for OP_Near
		struct
		{
			DWORD   segment;
			DWORD   offset;
		}   farptr;		//for OP_Far
	};
} *POPERITEM;

typedef struct XCPUCODE
{
	enum OPCODETYPE        opcode;		//	C_MOV...
	BYTE        lockflag;	// for LOCK prefix
	BYTE        repeatflag;	// for REPZ/REPNZ prefix
	OPERITEM    op[3];
    
    bool	IsJxx();
    bool	IsJmpNear();
} *PXCPUCODE;


// The list of the types of Opcode
enum OPCODETYPE
{
	C_ERROR,		// It'a invalid instruction
	C_GROUP,		// It'a group. If this, InstName specifies the group table.
	C_0FH,			// It's 0FH instruction. If this, InstName specifies the 0FH table.
	C_SEGPREFIX,	// If this, Opdata1 specifies the index of segment prefix
	C_OPRSIZE,		// Operand size change.
	C_ADRSIZE,		// Address size change.
	C_LOCK,			// LOCK prefix
	C_REPZ,			// REPZ prefix
	C_REPNZ,		// REPNZ prefix
	// Ok, prefix define completed.

	C_ADD,
	C_OR,
	C_ADC,
	C_SBB,
	C_AND,
	C_SUB,
	C_XOR,
	C_CMP,
	C_DAA,
	C_DAS,
	C_AAA,
	C_AAS,
	C_INC,
	C_DEC,
	C_PUSH,
	C_POP,
	C_PUSHA,
	C_POPA,
	C_BOUND,
	C_ARPL,
	C_IMUL,
	C_INS,
	C_OUTS,
	C_JO,
	C_JNO,
	C_JB,
	C_JNB,
	C_JZ,
	C_JNZ,
	C_JNA,
	C_JA,
	C_JS,
	C_JNS,
	C_JP,
	C_JNP,
	C_JL,
	C_JNL,
	C_JLE,
	C_JNLE,
	C_TEST,
	C_NOP,
	C_XCHG,
	C_MOV,
	C_LEA,
	C_CBW,
	C_CWD,
	C_CALL,
	C_WAIT,
	C_PUSHF,
	C_POPF,
	C_SAHF,
	C_LAHF,
	C_MOVS,
	C_CMPS,
	C_STOS,
	C_LODS,
	C_SCAS,
	C_RET,
	C_LES,
	C_LDS,
	C_ENTER,
	C_LEAVE,
	C_RETF,
	C_INT3,
	C_INT,
	C_INTO,
	C_IRET,
	C_AAM,
	C_AAD,
	C_XLAT,
	C_LOOPNZ,
	C_LOOPZ,
	C_LOOP,
	C_JCXZ,
	C_IN,
	C_OUT,
	C_JMP,
	C_HLT,
	C_CMC,
	C_CLC,
	C_STC,
	C_CLI,
	C_STI,
	C_CLD,
	C_STD,
	C_CALLFAR,
	C_JMPFAR,

	C_ROL,
	C_ROR,
	C_RCL,
	C_RCR,
	C_SHL,
	C_SHR,
	C_SAR,

	C_NOT,
	C_NEG,
	C_MUL,
	C_DIV,
	C_IDIV,
	// One-BYTE opcode table completed.

	C_LAR,
	C_LSL,
	C_LSS,
	C_LFS,
	C_LGS,
	C_MOVZX,
	C_MOVSX,
	C_BT,
	C_BTR,
	C_BTS,
	C_BTC,
	C_BSF,
	C_BSR,
	C_SHLD,
	C_SHRD,
	C_SETO,
	C_SETNO,
	C_SETB,
	C_SETNB,
	C_SETZ,
	C_SETNZ,
	C_SETNA,
	C_SETA,
	C_SETS,
	C_SETNS,
	C_SETP,
	C_SETNP,
	C_SETL,
	C_SETNL,
	C_SETLE,
	C_SETNLE,
	C_CMPXCHG,
	C_XADD,
	C_BSWAP,
	C_CLTS,
	C_CPUID,
	C_WRMSR,
	C_RDTSC,
	C_RDMSR,
	C_RDPMC,
	C_INVD,
	C_WBINVD,
	// Two-BYTE opcode table completed.

	C_JCASE	= 254,
	C_NONE
}   ;


#define	X_EAX		0x0000
#define	X_ECX		0x0004
#define	X_EDX		0x0008
#define	X_EBX		0x000C
#define	X_ESP		0x0010
#define	X_EBP		0x0014
#define	X_ESI		0x0018
#define	X_EDI		0x001C

#define	X_ES		0x0020
#define	X_CS		0x0024
#define	X_SS		0x0028
#define	X_DS		0x002C
#define	X_FS		0x0030
#define	X_GS		0x0034

#define	X_EFLAGS	0x0038
#define	X_EIP		0x003C

#define	X_TEMP1		0x0040

#define	X_AX		0x0000
#define	X_CX		0x0004
#define	X_DX		0x0008
#define	X_BX		0x000C
#define	X_SP		0x0010
#define	X_BP		0x0014
#define	X_SI		0x0018
#define	X_DI		0x001C

#define	X_AL		0x0000
#define	X_AH		0x0001
#define	X_CL		0x0004
#define	X_CH		0x0005
#define	X_DL		0x0008
#define	X_DH		0x0009
#define	X_BL		0x000C
#define	X_BH		0x000D


typedef struct INSTRUCTION
{
	DWORD	Opcode;
	PSTR	InstName;
	DWORD	Opdata1;
	DWORD	Opdata2;
	DWORD	Opdata3;
}	*PINSTRUCTION;


struct st_IDA_OUT
{//定义一种类似IDA的ASM输出结构
    CString LockName;
    CString RepName;
    CString CmdStr;
    CString Par1Ptr;
    CString Par1SegPrefix;
    CString Par1Str;
    CString Par2Ptr;
    CString Par2SegPrefix;
    CString Par2Str;
    CString Par3Str;
	
    ea_t linear;

    st_IDA_OUT()
    {
        BYTE* p0 = (BYTE*)this; //这个代码比较奇怪，是为了不把CString清掉
        BYTE* p1 = (BYTE*)&this->linear;
        ZeroMemory(p1, sizeof(st_IDA_OUT) - (p1 - p0));
    }

    void output(PSTR buf);
};

class CDisasm
{
    st_IDA_OUT* m_idaout;

    DWORD	U_ErrorCode;
    PBYTE	UasmCode;
    DWORD	BaseAddress;
    //	!!!Initialized by parameter!!!

    DWORD	CodeCount;       /*  It's code's number.   */
    
    DWORD	OpSize;
    DWORD	AdrSize;


    DWORD Global_OFFSET(PSTR outbuf,PBYTE codebuf,POPERITEM op);
    DWORD Global_MEMORY(PSTR outbuf,PBYTE codebuf,POPERITEM op);
    DWORD Global_MODRM(PSTR outbuf,PBYTE codebuf,POPERITEM op);
    BYTE	GetByte();
    WORD	GetWord();
    DWORD	GetDWord();
    BYTE	GetByteEx();
    WORD	GetWordEx();
    DWORD	GetDWordEx();
    DWORD Global_NEARPTR(PSTR outbuf,PBYTE codebuf,POPERITEM op);
    DWORD Global_FARPTR(PSTR outbuf,PBYTE codebuf,POPERITEM op);
    void	OpSizePrefix();
    void	AdrSizePrefix();
    BYTE Global_GetSize(DWORD srcsize);
    DWORD	ProcessOpdata(DWORD opdata,POPERITEM op,PSTR outbuf,DWORD codepos);
    void	SetError(DWORD errcode);
    void	DisassemblerOne();  
    void	ProcessGroup(PINSTRUCTION pG,PINSTRUCTION inst);
    void	ProcessInstruction(	DWORD	opcode,
    							PSTR	instname,
    							DWORD	opdata1,
    							DWORD	opdata2,
    							DWORD	opdata3);
    CString	ProcessSegPrefix(POPERITEM op);
    
public:
    BYTE	Disasm_OneCode(ea_t &pos);
    XCPUCODE* get_xcpu();
    DWORD   Disassembler_X(PBYTE codebuf, DWORD eip, OUT st_IDA_OUT* idaout);
};

#endif //DASM__H
