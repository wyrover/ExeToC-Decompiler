// Copyright(C) 1999-2005 LiuTaoTao，bookaa@rorsoft.com

// INSTR.h
#ifndef INSTR__H
#define INSTR__H

class	CFunc;

class INSTR;
typedef	INSTR*	PINSTR;

enum em_InstrAddOn
{
    IA_Nothing = 0,
    IA_AddImmed,    //简单地加立即数
    IA_MulImmed,    //简单地乘立即数
    IA_ReadPointTo, //*
    IA_GetAddress,  //&
};
struct st_InstrAddOn
{
    em_InstrAddOn type;
    union
    {
        struct
        {
            signed int iAddon;
        } addimmed; //for IA_AddImmed
    };

    st_InstrAddOn* pChild;

    st_InstrAddOn()
    {
        ZeroMemory(this, sizeof(st_InstrAddOn));
    }
    ~st_InstrAddOn()
    {
        if (pChild)
            delete pChild;
    }
    static bool IsSame(st_InstrAddOn* p1, st_InstrAddOn* p2);
};
typedef st_InstrAddOn* Pst_InstrAddOn;

struct VAR_ADDON
{
	VAR*	pv;
    st_InstrAddOn* pao; //point add on
    VAR_ADDON()
    {
        pv = NULL;
        pao = NULL;
    }
    ~VAR_ADDON()
    {
        //do not delete pv
        if (pao)
            delete pao;
    }
};

class INSTR
{
public:
	HLType	type;	//	i_Assign ...
    union
	{
		struct
		{
			JxxType	jmp_type;	//JMP_???
			DWORD   jmpto_off;
			PINSTR the_label;
			PINSTR next_ref_of_this_label;	//这里组成个链，用来保存对一个label的所有ref
		} jmp;					//for type = i_Jump only

		struct
		{
			PINSTR  ref_instr;	//for type = i_Label only
			ea_t	label_off;
			bool	f_conti;
		} label;

		struct
		{
			CFunc*  call_func;		// for i_Call
			CApi*	papi;			// for i_CallApi
			signed int		esp_level;
            PINSTR      p_callpara;
            PINSTR      p_callret;
		} call;

        struct
        {
            PINSTR      p_thecall;
        } call_addon;   //for i_CallPara and i_CallRet

		struct
		{
			PINSTR		m_end;		// for i_Begin
			enum_COMP	type;		// COMP_if
			PINSTR		m_break;	// 如果允许 break 的话，这是break到的label
			PINSTR		m_conti;	// 如果允许 continue 的话，这是continue到的label
			PINSTR		m_not_conti;	//	尽管这个jmp指向m_conti，它仍然不是continue.
		} begin;						//	这个特例是为了照顾while

        struct
        {
            signed int esp_level;
            UINT howlen;
        } espreport;    // for i_EspReport
	};

	VAR		var_w;
    VAR_ADDON va_r1;    //va=Var AddOn
    VAR_ADDON va_r2;
	VAR		var_r1;
	VAR		var_r2;
	DWORD	i1;	// =4, 当type == i_Address时，[eax+ebx*4+8888]
	DWORD	i2;	// =8888

	INSTR();
	~INSTR();

	//optim serials functions
	bool	optim_1_();
	bool	optim_4_();
	bool	optim_3_();
	bool	optim_3_1(PINSTR p);
	void	optim_3_2(PINSTR p);
	//-----------------
};

typedef	CList<PINSTR,PINSTR> INSTR_LIST;

class CInstrList
{
    bool	if_Ly_In(PINSTR p, POSITION firstpos, POSITION endpos);
    bool IsSwitchCase_multcomp(PINSTR begin);
    bool IsSwitchCase(PINSTR begin);
    bool	ifOneStatement(PINSTR pNode, POSITION firstpos, POSITION endpos);
    bool	Flow_c(PINSTR pNode);
    void	Flow_b(PINSTR pParentNode, POSITION firstpos, POSITION endpos);
    bool	Flow_aa(PINSTR pNode, POSITION firstpos, POSITION endpos);
    bool	Flow_cc(PINSTR pNode, POSITION firstpos, POSITION endpos);
    void	Add_Begin_End(POSITION firstpos, POSITION endpos, PINSTR begin, PINSTR end);
    void	Add_Begin_End_1(POSITION firstpos, POSITION endpos, PINSTR begin, PINSTR end);
    
    INSTR_LIST* m_list; //要尽量把它private
public:
    CInstrList(INSTR_LIST* p)
    {
        m_list = p;
    }

    bool	Flow_a(PINSTR pNode);
};

class CInstrList_Finger
{
    void	prt_partern(PINSTR phead, PSTR partern_buf);
    static int search_and_add(DWORD* buf,DWORD val,int* pn);
    static bool	finger_compare(PSTR f1,const char* f2);
public:
    INSTR_LIST* m_list; //要尽量把它private
    CInstrList_Finger(INSTR_LIST* p)
    {
        m_list = p;
    }
    bool	Finger_check_partern(PINSTR p);
    bool	Finger_check_partern_for1(PINSTR p);
};
#endif // INSTR__H
