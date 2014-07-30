#include "stdafx.h"
#include <stdio.h>
#include "test_class.h"

CTest1::CTest1()
{
	id1 = 80;
	id2 = new char[80];
	strcpy(id2, "hello world");
}
CTest1::~CTest1()
{
	if (id2 != NULL)
		delete id2;
}

void CTest1::func1()
{
	printf("test class %d %s\n",
		this->id1,
		this->id2);
}