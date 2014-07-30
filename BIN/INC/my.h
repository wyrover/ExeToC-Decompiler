//	exe2c include file
//	edit this file to add new function define

typedef DWORD size_t;
typedef DWORD UINT;

typedef void *PVOID;
typedef void *LPVOID;
typedef PVOID HANDLE;
typedef int                 BOOL;


typedef HANDLE HWND;

int __stdcall MessageBoxA(HWND, char *, char *, DWORD);

typedef HANDLE HINSTANCE;

typedef char *LPSTR, *PSTR;
//typedef char *PSTR;
//typedef char *LPSTR;

typedef long LONG;

#include "stdio.h"
#include "stdlib.h"
#include "windef.h"
#include "winbase.h"
#include "winuser.h"
#include "mfc42.h"
#include "winsock2.h"
#include "winnls.h"	
#include "test.h"
//	----------------------------------------------------------------


int __stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine,int nCmdShow);
//int __stdcall _WinMain@16(HINSTANCE hInst,HINSTANCE hPreInst,LPSTR lpszCmdLine,int nCmdShow)

extern "C" {
	void __cdecl EH_prolog();
	void __stdcall CxxThrowException(int, int);
	int __cdecl main(int argc, char * argv[]);	
}

