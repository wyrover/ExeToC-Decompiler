// Copyright(C) 1999-2005 LiuTaoTao£¬bookaa@rorsoft.com

#include "stdafx.h"
#include	"CISC.H"

void __stdcall	outstring_in_log(PCSTR str);

void	error(PSTR msg)
{
	alert(msg);
    exit(0);
}
void	alert(PSTR msg)
{
	MessageBoxA(0,msg,"EXE2C alert",0);
}
int		alert_prtf(PCSTR fmt,...)
{
    va_list argptr;
    int cnt;
	char buf[280];

    va_start(argptr, fmt);
    cnt = vsprintf(buf, fmt, argptr);
    va_end(argptr);

	alert(buf);

    return(cnt);
}

int log_prtf(PCSTR fmt,...)
{
    va_list argptr;
    int cnt;
	char buf[280];

    va_start(argptr, fmt);
    cnt = vsprintf(buf, fmt, argptr);
    va_end(argptr);

	outstring_in_log(buf);

    return(cnt);
}
int log_prtl(PCSTR fmt,...)
{
    va_list argptr;
    int cnt;
	char buf[280];

    va_start(argptr, fmt);
    cnt = vsprintf(buf, fmt, argptr);
    va_end(argptr);

	outstring_in_log(buf);
	outstring_in_log("\n");

    return(cnt);
}



void _stdcall _warn(char * __cond, char * __file, int __line)
{
	char	buf[280];
	sprintf(buf,"Warn condition %s, in file %s, at line %d",
			__cond,
			__file,
			__line);
	MessageBoxA(0,buf,"warn",0);
}

void* cdecl operator new(size_t size)        // Reload NEW !
{
	PVOID p = malloc((DWORD)size);
	if( p )
		memset(p,0,(DWORD)size);
	else
		alert("new: not enough memory");
	return p;
}

void cdecl operator delete(void* p)         // Reload DELETE !
{
	free(p);
}

PSTR new_str(PCSTR p)
{
	PSTR pnew = new char[strlen(p)+1];
	strcpy(pnew,p);
	return pnew;
}

PCSTR prt_DWORD(DWORD d)
{
	static char s[16];
	if (d < 16 || (d % 100) == 0)
		sprintf(s,"%d",d);
	else
		sprintf(s,"0x%x",d);
	return s;
}


