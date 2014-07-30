///////////////////////////////////////////////////////////////
//
// KS_OutBuf.h
// Copyright(C) 1999-2002 KnlSoft Inc. All right reserved
// Created at 2002.1.26
// Description:	The interface description of the component
// History:		
//
///////////////////////////////////////////////////////////////
//#include "..\..\KS_OutStr\KS_OutStr.H"
//#include "../I_KSUNKNOWN/KS_OutStr.h"
//using namespace KS;

#ifndef	_KS_OUTSTR_H_
#define	_KS_OUTSTR_H_

namespace KS
{
	class COutStr   
	{
	public:
		COutStr(int step = 256)
		{
			m_step = step;
			m_pbuf = NULL;
			m_bufsiz = m_allocsiz = 0;
		}
		COutStr(const COutStr& str)
		{
			OutStr(str);
		}
		~COutStr()
		{
			clear();
		}
		virtual void clear()
		{
			if (m_pbuf)
				delete m_pbuf;
			m_pbuf = NULL;
			m_bufsiz = m_allocsiz = 0;
		}

	public:
		//Add interface here
		// read buffer
		virtual char* __stdcall GetWritableBuf() const
		{
			return m_pbuf;
		}
		virtual PCSTR __stdcall c_str() const
		{
			return m_pbuf;
		}
		// write buffer
		virtual bool  __stdcall Out1Char(char b1)
		{
			WORD w = (BYTE)b1;
			return OutStr((PCSTR)&w);
		}
		virtual bool  __stdcall OutDWORD(DWORD d1)
		{
			char s[16];
			::sprintf(s, "%d", d1);
			return OutStr(s);
		}
		virtual bool __stdcall OutPut_2(const COutStr& p)
		{
			return this->OutStr(p);
		}
		virtual bool  __stdcall OutStr(PCSTR pszStr)
		{
			int sLen = strlen(pszStr);
			if (0 == sLen)
				return true;
			if (m_bufsiz + sLen +1 > m_allocsiz)
			{
				int sz = m_bufsiz + sLen + 1;
				sz += m_step-1;
				sz -= sz % m_step;
				char* pnew = new char[sz];
				if (pnew == NULL)
					return false;
				if (m_bufsiz != 0)
					strcpy(pnew, m_pbuf);
				delete m_pbuf;
				m_pbuf = pnew;
				m_allocsiz = sz;
			}
			strcpy(m_pbuf + m_bufsiz, pszStr);
			m_bufsiz += sLen;
			return true;
		}
		virtual bool __stdcall OutPut(const void* p, int iLen)
		{
			char* s = new char[iLen+1];
			::memcpy(s, p, iLen);
			s[iLen] = '\0';
			bool b = this->OutStr(s);
			delete s;
			return b;
		}

		// static
		virtual int   __stdcall BufSize() const
		{
			return m_bufsiz;
		}
		virtual int   __stdcall StrLen() const
		{
			if (NULL == m_pbuf)
				return 0;
			return strlen(this->m_pbuf);
		}
		virtual bool   __stdcall IfEmpty() const
		{
			// add by kuhx
			if (NULL == m_pbuf)
				return true;

			return(strlen(this->m_pbuf) == 0);
		}
		virtual bool  __cdecl prtf(PCSTR fmt, ...)
		{
			va_list arglist;
			va_start(arglist, fmt);
			char achTempBuf[4096];
			int nLen = vsprintf(achTempBuf, fmt, arglist);
			return this->OutStr(achTempBuf);
		}
		// store
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
			char* pnew = new char[sz];
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
		virtual bool __stdcall WriteToFile(PCSTR pcszFilePath) const
		{
			FILE* ff = fopen(pcszFilePath, "wt");
			if (ff)
			{
				fwrite(this->c_str(), this->BufSize(), 1, ff);
				fclose(ff);
				return true;
			}
			return false;
		}
		// memeory
		virtual void __stdcall SetStep(int step)
		{
			m_step = step;
		}

		virtual operator PCSTR() const
		{
			return m_pbuf;
		}
		virtual COutStr& operator += (PCSTR pszStr)
		{
			OutStr(pszStr);
			return *this;
		}
		virtual COutStr& operator += (char c)
		{
			Out1Char(c);
			return *this;
		}
		virtual COutStr& operator += (DWORD d)
		{
			OutDWORD(d);
			return *this;
		}
		virtual COutStr& operator + (PCSTR pszStr)
		{
			OutStr(pszStr);
			return *this;
		}
		virtual COutStr& operator + (char c)
		{
			Out1Char(c);
			return *this;
		}
		virtual COutStr& operator + (DWORD d)
		{
			OutDWORD(d);
			return *this;
		}

		//Add interface here

	private:
		//Add member here
		int   m_step;
		char* m_pbuf;
		int   m_bufsiz;
		int   m_allocsiz;
		//Add member here

	};

}	//	namespace KS
#endif	// _KS_OUTSTR_H_
