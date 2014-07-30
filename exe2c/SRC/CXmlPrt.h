// Copyright(C) 1999-2005 LiuTaoTao，bookaa@rorsoft.com

//	CXmlPrt.h

#ifndef	CXmlPrt_H
#define CXmlPrt_H

#include "CXmlList.h"
#include "CMyString.h"

#include "../EXE2C.h"   //for I_XmlOut


class CXmlPrt : public I_XmlOut
{
	CXmlList* 	m_xmllist;
	CMyString*	m_str;

	XMLTYPE m_curword_type;
	PVOID	m_curword_p;

	CString GetLine(int nLine);
    int GetPosXY(int x, int y);
public:

	CXmlPrt();
	~CXmlPrt();
	
	virtual void __stdcall prtt(PCSTR s);
	virtual void __stdcall XMLbegin(enum XMLTYPE xmltype, PVOID p);
	virtual void __stdcall XMLend(enum XMLTYPE xmltype);

	void	prtprtout(class CXmlOutPro* prt);

	void Clear();
	void Clicked(long x1,long x2);
	BOOL GetRightWord(long curpos, long &posfrom, long &posto);
	BOOL GetLeftWord(long curpos, long &posfrom, long &posto);
	BOOL GetCurWord(long curpos, long &posfrom, long &posto);
	int MoveHome(int nLine);
	int MoveLeftWord(int x, int y);
	int MoveRightWord(int x, int y);
	int WordToLeft(int x, int y);
	int WordToRight(int x, int y);
    CString GetText(int y1, int x1, int y2, int x2);
	
    void GetItem(int x, int y, OUT enum XMLTYPE& xmltype, OUT PVOID& p);
	void Display(I_COLOROUT* iColorOut);
    int GetLineCount();
    int GetLineLength(int nLine);
    CString GetString();
    void CommaLast();
    bool SetCurWord(int x, int y);
};

class CXmlOutPro
{
    I_XmlOut* m_out;
	UINT    m_nIdent;
    bool b_OneLine;
    bool fHasSpace;
public:
	BOOL	m_f_prt_in_1line;	//	为true表明要求输出到一行上，不能有回车
	BOOL	m_f_prt_in_comma;	//	为 1 表明用','代替';'
    CXmlOutPro(I_XmlOut* out)
    {
        fHasSpace = false;
        b_OneLine = false;
        m_out = out;
        m_f_prt_in_1line = FALSE;
        m_f_prt_in_comma = FALSE;
        m_nIdent = 0;
    }
	void prtt(PCSTR s)
    {
        if (fHasSpace)
            this->m_out->prtt(" ");
        fHasSpace = false;
        
        this->m_out->prtt(s);
    }
	void prtslen(PCSTR s, int len);
	void XMLbegin(enum XMLTYPE xmltype, PVOID p)
    {
        if (fHasSpace)
            this->m_out->prtt(" ");
        fHasSpace = false;
        this->m_out->XMLbegin(xmltype,p);
    }
	void XMLend(enum XMLTYPE xmltype)
    {
        this->m_out->XMLend(xmltype);
        this->fHasSpace = true;
    }
    void prtspace(int n = 1)
    {
        for (int i=0; i<n; i++) prtt(" ");
    }
	void prtf(PCSTR fmt,...);
	void prtl(PCSTR fmt,...);
	void	EOL();		//	一般情况下，是";\n"
    void endline();
    void SetOneLine(bool b)
    {
        b_OneLine = b;
        if (b)
        {
            m_f_prt_in_1line = true;
            m_f_prt_in_comma = true;
        }
        else
        {
            m_f_prt_in_1line = false;
            m_f_prt_in_comma = false;
        }
    }

	
	void	ident_add1();
	void	ident_sub1();
	void    ident();
	void 	prtl_ident(PSTR fmt,...);
    void 	prtf_ident(PSTR fmt,...);
    void    nospace()
    {
        fHasSpace = false;
    }

    //这个class的用意是，界面给我们提供了一个I_XmlOut，使用起来不方便
    //需要扩展一下
};

#endif	//	CXmlPrt_H
