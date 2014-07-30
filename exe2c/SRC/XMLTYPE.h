// Copyright(C) 1999-2005 LiuTaoTao，bookaa@rorsoft.com

//	XmlType.h

#ifndef	XmlType_H
#define	XmlType_H

enum XMLTYPE
{
	XT_invalid = 0,
	XT_blank,
	XT_Symbol,
	XT_Function,
	XT_Keyword,		//关键字，比如struct,union,for,while
	XT_Class,		//是个class或union或struct的名字
	XT_K1,			//{} []
	XT_Comment,		//注解
	XT_DataType,	//数据类型
	XT_Number,		//一个数
	XT_AsmStack,	//堆栈值
	XT_AsmOffset,	//汇编显示时，seg:offset
	XT_AsmLabel,	//汇编显示时，label name
    XT_FuncName,
};

#define	COLOR_DEFAULT	RGB(255,255,255)

COLORREF XmlType_2_Color(XMLTYPE xmltype);

void XML_Clicked(XMLTYPE xmltype, PVOID p);

#endif	//	XmlType_H
