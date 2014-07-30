// Copyright(C) 1999-2005 LiuTaoTao£¬bookaa@rorsoft.com

//	CXmlList.cpp

#include "stdafx.h"
#include	"00000.h"
#include	"CXmlList.h"
#include <assert.h>

CXmlList* CXmlList::new_CXmlList(XMLTYPE xmltype, PVOID p, UINT posfrom)
{//static int
    CXmlList* pnew = new CXmlList(0);
	ZeroMemory(pnew, sizeof(CXmlList));
    pnew->m_xmltype = xmltype;
    pnew->m_p = p;
    pnew->m_posfrom = posfrom;
    pnew->m_posto = (UINT)-1;
    pnew->m_sub = NULL;
    pnew->m_next = NULL;
    return pnew;
}
CXmlList::~CXmlList()
{
	if (this->m_sub)
		delete m_sub;
	if (this->m_next)
		delete m_next;
	this->m_sub = NULL;
	this->m_next = NULL;
}

CXmlList* CXmlList::GetLast_willbegin()
{
	CXmlList* p = this;
	while (p)
	{
		if (p->m_posto == (UINT)-1)
		{
			if (p->m_sub == NULL)
				return p;
			return p->m_sub->GetLast_willbegin();
		}
		if (p->m_next == NULL)
			return p;
		p = p->m_next;
	}
	assert(0);
	return NULL;
}
CXmlList* CXmlList::GetLast_willend()
{
	CXmlList* p = this;
	while (p)
	{
		if (p->m_posto == (UINT)-1)
		{
			if (p->m_sub == NULL)
				return p;
			CXmlList* p1 = p->m_sub->GetLast_willend();
			if (p1 != NULL)
				return p1;
			return p;
		}
		p = p->m_next;
	}
	return NULL;
}
void CXmlList::XMLbegin(XMLTYPE xmltype, PVOID p0, UINT pos)
{
	CXmlList* p = this->GetLast_willbegin();
    if (p->m_xmltype == XT_invalid)
    {
        p->m_xmltype = xmltype;
        p->m_p = p0;
        p->m_posfrom = pos;
        return;
    }
	
	CXmlList* pnew = new_CXmlList(xmltype, p0, pos);
	
	if (p->m_posto == (UINT)-1)
	{
		assert(p->m_sub == NULL);
		p->m_sub = pnew;
		return;
	}
	
	assert(p->m_next == NULL);
	p->m_next = pnew;
}
XMLTYPE CXmlList::XMLend(XMLTYPE xmltype, UINT pos)
{
	CXmlList* p = this->GetLast_willend();
	assert(p);
	assert(p->m_xmltype == xmltype);
	assert(p->m_posto == (UINT)-1);

	p->m_posto = pos;

	p = this->GetLast_willend();
	if (p)
		return p->m_xmltype;
	return XT_invalid;
}

void CXmlList::Clicked(long x1, long x2)
{
	long u1,u2;
	CXmlList* p = this->GetCurWord(x1,u1,u2);
	if (p == NULL)
		return;
	if (u1 != x1 || u2 != x2)
		return;
	XML_Clicked(p->m_xmltype, p->m_p);

}
CXmlList* CXmlList::GetCurWord(UINT curpos, long &posfrom, long &posto)
{
	CXmlList* p = this;
	while (p)
	{
		if (curpos < p->m_posfrom)
			return NULL;

		if (p->m_sub)
		{
			CXmlList* p1 = p->m_sub->GetCurWord(curpos,posfrom,posto);
			if (p1)
				return p1;
		}
		else if (curpos >= p->m_posfrom
			&& curpos < p->m_posto
			&& p->m_posto != -1)
		{
			posfrom = p->m_posfrom;
			posto = p->m_posto;
			return p;
		}
		p = p->m_next;
	}
	return NULL;
}
BOOL CXmlList::GetLeftWord(long curpos, long &posfrom, long &posto)
{
	for (int i=0;i<2;i++)
	{
		if (NULL != this->GetCurWord(curpos,posfrom,posto))		
			return TRUE;
		if (curpos == 0)
			return FALSE;
		curpos--;
	}
	return FALSE;
}

BOOL CXmlList::GetRightWord(long curpos, long &posfrom, long &posto)
{
	for (int i=0;i<2;i++)
	{
		if (NULL != this->GetCurWord(curpos,posfrom,posto))
			return TRUE;
		curpos++;
	}
	return FALSE;
}

#include "CXmlPrt.h"
void CXmlList::prtprtout(PCSTR str, CXmlOutPro* prt)
{
    prt->XMLbegin(this->m_xmltype, this->m_p);

    UINT k_pos = this->m_posfrom;

    CXmlList* p = this->m_sub;
    while (p)
    {
        //	------------------------------------
        if (p->m_posfrom > k_pos)
        {
            long len = p->m_posfrom - k_pos;
            prt->prtslen(str,len);

            str += len;
            k_pos += len;
        }
        //	------------------------------------
        {
            long len = p->m_posto - k_pos;
            p->prtprtout(str, prt);     //µÝ¹é
            str += len;
            k_pos += len;
        }

        p = p->m_next;
    }
    if (this->m_posto > k_pos)
        prt->prtslen(str, this->m_posto - k_pos);
    else if (this->m_posto == -1) 
        prt->prtt(str);

    prt->XMLend(this->m_xmltype);
}
void CXmlList::Display(PCSTR pstr, I_COLOROUT* iColorOut, XMLTYPE curw_xmltype, PVOID curw_p)
{
	if (curw_xmltype != XT_invalid && curw_p != NULL)
	if (curw_xmltype == this->m_xmltype && curw_p == this->m_p)
	{
		iColorOut->SetBKColor(RGB(255,255,0));
	}
	COLORREF k_color = XmlType_2_Color(this->m_xmltype);
	UINT k_pos = this->m_posfrom;

	CXmlList* p = this->m_sub;
	while (p)
	{
		//	------------------------------------
		if (p->m_posfrom > k_pos)
		{
			long len = p->m_posfrom - k_pos;
			iColorOut->ColorOut(pstr, len, k_color);
			pstr += len;
			k_pos += len;
		}
		//	------------------------------------
		{
            assert(k_pos == p->m_posfrom);
			assert(p->m_posto != -1);
			long len = p->m_posto - p->m_posfrom;
			p->Display(pstr, iColorOut, curw_xmltype, curw_p);
			pstr += len;
			k_pos += len;
		}

		p = p->m_next;
	}
	if (this->m_posto > k_pos)
	{
		long len = this->m_posto - k_pos;
		iColorOut->ColorOut(pstr, len, k_color);
	}
	else
	{
		iColorOut->ColorOut(pstr, strlen(pstr), k_color);
	}
	if (curw_xmltype != XT_invalid && curw_p != NULL)
	if (curw_xmltype == this->m_xmltype && curw_p == this->m_p)
	{
		iColorOut->SetBKColor(RGB(0,0,0));
	}
}
