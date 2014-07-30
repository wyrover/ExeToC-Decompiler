// Copyright(C) 1999-2005 LiuTaoTao£¬bookaa@rorsoft.com

//	CMyString.h
#ifndef	CMyString_H
#define	CMyString_H

const	MEMORY_STEP	= 2048;

class CMyString
{
	UINT	m_maxlen;
	UINT	m_curlen;
	PSTR	m_bufptr;
public:
	CMyString();
	~CMyString();
	
	void strcat(PCSTR str);
	void Clear();
	UINT	GetLength();
	PCSTR	GetString();
	PSTR	GetWritableString();
};

#endif	//	CMyString_H
