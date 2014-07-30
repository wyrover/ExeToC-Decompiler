// Copyright(C) 1999-2005 LiuTaoTao，bookaa@rorsoft.com

#include "stdafx.h"
#include "00000.h"
#include "CCbuf.h"

#include <io.h>

//	----------------------------------------------------------
CCbuf::CCbuf()
{
	this->f_str = 0;
}


void CCbuf::LoadFile(FILE *f)
{
	long flen = filelength(fileno(f));
	char *buf = new char[flen];
	fread(buf,1,flen,f);
	
	m_p = new char[flen+1];	//thats enough
	m_len = 0;

	for (long i = 0; i < flen; i++)
	{
		OneChar(buf[i]);
	}
	OneChar(EOF);
	delete buf;
	assert((long)m_len <= flen+1);
}

void CCbuf::OneLine(PCSTR pstr)
{
	while (*pstr)
	{
		OneChar(*pstr++);
	}
	OneChar(0);
}
void CCbuf::OneChar(int c3)
{	
	if (c3 == 0)
		c3 = 0;
	if (c3 == '\r')
		c3 = '\n';

	//	c3 是 input char 或 EOF
	//	如果有效，则把c3 加到p所指的buf，同时 len++
	int i = m_len;
	PSTR p = m_p;

	if (c3 == EOF)
	{
		assert(f_str == 0);
		OneChar(0);
		return;
	}
	char c = (char)c3;

	if ( f_str == 0)
	if ( i >= 2)
	{
		if (p[i-2] == '/' && p[i-1] == '/')
		{
			if (c == '\n' || c == 0)
			{
				m_len -= 2;
				OneChar(0);
				return;
			}
			else
				return;	//do nothing
		}
		if (p[i-2] == '/' && p[i-1] == '*')
		{
			static char c1 = 0;
			if (c1 == '*' && c == '/')
			{
				m_len -= 2;
				return;
			}
			c1 = c;
			return;
		}
	}

	if ( f_str )
	{
		static BOOL f = FALSE;	//	for '\\'
		if (c == 0 || c == '\n')
			assert(("hello",0));	//error !
		if (f)
		{
			f = FALSE;
		}
		else
		{
			if (c == '\\')
				f = TRUE;
			if (c == f_str)
				f_str = 0;
		}
	}
	else
	{
		if (c == '\'' || c == '\"')
			f_str = c;
	}
	
	
	switch (c)
	{
	case 0:
	case '\n':
		p[i] = 0;
		m_len++;
		if (i > 0)
		{
			//	把后面的空格去掉
			//	空行去掉
			if (p[i-1] == ' ' || p[i-1] == '\0')
			{
				p[i-1] = 0;
				m_len--;
				return;
			}
			//	检查是不是拐行符
			if ( p[i-1] == '\\')
			{
				m_len -= 2;
				return;		//	不拐了
			}
		}
		break;
	case '\t':
	case ' ':
		if (i == 0 || p[i-1] == '\0')
			break;	//	第一个字符就是空格是不允许的

		if (f_str == 0 && p[i-1] == ' ')
			break;	//	如果前面已经有一个空格，就算了

		c = ' ';
		//continue to next
	default:
		p[i] = c;
		m_len++;
		break;
	}
}

