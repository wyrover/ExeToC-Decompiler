///////////////////////////////////////////////////////////////
//
// KS_OutBuf.h
// Copyright(C) 1999-2002 KnlSoft Inc. All right reserved
// Created at 2002.1.26
// Description:	The interface description of the component
// History:		
//
///////////////////////////////////////////////////////////////
//#include "..\..\KS_OutBuf\KS_OutBuf.H"
//#include "../I_KSUNKNOWN/KS_OutBuf.h"
//using namespace KS;

#ifndef	_KS_OUTBUF_H_
#define	_KS_OUTBUF_H_

namespace KS
{
typedef const BYTE* PCBYTE;

class COutBuf
{
	COutBuf(const COutBuf&);	//不允许自我复制
public:
	COutBuf(int step = 256)
	{
		m_step = step;
		m_pbuf = NULL;
		m_bufsiz = m_allocsiz = 0;
	}
	~COutBuf(){clear();}
	virtual void clear()
	{
		if (m_pbuf)
			delete m_pbuf;
		m_pbuf = NULL;
		m_bufsiz = m_allocsiz = 0;
	}

public:
	//Add interface here
	virtual PBYTE __stdcall GetWritableBuf(){return m_pbuf;}
	virtual const BYTE* __stdcall GetBuf() const
		{return m_pbuf;}
	virtual int   __stdcall BufSize() const
		{return m_bufsiz;}
	virtual bool   __stdcall IfEmpty() const
		{return (m_bufsiz == 0);}
	virtual bool  __stdcall Out1Byte(BYTE b1){BYTE b=b1;return OutPut(&b,1);}
	virtual bool  __stdcall OutDWORD(DWORD d1){DWORD d = d1;return OutPut(&d,4);}
	virtual PCSTR __stdcall c_str()
	{
		if (this->m_allocsiz == this->m_bufsiz)
		{
			this->Out1Byte(0);
			this->m_bufsiz--;
		}
		else
		{
			m_pbuf[m_bufsiz] = 0;
		}
		return (PCSTR)m_pbuf;
	}
	virtual bool  __stdcall OutStr(PCSTR pszStr)
		{return OutPut(pszStr,strlen(pszStr));}

	virtual bool  __stdcall OutPut(const void* pbuf, int buflen)
	{
		if (buflen == 0)
			return true;
		if (m_bufsiz + buflen > m_allocsiz)
		{
			int sz = m_bufsiz + buflen;
			sz += m_step-1;
			sz -= sz % m_step;
			BYTE* pnew = new BYTE[sz];
			if (pnew == NULL)
				return false;
			if (m_bufsiz != 0)
				memcpy(pnew, m_pbuf, m_bufsiz);
			delete m_pbuf;
			m_pbuf = pnew;
			m_allocsiz = sz;
		}
		memcpy(m_pbuf + m_bufsiz, pbuf, buflen);
		m_bufsiz += buflen;
		return true;
	}
	virtual bool  __cdecl prtf(PCSTR fmt, ...)
	{
		va_list arglist;
		va_start(arglist, fmt);
		char achTempBuf[4096];
		int nLen = vsprintf(achTempBuf, fmt, arglist);
		return this->OutPut(achTempBuf, nLen);
	}
	virtual bool __stdcall ReadFile(PCSTR pcszFilePath)
	{
		FILE* hFile = fopen(pcszFilePath, "rb");
		if (hFile == NULL)
			return false;
		fseek(hFile, 0, SEEK_END);
		DWORD sz = ftell(hFile);
		fseek(hFile, 0, SEEK_SET);
		if (sz == 0)
		{
			fclose(hFile);
			return true;
		}
		PBYTE pnew = new BYTE[sz];
		DWORD readsz = fread(pnew, 1, sz, hFile);
		fclose(hFile);
		if (readsz != sz)
		{
			delete pnew;
			return false;
		}
		//assert(m_pbuf == NULL);
		//assert(m_bufsiz == 0);
		m_pbuf = pnew;
		m_bufsiz = m_allocsiz = sz;
		return true;
	}
	virtual bool __stdcall WriteToFile(PCSTR pcszFilePath)
	{
		FILE* ff = fopen(pcszFilePath,"wb");
		if (ff)
		{
			fwrite(this->GetBuf(), this->BufSize(),1,ff);
			fclose(ff);
			return true;
		}
		return false;
	}

	virtual bool __stdcall OutPut_2(COutBuf* p)
	{
		return this->OutPut(p->GetBuf(),p->BufSize());
	}
	virtual void __stdcall SetStep(int step)
	{
		m_step = step;
	}
	virtual void __stdcall Align(int n)
	{
		while (m_bufsiz % n)
		{
			this->Out1Byte(0);
		}
	}

	//Add interface here

private:
	//Add member here
	int   m_step;
	PBYTE m_pbuf;
	int   m_bufsiz;
	int   m_allocsiz;
	//Add member here

};


class COneTimeBuf
{
	BYTE* m_pBuf;
	int m_size;
	COneTimeBuf(const COneTimeBuf&);		//不允许自我复制
public:
	COneTimeBuf() { m_pBuf = NULL; m_size = 0;}
	virtual ~COneTimeBuf()
	{
		if (m_pBuf != NULL)
			delete m_pBuf;
	}
	virtual bool __stdcall NewBuf(int size)
	{
		if (m_pBuf != NULL)
			return false;
        m_pBuf = new BYTE[size];
		if (m_pBuf == NULL)
			return false;
		ZeroMemory(m_pBuf,size);
		m_size = size;
		return true;
	}
	BYTE* __stdcall GetBuf()
	{
		return m_pBuf;
	}
	int __stdcall GetSize()
	{
		return m_size;
	}
	BYTE* __stdcall GetBuf_and_ClearSelf()
	{	//一般不要用这个api，这里把指针取出，由外部来delete
		BYTE* p = m_pBuf;
		m_pBuf = NULL;
		return p;
	}
};

}	//	namespace KS


#endif	// _KS_OUTBUF_H_
